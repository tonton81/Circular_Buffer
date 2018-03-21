#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

template<typename T, uint16_t _size, uint16_t multi = 0>
class Circular_Buffer {
    public:

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
        uint16_t size() { return _available; }
        uint16_t available() { return _available; }
        T* front() { return _cabuf[peek()]; }
        T* back() { return _cabuf[(tail-1)&(_size-1)]; }
        void match(T *buffer, uint16_t length, int pos1, int pos2, int pos3, int pos4 = -1, int pos5 = -1);

    protected:
    private:
        uint16_t head = 0, tail = 0, _available = 0, _array_pointer = 0;
        T _cbuf[_size];
        T _cabuf[_size][multi];
};


template<typename T, uint16_t _size, uint16_t multi>
void Circular_Buffer<T, _size, multi>::match(T *buffer, uint16_t length, int pos1, int pos2, int pos3, int pos4, int pos5) {
  uint8_t input_count = 3;
  uint8_t queue_position = 0;
  bool found = 0;
  if ( pos4 != -1 ) input_count = 4;
  if ( pos5 != -1 ) input_count = 5;
  Serial.print("Q Size: "); Serial.println(_available);

  Serial.println("Displaying current queue: ");
  for ( uint8_t j = 0; j < _size; j++ ) {

/*
Serial.print("Peeking: ");
   for ( uint8_t i = 0; i < _available; i++ ) {
      Serial.print(peek(i));
      Serial.print(" ");
    } Serial.println();


   Serial.print(j); Serial.print(": ");
   for ( uint8_t i = 0; i < multi; i++ ) {
      Serial.print(_cabuf[peek(j)][i]);
      Serial.print(" ");
    } Serial.println();

*/
  }


//Serial.print(head); Serial.print(" "); Serial.println(tail);

// good when head is in front of tail

  Serial.println("Displaying current queue: ");
  for ( uint8_t j = 0; j < size(); j++ ) {
    Serial.print(j); Serial.print(": ");
    for ( uint8_t i = 0; i < multi; i++ ) {
      Serial.print(_cabuf[peek(j)][i]);
      Serial.print(" ");
    } Serial.println();
  }





  for ( uint8_t j = 0; j <= _available; j++ ) {
    queue_position = j;
    switch ( input_count ) {
      case 3: {
          if ( _cabuf[j][pos1] == buffer[pos1] && _cabuf[j][pos2] == buffer[pos2] &&
               _cabuf[j][pos3] == buffer[pos3] ) {
            found = 1; 
            break;
          }
        }
      case 4: {
          if ( _cabuf[j][pos1] == buffer[pos1] && _cabuf[j][pos2] == buffer[pos2] &&
               _cabuf[j][pos3] == buffer[pos3] && _cabuf[j][pos4] == buffer[pos4] ) {
            found = 1;
            break;
          }
        }
      case 5: {
          if ( _cabuf[j][pos1] == buffer[pos1] && _cabuf[j][pos2] == buffer[pos2] &&
               _cabuf[j][pos3] == buffer[pos3] && _cabuf[j][pos4] == buffer[pos4] &&
               _cabuf[j][pos5] == buffer[pos5] ) {
            found = 1;
            break;
          }
        }
    }
    if ( found ) {
      memmove(_cabuf[j],buffer,length*sizeof(T));
      break;
    }
  }

  Serial.print("Q Size: "); Serial.println(_available);
  if ( !found ) { Serial.println("Nothing Found"); }
  Serial.println();
  Serial.println("Displaying updated queue: ");
  for ( uint8_t j = 0; j < _available; j++ ) {
    Serial.print(j); Serial.print(": ");
    for ( uint8_t i = 0; i < multi; i++ ) {
      Serial.print(_cabuf[j][i]);
      Serial.print(" ");
    } Serial.println();
  }

}
template<typename T, uint16_t _size, uint16_t multi>
void Circular_Buffer<T,_size,multi>::print(const char *p) {
  if ( multi ) return;
  write((T*)p,strlen(p));
}

template<typename T, uint16_t _size, uint16_t multi>
void Circular_Buffer<T,_size,multi>::println(const char *p) {
  if ( multi ) return;
  write((T*)p,strlen(p));
  write('\n');
}


template<typename T, uint16_t _size, uint16_t multi>
void Circular_Buffer<T,_size,multi>::push_front(const T *buffer, uint16_t length) {
  if ( multi ) {
    push_front(_array_pointer);
    memmove(_cabuf[peek()],buffer,length*sizeof(T));
    if ( _array_pointer++ >= _size -1 ) _array_pointer = 0;
    return;
  }
  for ( uint16_t i = length-1; i > 0; i-- ) push_front(buffer[i]);
  push_front(buffer[0]);
}

template<typename T, uint16_t _size, uint16_t multi>
T Circular_Buffer<T,_size,multi>::pop_back() {
  _available--;
  tail = (tail - 1)&(2*_size-1);
  return _cbuf[tail&(_size-1)];
}

template<typename T, uint16_t _size, uint16_t multi>
void Circular_Buffer<T,_size,multi>::push_front(T value) {
  if ( multi ) return;
  head = (head - 1)&(2*_size-1);
  _cbuf[head&(_size-1)] = value;
  if ( _available++ >= _size ) _available = _size;
}
template<typename T, uint16_t _size, uint16_t multi>
void Circular_Buffer<T,_size,multi>::write(const T *buffer, uint16_t length) {
  if ( multi ) {
    memmove(_cabuf[_array_pointer],buffer,length*sizeof(T));
    if ( _available++ >= _size ) _available = _size;
    _cbuf[tail&(_size-1)] = _array_pointer;
    if ( tail == (head ^ _size) ) head = (head + 1)&(2*_size-1);
    tail = (tail + 1)&(2*_size-1);
    if ( _array_pointer++ >= _size -1 ) _array_pointer = 0;
    return;
  }
  if ( ( _available += length ) >= _size ) _available = _size;
  if ( length < ( _size - tail ) ) {
    memmove(_cbuf+tail,buffer,length*sizeof(T));
    tail = (tail + length)&(2*_size-1);
  }
  else for ( uint16_t i = 0; i < length; i++ ) write(buffer[i]);
}

template<typename T, uint16_t _size, uint16_t multi>
void Circular_Buffer<T,_size,multi>::write(T value) {
  if ( multi ) return;
  if ( _available++ >= _size ) _available = _size;
  _cbuf[tail&(_size-1)] = value;
  if ( tail == (head ^ _size) ) head = (head + 1)&(2*_size-1);
  tail = (tail + 1)&(2*_size-1);
}



template<typename T, uint16_t _size, uint16_t multi>
T Circular_Buffer<T,_size,multi>::read() {
  _available--;
  T value = _cbuf[head&(_size-1)];
  head = (head + 1)&(2*_size-1);
  return value;
}

template<typename T, uint16_t _size, uint16_t multi>
T Circular_Buffer<T,_size,multi>::peek(uint16_t pos) {
  if ( multi ) {
    return _cbuf[(head+pos)&(_size-1)];
  }
  if ( pos > _size ) return 0;
  return _cbuf[(head+pos)&(_size-1)];
}

template<typename T, uint16_t _size, uint16_t multi>
T Circular_Buffer<T,_size,multi>::peekBytes(T *buffer, uint16_t length) {
  if ( multi ) return 0;
  uint16_t _count;
  ( _available < length ) ? _count = _available : _count = length;
  if ( _count < ( _size - head ) ) memmove(buffer,_cbuf,_count*sizeof(T));
  else for ( uint16_t i = 0; i < _count; i++ ) buffer[i] = peek(i);
  return _count;
}

template<typename T, uint16_t _size, uint16_t multi>
T Circular_Buffer<T,_size,multi>::readBytes(T *buffer, uint16_t length) {
  if ( multi ) {
    memmove(&buffer[0],&_cabuf[peek()],length*sizeof(T)); // update CA buffer
    read(); // deque item
    return 0;
  }
  uint16_t _count;
  ( _available <= length ) ? _count = _available : _count = length; // memmove if aligned
  if ( _count < ( _size - head ) ) {
    _available -= length;
    memmove(buffer,_cbuf,_count*sizeof(T));
    head = (head + _count)&(2*_size-1);
  }
  else for ( uint16_t i = 0; i < _count; i++ ) buffer[i] = read(); // if buffer rollover
  return _count;
}






#endif // Circular_Buffer_H
