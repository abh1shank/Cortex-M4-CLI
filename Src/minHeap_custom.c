#include "minHeap_custom.h"
#include <string.h>
#include "main.h"

// ─── internal helpers ────────────────────────────────────────────

// Returns 1 if event a has higher priority than event b
// Lower priority NUMBER = higher urgency
// Timestamp breaks ties → earlier timestamp wins
static int comes_before(Event *a, Event *b)
{
    if (a->priority != b->priority)
        return a->priority < b->priority;
    return a->timestamp < b->timestamp;
}

static void swap(Event *a, Event *b)
{
    Event temp = *a;
    *a = *b;
    *b = temp;
}

// ─── bubble up (used after insert) ───────────────────────────────
static void bubble_up(MinHeap *h, int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (comes_before(&h->buffer[index], &h->buffer[parent]))
        {
            swap(&h->buffer[index], &h->buffer[parent]);
            index = parent;
        }
        else break;
    }
}

// ─── bubble down (used after pop) ────────────────────────────────
static void bubble_down(MinHeap *h, int index)
{
    while (1)
    {
        int left     = 2 * index + 1;
        int right    = 2 * index + 2;
        int smallest = index;

        if (left  < h->size && comes_before(&h->buffer[left],  &h->buffer[smallest]))
            smallest = left;
        if (right < h->size && comes_before(&h->buffer[right], &h->buffer[smallest]))
            smallest = right;

        if (smallest != index)
        {
            swap(&h->buffer[index], &h->buffer[smallest]);
            index = smallest;
        }
        else break;
    }
}

// ─── public API ──────────────────────────────────────────────────

// ─── aging: boost priority of all waiting events every second ────
void heap_age(MinHeap *h)
{
    static uint32_t last_age_time = 0;
    uint32_t now = HAL_GetTick();

    // run once per second
    if (now - last_age_time < 1000) return;
    last_age_time = now;

    // boost every event's priority by 1 (lower number = higher urgency)
    for (int i = 0; i < h->size; i++)
    {
        if (h->buffer[i].priority > 0)   // don't go below 0
            h->buffer[i].priority--;
    }

    // heap property violated after modifying priorities
    // rebuild heap from scratch (heapify)
    for (int i = (h->size / 2) - 1; i >= 0; i--)
        bubble_down(h, i);
}


void heap_insert(MinHeap *h, Event e)
{
    if (h->size >= HEAP_SIZE) return;   // full, drop event

    h->buffer[h->size] = e;
    bubble_up(h, h->size);
    h->size++;
}

Event heap_pop(MinHeap *h)
{
    Event result = h->buffer[0];

    h->size--;
    h->buffer[0] = h->buffer[h->size];  // move last to root
    bubble_down(h, 0);

    return result;
}

Event heap_peek(MinHeap *h)
{
    return h->buffer[0];   // just look, don't remove
}

int heap_isEmpty(MinHeap *h)
{
    return h->size == 0;
}
