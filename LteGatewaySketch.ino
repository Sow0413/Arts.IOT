#include <Arduino.h>
#include "lte_module.h"

void setup() {
    Serial.begin(115200);
    Serial.println("LTE Gateway Initialization");

    // モデム初期化
    if (!initializeModem()) {
        Serial.println("モデムの初期化に失敗しました。システムを終了します。");
        while (1);
    }

    // LTE接続設定
    if (!configureLTE()) {
        Serial.println("LTE接続の設定に失敗しました。システムを終了します。");
        while (1);
    }

    Serial.println("LTE Gateway Ready.");
}

void loop() {
    static unsigned long lastPingTime = 0;

    if (millis() - lastPingTime > 10000) { // 10秒ごとにPING
        lastPingTime = millis();

        if (!isPDPContextActive()) {
            Serial.println("PDPコンテキストが無効のため、再設定を試みます...");
            if (!configureLTE()) {
                Serial.println("PDPコンテキスト再設定に失敗しました。再起動を推奨します。");
            }
        } else {
            sendPing("8.8.8.8");
        }
    }
}
