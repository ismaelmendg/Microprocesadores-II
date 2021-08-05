#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_adc16.h"
#include "fsl_tpm.h"
unsigned int  cont;

int main(void) {

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif
    EnableIRQ(PORTD_IRQn);
	adc16_config_t adc16ConfigStruct;//configurar el ADC
	adc16_channel_config_t adc16ChannelConfigStruct;//Configurar
	ADC16_GetDefaultConfig(&adc16ConfigStruct);//
	adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;//
	ADC16_Init(ADC0, &adc16ConfigStruct);//Inica el ADC0
	ADC16_EnableHardwareTrigger(ADC0, false);//
	ADC16_DoAutoCalibration(ADC0);//Funcion para calibrar el ADC
	adc16ChannelConfigStruct.channelNumber = 0;//Para escoger el canal
	adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
	adc16ChannelConfigStruct.enableDifferentialConversion = false;

	tpm_config_t tpmInfo1; //estructura inicial
	CLOCK_SetTpmClock(1U);
	TPM_GetDefaultConfig(&tpmInfo1);
	TPM_Init(TPM1, &tpmInfo1);
	TPM_SetTimerPeriod(TPM1, 21936);//desborde cada 457ms 21936
	TPM_EnableInterrupts(TPM1, kTPM_TimeOverflowInterruptEnable);
	EnableIRQ(TPM1_IRQn);
	TPM_StartTimer(TPM1, kTPM_SystemClock);
	int pot;

	while(1){
		GPIO_ClearPinsOutput(GPIOB, 0x100);
		ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct);//////////////ADC
		while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, 0))){}
		pot = ADC16_GetChannelConversionValue(ADC0, 0);//////////////////////////Pot*/

		if(pot >= 1000){
			if(cont >= 9000){
				cont=0;
				while(cont < 1000){
				GPIO_SetPinsOutput(GPIOB, 0x100);
				}
				GPIO_ClearPinsOutput(GPIOB, 0x100);
				cont=0;
		}}
	}

    return 0 ;
}

void TPM1_IRQHandler(void){
TPM_ClearStatusFlags(TPM1, kTPM_TimeOverflowFlag);
cont++;
}
/*
 * MATRICULA 4570543
 * 457 ms
 * 1/457m = 2.1881Hz
 * ¿A qué frecuencia se desborda el timmer?
(48,000,)/1000*457=21936Hz
	21936Hz
¿Qué numero seteó en el timmer para que se desbordara a la frecuencia indicada?
	9 y 1
Liga video: https://eduuag-my.sharepoint.com/:v:/g/personal/ismael_mendoza_edu_uag_mx/Eauo5PCQssFApROZwVRWNsUB_fE5PqsWVgBhHqs3fRc4VA?e=12YbIS
 *
 * */
