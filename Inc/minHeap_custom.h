#ifndef MINHEAP_CUSTOM_H
#define MINHEAP_CUSTOM_H

#include <stdint.h>

#define HEAP_SIZE 16

typedef enum {
    EVENT_CMD,
    EVENT_BUTTON,
    EVENT_BLINK,
    EVENT_STATUS,
    EVENT_PANIC
} EventType;

typedef struct {
    uint8_t   priority;     // 0 = highest
    uint32_t  timestamp;    // HAL_GetTick() when created
    EventType type;
    char      data[64];     // command string payload
} Event;

typedef struct {
    Event   buffer[HEAP_SIZE];
    int     size;
} MinHeap;

void     heap_insert(MinHeap *h, Event e);
Event    heap_pop(MinHeap *h);
Event    heap_peek(MinHeap *h);
int      heap_isEmpty(MinHeap *h);

#endif /* MINHEAP_CUSTOM_H */
