

#ifndef __ALLINIT_H__
#define __ALLINIT_H__

extern void DMA0_IRQHandler();
extern void PORTA_IRQHandler();
extern void allinit();
extern uint8 imgbuff[CAMERA_SIZE];
extern uint8 img[CAMERA_H][CAMERA_W];
extern Site_t site;    
extern Size_t imgsize;
extern Size_t size; 
extern int DMA_Over_Flag;
extern uint8 *imgdata;
extern FATFS fs;            // Work area (file system object) for logical drive
extern FRESULT res;         // FatFs function common result code
extern UINT br,bw;         // File Write count
extern FIL testdata;  
extern FILINFO* sfil;
extern FRESULT rc;

#endif  //__DUOJI_H__
