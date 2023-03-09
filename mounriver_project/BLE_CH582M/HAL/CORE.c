/********************************** (C) COPYRIGHT *******************************
 * File Name          : CORE.c
 * Author             : ChnMasterOG
 * Version            : V1.1
 * Date               : 2022/12/24
 * Description        : ���µ硢MCU Sleep��ؿ���
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"

/*******************************************************************************
* Function Name  : APPJumpBoot
* Description    : ��ת��bootloader
* Input          : ��
* Return         : ��
*******************************************************************************/
__HIGH_CODE
void APPJumpBoot(void)   //�˶δ������������RAM��
{
  while(FLASH_ROM_ERASE(0, EEPROM_BLOCK_SIZE))
  {
    ;//ROM ��4K1����λ����0��ַ��ʼ
  }
  FLASH_ROM_SW_RESET();
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;  //��ȫ����ģʽ
  SAFEOPERATE;
  R16_INT32K_TUNE = 0xFFFF;
  R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
  R8_SAFE_ACCESS_SIG = 0;//�����ִ�и�λ����λ����Ϊ�ϵ縴λ
  while(1);//Ӫ���Ƭ����������ʱ�ͻ�ͣ��BOOT������д����ʱʱ��10s
}

/*******************************************************************************
* Function Name  : SoftReset
* Description    : �����λ
* Input          : ��
* Return         : ��
*******************************************************************************/
__HIGH_CODE
void SoftReset(void)   //�����λ
{
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;  //��ȫ����ģʽ
  SAFEOPERATE;
  R16_INT32K_TUNE = 0xFFFF;
  R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
  R8_SAFE_ACCESS_SIG = 0;
  while(1);
}

/*******************************************************************************
* Function Name  : TP78Reinit
* Description    : TP78����˯�߻���
* Input          : mode - 0Ϊ����sleep����; 1Ϊ����wakeup����
*                  lp_type - �͹���ģʽ
* Return         : ��
*******************************************************************************/
__HIGH_CODE
void TP78Reinit(uint8_t mode, enum LP_Type lp_type)
{
  if (mode == 0) {  // ����˯��
    WWDG_ResetCfg(DISABLE); // �ؿ��Ź�
    Row_GPIO_(SetBits)(Row_Pin_ALL);  // ��������
#if (defined HAL_OLED) && (HAL_OLED == TRUE)
    OLED_WR_Byte(0xAE, OLED_CMD);  // OLED display off
#endif
#ifdef HAL_WS2812_PWM
    led_style_func = WS2812_Style_Custom; WS2812_Send(); // WS2812
#endif
#if (defined HAL_HW_I2C) && (HAL_HW_I2C == TRUE)
#if (defined HAL_I2C_TP) && (HAL_I2C_TP == TRUE)
    I2C_TP_SendCommand_Sleep();   // С���sleep
#endif
#if ((defined HAL_MPR121_CAPMOUSE) && (HAL_MPR121_CAPMOUSE == TRUE)) || ((defined HAL_MPR121_TOUCHBAR) && (HAL_MPR121_TOUCHBAR == TRUE))  // MPR121��Ҫ�ϵ��ӳ�
    MPR121_WriteReg(MPR121_REG_FG_CDT, 0x7);
#endif
#ifdef HAL_BATTADC
    BAT_ADC_DIS();  // ADC
#endif
#endif
  } else {  // ���Ѽ���
    if (lp_type == idle_mode) { // �ָ��ֳ�
#if (defined HAL_WS2812_PWM)
      DATAFLASH_Read_LEDStyle();  // WS2812
#endif
#if (defined HAL_HW_I2C) && (HAL_HW_I2C == TRUE)
#if (defined HAL_I2C_TP) && (HAL_I2C_TP == TRUE)
      I2C_TP_SendCommand_Wakeup();   // С���wake up
#endif
#endif
#if (defined HAL_OLED) && (HAL_OLED == TRUE)
      OLED_WR_Byte(0xAF, OLED_CMD);  // OLED display on
#endif
#if ((defined HAL_MPR121_CAPMOUSE) && (HAL_MPR121_CAPMOUSE == TRUE)) || ((defined HAL_MPR121_TOUCHBAR) && (HAL_MPR121_TOUCHBAR == TRUE))  // MPR121��Ҫ�ϵ��ӳ�
    MPR121_WriteReg(MPR121_REG_FG_CDT, 0x24);
#endif
      WWDG_ResetCfg(ENABLE);  // �����Ź�
    } else SoftReset();
  }
}

/*******************************************************************************
* Function Name  : GotoLowpower
* Description    : MCU��Low Powerģʽ
* Input          : type: �͹���ģʽ����
* Return         : ��
*******************************************************************************/
__HIGH_CODE
void GotoLowpower(enum LP_Type type)
{
#if (defined HAL_KEYBOARD) && (HAL_KEYBOARD == TRUE)
  if (type > 3) return; // error type
#if (defined MODULE_DEMO) && (MODULE_DEMO == TRUE)
  MODULE_I2C_WR_Reg(reg, dat, addr);  // ������չģ����͹���ģʽ
#endif
  Colum_GPIO_(ModeCfg)( Colum_Pin_ALL, GPIO_ModeIN_PD );
  Colum_GPIO_(ITModeCfg)( Colum_Pin_ALL, GPIO_ITMode_RiseEdge ); // �����ػ���
  PFIC_EnableIRQ(GPIO_A_IRQn);  // colum GPIO is GPIOA
  PWR_PeriphWakeUpCfg(ENABLE, RB_SLP_GPIO_WAKE, Short_Delay);
  switch (type)
  {
    case idle_mode: // ����ģʽ - 1.6mA
      TP78Reinit(0, type);
      LowPower_Idle();
      break;
    case halt_mode: // ��ͣģʽ - 320uA
      TP78Reinit(0, type);
      LowPower_Halt();
      break;
    case sleep_mode:  // ˯��ģʽ - 0.7uA~2.8uA
      TP78Reinit(0, type);
      LowPower_Sleep(RB_PWR_RAM30K | RB_PWR_RAM2K | RB_PWR_EXTEND | RB_PWR_XROM);
      break;
    case shutdown_mode: // �µ�ģʽ - 0.2uA~2.3uA
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
