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
* File Name    : counter.h
* Version      : Applilet EZ PL for RL78
* Device(s)    : R5F1056A,R5F1057A,R5F1058A
* Tool-Chain   : CC-RL
* Description  : This file implements main function.
* Creation Date: 2016/09/14
*******************************************************************************/

#ifndef _COUNTER_H_
#define _COUNTER_H_
/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define CNT_HOLDTYPE		1
#define CNT_CYCLICTYPE		2

/*******************************************************************************
** CNT_INIT0	
********************************************************************************/
#define	CNT_INIT0																\
{																				\
		CNT_Initialize();														\
}

/*******************************************************************************
** CNT_INIT	
********************************************************************************/
#define	CNT_INIT																\
{																				\
		CNT_Counter_Clear();													\
}

/*******************************************************************************
** CNT_PROC	
********************************************************************************/
#define	CNT_PROC(In, Reset, Type, Limit)										\
{																				\
		CNT_Set(Limit, Type, In, Reset);										\
		CNT_Counter();															\
}

/*******************************************************************************
** CNT_OUT	
********************************************************************************/
#define	CNT_OUT(Val, Out)														\
{																				\
	{																			\
		UCHAR	ucret;															\
																				\
		ucret = CNT_Compare(Val);												\
		Out = ucret & 0x01;														\
	}																			\
}

/*******************************************************************************
** BCNT_INIT0	
********************************************************************************/
#define	BCNT_INIT0																\
{																				\
		BCNT_Initialize();														\
}

/*******************************************************************************
** BCNT_INIT	
********************************************************************************/
#define	BCNT_INIT																\
{																				\
		BCNT_Counter_Clear();													\
}

/*******************************************************************************
** BCNT_PROC	
********************************************************************************/
#define	BCNT_PROC(max, mr, cp0, cp1, O0, O1, O2, O3)							\
{																				\
		UCHAR ucret;															\
		ucret = BCNT_Evaluate(mr, cp0, cp1, max);								\
		O0 = (ucret & 0x01);													\
		ucret >>= 1;															\
		O1 = (ucret & 0x01);													\
		ucret >>= 1;															\
		O2 = (ucret & 0x01);													\
		ucret >>= 1;															\
		O3 = (ucret & 0x01);													\
		BCNT_Counter();															\
}

/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
/*	Function Prototype	*/
void	CNT_Set( USHORT Limit, UCHAR Type, UCHAR In, UCHAR Reset );
UCHAR	CNT_Compare( USHORT Val );
void	CNT_Initialize( void );
void	CNT_Counter_Clear( void );
void	CNT_Counter( void );

void	BCNT_Initialize( void );
void	BCNT_Counter_Clear( void );
UCHAR	BCNT_Evaluate( UCHAR mr, UCHAR cp0, UCHAR cp1, UCHAR max );
void	BCNT_Counter( void );

#endif /* _COUNTER_H_ */
