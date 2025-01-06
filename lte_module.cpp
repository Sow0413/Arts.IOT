#include "lte_module.h"

// モデムの初期化
bool initializeModem() {
    int restartAttempts = 0;

    while (restartAttempts < 3) {
        Serial.println("BG77モデムの初期化を開始...");

        // モデムの再起動シーケンス
        pinMode(BG77_POWER_KEY, OUTPUT);
        digitalWrite(BG77_POWER_KEY, LOW);
        delay(1000);
        digitalWrite(BG77_POWER_KEY, HIGH);
        delay(2000);
        digitalWrite(BG77_POWER_KEY, LOW);
        delay(1000);

        Serial1.begin(115200);
        String response = sendATCommand("ATI", 1000);

        if (response.indexOf("Quectel") != -1) {
            Serial.println("BG77モデム起動完了");
            return true;
        }

        Serial.println("モデムの初期化に失敗しました。再試行中...");
        restartAttempts++;
    }

    Serial.println("モデム初期化の再試行回数が上限に達しました。");
    return false;
}

// LTE接続設定
bool configureLTE() {
    Serial.println("LTE接続設定を開始...");

    if (!sendATCommand("AT+CGDCONT=1,\"IP\",\"soracom.io\"", 1000).length()) {
        Serial.println("APN設定に失敗しました");
        return false;
    }

    if (!sendATCommand("AT+QIACT=1", 5000).length()) {
        Serial.println("PDPコンテキストの有効化に失敗しました");
        return false;
    }

    Serial.println("LTE接続設定完了");
    return true;
}

// PDPコンテキストの状態確認
bool isPDPContextActive() {
    String response = sendATCommand("AT+CGACT?", 1000);
    return (response.indexOf("+CGACT: 1,1") != -1);
}

// ATコマンド送信
String sendATCommand(const char *command, int timeout) {
    Serial1.println(command);
    String response = "";
    long startTime = millis();

    while (millis() - startTime < timeout) {
        while (Serial1.available()) {
            response += (char)Serial1.read();
        }
    }

    if (response.length() > 0) {
        Serial.println("コマンド応答: ");
        Serial.println(response);
    } else {
        Serial.println("応答なし");
    }

    return response;
}

// PING送信
void sendPing(const char *server) {
    String command = String("AT+QPING=1,\"") + server + "\"";
    String response = sendATCommand(command.c_str(), 10000);

    if (response.indexOf("+QPING:") != -1) {
        Serial.println("PING応答: ");
        Serial.println(response);
    } else {
        Serial.println("PING応答なしまたは失敗");
    }
}
