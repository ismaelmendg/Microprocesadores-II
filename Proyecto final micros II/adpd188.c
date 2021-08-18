#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "AdpdDrv.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
/* Macros -------------------------------------------------------------------*/

/* Private define ---------------------------------------------------------- */

uint32_t gnAdpdTimeCurVal = 0;
uint8_t gnAdpdDataReady = 0;
i2c_master_config_t masterConfig;

//volatile bool completionFlag = false;
//volatile bool nakFlag = false;

/* Private variables --------------------------------------------------------*/

#define BUF_SIZE (256)

//char _SBZ[BUF_SIZE]; // used by 'debug'



uint32_t dcfg_org_188[] = {

  0x00120014,

  0x00150330,

  0x00183FFF,

  0x00193FFF,

  0x001A1F00,

  0x001B1F00,

  0x001E3FFF,

  0x001F3FFF,

  0x00201F00,

  0x00211F00,

  0x00340000,

  0x00060000,

  0x001130A0,

  0x00140555,

  0x00221030,

  0x00233036,

  0x00241030,

  0x0025630C,

  0x00300220,

  0x0031020f,

  0x00350220,

  0x0036020f,

  0x00391af8,

  0x003B1af8,

    0x003C7006,

  0x00421C35,

  0x0043ADA5,

  0x00441C34,

  0x0045ADA5,

  0x004E7040,

  0x00540AA0,

  0x003F0320,

  0x00580000,

  0x00590808,

  0x005A0010,

  0xFFFFFFFF,

};


/* Private function prototypes ----------------------------------------------*/

void HW_Global_Init(void);

void LoadDefaultConfig(uint32_t *cfg);

void VerifyDefaultConfig(uint32_t *cfg);

void AdpdDriverBringUp(uint8_t nSlotA, uint8_t nSlotB);

void AdpdFifoCallBack(void);



void SystemClock_Config();

void HAL_Init();

void GPIO_Init();

void UART_Init();

void SPI_Init();

void I2C_Init();

void TIM_Init();

void ADP_init();

void MCU_HAL_Delay(uint32_t);

void ADPD_configuracion(void);

uint32_t MCU_HAL_GetTick();



uint16_t AdpdRxBufferInsertData(uint32_t tcv);



/* Private function prototypes --------------------------------------------- */



uint16_t AppReadAdpdDataBuffer(ADPDData_t *rxData, uint32_t *time);


void  AdpdFifoCallBack ( void )

{



  //gnAdpdTimeCurVal = MCU_HAL_GetTick();

  gnAdpdDataReady = 1 ;

}
/**
  *  @brief    Callback function.
  *  @param    None
  *  @retval   None
*/





/**
                                 * Flow diagram of the code *
                                 ----------------------------
                                 | Hardware initializations |
                                 ----------------------------
                                             |
                                             |
                                 ----------------------------
                                 |  Data ready callback     |
                                 ----------------------------
                                             |
                                             |
                                 ----------------------------
                                 |Soft reset the ADPD device|
                                 |Initialize the ADPD driver|
                                 ----------------------------
                                             |
                                             |
                                 ----------------------------
                                 | Load the default config  |
                                 | and verify it            |
                                 ----------------------------
                                             |
                                             |
                                 ----------------------------
                                 | Write standard value of  |
                                 | clock registers          |
                                 ----------------------------
                                             |
                                             |
                                 ----------------------------
                             --->|     Driver bring up      |
                             |   ----------------------------
                             |               |
                             |               |
                             |---------------|
*/



/**
  *  @brief    Main program.
  *  @param    None
  *  @retval   None
*/

int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();
   // I2C_MasterTransferCreateHandle(BOARD_ACCEL_I2C_BASEADDR, &g_m_handle, i2c_master_callback, NULL);

    I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = 400000U;
	I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(I2C0_CLK_SRC));

	printf("Start\r\n");
	AdpdDrvDataReadyCallback (AdpdFifoCallBack);
	I2C_Init();
	gnAdpdDataReady = 1;
	AdpdDrvSoftReset();
while(1){
	AdpdDrvRegWrite(0x10, 1);
}

  /* Initialize the ADPD driver*/

  AdpdDrvOpenDriver();



  /* Load default configuration parameters */

  LoadDefaultConfig(dcfg_org_188);

  ADPD_configuracion();
  /* Read default configuration parameters from the device registers and verify */

  VerifyDefaultConfig(dcfg_org_188);



  /* Write standard value of clock registers */

  AdpdDrvRegWrite(0x004B, 0x2695);

  AdpdDrvRegWrite(0x004D, 0x4272);

  /* Driver bring up with 16-bits output data and 8 channel mode */

  AdpdDriverBringUp(ADPDDrv_4CH_16, ADPDDrv_4CH_16);
return 0;
}



void LoadDefaultConfig(uint32_t *cfg)

{

  uint8_t regAddr, i;

  uint16_t regData;

  if (cfg == 0) {

    return;

  }

  /* Clear the FIFO */

  AdpdDrvRegWrite(0x10, 0);

  AdpdDrvRegWrite(0x5F, 1);

  AdpdDrvRegWrite(0x00, 0x80FF);

  AdpdDrvRegWrite(0x5F, 0);

  i = 0;

  while (1) {

    /* Read the address and data from the config */

    regAddr = (uint8_t)(cfg[i] >> 16);

    regData = (uint16_t)(cfg[i]);

    i++;

    if (regAddr == 0xFF) {

      break;

    }

    /* Load the data into the ADPD registers */

    if (AdpdDrvRegWrite(regAddr, regData) != ADPDDrv_SUCCESS) {

      break;

    }

  }

}



/**
  *  @brief    Read default configuration parameters to verify
  *  @param    uint32_t *cfg
  *  @retval   None
*/

void VerifyDefaultConfig(uint32_t *cfg)

{

  uint16_t def_val;

  uint8_t  i;

  uint8_t  regAddr;

  uint16_t regData;

  if (cfg == 0) {

    return;

  }

  i = 0;

  /* Read the address and data from the config */

  regAddr = (uint8_t)(cfg[0] >> 16);

  def_val = (uint16_t)(cfg[0]);

  /* Read the data from the ADPD registers and verify */

  while (regAddr != 0xFF) {

    if (AdpdDrvRegRead(regAddr, &regData) != ADPDDrv_SUCCESS) {

      printf("DCFG: Read Error reg(%0.2x)\n", regAddr);

      return;

    }else if(regData != def_val){

      printf("DCFG: Read mismatch reg(%0.2x) (%0.2x != %0.2x)\n",

            regAddr, def_val, regData);

      return;

    }

    i++;

    regAddr = (uint8_t)(cfg[i] >> 16);

    def_val = (uint16_t)(cfg[i]);

  }

}



/**
  *  @brief  ADPD Driver bring up.
  *  @param  uint8_t nSlotA
  *  @param  uint8_t nSlotB
  *  @retval None
*/

void AdpdDriverBringUp(uint8_t nSlotA, uint8_t nSlotB)

{

  uint32_t LoopCnt;

  uint16_t nRetValue = 0;

  uint16_t nAdpdFifoLevelSize = 0, nAdpdDataSetSize;

  uint8_t value[16] = {0};

    uint8_t nLoopLim;



  /* Set the slot modes for slot A and slot B */

  AdpdDrvSetSlot(nSlotA, nSlotB);

        /* Set the device operation to sample mode. The data can be collected now */

  AdpdDrvSetOperationMode(ADPDDrv_MODE_SAMPLE);

        nLoopLim = nAdpdDataSetSize = 16;

  while (1) {

    /* Check if the data is ready */

    if(gnAdpdDataReady){

      gnAdpdDataReady = 0;

      /* Read the size of the data available in the FIFO */

      AdpdDrvGetParameter(ADPD_FIFOLEVEL, &nAdpdFifoLevelSize);

      /* Read the data from the FIFO and print them */

      while (nAdpdFifoLevelSize >= nAdpdDataSetSize) {

        nRetValue = AdpdDrvReadFifoData(&value[0], nAdpdDataSetSize);

        if (nRetValue == ADPDDrv_SUCCESS){

          for (LoopCnt = 0; LoopCnt < nLoopLim; LoopCnt += 2)

            /* Byte swapping is needed to print ADPD data in proper format */

            printf("%u ", (value[LoopCnt] << 8) | value[LoopCnt + 1]);

          printf("%u\r\n", gnAdpdTimeCurVal);

          nAdpdFifoLevelSize = nAdpdFifoLevelSize - nAdpdDataSetSize;

}}}}}

void ADPD_configuracion(void){
	AdpdDrvRegWrite(0x10, 1);
	//AdpdDrvCloseDriver(8,8);
	AdpdDrvSetSlot(1,1);
	AdpdDrvSetSlotLed(1,1);/////////
	//AdpdDrvGetSlotLed(1,1);
	//AdpdDrvSetParameter();
	//AdpdDrvEfuseRead();
	//AdpdDrvEfuseModuleTypeRead();
	//AdpdDrvEfuseModuleNameRead();
	AdpdDrvSetLedCurrent(12,1);/////////
	//AdpdDrvGetLedCurrent();
	AdpdDrvSetLedTrimCurrent(15,1);/////
	//AdpdDrvGetLedTrimCurrent();
	AdpdDrvSetNumPulses(150,1);//////////
	//AdpdDrvGetNumPulses();
	AdpdDrvSetAfeTiaGain(2,1);///////////////
	//AdpdDrvGetAfeTiaGain();
	AdpdDrvSetSamplingFrequency(0x0028);////////
	//AdpdDrvGetSamplingFrequency();

	AdpdDrvSetInternalAverage(4,1);/////
	//AdpdDrvGetInternalAverage();
	AdpdDrvSetAdcOffset(0x3FFF, 4,1);/////////Verificar
	//AdpdDrvGetAdcOffset();
	//AdpdDrvSoftReset();////////
	//AdpdDrvSetInterrupt();
	//SetInterruptControl();
//	SetAdpdIdleMode();
	//AdpdFillDataToArray();
	AdpdDrvRegWrite(0x10, 0x0002);
}

