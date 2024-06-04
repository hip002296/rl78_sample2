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
* File Name    : puls.h
* Version      : Applilet EZ PL for RL78
* Device(s)    : R5F1056A,R5F1057A,R5F1058A
* Tool-Chain   : CC-RL
* Description  : This file implements main function.
* Creation Date: 2016/09/14
*******************************************************************************/

#ifndef _PULS_H_
#define _PULS_H_
/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/

/*******************************************************************************
Macro definitions
*******************************************************************************/
/*******************************************************************************
** PULSE_INIT0	
********************************************************************************/
#define	PULSE_INIT0( DutyMode, OutPort )										\
{																				\
		PULSE_Set(OutPort, DutyMode);											\
}

/*******************************************************************************
** PULSE_INIT	
********************************************************************************/
#define	PULSE_INIT																\
{																				\
		PULSE_Counter_Clear();													\
}

/*******************************************************************************
** PULSE_PROC	
********************************************************************************/
#define	PULSE_PROC(In1, In2, In3, In4, In5)										\
{																				\
		PULSE_Set_Value(In1, In2, In3, In4, In5);								\
}

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/*  Structure Definition	*/
typedef	struct	tagPULSE_TBL
{
	UCHAR	Port;
	UCHAR	TermNum;
	UCHAR	Mode;
}PULSE_TBL;

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
/*	Function Prototype	*/
void	PULSE_Set( UCHAR Port, UCHAR Chat );
UCHAR	PULSE_Proc3( UCHAR In100, UCHAR In50, UCHAR In0 );
UCHAR	PULSE_Proc5( UCHAR In100, UCHAR In75, UCHAR In50, UCHAR In25, UCHAR In0 );
void	PULSE_Count( void );
void	PULSE_Counter_Clear( void );
void	PULSE_Set_Value( UCHAR In1,UCHAR In2,UCHAR In3,UCHAR In4,UCHAR In5 );

#endif /* _PULS_H_ */
