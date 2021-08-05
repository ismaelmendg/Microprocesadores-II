#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_adc16.h"

void delay(void){

	int x = 0xFFFF;
	while(x > 0){
		x--;
}}

int main(void) {

	adc16_config_t adc16ConfigStruct;//configurar el ADC
	adc16_channel_config_t adc16ChannelConfigStruct[2];//Configurar canal ADDC;
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif
    ADC16_GetDefaultConfig(&adc16ConfigStruct);//
    adc16ConfigStruct.resolution = kADC16_ResolutionSE16Bit;//Cambiar valor del bit
    ADC16_Init(ADC0, &adc16ConfigStruct);//Inica el ADC0
    ADC16_EnableHardwareTrigger(ADC0, false);//
    ADC16_DoAutoCalibration(ADC0);//Funcion para calibrar el ADC
    adc16ChannelConfigStruct[0].channelNumber = 0;//Para escoger el canal
    adc16ChannelConfigStruct[0].enableInterruptOnConversionCompleted = false;
    adc16ChannelConfigStruct[0].enableDifferentialConversion = false;
    adc16ChannelConfigStruct[1].channelNumber = 3;//Para escoger el canal
  	adc16ChannelConfigStruct[1].enableInterruptOnConversionCompleted = false;
  	adc16ChannelConfigStruct[1].enableDifferentialConversion = false;
  	int canal_u, canal_d, variable;

  while(1){

	delay();
	//////////////////////////////////////////////////////////////////////////////////////////////ADC Pot y Diodos
	ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct[0]);//Canal a leer
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, 0))){}
	canal_u = ADC16_GetChannelConversionValue(ADC0, 0);//Pot

	ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct[1]);//Canal a leer
	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, 0))){}
	canal_d = ADC16_GetChannelConversionValue(ADC0, 0);//Infrarrojo y fototransistor

/////////////////////////////////////////////////////////////////////////////////////////////Función

	variable = 4000 + (canal_u * 0.6875);//Ecuación

    if(canal_d > 35000){//Rango 35,000 a 48,000
    	if(canal_d < (variable + 4000) && canal_d > (variable - 4000)){
			GPIO_SetPinsOutput(GPIOB, 0x100);
		}else{
			GPIO_ClearPinsOutput(GPIOB, 0x100);
			}}

    if(canal_d < 34999 && canal_d > 7500){//Rango 7,500 a 35,000
    	if(canal_d < (variable + 2000) && canal_d > (variable - 2000)){
			GPIO_SetPinsOutput(GPIOB, 0x100);
		}else{
			GPIO_ClearPinsOutput(GPIOB, 0x100);
			}}
    if(canal_d < 7499 && canal_d > 0){//Rango 0 a 7,500
    	if(canal_d < (variable + 900) && canal_d > (variable - 900)){
			GPIO_SetPinsOutput(GPIOB, 0x100);
		}else{
			GPIO_ClearPinsOutput(GPIOB, 0x100);
			}}
////////////////////////////////////////////////////////////////////////////////////////////
  printf("POT: %5d   InfraFoto: %5d\r\n", canal_u, canal_d);
}}
/*
 Ecuación:
 PotMax = 64,000 PotMin = 800
 InfraFotoMax = 48,000 - InfraFotoMin = 4000
 (InfraFotoMin) + (PotMax * x) = InfraFotoMax
 Despeje
 4000 + (64,000 * x) = 48,000
 64,000x = 44,000
 x = 0.6875
 Comprobando con el numero más pequeño
 4000 + (800(PotMin)*0.6875) = 4550(InfraFotoMin - Más cercano)
 */
