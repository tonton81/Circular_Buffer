/* This exmaple illustrates the use of the replace method with
 * using a circular array buffer.
 * The replace function is special. It searches all your 
 * "available" queues and replaces the entry thats found for a 
 * match. This is good when your running async code and if the
 * buffer wasnt written yet before the next queue addition, this
 * will replace your queue with the current one rather than adding
 * a duplicate command to the queue. It returns 0 if there was
 * no match. If a match was found, it would be updated and a 
 * 1 returned indicating it was updated.  An example is shown on the
 * Github page, https://github.com/tonton81/Circular_Buffer
 */
#include "circular_buffer.h"

/* The library supports uint8_t, uint16_t, and 
 * uint32_t and float entries 
 */
Circular_Buffer<uint8_t, 64, 10> k;

void setup() {
  Serial.begin(115200);
  delay(3000);  //not necessary but added to give user time to
                //open serial monitor.
  Serial.println("----------------------");
  Serial.print("Initial Q Size: "); 
  /* returns the size of the ring buffer or the count of 
   * circular arrays.  In our case it would be 64 
   */
  Serial.println(k.capacity());

  /* To get the raw array size, you call max_size(), to get 
   * the actual array data size, you call length_front() or 
   * length_back()
   */
  Serial.print("max_size: "); Serial.println(k.max_size());
  Serial.println("----------------------");

  //initialize the buffer
  init_buffer();
  Serial.print("After Init, Q Size Remaining: ");
  /*size() returns the size of the queue, whats actually used
   * in our case it would be 4.  Substracting the two returns
   * tells you the remaing buffer or array left.
   */
  Serial.println(k.capacity() - k.size());
  Serial.print("length_front(): "); Serial.println(k.length_front());
  Serial.print("length_back(): "); Serial.println(k.length_back());
`
  // set up test buffer for comparison
  uint8_t bufme[] = { 6, 19, 20, 21, 88, 12, 13, 4, 5 };

  /* replace method is comparing values, in this case, 19,20,21 , 
    between queue and buffer, the order is not imporant.
    replace is a very nice feature, it can compare and replace between 
    3 MIN to 5 MAX array indexes without modifying the head or tail, 
    this is good for user code that constantly writes to the array 
    system, where an update to an existing queue is preferred over a 
    double queue
  */
  Serial.println("----------------------");
  Serial.println("Example of replace with 3 indicies");
  Serial.println("----------------------");
  k.replace(bufme, sizeof(bufme), 1, 2, 3);
  /* list() is a visual perspective of whats in your queue, 
   * printed to Serial interface, without displaying 
   * the garbage of the raw storage container, only displaying
   * actual array data input.
   */
  k.list();

  Serial.println("----------------------");
  Serial.println("Indicies Don't Matter");
  // it's the same search pattern, if those indexes match, 
  // the buffer will replace that queue content
  Serial.println("----------------------");
  init_buffer();
  k.replace(bufme, sizeof(bufme), 3, 1, 2);
  k.list();

  // There is a minimum of replace indicies need for replace,
  // however, it is possible to use only 1 or two indicies
  Serial.println("----------------------");
  Serial.println("Example to replace based on 1 field");
  Serial.println("----------------------");
  init_buffer();
  k.replace(bufme, sizeof(bufme), 0, 0, 0);  // 1 field
  k.list();
  
  Serial.println("----------------------");
  Serial.println("(no replace) Example to replace based on 2 fields");
  Serial.println("----------------------");
  init_buffer();
  k.replace(bufme, sizeof(bufme), 5, 6, 6);  // 2 fields
  k.list(); 
  
  Serial.println("----------------------");
  Serial.println("(will replace) Example to replace based on 2 fields");
  Serial.println("----------------------");
  init_buffer();
  Serial.println("---->   added an extry buffer entry at end");
  uint8_t bufc4[] = { 21, 22, 23, 24, 25, 12, 13, 14 };
  k.push_back(bufc4, sizeof(bufc4));
  k.replace(bufme, sizeof(bufme), 5, 6, 6);  // 2 fields
  k.list();

  // Lets try that again with a little mix up on the buffer 
  Serial.println("mixed up buffer entries");
  init1_buffer();
  k.replace(bufme, sizeof(bufme), 5, 6, 6);  // 2 fields
  k.list();
}

void init_buffer(){
  k.clear();         //empties the buffer
  //set up temp arrays for loading buffer
  uint8_t bufc[] = { 0, 1, 2, 3, 4, 5 };
  uint8_t bufc1[] = { 6, 7, 8, 9, 10, 11 };
  uint8_t bufc2[] = { 12, 13, 14, 15, 16, 17 };
  uint8_t bufc3[] = { 18, 19, 20, 21, 22, 23 };

  /* push_back adds a value to the back of the queue
   * while push_front adds a value to the front of the 
   * queue.
   */
  k.push_back(bufc, sizeof(bufc));
  k.push_back(bufc1, sizeof(bufc1));
  k.push_back(bufc2, sizeof(bufc2));
  k.push_back(bufc3, sizeof(bufc3));
  k.list();
}

void init1_buffer(){
  k.clear();
  uint8_t bufc[] = { 0, 1, 2, 3, 4, 5 };
  uint8_t bufc1[] = { 6, 7, 8, 9, 10, 11 };
  uint8_t bufc2[] = { 12, 13, 14, 15, 16, 17 };
  uint8_t bufc3[] = { 18, 19, 20, 21, 22, 23 };
  uint8_t bufc4[] = { 21, 22, 23, 24, 25, 12, 13, 14 };

  k.push_back(bufc, sizeof(bufc));
  k.push_back(bufc1, sizeof(bufc1));
  k.push_back(bufc4, sizeof(bufc4));
  k.push_back(bufc3, sizeof(bufc3));
  k.push_back(bufc2, sizeof(bufc2));
  k.list();
}

void loop() {}
