#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
int var=0;
int x;

int velocity(char v1, char v2, char v3);
int steps(char p1, char p2, char p3);
void delay(int x);
///////////////////////////////////////////////////////////FUNCIONES
void delay(int x)
{
    volatile uint32_t ui32Loop = x;
    while(ui32Loop > 0){
        ui32Loop--;
}}

void PORTA_IRQHandler(void){

	uint32_t boton = 0;
		boton = GPIO_GetPinsInterruptFlags(GPIOA);
		if(boton == 0x2000){
			var = 1;
		}

	    GPIO_ClearPinsInterruptFlags(GPIOA, (1U << 13));

}

int velocity(char v1, char v2, char v3){
	int velocidad_return=0;
	if(v1==1){
		v1 = 0x4;
	}else{
		v1 = 0x0;
	}

	if(v2==1){
			v2 = 0x2;
		}else{
			v2 = 0x0;
		}

	if(v3==1){
			v3 = 0x1;
		}else{
			v3 = 0x0;
		}
	velocidad_return = velocidad_return | v1 | v2 | v3;
	return velocidad_return;
}

int steps(char p1, char p2, char p3){
	int pasos_return = 0;
	int i;
	int steps_return = 1;
	//////
	if(p1==1){
		p1 = 0x4;
	}else{
		p1 = 0x0;
	}

	if(p2==1){
			p2 = 0x2;
		}else{
			p2 = 0x0;
		}

	if(p3==1){
			p3 = 0x1;
		}else{
			p3 = 0x0;
		}
	pasos_return = pasos_return | p1 | p2 | p3;

	for(i=0; i<pasos_return; i++){
		steps_return = steps_return * 2;//Multiplica por dos la variable guardada para dar un resultado exponencial a cada bit aumentado
	}
	return steps_return;
}
/////////////////////////////////////////////////////////////////////MAIN
int main(void) {

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif
    EnableIRQ(PORTA_IRQn);
 ////////////////////////////////////////////////////////////////////VARIABLES
    	uint32_t enable;//B8
        uint32_t direccion;//B9
        char i;
        uint32_t p1;//B10
        uint32_t p2;//B11
        uint32_t p3;//E2
        uint32_t v1;//E3
        uint32_t v2;//E4
        uint32_t v3;//E5
        int velocidad, pasos, cont;
        int static velocidad_uno;
        var = 0;
/////////////////////////////////////////////////////////////////////WHILE PRINCIPAL
    while(1) {
    	GPIO_SetPinsOutput(GPIOC, 0x4);
    	enable = GPIO_ReadPinInput(GPIOB, 8);///////B8
////////////////////////////////////////////////////////////////////INICIO
		switch(enable){
		case 0:
			GPIO_ClearPinsOutput(GPIOC, 0x4);
			var=0;
			break;
		case 1://Habilita el sistema y enciende un LED como aviso
			GPIO_SetPinsOutput(GPIOC, 0x4);

		if(var == 1){//Se podra pasar y leer todos los dip despues de que se presione el botón, apagando un LED, lo cual significa que ya comenzó la acción
			GPIO_ClearPinsOutput(GPIOC, 0x4);
			direccion = GPIO_ReadPinInput(GPIOB, 9);//B9
			p1 = GPIO_ReadPinInput(GPIOB, 10);//B10
			p2 = GPIO_ReadPinInput(GPIOB, 11);//B11
			p3 = GPIO_ReadPinInput(GPIOE, 2);//E2
			v1 = GPIO_ReadPinInput(GPIOE, 3);//E3
			v2 = GPIO_ReadPinInput(GPIOE, 4);//E4
			v3 = GPIO_ReadPinInput(GPIOE, 5);//E5
			velocidad = velocity(v1, v2, v3);
			pasos = steps(p1, p2, p3);
			velocidad_uno = 0xFFFFF;
			cont = 0;

	for(i = 0; i<velocidad; i++){//se restara la cantidad de veces que obtengamos de velocidad, comenzando con una velocidad incial de 0xFFFFF y terminando con 0x1FFFF
		velocidad_uno = velocidad_uno - 0x20000;
	}

	if(direccion == 1){
		while(1){
			cont++;
			GPIO_ClearPinsOutput(GPIOB, 0x7);//s1, s2, s3 apagado
			GPIO_SetPinsOutput(GPIOB, 0x8);//s4 prendido
			delay(velocidad_uno);
			if(cont==pasos){//El contador tendra ya un 1 en este punto, e ira sumando hasta llegar al numero de pasos necesitado, obteniendo asi, el numero de pasos exacto
				break;
			}else{
				cont++;
			}
			GPIO_ClearPinsOutput(GPIOB, 0xD);//s1, s3, s4 apagado
			GPIO_SetPinsOutput(GPIOB, 0x2);//s2 prendido
			delay(velocidad_uno);
			if(cont==pasos){
				break;
			}else{
				cont++;
			}
			GPIO_ClearPinsOutput(GPIOB, 0xB);//s1, s2, s4 apagado
			GPIO_SetPinsOutput(GPIOB, 0x4);//s3 Prendido
			delay(velocidad_uno);
			if(cont==pasos){
				break;
			}else{
				cont++;
			}
			GPIO_ClearPinsOutput(GPIOB, 0xE);//s2, s3, s4 apagado
			GPIO_SetPinsOutput(GPIOB, 0x1);//s1 prendido
			delay(velocidad_uno);
			if(cont==pasos){
				break;
			}else{
				cont++;
			}
		}//Fin while
	}else if(direccion == 0){
		while(1){
			cont++;
			GPIO_ClearPinsOutput(GPIOB, 0xE);//s2, s3, s4 apagado
			GPIO_SetPinsOutput(GPIOB, 0x1);//s1 prendido
			delay(velocidad_uno);
			if(cont==pasos){
			break;
			}else{
			cont++;
			}
			GPIO_ClearPinsOutput(GPIOB, 0xB);//s1, s2, s4 apagado
			GPIO_SetPinsOutput(GPIOB, 0x4);//s3 prendido
			delay(velocidad_uno);
			if(cont==pasos){
			break;
			}else{
			cont++;
			}
			GPIO_ClearPinsOutput(GPIOB, 0xD);//s1, s3, s4 apagado
			GPIO_SetPinsOutput(GPIOB, 0x2);//s2 prendido
			delay(velocidad_uno);
			if(cont==pasos){
			break;
			}else{
			cont++;
			}
			GPIO_ClearPinsOutput(GPIOB, 0x7);//s1, s2, s3 apagado
			GPIO_SetPinsOutput(GPIOB, 0x8);//s4 prendido
			delay(velocidad_uno);
			if(cont==pasos){
				break;
			}else{
				cont++;
			}

}//FIN WHILE IZQUIERDA
}//FIN IZQUIERDA
}//FIN VAR
var = 0;//Para eliminar los botonasos que se den mientras el motor esta funcionando
break;
}//FIN SWITCH
}//FIN WHILE
return 0 ;
}//FIN MAIN

