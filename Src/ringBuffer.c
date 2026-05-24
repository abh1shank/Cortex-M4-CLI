#include "ringBuffer.h"
#include <stdio.h>

void rb_init(RingBuffer *buffer)
{
    buffer->head = &buffer->bufferArr[0];
    buffer->tail = &buffer->bufferArr[0];
    buffer->size = 0;
}

int rb_isEmpty(RingBuffer *buffer)
{
    return buffer->size == 0;
}

int rb_isFull(RingBuffer *buffer)
{
    return buffer->size == MAX_SIZE;
}

void rb_push(RingBuffer *buffer, char inst)
{
    if (rb_isFull(buffer)){
        return;                // drop byte, safe
    }

    *(buffer->head) = inst;

    if (buffer->head == &(buffer->bufferArr[MAX_SIZE-1])){
        buffer->head = &(buffer->bufferArr[0]);
    }
    else{
        buffer->head++;
    }

    buffer->size++;
}

char rb_pop(RingBuffer *buffer)
{
    if (rb_isEmpty(buffer)) return 0;

    char val = *(buffer->tail);   // save before moving tail

    if (buffer->tail == &(buffer->bufferArr[MAX_SIZE-1])){
        buffer->tail = &(buffer->bufferArr[0]);
    }
    else{
        buffer->tail++;
    }

    buffer->size--;
    return val;
}
