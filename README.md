# Cortex-M4-CLI

Interrupt Sources
  UART RX (USART2)       ->  ring buffer  ->  command builder  ->  event queue
  GPIO Button (PC13)     ->  debounce     ->  directly into event queue

Event Queue (Min-Heap)
  ordered by priority (lower number = higher urgency)
  timestamp used as tiebreaker among equal priorities
  priority aging: every event gains +1 urgency per second in queue

Main Loop Dispatcher
  pops due events from heap
  routes by EventType to handler via switch
  handlers execute via function pointer command table

State Machine
  IDLE, LED_ON, BLINKING, PAUSED, SOS
  illegal transitions silently ignored
  button press changes state at any time (PRIORITY_CRITICAL)
