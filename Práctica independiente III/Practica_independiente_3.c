#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "fsl_adc16.h"
#include "fsl_tpm.h"
#include "carlet.h"
#include "dutycycle.h"
int var_b,var_d, counter_u,velocidad, pwm=0, var;

uint8_t g_master_buff[2U];
i2c_master_config_t masterConfig;
i2c_master_transfer_t masterXfer;

unsigned char LCD_screen_buffer[1024];
char LCD_line1[18];
char LCD_line2[18];
char LCD_line3[18];
char LCD_line4[18];

void delay(void)
{
	int x = 0x7FFFFF;
	while(x > 0){
	x--;
}}
void LCD_send_Command(unsigned char* commands,unsigned int command_length )
{
	g_master_buff[0] = 0x00;
	for (int x=0; x<command_length; x++)
	{
		g_master_buff[1] = commands[x];
		masterXfer.data = g_master_buff;
		I2C_MasterTransferBlocking(I2C0, &masterXfer);
	}

	return;
}
void LCD_send_Data(unsigned char* data_, unsigned int data_lenght)
{
	g_master_buff[0] = 0x40;
	for (int x=0; x<data_lenght; x++)
	{
		g_master_buff[1] = data_[x];
		masterXfer.data = g_master_buff;
		I2C_MasterTransferBlocking(I2C0, &masterXfer);
	}
	return;
}

void LCD_init()
{

	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress = 0x3CU;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = 0;
	masterXfer.subaddressSize = 0;
	masterXfer.dataSize = 2U;
	masterXfer.flags = kI2C_TransferDefaultFlag;

	unsigned char init_sequence[27]={0xAE,0xD5,0x80,0xA8,63,0xD3,0x00,0x40,0x8D,
			0xD5,0x14,0x20,0x00,0xA1,0xC8,0xDA,0x12,0x81,0xCF,0xD9,0xF1,  0xDB,0x40,
			0xA4,0xA6,0x2E,0xAF};
	LCD_send_Command(init_sequence,27);
}

void LCD_print()
{

	unsigned char start_screen[6]={0x22,0x00,0xFF,0x21,0x00,127};
	LCD_send_Command(start_screen,6);

	LCD_send_Data(LCD_screen_buffer,1024);

}

void LCD_print_text()
{
	char buffer_letra[8];
	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line1[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[129+ (7*y) +z] = buffer_letra[0+z];
		}
	}

	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line2[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[385+ (7*y) +z] = buffer_letra[0+z];
		}
	}
	//////////
	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line3[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[641+ (7*y) +z] = buffer_letra[0+z];
		}
	}
	////////////
	for(int y=0; y<18 ;y++)
	{
		LCD_parse(buffer_letra, LCD_line4[y]);
		for(int z=0; z<7 ;z++)
		{
			LCD_screen_buffer[897+ (7*y) +z] = buffer_letra[0+z];
		}
	}
	LCD_print();
}

void LCD_clear()
{
	memset(&LCD_screen_buffer, 0, 1024);
	LCD_print();
}


void PORTD_IRQHandler(void){

	uint32_t boton = 0;
	boton = GPIO_GetPinsInterruptFlags(GPIOD);
		if(boton == 0x1){
			var_b = 1;
		}

		if(boton == 0x20){
		var_d = 1;
		}
	GPIO_ClearPinsInterruptFlags(GPIOD, (1U << 0));
	GPIO_ClearPinsInterruptFlags(GPIOD, (1U << 5));
}
void PORTA_IRQHandler(void){
	velocidad++;
	GPIO_ClearPinsInterruptFlags(GPIOA, (1U << 16));
}

void TPM2_IRQHandler(void){///////50us -  1500
TPM_ClearStatusFlags(TPM2, kTPM_TimeOverflowFlag);
counter_u++;
}


int main(void) {

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();
    ///////////////
    adc16_config_t adc16ConfigStruct;//configurar el ADC
    adc16_channel_config_t adc16ChannelConfigStruct;//Configurar
    ADC16_GetDefaultConfig(&adc16ConfigStruct);//
    adc16ConfigStruct.resolution = kADC16_ResolutionSE16Bit;//Cambiar valor del bit
    ADC16_Init(ADC0, &adc16ConfigStruct);//Inica el ADC0
    ADC16_EnableHardwareTrigger(ADC0, false);//
    ADC16_DoAutoCalibration(ADC0);//Funcion para calibrar el ADC
    adc16ChannelConfigStruct.channelNumber = 9;//Para escoger el canal
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
    adc16ChannelConfigStruct.enableDifferentialConversion = false;
    ///////////
    EnableIRQ(PORTD_IRQn);
    EnableIRQ(PORTA_IRQn);
    //////////
    tpm_config_t tpmInfo; //estructura inicial
    CLOCK_SetTpmClock(1U);
    TPM_GetDefaultConfig(&tpmInfo);
    TPM_Init(TPM2, &tpmInfo);
    TPM_SetTimerPeriod(TPM2, 48000);
    TPM_EnableInterrupts(TPM2, kTPM_TimeOverflowInterruptEnable);
    EnableIRQ(TPM2_IRQn);
    TPM_StartTimer(TPM2, kTPM_SystemClock);
    /////////////
	tpm_config_t tpminfo;
	tpm_chnl_pwm_signal_param_t tpmParam;
	tpmParam.chnlNumber = (tpm_chnl_t)4u;
	tpmParam.level = kTPM_HighTrue;
	tpmParam.dutyCyclePercent = 0;
	CLOCK_SetTpmClock(1U);
	TPM_GetDefaultConfig(&tpminfo);
	TPM_Init(TPM0, &tpminfo);
	TPM_SetupPwm(TPM0, &tpmParam, 1U, kTPM_EdgeAlignedPwm, 35000U, CLOCK_GetFreq(kCLOCK_PllFllSelClk));
	TPM_StartTimer(TPM0, kTPM_SystemClock);
    ////////////
    I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = 400000;
	I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(I2C0_CLK_SRC));

    LCD_init();
    LCD_clear();
    //////////////////

    int canal_u, canal_t;

    	sprintf(LCD_line1,"{}{}{}{}{}{}{}{}{}");
    	sprintf(LCD_line2,"| practica ind.3 !");
		sprintf(LCD_line3,"| ismael & nezly !");
   		sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{}");

   		LCD_print_text();
   		delay();
    while(1) {
       	//////////////////////////////////STOP
       	ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct);//Canal a leer
       	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, 0))){}
       	canal_u = ADC16_GetChannelConversionValue(ADC0, 0);//Pot
       	canal_t = canal_u * 0.3814755474;//1373311971

       	sprintf(LCD_line1,"-------------------");
   		sprintf(LCD_line2,"| seleccione rpm !");
   		sprintf(LCD_line3,"|     <%4d>    !", canal_t);
   		sprintf(LCD_line4,"------------------");
   		LCD_print_text();

       	TPM_PWM(TPM0, (tpm_chnl_t)4u, kTPM_EdgeAlignedPwm, 0);
       	//////////////////////////////////START
   		if(var_b == 1){
   		   var_b = 0;
   		   sprintf(LCD_line1,"rpm nvo & rpm act ");
   			LCD_print_text();
   		   sprintf(LCD_line4,"{}{}{}{}{}{}{}{}{}");
   			LCD_print_text();

   		while(1){

   			if(counter_u >= 50){//Cada 50ms * 20 la velocidad daria 1 segundo, pero..., al tener 20 agujeros el encoder a detectar
   				velocidad = velocidad * 60;// dividimos ese datos entre 20 quedando unicamente el valor de la velocidad tal cual
   				counter_u = 0;//dicho valor equivale a un segundo, lo multiplicamos por 60 para que sea equivalente a un minuto

   				var = velocidad < canal_t ? pwm++ : pwm--;

				sprintf(LCD_line2," <%d> - <%4d>   ", canal_t, velocidad);
				LCD_print_text();
				velocidad = 0;}

   	   		TPM_PWM(TPM0, (tpm_chnl_t)4u, kTPM_EdgeAlignedPwm, var);

   	   		sprintf(LCD_line3,"  pwm act  <%d>    ", pwm);
   	   		LCD_print_text();

   			if(pwm > 100){
   				pwm = 97;
   			}

   		if(var_d == 1){
   			var_d = 0;
   			break;

   }//Fin if botón STOP
   }//Fin while motor
   }//Fin if start
   }//Fin while
   }//Fin main
