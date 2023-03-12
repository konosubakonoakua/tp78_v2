/********************************** (C) COPYRIGHT *******************************
 * File Name          : OLED_UI_CFG.c
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/3/4
 * Description        : 存放OLED UI常量配置
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"

/* 菜单项 */
const oled_ui_menu_structure cfg_menu_1 = {
  .type = OLED_UI_TYPE_MENU,
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
  .type = OLED_UI_TYPE_MENU,
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
  .type = OLED_UI_TYPE_MENU,
  .text[0] = "MPRparam7",
  .p[0] = (uint8_t*)&mprparam7_en,
  .p[3] = (uint8_t*)&main_menu,
  .p[4] = (uint8_t*)&cfg_menu_2,
  .p[5] = (uint8_t*)&cfg_menu_1,
  .menu_size = 1,
};
const oled_ui_menu_structure mpr_status_menu_1 = {
  .type = OLED_UI_TYPE_MENU,
  .text[0] = "capmouseU",
  .text[1] = "capmouseD",
  .text[2] = "capmouseL",
  .p[0] = (uint8_t*)&mpr_status_mousecap_U,
  .p[1] = (uint8_t*)&mpr_status_mousecap_D,
  .p[2] = (uint8_t*)&mpr_status_mousecap_L,
  .p[3] = (uint8_t*)&main_menu,
  .p[4] = (uint8_t*)&mpr_status_menu_2,
  .p[5] = (uint8_t*)&mpr_status_menu_2,
  .menu_size = 3,
};
const oled_ui_menu_structure mpr_status_menu_2 = {
  .type = OLED_UI_TYPE_MENU,
  .text[0] = "capmouseR",
  .p[0] = (uint8_t*)&mpr_status_mousecap_R,
  .p[3] = (uint8_t*)&main_menu,
  .p[4] = (uint8_t*)&mpr_status_menu_1,
  .p[5] = (uint8_t*)&mpr_status_menu_1,
  .menu_size = 1,
};
const oled_ui_menu_structure main_menu = {
  .type = OLED_UI_TYPE_MENU,
  .text[0] = "MPRStatus",
  .text[1] = "KeyCfg",
  .p[0] = (uint8_t*)&mpr_status_menu_1,
  .p[1] = (uint8_t*)&cfg_menu_1,
  .menu_size = 2,
};

/* MPR121状态项 */
const oled_ui_mpr121_status_structure mpr_status_mousecap_U = {
  .type = OLED_UI_TYPE_MPR121_STATUS,
  .p = (uint8_t*)&mpr_status_menu_1,
  .reg = MPR121_REG_EFD1LB,   // 根据MPR121_Cap_Mouse_Pinmux修改
  .is_half_word = TRUE,
};
const oled_ui_mpr121_status_structure mpr_status_mousecap_D = {
  .type = OLED_UI_TYPE_MPR121_STATUS,
  .p = (uint8_t*)&mpr_status_menu_1,
  .reg = MPR121_REG_EFD2LB,   // 根据MPR121_Cap_Mouse_Pinmux修改
  .is_half_word = TRUE,
};
const oled_ui_mpr121_status_structure mpr_status_mousecap_L = {
  .type = OLED_UI_TYPE_MPR121_STATUS,
  .p = (uint8_t*)&mpr_status_menu_1,
  .reg = MPR121_REG_EFD3LB,   // 根据MPR121_Cap_Mouse_Pinmux修改
  .is_half_word = TRUE,
};
const oled_ui_mpr121_status_structure mpr_status_mousecap_R = {
  .type = OLED_UI_TYPE_MPR121_STATUS,
  .p = (uint8_t*)&mpr_status_menu_2,
  .reg = MPR121_REG_EFD0LB,   // 根据MPR121_Cap_Mouse_Pinmux修改
  .is_half_word = TRUE,
};

/* 输入项 */
const oled_ui_enter_num_structure bledevice_en = {
  .type = OLED_UI_TYPE_ENTER_NUM,
  .p = (uint8_t*)&cfg_menu_1,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_BLE_DEVICE,
  .limit_len = 1,
};
const oled_ui_enter_num_structure ledstyle_en = {
  .type = OLED_UI_TYPE_ENTER_NUM,
  .p = (uint8_t*)&cfg_menu_1,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_LED_STYLE,
  .limit_len = 1,
};
const oled_ui_enter_num_structure rfenable_en = {
  .type = OLED_UI_TYPE_ENTER_NUM,
  .p = (uint8_t*)&cfg_menu_1,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_RF_READY,
  .limit_len = 1,
};
const oled_ui_enter_num_structure udiskmode_en = {
  .type = OLED_UI_TYPE_ENTER_NUM,
  .p = (uint8_t*)&cfg_menu_2,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_UDISK_MODE,
  .limit_len = 1,
};
const oled_ui_enter_num_structure mprparam3_en = {
  .type = OLED_UI_TYPE_ENTER_NUM,
  .p = (uint8_t*)&cfg_menu_2,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_MPR_CAPMOUSE_MOV_SPD,
  .limit_len = 1,
};
const oled_ui_enter_num_structure mprparam6_en = {
  .type = OLED_UI_TYPE_ENTER_NUM,
  .p = (uint8_t*)&cfg_menu_2,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_MPR_DOUBLE_TOUCH_CNT,
  .limit_len = 5,
};
const oled_ui_enter_num_structure mprparam7_en = {
  .type = OLED_UI_TYPE_ENTER_NUM,
  .p = (uint8_t*)&cfg_menu_3,
  .preStr = "val:",
  .postStr = "OK",
  .pStr_len = 4,
  .line = FS_LINE_MPR_LONG_TOUCH_CNT,
  .limit_len = 5,
};
