/********************************** (C) COPYRIGHT *******************************
 * File Name          : CORE.c
 * Author             : ChnMasterOG
 * Version            : V1.1
 * Date               : 2022/12/24
 * Description        : 上下电、MCU Sleep相关控制
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"

/*******************************************************************************
* Function Name  : APPJumpBoot
* Description    : 跳转到bootloader
* Input          : 无
* Return         : 无
*******************************************************************************/
__HIGH_CODE
void APPJumpBoot(void)   //此段代码必须运行在RAM中
{
  while(FLASH_ROM_ERASE(0, EEPROM_BLOCK_SIZE))
  {
    ;//ROM 擦4K1个单位，擦0地址起始
  }
  FLASH_ROM_SW_RESET();
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;  //安全访问模式
  SAFEOPERATE;
  R16_INT32K_TUNE = 0xFFFF;
  R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
  R8_SAFE_ACCESS_SIG = 0;//进入后执行复位，复位类型为上电复位
  while(1);//营造空片的现象，启动时就会停在BOOT，等烧写，超时时间10s
}

/*******************************************************************************
* Function Name  : SoftReset
* Description    : 软件复位
* Input          : 无
* Return         : 无
*******************************************************************************/
__HIGH_CODE
void SoftReset(void)   //软件复位
{
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;  //安全访问模式
  SAFEOPERATE;
  R16_INT32K_TUNE = 0xFFFF;
  R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
  R8_SAFE_ACCESS_SIG = 0;
  while(1);
}

/*******************************************************************************
* Function Name  : TP78Reinit
* Description    : TP78键盘睡眠唤醒
* Input          : mode - 0为进入sleep流程; 1为进入wakeup流程
*                  lp_type - 低功耗模式
* Return         : 无
*******************************************************************************/
__HIGH_CODE
void TP78Reinit(uint8_t mode, enum LP_Type lp_type)
{
  if (mode == 0) {  // 进入睡眠
#if (defined HAL_WDG) && (HAL_WDG == TRUE)
    WWDG_ResetCfg(DISABLE); // 关看门狗
#endif
    Row_GPIO_(SetBits)(Row_Pin_ALL);  // 唤醒条件
#if (defined HAL_OLED) && (HAL_OLED == TRUE)
    OLED_WR_Byte(0xAE, OLED_CMD);  // OLED display off
#endif
#ifdef HAL_WS2812_PWM
    led_style_func = WS2812_Style_Custom; WS2812_Send(); // WS2812
#endif
#if (defined HAL_HW_I2C) && (HAL_HW_I2C == TRUE)
#if (defined HAL_I2C_TP) && (HAL_I2C_TP == TRUE)
    I2C_TP_SendCommand_Sleep();   // 小红点sleep
#endif
#if ((defined HAL_MPR121_CAPMOUSE) && (HAL_MPR121_CAPMOUSE == TRUE)) || ((defined HAL_MPR121_TOUCHBAR) && (HAL_MPR121_TOUCHBAR == TRUE))  // MPR121需要上电延迟
    MPR121_WriteReg(MPR121_REG_FG_CDT, 0x7);
#endif
#ifdef HAL_BATTADC
    BAT_ADC_DIS();  // ADC
#endif
#endif
  } else {  // 唤醒键盘
    if (lp_type == idle_mode) { // 恢复现场
#if (defined HAL_WS2812_PWM)
      DATAFLASH_Read_LEDStyle();  // WS2812
#endif
#if (defined HAL_HW_I2C) && (HAL_HW_I2C == TRUE)
#if (defined HAL_I2C_TP) && (HAL_I2C_TP == TRUE)
      I2C_TP_SendCommand_Wakeup();   // 小红点wake up
#endif
#endif
#if (defined HAL_OLED) && (HAL_OLED == TRUE)
      OLED_WR_Byte(0xAF, OLED_CMD);  // OLED display on
#endif
#if ((defined HAL_MPR121_CAPMOUSE) && (HAL_MPR121_CAPMOUSE == TRUE)) || ((defined HAL_MPR121_TOUCHBAR) && (HAL_MPR121_TOUCHBAR == TRUE))  // MPR121需要上电延迟
    MPR121_WriteReg(MPR121_REG_FG_CDT, 0x24);
#endif
#if (defined HAL_WDG) && (HAL_WDG == TRUE)
      WWDG_ResetCfg(ENABLE);  // 开看门狗
#endif
    } else SoftReset();
  }
}

/*******************************************************************************
* Function Name  : GotoLowpower
* Description    : MCU进Low Power模式
* Input          : type: 低功耗模式类型
* Return         : 无
*******************************************************************************/
__HIGH_CODE
void GotoLowpower(enum LP_Type type)
{
#if (defined HAL_KEYBOARD) && (HAL_KEYBOARD == TRUE)
  if (type > 3) return; // error type
#if (defined MODULE_DEMO) && (MODULE_DEMO == TRUE)
  MODULE_I2C_WR_Reg(reg, dat, addr);  // 控制扩展模块进低功耗模式
#endif
  Colum_GPIO_(ModeCfg)( Colum_Pin_ALL, GPIO_ModeIN_PD );
  Colum_GPIO_(ITModeCfg)( Colum_Pin_ALL, GPIO_ITMode_RiseEdge ); // 上升沿唤醒
  PFIC_EnableIRQ(GPIO_A_IRQn);  // colum GPIO is GPIOA
  PWR_PeriphWakeUpCfg(ENABLE, RB_SLP_GPIO_WAKE, Short_Delay);
  switch (type)
  {
    case idle_mode: // 空闲模式 - 1.6mA
      TP78Reinit(0, type);
      LowPower_Idle();
      break;
    case halt_mode: // 暂停模式 - 320uA
      TP78Reinit(0, type);
      LowPower_Halt();
      break;
    case sleep_mode:  // 睡眠模式 - 0.7uA~2.8uA
      TP78Reinit(0, type);
      LowPower_Sleep(RB_PWR_RAM30K | RB_PWR_RAM2K | RB_PWR_EXTEND | RB_PWR_XROM);
      break;
    case shutdown_mode: // 下电模式 - 0.2uA~2.3uA
      TP78Reinit(0, type);
      LowPower_Shutdown(0);
      break;
    default:  // do not run here
      return;
  }
#else
  return;
#endif
}
