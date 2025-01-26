/*
 * CheckSourcesMain.c
 *
 *  Created on: Dec 2, 2024
 *      Author: namontoy
 *      Editor: Isaac Durango
 */

#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx.h>

/* Definiciond de variables */
uint32_t rotation;
int16_t temperatureValue;
int dummy;


// Definicion de las cabeceras de las funciones del main
extern void configMagic(void);
int16_t getTemperature(uint8_t getData);
uint32_t checkRotation(void);
uint8_t leaking(uint16_t const range);
uint8_t positiveFunction(uint8_t data);
int dostuff(char *data, int value);
uint8_t weirdFunction(uint8_t data);



/*
// * The main function, where everything happens.
 */
int main(void)
{
	/* Configuramos la magia! */
	configMagic();

	// Ciclo principal
	printf("Hola Mundo!\n");

	/* Probando diferentes funciones */
	checkRotation();
	getTemperature(23);
	leaking(350);
	positiveFunction(2);
	dostuff("abc", 1024);
	weirdFunction(26);

	while (1) {
	}

	return 0;
}

/* Describir cuales son los problemas que hay en esta función y como se pueden corregir
 * No es claro lo que el código quiere hacer, estos if anidados son ineficientes, por ejemplo, si rotation > 25, retorna a 1,
 * y pasa al siguiente if, si es menor que 45 retornará igual un 1, si es mayor pasará al siguiente if, y obviamente ahí será
 *  menor que 23 y retornará a 0, cuando desde el primer if pudo volver a 0 y realizar la tarea asignada del código.*/
//uint32_t checkRotation(void){

//	if(rotation > 25){
//		if(rotation > 45){
//			if(rotation < 23){
//				return 0;
//			}
//		}
//		return 1;
//	}
//	return 1;
//}

/* Corrección, si lo que quiero es que mi código ejecute una acción para una condición mayor a 25, sería así: */
uint32_t checkRotation(void){
    if (rotation > 25){
		return 1;              // Si rotation es mayor a 25, devuelve 1
	}
	return 0;                  // Si no, devuelve 0
}

/* Describir cuales son los problemas que hay en esta función y como se pueden corregir
 * La linea i--; genera un problema de ciclo infinito, para cierto valor de temperatura, primero aumenta 1 valor y luego decrece 1 valor,
 * por lo que nunca se alcanzará el valor de 10 y se entrará en un bucle, para corregirlo se debe eliminar la línea que genere el problema.*/
 // int16_t getTemperature(uint8_t getData){
//	if(getData == 1){
//		for(int i = 0; i < 10; i++){
//			temperatureValue = i*35;
//			i--;
//		}
//		return temperatureValue;
//	}
//	return 0;
//}

/* Corrección: */
int16_t getTemperature(uint8_t getData){
       if(getData == 1){
	 		for(int i = 0; i < 10; i++){
	 			temperatureValue = i*35; //Toma valores de i entre 0 y 10, incrementando de a 1, y le asigna un valor de temperatura
	 			}
	         return temperatureValue;    //Retorna el valor de temperatura y vuelve al ciclo
	 }
	 	return 0;   //Una vez alcanzado el 10, deja de cumplir la condición y termina el ciclo.
	 }





//Describir cuales son los problemas que hay en esta función y como se pueden corregir




//
//uint8_t leaking(uint16_t const range){
	//char a[10];

	//Utilice una linea de codigo del ciclo FOR y luego la otra, ¿que observa en la salida del cppcheck?
	//for(uint8_t size = 0; size < range; size++){ //Al utilizar esta, me dice que el índice que está por fuera de los límites, ya que los índices van de 0-9
	                                               // Tampoco le doy un límite a size, por lo que siguiera también desborda los límites
	//for(uint8_t size = 0; size < 350; size++){     //Al usar esta estoy asignando a cada índice del arreglo a un valor determinado, pero nuevamente supera los límites.
		//a[size] = size*2;


    //Utilice una linea de codigo del ciclo FOR y luego la otra, ¿que observa en la salida del cppcheck?
	//return a[9];  //Al usar esta com ambas lineas nuevamente supera los límites
	//return a[10];

uint8_t leaking(uint16_t const range){
	char a[10];

	/* Utilice una linea de codigo del ciclo FOR y luego la otra, ¿que observa en la salida del cppcheck?*/
	//for(uint8_t size = 0; size < range; size++){

	for(uint8_t size = 0; size < 10; size++){   //Defino un nuevo límite para size que sí cuente con el espacio necesario en a[]
		a[size] = size*2;                       //A cada índice le asigno un valor size*2
	}

	/* Utilice una linea de codigo del ciclo FOR y luego la otra, ¿que observa en la salida del cppcheck?*/
	return a[9];  //Retorno el índice 9 que está dentro de los valores permitidos, de hecho, es el máximo.
	//return a[10];
}



/* Describir cuales son los problemas que hay en esta función y como se pueden corregir */
/*uint8_t positiveFunction(uint8_t data){
	if(data == 1){     En este caso hay un problema de utilizar el if-else de forma redundante, y en ambos casos retornar a 1, no tiene sentido agregar más líneas
		return 1;
	}else{
		return 1;
	}
}*/

/* Corrección: Simplemente comparar si data es igual a 1 y retornar 1 para confirmar, caso contrario retornar 0 */
uint8_t positiveFunction(uint8_t data){
	if(data == 1){
		return 1;
	}
	    return 0;
}



/* Describir cuales son los problemas que hay en esta función y como se pueden corregir
 * Sobra definir weird= 10, y luego compararlo con 25, ya que no serán iguales y retornará 0
 * En la tercera línea se está asignando un valor y además comparando, algo que puede llevar a errores, em ambos casos la comparación retorna a 0,
 *  por lo que hace ineficiente el código, si quiero verificar que data es igual a 25 para ejecutar una acción, simplemente los comparo,
 *  y ejecuto, sino cumple que retorne a 0.*/

// uint8_t weirdFunction(uint8_t data){
//	uint8_t weird = 10;
//	if((weird = data) == 25){
//		return 0;
//	}else{
//		return 0;
//	}
//}


/* Corrección: Para comparar el valor de data con 25 y tomar una decisión determinada */

uint8_t weirdFunction(uint8_t data){
	if(data == 25){       //Compara data con 25
		return 1;         // Si es 25 retorna 1
	}
	return 0;             //Si no, retorna 0 y acaba.
}




/* Describir cuales son los problemas que hay en esta función y como se pueden corregir
 * No se especifica el valor del arreglo data y se está asignando al índice 125 del arreglo, como 200, sin saber si existe
 * el espacio suficiente para esto, no se ha tampoco la variable dummy, por lo que si se va a usar se debe declarar primero,
 * aunque el uso de esta variable no es clara, no tiene sentido usarla.*/
//int dostuff(char *data, int value){
//	data[125] = 200;
//	dummy = value + 1;
//
//	return 0;
//}

/* Describir cuales son los problemas que hay en esta función y como se pueden corregir */
int dostuff(char data[150], int value ){    //Asigna un espacio a data suficiente para luego usar el índice 125
	data[125] = 200;
	dummy = value + 1;
	return 0;   //Retorna 0 para confirmar la asignación
}


/*Explicar cada una de las opciones de la línea de comandos que se utiliza para ejecutar el análisis estático del código.*/
/* cppcheck-- Simplemente accede al programa desde la terminal y se prepara para realizar un análisis estático para un código
 * template=gcc-- Se utiliza en el cppcheck para aclarle al programa en qué entorno de compilación realizará el análisis estático
 * --enable=all-- Se encarga de que el cppcheck haga un análisis más exhaustivo del código, es decir, que permita encontrar errores que comunmente no se encuentren al compilar el código
 * --platform=unix64 Le especifíca al cppcheck en qué ambiente se está trabajando, tipo linux o windows
 * --std=c11  Aclara que el lenguaje en el que está escrito el código que se va a analizar es C, y además hace énfasis en que es el C11, para que detecte problemas de compatibilidad entre versiones, si así lo requiere.
 * --suppress=missingIncludeSystem Le indica al cppcheck que omita todos los errores relacionados con falta de archivos encabezados, librerías, etc, esto hace que la salida del análisis estático sea más simplificada.
 * verbose Permite que el cppcheck emita una salida con errores más clara y concisa, de tal manera que el usuario pueda comprender bien sobre qué tratan los errores y hacer más eficiente la corrección de los mismos.
 * --suppress=unusedFunction Este comando permite que el análisis estático ignore errores o fallas en el caso de que se haya declarado una variable al inicio pero no se use durante el código, herramienta que es útil
 * en el desarrollo de proyectos en los cuales funciones que se van a utilizar a futuro sean ignoradas para no generar "errores" al momento del análisis estático de cierta parte del código final del proyecto.
 */










