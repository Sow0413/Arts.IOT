#ifndef LTE_MODULE_H
#define LTE_MODULE_H

#include <Arduino.h>

#define BG77_POWER_KEY WB_IO1

// モデム関連の関数
bool initializeModem(); // モデムを初期化する
bool configureLTE();    // LTE接続を設定する
bool isPDPContextActive(); // PDPコンテキストの状態を確認する
String sendATCommand(const char *command, int timeout); // ATコマンドを送信する
void sendPing(const char *server); // PINGを送信する

#endif // LTE_MODULE_H
