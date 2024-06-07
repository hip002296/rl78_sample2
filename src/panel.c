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
				//たぶん下3つのカウンターはpanel関数が始まると0になり、終わると1になる
	DGIN_INIT; 		//g_ucDGIN_Count = 0;	//たぶん入力信号
	BCNT_INIT;		//g_ucBCNT_Count = 0;	//バイナリーカウンター?
	IC74HC4511_INIT;	//g74HC4511_Count = 0;
	
	flag = dotstate();

	DGIN_PROC( I_18,0, LOW,0,fTrg10ms);//I_18に0 or 1が入る?	//fTrg10ms(使わないもの?)が引数にあるため意味ない可能性あり?
	BCNT_PROC( 9,fOFF,fOFF,I_18,F0617,F0618,F0619,F0620 );
	
	//IC74HC4511_PROC関数にて、BCNT_PROC関数に渡した引数とDGOUT_PROCに渡すものを引数にしている
	//最初の引数fOFF,fON,fONでパネルの状態を数値表示状態にする
	//中央の引数F0617,F0618,F0619,F0620で入力信号をみる
	//最後の引数F0914,F0915,F0916,F0917,F0918,F0919,F0920で入力に対応する数字を出力する
	IC74HC4511_PROC( fOFF,fON,fON,F0617,F0618,F0619,F0620,F0914,F0915,F0916,F0917,F0918,F0919,F0920 );	//ここで数字をうまいことやってる?
	
	//DGOUT_setValue関数	//これ以降では受け取った数値を表示する
	DGOUT_PROC( 30, F0914, HIGH );//上の横棒
	DGOUT_PROC( 31, F0915, HIGH );//右上縦棒
	DGOUT_PROC( 32, F0916, HIGH );//右下縦棒
	DGOUT_PROC( 33, F0917, HIGH );//下の横棒
	DGOUT_PROC( 51, F0918, HIGH );//左下縦棒
	DGOUT_PROC( 52, F0919, HIGH );//左上縦棒
	DGOUT_PROC( 53, F0920, HIGH );//中央横棒
	DGOUT_PROC( 54, flag, HIGH );//右下の点		//これに条件付け加える
}

