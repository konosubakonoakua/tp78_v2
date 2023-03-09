/********************************** (C) COPYRIGHT *******************************
 * File Name          : MODULE_DEMO.h
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/3/5
 * Description        : ��չģ��I2Cͨ������
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#ifndef __MSG_CP_H
  #define __MSG_CP_H

  #include "HAL.h"

  #define MODULE_WAKEUP_PIN         HW_I2C_SDA_PIN  // ���ѽ�ΪSDA
  #define MODULE_WAKEUP_GPIO(x)     GPIOB_ ## x

  /* ������չģ���޸� */
  #define MODULE_I2C_ADDR           0xB0
  #define MODULE_ID_REG             0x0
  #define MODULE_STATUS_REG         0x1

  #define MODULE_I2C_WR_Reg(reg, dat)               HW_I2C_WR_Reg(reg, dat, MODULE_I2C_ADDR)
  #define MODULE_I2C_RD_Reg(reg, p_dat)             HW_I2C_RD_Reg(reg, p_dat, MODULE_I2C_ADDR)
  #define MODULE_I2C_Muti_RD_Reg(reg, p_dat, len)   HW_I2C_Muti_RD_Reg(reg, p_dat, MODULE_I2C_ADDR, len)

  uint8_t MSG_MODULE_Init(char* debug_info);

#endif
