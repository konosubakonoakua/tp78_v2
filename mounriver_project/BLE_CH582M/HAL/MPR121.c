/********************************** (C) COPYRIGHT *******************************
 * File Name          : MPR121.c
 * Author             : ChnMasterOG
 * Version            : V1.0
 * Date               : 2023/1/2
 * Description        : mpr121电容传感器驱动
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"

/* pinmux */
const uint8_t MPR121_Cap_Mouse_Pinmux[4] = {1, 2, 3, 0};  // up-ELE1, down-ELE2, left-ELE3, right-ELE0
const uint8_t MPR121_TouchBar_Pinmux[7] = {10, 9, 8, 7, 6, 5, 4}; // L1, L2, L3, M, R1, R2, R3

/**************use py to generate***************
  import math
  for i in range(37):
    a = round(math.sin(math.pi * i / 4 / 36), 4)
    b = round(math.cos(math.pi * i / 4 / 36), 4)
    print("{%.4f, %.4f},  //%d" % (a, b, i))
************************************************/
/* cap_mouse movement angle arr */
const float MPR121_Cap_Mouse_Movement_arr[37][2] = { {0.0000, 1.0000},  //0
                                                     {0.0000, 1.0000},  //1 {0.0218, 0.9998},  //1
                                                     {0.0000, 1.0000},  //2 {0.0436, 0.9990},  //2
                                                     {0.0000, 1.0000},  //3 {0.0654, 0.9979},  //3
                                                     {0.0000, 1.0000},  //4 {0.0872, 0.9962},  //4
                                                     {0.1089, 0.9941},  //5
                                                     {0.1305, 0.9914},  //6
                                                     {0.1521, 0.9884},  //7
                                                     {0.1736, 0.9848},  //8
                                                     {0.1951, 0.9808},  //9
                                                     {0.2164, 0.9763},  //10
                                                     {0.2377, 0.9713},  //11
                                                     {0.2588, 0.9659},  //12
                                                     {0.2798, 0.9600},  //13
                                                     {0.3007, 0.9537},  //14
                                                     {0.3214, 0.9469},  //15
                                                     {0.3420, 0.9397},  //16
                                                     {0.3624, 0.9320},  //17
                                                     {0.3827, 0.9239},  //18
                                                     {0.4027, 0.9153},  //19
                                                     {0.4226, 0.9063},  //20
                                                     {0.4423, 0.8969},  //21
                                                     {0.4617, 0.8870},  //22
                                                     {0.4810, 0.8767},  //23
                                                     {0.5000, 0.8660},  //24
                                                     {0.5188, 0.8549},  //25
                                                     {0.5373, 0.8434},  //26
                                                     {0.5556, 0.8315},  //27
                                                     {0.5736, 0.8192},  //28
                                                     {0.5913, 0.8064},  //29
                                                     {0.6088, 0.7934},  //30
                                                     {0.6259, 0.7799},  //31
                                                     {0.6428, 0.7660},  //32
                                                     {0.6593, 0.7518},  //33
                                                     {0.6756, 0.7373},  //34
                                                     {0.6915, 0.7224},  //35
                                                     {0.7071, 0.7071},  //36
};

/* algorithom variables */
static alg_ListNode cap_mouse_data[4][ALG_BUF_LEN]; // 4 Corresponds to UP/DOWN/LEFT/RIGHT
static alg_ListNode mpr121_sts_data[ALG_BUF_LEN];
static uint16_t cap_mouse_base_data[4];
alg_ListNode* cap_mouse_dat_head[4];
alg_ListNode* mpr121_sts_head[1];
alg_Param mpr_algParameter;

BOOL cap_mouse_data_change = FALSE;
BOOL touchbar_data_change = FALSE;

Touchbar_Data_t TouchbarDat;

/*******************************************************************************
* Function Name  : MPR121_Config_Registers
* Description    : MPR121配置相关寄存器
* Input          : buf - 错误信息
* Return         : None
*******************************************************************************/
static void MPR121_Config_Registers(char* buf)
{
  uint8_t i, err;

  err = MPR121_WriteReg(MPR121_REG_SRST, 0x63);    // soft reset
  if (err) {
    strcpy(buf, "MPR121-ERR");
  }
  MPR121_WriteReg(MPR121_REG_ECR, 0x00);     // stop mode

  // filtering control, data is > baseline
  MPR121_WriteReg(MPR121_REG_MHDR, 0x01);
  MPR121_WriteReg(MPR121_REG_NHDR, 0x01);
  MPR121_WriteReg(MPR121_REG_NCLR, 0x00);
  MPR121_WriteReg(MPR121_REG_FDLR, 0x00);

  // filtering control, data is < baseline
  MPR121_WriteReg(MPR121_REG_MHDF, 0x01);
  MPR121_WriteReg(MPR121_REG_NHDF, 0x01);
  MPR121_WriteReg(MPR121_REG_NCLF, 0xFF);
  MPR121_WriteReg(MPR121_REG_FDLF, 0x00);

  // baseline filtering control register
  MPR121_WriteReg(MPR121_REG_NHDT, 0x00);    //noise half delta touched
  MPR121_WriteReg(MPR121_REG_NCLT, 0x00);    //noise counts touched
  MPR121_WriteReg(MPR121_REG_FDLT, 0x00);    //filter delay touched

  MPR121_WriteReg(MPR121_REG_MHDPROXR, 0x0F);
  MPR121_WriteReg(MPR121_REG_NHDPROXR, 0x0F);
  MPR121_WriteReg(MPR121_REG_NCLPROXR, 0x00);
  MPR121_WriteReg(MPR121_REG_FDLPROXR, 0x00);
  MPR121_WriteReg(MPR121_REG_MHDPROXF, 0x01);
  MPR121_WriteReg(MPR121_REG_NHDPROXF, 0x01);
  MPR121_WriteReg(MPR121_REG_NCLPROXF, 0xFF);
  MPR121_WriteReg(MPR121_REG_FDLPROXF, 0xFF);
  MPR121_WriteReg(MPR121_REG_NHDPROXT, 0x00);
  MPR121_WriteReg(MPR121_REG_NCLPROXT, 0x00);
  MPR121_WriteReg(MPR121_REG_FDLPROXT, 0x00);

  // set touch & release threshold for each ELE
  for (i = 0; i < 4; i++) {
    MPR121_WriteReg(MPR121_REG_E0TTH + MPR121_Cap_Mouse_Pinmux[i] * 2, mpr_algParameter.cap_mouse_tou_thr);
    MPR121_WriteReg(MPR121_REG_E0RTH + MPR121_Cap_Mouse_Pinmux[i] * 2, mpr_algParameter.cap_mouse_rel_thr);
  }
  for (i = 0; i < 7; i++) {
    MPR121_WriteReg(MPR121_REG_E0TTH + MPR121_TouchBar_Pinmux[i] * 2, mpr_algParameter.touchbar_tou_thr);
    MPR121_WriteReg(MPR121_REG_E0RTH + MPR121_TouchBar_Pinmux[i] * 2, mpr_algParameter.touchbar_rel_thr);
  }

  MPR121_WriteReg(MPR121_REG_EPROXTTH, 0x02);
  MPR121_WriteReg(MPR121_REG_EPROXRTH, 0x01);
  MPR121_WriteReg(MPR121_REG_DTR, 0x00);
  MPR121_WriteReg(MPR121_REG_FG_CDC, 0x10);
  MPR121_WriteReg(MPR121_REG_FG_CDT, 0x24);

  // enable auto config & auto reconfig
  MPR121_WriteReg(MPR121_REG_ACCR0, 0x0B);
  MPR121_WriteReg(MPR121_REG_ACUSL, 0xC8);
  MPR121_WriteReg(MPR121_REG_ACLSL, 0x82);
  MPR121_WriteReg(MPR121_REG_ACTLR, 0xB4);

  // ELE control
  MPR121_WriteReg(MPR121_REG_ECR, 0xBC); //enable all electrodes
}

/*******************************************************************************
* Function Name  : MPR121_ELE_to_Pin
* Description    : MPR121寄存器数据根据pinmux交换引脚顺序
* Input          : ele_data
* Return         : None
*******************************************************************************/
static uint16_t MPR121_ELE_to_Pin(uint16_t ele_data, const uint8_t* pinmux, uint8_t size)
{
  uint8_t i;
  uint16_t pin_data = 0;
  for (i = 0; i < size; i++) {
    pin_data |= ((ele_data >> pinmux[i]) & 1) << i;
  }
  return pin_data;
}

/*******************************************************************************
* Function Name  : MPR121_ALG_Init
* Description    : MPR121算法初始化
* Input          : None
* Return         : None
*******************************************************************************/
static void MPR121_ALG_Init(void)
{
  uint8_t i, j;
  /* Cap Mouse Data(cycle list) Init */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < ALG_BUF_LEN-1; j++) {
      cap_mouse_data[i][j].next = &cap_mouse_data[i][j+1];
      cap_mouse_data[i][j+1].prev = &cap_mouse_data[i][j];
    }
    cap_mouse_data[i][0].prev = &cap_mouse_data[i][ALG_BUF_LEN-1];
    cap_mouse_data[i][ALG_BUF_LEN-1].next = &cap_mouse_data[i][0];
    cap_mouse_dat_head[i] = &cap_mouse_data[i][0];
  }
  /* MPR121 Status(cycle list) Init */
  for (i = 0; i < ALG_BUF_LEN-1; i++) {
    mpr121_sts_data[i].next = &mpr121_sts_data[i+1];
    mpr121_sts_data[i+1].prev = &mpr121_sts_data[i];
  }
  mpr121_sts_data[0].prev = &mpr121_sts_data[ALG_BUF_LEN-1];
  mpr121_sts_data[ALG_BUF_LEN-1].next = &mpr121_sts_data[0];
  mpr121_sts_head[0] = &mpr121_sts_data[0];
}

/*******************************************************************************
* Function Name  : MPR121_BASE_Init
* Description    : MPR121基准数据初始化
* Input          : None
* Return         : None
*******************************************************************************/
static void MPR121_BASE_Init(void)
{
  uint8_t i;
  for (i = 0; i < 4; i++) { // repeat
    cap_mouse_base_data[i] = 750;
  }
}

/*******************************************************************************
* Function Name  : MPR121_Init
* Description    : 初始化MPR121
* Input          : buf - 错误信息
* Return         : None
*******************************************************************************/
void MPR121_Init(char* buf)
{
  /* config PB18 as TP_INT */
  MPRINT_GPIO_(SetBits)( MPRINT_Pin );
  MPRINT_GPIO_(ModeCfg)( MPRINT_Pin, GPIO_ModeIN_PU );

  /* MPR121 IRQ */
  /*
  MPRINT_GPIO_(ITModeCfg)( MPRINT_Pin, GPIO_ITMode_FallEdge );
  PFIC_EnableIRQ( GPIO_B_IRQn );  //MPRINT_GPIO
  */

  DATAFLASH_Read_MPR121_ALG_Parameter();
  MPR121_ALG_Init();
  MPR121_Config_Registers(buf);
  MPR121_BASE_Init();
}

/*******************************************************************************
* Function Name  : DATAFLASH_Read_MPR121_ALG_Parameter
* Description    : 从DataFlash读取MPR121算法参数
* Input          : None
* Return         : None
*******************************************************************************/
void DATAFLASH_Read_MPR121_ALG_Parameter(void)
{
  HAL_Fs_Read_keyboard_cfg(FS_LINE_MPR_ALG_MAGIC, 8, (uint16_t*)&mpr_algParameter);
  if (mpr_algParameter.magic != ALG_PARAM_MAGIC) {
    // use default parameter
    mpr_algParameter.magic = ALG_PARAM_MAGIC;
    mpr_algParameter.cap_mouse_tou_thr = CAP_MOUSE_TOU_THRESH;
    mpr_algParameter.cap_mouse_rel_thr = CAP_MOUSE_REL_THRESH;
    mpr_algParameter.cap_mouse_move_speed = CAP_MOUSE_MOVE_SPEED;
    mpr_algParameter.touchbar_tou_thr = TOUCHBAR_TOU_THRESH;
    mpr_algParameter.touchbar_rel_thr = TOUCHBAR_REL_THRESH;
    mpr_algParameter.double_touch_cnt = DOUBLE_TOUCH_CNT;
    mpr_algParameter.long_touch_cnt = LONG_TOUCH_CNT;
  }
}

/*******************************************************************************
* Function Name  : DATAFLASH_Write_MPR121_ALG_Parameter
* Description    : 将MPR121算法参数写入DataFlash
* Input          : None
* Return         : None
*******************************************************************************/
void DATAFLASH_Write_MPR121_ALG_Parameter(void)
{
  HAL_Fs_Write_keyboard_cfg(FS_LINE_MPR_ALG_MAGIC, 7, (uint16_t*)&mpr_algParameter);
}

/*******************************************************************************
* Function Name  : MPR121_ALG_Update_algListNode
* Description    : MPR121算法更新链表
* Input          : p - 链表指针; index - 数组下标; dat - 链表数据
* Return         : None
*******************************************************************************/
void MPR121_ALG_Update_algListNode(alg_ListNode* p[], uint8_t index, uint16_t dat)
{
  p[index] = p[index]->next;
  p[index]->dat = dat;
}

#if 0
/*******************************************************************************
* Function Name  : MPR121_ALG_Judge_Cap_Mouse
* Description    : MPR121算法判断触摸板
* Input          : None
* Return         : None
*******************************************************************************/
void MPR121_ALG_Judge_Cap_Mouse(void)
{
  Mouse_Data_t* const data = (Mouse_Data_t*)HIDMouse;
  signed char XMovement = 0;
  signed char YMovement = 0;
  signed char sign_state_x, sign_state_y;
  uint8_t temp;
  uint16_t now_dat = MPR121_ELE_to_Pin(mpr121_sts_head[0]->dat, MPR121_Cap_Mouse_Pinmux, 4);

  /* judge dir-up */
  if (now_dat & ALG_PINMUX_BIT(ALG_MOVE_UP_INDEX)) {
    YMovement--;
  }
  /* judge dir-down */
  if (now_dat & ALG_PINMUX_BIT(ALG_MOVE_DOWN_INDEX)) {
    YMovement++;
  }
  /* judge dir-left */
  if (now_dat & ALG_PINMUX_BIT(ALG_MOVE_LEFT_INDEX)) {
    XMovement--;
  }
  /* judge dir-right -> special */
  if (now_dat & ALG_PINMUX_BIT(ALG_MOVE_RIGHT_INDEX)) {
    XMovement++;
  }
  if (now_dat) {
    sign_state_x = __SIGN_STATE__(data->XMovement);
    sign_state_y = __SIGN_STATE__(data->YMovement);
    if (sign_state_x == __SIGN_STATE__(XMovement) && sign_state_y == __SIGN_STATE__(YMovement)) {
      data->XMovement = __ABS_LIMIT__(data->XMovement + 1 * sign_state_x, 15);
      data->YMovement = __ABS_LIMIT__(data->YMovement + 1 * sign_state_y, 15);
    } else {
      data->XMovement = (uint8_t)XMovement;
      data->YMovement = (uint8_t)YMovement;
    }
    cap_mouse_data_change = TRUE;
  } else {  // release
    data->XMovement = 0;
    data->YMovement = 0;
    cap_mouse_data_change = TRUE;
  }
}
#endif

/*******************************************************************************
* Function Name  : MPR121_ALG_Judge_Cap_Mouse
* Description    : MPR121算法判断触摸板
* Input          : None
* Return         : None
*******************************************************************************/
void MPR121_ALG_Judge_Cap_Mouse(void)
{
  Mouse_Data_t* const data = (Mouse_Data_t*)HIDMouse;
  uint32_t angle;
  uint16_t min_data = 0xFFFF, min_data2 = 0xFFFF;
  uint16_t now_dat = MPR121_ELE_to_Pin(mpr121_sts_head[0]->dat, MPR121_Cap_Mouse_Pinmux, 4);
  signed char XMovement = 0;
  signed char YMovement = 0;
  uint8_t i, min_idx = 0, min_idx2 = 0;

  if ((now_dat & 0xF) == 0) {
    if (data->XMovement != 0) {
      data->XMovement = 0;
      cap_mouse_data_change = TRUE;
    }
    if (data->YMovement != 0) {
      data->YMovement = 0;
      cap_mouse_data_change = TRUE;
    }
    return;
  }

  for (i = 0; i < 4; i++) {
    if (cap_mouse_data[i]->dat < min_data) {
      min_data2 = min_data;
      min_data = cap_mouse_data[i]->dat;
      min_idx2 = min_idx;
      min_idx = i;
    } else if (cap_mouse_data[i]->dat < min_data2) {
      min_data2 = cap_mouse_data[i]->dat;
      min_idx2 = i;
    }
  }

  angle = 72 * (cap_mouse_base_data[min_idx2] - min_data2) / (cap_mouse_base_data[min_idx2] - min_data2 + cap_mouse_base_data[min_idx] - min_data);  // 0~36

  switch (min_idx) {
    case 0:   // up
      data->YMovement = -mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][1];
      if (min_idx2 == 2) data->XMovement = -mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][0];
      else if (min_idx2 == 3) data->XMovement = mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][0];
      else data->XMovement = 0;
      break;
    case 1:   // down
      data->YMovement = mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][1];
      if (min_idx2 == 2) data->XMovement = -mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][0];
      else if (min_idx2 == 3) data->XMovement = mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][0];
      else data->XMovement = 0;
      break;
    case 2:   // left
      data->XMovement = -mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][1];
      if (min_idx2 == 0) data->YMovement = -mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][0];
      else if (min_idx2 == 1) data->YMovement = mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][0];
      else data->YMovement = 0;
      break;
    case 3:   // right
      data->XMovement = mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][1];
      if (min_idx2 == 0) data->YMovement = -mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][0];
      else if (min_idx2 == 1) data->YMovement = mpr_algParameter.cap_mouse_move_speed * MPR121_Cap_Mouse_Movement_arr[angle][0];
      else data->YMovement = 0;
      break;
  }

  cap_mouse_data_change = TRUE;

}

/*******************************************************************************
* Function Name  : MPR121_ALG_Judge_Touchbar
* Description    : MPR121算法判断触摸条
* Input          : None
* Return         : None
*******************************************************************************/
void MPR121_ALG_Judge_Touchbar(void)
{
  /* read touch status version */
  static alg_TouchbarDirectiion dir = DIRECT_OTHER;
  Mouse_Data_t* const m_data = (Mouse_Data_t*)HIDMouse;
  uint8_t record;
  uint16_t now_dat = MPR121_ELE_to_Pin(mpr121_sts_head[0]->dat, MPR121_TouchBar_Pinmux, 7);
  uint16_t pre_dat = MPR121_ELE_to_Pin(mpr121_sts_head[0]->prev->dat, MPR121_TouchBar_Pinmux, 7);

  record = m_data->data[0] & 0x7;

  /* judge swipe */
  if (now_dat > pre_dat) { // swip to right
    if (dir & 1) dir = DIRECT_RIGHT;
    else {
      dir += 2;
      if (dir == DIRECT_JUDGE_RIGHT) {  // judge to swipe right
        dir = DIRECT_OTHER;
        TouchbarDat.swip_right = TRUE;
        OLED_UI_add_SHOWINFO_task("R Swipe");
        OLED_UI_add_CANCELINFO_delay_task(2000);
        goto touchbar_judge_end;
      }
    }
  } else if (now_dat < pre_dat) { // swip to left
    if (!(dir & 1)) dir = DIRECT_LEFT;
    else {
      dir += 2;
      if (dir == DIRECT_JUDGE_LEFT) { // judge to swipe left
        dir = DIRECT_OTHER;
        TouchbarDat.swip_left = TRUE;
        OLED_UI_add_SHOWINFO_task("L Swipe");
        OLED_UI_add_CANCELINFO_delay_task(2000);
        goto touchbar_judge_end;
      }
    }
  }
  /* judge left touch */
  if (__BOOL__(now_dat & 0x3) != __BOOL__(pre_dat & 0x3)) { // LBtn0 => LBtn1 or LBtn1 => LBtn0
    if (__iBOOL__(now_dat & 0x3)) { // LBtn1 => LBtn0
      if (mpr_algParameter.l_cnt_dat >= FILTER_CNT) {
        mpr_algParameter.dbtn_dat = pre_dat; // next touch is double touch
      }
      m_data->LeftBtn = 0;  // release mouse left btn
    }
    mpr_algParameter.l_cnt_dat = 0;
  } else {  // LBtn1 => LBtn1 or LBtn0 => LBtn0
    mpr_algParameter.l_cnt_dat = __LIMIT__(mpr_algParameter.l_cnt_dat+1, 65534);
    if (__iBOOL__(now_dat & 0x3)) { // LBtn0 => LBtn0
      if (mpr_algParameter.l_cnt_dat >= mpr_algParameter.double_touch_cnt) {
        mpr_algParameter.dbtn_dat = 0;
      }
    } else {  // LBtn1 => LBtn1
      if (mpr_algParameter.dbtn_dat != 0) {
        mpr_algParameter.dbtn_dat = 0;
        m_data->LeftBtn = 1;  // press mouse left btn
        OLED_UI_add_SHOWINFO_task("L Btn");
        OLED_UI_add_CANCELINFO_delay_task(2000);
        MOTOR_GO();
        goto touchbar_judge_end;
      }
    }
  }
  /* judge right touch */
  if (__BOOL__(now_dat & 0x60) != __BOOL__(pre_dat & 0x60)) { // RBtn0 => RBtn1 or RBtn1 => RBtn0
      if (__iBOOL__(now_dat & 0x60)) { // RBtn1 => RBtn0
        m_data->RightBtn = 0;  // release mouse right btn
      }
      mpr_algParameter.r_cnt_dat = 0;
  } else if (__BOOL__(now_dat & 0x60)) {  // RBtn1 => RBtn1
    mpr_algParameter.r_cnt_dat = __LIMIT__(mpr_algParameter.r_cnt_dat+1, 65534);
    if (mpr_algParameter.r_cnt_dat == mpr_algParameter.long_touch_cnt) {
      m_data->RightBtn = 1; // press mouse right btn
      OLED_UI_add_SHOWINFO_task("R Btn");
      OLED_UI_add_CANCELINFO_delay_task(2000);
      MOTOR_GO();
      goto touchbar_judge_end;
    }
  }

  touchbar_judge_end:
  if ((m_data->data[0] & 0x7) != record) {
    touchbar_data_change = TRUE;
  }
}
