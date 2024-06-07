/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/

/*******************************************************************************
* File Name    : panel.c
* Version      : Applilet EZ PL for RL78
* Device(s)    : R5F1056A,R5F1057A,R5F1058A
* Tool-Chain   : CC-RL
* Description  : This file implements main function.
* Creation Date: 2016/09/14
*******************************************************************************/

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include "sfr.h"
#include "common.h"
#include "config.h"
#include "panel.h"

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
#if defined DTC_USED || defined STANDBY_USED
#pragma address dtc_vectortable = VECTOR_ADDRESS
UCHAR __near dtc_vectortable[40];
#pragma address dtc_controldata = CONTROLDATA_ADDRESS
ST_DTC_DATA __near dtc_controldata[24];
#endif /*DTC_USED || STANDBY_USED*/
/*--- Variable declaration ---*/
	UCHAR I_18;
	UCHAR F0416 = 0;
	UCHAR F0614 = 0;
	UCHAR F0615 = 0;
	UCHAR F0617 = 0;
	UCHAR F0618 = 0;
	UCHAR F0619 = 0;
	UCHAR F0620 = 0;
	UCHAR F0914 = 0;
	UCHAR F0915 = 0;
	UCHAR F0916 = 0;
	UCHAR F0917 = 0;
	UCHAR F0918 = 0;
	UCHAR F0919 = 0;
	UCHAR F0920 = 0;
	UCHAR F1321 = 0;

/*----------------------------*/

void panel_init0(void)
{

	DGIN_INIT0(0);
	BCNT_INIT0;
	IC74HC4511_INIT0;
}

void panel(void)
{
	UCHAR flag;
				//���Ԃ�3�̃J�E���^�[��panel�֐����n�܂��0�ɂȂ�A�I����1�ɂȂ�
	DGIN_INIT; 		//g_ucDGIN_Count = 0;	//���Ԃ���͐M��
	BCNT_INIT;		//g_ucBCNT_Count = 0;	//�o�C�i���[�J�E���^�[?
	IC74HC4511_INIT;	//g74HC4511_Count = 0;
	
	flag = dotstate();

	DGIN_PROC( I_18,0, LOW,0,fTrg10ms);//I_18��0 or 1������?	//fTrg10ms(�g��Ȃ�����?)�������ɂ��邽�߈Ӗ��Ȃ��\������?
	BCNT_PROC( 9,fOFF,fOFF,I_18,F0617,F0618,F0619,F0620 );
	
	//IC74HC4511_PROC�֐��ɂāABCNT_PROC�֐��ɓn����������DGOUT_PROC�ɓn�����̂������ɂ��Ă���
	//�ŏ��̈���fOFF,fON,fON�Ńp�l���̏�Ԃ𐔒l�\����Ԃɂ���
	//�����̈���F0617,F0618,F0619,F0620�œ��͐M�����݂�
	//�Ō�̈���F0914,F0915,F0916,F0917,F0918,F0919,F0920�œ��͂ɑΉ����鐔�����o�͂���
	IC74HC4511_PROC( fOFF,fON,fON,F0617,F0618,F0619,F0620,F0914,F0915,F0916,F0917,F0918,F0919,F0920 );	//�����Ő��������܂����Ƃ���Ă�?
	
	//DGOUT_setValue�֐�	//����ȍ~�ł͎󂯎�������l��\������
	DGOUT_PROC( 30, F0914, HIGH );//��̉��_
	DGOUT_PROC( 31, F0915, HIGH );//�E��c�_
	DGOUT_PROC( 32, F0916, HIGH );//�E���c�_
	DGOUT_PROC( 33, F0917, HIGH );//���̉��_
	DGOUT_PROC( 51, F0918, HIGH );//�����c�_
	DGOUT_PROC( 52, F0919, HIGH );//����c�_
	DGOUT_PROC( 53, F0920, HIGH );//�������_
	DGOUT_PROC( 54, flag, HIGH );//�E���̓_		//����ɏ����t��������
}

