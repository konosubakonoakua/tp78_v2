/********************************** (C) COPYRIGHT *******************************
 * File Name          : MODULE_DEMO.c
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/3/5
 * Description        : 扩展模块I2C通信驱动
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"

/*******************************************************************************
* Function Name  : MSG_MODULE_Init
* Description    : 初始化Module MSG
* Input          : debug_info - 错误信息
* Return         : 成功返回0，失败返回1
*******************************************************************************/
uint8_t MSG_MODULE_Init(char* debug_info)
{
  uint8_t dat, err;
  uint16_t cnt = 0;
#if !(defined HAL_HW_I2C) || (HAL_HW_I2C == FALSE)  // should config module after HW_I2C
  strcpy(debug_info, "MSG-ERR-01");
  return 1;
#endif
  g_Ready_Status.module = FALSE;
  tmos_start_task( halTaskID, MODULE_INITIAL_EVENT, MS1_TO_SYSTEM_TIME(100) );
  return 0;
}
