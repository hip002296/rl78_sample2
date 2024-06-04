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
* File Name    : 74hc.h
* Version      : Applilet EZ PL for RL78
* Device(s)    : R5F1056A,R5F1057A,R5F1058A
* Tool-Chain   : CC-RL
* Description  : This file implements main function.
* Creation Date: 2016/09/14
*******************************************************************************/

#ifndef _74HC_H_
#define _74HC_H_
/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/

/*******************************************************************************
Macro definitions
*******************************************************************************/
/*******************************************************************************
** 74HC4075	
********************************************************************************/
#define	IC74HC4075_PROC(A_in, B_in, C_in, Y_out)								\
{																				\
			Y_out =  A_in | B_in | C_in;										\
}

/*******************************************************************************
** 74HC4072	
********************************************************************************/
#define	IC74HC4072_PROC(A_in, B_in, C_in, D_in, Y_out)							\
{																				\
			Y_out = A_in | B_in | C_in | D_in;									\
}

/*******************************************************************************
** 74HC11	
********************************************************************************/
#define	IC74HC11_PROC(A_in, B_in, C_in, Y_out)									\
{																				\
			Y_out =  A_in & B_in & C_in;										\
}

/*******************************************************************************
** 74HC21	
********************************************************************************/
#define	IC74HC21_PROC(A_in, B_in, C_in, D_in, Y_out)							\
{																				\
			Y_out = A_in & B_in & C_in & D_in;									\
}

/*******************************************************************************
** 74HC02	
********************************************************************************/
#define	IC74HC02_PROC(A_in, B_in, Y_out)										\
{																				\
			Y_out =  (~(A_in | B_in)) & 0x01;									\
}

/*******************************************************************************
** 74HC27	
********************************************************************************/
#define	IC74HC27_PROC(A_in, B_in, C_in, Y_out)									\
{																				\
			Y_out = A_in | B_in | C_in;											\
			Y_out = (~Y_out) & 0x01;											\
}

/*******************************************************************************
** 74HC4002	
********************************************************************************/
#define	IC74HC4002_PROC(A_in, B_in, C_in, D_in, Y_out)							\
{																				\
			Y_out = A_in | B_in | C_in | D_in;									\
			Y_out = (~Y_out) & 0x01;											\
}

/*******************************************************************************
** 74HC00	
********************************************************************************/
#define	IC74HC00_PROC(A_in, B_in, Y_out)										\
{																				\
			Y_out = A_in & B_in;												\
			Y_out = (~Y_out) & 0x01;											\
}

/*******************************************************************************
** 74HC10	
********************************************************************************/
#define	IC74HC10_PROC(A_in, B_in, C_in, Y_out)									\
{																				\
			Y_out = A_in & B_in & C_in;											\
			Y_out = (~Y_out) & 0x01;											\
}

/*******************************************************************************
** 74HC20	
********************************************************************************/
#define	IC74HC20_PROC(A_in, B_in, C_in, D_in, Y_out)							\
{																				\
			Y_out = A_in & B_in & C_in & D_in;									\
			Y_out = (~Y_out) & 0x01;											\
}

/*******************************************************************************
** 74HC30	
********************************************************************************/
#define	IC74HC30_PROC(A_in, B_in, C_in, D_in, E_in, F_in, G_in, H_in, Y_out)	\
{																				\
			Y_out = A_in & B_in & C_in & D_in & E_in & F_in & G_in & H_in;		\
			Y_out = (~Y_out) & 0x01;											\
}

/*******************************************************************************
** 74HC133	
********************************************************************************/
#define	IC74HC133_PROC(A_in, B_in, C_in, D_in, E_in, F_in, G_in, H_in, 			\
										I_in, J_in, K_in, L_in, M_in, Y_out)	\
{																				\
			Y_out = A_in & B_in & C_in & D_in & E_in & F_in & G_in & H_in & I_in & J_in & K_in & L_in & M_in;	\
			Y_out = (~Y_out) & 0x01;											\
}

/*******************************************************************************
** 74HC7266	
********************************************************************************/
#define	IC74HC7266_PROC(A_in, B_in, Y_out)										\
{																				\
			if(A_in == B_in) Y_out = HIGH;										\
			else			 Y_out = LOW;										\
}

/*******************************************************************************
** 74HC4078	
********************************************************************************/
#define	IC74HC4078_PROC(A_in, B_in, C_in, D_in, E_in, F_in, G_in, H_in, X_out, Y_out)	\
{																						\
			Y_out = A_in | B_in | C_in | D_in | E_in | F_in | G_in | H_in;				\
			X_out = (~Y_out) & 0x01;													\
}

/*******************************************************************************
** 74HC51	
********************************************************************************/
#define	IC74HC51_PROC(A1_in, B1_in, C1_in, D1_in, E1_in, F1_in, 				\
								A2_in, B2_in, C2_in, D2_in,	Y1_out, Y2_out)		\
{																				\
	Y1_out = (A1_in & B1_in & C1_in) | (D1_in & E1_in & F1_in);					\
	Y1_out = (~Y1_out) & 0x01;													\
	Y2_out = (A2_in & B2_in ) | (C2_in & D2_in);								\
	Y2_out = (~Y2_out) & 0x01;													\
}

/*******************************************************************************
** 74HC112	
********************************************************************************/
#define	IC74HC112_INIT0															\
{																				\
			IC74HC112_Initialize();												\
}

#define	IC74HC112_INIT															\
{																				\
			IC74HC112_Counter_Clear();											\
}

#define	IC74HC112_PROC(CLR_in, PR_in, J_in, K_in, CK_in, Q_out, invQ_out)		\
{																				\
			Q_out = IC_74HC112_Out_Q(J_in, K_in, CLR_in, PR_in, CK_in);			\
			invQ_out = IC_74HC112_Out_invQ(Q_out, CLR_in, PR_in);				\
			IC74HC112_Counter();												\
}

/*******************************************************************************
** 74HC153	
********************************************************************************/
#define	IC74HC153_PROC(G_in, A_in, B_in, C0_in, C1_in, C2_in, C3_in, Y_out)		\
{																				\
			Y_out = IC_74HC153(G_in, A_in, B_in, C0_in, C1_in, C2_in, C3_in);	\
}

/*******************************************************************************
** 74HC138	
********************************************************************************/
#define	IC74HC138_PROC(G1_in, G2A_in, G2B_in, A_in, B_in, C_in, 				\
				Y0_out, Y1_out, Y2_out, Y3_out, Y4_out, Y5_out, Y6_out, Y7_out)	\
{																				\
	{																			\
			UCHAR	ucVal;														\
																				\
			ucVal  = IC_74HC138_Evaluate(G1_in, G2A_in, G2B_in,A_in, B_in, C_in);		\
			Y0_out = ucVal & 0x01;												\
			Y1_out = (ucVal>>1) & 0x01;											\
			Y2_out = (ucVal>>2) & 0x01;											\
			Y3_out = (ucVal>>3) & 0x01;											\
			Y4_out = (ucVal>>4) & 0x01;											\
			Y5_out = (ucVal>>5) & 0x01;											\
			Y6_out = (ucVal>>6) & 0x01;											\
			Y7_out = (ucVal>>7) & 0x01;											\
	}																			\
}

/*******************************************************************************
** 74HC148	
********************************************************************************/
#define	IC74HC148_PROC(E0_in, In0_in, In1_in, In2_in, In3_in, In4_in, In5_in,	\
						In6_in, In7_in, A0_out, A1_out, A2_out, GS_out, EO_out)	\
{																				\
	{																			\
			UCHAR	ucVal;														\
																				\
			ucVal = IC_74HC148_Evaluate(E0_in,In0_in, In1_in, In2_in, In3_in, In4_in,	\
													In5_in, In6_in, In7_in);			\
			A0_out = ucVal & 0x01;												\
			A1_out = (ucVal>>1) & 0x01;											\
			A2_out = (ucVal>>2) & 0x01;											\
			GS_out = (ucVal>>3) & 0x01;											\
			EO_out = (ucVal>>4) & 0x01;											\
	}																			\
}

/*******************************************************************************
** 74HC77	
********************************************************************************/
#define	IC74HC77_INIT0															\
{																				\
			IC74HC77_Initialize();												\
}

#define	IC74HC77_INIT															\
{																				\
			IC74HC77_Counter_Clear();											\
}

#define	IC74HC77_PROC(D_in, G_in, Q_out)										\
{																				\
			Q_out = IC_74HC77(D_in, G_in);										\
			IC74HC77_Counter();													\
}


/*******************************************************************************
** 74HC4511	
********************************************************************************/
#define	IC74HC4511_INIT0														\
{																				\
			IC74HC4511_Initialize();											\
}

#define	IC74HC4511_INIT															\
{																				\
			IC74HC4511_Counter_Clear();											\
}

#define	IC74HC4511_PROC(LE_in, BI_in, LT_in, A_in, B_in, C_in, D_in,			\
							a_out, b_out, c_out, d_out, e_out, f_out, g_out)	\
{																				\
	{																			\
			UCHAR	State;														\
			UCHAR	ucSeg;														\
																				\
			State = IC_74HC4511_Judge_State(LE_in, BI_in, LT_in);				\
			ucSeg = IC_74HC4511_Evaluate(State, A_in, B_in, C_in, D_in);		\
			a_out = (ucSeg>>7) & 0x01;											\
			b_out = (ucSeg>>6) & 0x01;											\
			c_out = (ucSeg>>5) & 0x01;											\
			d_out = (ucSeg>>4) & 0x01;											\
			e_out = (ucSeg>>3) & 0x01;											\
			f_out = (ucSeg>>2) & 0x01;											\
			g_out = (ucSeg>>1) & 0x01;											\
			IC74HC4511_Counter();												\
	}																			\
}

/*******************************************************************************
** 74HC166	
********************************************************************************/
#define	IC74HC166_INIT0															\
{																				\
			IC74HC166_Initialize();												\
}

#define	IC74HC166_INIT															\
{																				\
			IC74HC166_Counter_Clear();											\
}

#define	IC74HC166_PROC(CLR_in, SL_in, CK_INH_in, CK_in, S_IN_in, 				\
						A_in, B_in, C_in, D_in,	E_in, F_in, G_in, H_in, QH_out)	\
{																				\
	{																			\
			UCHAR	State;														\
																				\
			State = IC_74HC166_Judge_State(CLR_in, SL_in, CK_INH_in, CK_in);	\
			QH_out = IC_74HC166_Out_QH(State, S_IN_in, A_in, B_in, C_in, D_in,	\
														E_in, F_in, G_in, H_in);\
			IC74HC166_Counter();												\
	}																			\
}

/*******************************************************************************
** 74HC283	
********************************************************************************/
#define	IC74HC283_PROC(A1_in, A2_in, A3_in, A4_in, B1_in, B2_in, B3_in, B4_in,	\
								C0_in, Q1_out, Q2_out, Q3_out, Q4_out, C4_out)	\
{																				\
	{																			\
			UCHAR	Num;														\
																				\
			Num = IC_74HC283_Evaluate(A1_in, A2_in, A3_in, A4_in, B1_in, B2_in, \
														  B3_in, B4_in, C0_in);	\
			Q1_out = Num & 0x01;												\
			Q2_out = (Num >> 1) & 0x01;											\
			Q3_out = (Num >> 2) & 0x01;											\
			Q4_out = (Num >> 3) & 0x01;											\
			C4_out = (Num >> 4) & 0x01;											\
	}																			\
}

/*******************************************************************************
** 74HC280	
********************************************************************************/
#define	IC74HC280_PROC(A_in, B_in, C_in, D_in, E_in, F_in, G_in, H_in, I_in, 	\
															EVEN_out, ODD_out)	\
{																				\
	{																			\
			UCHAR	ucCnt;														\
																				\
			ucCnt = IC_74HC280_Evaluate(A_in, B_in, C_in, D_in, E_in, F_in, G_in,H_in, I_in);	\
			EVEN_out = (ucCnt + 1) & 0x01;										\
			ODD_out  = ucCnt%2;													\
	}																			\
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
UCHAR	IC_74HC21( UCHAR A_in, UCHAR B_in, UCHAR C_in, UCHAR D_in );
UCHAR	IC_74HC02( UCHAR  A_in, UCHAR  B_in );
UCHAR	IC_74HC112_Out_Q( UCHAR J_in, UCHAR K_in, UCHAR CLR_in, UCHAR PR_in, UCHAR CK_in );
UCHAR	IC_74HC112_Out_invQ( UCHAR Q_out, UCHAR CLR_in, UCHAR PR_in );
void	IC74HC112_Initialize( void );
void	IC74HC112_Counter_Clear( void );
void	IC74HC112_Counter( void );
UCHAR	IC_74HC153( UCHAR G_in, UCHAR A_in, UCHAR B_in, UCHAR C0_in, UCHAR C1_in, UCHAR C2_in, UCHAR C3_in );
UCHAR	IC_74HC138_Evaluate( UCHAR G1_in, UCHAR G2A_in, UCHAR G2B_in, UCHAR A_in, UCHAR B_in, UCHAR C_in );
UCHAR	IC_74HC148_Evaluate( UCHAR E0_in, UCHAR In0_in, UCHAR In1_in, UCHAR In2_in, UCHAR In3_in, UCHAR In4_in, UCHAR In5_in, UCHAR In6_in, UCHAR In7_in );
UCHAR	IC_74HC148_Out_A0( UCHAR E1_in, UCHAR Addr );
UCHAR	IC_74HC148_Out_A1( UCHAR E1_in, UCHAR Addr );
UCHAR	IC_74HC148_Out_A2( UCHAR E1_in, UCHAR Addr );
UCHAR	IC_74HC148_Out_GS( UCHAR E1_in, UCHAR Addr );
UCHAR	IC_74HC148_Out_EO( UCHAR E1_in, UCHAR Addr );
UCHAR	IC_74HC77( UCHAR D_in, UCHAR G_in);
void	IC74HC77_Initialize( void );
void	IC74HC77_Counter_Clear( void );
void	IC74HC77_Counter( void );
UCHAR	IC_74HC4511_Judge_State( UCHAR LE_in, UCHAR BI_in, UCHAR LT_in );
UCHAR	IC_74HC4511_Evaluate( UCHAR State, UCHAR A_in, UCHAR B_in, UCHAR C_in, UCHAR D_in );
void	IC74HC4511_Initialize( void );
void	IC74HC4511_Counter_Clear( void );
void	IC74HC4511_Counter( void );
UCHAR	IC_74HC166_Judge_State( UCHAR CLR_in, UCHAR SL_in, UCHAR CK_INH_in, UCHAR CK_in );
UCHAR	IC_74HC166_Out_QH( UCHAR State, UCHAR S_IN_in, UCHAR A_in, UCHAR B_in,  UCHAR C_in, UCHAR D_in, UCHAR E_in, UCHAR F_in, UCHAR G_in, UCHAR H_in );
void	IC74HC166_Initialize( void );
void	IC74HC166_Counter_Clear( void );
void	IC74HC166_Counter( void );
UCHAR	IC_74HC283_Evaluate( UCHAR A1_in, UCHAR A2_in, UCHAR A3_in, UCHAR A4_in, UCHAR B1_in, UCHAR B2_in, UCHAR B3_in, UCHAR B4_in, UCHAR C0_in );
UCHAR	IC_74HC280_Evaluate( UCHAR A_in, UCHAR B_in, UCHAR C_in, UCHAR D_in, UCHAR E_in, UCHAR F_in, UCHAR G_in, UCHAR H_in, UCHAR I_in );

#endif /* _74HC_H_ */
