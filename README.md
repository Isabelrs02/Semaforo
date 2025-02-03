🚦 Atividade 1 - Temporizador Periódico (Semáforo) 
* Colaboradora : Isabel Rosa de Santana.

Este projeto implementa um semáforo de LEDs utilizando o Raspberry Pi Pico W. O código alterna entre os estados vermelho → amarelo → verde de forma automática, utilizando um temporizador periódico com callback.

📌 Objetivo

Criar um sistema de semáforo utilizando temporizadores para alternar os LEDs sem precisar de delay(), tornando o código mais eficiente.

🛠️ Hardware Necessário

1x Raspberry Pi Pico W

3x LEDs (Vermelho, Amarelo e Verde)

3x Resistores de 330Ω

🖥️ Ligações (GPIOs)

Se estiver usando um LED RGB de cátodo comum, os pinos já correspondem ao setup.

📜 Código Completo

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define LED_VERMELHO 13
#define LED_AMARELO  12
#define LED_VERDE    11

// Variável global para controle do estado do semáforo
volatile int estado = 0;

// Função de callback do temporizador
bool semaforo_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Alterna entre os LEDs
    switch (estado) {
        case 0:
            gpio_put(LED_VERMELHO, 1);
            printf("🚦 Sinal VERMELHO\n");
            estado = 1;
            break;
        case 1:
            gpio_put(LED_AMARELO, 1);
            printf("🚦 Sinal AMARELO\n");
            estado = 2;
            break;
        case 2:
            gpio_put(LED_VERDE, 1);
            printf("🚦 Sinal VERDE\n");
            estado = 0;
            break;
    }
    return true; // Continua repetindo o temporizador
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial

    // Configuração dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Liga o LED vermelho no início
    gpio_put(LED_VERMELHO, 1);
    printf("🚦 Semáforo iniciado com Sinal VERMELHO\n");

    // Configuração do temporizador periódico de 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);

    // Loop principal para monitoramento via serial
    while (1) {
        printf("📢 Semáforo rodando...\n");
        sleep_ms(1000);
    }

    return 0;
}

📌 Passo a Passo do Código

1️⃣ Inicialização

Importamos as bibliotecas necessárias (pico/stdlib.h e hardware/timer.h).

Definimos os GPIOs dos LEDs (#define LED_VERMELHO 13...).

Criamos a variável estado, que controla a sequência do semáforo.


2️⃣ Callback do Temporizador

A função semaforo_callback():

1. Desliga todos os LEDs no início.


2. Verifica o estado atual e liga o LED correspondente:

Estado 0 → Liga o LED vermelho.

Estado 1 → Liga o LED amarelo.

Estado 2 → Liga o LED verde.

3. Atualiza o estado para a próxima troca.

4. Retorna true para continuar repetindo.


3️⃣ Configuração do main()

1. Inicializamos a comunicação serial (stdio_init_all();).


2. Configuramos os GPIOs como saída (gpio_set_dir()).


3. Ligamos o LED vermelho inicialmente.


4. Criamos o temporizador periódico:

add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);

Ele chama semaforo_callback() a cada 3 segundos.


5. Loop infinito que imprime mensagens de status a cada 1 segundo.


🛠️ Como Compilar e Executar

1️⃣ Configurar o CMakeLists.txt

Crie um arquivo CMakeLists.txt com o seguinte conteúdo:

cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(Semaforo C CXX ASM)
pico_sdk_init()

add_executable(semaforo main.c)

target_link_libraries(semaforo pico_stdlib)

pico_add_extra_outputs(semaforo)

2️⃣ Compilar

Abra o terminal e execute:

mkdir build
cd build
cmake ..
make

3️⃣ Subir o Código no Raspberry Pi Pico

Conecte o Raspberry Pi Pico W ao PC.

Copie o arquivo .uf2 gerado para o Pico (modo BOOTSEL).


4️⃣ Rodar no Wokwi 

Configure um projeto Raspberry Pi Pico no Wokwi.

Simule a execução e veja os LEDs alternando.

📢 Conclusão

✅ O código utiliza um temporizador periódico com callback para alternar os LEDs do semáforo automaticamente.
✅ Evita o uso de sleep_ms() dentro do fluxo principal, garantindo eficiência.
✅ A estrutura é modular e fácil de adaptar para projetos maiores.
