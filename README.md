# Circular_Buffer

This pretty much an advanced version of a circular buffer that follows the STL naming convections of std::queue,deque,vector, etc...

It supports multiple circular buffer creations without the use of reallocation, new, or malloc. The system uses a template for the configuration of the buffers for the class.

Both circular buffers and circular arrays all support FIFO, LIFO, and MIXED (FIFO+LIFO); This can lead you to design a priority queue system where front entries for priority items and back entries for least priority.

Library is capable of inserting to back or front, including reading from back or front, and removing from back and front. Ditto with the array version.

Regarding the features, the public methods are as follows:

        void push_back(T value) { return write(value); }
        void push_front(T value);
        T pop_front() { return read(); }
        T pop_back();
        void write(T value);
        void push_back(const T *buffer, uint16_t length) { write(buffer, length); }
        void write(const T *buffer, uint16_t length);
        void push_front(const T *buffer, uint16_t length);
        T peek(uint16_t pos = 0);
        T peekBytes(T *buffer, uint16_t length);
        T read();
        T pop_front(T *buffer, uint16_t length) { readBytes(buffer,length); }
        T read(T *buffer, uint16_t length) { readBytes(buffer,length); }
        T readBytes(T *buffer, uint16_t length);
        void flush() { return head = tail = _available = 0; }
        void print(const char *p);
        void println(const char *p);
        uint16_t size() { return available(); }
        uint16_t available() { return _available; }
        T* front() { return _cabuf[peek()]; }
        T* back() { return _cabuf[(tail-1)&(_size-1)]; }
        
Aside from the circular buffer, there is an even more powerful feature introduced, which is called "Circular Arrays", which might be an interest to most people

if we call:

      Circular_Buffer<uint16_t, 32> c5;

c5 is your circular buffer, with 32 entry queue supporting uint16_t Types.
The library supports uint8_t, uint16_t, and uint32_t entries

To use the circular array version, its as follows:
        Circular_Buffer<uint16_t, 64, 250> myQueue;

myQueue now contains 64 arrays of 250 uint16_t elements!

The array version circulates the entire bank of 64 before circling back to recycle the arrays, so its pretty efficient.
Whats more important is that both circular buffers and circular arrays all use memmove, for fastest data transfers!



There is a demo in the examples folder, hope you all enjoy it.
