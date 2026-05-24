#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#define MAX_SIZE 20

typedef struct {
    char bufferArr[MAX_SIZE];
    char* head;
    char* tail;
    int size;
} RingBuffer;

void  rb_push(RingBuffer *buffer, char inst);  // char not char* (one byte)
char  rb_pop(RingBuffer *buffer);              // returns char
int   rb_isEmpty(RingBuffer *buffer);
int   rb_isFull(RingBuffer *buffer);
void  rb_init(RingBuffer *buffer);             // initializer since C can't init in struct

#endif
