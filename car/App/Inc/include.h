#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include 用户自定义的头文件
 */
#include  "MK60_wdog.h"
#include  "MK60_gpio.h"     //IO口操作
#include  "MK60_uart.h"     //串口
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //低功耗定时器(延时)
#include  "MK60_i2c.h"      //I2C
#include  "MK60_spi.h"      //SPI
#include  "MK60_ftm.h"      //FTM
#include  "MK60_pit.h"      //PIT
#include  "MK60_rtc.h"      //RTC
#include  "MK60_adc.h"      //ADC
#include  "MK60_dac.h"      //DAC
#include  "MK60_dma.h"      //DMA
//#include  "MK60_FLASH.h"    //FLASH
#include  "MK60_can.h"      //CAN
#include  "MK60_sdhc.h"     //SDHC
#include  "MK60_usb.h"      //usb

#include  "VCAN_LED.H"          //LED
#include  "VCAN_KEY.H"          //KEY
#include  "VCAN_MMA7455.h"      //三轴加速度MMA7455
#include  "VCAN_NRF24L0.h"      //无线模块NRF24L01+
#include  "VCAN_RTC_count.h"    //RTC 时间转换
#include  "VCAN_camera.h"       //摄像头总头文件
#include  "VCAN_LCD.h"          //液晶总头文件
#include  "ff.h"                //FatFs
#include  "VCAN_TSL1401.h"      //线性CCD
#include  "VCAN_key_event.h"    //按键消息处理
#include  "VCAN_NRF24L0_MSG.h"  //无线模块消息处理

#include  "VCAN_BMP.h"          //BMP
#include  "vcan_img2sd.h"       //存储图像到sd卡一个文件
#include  "vcan_sd_app.h"       //SD卡应用（显示sd看上图片固件）
#include  "spi.h"    
#include  "sd_driver.h"            
#include  "diskio.h"

#include  "Vcan_touch.h"        //触摸驱动

#include  "VCAN_computer.h"     //多功能调试助手

#include "global_variable.h"       //全局变量
#include "allinit.h"               //所有初始化
#include "handle_img.h"            //图像处理
#include "get_center.h"            //中线提取
#include "duoji.h"                 //舵机控制
#include "dianji.h"                //电机控制
#include "LCD_show.h"              //LCD显示
#include "jiwan.h"                 //急弯控制
#include "Encoder.h"               //编码器
#include "zhidao.h"                //直道识别

#include "quick_stop.h"            //急停识别


#endif  //__INCLUDE_H__
