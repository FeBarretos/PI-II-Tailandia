#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include "como_jogar.h"


void como_jogar(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue) {
    // Carregar a imagem de fundo
    ALLEGRO_BITMAP* background = al_load_bitmap("COMO JOGAR.png");
    if (!background) {
        fprintf(stderr, "Falha ao carregar a imagem de fundo para a tela 'Como Jogar'\n");
        return;
    }

    int display_width = al_get_display_width(display);
    int display_height = al_get_display_height(display);

    // Largura e altura dos botões (ajustar conforme necessário)
    int largura_botao = 210, altura_botao = 50;

    // Coordenadas dos botões na imagem
    int botao_como_jogar_x = 365, botao_como_jogar_y = 450;

    bool rodando = true;
    while (rodando) {
        // Desenha o fundo
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_bitmap(background, 0, 0, 0);
        al_flip_display();

        // Espera e trata eventos
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            rodando = false;  // Encerra o loop ao fechar a janela
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = ev.mouse.x;
            int mouse_y = ev.mouse.y;

            if (mouse_sobre_botao(mouse_x, mouse_y, botao_como_jogar_x, botao_como_jogar_y, largura_botao, altura_botao)) {
                if (tela_inicio(display, event_queue)) {  // Verifica o retorno de tela_inicio
                    rodando = false;
                }
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                if (tela_inicio(display, event_queue)) {  // Verifica o retorno de tela_inicio
                    rodando = false;
                }
            }
        }
    }

    // Liberação de recursos
    al_destroy_bitmap(background);
}