/****************************************************
   this example is meant as a learning aid to circular buffering
   using list and normal buffering.
*/

#include "circular_buffer.h"

void setup() {
  Serial.begin(115200);
  delay(5000);
  /*
     Create a list circular buffer of 4 slots with a max
     of 6 list items that are floats, can be ints if you prefer.
     Remember that the specified slots has to 2^n slots, i.e.,
     2,4,8,16,32,64, 128........
  */
  Circular_Buffer<float, 4, 6> flt;

  /*
     let's load some data into list items
  */
  float _f0[] = { 123.456789, 789.012345 };
  float _f1[] = { 333.78643, 69.11 };
  float _f2[] = { 88.02, 743.69 };
  float _f3[] = { 223.456789, 989.012345 };
  float _f4[] = { 433.78643, 79.11 };
  float _f5[] = { 99.02, 843.69 };

  /*
     lets push the data from the back of the buffer
  */
  flt.push_back(_f0, 2);  flt.list();
  flt.push_back(_f1, 2);  flt.list();
  flt.push_back(_f2, 2);  flt.list();
  flt.push_back(_f3, 2);  flt.list();
  /*
     since we only have 4 slots specified for the buffer
     pushing anymore will automatically pop from the front or
     the top of the buffer and fill from the back since we
     are using push_back

     flt.list prints the status of the buffer
  */
  flt.push_back(_f4, 2);  flt.list();
  flt.push_back(_f5, 2);  flt.list();

  /*
     dump[2] is an temporary array to hold 2 elements
     since we only have 2 items specified
  */
  float dump[2];

  /*
     pop 1 slot from the front of the buffer and print it.
  */
  flt.pop_front(dump, 2);
  Serial.print(dump[0], 7); Serial.print(" : "); Serial.println(dump[1], 7);



  /*
     ok lets try something different, lets create a non-list
     buffer and again push the data to the back.
     Because the buffer can only hold 4 elements when we do the
     k.list it will only print the last 4 values we pushed.  In
     this case 6, 7, 8 and 9.
  */
  Serial.println("----------------------------------------------");
  Circular_Buffer<uint8_t, 4> k;
  k.push_back(1);
  k.push_back(2);
  k.push_back(3);
  k.push_back(4);
  k.push_back(5);
  k.push_back(6);
  k.push_back(7);
  k.push_back(8);
  k.push_back(9);
  k.list();

  /*
      Ok lets do that in reverse but pushing the data to front
      or head of the buffer.
      Since this time we specified 8 elements to the buffer
      9 will be at the top and 2 will be at the end of the
      buffer.
  */
  Serial.println("----------------------------------------------");
  Circular_Buffer<uint8_t, 8> k1;
  k1.push_front(1);
  k1.push_front(2);
  k1.push_front(3);
  k1.push_front(4);
  k1.push_front(5);
  k1.push_front(6);
  k1.push_front(7);
  k1.push_front(8);
  k1.push_front(9);
  k1.list();

  Serial.println("----------------Going back to the list example ------------------------------");
  flt.list();
  Serial.print("FLT size => "); Serial.println(flt.size());
  Serial.print("Length Front => "); Serial.println(flt.length_front());
  Serial.println("Peak at the 2nd row(1st array index),");
  Serial.print(" top row from the front with 7 decimal places  => ");
  //remember its a c list which starts at 0.
  Serial.print(flt.peek_front()[1], 7);  Serial.println("  (peek only looks but leaves the data in place)");

  Serial.println("Print of the first row of the buffer: ");
  for ( uint16_t i = 0; i < flt.length_front(); i++ ) {
    Serial.print(flt.peek_front()[i], 7); // print 7 decimals
    Serial.print(" ");
  }
  Serial.println("\n");

  Serial.println("To print out the whole buffer: ");
  uint16_t _s = flt.size();
  for ( uint16_t k = 0; k < _s; k++) {
    for ( uint16_t i = 0; i < flt.length_front(); i++ ) {
      Serial.print(flt.peek_front()[i], 7); // print 7 decimals
      Serial.print(" ");
    }
//    flt.pop_front();
    Serial.println();
  }
  Serial.println();

  Serial.println("Lets remove the top row from queue using pop_front:");
  flt.pop_front();
  flt.list();
  Serial.println("\n");

  Serial.println("Another way is to use the list indicie to remove a row,");
  Serial.println(" removing index 1:");
  /*
     the tail is untouched during the removal. all queues before the removal
     are shifted up with memmove, the head is increased, and available is decreased,
     this gives the producer his rights to the tail
  */
  Serial.println("Before:");
  flt.push_back(_f1, 2); flt.list();
  Serial.println("After:");
  flt.remove(1);
  flt.list();
  Serial.println("\n");
}

void loop() {
  // put your main code here, to run repeatedly:

}
