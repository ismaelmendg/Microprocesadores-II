#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_tpm.h"
unsigned int counter_u, counter_d;

int main(void) {

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif
    tpm_config_t tpmInfo; //estructura inicial
    CLOCK_SetTpmClock(1U);
    TPM_GetDefaultConfig(&tpmInfo);
    TPM_Init(TPM2, &tpmInfo);
    TPM_SetTimerPeriod(TPM2, 480);
    TPM_EnableInterrupts(TPM2, kTPM_TimeOverflowInterruptEnable);
    EnableIRQ(TPM2_IRQn);
    TPM_StartTimer(TPM2, kTPM_SystemClock);
    ////////////
    tpm_config_t tpmInfo_u; //estructura inicial
    CLOCK_SetTpmClock(1U);
    TPM_GetDefaultConfig(&tpmInfo_u);
    TPM_Init(TPM1, &tpmInfo_u);
    TPM_SetTimerPeriod(TPM1, 48000);
    TPM_EnableInterrupts(TPM1, kTPM_TimeOverflowInterruptEnable);
    EnableIRQ(TPM1_IRQn);
    TPM_StartTimer(TPM1, kTPM_SystemClock);

while(1){

	if(counter_u == 2){
		GPIO_TogglePinsOutput(GPIOE, 0x400000);
			counter_u = 0;
	}
	if(counter_d == 5000){
		GPIO_TogglePinsOutput(GPIOB, 0x1);
			counter_d = 0;
}
}
    return 0 ;
}

void TPM2_IRQHandler(void){
	TPM_ClearStatusFlags(TPM2, kTPM_TimeOverflowFlag);
	counter_u++;
}

void TPM1_IRQHandler(void){
	TPM_ClearStatusFlags(TPM1, kTPM_TimeOverflowFlag);
	counter_d++;
}
