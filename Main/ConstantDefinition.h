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

#define Baud_Rate 115200

//
// LED pins definition
//
#define LED_Pin_0_D 4
#define LED_Pin_1_D 2
#define LED_Pin_2_D 15

//
// Task handles definition
//
TaskHandle_t TaskHandle_On_Core_0;
TaskHandle_t TaskHandle_On_Core_1;
TaskHandle_t TaskHandle_On_Core_1_New;
