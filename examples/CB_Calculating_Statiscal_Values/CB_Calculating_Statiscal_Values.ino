#include "circular_buffer.h"

/****************************
 * Example sketch showing how to use circular arrays
 * to calculate statistically values.  The functions
 * to this are built into the library
 */

void setup() {
  Serial.begin(115200);
  delay(3000);
  // Remember when you create you buffer you make sure
  // its a power of 2 or expected results will occur and
  // be wrong. inother words, 1,2,4,8,16,32,64,128,256,512,1024,etc... 
  Circular_Buffer<float, 8> myFloats;

  //load your buffer with some values.
  myFloats.push_back(3.14159);
  myFloats.push_back(12.3456);
  myFloats.push_back(78.91234);
  myFloats.push_back(7.91234);
  myFloats.push_back(11.91234);
  myFloats.push_back(58.91234);
  myFloats.push_back(18.91234);

  Serial.print("MIN: "); Serial.println(myFloats.min(), 5);
  Serial.print("MAX: "); Serial.println(myFloats.max(), 5);
  Serial.print("VARIANCE: "); Serial.println(myFloats.variance(), 5);
  Serial.print("DEVIATION: "); Serial.println(myFloats.deviation(), 5);
  Serial.print("MEAN: "); Serial.println(myFloats.mean(), 5);
  Serial.print("SUM: "); Serial.println(myFloats.sum(), 5);
  Serial.print("AVERAGE: "); Serial.println(myFloats.average(), 5);
  Serial.print("MEDIAN: "); Serial.println(myFloats.median(), 5);
  Serial.println();
  
  //data sorted in ascending order
  myFloats.sort_ascending();
  Serial.print("Print myFloats in ascending order: ");  
  Serial.println(myFloats.size());
  Serial.println();

  for(int i = 0; i < myFloats.size(); i++) {
    // peek show whats currently in queue, but doesn't remove. 
    // if you use read it will remove it from the buffer.   
    Serial.print(myFloats.peek(i)); Serial.print(", ");
  }
  Serial.println();
  
  //data sorted in descending order
  myFloats.sort_descending();
  Serial.print("Print myFloats in descending order: "); 
  Serial.println(myFloats.size());
  for(int i = 0; i < myFloats.size(); i++) {
    // peek show whats currently in queue, but doesn't remove.
    // if you use read it will remove it from the buffer. 
    Serial.print(myFloats.peek(i)); Serial.print(", ");
  }
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

}
