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
#include "duty.h"
#include "ABC.h"
#define rango 127
#define Filtro 250

int cont = 0;
int arreglo[Filtro];
int arreglo_y[rango];
int arreglo_x[rango];

int var_b;
int counter_u = 0, counter_d = 0;
uint8_t g_master_buff[2U];
i2c_master_config_t masterConfig;
i2c_master_transfer_t masterXfer;

unsigned char LCD_screen_buffer[1024];
char LCD_line1[18];
char LCD_line2[18];
char LCD_line3[18];
char LCD_line4[18];
char LCD_line5[18];


void delay()
{
	int x= 0xFFFFF;
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
	//memset(&LCD_screen_buffer, 0xFF, 1024);
	//LCD_print();
	memset(&LCD_screen_buffer, 0, 1024);
	LCD_print();
}
void punto(char corx, char cory, char ClearClean){

	int filasCom=0, caracter = 0, pixel =0;
	unsigned char bits = 0x1;
	cory = 65 - cory;
	if((corx <= 128) && (cory <= 64)){
		filasCom = cory/8;
		caracter = (filasCom * 128) + corx;
		pixel = cory - (filasCom * 8);
		bits = bits << (pixel -1);
		if(ClearClean == 1){
		LCD_screen_buffer[caracter] = LCD_screen_buffer[caracter] | bits;
		}else{
			bits = ~bits;
			LCD_screen_buffer[caracter] = LCD_screen_buffer[caracter] & bits;
		}

		LCD_print();

	}
}
void grafica(int y, int contx){

	int cleany, cleanx,i;

	cont++;
	punto(contx, y, 1);
	for(i = rango-1; i > 0; i--){
		arreglo_y[i] = arreglo_y[i-1];
		arreglo_x[i] = arreglo_x[i-1];
       	}

       	arreglo_y[0] = y;
       	arreglo_x[0] = contx;
       	cleany = arreglo_y[126];
       	cleanx = arreglo_x[126];
		punto(cleanx, cleany, 0);

	if(cont >= 135){
		cont = 0;
}
}
int filtro(int pot){

	int i, PotFilter;
		for(i=Filtro-1; i>0; i--){
		arreglo[i] = arreglo[i-1];
		}
	arreglo[0] = pot;
	PotFilter = 0;
		for(i=Filtro-1; i>=0; i--){
		PotFilter = PotFilter + arreglo[i];
		}
	pot = PotFilter / Filtro;
return pot;}

void TPM1_IRQHandler(void){///////50us -  1500
TPM_ClearStatusFlags(TPM1, kTPM_TimeOverflowFlag);
counter_u++;
counter_d++;
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
    /////////////
    //////////
    tpm_config_t tpmInfo; //estructura inicial
    CLOCK_SetTpmClock(1U);
    TPM_GetDefaultConfig(&tpmInfo);
    TPM_Init(TPM1, &tpmInfo);
    TPM_SetTimerPeriod(TPM1, 48000);
    TPM_EnableInterrupts(TPM1, kTPM_TimeOverflowInterruptEnable);
    EnableIRQ(TPM1_IRQn);
    TPM_StartTimer(TPM1, kTPM_SystemClock);
    /////////////
	tpm_config_t tpminfo;
	tpm_chnl_pwm_signal_param_t tpmParam;
	tpmParam.chnlNumber = (tpm_chnl_t)0u;
	tpmParam.level = kTPM_HighTrue;
	tpmParam.dutyCyclePercent = 0;
	CLOCK_SetTpmClock(1U);
	TPM_GetDefaultConfig(&tpminfo);
	tpminfo.prescale = kTPM_Prescale_Divide_128;
	TPM_Init(TPM2, &tpminfo);
	TPM_SetupPwm(TPM2, &tpmParam, 1U, kTPM_EdgeAlignedPwm, 50, CLOCK_GetFreq(kCLOCK_PllFllSelClk));//750000
	TPM_StartTimer(TPM2, kTPM_SystemClock);
    ////////////
    I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = 400000;
	I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(I2C0_CLK_SRC));

	LCD_init();
	LCD_clear();

	int var, pot, var_u, var_d, y, var_t;
    int adc(void){
        ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct);//Canal a leer
    	while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, 0))){}
    	pot = ADC16_GetChannelConversionValue(ADC0, 0);
    	var_u = filtro(pot);
    	return var_u;
    }

    while(1){


    	//if(counter_d >= 5){
    	var = adc();
    	var_t = 50 + (var*0.003051804379);//1955034213
    	TPM_PWM(TPM2, (tpm_chnl_t)0u, kTPM_EdgeAlignedPwm, var_t);//.5 a 2.5 -----  25 a 125 ---- 50 a 250
    	var = adc();
    	//delay();
    	//}
    	//grafica(y, cont);
    	if(counter_u >= 50){
        	var_d = adc();
        	y = var_d * 0.0009765774014;//06256109482
    		grafica(y, cont);
    		counter_u = 0;

    	}
    	//delay();

}}
