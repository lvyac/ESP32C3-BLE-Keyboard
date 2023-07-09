/**
 * This example turns the ESP32C3 into a Bluetooth LE keyboard that presses a media key.
 * https://github.com/T-vK/ESP32-BLE-Keyboardを改変しESP32C3でのメディアコントロールに特化したやつ
 * NimBLE-Arduinoをライブラリマネージャからダウンロードしてください。
 * また，arduino BLEとライブラリ名が競合しているため共存できません。
 * 必ずアンインストールしてください。
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32C3 Media Keybord","Mendako Lab",50);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  
  // 使えるメディア制御コマンド
  // keyIDの実装参考
  // https://www.usb.org/document-library/hid-usage-tables-14
  /*
  KEY_MEDIA_NEXT_TRACK
  KEY_MEDIA_PREVIOUS_TRACK
  KEY_MEDIA_STOP 
  KEY_MEDIA_PLAY
  KEY_MEDIA_PAUSE
  KEY_MEDIA_MUTE
  KEY_MEDIA_VOLUME_UP
  KEY_MEDIA_VOLUME_DOWN
  */
  
  // 入力ピンの設定
  // D6,8,9はめんどくさいので使わない
  // 詳細は → https://lab.seeed.co.jp/entry/2023/04/03/120000
  pinMode(D0,INPUT_PULLUP);    //GPIO0(BOOT)をプルアップ付き入力設定
  pinMode(D1,INPUT_PULLUP);    //GPIO0(BOOT)をプルアップ付き入力設定
  pinMode(D2,INPUT_PULLUP);    //GPIO0(BOOT)をプルアップ付き入力設定
  pinMode(D3,INPUT_PULLUP);    //GPIO0(BOOT)をプルアップ付き入力設定
  pinMode(D4,INPUT_PULLUP);    //GPIO0(BOOT)をプルアップ付き入力設定
  pinMode(D5,INPUT_PULLUP);    //GPIO0(BOOT)をプルアップ付き入力設定
  pinMode(D7,INPUT_PULLUP);    //GPIO0(BOOT)をプルアップ付き入力設定
  pinMode(D10,INPUT_PULLUP);    //GPIO0(BOOT)をプルアップ付き入力設定

}

void loop() {
  // 長押し判定用のフラグ
  static bool flag_KEY_MEDIA_NEXT_TRACK = false;
  static bool flag_KEY_MEDIA_PREVIOUS_TRACK = false;
  if(bleKeyboard.isConnected()) {
    if(digitalRead(D0) == LOW && flag_KEY_MEDIA_NEXT_TRACK == false){
      Serial.println("Sending Scan Next Track media key...");
      flag_KEY_MEDIA_NEXT_TRACK = true;
      bleKeyboard.press(KEY_MEDIA_NEXT_TRACK);
    }
    else if(digitalRead(D0) == HIGH && flag_KEY_MEDIA_NEXT_TRACK == true){
      flag_KEY_MEDIA_NEXT_TRACK = false;
      bleKeyboard.release(KEY_MEDIA_NEXT_TRACK);
    }
    if(digitalRead(D1) == LOW && flag_KEY_MEDIA_PREVIOUS_TRACK == false){
      Serial.println("Sending Scan Previous Track media key...");
      flag_KEY_MEDIA_PREVIOUS_TRACK = true;
      bleKeyboard.press(KEY_MEDIA_PREVIOUS_TRACK);
    }
    else if(digitalRead(D1) == HIGH && flag_KEY_MEDIA_PREVIOUS_TRACK == true){
      flag_KEY_MEDIA_PREVIOUS_TRACK = false;
      bleKeyboard.release(KEY_MEDIA_PREVIOUS_TRACK);
    }
    if(digitalRead(D2) == LOW){
      Serial.println("Sending Stop media key...");
      bleKeyboard.write(KEY_MEDIA_STOP);
      delay(200);
    }
    if(digitalRead(D3) == LOW){
      Serial.println("Sending Play media key...");
      bleKeyboard.write(KEY_MEDIA_PLAY);
      delay(200);
    }
    if(digitalRead(D4) == LOW){
      Serial.println("Sending Pause media key...");
      bleKeyboard.write(KEY_MEDIA_PAUSE);
      delay(200);
    }
    if(digitalRead(D5) == LOW){
      Serial.println("Sending Mute media key...");
      bleKeyboard.write(KEY_MEDIA_MUTE);
      delay(200);
    }
    if(digitalRead(D7) == LOW){
      Serial.println("Sending Volume Increment media key...");
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      delay(50);
    }
    if(digitalRead(D10) == LOW){
      Serial.println("Sending Volume Decrement media key...");
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
      delay(50);
    }
  }
}