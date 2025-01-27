// matrix_keypad_led.c
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h" // For clock_get_hz and clk_sys
#include "desenhos/desenhos.h"

#include "pio_matrix.pio.h" // Include the autogenerated file

#define ROWS 4
#define COLS 4
#define LED_PIN 14


const uint8_t row_pins[ROWS] = {9, 8, 7, 6};
const uint8_t col_pins[COLS] = {5, 4, 3, 2};

const char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Função para inicializar o teclado matricial
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

// Função para verificar a tecla pressionada
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

uint32_t matrix_rgb(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void desenho_pio2(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        if (i % 2 == 0)
        {
            valor_led = matrix_rgb(desenho[24 - i], r = 0.0, g = 0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
        else
        {
            valor_led = matrix_rgb(b = 0.0, desenho[24 - i], g = 0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}


void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        uint32_t valor_led = matrix_rgb(desenho[24 - i]*r, desenho[24 - i]*g, desenho[24 - i]*b);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

void desenho_pio3(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        uint32_t valor_led = matrix_rgb(desenho[24 - i]*r, desenho[24 - i]*g, desenho[24 - i]*b);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

void desenho_pio_blue(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        valor_led = matrix_rgb(b, r = 0.0, g = 0.0);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Função principal
int main()
{
    double intensidade;
    double r = 0.0, b = 0.0, g = 0.0;
    uint32_t valor_led;
    stdio_init_all();
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, LED_PIN);

    iniciar_teclado();

    while (true)
    {
        char tecla = get_tecla();

        switch(tecla){
            case '0':
                r = 1.0;
                g = 0.0;
                b = 1.0;
                desenho_pio(desenhomiddle1, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                desenho_pio(desenhomiddle2, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                desenho_pio(desenhomiddle3, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                desenho_pio(desenhomiddle4, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                desenho_pio(desenhomiddle5, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                break;
            case '1':
                b = 1.0;
                setIntensidade(circulo, intensidade);
                setIntensidade(coracao, intensidade);
                setIntensidade(setaBaixo, intensidade);
                setIntensidade(setaCima, intensidade);
                setIntensidade(quadrado, intensidade);
                desenho_pio(circulo, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                desenho_pio(coracao, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                desenho_pio(setaBaixo, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                desenho_pio(setaCima, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                desenho_pio(quadrado, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                break;
            case '2':
                r = 1.0;
                b = 1.0;
                setIntensidade(estrela, intensidade);
                setIntensidade(coroa, intensidade);
                setIntensidade(setaEsquerda, intensidade);
                setIntensidade(setaDireita, intensidade);
                setIntensidade(rosto, intensidade);
                desenho_pio(estrela, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                desenho_pio(coroa, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                desenho_pio(setaEsquerda, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                desenho_pio(setaDireita, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                desenho_pio(rosto, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                break;
            case '3':
                // Desenhar a palavra TECH!
                desenho_pio2(letraT, valor_led, pio, sm, r, g, b);
                sleep_ms(1100);
                desenho_pio2(letraE, valor_led, pio, sm, r, g, b);
                sleep_ms(1100);
                desenho_pio2(letraC, valor_led, pio, sm, r, g, b);
                sleep_ms(1100);
                desenho_pio2(letraH, valor_led, pio, sm, r, g, b);
                sleep_ms(1100);
                desenho_pio2(exclamacao, valor_led, pio, sm, r, g, b);
                sleep_ms(1100);
                
                break;
            case '4':
                // fazer contagem de 1 a 5
                desenho_pio2(numero1, valor_led, pio, sm, r, g, b);
                sleep_ms(1500);
                desenho_pio2(numero2, valor_led, pio, sm, r, g, b);
                sleep_ms(1500);
                desenho_pio2(numero3, valor_led, pio, sm, r, g, b);
                sleep_ms(1500);
                desenho_pio2(numero4, valor_led, pio, sm, r, g, b);
                sleep_ms(1500);
                desenho_pio2(numero5, valor_led, pio, sm, r, g, b);
                sleep_ms(1500);
                break;
            case '9': 
                r = 1.0;
                g = 1.0;
                b = 0.0;
                desenho_pio(desenhocorner1, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                desenho_pio(desenhocorner2, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                desenho_pio(desenhocorner3, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                desenho_pio(desenhocorner4, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                desenho_pio(desenhocorner5, valor_led, pio, sm, b, r, g);
                sleep_ms(500);
                break;
            case 'B':
                r = 0.0;
                g = 0.0;
                b = 1.0;
                intensidade = 1.0;
                break;
            case 'D':
                desenho_pio3(ledsLigados, valor_led, pio, sm, 0.0, 0.0, 1.0);
                sleep_ms(1500);
                break;
            case '#':
                r = 1.0;
                g = 1.0;
                b = 1.0;
                desenho_pio3(desenho_white, valor_led, pio, sm, b, r, g);
                sleep_ms(1000);
                break;
            default:
                desenho_pio3(ledsLigados, valor_led, pio, sm, 0.0 ,1.0,0.0);
                break;
        }
        sleep_ms(100);
    }
    return 0;
}
