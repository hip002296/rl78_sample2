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
* File Name    : 74hc.c
* Version      : Applilet EZ PL for RL78
* Device(s)    : R5F1056A,R5F1057A,R5F1058A
* Tool-Chain   : CC-RL
* Description  : This file implements the function of 74HC IC Series.
* Creation Date: 2016/09/14
*******************************************************************************/

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include "sfr.h"
#include "common.h"
#include <string.h>
#include "74hc.h"
#include "config.h"

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
#if defined IC74HC112_USED
UCHAR	g74HC112_LastQ[(IC74HC112_USED / 8) + 1];
UCHAR	g74HC112_LastCK[(IC74HC112_USED / 8) + 1];
UCHAR	g74HC112_Count = 0;
#endif /* end of defined IC74HC112_USED */

#if defined IC74HC77_USED
UCHAR	g74HC77_LastQ[(IC74HC77_USED / 8) + 1];
UCHAR	g74HC77_Count = 0;
#endif /* end of defined IC74HC77_USED */

#if defined IC74HC4511_USED
UCHAR	g74HC4511_LastNum[IC74HC4511_USED];
UCHAR	g74HC4511_Count = 0;
#endif /* end of defined IC74HC4511_USED */

#if defined IC74HC166_USED
UCHAR	g74HC166_LastCK[(IC74HC166_USED / 8) + 1];
UCHAR	g74HC166_LastValue[IC74HC166_USED];
UCHAR	g74HC166_Count = 0;
#endif /* end of defined IC74HC166_USED */

/*******************************************************************************
Private variables and functions
*******************************************************************************/

#if defined IC74HC112_USED
/*******************************************************************************
* Function Name: IC_74HC112_Out_Q
* Description  : J-K Flip-Flop with Preset and Clear.
*                (Q-terminal output value calculate)
* Arguments    : J_in	J-terminal input value (HIGH or LOW)
*                K_in	K-terminal input value (HIGH or LOW)
*                CLR_in CLR-terminal input value (HIGH or LOW)
*                PR_in 	PR-terminal input value (HIGH or LOW)
*                CK_in	CK-terminal input value (HIGH or LOW)
* Return Value : Q-terminal output value (HIGH or LOW)
********************************************************************************/
UCHAR  IC_74HC112_Out_Q( UCHAR J_in, UCHAR K_in, UCHAR CLR_in, UCHAR PR_in, UCHAR CK_in )
{
	UCHAR	Q_out;
	UCHAR	work;
	UCHAR	lastQ;
	UCHAR	lastCK;
	
	lastQ = BitMemGet(g74HC112_LastQ, g74HC112_Count);
	lastCK = BitMemGet(g74HC112_LastCK, g74HC112_Count);
	if(PR_in == HIGH)
	{
		if(CLR_in == HIGH)
		{
			if(CK_in == LOW)
			{
				if(lastCK == HIGH)
				{
					work = J_in + K_in;
					if	   (work == 0)	Q_out = lastQ;
					else if(work == 1)	Q_out = J_in;
					else 				Q_out = (~lastQ) & 0x01;	/* work == 2 */
				}
				else	/* lastCK == LOW */
				{
					Q_out = lastQ;
				}
			}
			else	/* CK_in == HIGH */
			{
				Q_out = lastQ;
			}
		}
		else	/* CLR_in == LOW */
		{
			Q_out = LOW;
		}
	}
	else	/* PR_in == LOW */
	{
		Q_out = HIGH;
	}
	BitMemSet(g74HC112_LastCK, g74HC112_Count, CK_in);
	BitMemSet(g74HC112_LastQ, g74HC112_Count, Q_out);

	return (Q_out);
}

/*******************************************************************************
* Function Name: IC_74HC112_Out_invQ
* Description  : J-K Flip-Flop with Preset and Clear
*                (~Q-terminal output value calculate)
* Arguments    : Q_out	Q-terminal output value (HIGH or LOW)
*                CLR_in	CLR-terminal input value (HIGH or LOW)
*                PR_in 	PR-terminal input value (HIGH or LOW)
* Return Value : ~Q-terminal output value (HIGH or LOW)
********************************************************************************/
UCHAR IC_74HC112_Out_invQ( UCHAR Q_out, UCHAR CLR_in, UCHAR PR_in )
{
	UCHAR	invQ_out;
	
	if(PR_in == LOW){
		if(CLR_in == LOW){
			return (HIGH);
		}
	}
	invQ_out = (~Q_out) & 0x01;
	
	return invQ_out;
}

/*******************************************************************************
* Function Name: IC74HC112_Initialize
* Description  : IC74HC112 Panel Initialize.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC112_Initialize( void )
{
	memset(g74HC112_LastQ, 0, (IC74HC112_USED / 8) + 1);
	memset(g74HC112_LastCK, 0, (IC74HC112_USED / 8) + 1);
}

/*******************************************************************************
* Function Name: IC74HC112_Counter_Clear
* Description  : IC74HC112 Panel Counter Clear.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC112_Counter_Clear( void )
{
	g74HC112_Count = 0;
}

/*******************************************************************************
* Function Name: IC74HC112_Counter
* Description  : IC74HC112 Panel Counter.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC112_Counter( void )
{
	g74HC112_Count ++;
}
#endif /* end of defined IC74HC112_USED */


#if defined IC74HC153_USED
/*******************************************************************************
* Function Name: IC_74HC153
* Description  : 4-Channel Multiplexer
* Arguments    : G_in	G-terminal input value (HIGH or LOW)
*                A_in	A-terminal input value (HIGH or LOW)
*                B_in 	B-terminal input value (HIGH or LOW)
*                C0_in 	C0-terminal input value (HIGH or LOW)
*                C1_in	C1-terminal input value (HIGH or LOW)
*                C2_in 	C2-terminal input value (HIGH or LOW)
*                C3_in 	C3-terminal input value (HIGH or LOW)
* Return Value : Y-terminal output value (HIGH or LOW)
********************************************************************************/
UCHAR  IC_74HC153( UCHAR G_in, UCHAR A_in, UCHAR B_in, UCHAR C0_in, UCHAR C1_in, UCHAR C2_in, UCHAR C3_in )
{
	UCHAR	Y_out;
	
	if(G_in == LOW){
		switch(A_in + (B_in << 1)){
			case 0:
				Y_out = C0_in;
				break;
			case 1:
				Y_out = C1_in;
				break;
			case 2:
				Y_out = C2_in;
				break;
			case 3:
				Y_out = C3_in;
				break;
		}
	}else{	/* G_in == HIGH */
		Y_out = LOW;
	}
	
	return Y_out;
}
#endif /* end of defined IC74HC153_USED */

#if defined IC74HC138_USED
/*******************************************************************************
* Function Name: IC_74HC138_Judge_Enable
* Description  : 3-to-8 Line Decoder
*                (enable or disable of operation is judged)
* Arguments    : G1_in	G1-terminal input value (HIGH or LOW)
*                G2A_in	G2A-terminal input value (HIGH or LOW)
*                G2B_in 	G2B-terminal input value (HIGH or LOW)
* Return Value : permission of operation (enable:HIGH  disable:LOW)
********************************************************************************/
UCHAR  IC_74HC138_Judge_Enable( UCHAR G1_in, UCHAR G2A_in, UCHAR G2B_in )
{
	UCHAR	state;
	UCHAR	work;
	
	if(G1_in == HIGH)
	{
		work = G2A_in | G2B_in;
		if(work == LOW)	state = HIGH;
		else			state = LOW;	/* work == HIGH */
	}
	else	/* G1_in == LOW */
	{
		state = LOW;
	}
	
	return (state);
}

/*******************************************************************************
* Function Name: IC_74HC138_Evaluate
* Description  : 3-to-8 Line Decoder
*                (address value calculate)
* Arguments    : A_in	A-terminal input value (HIGH or LOW)
*                B_in	B-terminal input value (HIGH or LOW)
*                C_in 	C-terminal input value (HIGH or LOW)
* Return Value : address value that input value indicates
********************************************************************************/
UCHAR  IC_74HC138_Evaluate( UCHAR G1_in, UCHAR G2A_in, UCHAR G2B_in, UCHAR A_in, UCHAR B_in, UCHAR C_in )
{
	UCHAR	ucRet = 0b11111111;

	UCHAR	ucEnable = LOW;
	
	if(G1_in == HIGH){
		if ((G2A_in | G2B_in)==0){
			ucRet = 0;
			switch(A_in + (B_in << 1) + (C_in << 2)){
			case 0: ucRet = 0b11111110; break;
			case 1: ucRet = 0b11111101; break;
			case 2: ucRet = 0b11111011; break;
			case 3: ucRet = 0b11110111; break;
			case 4: ucRet = 0b11101111; break;
			case 5: ucRet = 0b11011111; break;
			case 6: ucRet = 0b10111111; break;
			case 7: ucRet = 0b01111111; break;
			default:
					ucRet = 0b11111111;
			}
		}
	}	

	return ucRet;
}

/*******************************************************************************
* Function Name: IC_74HC138_Out_Y0
* Description  : 3-to-8 Line Decoder
*                (Y0-terminal output value calculate)
* Arguments    : State	permission of operation
*                Addr	address value
* Return Value : Y0-terminal output value
********************************************************************************/
UCHAR  IC_74HC138_Out_Y0( UCHAR State, UCHAR Addr )
{
	UCHAR	Y0_out;
	
	if(State == HIGH)
	{
		if(Addr == 0)	Y0_out = LOW;
		else			Y0_out = HIGH;	/* Addr != 0 */
	}
	else	/* State == LOW */
	{
		Y0_out = HIGH;
	}
	return(Y0_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC138_Out_Y1
* Description  : 3-to-8 Line Decoder
*                (Y1-terminal output value calculate)
* Arguments    : State	permission of operation
*                Addr	address value
* Return Value : Y1-terminal output value
********************************************************************************/
UCHAR  IC_74HC138_Out_Y1( UCHAR State, UCHAR Addr )
{
	UCHAR	Y1_out;
	
	if(State == HIGH)
	{
		if(Addr == 1)	Y1_out = LOW;
		else			Y1_out = HIGH;	/* Addr != 0 */
	}
	else	/* State == LOW */
	{
		Y1_out = HIGH;
	}
	return(Y1_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC138_Out_Y2
* Description  : 3-to-8 Line Decoder
*                (Y2-terminal output value calculate)
* Arguments    : State	permission of operation
*                Addr	address value
* Return Value : Y2-terminal output value
********************************************************************************/
UCHAR  IC_74HC138_Out_Y2( UCHAR State, UCHAR Addr )
{
	UCHAR	Y2_out;
	
	if(State == HIGH)
	{
		if(Addr == 2)	Y2_out = LOW;
		else			Y2_out = HIGH;	/* Addr != 0 */
	}
	else	/* State == LOW */
	{
		Y2_out = HIGH;
	}
	return(Y2_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC138_Out_Y3
* Description  : 3-to-8 Line Decoder
*                (Y3-terminal output value calculate)
* Arguments    : State	permission of operation
*                Addr	address value
* Return Value : Y3-terminal output value
********************************************************************************/
UCHAR  IC_74HC138_Out_Y3( UCHAR State, UCHAR Addr )
{
	UCHAR	Y3_out;
	
	if(State == HIGH)
	{
		if(Addr == 3)	Y3_out = LOW;
		else			Y3_out = HIGH;	/* Addr != 0 */
	}
	else	/* State == LOW */
	{
		Y3_out = HIGH;
	}
	return(Y3_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC138_Out_Y4
* Description  : 3-to-8 Line Decoder
*                (Y4-terminal output value calculate)
* Arguments    : State	permission of operation
*                Addr	address value
* Return Value : Y4-terminal output value
********************************************************************************/
UCHAR  IC_74HC138_Out_Y4( UCHAR State, UCHAR Addr )
{
	UCHAR	Y4_out;
	
	if(State == HIGH)
	{
		if(Addr == 4)	Y4_out = LOW;
		else			Y4_out = HIGH;	/* Addr != 0 */
	}
	else	/* State == LOW */
	{
		Y4_out = HIGH;
	}
	return(Y4_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC138_Out_Y5
* Description  : 3-to-8 Line Decoder
*                (Y5-terminal output value calculate)
* Arguments    : State	permission of operation
*                Addr	address value
* Return Value : Y5-terminal output value
********************************************************************************/
UCHAR  IC_74HC138_Out_Y5( UCHAR State, UCHAR Addr )
{
	UCHAR	Y5_out;
	
	if(State == HIGH)
	{
		if(Addr == 5)	Y5_out = LOW;
		else			Y5_out = HIGH;	/* Addr != 0 */
	}
	else	/* State == LOW */
	{
		Y5_out = HIGH;
	}
	return(Y5_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC138_Out_Y6
* Description  : 3-to-8 Line Decoder
*                (Y6-terminal output value calculate)
* Arguments    : State	permission of operation
*                Addr	address value
* Return Value : Y6-terminal output value
********************************************************************************/
UCHAR  IC_74HC138_Out_Y6( UCHAR State, UCHAR Addr )
{
	UCHAR	Y6_out;
	
	if(State == HIGH)
	{
		if(Addr == 6)	Y6_out = LOW;
		else			Y6_out = HIGH;	/* Addr != 0 */
	}
	else	/* State == LOW */
	{
		Y6_out = HIGH;
	}
	return(Y6_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC138_Out_Y7
* Description  : 3-to-8 Line Decoder
*                (Y7-terminal output value calculate)
* Arguments    : State	permission of operation
*                Addr	address value
* Return Value : Y7-terminal output value
********************************************************************************/
UCHAR  IC_74HC138_Out_Y7( UCHAR State, UCHAR Addr )
{
	UCHAR	Y7_out;
	
	if(State == HIGH)
	{
		if(Addr == 7)	Y7_out = LOW;
		else			Y7_out = HIGH;	/* Addr != 0 */
	}
	else	/* State == LOW */
	{
		Y7_out = HIGH;
	}
	return(Y7_out);
	
}
#endif /* end of defined IC74HC138_USED */

#if defined IC74HC148_USED
/*******************************************************************************
* Function Name: IC_74HC148_Evaluate
* Description  : 8-to-3 Line Priority Encoder
*                (address value calculate)
* Arguments    : In0_in	In0-terminal input value (HIGH or LOW)
*                In1_in	In1-terminal input value (HIGH or LOW)
*                In2_in 	In2-terminal input value (HIGH or LOW)
*                In3_in 	In3-terminal input value (HIGH or LOW)
*                In4_in	In4-terminal input value (HIGH or LOW)
*                In5_in 	In5-terminal input value (HIGH or LOW)
*                In6_in 	In6-terminal input value (HIGH or LOW)
*                In7_in 	In7-terminal input value (HIGH or LOW)
* Return Value : address value that input value indicates
*                (If all the input values are HIGH, 8 is returned)
********************************************************************************/
UCHAR  IC_74HC148_Evaluate( UCHAR E0_in, UCHAR In0_in, UCHAR In1_in, UCHAR In2_in, UCHAR In3_in, UCHAR In4_in, UCHAR In5_in, UCHAR In6_in, UCHAR In7_in )
{
	/*	E0,GS,A2,A1,A0 */
	UCHAR ucRet;
	
	if (E0_in==HIGH){
		ucRet = 0b00011111;
	}else{
		if(In7_in == LOW)		ucRet = 0b00010000;
		else if(In6_in == LOW)	ucRet = 0b00010001;
		else if(In5_in == LOW)	ucRet = 0b00010010;
		else if(In4_in == LOW)	ucRet = 0b00010011;
		else if(In3_in == LOW)	ucRet = 0b00010100;
		else if(In2_in == LOW)	ucRet = 0b00010101;
		else if(In1_in == LOW)	ucRet = 0b00010110;
		else if(In0_in == LOW)	ucRet = 0b00010111;
		else 					ucRet = 0b00001111;
	}

	return ucRet;

}

/*******************************************************************************
* Function Name: IC_74HC148_Out_A0
* Description  : 8-to-3 Line Priority Encoder
*                (A0-terminal output value calculate)
* Arguments    : E1_in	E1-terminal input value (HIGH or LOW)
*                Addr	address value
* Return Value : A0-terminal output value
********************************************************************************/
UCHAR  IC_74HC148_Out_A0( UCHAR E1_in, UCHAR Addr )
{
	UCHAR	A0_out;
	
	if(E1_in == LOW)
	{
		if(Addr == 8)	A0_out = HIGH;
		else			A0_out = (~Addr) & 0x01;	/* Addr != 8 */
	}
	else	/* E1_in == HIGH */
	{
		A0_out = HIGH;
	}
	return(A0_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC148_Out_A1
* Description  : 8-to-3 Line Priority Encoder
*                (A1-terminal output value calculate)
* Arguments    : E1_in	E1-terminal input value (HIGH or LOW)
*                Addr	address value
* Return Value : A1-terminal output value
********************************************************************************/
UCHAR  IC_74HC148_Out_A1( UCHAR E1_in, UCHAR Addr )
{
	UCHAR	A1_out;
	
	if(E1_in == LOW)
	{
		if(Addr == 8)	A1_out = HIGH;
		else			A1_out = ((~Addr) >> 1) & 0x01;	/* Addr != 8 */
	}
	else	/* E1_in == HIGH */
	{
		A1_out = HIGH;
	}
	return(A1_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC148_Out_A2
* Description  : 8-to-3 Line Priority Encoder
*                (A2-terminal output value calculate)
* Arguments    : E1_in	E1-terminal input value (HIGH or LOW)
*                Addr	address value
* Return Value : A2-terminal output value
********************************************************************************/
UCHAR  IC_74HC148_Out_A2( UCHAR E1_in, UCHAR Addr )
{
	UCHAR	A2_out;
	
	if(E1_in == LOW)
	{
		if(Addr == 8)	A2_out = HIGH;
		else			A2_out = ((~Addr) >> 2) & 0x01;	/* Addr != 8 */
	}
	else	/* E1_in == HIGH */
	{
		A2_out = HIGH;
	}
	return(A2_out);
	
}

/*******************************************************************************
* Function Name: IC_74HC148_Out_GS
* Description  : 8-to-3 Line Priority Encoder
*                (GS-terminal output value calculate)
* Arguments    : E1_in	E1-terminal input value (HIGH or LOW)
*                Addr	address value
* Return Value : GS-terminal output value
********************************************************************************/
UCHAR  IC_74HC148_Out_GS( UCHAR E1_in, UCHAR Addr )
{
	UCHAR	GS_out;
	
	if (E1_in == LOW){
		if(Addr == 8)	GS_out = HIGH;
		else			GS_out = LOW;	/* Addr != 8 */
	
	}else{	/* E1_in == HIGH */
		GS_out = HIGH;
	}
	return GS_out;
	
}

/*******************************************************************************
* Function Name: IC_74HC148_Out_EO
* Description  : 8-to-3 Line Priority Encoder
*                (EO-terminal output value calculate)
* Arguments    : E1_in	E1-terminal input value (HIGH or LOW)
*                Addr	address value
* Return Value : EO-terminal output value
********************************************************************************/
UCHAR  IC_74HC148_Out_EO( UCHAR E1_in, UCHAR Addr )
{
	UCHAR	EO_out;
	
	if (E1_in == LOW){
		if(Addr == 8)	EO_out = LOW;
		else			EO_out = HIGH;	/* Addr != 8 */
	
	}else{	/* E1_in == HIGH */
		EO_out = HIGH;
	}
	
	return EO_out;
	
}
#endif /* end of defined IC74HC148_USED */

#if defined IC74HC77_USED
/*******************************************************************************
* Function Name: IC_74HC77
* Description  : Bistable Latch
* Arguments    : D_in	D-terminal input value (HIGH or LOW)
*                G_in	G-terminal input value (HIGH or LOW)
* Return Value : Q-terminal output value (HIGH or LOW)
********************************************************************************/
UCHAR  IC_74HC77( UCHAR D_in, UCHAR G_in )
{
	UCHAR	Q_out;
	UCHAR	lastQ;
	
	lastQ = BitMemGet(g74HC77_LastQ, g74HC77_Count);
	
	if (G_in == HIGH)	Q_out = D_in;
	else				Q_out = lastQ;	/* G_in == LOW */

	BitMemSet(g74HC77_LastQ, g74HC77_Count, Q_out);
	
	return Q_out;
}

/*******************************************************************************
* Function Name: IC74HC77_Initialize
* Description  : IC74HC77 Panel Initialize.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC77_Initialize( void )
{
	memset(g74HC77_LastQ, 0, (IC74HC77_USED / 8) + 1);
}

/*******************************************************************************
* Function Name: IC74HC77_Counter_Clear
* Description  : IC74HC77 Panel Counter Clear.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC77_Counter_Clear( void )
{
	g74HC77_Count = 0;
}

/*******************************************************************************
* Function Name: IC74HC77_Counter
* Description  : IC74HC77 Panel Counter.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC77_Counter( void )
{
	g74HC77_Count ++;
}
#endif /* end of defined IC74HC77_USED */

#if defined IC74HC4511_USED
/*******************************************************************************
* Function Name: IC_74HC4511_Judge_State
* Description  : BCD-to-7-Segment Latch/Decoder/Driver
*                (state of operation of IC is judged)
* Arguments    : LE_in	LE-terminal input value (HIGH or LOW)
*                BI_in	BI-terminal input value (HIGH or LOW)
*                LT_in	LT-terminal input value (HIGH or LOW)
* Return Value : state of operation of IC	(0 - 3)
*                    0:Numeric Display
*                    1:All Lightning
*                    2:All Turning Off
*                    3:Display Continuance
********************************************************************************/
UCHAR  IC_74HC4511_Judge_State( UCHAR LE_in, UCHAR BI_in, UCHAR LT_in )
{
	UCHAR	state;

	if (LT_in == HIGH){
		if (BI_in == HIGH){
			if (LE_in == LOW)	state = 0;
			else				state = 3;	/* LE_in == HIGH */
		
		}else{	/* BI_in == LOW */
			state = 2;
		}
	}else{	/* LT_in == LOW */
		state = 1;
	}
	
	return state;
	
}

/*******************************************************************************
* Function Name: IC_74HC4511_Evaluate
* Description  : BCD-to-7-Segment Latch/Decoder/Driver
*                (numerical value that the input value shows is calculated )
* Arguments    : State	state of operation of IC (0 - 3)
*                A_in	A-terminal input value (HIGH or LOW)
*                B_in	B-terminal input value (HIGH or LOW)
*                C_in	C-terminal input value (HIGH or LOW)
*                D_in	D-terminal input value (HIGH or LOW)
* Return Value : Numerical value that input value shows	(0-10)
*                (Ten is set in case of ten or more)
********************************************************************************/
UCHAR  IC_74HC4511_Evaluate( UCHAR State, UCHAR A_in, UCHAR B_in, UCHAR C_in, UCHAR D_in )
{
	/*							   abcdefgh		*/
	UCHAR ucRet[11] =  { 0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110,
							     0b10110110, 0b00111110, 0b11100000, 0b11111110, 0b11100110, 0b00000000 };
	UCHAR	ucValue;
	
	switch(State)
	{
		case 0:
			ucValue = A_in + (B_in << 1) + (C_in << 2) + (D_in << 3);
			if(ucValue > 10) ucValue = 10;
			ByteMemSet(g74HC4511_LastNum, g74HC4511_Count, ucValue);
			break;
		case 1:
			ucValue = 8;
			break;
		case 2:
			ucValue = 10;
			break;
		case 3:
			ucValue = ByteMemGet(g74HC4511_LastNum, g74HC4511_Count);
			break;
		default:
			ucValue = 10;
			break;
	}
	
	if (ucValue > 10) ucValue = 10;
	return ucRet[ucValue];
}

/*******************************************************************************
* Function Name: IC74HC4511_Initialize
* Description  : IC74HC4511 Panel Initialize.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC4511_Initialize( void )
{
	memset(g74HC4511_LastNum, 0, IC74HC4511_USED);
}

/*******************************************************************************
* Function Name: IC74HC4511_Counter_Clear
* Description  : IC74HC4511 Panel Counter Clear.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC4511_Counter_Clear( void )
{
	g74HC4511_Count = 0;
}

/*******************************************************************************
* Function Name: IC74HC4511_Counter
* Description  : IC74HC4511 Panel Counter.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC4511_Counter( void )
{
	g74HC4511_Count ++;
}
#endif /* end of defined IC74HC4511_USED */

#if defined IC74HC166_USED
/*******************************************************************************
* Function Name: IC_74HC166_Judge_State
* Description  : 8-bit parallel-in / serial-out shift register
*                (state of operation of IC is judged)
* Arguments    : CLR_in		CLR-terminal input value (HIGH or LOW)
*                SL_in		SL-terminal input value (HIGH or LOW)
*                CK_INH_in	CKINH-terminal input value (HIGH or LOW)
*                CK_in		CK-terminal input value (HIGH or LOW)
* Return Value : state of operation of IC	(0 - 3)
*                    0:Clear
*                    1:Load
*                    2:Shift
*                    3:Continuance
********************************************************************************/
UCHAR  IC_74HC166_Judge_State( UCHAR CLR_in, UCHAR SL_in, UCHAR CK_INH_in, UCHAR CK_in )
{
	UCHAR	state;
	UCHAR	last_CK;

	if (CLR_in == HIGH){
		if (CK_INH_in == LOW){
			if (CK_in == HIGH){
				last_CK = BitMemGet(g74HC166_LastCK, g74HC166_Count);
				if (last_CK == LOW){
					if (SL_in == LOW)	state = 1;
					else				state = 2;	/* SL_in == HIGH */
				
				}else{	/* last_CK == HIGH	*/
					state = 3;
				}
			}else{	/* CK_in == LOW */
				state = 3;
			}
		}else{	/* CK_INH_in == HIGH */
			state = 3;
		}
	}else{	/* CLR_in == LOW */
		state = 0;
	}
	BitMemSet(g74HC166_LastCK, g74HC166_Count, CK_in);
	return state;
}

/*******************************************************************************
* Function Name: IC_74HC166_Out_QH
* Description  : 8-bit parallel-in / serial-out shift register
*                (QH-terminal output value calculate)
* Arguments    : State	State of operation of IC	(0 - 3)
*                S_IN_in	S_IN-terminal input value (HIGH or LOW)
*                A_in	A-terminal input value (HIGH or LOW)
*                B_in	B-terminal input value (HIGH or LOW)
*                C_in	C-terminal input value (HIGH or LOW)
*                D_in	D-terminal input value (HIGH or LOW)
*                E_in	E-terminal input value (HIGH or LOW)
*                F_in	F-terminal input value (HIGH or LOW)
*                G_in	G-terminal input value (HIGH or LOW)
*                H_in	H-terminal input value (HIGH or LOW)
* Return Value : QH-terminal output value (HIGH or LOW)
********************************************************************************/
UCHAR  IC_74HC166_Out_QH( UCHAR State, UCHAR S_IN_in, UCHAR A_in, UCHAR B_in, UCHAR C_in, UCHAR D_in, UCHAR E_in, UCHAR F_in, UCHAR G_in, UCHAR H_in )
{
	UCHAR	work;
	UCHAR	QH_out;
	
	switch(State)
	{
		case 0:
			work = 0b00000000;
			QH_out = LOW;
			ByteMemSet(g74HC166_LastValue, g74HC166_Count, work);
			break;
		case 1:
			work = A_in + (B_in << 1) + (C_in << 2) + (D_in << 3) + 
			        (E_in << 4) + (F_in << 5) + (G_in << 6) + (H_in << 7);
			QH_out = H_in;
			ByteMemSet(g74HC166_LastValue, g74HC166_Count, work);
			break;
		case 2:
			work = ByteMemGet(g74HC166_LastValue, g74HC166_Count);
			work <<= 1;
			QH_out = (work >> 7) & 0x01;
			work += S_IN_in;
			ByteMemSet(g74HC166_LastValue, g74HC166_Count, work);
			break;
		case 3	:
			work = ByteMemGet(g74HC166_LastValue, g74HC166_Count);
			QH_out = (work >> 7) & 0x01;
			break;
		default:
			break;
	}
	return QH_out;
}

/*******************************************************************************
* Function Name: IC74HC166_Initialize
* Description  : IC74HC166 Panel Initialize.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC166_Initialize( void )
{
	memset(g74HC166_LastCK, 0, (IC74HC166_USED / 8) + 1);
	memset(g74HC166_LastValue, 0, IC74HC166_USED);
}

/*******************************************************************************
* Function Name: IC74HC166_Counter_Clear
* Description  : IC74HC166 Panel Counter Clear.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC166_Counter_Clear( void )
{
	g74HC166_Count = 0;
}

/*******************************************************************************
* Function Name: IC74HC166_Counter
* Description  : IC74HC166 Panel Counter.
* Arguments    : none
* Return Value : none
********************************************************************************/
void IC74HC166_Counter( void )
{
	g74HC166_Count ++;
}
#endif /* end of defined IC74HC166_USED */

#if defined IC74HC283_USED
/*******************************************************************************
* Function Name: IC_74HC283_Evaluate
* Description  : 4-Bit Binary Full Adder
*                (sum total of two values of 4bit indicated by input value and C0_in is calculated)
* Arguments    : A1_in	A1-terminal input value (HIGH or LOW)
*                A2_in	A2_IN-terminal input value (HIGH or LOW)
*                A3_in	A3-terminal input value (HIGH or LOW)
*                A4_in	A4-terminal input value (HIGH or LOW)
*                B1_in	B1-terminal input value (HIGH or LOW)
*                B2_in	B2-terminal input value (HIGH or LOW)
*                B3_in	B3-terminal input value (HIGH or LOW)
*                B4_in	B4-terminal input value (HIGH or LOW)
*                C0_in	C0-terminal input value (HIGH or LOW)
* Return Value : sum total of two values of 4bit indicated by input value and C0_in
********************************************************************************/
UCHAR  IC_74HC283_Evaluate( UCHAR A1_in, UCHAR A2_in, UCHAR A3_in, UCHAR A4_in, UCHAR B1_in, UCHAR B2_in, UCHAR B3_in, UCHAR B4_in, UCHAR C0_in )
{
	UCHAR	work_a;
	UCHAR	work_b;
	UCHAR	work;

	work_a = A1_in + (A2_in << 1) + (A3_in << 2) + (A4_in << 3);
	work_b = B1_in + (B2_in << 1) + (B3_in << 2) + (B4_in << 3);
	work = work_a + work_b + C0_in;
	return (work);
}
#endif /* end of defined IC74HC283_USED */

#if defined IC74HC280_USED
/*******************************************************************************
* Function Name: IC_74HC280_Evaluate
* Description  : 9-Bit Parity Generator/Checker
*                (sum total in input terminal where input value is HIGH is calculated)
* Arguments    : A_in	A-terminal input value (HIGH or LOW)
*                B_in	B_IN-terminal input value (HIGH or LOW)
*                C_in	C-terminal input value (HIGH or LOW)
*                D_in	D-terminal input value (HIGH or LOW)
*                E_in	E-terminal input value (HIGH or LOW)
*                F_in	F-terminal input value (HIGH or LOW)
*                G_in	G-terminal input value (HIGH or LOW)
*                H_in	H-terminal input value (HIGH or LOW)
*                I_in	I-terminal input value (HIGH or LOW)
* Return Value : sum total in input terminal where input value is HIGH
********************************************************************************/
UCHAR  IC_74HC280_Evaluate( UCHAR A_in, UCHAR B_in, UCHAR C_in, UCHAR D_in, UCHAR E_in, UCHAR F_in, UCHAR G_in, UCHAR H_in, UCHAR I_in )
{
	UCHAR	ucCnt;

	ucCnt = A_in + B_in + C_in + D_in + E_in + F_in + G_in + H_in + I_in;
	return ucCnt;
}
#endif /* end of defined IC74HC280_USED */

