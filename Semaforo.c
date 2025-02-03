
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define LED_VERMELHO 13
#define LED_AMARELO  12
#define LED_VERDE    11

// Variável global para controle do estado do semáforo
volatile int estado = 0;

// Função de callback para o temporizador
bool semaforo_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de mudar de estado
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Alterna entre os LEDs
    switch (estado) {
        case 0:
            gpio_put(LED_VERMELHO, 1);
            printf("Sinal VERMELHO\n");
            estado = 1;
            break;
        case 1:
            gpio_put(LED_AMARELO, 1);
            printf("Sinal AMARELO\n");
            estado = 2;
            break;
        case 2:
            gpio_put(LED_VERDE, 1);
            printf("Sinal VERDE\n");
            estado = 0;
            break;
    }
    return true; // Continua repetindo o temporizador
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial

    // Configuração dos pinos dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Liga o LED vermelho no início
    gpio_put(LED_VERMELHO, 1);
    printf("Semáforo iniciado com Sinal VERMELHO\n");

    // Criar o temporizador periódico de 3 segundos e associar a callback
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);

    // Loop infinito apenas para manter o programa rodando
    while (1) {
        printf("Semáforo rodando...\n");
        sleep_ms(1000); // Mensagem a cada 1 segundo
    }

    return 0;
}
