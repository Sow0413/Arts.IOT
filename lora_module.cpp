#include "lora_module.h"

bool initializeLoRa() {
    if (!LoRa.begin(920E6)) { // 周波数: 920 MHz
        Serial.println("LoRaの初期化に失敗しました。");
        return false;
    }
    Serial.println("LoRaの初期化に成功しました。");
    return true;
}

bool receiveLoRaData(String& data) {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        while (LoRa.available()) {
            data += (char)LoRa.read();
        }
        return true;
    }
    return false;
}
