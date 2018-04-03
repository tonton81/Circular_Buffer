Circular\_Buffer
================

This is pretty much an advanced version of a circular buffer that
follows the STL naming conventions of std::queue,deque,vector, etc...

It supports multiple circular buffer creations without the use of
reallocation, new, or malloc. The system uses a template for the
configuration of the buffers for the class.

Both circular buffers and circular arrays all support FIFO, LIFO, and
MIXED (FIFO+LIFO); This can lead you to design a priority queue system
where front entries for priority items and back entries for least
priority.

The library is capable of inserting and reading from both the front and
the back of the queue.

The buffer system this library supports is not just for ring buffer
usage. There is an even more powerful array system. Both buffer types
have advanced feature sets of their own we will talk about.

Methods for circular ring buffer
--------------------------------

            void print(const char *p);
            void println(const char *p);
            void push_front(const T *buffer, uint16_t length);
            void push_front(T value);
            void push_back(T value) { return write(value); }
            void push_back(const T *buffer, uint16_t length) { write(buffer, length); }
            T pop_front() { return read(); }
            T pop_front(T *buffer, uint16_t length) { return readBytes(buffer,length); }
            T pop_back();
            void write(T value);
            void write(const T *buffer, uint16_t length);
            T peek(uint16_t pos = 0);
            T peekBytes(T *buffer, uint16_t length);
            T read();
            T read(T *buffer, uint16_t length) { return readBytes(buffer,length); }
            T readBytes(T *buffer, uint16_t length);
            T variance();
            T deviation();
            T average();
            T median(bool override = 0);
            void sort_ascending();
            void sort_descending();
            T sum();
            T min();
            T max();
            T mean() { return average(); }
            T capacity() { return _size; }
            void flush() { clear(); }
            void clear() { head = tail = _available = 0; }
            uint16_t size() { return _available; }
            uint16_t available() { return _available; }

Methods for circular array buffer
=================================

            uint16_t size() { return _available; }
            uint16_t available() { return _available; }
            T capacity() { return _size; }
            T length_back() { return ((T)(_cabuf[_cbuf[(head+size()-1)&(_size-1)]][0] << 8*sizeof(T)) | _cabuf[_cbuf[(head+size()-1)&(_size-1)]][1]); }
            T length_front() { return ((T)(_cabuf[_cbuf[(head)&(_size-1)]][0] << 8*sizeof(T)) | _cabuf[_cbuf[(head)&(_size-1)]][1]); }
            T list();
            T max_size() { return multi; }
            T pop_back(T *buffer, uint16_t length);
            T* peek_front() { return front(); } 
            T* peek_back() { return back(); } 
            T* front() { return _cabuf[_cbuf[(head)&(_size-1)]]+2; }
            T* back() { return _cabuf[(tail-1)&(_size-1)]+2; }
            bool replace(T *buffer, uint16_t length, int pos1, int pos2, int pos3, int pos4 = -1, int pos5 = -1);
            T pop_back();
            void flush() { clear(); }
            void clear() { head = tail = _available = 0; }
            void push_back(const T *buffer, uint16_t length) { write(buffer, length); }
            void push_front(const T *buffer, uint16_t length);
            T pop_front(T *buffer, uint16_t length) { return readBytes(buffer,length); }
            T read();
            T read(T *buffer, uint16_t length) { return readBytes(buffer,length); }
            T readBytes(T *buffer, uint16_t length);
            void write(const T *buffer, uint16_t length);

### Method explanations

If you ever used queues before, you will notice some similarities. Here
is the full list of both buffers combined above since they share quite a
few methods but run differently depending on which buffer calls it.

            void push_back(T value) { return write(value); } // adds a value to the back of the queue
            void push_front(T value); // adds a value to the front of the queue
            T pop_front() { return read(); } // read and remove an item from the front queue
            T pop_back(); // read and remove an item from the back of the queue
            void write(T value); // write an item to the back of the queue
            void push_back(const T *buffer, uint16_t length) { write(buffer, length); } // write a buffer to the back of the queue
            void write(const T *buffer, uint16_t length); // write a buffer to the back of the queue
            void push_front(const T *buffer, uint16_t length); // write a buffer to the front of the queue
            T peek(uint16_t pos = 0); // show whats currently in queue, but don't remove. default 1st entry shown.
            T peekBytes(T *buffer, uint16_t length); // updates the buffer passed into the function with whats currently in queue, up to the length, or whatevers available, whichever comes first.
            T read(); // read an item from front of the queue and remove it
            T pop_front(T *buffer, uint16_t length) { return readBytes(buffer,length); } // read the front of the queue into a buffer and remove it
            T read(T *buffer, uint16_t length) { return readBytes(buffer,length); } // read the front of the queue into a buffer and remove it
            T readBytes(T *buffer, uint16_t length); // read the front of the queue into a buffer and remove it
            void flush() { clear(); } // clears the queue
            void clear() { head = tail = _available = 0; } // clears the queue
            void print(const char *p); // print("text") to the queue
            void println(const char *p); // println("text") to the queue, function appends the newline
            uint16_t size() { return _available; } // returns the size of the queue
            uint16_t available() { return _available; } // returns the size of the queue
            T capacity() { return _size; } // returns the size of the ring buffer or the count of circular arrays
            T length_back() { return ((T)(_cabuf[_cbuf[(head+size()-1)&(_size-1)]][0] << 8*sizeof(T)) | _cabuf[_cbuf[(head+size()-1)&(_size-1)]][1]); } // gives the length of the actual array (not raw size of array) of the back queue
            T length_front() { return ((T)(_cabuf[_cbuf[(head)&(_size-1)]][0] << 8*sizeof(T)) | _cabuf[_cbuf[(head)&(_size-1)]][1]); } // gives the length of the actual array (not raw size of array) of the front queue
            T list(); // prints out a list of your array entries stats on Serial. (only for circular arrays)
            T variance(); // calculates variance of entries stored in ring buffer
            T deviation(); // calculates standard deviation of entries stored in ring buffer
            T average(); // calculates average of entries stored in ring buffer
            T median(bool override = 0); // calculates median of entries stored in ring buffer, overload it to leave ring buffer sorted ascendingly
            void sort_ascending(); // sort ring buffer by ascending values
            void sort_descending(); // sort ring buffer by descending values
            T sum(); // sum of all entries in ring buffer
            T min(); // smallest value of all entries in ring buffer
            T max(); // largest value of all entries in ring buffer
            T mean() { return average(); } // average/mean of all entries in ring buffer
            T max_size() { return multi; } // max size of the internal buffer for the circular array, not the actual input array
            T pop_back(T *buffer, uint16_t length); // update a passed in buffer with the contents of the queue and remove it from queue
            T* peek_front() { return front(); } // look through the items of the front queued circular array
            T* peek_back() { return back(); }  // look through the items of the back queued circular array
            T* front() { return _cabuf[_cbuf[(head)&(_size-1)]]+2; } // look through the items of the front queued circular array
            T* back() { return _cabuf[(tail-1)&(_size-1)]+2; } // look through the items of the back queued circular array
            bool replace(T *buffer, uint16_t length, int pos1, int pos2, int pos3, int pos4 = -1, int pos5 = -1); // This replaces an array if 3-5 patterns match


The replace function is special. It searches all your "available" queues and replaces the entry thats found for a match.
This is good when your running async code and if the buffer wasnt written yet before the next queue addition, this will
replace your queue with the current one rather than adding a duplicate command to the queue. It returns 0 if there was no match.
If a match was found, it would be updated and a 1 returned indicating it was updated.

An example is as follows:
```
  uint8_t checksum = 0, buffer[4] = { (uint8_t)Form, WRITE_CMD, value, 0 };
  for ( uint8_t i = 1; i < 3; i++ ) checksum ^= buffer[i];
  buffer[3] = checksum;
  if ( !_outgoing_queue.replace(buffer,4,1,1,1) ) _outgoing_queue.push_back(buffer,4);
    return 0;
  }
```
That simple line above demonstrates that if no match is found "!_outgoing_queue.replace(buffer,4,1,2,3)",
in this case, it's comparing "buffer" against all your circular arrays in queue.
(buffer being the buffer to compare, 4 being it's size, 1,2,3 being the 3 indices to verify).
In this case, I'll mention byte[1] store the command, byte[2] stores object, byte[3] stores index, 4 and 5 actually contain the value, which is not our concern.
So if a buffer command, index, and object all match up, the buffer is replaced with one of updated values (_outgoing_queue.push_back(buffer,4);).

The library has a tracking system for the actual size of your arrays in the circular array raw buffer.
When you create a circular array buffer, of lets say, 200 per array in size, the library actually creates 202.
This is because the 2 first entries of the array internally are used when you buffer write the length of the array to queue.
The length is stored in the first 2 positions of the raw array space. Why 2? When dealing with char or uint8_t or other 8 bit buffers, going beyond 255 byte array indexing wont be possible...

The library supports many types, ones that have been tested are floats, uint8_t, uint16_t, and uint32_t.

## Construction

Theres 2 ways to construct the buffer of your choice.

```
Circular_Buffer<uint8_t, 16, 300> myBuffer; // creates a circular array system with 16 queue slots of arrays capable of storing 300 8bit entries
Circular_Buffer<float, 8, 200> myBuffer; // creates a circular array system with 8 queue slots of arrays capable of storing 200 float entries
Circular_Buffer<uint16_t, 4, 100> myBuffer; // creates a circular array system with 4 queue slots of arrays capable of storing 100 16bit entries

Circular_Buffer<uint16_t_t, 4> myBuffer; // creates a ring buffer holding 16bit x 4 entries max
Circular_Buffer<float, 32> myBuffer; // creates a ring buffer holding floats x 32 entries max
Circular_Buffer<uint32_t, 64> myBuffer; // creates a ring buffer holding 32bit x 64 entries max
```

### ALL YOUR SIZES MUST BE A POWER OF 2 FOR THE FIRST FIELD!!! IMPORTANT!
If you don't heed this warning, undefined behaviour will result!


There is a demo in the examples folder, hope you all enjoy it.
