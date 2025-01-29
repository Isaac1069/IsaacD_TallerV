/*
 * gpio_driver_bal.h
 *
 * created in Jan.28
 *               Author: idurango
 */

#ifndef GPIO_DRIVER_HAL_H_
#define GPIO_DRIVER_HAL_H_

#include <stdint.h>
#include <smt32f4xx.h>

/*Descripción de cada uno de los registros del periférico (no es necesario para este)*/

/**
  * GPIO bit set and bit reset enumeration
 */
enum
{
	     GPIO_PIN_RESET = 0,
		 GPIO_PIN_SET
};

/* Valores estandar para las configuraciones */
/* 8.4.1 GPIOx_MODER (Dos bits por cada pin*/
enum
{
	     GPIO_MODE_IN = 0,
		 GPIO_MODE_OUT,
		 GPIO_MODE_ALTFN,
		 GPIO_MODE_ANALOG
};

/*/* 8.4.2 GPIOx_OTYPER (UN BIT POR PIN)*/
 enum
 {
	     GPIO_OTYPE_PUSHPULL = 0,
		 GPIO_OTYPE_OPENDRAIN
 };

 /*8.4.3 GPIOx_OSPEEDR (dos bits por cada pin)*/
 enum
 {
	     GPIO_OSPEED_LOW = 0,
		 GPIO_OSPEED_MEDIUM,
		 GPIO_OSPEED_FAST,
		 GPIO_OSPEED_HIGH
 };

 /*8.4.4 GPIOx_PUPDR (2 bits por cada PIN)*/
 enum
 {
	     GPIO_PUODR_NOTHING = 0,
		 GPIO_PUPDR_PULLIP,
		 GPIO_PUPDR_PULLDOWN,
		 GPIO_PUPDR_RESERVED,
 };


 /*8.4.5 GPIOx_IDR (un bit por cada PIN) - Este es el registro para leer el estado un PIN*/

 /*8.4.6 GPIOx_ODR (un bit por cada PIN) - Este es el registro para escribir el estado un PIN
  * (1  o 0). Este registro puede ser escrito y leido desde software, pero no garantiza
  * escritura atomica. Es preferible usar registros BSRR*/

 /*Definicion de los nombes de los pines */
enum
{
	    PIN_0 = 0,
		PIN_1,
		PIN_2,
		PIN_3,
		PIN_4,
		PIN_5,
		PIN_6,
		PIN_7,
		PIN_8,
		PIN_9,
		PIN_10,
		PIN_11,
		PIN_12,
		PIN_13,
		PIN_14,
		PIN_15

};


/*definición de las funciones alternativas*/
enum
{
	    AF0 = 0b0000,
	    AF1 = 0b0001,
	    AF2 = 0b0010,
	    AF3 = 0b0011,
	    AF4 = 0b0100,
	    AF5 = 0b0101,
	    AF6 = 0b0110,
	    AF7 = 0b0111,
	    AF8 = 0b1000,
	    AF9 = 0b1001,
	    AF10 = 0b1010,
	    AF11 = 0b1011,
	    AF12 = 0b1100,
	    AF13 = 0b1101,
	    AF14 = 0b1110,
	    AF15 = 0b1111
};

#define GPIO_PIN_MASK  0x0FU  /*Pin mask for assert test */

/*Structure definition wich will keeps the configuration information for pinX */
typedef struct
{
        uint8_t GPIO_PinNumber;       //Working Pin
        uint8_t GPIO_PinMode;         //Config mode: imput, output analog, alternate func
        uint8_t GPIO_PinoutSpeed;     //Output speed for working pin
        uint8_t GPIO_PinPuOdControl;   //Turn on/off the pull-up and pull-down resistor for working pin
		uint8_t GPIO_PinOutputType;    //Selects output type: puss-pull or opendDrain
		uint8_t GPIO_PintAltFunMode;   //Type to alternate function assigned to working pin

} GPIO_PinConfig_t;

/*
 * Pin Handler definition.
 * This handler is used to configure the port at wich the selected pin is working
 * It holds two elements:
 * -Reference to the complete port(GPIOx), to have acces for the specific registers.
 * -Configuration structure: GPIO_PinConfig_t
 */
typedef struct
{
	    GPIO_typeDef           *pGPIOx;     //Pointer to the port of selected PinX
	    GPIO_PinConfig_t       pinConfig;   //Holds the configuration for selected PinX
} GPIO_Handler_t;


/*FOr testing assert parameters - checking basic configuration */
#define IS_GPIO_PIN_ACTION(ACTION)  (((ACTION) == GPIO_PIN_RESET) || (ACTION == GPIO_PIN_SET))

#define IS_GPIO_PIN(PIN)                        (((uint32_t)PIN)  <= GPIO_PIN_MASK)

#define IS_GPIO_MODE(MODE)                (((MODE) == GPIO_MODE_IN)             ||    \
                                                                          ((MODE) == GPIO_MODE_OUT)		      || \
									                                      ((MODE) == GPIO_MODE_ALTFN)	|| \
									                                      ((MODE) == GPIO_ANALOG)))

#define IS_GPIO_OUTPUT_TYPE(OUTPUT) (((OUTPUT)  == GPIO_OTYPE_PUSHPULL) || ((OUTPUT) == GPIO_OTYPE_OPENDRAIN))

#define IS_GPIO_OSPEED(SPEED)	(((SPEED) == GPIO_OSPEED_LOW)  || \
								 ((SPEED) == GPIO_SPEED_MEDIUM)|| \
								 ((SPEED) == GPIO_SPEED_FAST)|| \
								 ((SPEED) == GPIO_SPEED_HIGH))

#define IS_GPIO_PUPDR(PULL)		(((PULL) == GPIO_PUPDR_NOTHING) || \
								 ((PULL) == GPIO_PUPDR_PULLUP)	|| \
								 ((PULL) == GPIO_PUPDR_PULLDOWN))


/*Header definitions for the "public functions" of gpio_driver_hal */
void gpio_Config (GPIO_Handler_t *pGPIOHandler);
void gpio_WritePin(GPIO_Handler_t *PinHandler, uint8_t newState);
void gpio_TooglePin(GPIO_Handler_t *pPinHandler);
uint32_t gpio_ReadPin(GPIO_Handler_t *pPinHandler);


#endif /*GPIO_DRIVER_HAL_ */




