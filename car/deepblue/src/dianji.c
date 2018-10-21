#include "common.h"
#include "include.h"
#include "dianji.h"

int settingspeed=200;          //输入速度
uint32 vsyncount;

void dianji()
{
  /*
  vsyncount++;
  if(vsyncount <500)
    settingspeed = 100;
  if(vsyncount >500)
  {
    settingspeed = 200;
  }
  if(vsyncount == 1000)
    vsyncount = 0;
  */
/*************************终点*****************************/
  if(stop_flag && !zdnum)
    settingspeed=0;


/************************直道速度************************/ 
  else if(zhidaoflag)
  {
     switch(deepblue)
    {
      case 1: settingspeed=250;break;
      case 2: settingspeed=250;break;
      case 3: settingspeed=270;break;
      case 4: settingspeed=250;break;
      case 5: settingspeed=250;break;
      case 6: settingspeed=270;break;
      case 7: settingspeed=250;break;
      case 8: settingspeed=250;break;
      case 9: settingspeed=270;break;
      case 10: settingspeed=250;break;
      case 11: settingspeed=250;break;//////
      case 12: settingspeed=270;break;
      case 13: settingspeed=270;break; 
    }
  
  
  
  }
  /***********************其他速度************************/
  else
  {
     switch(deepblue)
    {
      case 1: settingspeed=200;break;
      case 2: settingspeed=270;break;
      case 3: settingspeed=200;break;
      case 4: settingspeed=210;break;
      case 5: settingspeed=210;break;
      case 6: settingspeed=210;break;
      case 7: settingspeed=220;break;
      case 8: settingspeed=220;break;
      case 9: settingspeed=220;break;
      case 10: settingspeed=230;break;
      case 11: settingspeed=230;break;
      case 12: settingspeed=230;break;
      case 13: settingspeed=240; break;
    }
  
  
  
  }

}

