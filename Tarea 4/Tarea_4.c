#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "PWM.h"
#include "fsl_tpm.h"

char lec1, lec2, lec3, lec4, boton;
//B0 ,1, 2 E20lectura,--- B3, C2,c1 E21escritura
void delay(){

	int x = 0xFFFFF;
	while(x>0){
		x--;
	}
}
char teclado(void){


	GPIO_ClearPinsOutput(GPIOB, 0x8);
	GPIO_SetPinsOutput(GPIOC, 0x2);
	GPIO_SetPinsOutput(GPIOC, 0x4);

	lec1 = GPIO_ReadPinInput(GPIOB, 0);
	lec2 = GPIO_ReadPinInput(GPIOB, 1);
	lec3 = GPIO_ReadPinInput(GPIOB, 2);

	if(lec1 == 0){
		return 1;
	}
	if(lec2 == 0){
		return 2;
	}
	if(lec3 == 0){
		return 3;
	}

	GPIO_SetPinsOutput(GPIOB, 0x8);
	GPIO_ClearPinsOutput(GPIOC, 0x2);
	GPIO_SetPinsOutput(GPIOC, 0x4);

	lec1 = GPIO_ReadPinInput(GPIOB, 0);
	lec2 = GPIO_ReadPinInput(GPIOB, 1);
	lec3 = GPIO_ReadPinInput(GPIOB, 2);

	if(lec1 == 0){
		return 4;
	}
	if(lec2 == 0){
		return 5;
	}
	if(lec3 == 0){
		return 6;
	}

	GPIO_SetPinsOutput(GPIOB, 0x8);
	GPIO_SetPinsOutput(GPIOC, 0x2);
	GPIO_ClearPinsOutput(GPIOC, 0x4);

	lec1 = GPIO_ReadPinInput(GPIOB, 0);
	lec2 = GPIO_ReadPinInput(GPIOB, 1);
	lec3 = GPIO_ReadPinInput(GPIOB, 2);

	if(lec1 == 0){
		return 7;
	}
	if(lec2 == 0){
		return 8;
	}
	if(lec3 == 0){
		return 9;
	}

	GPIO_ClearPinsOutput(GPIOC, 0x400000);
	lec4 = GPIO_ReadPinInput(GPIOE, 20);
	if(lec4 == 0){
		return 0;
	}
	return 10;
}

int main(void) {

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();
    ////////////////B18, B19, D1
    tpm_config_t tpmInfo;
    tpm_chnl_pwm_signal_param_t tpmParam[3];
    tpmParam[0].chnlNumber = (tpm_chnl_t)0u;
	tpmParam[0].level = kTPM_LowTrue;
	tpmParam[0].dutyCyclePercent = 0;
	tpmParam[1].chnlNumber = (tpm_chnl_t)1u;
	tpmParam[1].level = kTPM_LowTrue;
	tpmParam[1].dutyCyclePercent = 0;
	tpmParam[2].chnlNumber = (tpm_chnl_t)1u;
	tpmParam[2].level = kTPM_LowTrue;
	tpmParam[2].dutyCyclePercent = 0;
	CLOCK_SetTpmClock(1U);
	TPM_GetDefaultConfig(&tpmInfo);
	TPM_Init(TPM2, &tpmInfo);
	TPM_Init(TPM0, &tpmInfo);

	TPM_SetupPwm(TPM2, &tpmParam[0], 1U, kTPM_EdgeAlignedPwm, 24000U, CLOCK_GetFreq(kCLOCK_PllFllSelClk));
	TPM_SetupPwm(TPM2, &tpmParam[1], 1U, kTPM_EdgeAlignedPwm, 24000U, CLOCK_GetFreq(kCLOCK_PllFllSelClk));
	TPM_SetupPwm(TPM0, &tpmParam[2], 1U, kTPM_EdgeAlignedPwm, 24000U, CLOCK_GetFreq(kCLOCK_PllFllSelClk));
	TPM_StartTimer(TPM2, kTPM_SystemClock);
	TPM_StartTimer(TPM0, kTPM_SystemClock);
	volatile static int i_u, i_d, i_t, i;


//////////////////
    	while(1){
    	for(i = 1; i < 4; i++){//i_u
    		//boton = 10;
    		delay();
    		do{
    			boton = teclado();
    		}while(boton == 10);
    		if(i == 1){
    			i_u = boton * 100;
    		}if(i == 2){
    			i_u = i_u + (boton * 10);
    		}if(i == 3){
    			i_u = i_u + boton;
    		}
    	}
/////////////////
//////////////////
		for(i = 1; i < 4; i++){//i_u
    		delay();
			do{
				boton = teclado();
    		}while(boton == 10);
			if(i == 1){
				i_d = boton * 100;
			}if(i == 2){
				i_d = i_d + (boton * 10);
			}if(i == 3){
				i_d = i_d + boton;
			}
		}
/////////////////
//////////////////
		for(i = 1; i < 4; i++){//i_u
    		delay();
			do{
				boton = teclado();
    		}while(boton ==  10);
			if(i == 1){
				i_t = boton * 100;
			}if(i == 2){
				i_t = i_t + (boton * 10);
			}if(i == 3){
				i_t = i_t + boton;
			}
		}
    	break;}
/////////////////
while(1){
		TPM_PWM(TPM2, (tpm_chnl_t)0u, kTPM_EdgeAlignedPwm, i_u);//Rojo
		TPM_PWM(TPM2, (tpm_chnl_t)1u, kTPM_EdgeAlignedPwm, i_d);//Verde
		TPM_PWM(TPM0, (tpm_chnl_t)1u, kTPM_EdgeAlignedPwm, i_t);//Azul
    }
    return 0 ;
}
