#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "tela_inicio.h"
#include "jogo.h"
#include "fase_2.h"

// Variável da vida
int contVida = 3;

// Estados do jogo
typedef enum {
    TELA_INICIO,
    TELA_JOGO,
    SAIR
} EstadoJogo;

int main() {
    // Inicializar Allegro
    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar Allegro\n");
        return -1;
    }

    // Inicializa addons e dispositivos
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_acodec_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();

    // Criar o display
    ALLEGRO_DISPLAY* display = al_create_display(960, 540);
    if (!display) {
        fprintf(stderr, "Falha ao criar o display\n");
        return -1;
    }

    // Criar a fila de eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Estado inicial do jogo
    EstadoJogo estadoAtual = TELA_INICIO;

    // Loop principal do jogo
    while (estadoAtual != SAIR) {
        switch (estadoAtual) {
        case TELA_INICIO:
            if (tela_inicio(event_queue)) {
                estadoAtual = TELA_JOGO; // Transita para o jogo
            }
            else {
                estadoAtual = SAIR; // Sai do programa
            }
            break;

        case TELA_JOGO:
            jogo(display, event_queue); // Executa o jogo
            if (contVida <= 0) {
                estadoAtual = TELA_INICIO; // Volta para a tela de início se vidas acabarem
                contVida = 3; // Reseta a quantidade de vidas (se necessário)
            }
            else {
                estadoAtual = SAIR; // Encerra o programa ao finalizar o jogo
            }
            break;

        case SAIR:
            // Pode incluir lógica de saída, se necessário
            break;
        }
    }

    // Finalização
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
