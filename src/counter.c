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
* File Name    : counter.c
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
#include <string.h>
#include "counter.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/

/*******************************************************************************
Private variables and functions
*******************************************************************************/
#if defined CNT_USED
static UCHAR	ucgCNT_Flg[(CNT_USED / 8) + 1];
static USHORT	usgCNT_Val[CNT_USED];
static UCHAR	ucgCNT_Cnt;
#endif /* end of defined CNT_USED */

#if defined BCNT_USED
static UCHAR	g_ucBCNT_LastCounterVal[BCNT_USED];
static UCHAR	g_ucBCNT_LastCp0[(BCNT_USED / 8) + 1];
static UCHAR	g_ucBCNT_LastCp1[(BCNT_USED / 8) + 1];
static UCHAR	g_ucBCNT_Count;
#endif /* end of defined BCNT_USED */

#if defined CNT_USED
/*******************************************************************************
* Function Name: CNT_Set
* Description  : Counter panel increment.
* Arguments    : Limit 	... count limit
*                Type 	... count mode (HOLD/CYCLINC)
*                In    	... enable(=1)/disable(=0)
*                Reset   ... reset(=1)
* Return Value : none
********************************************************************************/
void CNT_Set( USHORT Limit, UCHAR Type, UCHAR In, UCHAR Reset )
{
	UCHAR	ucflg;

	if (Reset == HIGH)
	{
		BitMemSet(ucgCNT_Flg, ucgCNT_Cnt, 1);
		usgCNT_Val[ucgCNT_Cnt] = 0;
		return;
	}
	
	ucflg = BitMemGet(ucgCNT_Flg, ucgCNT_Cnt);
	
	if(In == HIGH)
	{
		if(ucflg == LOW)
		{
			usgCNT_Val[ucgCNT_Cnt]++;
			if(usgCNT_Val[ucgCNT_Cnt] > Limit)
			{
				if(Type == CNT_HOLDTYPE)			usgCNT_Val[ucgCNT_Cnt] = Limit;
				else if(Type == CNT_CYCLICTYPE)		usgCNT_Val[ucgCNT_Cnt] = 0;
			}
		}
	}
	
	BitMemSet(ucgCNT_Flg, ucgCNT_Cnt, In);
}

/*******************************************************************************
* Function Name: CNT_Compare
* Description  : Compare counter.
* Arguments    : Val ... compare value.
* Return Value : none
********************************************************************************/
UCHAR CNT_Compare( USHORT Val )
{
	if (usgCNT_Val[ucgCNT_Cnt-1] == Val) return 1;
	return 0;
}

/*******************************************************************************
* Function Name: CNT_Initialize
* Description  : COUNTER Panel Initialize.
* Arguments    : none
* Return Value : none
********************************************************************************/
void CNT_Initialize( void )
{
	memset(ucgCNT_Flg, 0, (CNT_USED / 8) + 1);
	memset(usgCNT_Val, 0, CNT_USED * 2);
}

/*******************************************************************************
* Function Name: CNT_Counter_Clear
* Description  : COUNTER Panel Counter Clear.
* Arguments    : none
* Return Value : none
********************************************************************************/
void CNT_Counter_Clear( void )
{
	ucgCNT_Cnt = 0;
}

/*******************************************************************************
* Function Name: CNT_Counter
* Description  : COUNTER Panel Counter.
* Arguments    : none
* Return Value : none
********************************************************************************/
void CNT_Counter( void )
{
	ucgCNT_Cnt++;
}
#endif /* end of defined CNT_USED */

#if defined BCNT_USED
/*******************************************************************************
* Function Name: BCNT_Initialize
* Description  : COUNTER Panel BCNT_Initialize.
* Arguments    : none
* Return Value : none
********************************************************************************/
void BCNT_Initialize( void )
{
	/* memset( "Count value of binary counter", 0, "Number of binary counters" ) */
	memset( g_ucBCNT_LastCounterVal, 0, BCNT_USED );
	
	/* memset( "Last value of cp0 of binary counter" , 0, "Number of binary counters" / 8 + 1 ) */
	memset( g_ucBCNT_LastCp0, 0, (BCNT_USED / 8)+1 );
	
	/* memset( "Last value of cp1 of binary counter" , 0, "Number of binary counters" / 8 + 1 ) */
	memset( g_ucBCNT_LastCp1, 0, (BCNT_USED / 8)+1 );
}

/*******************************************************************************
* Function Name: BCNT_Counter_Clear
* Description  : COUNTER Panel BCNT_Counter_Clear.
* Arguments    : none
* Return Value : none
********************************************************************************/
void BCNT_Counter_Clear( void )
{
	/* "Count of PROC of binary counter" <- 0 */
	g_ucBCNT_Count = 0;
}

/*******************************************************************************
* Function Name: BCNT_Evaluate
* Description  : COUNTER Panel BCNT_Evaluate.
* Arguments    : mr
*                cp0 ... cp0 of binary counter
*                cp1 ... cp1 of binary counter
*                maximum value
* Return Value : Count value of binary counter
********************************************************************************/
UCHAR BCNT_Evaluate( UCHAR mr, UCHAR cp0, UCHAR cp1, UCHAR max )
{
	UCHAR	lastcp0;	/* Last input value of cp0 terminal */
	UCHAR	lastcp1;	/* Last input value of cp1 terminal */
	UCHAR	count;		/* Count value of binary counter */
	
	/* Last value of cp0 of binary counter is acquired. */
	lastcp0 = BitMemGet(g_ucBCNT_LastCp0, g_ucBCNT_Count);
	
	/* Last value of cp1 of binary counter is acquired. */
	lastcp1 = BitMemGet(g_ucBCNT_LastCp1, g_ucBCNT_Count);
	
	/* Count value of binary counter is acquired. */
	count = ByteMemGet(g_ucBCNT_LastCounterVal, g_ucBCNT_Count);
	
	if (mr == LOW) {
		if (cp0 == LOW) {
			if (cp1 == LOW) {
				if (lastcp1 == HIGH) {
					/* (Count value of binary counter)++ */
					count++;
				}
			}
		}
		else {
			if (lastcp0 == LOW) {
				if (cp1 == HIGH) {
					/* (Count value of binary counter)++ */
					count++;
				}
			}
		}
	}
	
	else {
		/* (Count value of binary counter)<-0 */
		count = 0;
	}
	
	/* If the count value is larger than the count maximum value, it returns it to 0. */
	if (count > max) {
		/* (Count value of binary counter)<-0 */
		count = 0;
	}
	
	/* This value of cp0 of binary counter is preserved. */
	BitMemSet(g_ucBCNT_LastCp0, g_ucBCNT_Count, cp0);
	
	/* This value of cp1 of binary counter is preserved. */
	BitMemSet(g_ucBCNT_LastCp1, g_ucBCNT_Count, cp1);
	
	/* This count value of binary counter is preserved. */
	ByteMemSet(g_ucBCNT_LastCounterVal, g_ucBCNT_Count, count);
	
	/* (Count value of binary counter) is returned. */
	return count;
}

/*******************************************************************************
* Function Name: BCNT_Counter
* Description  : COUNTER Panel BCDCNT_Counter.
* Arguments    : none
* Return Value : none
********************************************************************************/
void BCNT_Counter( void )
{
	/* "Count of PROC of binary counter"++ */
	g_ucBCNT_Count++;
}

#endif /* end of defined BCNT_USED */
