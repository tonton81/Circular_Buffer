#include "circular_buffer.h"

Circular_Buffer<uint16_t, 2048> cb;
Circular_Buffer<uint16_t, 4> cb2;
Circular_Buffer<uint32_t, 16> cb3;
Circular_Buffer<uint16_t, 16> cb4;

Circular_Buffer<uint32_t, 32, 250> print_test;

Circular_Buffer<uint16_t, 32> c5;



void setup() {
  Serial.begin(1);
  delay(2000);
  Serial.println("----------------------");


  for ( uint16_t i = 0; i < 34; i++ ) c5.write(i);
  while ( c5.size() > 0 ) {
    Serial.println(c5.read());
  } Serial.println("OK");
  
  print_test.print("Hello World");
  print_test.print("  ");
  print_test.println("Teensy here!");
  while ( print_test.size() > 0 ) {
    Serial.print((char)print_test.read());
  } Serial.println("OK");


  //  return;

  uint16_t testBuf[100];
  for ( uint16_t i = 0; i < 100; i++ ) testBuf[i] = i;
  uint32_t time = micros();

  cb.write(testBuf, 100);
  //  uint16_t myBuf2[] = { 1, 2, 3, 4, 5 };
  //  cb.push_front(myBuf2, 5);
  Serial.print(micros() - time);
  Serial.print("Size: "); Serial.println(cb.size());
  uint16_t size = cb.size();
  for ( uint16_t i = 0; i < size; i++ ) Serial.println(cb.read());
  //return;

  cb.write(0x1111);
  cb.write(0x1112);
  cb.write(0x1113);
  cb.write(0x1114);
  cb.write(0x1115);
  cb.push_front(0x85);
  cb.push_back(0x33);
  cb.push_front(0x66);
  uint16_t myBuf[] = { 1, 2, 3, 4, 5 };
  cb.push_front(myBuf, 5);
  Serial.print("Available: ");  Serial.println(cb.size());
  while ( cb.size() > 0 ) {
    Serial.println(cb.pop_front(), HEX);
  }


  Serial.println("----------------------");
  cb2.write(0x8807);
  cb2.write(6);
  cb2.write(0x2113);
  cb2.write(0x2114);
  cb2.write(0x2115);
  cb2.write(0x2116);
  cb2.write(0x2117);
  cb2.write(0x2118);
  cb2.push_back(0x2119);
  Serial.print("Available: ");  Serial.println(cb2.size());

  Serial.println("Peekbytes:");
  uint16_t buf[6];
  Serial.print("Count: "); Serial.println(cb2.peekBytes(buf, 6));
  for ( uint16_t i = 0; i < 6; i++ ) {
    Serial.print(buf[i], HEX); Serial.print(" ");
  } Serial.println();

  Serial.print("Print FIFO: ");  Serial.println(cb2.size());
  while ( cb2.size() > 0 ) {
    Serial.println(cb2.peek(), HEX);
    Serial.println(cb2.read(), HEX);
  }




  cb3.write(0x10002111);
  cb3.write(0x10002112);
  cb3.write(0x10002113);
  cb3.write(0x10002114);
  cb3.write(0x10002115);
  cb3.write(0x10002116);
  cb3.write(0x10002117);
  cb3.write(0x10002118);
  cb3.write(0x10002119);
  cb3.write(0x10002110);



  Serial.print("Available: "); Serial.println(cb3.size());
  while ( cb3.size() > 0 ) {
    Serial.println(cb3.peek(), HEX);
    Serial.println(cb3.read(), HEX);
  }










  cb4.write(0x2113);
  cb4.write(0x2114);
  uint16_t buff[4] = { 'T', 'o', 'n', 'y' };
  cb4.push_front(buff, 4);
  cb4.push_back(buff, 4);
  cb4.write(0x2115);
  cb4.write(0x2116);

  Serial.print("cb4 Available: ");  Serial.println(cb4.size());

  Serial.println("Printout:");
  while ( cb4.size() > 0 ) {
    Serial.println(cb4.read(), HEX);
  }



}

uint16_t buffer_arrays[32][250];
Circular_Buffer<uint16_t, 16> cb_ba;
Circular_Buffer<uint16_t, 32, 250> ca;

void loop() {
  static uint32_t timer = millis() - 3000;
  if ( millis() - timer > 2000 ) {
    timer = millis();


    for ( uint16_t i = 0; i < 35; i++ ) {
      static uint16_t val = 0;
      uint16_t Buf[20];
      for ( uint16_t i = 0; i < 20; i++ ) Buf[i] = i + val;
      ca.write(Buf, 20);
      val += 20;
    }

    while ( ca.size() > 0 ) {
      for ( uint16_t i = 0; i < 20; i++ ) {
        Serial.print(ca.front()[i]); Serial.print(" ");
      } Serial.println();
      ca.pop_front();
    }
while(1);


  }
}
