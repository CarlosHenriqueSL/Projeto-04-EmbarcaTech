#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "blink.pio.h"

#define ROWS 4
#define COLS 4

const uint8_t row_pins[ROWS] = {9, 8, 7, 6};
const uint8_t col_pins[COLS] = {5, 4, 3, 2};

const char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

void iniciar_teclado()
{
    for (int i = 0; i < ROWS; i++)
    {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 1);
    }
    for (int j = 0; j < COLS; j++)
    {
        gpio_init(col_pins[j]);
        gpio_set_dir(col_pins[j], GPIO_IN);
        gpio_pull_up(col_pins[j]);
    }
}

char get_tecla()
{
    for (int i = 0; i < ROWS; i++)
    {
        gpio_put(row_pins[i], 0);
        for (int j = 0; j < COLS; j++)
        {
            if (gpio_get(col_pins[j]) == 0)
            {
                while (gpio_get(col_pins[j]) == 0)
                    ; // Aguarda a tecla ser solta
                gpio_put(row_pins[i], 1);
                return keys[i][j];
            }
        }
        gpio_put(row_pins[i], 1);
    }
    return '\0'; // Nenhuma tecla pressionada
}

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq)
{
    blink_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);

    printf("Blinking pin %d at %d Hz\n", pin, freq);

    // PIO counter program takes 3 more cycles in total than we pass as
    // input (wait for n + 1; mov; jmp)
    pio->txf[sm] = (125000000 / (2 * freq)) - 3;
}

int main()
{
    stdio_init_all();

    // PIO Blinking example
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &blink_program);
    printf("Loaded program at %d\n", offset);

#ifdef PICO_DEFAULT_LED_PIN
    blink_pin_forever(pio, 0, offset, PICO_DEFAULT_LED_PIN, 3);
#else
    blink_pin_forever(pio, 0, offset, 6, 3);
#endif
    // For more pio examples see https://github.com/raspberrypi/pico-examples/tree/master/pio

    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
