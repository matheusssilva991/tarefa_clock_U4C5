#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define GREEN_LED_PIN 11
#define BLUE_LED_PIN 12
#define RED_LED_PIN 13

const LEDS_DELAY = 3000;

bool repeating_timer_callback(repeating_timer_t *rt);
void init_led(uint led_pin);

int main()
{
    stdio_init_all();

    init_led(GREEN_LED_PIN);
    init_led(BLUE_LED_PIN);
    init_led(RED_LED_PIN);

    add_repeating_timer_ms(LEDS_DELAY, repeating_timer_callback, 1, NULL);
    add_repeating_timer_ms(LEDS_DELAY * 2, repeating_timer_callback, 2, NULL);
    add_repeating_timer_ms(LEDS_DELAY * 3, repeating_timer_callback, 3, NULL);

    while (true) {
        uint32_t start_ms = to_ms_since_boot(get_absolute_time());

        sleep_ms(1000);

        printf("Tempo absoluto em ms: %d \n", start_ms);
    }
}

bool repeating_timer_callback(repeating_timer_t *rt)
{
    switch ((int)rt->user_data) {
        case 1:
            printf("Repeating timer 1 callback\n");
            gpio_put(RED_LED_PIN, 1);
            gpio_put(GREEN_LED_PIN, 0);
            gpio_put(BLUE_LED_PIN, 0);
            break;
        case 2:
            printf("Repeating timer 2 callback\n");
            gpio_put(RED_LED_PIN, 0);
            gpio_put(GREEN_LED_PIN, 1);
            gpio_put(BLUE_LED_PIN, 1);
            break;
        case 3:
            gpio_put(RED_LED_PIN, 0);
            gpio_put(GREEN_LED_PIN, 1);
            gpio_put(BLUE_LED_PIN, 0);
            break;
    }
    return true;
}

void init_led(uint led_pin)
{
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}
