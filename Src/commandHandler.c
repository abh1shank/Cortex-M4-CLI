#include "commandHandler.h"
#include "minHeap_custom.h"
#include <string.h>
#include <stdio.h>

// private helper — non blocking version comes later with events
// for now blocking is acceptable for SOS and button
static void timed_toggle(int interval_ms, int times)
{
    uint32_t last = 0;
    int count = 0;
    while (count < times)
    {
        uint32_t now = HAL_GetTick();
        if (now - last >= (uint32_t)interval_ms)
        {
            HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);  // use correct port/pin
            count++;
            last = now;
        }
    }
}

void command_handler(char *cmd)
{
    if (strncmp(cmd, "LED_ON", 6) == 0)
    {
        HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
        printf("LED ON\r\n");
    }
    else if (strncmp(cmd, "LED_OFF", 7) == 0)
    {
        HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
        printf("LED OFF\r\n");
    }
    else if (strncmp(cmd, "BLINK", 5) == 0)
    {
        // "BLINK 5" → freq at index 6
        int freq = (*(cmd + 6) - '0') * 100;
        int toggles = 10000 / freq;
        printf("Blinking at %d ms\r\n", freq);
        timed_toggle(freq, toggles);
    }
    else if (strncmp(cmd, "PANIC", 5) == 0)
    {
        SOS_handler();
    }
    else if (strncmp(cmd, "HELP", 4) == 0)
    {
        printf("Commands:\r\n");
        printf("  LED_ON       - Turn LED on\r\n");
        printf("  LED_OFF      - Turn LED off\r\n");
        printf("  BLINK <1-9>  - Blink LED (N*100ms interval)\r\n");
        printf("  PANIC        - SOS sequence\r\n");
        printf("  HELP         - Show this menu\r\n");
    }
    else
    {
        printf("Unknown command: %s\r\n", cmd);
        printf("Type HELP for commands\r\n");
    }
}

void SOS_handler(void)
{
    printf("SOS!\r\n");
    timed_toggle(200, 6);   // S - 3 short (on+off = 2 toggles each)
    HAL_Delay(200);
    timed_toggle(600, 6);   // O - 3 long
    HAL_Delay(200);
    timed_toggle(200, 6);   // S - 3 short
}

void button_handler(void)
{
    printf("Button pressed!\r\n");
    timed_toggle(100, 6);   // quick acknowledgement blink
}
