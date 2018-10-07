#include "include.h"

//=================内部函数声明=============================================

//=========================================================================
//函数名称：hw_spi_get_base_address                                                        
//功能概要：获取SPI寄存器的基址                                                
//参数说明：spiNo:SPI号      
//函数返回：SPI的基址值                                                                  
//=========================================================================
SPI_MemMapPtr hw_spi_get_base_address(uint8 spiNo);

//=================接口函数实现=============================================

//=========================================================================
//函数名称：hw_spi_init
//函数参数：spiNo：SPI通道号。
//          Master:是否是主机。
//函数返回：无
//功能概要：SPI初始化。
//=========================================================================
void hw_spi_init(uint8 spiNo,uint8 master)
{
    SPI_MemMapPtr BaseAdd = hw_spi_get_base_address(spiNo);
    
    //使能SPI模块时钟，配置SPI引脚功能
    if(spiNo == 0)
    {
        SIM_SCGC6 |= SIM_SCGC6_DSPI0_MASK;
        PORTA_PCR14 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK;//PCS
        PORTA_PCR15 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK;//SCK
        PORTA_PCR16 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK;//SOUT
        PORTA_PCR17 = 0 | PORT_PCR_MUX(0x2);//SIN
    }
    else if(spiNo == 1)
    {
        SIM_SCGC6 |= SIM_SCGC6_DSPI1_MASK;
        PORTE_PCR1 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK;//SOUT
        PORTE_PCR2 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK;//SCK
        PORTE_PCR3 = 0 | PORT_PCR_MUX(0x2);//SIN
        PORTE_PCR4 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK;//PCS0
    }
    /*else 
    {
        SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;
    }*/
    
    SPI_MCR_REG(BaseAdd) = 0 
                 | SPI_MCR_CLR_TXF_MASK     //Clear the Tx FIFO counter.
                 | SPI_MCR_CLR_RXF_MASK     //Clear the Rx FIFO counter.
                 | SPI_MCR_PCSIS_MASK
                 | SPI_MCR_HALT_MASK;

    //根据主从机模式设置工作模式
    if(master == MASTER)
    {
        SPI_MCR_REG(BaseAdd) |= SPI_MCR_MSTR_MASK;//在开始要先停止传输
        SPI_CTAR_REG(BaseAdd,0) = 0
                       | SPI_CTAR_DBR_MASK
                       | SPI_CTAR_FMSZ(0x08)
                       | SPI_CTAR_PDT_MASK//延时因子为7  可以改小点 就是每次传输完成之后立马下一次
                       | SPI_CTAR_BR(0)//2分频
                       | SPI_CTAR_CPOL_MASK 
                       | SPI_CTAR_CPHA_MASK;
    }
    else
    {
        SPI_CTAR_SLAVE_REG(BaseAdd,0) = 0 
                            | SPI_CTAR_SLAVE_FMSZ(0x08)
                            | SPI_CTAR_SLAVE_CPOL_MASK 
                            | SPI_CTAR_SLAVE_CPHA_MASK; 
    }
 
    SPI_SR_REG(BaseAdd) = (SPI_SR_EOQF_MASK
                         | SPI_SR_TFUF_MASK
                         | SPI_SR_TFFF_MASK
                         | SPI_SR_RFOF_MASK
                         | SPI_SR_RFDF_MASK);
    
    SPI_MCR_REG(BaseAdd) &= ~SPI_MCR_HALT_MASK;
}


//=========================================================================
//函数名称：hw_spi_send
//函数参数：spiNo：SPI通道号。
//          data[]：需要发送的数据。
//          len：数据长度。
//函数返回：无
//功能概要：SPI发送数据。
//=========================================================================
//uint32 hw_spi_send(uint8 spiNo,uint8 data[],uint32 len)
uint32 SPI_ReadWriteByte(uint8 spiNo,unsigned char buffer)
{
    uint32 RX_Data;
    SPI_MemMapPtr BaseAdd = hw_spi_get_base_address(spiNo);
    
    SPI_SR_REG(BaseAdd) = (SPI_SR_EOQF_MASK
         | SPI_SR_TFUF_MASK
         | SPI_SR_TFFF_MASK
         | SPI_SR_RFOF_MASK
         | SPI_SR_RFDF_MASK)
      ;
    SPI_MCR_REG(BaseAdd) |= SPI_MCR_CLR_TXF_MASK | SPI_MCR_CLR_RXF_MASK  ;
#if 0              
    for(i = 0;i < len;i++)
    {
        if(i == (len - 1))
        {
                SPI_PUSHR_REG(BaseAdd) = 0 
                               | SPI_PUSHR_CTAS(0)
                               | SPI_PUSHR_EOQ_MASK
                               | SPI_PUSHR_PCS(1)
                               | SPI_PUSHR_TXDATA(data[i]);
        }
        else
        {
                SPI_PUSHR_REG(BaseAdd) = 0 | SPI_PUSHR_CONT_MASK 
                               | SPI_PUSHR_CTAS(0)
                               | SPI_PUSHR_PCS(1)
                               | SPI_PUSHR_TXDATA(data[i]);
        }
    }
#endif
    
#if 1
    SPI_SR_REG(BaseAdd) |= SPI_SR_TCF_MASK;                         //清除发送完成标志
    
    SPI_PUSHR_REG(BaseAdd) = (SPI_PUSHR_CTAS(0)                     //选择CTAR0寄存器定义传输特性
                          | SPI_PUSHR_EOQ_MASK                      //该帧SPI数据是最后一帧数据
                          | SPI_PUSHR_TXDATA(buffer));              //写入数据
    
    SPI_MCR_REG(BaseAdd) &= ~SPI_MCR_HALT_MASK;                     //启动SPI数据传输
    
    while((SPI_SR_REG(BaseAdd) & SPI_SR_TCF_MASK) == 0);            //等待发送完成

#endif
  
    SPI_SR_REG(BaseAdd) |= SPI_SR_TCF_MASK;                         //清除传送完成标志
    
    while((SPI_SR_REG(BaseAdd) & SPI_SR_RFDF_MASK) == 0);           //等待接收缓冲区有有效数据，即等待RX FIFO不为空为止
    
    RX_Data = (uint8)SPI_POPR_REG(BaseAdd);                         //读取RX FIFO内部数据
    
    SPI_SR_REG(BaseAdd) |= SPI_SR_RFDF_MASK;                        //清除RX FIFO不为空标志
    
    SPI_MCR_REG(BaseAdd) |= SPI_MCR_HALT_MASK;                      //停止SPI数据传输
    
    return (RX_Data);

}

//=========================================================================
//函数名称：hw_spi_re
//函数参数：spiNo：SPI通道号。
//          data[]：需要接收的数据。
//函数返回：0：成功 1：失败
//功能概要：SPI接收数据。
//=========================================================================
uint8 hw_spi_re(uint8 spiNo,uint8 data[])
{
      SPI_MemMapPtr BaseAdd = hw_spi_get_base_address(spiNo);

      if(SPI_SR_REG(BaseAdd) & SPI_SR_RFDF_MASK)
      {
    	      data[0] = (uint8)SPI_POPR_REG(BaseAdd);                
              SPI_SR_REG(BaseAdd) |= SPI_SR_RFDF_MASK;
              return 1;
      }
        SPI_SR_REG(BaseAdd) = (SPI_SR_EOQF_MASK
                              | SPI_SR_TFUF_MASK
                              | SPI_SR_TFFF_MASK
                              | SPI_SR_RFOF_MASK
                              | SPI_SR_RFDF_MASK);

      SPI_MCR_REG(BaseAdd) |= SPI_MCR_CLR_TXF_MASK      //Clear the Tx FIFO counter.
                | SPI_MCR_CLR_RXF_MASK;                 //Clear the Rx FIFO counter.
      return 0;
}

//=========================================================================
//函数名称：hw_spi_enable_re_int
//参数说明：spiNo: SPI号
//函数返回： 无
//功能概要：开SPI接收中断
//=========================================================================
/*
void hw_spi_enable_re_int(uint8 spiNo)
{
    SPI_MemMapPtr BaseAdd = hw_spi_get_base_address(spiNo);
    BSET(SPI_RSER_RFDF_RE_SHIFT, SPI_RSER_REG(BaseAdd));//开放SPI接收中断
    enable_irq(spiNo + SPI0IRQ);			 //开接收引脚的IRQ中断
}
*/
//=========================================================================
//函数名称：hw_spi_disable_re_int
//参数说明：spiNo: SPI号
//函数返回： 无
//功能概要：关SPI接收中断
//=========================================================================
/*
void hw_spi_disable_re_int(uint8 spiNo)
{
    SPI_MemMapPtr BaseAdd = hw_spi_get_base_address(spiNo);
    BCLR(SPI_RSER_RFDF_RE_SHIFT, SPI_RSER_REG(BaseAdd));//关闭SPI接收中断
    disable_irq(spiNo + SPI0IRQ);			 //开接收引脚的IRQ中断
}
*/
//=================内部函数实现=============================================
//=========================================================================
//函数名称：hw_spi_get_base_address
//函数参数：spiNo：SPI通道号
//函数返回：无
//功能概要：将SPI通道号转换成对应基指针。
//=========================================================================
SPI_MemMapPtr hw_spi_get_base_address(uint8 spiNo)
{
    switch(spiNo)
    {
    case 0:
      return SPI0_BASE_PTR;
    case 1:
      return SPI1_BASE_PTR;
    case 2:
      return SPI2_BASE_PTR;
    default:
      return 0;
    }
}
//void lqspiinit(void)
void SPI_Configuration(void)
{
  ///先把时钟引脚打开
        SIM_SCGC6 |= SIM_SCGC6_DSPI0_MASK;
        PORTA_PCR14 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK;//PCS0
       // gpio_init(PTA_BASE_PTR,13,1,0);
        PORTA_PCR15 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK;//SCK
        PORTA_PCR16 = 0 | PORT_PCR_MUX(0x2) | PORT_PCR_DSE_MASK;//SOUT
        PORTA_PCR17 = 0 | PORT_PCR_MUX(0x2);                    //SIN
        SPI0_MCR|=SPI_MCR_MSTR_MASK;                            //主机模式
	    SPI0_MCR|=SPI_MCR_PCSIS(1);                             //PCS0低电平有效
        SPI0_MCR&=~SPI_MCR_MDIS_MASK;                           //使能DSPI时钟
	    SPI0_MCR&=~SPI_MCR_HALT_MASK;                           //启动SPI模块
        SPI0_CTAR0|=SPI_CTAR_DBR_MASK;                          //两倍波特率 SCK Duty Cycle
	    SPI0_CTAR0=SPI_CTAR_FMSZ(7);                            //帧大小为8bit
	    SPI0_CTAR0|=SPI_CTAR_PBR(0);//预分频30M//
                                    //00 Baud Rate Prescaler value is 2
                                    //01 Baud Rate Prescaler value is 3.
                                    //10 Baud Rate Prescaler value is 5.
                                    //11 Baud Rate Prescaler value is 7.
	    SPI0_CTAR0|=SPI_CTAR_BR(0x0100); //最终分频180/4=45MHz
                                    //0000 2
                                    //0001 4
                                    //0010 6
                                    //0011 8
                                    //0100 16
                                    //0101 32
                                    //0110 64
                                    //0111 128
                                    //SCK baud rate = (fSYS/PBR) x [(1+DBR)/BR]    
  
}

void SPI_SetSpeed(unsigned char SpeedSet)
{
    if(SpeedSet == SPI_SPEED_LOW)
    {
        SPI0_CTAR0|=SPI_CTAR_DBR_MASK;                          //两倍波特率 SCK Duty Cycle
	    SPI0_CTAR0=SPI_CTAR_FMSZ(7);                            //帧大小为8bit
	    SPI0_CTAR0|=SPI_CTAR_PBR(0);//预分频30M//
                                    //00 Baud Rate Prescaler value is 2
                                    //01 Baud Rate Prescaler value is 3.
                                    //10 Baud Rate Prescaler value is 5.
                                    //11 Baud Rate Prescaler value is 7.
	    SPI0_CTAR0|=SPI_CTAR_BR(0x0100); //最终分频180/4=45MHz
                                    //0000 2
                                    //0001 4
                                    //0010 6
                                    //0011 8
                                    //0100 16
                                    //0101 32
                                    //0110 64
                                    //0111 128
                                    //SCK baud rate = (fSYS/PBR) x [(1+DBR)/BR]     
    }
    else
    {
        SPI0_CTAR0|=SPI_CTAR_DBR_MASK;                          //两倍波特率 SCK Duty Cycle
	    SPI0_CTAR0=SPI_CTAR_FMSZ(7);                            //帧大小为8bit
	    SPI0_CTAR0|=SPI_CTAR_PBR(0);//预分频30M//
                                    //00 Baud Rate Prescaler value is 2
                                    //01 Baud Rate Prescaler value is 3.
                                    //10 Baud Rate Prescaler value is 5.
                                    //11 Baud Rate Prescaler value is 7.
      SPI0_CTAR0|=SPI_CTAR_BR(0);
    }
}


#if 0
void lqwrite(unsigned char cmd)
{ 
    SPI0_PUSHR=cmd;
	while((SPI0_SR&SPI_SR_TCF_MASK)==0);//等待传送完成
	SPI0_SR|=SPI_SR_TCF_MASK;//清除标志	

}
#endif