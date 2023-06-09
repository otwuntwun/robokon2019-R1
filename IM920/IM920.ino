#include <SoftwareSerial.h>
#include "IM920Driver.h"

// シリアル通信に使うRX,TXピン
#define IM920_RX_PIN 10
#define IM920_TX_PIN 11

SoftwareSerial IM920Serial(IM920_RX_PIN, IM920_TX_PIN);
// SoftwareSerialのポインタを与える
IM920Driver im920(&IM920Serial);

void setup() {
  IM920Serial.begin(19200); // デフォルトでは19200bps(設定で変更可)
  Serial.begin(19200);
  
  // ECIOモードにする(デフォルトでDCIO)
  // im920.send("ECIO");
  
  // DCIOモードにする(デフォルトでDCIO)
  // im920.send("DCIO");
  delay(1000);
}

void loop() {
  char buff[IM920_BUFFER_SIZE];
  int n;

 
  while (im920.available()) {
     // ひたすらreadする
    im920.read();

    // 改行が認識された場合
    if ( im920.get_line_changed() ) {
      // その1行を受け取る
      im920.get_last_line(buff);
      
      // "OK"や"NG"でなければ表示する
      if ( strcmp(buff, "OK\r\n") != 0 && strcmp(buff, "NG\r\n") != 0) {
        Serial.println("New line >>");
        Serial.println(buff);
        
        // 通信相手にデータを送る
        im920.send("TXDA 54455354");
      }
    }
  }
  delay(50);
}
