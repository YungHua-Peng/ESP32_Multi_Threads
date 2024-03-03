//==========================================================================//
// Copyright 2024 - 2024 YungHua-Peng                                       //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//         http://www.apache.org/licenses/LICENSE-2.0                       //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
//==========================================================================//

#include "ConstantDefinition.h"

//
// Declare the global variable
//
int   LoopTimes = 1;
bool  New_Task  = false;

//
// Declare the task functions
//
void Create_Tasks(void);
void Task_Function_Core_1(void * pvParameters);
void Task_Function_Core_0(void * pvParameters);

void setup() {
  // Set the serial baud rate
  Serial.begin(Baud_Rate);

  // Create the tasks
  Create_Tasks();

  //
  // Define the pin mode and set the LED status to off
  //
  pinMode(LED_Pin_0_D, OUTPUT);
  pinMode(LED_Pin_1_D, OUTPUT);
  pinMode(LED_Pin_2_D, OUTPUT);

  digitalWrite(LED_Pin_0_D, LOW);
  digitalWrite(LED_Pin_1_D, LOW);
  digitalWrite(LED_Pin_2_D, LOW);
}

//
// The code in loop() will be run on core 1
// Usually, when using the task features, the main loop should do nothing
//
void loop() {
  // Check the loop times. If the loop times is more than 5, delete the task handle on core 1.
  if (LoopTimes > 5 && !New_Task ) {
    vTaskDelete(TaskHandle_On_Core_1);
    TaskHandle_On_Core_1 = NULL;

    // Create new task on core 1
    xTaskCreatePinnedToCore(
                    Task_Function_Core_1_new,   /* Task function. */
                    "Task1_new",                /* name of task. */
                    10000,                      /* Stack size of task */
                    NULL,                       /* parameter of the task */
                    1,                          /* priority of the task */
                    &TaskHandle_On_Core_1_New,  /* Task handle to keep track of created task */
                    1);                         /* pin task to core 0 */                  
    delay(500);
    New_Task = true;
  }
}

void Create_Tasks(void) {
  // Create a task that will be executed in the Task_Function_Core_0() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task_Function_Core_0,   /* Task function. */
                    "Task0",                /* name of task. */
                    10000,                  /* Stack size of task */
                    NULL,                   /* parameter of the task */
                    1,                      /* priority of the task */
                    &TaskHandle_On_Core_0,  /* Task handle to keep track of created task */
                    0);                     /* pin task to core 0 */                  
  delay(500); 

  // Create a task that will be executed in the Task_Function_Core_1() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task_Function_Core_1,   /* Task function. */
                    "Task1",                /* name of task. */
                    10000,                  /* Stack size of task */
                    NULL,                   /* parameter of the task */
                    1,                      /* priority of the task */
                    &TaskHandle_On_Core_1,  /* Task handle to keep track of created task */
                    1);                     /* pin task to core 1 */
  delay(500);
}

//
// Blinks the LED 0 every 1 second
//
void Task_Function_Core_0(void * pvParameters) {
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  while (true) {
    digitalWrite(LED_Pin_0_D, HIGH);
    delay(1000);
    digitalWrite(LED_Pin_0_D, LOW);
    delay(1000);
  } 
}

//
// Blinks the LED 1 every 2 seconds
//
void Task_Function_Core_1(void * pvParameters) {
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  while (true) {
    Serial.print("Loop times = ");
    Serial.println(LoopTimes);

    digitalWrite(LED_Pin_1_D, HIGH);
    delay(2000);
    digitalWrite(LED_Pin_1_D, LOW);
    delay(2000);

    LoopTimes++;
  }
}

//
// Show the information every 1 seconds
//
void Task_Function_Core_1_new(void * pvParameters) {
  while (true) {
    Serial.print("New task running on core ");
    Serial.println(xPortGetCoreID());
    delay(1000);
  }
}