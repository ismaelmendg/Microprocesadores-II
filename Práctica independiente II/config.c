#include "fsl_adc16.h"
#include "fsl_tpm.h"
void config(void){
	adc16_config_t adc16ConfigStruct;//configurar el ADC
		adc16_channel_config_t adc16ChannelConfigStruct;//Configurar
		ADC16_GetDefaultConfig(&adc16ConfigStruct);//
		adc16ConfigStruct.resolution = kADC16_ResolutionSE16Bit;//
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
		TPM_SetTimerPeriod(TPM1, 48000);
		TPM_EnableInterrupts(TPM1, kTPM_TimeOverflowInterruptEnable);
		EnableIRQ(TPM1_IRQn);
		TPM_StartTimer(TPM1, kTPM_SystemClock);

		tpm_config_t tpmInfo; //estructura inicial
		CLOCK_SetTpmClock(1U);
		TPM_GetDefaultConfig(&tpmInfo);
		TPM_Init(TPM2, &tpmInfo);
		TPM_SetTimerPeriod(TPM2, 480);//480
		TPM_EnableInterrupts(TPM2, kTPM_TimeOverflowInterruptEnable);
		EnableIRQ(TPM2_IRQn);
		TPM_StartTimer(TPM2, kTPM_SystemClock);
}
