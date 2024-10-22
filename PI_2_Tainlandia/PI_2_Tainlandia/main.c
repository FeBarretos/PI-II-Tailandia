#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include "tela_inicio.h"
#include "jogo.h"
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

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

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Executar tela de início
    if (!tela_inicio(event_queue)) {
        return 0; // Fechar o programa se o usuário sair da tela de início
    }

    // Executar o jogo
    jogo(display, event_queue);

    // Finalização
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}