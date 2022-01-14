/*
* DEBER 5: FUNCIONES ESPECÍFICAS
* OBJETIVO: Ejecutar tareas directamente en el Kernel del uC.
* NOMBRE:Juma Keneth
*/

#include <Arduino_FreeRTOS.h>           //Libreria RTOS
#include "queue.h"                      //Libreria Queue
#include <LiquidCrystal.h>              //Libreria LiquidCrystal
LiquidCrystal lcd (13,12,11,10,9,8);    //Seleccion de pines para la LCD
LiquidCrystal lcd2 (7,6,5,4,3,2);       //Seleccion de pines para la LCD
QueueHandle_t tempQueue;

void setup() {   
Serial.begin(9600);        // Inicio de comunicación serial 
lcd.begin(16,2);           // Inicializa la LCD
lcd2.begin(16,2);          // Inicializa la LCD
lcd.setCursor(3,0);        //Selecciona posicion en LCD 
lcd.print("Transmisor");   // Imprime mensaje 
lcd2.setCursor(4,0);       //Selecciona posicion en LCD 
lcd2.print("Receptor");   // Imprime mensaje 

lcd.setCursor(0,1);       //Selecciona posicion en LCD 
lcd.print("Temp Tx:");   // Imprime mensaje 

lcd2.setCursor(0,1);       //Selecciona posicion en LCD 
lcd2.print("Temp Rx:");   // Imprime mensaje

tempQueue = xQueueCreate(5,sizeof(int32_t)); //Creacion del paquete 
xTaskCreate(vSenderTask,"Sender Task",100,NULL,1,NULL);   //Tarea de envio de datos
xTaskCreate(vReceiverTask,"Receiver Task", 100,NULL, 1, NULL); //Tarea de recpeción de datos
}

void vSenderTask(void *pvParameters) { 
  BaseType_t qStatus;        //Conocer el estado del envio
  int32_t valueToSend = 20;  //Variable a enviar
  while(1) { 
    valueToSend++;            // Contador de temperatura
    qStatus = xQueueSend(tempQueue,&valueToSend,0); //Envio de datos al inicio de la cola 
    lcd.setCursor(9,1);        //Selecciona posicion en LCD 
    lcd.print(valueToSend);   // Imprime mensaje
    lcd.setCursor(12,1);        //Selecciona posicion en LCD 
    lcd.print("C");   // Imprime mensaje 
    Serial.print("Temperatura enviada : ");     // Impresión por cx serial
    Serial.println(valueToSend); vTaskDelay(1); // Impresión por cx serial
    vTaskDelay(50); // Delay()
    } 
}

void vReceiverTask(void*pvParameters) { //Metodo de recpeción de datos
  int32_t valueReceived;                //Valor recibido
  BaseType_t qStatus;                   //Identifica el estado de la tarea
  const TickType_t xTicksToWait = pdMS_TO_TICKS(500); 
  while(1) { 
    xQueueReceive(tempQueue,&valueReceived,xTicksToWait);
    lcd2.setCursor(9,1);        //Selecciona posicion en LCD 
    lcd2.print(valueReceived);   // Imprime mensaje
    lcd2.setCursor(12,1);        //Selecciona posicion en LCD 
    lcd2.print("C");   // Imprime mensaje  
    Serial.print("Temperatura recibida : ");// Impresión por cx serial
    Serial.println(valueReceived); // Impresión por cx serial
    vTaskDelay(1); // Delay()
    }
    }

void loop(){
  
  }
  
