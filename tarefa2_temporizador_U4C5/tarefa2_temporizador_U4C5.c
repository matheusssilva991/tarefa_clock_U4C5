#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define GREEN_LED_PIN 11
#define BLUE_LED_PIN 12
#define RED_LED_PIN 13
#define BTN_A_PIN 5
#define LEDS_DELAY 3000
#define DEBOUNCE_DELAY 200

static volatile bool btn_disabled = false;
static volatile bool btn_pressed = false;
static volatile int led_state = 0;

void init_led(uint led_pin);
void init_btn(uint btn_pin);
int64_t alarm_callback(alarm_id_t id, void *user_data);
void btn_callback(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    // Inicializa os LEDs
    init_led(RED_LED_PIN);
    init_led(BLUE_LED_PIN);
    init_led(GREEN_LED_PIN);

    // Inicializa o botão
    init_btn(BTN_A_PIN);

    while (true)
    {
        if (btn_pressed && !btn_disabled)
        {
            btn_disabled = true;
            btn_pressed = false;
            add_alarm_in_ms(LEDS_DELAY * 0, alarm_callback, NULL, false);
        }
        sleep_ms(10);
    }
}

void init_led(uint led_pin)
{
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}

void init_btn(uint btn_pin)
{
    gpio_init(btn_pin);
    gpio_set_dir(btn_pin, GPIO_IN);
    gpio_pull_up(btn_pin);
    gpio_set_irq_enabled_with_callback(btn_pin, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
}

int64_t alarm_callback(alarm_id_t id, void *user_data)
{
    printf("Callback chamado - Led state antes: %d\n", led_state);
    switch (led_state)
    {
    case 0:
        gpio_put(GREEN_LED_PIN, 1);
        gpio_put(BLUE_LED_PIN, 1);
        gpio_put(RED_LED_PIN, 1);
        break;
    case 1:
        gpio_put(GREEN_LED_PIN, 0);
        gpio_put(BLUE_LED_PIN, 1);
        gpio_put(RED_LED_PIN, 1);
        break;
    case 2:
        gpio_put(GREEN_LED_PIN, 0);
        gpio_put(BLUE_LED_PIN, 0);
        gpio_put(RED_LED_PIN, 1);
        break;
    case 3:
        gpio_put(GREEN_LED_PIN, 0);
        gpio_put(BLUE_LED_PIN, 0);
        gpio_put(RED_LED_PIN, 0);
        btn_disabled = false;
        led_state = 0;
        return 0;
    }

    led_state = (led_state + 1) % 4;
    printf("Callback terminado - Led state depois: %d\n", led_state);

    add_alarm_in_ms(LEDS_DELAY, alarm_callback, NULL, false); // Reagendar próxima transição
}

void btn_callback(uint gpio, uint32_t events) {
    static uint64_t last_press_time = 0;
    uint64_t current_time = time_us_64() / 1000;

    if (current_time - last_press_time > DEBOUNCE_DELAY) {
        btn_pressed = true;
        last_press_time = current_time;
    }
}
