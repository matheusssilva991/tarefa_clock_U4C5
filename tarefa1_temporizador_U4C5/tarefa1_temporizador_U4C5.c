#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define RED_LED_PIN 11
#define YELLOW_LED_PIN 12
#define GREEN_LED_PIN 13

const int LEDS_DELAY = 3000;
static volatile int led_id = 1;

bool repeating_timer_callback(repeating_timer_t *rt);
void init_led(uint led_pin);

int main()
{
    stdio_init_all();

    init_led(RED_LED_PIN);
    init_led(YELLOW_LED_PIN);
    init_led(GREEN_LED_PIN);

    struct repeating_timer timer;

    add_repeating_timer_ms(LEDS_DELAY, repeating_timer_callback, NULL, &timer);

    while (true)
    {
        uint32_t start_ms = to_ms_since_boot(get_absolute_time());

        sleep_ms(1000);

        printf("Tempo absoluto em ms: %d \n", start_ms);
    }
}

bool repeating_timer_callback(repeating_timer_t *rt)
{
    switch (led_id)
    {
    case 1:
        printf("Led Vermelho.\n");
        gpio_put(RED_LED_PIN, 1);
        gpio_put(YELLOW_LED_PIN, 0);
        gpio_put(GREEN_LED_PIN, 0);
        break;
    case 2:
        printf("Led Amarelo.\n");
        gpio_put(RED_LED_PIN, 0);
        gpio_put(YELLOW_LED_PIN, 1);
        gpio_put(GREEN_LED_PIN, 0);
        break;
    case 3:
        printf("Led Verde.\n");
        gpio_put(RED_LED_PIN, 0);
        gpio_put(YELLOW_LED_PIN, 0);
        gpio_put(GREEN_LED_PIN, 1);
        break;
    }

    led_id = (led_id % 3) + 1;

    return true;
}

void init_led(uint led_pin)
{
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}
