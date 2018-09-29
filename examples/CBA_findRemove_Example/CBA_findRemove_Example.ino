#include "IFCT.h"

Circular_Buffer<uint32_t, 8, 5> cba;

void setup() {
  Serial.begin(1);
  delay(1000);
  uint32_t buf1[5] = { 1, 2, 3, 4 , 5 };
  uint32_t buf2[5] = {  6, 7, 8, 9, 10 };
  uint32_t buf3[5] = { 11, 12, 13, 14, 15 };
  uint32_t buf4[5] = { 16, 17, 18, 19, 20 };
  cba.push_back(buf1, 5);
  cba.push_back(buf2, 5);
  cba.push_back(buf3, 5);
  cba.list();
  cba.findRemove(buf1, 5, 0, 0, 0);
  cba.list();
}

void loop() {
  // put your main code here, to run repeatedly:

}
