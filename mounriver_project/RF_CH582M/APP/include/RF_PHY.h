/********************************** (C) COPYRIGHT *******************************
 * File Name          : rf_phy.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/11/12
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef CENTRAL_H
#define CENTRAL_H

#ifdef __cplusplus
extern "C" {
#endif

#define SBP_RF_START_DEVICE_EVT    1
#define SBP_RF_PERIODIC_EVT        2
#define SBP_RF_RF_RX_EVT           4
#define SBP_RF_CAPSLOCK_TX_EVT     8

#define LLE_MODE_ORIGINAL_RX       (0x80) //�������LLEMODEʱ���ϴ˺꣬����յ�һ�ֽ�Ϊԭʼ���ݣ�ԭ��ΪRSSI��

extern tmosTaskID RFtaskID;
extern uint8_t CAPSLOCK_DATA[2];

extern void RF_Init(void);

#ifdef __cplusplus
}
#endif

#endif