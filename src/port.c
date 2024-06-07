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
* File Name    : port.c
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
#include "port.h"

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

/*******************************************************************************
* Function Name: PORT_Init
* Description  : This function initializes the I/O port module.
* Arguments    : none
* Return Value : none
********************************************************************************/
void PORT_Init( void )
{
	/* Initialize the port output mode register 0 */
	POM0 = 0x00;
	POM2 = 0x00;
	POM3 = 0x00;
	POM4 = 0x00;
	POM5 = 0x00;
	/* Initialize the port registers */
	P0 = INIT_P0;
	P2 = INIT_P2;
	P3 = INIT_P3;
	P4 = INIT_P4;
	P5 = INIT_P5;

	/* Initialize the pull-up resistor option registers */
	PU0 = INIT_PU0;
	PU3 = INIT_PU3;
	PU4 = INIT_PU4;
	PU5 = INIT_PU5;
	PU12 = INIT_PU12;

	/* Initialize the mode registers */
	PM0 = INIT_PM0;
	PM2 = INIT_PM2;
	PM3 = INIT_PM3;
	PM4 = INIT_PM4;
	PM5 = INIT_PM5;

	/* Initialize the port mode control register 0 */
	PMC0 = INIT_PMC0;
	PMC2 = INIT_PMC2;
	PMC3 = INIT_PMC3;
	PMC5 = INIT_PMC5;
}
