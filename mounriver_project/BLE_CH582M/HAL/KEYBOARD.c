/********************************** (C) COPYRIGHT *******************************
 * File Name          : KEYBOARD.c
 * Author             : ChnMasterOG
 * Version            : V2.0
 * Date               : 2022/12/1
 * Description        : ��е��������Դ�ļ�
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"
#include "snake.h"

const uint32_t Row_Pin[ROW_SIZE] = {GPIO_Pin_6, GPIO_Pin_5, GPIO_Pin_3, GPIO_Pin_2, GPIO_Pin_1, GPIO_Pin_0};   //row 6 - �������̲������޸Ĵ˴�
const uint32_t Colum_Pin[COL_SIZE] = {GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3,
                                      GPIO_Pin_15, GPIO_Pin_14, GPIO_Pin_13, GPIO_Pin_12, GPIO_Pin_11, GPIO_Pin_9, GPIO_Pin_7};   //colum 14 - �������̲������޸Ĵ˴�
//row*colum = 6*14 = 84
const uint8_t KeyArrary[COL_SIZE][ROW_SIZE] = {
        { KEY_ESCAPE,   KEY_GraveAccent,    KEY_TAB,        KEY_CapsLock,   KEY_LeftShift,  KEY_LeftCTRL  }, //1
        { KEY_F1,       KEY_1,              KEY_Q,          KEY_A,          KEY_None,       KEY_LeftGUI   }, //2
        { KEY_F2,       KEY_2,              KEY_W,          KEY_S,          KEY_Z,          KEY_LeftAlt   }, //3
        { KEY_F3,       KEY_3,              KEY_E,          KEY_D,          KEY_X,          KEY_SPACEBAR  }, //4
        { KEY_F4,       KEY_4,              KEY_R,          KEY_F,          KEY_C,          KEY_SPACEBAR  }, //5
        { KEY_F5,       KEY_5,              KEY_T,          KEY_G,          KEY_V,          KEY_RightAlt  }, //6
        { KEY_F6,       KEY_6,              KEY_Y,          KEY_H,          KEY_B,          KEY_Fn        }, //7
        { KEY_F7,       KEY_7,              KEY_U,          KEY_J,          KEY_N,          KEY_RightCTRL }, //8
        { KEY_F8,       KEY_8,              KEY_I,          KEY_K,          KEY_M,          KEY_LeftArrow }, //9
        { KEY_F9,       KEY_9,              KEY_O,          KEY_L,          KEY_Comma,      KEY_DownArrow }, //10
        { KEY_F10,      KEY_0,              KEY_P,          KEY_Semicolon,  KEY_FullStop,   KEY_RightArrow}, //11
        { KEY_F11,      KEY_Subtraction,    KEY_LSbrackets, KEY_Quotation,  KEY_Slash,      KEY_UpArrow   }, //12
        { KEY_F12,      KEY_Equal,          KEY_RSbrackets, KEY_ENTER,      KEY_RightShift, KEY_End       }, //13
        { KEY_Delete,   KEY_BACKSPACE,      KEY_NonUS_WS,   KEY_PageUp,     KEY_PageDown,   KEY_Home      }, //14
};  // Ĭ�ϼ��̲��� - �������̲������޸Ĵ˴�
const uint8_t Extra_KeyArrary[COL_SIZE][ROW_SIZE] = {
        { KEY_None,     KEY_None,           KEY_None,       KEY_None,       KEY_None,       KEY_None }, //1
        { KEY_None,     KEY_None,           KEY_BACKSPACE,  KEY_LeftArrow,  KEY_None,       KEY_None }, //2
        { KEY_None,     KEY_None,           KEY_UpArrow,    KEY_DownArrow,  KEY_None,       KEY_None }, //3
        { KEY_None,     KEY_None,           KEY_ENTER,      KEY_RightArrow, KEY_None,       KEY_None }, //4
        { KEY_None,     KEY_None,           KEY_PageUp,     KEY_PageDown,   KEY_Home,       KEY_None }, //5
        { KEY_None,     KEY_None,           KEY_None,       KEY_None,       KEY_End,        KEY_None }, //6
        { KEY_None,     KEY_None,           KEY_None,       KEY_None,       KEY_None,       KEY_None }, //7
        { KEY_None,     KEY_None,           KEY_None,       KEY_None,       KEY_None,       KEY_None }, //8
        { KEY_None,     KEY_None,           KEY_None,       KEY_None,       KEY_None,       KEY_None }, //9
        { KEY_None,     KEY_None,           KEY_None,       KEY_None,       KEY_None,       KEY_None }, //10
        { KEY_None,     KEY_None,           KEY_PrintScreen,KEY_None,       KEY_None,       KEY_None }, //11
        { KEY_None,     KEY_None,           KEY_None,       KEY_None,       KEY_None,       KEY_None }, //12
        { KEY_None,     KEY_None,           KEY_None,       KEY_None,       KEY_None,       KEY_None }, //13
        { KEY_None,     KEY_None,           KEY_None,       KEY_None,       KEY_None,       KEY_None }, //14
};  // ����Ĭ�ϼ��̲��� - �������̲������޸Ĵ˴�
const uint8_t SP_KeyArrary[][8] = {
        { 0x5,      0x0,      KEY_Delete,       0x0,      0x0,      0x0,      0x0,      0x0 }, //1 - Ctrl+Alt+Del
        { 0x3,      0x0,      KEY_Delete,       0x0,      0x0,      0x0,      0x0,      0x0 }, //2 - Ctrl+Shift+Del
        { 0x0,      0x0,      0x0,              0x0,      0x0,      0x0,      0x0,      0x0 }, //3
        { 0x0,      0x0,      0x0,              0x0,      0x0,      0x0,      0x0,      0x0 }, //4
        { 0x0,      0x0,      0x0,              0x0,      0x0,      0x0,      0x0,      0x0 }, //5
        { 0x9,      0x0,      KEY_LeftArrow,    0x0,      0x0,      0x0,      0x0,      0x0 }, //6 - GUI+Ctrl+Left
        { 0x9,      0x0,      KEY_RightArrow,   0x0,      0x0,      0x0,      0x0,      0x0 }, //7 - GUI+Ctrl+Right
};  // SP����Ĭ��ӳ��
const uint8_t Key_To_LEDNumber[COL_SIZE][ROW_SIZE] = {
        { 0,    14,   28,   42,   56,   69 }, //1
        { 1,    15,   29,   43,   0xFF, 70 }, //2
        { 2,    16,   30,   44,   57,   71 }, //3
        { 3,    17,   31,   45,   58,   72 }, //4
        { 4,    18,   32,   46,   59,   73 }, //5
        { 5,    19,   33,   47,   60,   74 }, //6
        { 6,    20,   34,   48,   61,   75 }, //7
        { 7,    21,   35,   49,   62,   76 }, //8
        { 8,    22,   36,   50,   63,   77 }, //9
        { 9,    23,   37,   51,   64,   78 }, //10
        { 10,   24,   38,   52,   65,   79 }, //11
        { 11,   25,   39,   53,   66,   80 }, //12
        { 12,   26,   40,   54,   67,   81 }, //13
        { 13,   27,   41,   55,   68,   82 }, //14
};  // �������λ��תLED���
uint32_t Row_Pin_ALL = 0, Colum_Pin_ALL = 0;
uint8_t CustomKey[COL_SIZE][ROW_SIZE];  //�Զ��尴����
uint8_t Extra_CustomKey[COL_SIZE][ROW_SIZE];   //�Զ�����ⰴ����
uint8_t KeyMatrix[COL_SIZE][ROW_SIZE] = { 0 };  //��������-��ǰ��º�δ����
uint8_t Extra_KeyMatrix[COL_SIZE][ROW_SIZE] = { 0 };  //����㰴������-��ǰ��º�δ����
uint8_t SP_Key_Map[SP_KEY_NUMBER][8] = { 0 }; //���ϰ���
uint8_t KEYBOARD_data_index = 2;
Keyboard_Status_t g_keyboard_status;

static uint8_t (*KeyArr_Ptr)[ROW_SIZE] = CustomKey;
static uint16_t KeyArr_ChangeTimes = 0;

/*******************************************************************************
* Function Name  : DATAFLASH_Read_KeyArray
* Description    : ��DataFlash��ȡ��������
* Input          : None
* Return         : None
*******************************************************************************/
void DATAFLASH_Read_KeyArray( void )
{
  HAL_Fs_Read_keyboard_mat("0:keyboard_mat.txt", (uint8_t*)CustomKey);
  HAL_Fs_Read_keyboard_mat("0:keyboard_ext_mat.txt", (uint8_t*)Extra_CustomKey);
}

/*******************************************************************************
* Function Name  : DATAFLASH_Write_KeyArray
* Description    : ����������д��DataFlash
* Input          : None
* Return         : None
*******************************************************************************/
void DATAFLASH_Write_KeyArray( void )
{
  HAL_Fs_Write_keyboard_mat("0:keyboard_mat.txt", (const uint8_t*)CustomKey);
  HAL_Fs_Write_keyboard_mat("0:keyboard_ext_mat.txt", (const uint8_t*)Extra_CustomKey);
}

/*******************************************************************************
* Function Name  : KEYBOARD_Reset
* Description    : ����FLASH
* Input          : None
* Return         : None
*******************************************************************************/
void KEYBOARD_Reset( void )
{
  uint16_t param[] = { 1, 1, 0, 0,
                       ALG_PARAM_MAGIC,
                       CAP_MOUSE_TOU_THRESH, CAP_MOUSE_REL_THRESH, CAP_MOUSE_MOVE_SPEED,
                       TOUCHBAR_TOU_THRESH, TOUCHBAR_REL_THRESH,
                       DOUBLE_TOUCH_CNT, LONG_TOUCH_CNT
  };

  memcpy(CustomKey, KeyArrary, COL_SIZE*ROW_SIZE);
  memcpy(Extra_CustomKey, Extra_KeyArrary, COL_SIZE*ROW_SIZE);
  memcpy(SP_Key_Map, SP_KeyArrary, SP_KEY_NUMBER*8);
  DATAFLASH_Write_KeyArray( );
  HAL_Fs_Write_keyboard_spkey((uint8_t*)SP_Key_Map);
  HAL_Fs_Create_keyboard_cfg(sizeof(param)/sizeof(uint16_t), param);
}

/*******************************************************************************
* Function Name  : KEYBOARD_ChangeKey
* Description    : ���̽���2������
* Input          : dst_key - Ŀ���, src_key - ԭʼ��
* Return         : None
*******************************************************************************/
void KEYBOARD_ChangeKey( uint8_t dst_key, uint8_t src_key )
{
  uint8_t i = COL_SIZE*ROW_SIZE;
  uint8_t* memaddr = &CustomKey[0][0];
  while (i) {
    --i;
    /* ����src����dst�� */
    if ( *(memaddr + i) == src_key ) *(memaddr + i) = dst_key;
    else if ( *(memaddr + i) == dst_key ) *(memaddr + i) = src_key;
  }
  DATAFLASH_Write_KeyArray( );
}

/*******************************************************************************
* Function Name  : KEYBOARD_Custom_Function
* Description    : ���̶��ƻ�����(���Fn����������ع���)
* Input          : None
* Return         : �������Ҫ���Ͱ�����Ϣ�򷵻�0
*******************************************************************************/
UINT8 KEYBOARD_Custom_Function( void )
{
  static uint8_t Fn_Mode = 0;
  static uint8_t last_state = 0;
  static uint8_t Fn_cnt = 0;  // 4/2/1/1 bit for Reset/ChangeKey/SaveDevices/Reserved
  static uint8_t src_key = 0, dst_key = 0;
  uint16_t Udisk_mode = 1;
  if ( g_keyboard_status.Fn == TRUE && KeyboardDat->Key2 == KEY_None ) { // ����Fn+1��������ֻ��Fn��
    last_state = 1;
    if ( KeyboardDat->Key1 == KEY_None ) { // ���̲��ָ�λ
      if ( Fn_Mode == Fn_Mode_None ) {
        Fn_Mode = Fn_Mode_Reset;
        Fn_cnt &= 0xF0;   // ������������
      }
    } else if ( Fn_Mode == Fn_Mode_ChangeKey ) {  // ���øļ� - ��Fn+src��Fn+dst
      if ( Fn_cnt == 0x04 ) src_key = KeyboardDat->Key1;
      else if ( Fn_cnt == 0x08 ) dst_key = KeyboardDat->Key1;
    } else if ( KeyboardDat->Key1 == KEY_C && Fn_Mode != Fn_Mode_ChangeKey ) { // ���øļ� - �Ȱ�Fn+C
      Fn_Mode = Fn_Mode_ChangeKey;
      Fn_cnt &= 0x0C;
    } else if ( KeyboardDat->Key1 == KEY_O && Fn_Mode != Fn_Mode_ChangeKey ) { // ���ò���ģʽ
      Fn_Mode = Fn_Mode_Enter_Cfg;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_R && Fn_Mode != Fn_Mode_SoftReset ) { // �����λģʽ
      Fn_Mode = Fn_Mode_SoftReset;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_N && Fn_Mode != Fn_Mode_RForBLE ) { // �л�RFģʽ��BLEģʽ
      Fn_Mode = Fn_Mode_RForBLE;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_M && Fn_Mode != Fn_Mode_RFJumptoBoot ) { // RF����0x7A�ý�������BOOT
      Fn_Mode = Fn_Mode_RFJumptoBoot;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_B && Fn_Mode != Fn_Mode_JumpBoot ) { // ��תBOOTģʽ
      Fn_Mode = Fn_Mode_JumpBoot;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_Subtraction && Fn_Mode != Fn_Mode_VolumeDown ) { // ������ģʽ
      Fn_Mode = Fn_Mode_VolumeDown;
      HIDVolume[0] |= Volume_Decr;
      HID_VOL_Process();
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_Equal && Fn_Mode != Fn_Mode_VolumeUp ) { // ������ģʽ
      Fn_Mode = Fn_Mode_VolumeUp;
      HIDVolume[0] |= Volume_Incr;
      HID_VOL_Process();
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_Delete && Fn_Mode != Fn_Mode_PaintedEgg ) { // �ʵ�ģʽ
      Fn_Mode = Fn_Mode_PaintedEgg;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_GraveAccent && Fn_Mode != Fn_Mode_DisEnableBLE ) { // ʹ��/ʧ������
      Fn_Mode = Fn_Mode_DisEnableBLE;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_T && Fn_Mode != Fn_Mode_DisEnableTP ) { // ʹ��/ʧ��С���
      Fn_Mode = Fn_Mode_DisEnableTP;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_U && Fn_Mode != Fn_Mode_UDiskMode ) { // ����U��ģʽ
      Fn_Mode = Fn_Mode_UDiskMode;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_0 && Fn_Mode != Fn_Mode_PriorityUSBorBLE ) { // �����������߻�USB
      Fn_Mode = Fn_Mode_PriorityUSBorBLE;
      Fn_cnt = 0;
    }  else if ( KeyboardDat->Key1 == KEY_1 && Fn_Mode != Fn_Mode_SelectDevice1 ) { // �л����豸1
      Fn_Mode = Fn_Mode_SelectDevice1;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_2 && Fn_Mode != Fn_Mode_SelectDevice2 ) { // �л����豸2
      Fn_Mode = Fn_Mode_SelectDevice2;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_3 && Fn_Mode != Fn_Mode_SelectDevice3 ) { // �л����豸3
      Fn_Mode = Fn_Mode_SelectDevice3;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_4 && Fn_Mode != Fn_Mode_SelectDevice4 ) { // �л����豸4
      Fn_Mode = Fn_Mode_SelectDevice4;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F1 && Fn_Mode != Fn_Mode_LED_Style1 ) { // ����ģʽ1
      Fn_Mode = Fn_Mode_LED_Style1;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F2 && Fn_Mode != Fn_Mode_LED_Style2 ) { // ����ģʽ2
      Fn_Mode = Fn_Mode_LED_Style2;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F3 && Fn_Mode != Fn_Mode_LED_Style3 ) { // ����ģʽ3
      Fn_Mode = Fn_Mode_LED_Style3;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F4 && Fn_Mode != Fn_Mode_LED_Style4 ) { // ����ģʽ4
      Fn_Mode = Fn_Mode_LED_Style4;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F5 && Fn_Mode != Fn_Mode_LED_Style5 ) { // ����ģʽ5
      Fn_Mode = Fn_Mode_LED_Style5;
      Fn_cnt = 0;
    } else {  // ��ʶ���ָ��
      Fn_Mode = Fn_Mode_None;
      Fn_cnt = 0;
    }
    return 0;
  } else if ( last_state == 1 && g_keyboard_status.Fn == FALSE ) {  // �ɿ�Fnִ��ָ��
    last_state = 0;
    switch ( Fn_Mode ) {
      case Fn_Mode_Reset: // ����5��Fn���ð���
        Fn_cnt += 0x10;
        if ( Fn_cnt == 0x50 ) {
          Fn_cnt = 0;
          Fn_Mode = Fn_Mode_None;
          WWDG_ResetCfg(DISABLE); // �ؿ��Ź�
          KEYBOARD_Reset( );
          WWDG_ResetCfg(ENABLE);  // �����Ź�
          OLED_UI_add_SHOWINFO_task("Reset OK!");
          OLED_UI_add_CANCELINFO_delay_task(3000);
        } else if ( Fn_cnt >= 0x30 ) {
          OLED_UI_add_SHOWINFO_task("%d/5 Reset", Fn_cnt >> 4);
          OLED_UI_add_CANCELINFO_delay_task(1500);
        }
        break;
      case Fn_Mode_ChangeKey:
        Fn_cnt += 0x04;
        if ( Fn_cnt == 0x0C ) {
          Fn_cnt = 0;
          Fn_Mode = Fn_Mode_None;
          OLED_UI_add_SHOWINFO_task("Change OK!");
          OLED_UI_add_CANCELINFO_delay_task(3000);
          KEYBOARD_ChangeKey( dst_key, src_key );
        }
        break;
      case Fn_Mode_Enter_Cfg:  // Fn+O��������
        Fn_Mode = Fn_Mode_None;
        if (g_keyboard_status.enter_cfg) {  // �˳���������
#ifdef HAL_OLED
#ifdef OLED_0_66
          OLED_UI_add_CLEARPAGE_task(2, 5);
#endif
#ifdef OLED_0_91
          // TODO
#endif
#endif
          g_keyboard_status.enter_cfg = 0;
        } else {  // �����������
#ifdef HAL_OLED
          OLED_UI_draw_menu(OLED_UI_MENU_REFRESH);
#endif
          g_keyboard_status.enter_cfg = 1;
        }
        break;
      case Fn_Mode_SoftReset:  // Fn+R�����λ
        Fn_Mode = Fn_Mode_None;
        SoftReset();
        break;
      case Fn_Mode_RForBLE:  // Fn+N�л�RF��BLEģʽ�������λ
        Fn_Mode = Fn_Mode_None;
        if (g_Ready_Status.rf == TRUE) DATAFLASH_Write_RForBLE(0);
        else DATAFLASH_Write_RForBLE(1);
        SoftReset();
        break;
      case Fn_Mode_RFJumptoBoot:  // Fn+M����0x7A�ý�������BOOT
        Fn_Mode = Fn_Mode_None;
        if (g_Ready_Status.rf == TRUE) {
          tmos_set_event( RFTaskId, SBP_RF_JUMPBOOT_REPORT_EVT );  // RF JUMPBOOT�¼�
        }
        break;
      case Fn_Mode_JumpBoot:  // Fn+B��תBOOT
        Fn_Mode = Fn_Mode_None;
        APPJumpBoot();
        break;
      case Fn_Mode_VolumeDown:  // Fn+���ż�С���� - �ɿ�ֹͣ
        Fn_Mode = Fn_Mode_None;
        HIDVolume[0] &= ~Volume_Decr;
        HID_VOL_Process();
        break;
      case Fn_Mode_VolumeUp:  // Fn+�Ӻ���������
        Fn_Mode = Fn_Mode_None;
        HIDVolume[0] &= ~Volume_Incr;
        HID_VOL_Process();
        break;
      case Fn_Mode_PaintedEgg:  // Fn+Delete�ʵ�
        Fn_Mode = Fn_Mode_None;
        if (g_Enable_Status.paintedegg == FALSE) {
          g_keyboard_status.changeBL = TRUE;
          led_style_func = WS2812_Style_Custom; // �ʵ�����
          Snake_Init();
          OLED_UI_show_version(1);  // ��ʾ�汾��Ϣ
          g_Enable_Status.paintedegg = TRUE;
        } else {
          OLED_UI_show_version(0);  // ȡ����ʾ�汾��Ϣ
          led_style_func = WS2812_Style_Off;
          g_Enable_Status.paintedegg = FALSE;
        }
        break;
      case Fn_Mode_DisEnableBLE:
        Fn_Mode = Fn_Mode_None; // Fn+���˺Źر�/��������
        if ( g_Ready_Status.ble == FALSE && g_Ready_Status.rf == FALSE ) {
          g_Enable_Status.ble = !g_Enable_Status.ble;
          uint8_t ena_ble = g_Enable_Status.ble;
          bStatus_t status = GAPRole_SetParameter( GAPROLE_ADVERT_ENABLED, sizeof( uint8 ), &ena_ble );
          if ( status != SUCCESS ) OLED_UI_add_SHOWINFO_task("ERR %d", status);
          else if ( g_Enable_Status.ble == TRUE ) OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_BLE_UNCONNECT_IDX, " ON");
          else OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_BLE_UNCONNECT_IDX, " OFF");
          OLED_UI_add_CANCELINFO_delay_task(2000);
        }
        break;
      case Fn_Mode_DisEnableTP:
        Fn_Mode = Fn_Mode_None; // Fn+T�ر�/����С���
        g_Enable_Status.tp = !g_Enable_Status.tp;
        if ( g_Enable_Status.tp == TRUE ) OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_TP_IDX, " ON");
        else OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_TP_IDX, " OFF");
        OLED_UI_add_CANCELINFO_delay_task(2000);
        break;
      case Fn_Mode_UDiskMode:
        Fn_Mode = Fn_Mode_None; // Fn+U����U��ģʽ
        HAL_Fs_Write_keyboard_cfg(FS_LINE_UDISK_MODE, 1, &Udisk_mode);
        SoftReset();
        break;
      case Fn_Mode_PriorityUSBorBLE:  // Fn+0��������/RF��USB�л�
        Fn_Mode = Fn_Mode_None;
        extern BOOL priority_USB;
        if ( g_Ready_Status.usb == TRUE && (g_Ready_Status.ble == TRUE || g_Ready_Status.rf == TRUE) ) {  // ���ж�����Ӳ��л�
          priority_USB = !priority_USB;
#ifdef OLED_0_91
          OLED_UI_ShowOK(26 + priority_USB * 30, 0, FALSE);
          OLED_UI_ShowOK(26 + !priority_USB * 30, 0, TRUE);
#endif
#ifdef OLED_0_66
          if ( priority_USB ) {
            OLED_UI_slot_active((uint8_t*)UI_Slot_Icon[OLED_UI_ICON_USB_IDX],
                                (uint8_t*)UI_Slot_Icon[OLED_UI_ICON_USB_IDX]);
          } else if ( g_Ready_Status.ble == TRUE ) {
            OLED_UI_slot_active((uint8_t*)UI_Slot_Icon[OLED_UI_ICON_BLE_UNCONNECT_IDX + DeviceAddress[5]],
                                (uint8_t*)UI_Slot_Icon[OLED_UI_ICON_BLE_UNCONNECT_IDX + DeviceAddress[5]]);
          } else {  // RF_Ready
            OLED_UI_slot_active((uint8_t*)UI_Slot_Icon[OLED_UI_ICON_RF_IDX],
                                (uint8_t*)UI_Slot_Icon[OLED_UI_ICON_RF_IDX]);
          }
          OLED_UI_add_default_task(OLED_UI_FLAG_DRAW_SLOT);
#endif
          if ( priority_USB ) OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_USB_IDX, "Priority");
          else if ( g_Ready_Status.rf == FALSE ) OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_BLE_UNCONNECT_IDX, "Priority");
          else OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_RF_IDX, "Priority");
          OLED_UI_add_CANCELINFO_delay_task(2000);
        }
        break;
      case Fn_Mode_SelectDevice1 ... Fn_Mode_SelectDevice4: // ��Fn+1~4�л��豸
        DeviceAddress[5] = Fn_Mode - Fn_Mode_SelectDevice1 + 1;
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_BLE_UNCONNECT_IDX, "Device%d", DeviceAddress[5]);
        OLED_UI_add_CANCELINFO_delay_task(2000);
        Fn_Mode = Fn_Mode_None;
        tmos_start_task( hidEmuTaskId, CHANGE_ADDR_EVT, 500 );
        break;
      case Fn_Mode_LED_Style1:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S0");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, " OFF");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Custom;  // Fn+F1 - �رձ���(���Ᵽ�ֲ���)
        break;
      case Fn_Mode_LED_Style2:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S1");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, "Breath");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Breath;  // Fn+F2 - ����ʹ�ú�����ģʽ
        break;
      case Fn_Mode_LED_Style3:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S2");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, "Waterful");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Waterful;  // Fn+F3 - ����ʹ����ˮ��ģʽ
        break;
      case Fn_Mode_LED_Style4:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S3");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, "Touch");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Touch;  // Fn+F4 - ����ʹ�ô��غ�����ģʽ
        break;
      case Fn_Mode_LED_Style5:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S4");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, "Rainbow");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Rainbow;  // Fn+F5 - ����ʹ�òʺ��ģʽ
        break;
      case Fn_Mode_GiveUp:
        Fn_cnt = 0;
        Fn_Mode = Fn_Mode_None;
        break;
      default:  // δʶ���ָ��
        ;
    }
    return 0;
  }
  return 1;
}

/*******************************************************************************
* Function Name  : KEYBOARD_Init
* Description    : ���̳�ʼ������
* Input          : None
* Return         : None
*******************************************************************************/
void KEYBOARD_Init( void )
{
    uint8_t i;
    DATAFLASH_Read_KeyArray( );   // DataFlash���밴��
    HAL_Fs_Read_keyboard_spkey((uint8_t*)SP_Key_Map);   // DataFlash����spKEY
    CustomKey[12][5] = KEY_Fn;   // ��֤�ϵ�Fn���ڶ�Ӧλ�� - �������̲������޸Ĵ˴�
    for (i = 0; i < ROW_SIZE; i++) {
        Row_Pin_ALL |= Row_Pin[i];
    }
    Row_GPIO_(SetBits)( Row_Pin_ALL );
    Row_GPIO_(ModeCfg)( Row_Pin_ALL, GPIO_ModeOut_PP_20mA );
    Row_GPIO_(SetBits)( Row_Pin[0] );

    for (i = 0; i < COL_SIZE; i++) {
        Colum_Pin_ALL |= Colum_Pin[i];
    }
    Colum_GPIO_(ResetBits)( Colum_Pin_ALL );
    Colum_GPIO_(ModeCfg)( Colum_Pin_ALL, GPIO_ModeIN_PD );
}

/*******************************************************************************
* Function Name  : KEYBOARD_Detection
* Description    : ���̼�ⰴ����Ϣ����
* Input          : None
* Return         : None
*******************************************************************************/
void KEYBOARD_Detection( void )
{
    static uint8_t current_row = 0;
    static uint8_t press_Capslock = 0;  // ����0��ʾCapsLock����
    static uint8_t Touchbar_SP_Key = 0;  // ����0��ʾ������������
    static BOOL press_NormalKey = FALSE;
    uint8_t current_colum, key_idx, i, j;

    /* �������������̰������ */
    if (TouchbarDat.swip_left == TRUE) {
        TouchbarDat.swip_left = FALSE;
        Touchbar_SP_Key = PRESS_HOLDING_TIMES;
        memcpy(KeyboardDat->data, SP_Key_Map[5], 8);  // KEY_SP_6
        g_Ready_Status.keyboard_key_data = TRUE;  // �����¼�
        return;
    } else if (TouchbarDat.swip_right == TRUE) {
        TouchbarDat.swip_right = FALSE;
        Touchbar_SP_Key = PRESS_HOLDING_TIMES;
        memcpy(KeyboardDat->data, SP_Key_Map[6], 8);  // KEY_SP_7
        g_Ready_Status.keyboard_key_data = TRUE;  // �����¼�
        return;
    } else if (Touchbar_SP_Key) {
        if (--Touchbar_SP_Key == 0) {  // ������SP���ĳ���ʱ�䵽��
            memset(KeyboardDat->data, 0, 8);
            KEYBOARD_data_index = 2;
            g_Ready_Status.keyboard_key_data = TRUE;  // �����¼�
        }
        return;
    }
    /* CapsLock������� */
    if (KeyArr_ChangeTimes > 0 && KeyArr_ChangeTimes <= MAX_CHANGETIMES) {  // ����CapsLock���̲��ָı�����ȴ�
        if (KeyArr_ChangeTimes == MAX_CHANGETIMES) { // ����ֵ����MAX_CHANGETIMES�ı���̲���
            KeyArr_Ptr = Extra_CustomKey;
#ifdef OLED_0_91
            OLED_UI_add_SHOWSTRING_task(2, 1, "L2");
#endif
        }
        ++KeyArr_ChangeTimes; // ���̼���ֵ����
    } else if (press_Capslock) {  // CapsLock������
        if (--press_Capslock == 0) {  // CapsLock���³���ʱ�䵽��
          for (key_idx = 2; key_idx < 8; key_idx++) {
              if (KeyboardDat->data[key_idx] == KEY_CapsLock) {
                  memcpy(&KeyboardDat->data[key_idx], &KeyboardDat->data[key_idx] + 1, 7 - key_idx);
                  KeyboardDat->Key6 = 0;
              }
          }
          KEYBOARD_data_index--;
          g_Ready_Status.keyboard_key_data = TRUE;  // �����¼�
          return;
        }
    }
    /* �������� */
    for (current_colum = 0; current_colum < COL_SIZE; current_colum++) {    // ��ѯ��һ�иı�
        if (KeyMatrix[current_colum][current_row] == 0 && Colum_GPIO_(ReadPortPin)( Colum_Pin[current_colum] ) != 0) {  // ����
            if (g_keyboard_status.SP_Key != 0) continue;  // SP����Ч�󲻽������ఴ��
            else if (KEYBOARD_data_index >= 8 && KeyArr_Ptr[current_colum][current_row] < KEY_LeftCTRL) continue;    // ����6����ͨ��������
            KeyMatrix[current_colum][current_row] = 1;  // ����״̬��ɰ���
            if (led_style_func == WS2812_Style_Touch && Key_To_LEDNumber[current_colum][current_row] != 0xFF) { // ���غ�����ģʽ
                LED_BYTE_Buffer[Key_To_LEDNumber[current_colum][current_row]][0] =
                LED_BYTE_Buffer[Key_To_LEDNumber[current_colum][current_row]][1] =
                LED_BYTE_Buffer[Key_To_LEDNumber[current_colum][current_row]][2] = LED_BRIGHTNESS;
            }
            g_Ready_Status.keyboard_key_data = TRUE; // �����¼�
            if (KeyArr_Ptr[current_colum][current_row] == KEY_Fn) {  // ���ܼ�
                g_keyboard_status.Fn = TRUE;
            } else if (KeyArr_Ptr[current_colum][current_row] >= KEY_SP_1) {  // SP��(��������)
                g_keyboard_status.SP_Key = KeyArr_Ptr[current_colum][current_row] - KEY_SP_1;
                memcpy(KeyboardDat->data, SP_Key_Map[g_keyboard_status.SP_Key], 8);
            } else if (KeyArr_Ptr[current_colum][current_row] >= KEY_MouseL) {    // ������
                MouseDat->data[0] |= 1 << KeyArr_Ptr[current_colum][current_row] - KEY_MouseL;
                g_Ready_Status.keyboard_mouse_data = TRUE;  // ��������¼�
            } else if (KeyArr_Ptr[current_colum][current_row] >= KEY_LeftCTRL) {    // Ctrl�������
                KeyboardDat->data[0] |= 1 << (KeyArr_Ptr[current_colum][current_row] - KEY_LeftCTRL);
            } else {
                if (CustomKey[current_colum][current_row] == KEY_CapsLock) {  // ������Сд������Extra_CustomKey��
                    KeyArr_ChangeTimes = 1; // ���̲���ת��-��ʼ����
                } else {
                    KeyboardDat->data[KEYBOARD_data_index++] = KeyArr_Ptr[current_colum][current_row];
                    press_NormalKey = KeyArr_ChangeTimes > MAX_CHANGETIMES;
                }
            }
        } else if (KeyMatrix[current_colum][current_row] != 0 && Colum_GPIO_(ReadPortPin)( Colum_Pin[current_colum] ) == 0) {   // ����
            KeyMatrix[current_colum][current_row] = 0;
            g_Ready_Status.keyboard_key_data = TRUE; // �����¼�
            if (KeyArr_Ptr[current_colum][current_row] == KEY_Fn) {  // ���ܼ�
                g_keyboard_status.Fn = FALSE;
            } else if (KeyArr_Ptr[current_colum][current_row] >= KEY_SP_1) {  // SP��(��������)
                g_keyboard_status.SP_Key = 0;
                memset(KeyboardDat->data, 8, 0);
            }  else if (KeyArr_Ptr[current_colum][current_row] >= KEY_MouseL) {    // ������
                MouseDat->data[0] &= ~(1 << KeyArr_Ptr[current_colum][current_row] - KEY_MouseL);
                g_Ready_Status.keyboard_mouse_data = TRUE;  // ��������¼�
            } else if (KeyArr_Ptr[current_colum][current_row] >= KEY_LeftCTRL) {    // Ctrl�������
                KeyboardDat->data[0] &= ~(1 << (KeyArr_Ptr[current_colum][current_row] - KEY_LeftCTRL));
            } else {
                if (CustomKey[current_colum][current_row] == KEY_CapsLock) {  // �����Сд���뿪Extra_CustomKey��
                    if (KeyArr_ChangeTimes > MAX_CHANGETIMES) {
                        KeyArr_Ptr = CustomKey;
#ifdef OLED_0_91
                        OLED_UI_add_SHOWSTRING_task(2, 1, "L1");
#endif
                    }
                    if (press_NormalKey == FALSE || KeyArr_ChangeTimes <= MAX_CHANGETIMES) {
                        if (KEYBOARD_data_index < 8) {
                            press_Capslock = PRESS_HOLDING_TIMES;
                            KeyboardDat->data[KEYBOARD_data_index++] = KEY_CapsLock;
                        }
                    }
                    KeyArr_ChangeTimes = 0;
                    press_NormalKey = FALSE;
                } else {
                    for (key_idx = 2; key_idx < 8; key_idx++) {
                        if (KeyboardDat->data[key_idx] == CustomKey[current_colum][current_row] ||
                            KeyboardDat->data[key_idx] == Extra_CustomKey[current_colum][current_row]) {  // ���𰴼�2�㶼���
                            memcpy(&KeyboardDat->data[key_idx], &KeyboardDat->data[key_idx] + 1, 7 - key_idx);
                            KeyboardDat->Key6 = 0;
                        }
                    }
                    KEYBOARD_data_index--;
                }
            }
        }
    }
    Row_GPIO_(ResetBits)( Row_Pin[current_row++] );
    if (current_row >= ROW_SIZE) {
        current_row = 0;
    }
    Row_GPIO_(SetBits)( Row_Pin[current_row] );
}

/*******************************************************************************
* Function Name  : KEYBOARD_EnterNumber
* Description    : �����������ֿ�
* Input          : *key - ָ���������ֵ�ָ��
*                  *preStr - ����ǰ����ʾ
*                  *postStr - ������ɵ���ʾ
*                  *limit_len - ���Ƴ���(Ϊ0������, �24)
* Return         : ����0��ʾ������ɣ�����0xFF��ʾ�������
*******************************************************************************/
uint8_t KEYBOARD_EnterNumber(uint32_t *key, const char* preStr, const char* postStr, uint8_t limit_len)
{
  static uint8_t idx = 0;
  static uint32_t passkey = 0;
  static char passkey_str[25] = { '\0' };
  const uint8_t keyhash[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
  if ( KeyboardDat->Key1 == KEY_BACKSPACE ) { // �˸񵥶�����
      if ( idx > 0 ) {
          passkey_str[--idx] = '\0';
          passkey /= 10;
      }
      if ( passkey_str[0] == '\0' ) {
        OLED_PRINT("%s", preStr);
      } else {
        OLED_PRINT("%s", passkey_str);
      }
  } else if ( idx == limit_len || limit_len == 0 ) {  // ���һ��������Enter�����
      if ( KeyboardDat->Key1 == KEY_ENTER ) {
          OLED_PRINT("%s", postStr);
          *key = passkey;
          passkey = idx = passkey_str[0] = 0;
          return 0;
      }
  } else if ( KeyboardDat->Key1 >= KEY_1 && KeyboardDat->Key1 <= KEY_0 ){
      passkey = passkey * 10 + keyhash[KeyboardDat->Key1 - KEY_1];
      passkey_str[idx++] = keyhash[KeyboardDat->Key1 - KEY_1] + 0x30;
      passkey_str[idx] = '\0';
      OLED_PRINT("%s", passkey_str);
  } else if ( KeyboardDat->Key1 == KEY_ESCAPE ){  // Esc���������
      passkey = idx = passkey_str[0] = 0;
      OLED_PRINT("%s", preStr);
      return 0xFF;
  }
  return 1;
}
