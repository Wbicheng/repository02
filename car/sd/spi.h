//============================================================================
//文件名称：hw_spi.h
//功能概要：K60 SPI底层驱动程序头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//============================================================================
#ifndef __SPI_H__
#define __SPI_H__

//1 头文件
#include "common.h"

//2 宏定义
//定义SPI口号
#define SPI_0 0
#define SPI_1 1
#define SPI_2 2



//SPI对于的IRQ中断号
#define SPI0IRQ 26
#define SPI1IRQ 27
#define SPI2IRQ 28

#define SPI_SPEED_LOW   0
#define SPI_SPEED_HIGH  1

//                电路连接: SPI0与SPI1的引脚连接
//                SPI0 引脚   功能       连接       SPI1 引脚   功能
//                PTA14  PCS0   --------------      PTE4   PCS0
//                PTA15  SCK    --------------      PTE2   SCK
//                PTA16  SOUT   --------------      PTE3   SIN
//                PTA17  SIN    --------------      PTE1   SOUT
//=========================================================================
//函数名称：hw_spi_init
//函数参数：spiNo：SPI通道号。
//          Master:是否是主机。
//函数返回：无
//功能=====================================================================
//void hw_spi_init(uint8 spiNo,uint8 master);
void SPI_Configuration(void);
void SPI_SetSpeed(unsigned char SpeedSet);
//=========================================================================
//函数名称概要：SPI初始化。
//====：hw_spi_send
//函数参数：spiNo：SPI通道号。
//          data[]：需要发送的数据。
//          len：数据长度。
//函数返回：无
//功能概要：SPI发送数据。
//=========================================================================
//uint32 hw_spi_send(uint8 spiNo,uint8 data[],uint32 len);
uint32 SPI_ReadWriteByte(uint8 spiNo,unsigned char buffer);

//=========================================================================
//函数名称：hw_spi_re
//函数参数：spiNo：SPI通道号。
//          data[]：需要接收的数据。
//函数返回：0：成功 1：失败
//功能概要：SPI接收数据。
//=========================================================================
uint8 hw_spi_re(uint8 spiNo,uint8 data[]);

//=========================================================================
//函数名称：hw_spi_enable_re_int
//参数说明：spiNo: SPI号
//函数返回： 无
//功能概要：开SPI接收中断
//=========================================================================
void hw_spi_enable_re_int(uint8 spiNo);

//=========================================================================
//函数名称：hw_spi_disable_re_int
//参数说明：spiNo: SPI号
//函数返回： 无
//功能概要：关SPI接收中断
//=========================================================================
void hw_spi_disable_re_int(uint8 spiNo);

//void lqspiinit(void);
//void lqwrite(unsigned char cmd);


#endif //__SPI_H__
