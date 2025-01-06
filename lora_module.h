#ifndef LORA_MODULE_H
#define LORA_MODULE_H

#include <Arduino.h>
#include <LoRa.h>

bool initializeLoRa();
bool receiveLoRaData(String& data);

#endif // LORA_MODULE_H
