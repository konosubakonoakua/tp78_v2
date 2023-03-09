/********************************** (C) COPYRIGHT *******************************
 * File Name          : OLED_UI_CFG.c
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/3/4
 * Description        : 存放OLED UI常量配置
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "OLED_UI.h"
#include "FATFS.h"

/* 菜单项 */
const oled_ui_menu_structure cfg_menu_1 = {
  .text[0] = "BLEdevice",
  .text[1] = "LEDstyle",
  .text[2] = "RFenable",
  .p[0] = (uint8_t*)&bledevice_en,
  .p[1] = (uint8_t*)&ledstyle_en,
  .p[2] = (uint8_t*)&rfenable_en,
  .p[3] = (uint8_t*)&main_menu,
  .p[4] = (uint8_t*)&cfg_menu_3,
  .p[5] = (uint8_t*)&cfg_menu_2,
  .menu_size = 3,
};
const oled_ui_menu_structure cfg_menu_2 = {
  .text[0] = "UDISKmode",
  .text[1] = "MPRspeed",
  .text[2] = "MPRparam6",
  .p[0] = (uint8_t*)&udiskmode_en,
  .p[1] = (uint8_t*)&mprparam3_en,
  .p[2] = (uint8_t*)&mprparam6_en,
  .p[3] = (uint8_t*)&main_menu,
  .p[4] = (uint8_t*)&cfg_menu_1,
  .p[5] = (uint8_t*)&cfg_menu_3,
  .menu_size = 3,
};
const oled_ui_menu_structure cfg_menu_3 = {
  .text[0] = "MPRparam7",
  .p[0] = (uint8_t*)&mprparam7_en,
  .p[3] = (uint8_t*)&main_menu,
  .p[4] = (uint8_t*)&cfg_menu_2,
  .p[5] = (uint8_t*)&cfg_menu_1,
  .menu_size = 1,
};
const oled_ui_menu_structure main_menu = {
  .text[0] = "KeyStatus",
  .text[1] = "KeyCfg",
  .p[1] = (uint8_t*)&cfg_menu_1,
  .menu_size = 2,
};

/* 输入项 */
const oled_ui_enter_num_structure bledevice_en = {
  .p = (uint8_t*)&cfg_menu_1,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_BLE_DEVICE,
  .limit_len = 1,
};
const oled_ui_enter_num_structure ledstyle_en = {
  .p = (uint8_t*)&cfg_menu_1,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_LED_STYLE,
  .limit_len = 1,
};
const oled_ui_enter_num_structure rfenable_en = {
  .p = (uint8_t*)&cfg_menu_1,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_RF_READY,
  .limit_len = 1,
};
const oled_ui_enter_num_structure udiskmode_en = {
  .p = (uint8_t*)&cfg_menu_2,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_UDISK_MODE,
  .limit_len = 1,
};
const oled_ui_enter_num_structure mprparam3_en = {
  .p = (uint8_t*)&cfg_menu_2,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_MPR_CAPMOUSE_MOV_SPD,
  .limit_len = 1,
};
const oled_ui_enter_num_structure mprparam6_en = {
  .p = (uint8_t*)&cfg_menu_2,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_MPR_DOUBLE_TOUCH_CNT,
  .limit_len = 5,
};
const oled_ui_enter_num_structure mprparam7_en = {
  .p = (uint8_t*)&cfg_menu_3,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_MPR_LONG_TOUCH_CNT,
  .limit_len = 5,
};
