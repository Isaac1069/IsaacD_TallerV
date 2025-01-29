/**
 ******************************************************************************
 * @file           : main.c
 * @author         : namontoy@unal.edu.co
 * @brief          : Here starts the magic!!
 ******************************************************************************
 */
#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx.h>


#define RCC_BASE_ADDRESS 0x40023800UL
#define RCC_AHB1ENR_OFFSET 0x30
#define RCC_AHB1ENR   (RCC_BASE_ADDRESS + RCC_AHB1ENR_OFFSET)

#define GPIOA_BASE_ADDRESS 0x40020000UL
#define GPIOA_MODE_REG_OFFSET 0X00
#define GPIOA_MODE_ODR_OFFSET 0X14
#define GPIOA_MODE_REG   (GPIOA_BASE_ADDRESS + GPIOA_MODE_REG_OFFSET)
#define GPIOA_OPD_REG    (GPIOA_BASE_ADDRESS + GPIOA_MODE_ODR_OFFSET)



// Definicion de las cabeceras de las funciones del main
extern void configMagic(void);

/*
 * The main function, where everything happens.
 */
int main(void)
{
	/* Configuramos la magia! */
	configMagic();

	// Ciclo principal
    printf("Pruebas GPIO\n");

    uint32_t *registerAHB1enb = (uint32_t *)RCC_AHB1ENR;
    //uint32_t *registerAHB1enb = (uint32_t *)0x40023830UL;

    *registerAHB1enb |= (1 << 2); //Activando la señal del reloj para el puerto GPIOc
    *registerAHB1enb |= (1 << 0); //Activando la señal del reloj para el puerto GPIOA

    uint32_t *registerGPIOA_MODE = (uint32_t *)GPIOA_MODE_REG;
    *registerGPIOA_MODE |= (1 << 10);

    uint32_t *registerGPIOA_ODR = (uint32_t *)GPIOA_MODE_REG;
    *registerGPIOA_ODR |= (1 << 5); //LED2 (green) set

	while (1) {
	}

	return 0;
}

