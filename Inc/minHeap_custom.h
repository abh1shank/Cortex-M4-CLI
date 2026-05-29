#ifndef MINHEAP_CUSTOM_H
#define MINHEAP_CUSTOM_H

#include <stdint.h>
#include "main.h"
#define HEAP_SIZE 16


//this enum is to be used in switch case inside infinite while looop,
//we need to check what the event type actually is so that we can take appropriate actions
typedef enum {
    EVENT_CMD,
    EVENT_BUTTON,
    EVENT_SOS
} EventType;

typedef struct {
    int16_t   priority;     // 0 = highest
    uint32_t  timestamp;    // HAL_GetTick() when created
    EventType type;
    char      data[64];     // command string payload
} Event;

typedef struct {
    Event   buffer[HEAP_SIZE];
    int     size; //initialise with zero, means empty heap in the beginning
} MinHeap;

void     heap_insert(MinHeap *h, Event e);
Event    heap_pop(MinHeap *h);
Event    heap_peek(MinHeap *h);
int      heap_isEmpty(MinHeap *h);
void heap_age(MinHeap *h);
#endif /* MINHEAP_CUSTOM_H */
