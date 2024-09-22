#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>  // Adicionar suporte a imagens
#include "tela_inicio.h"

bool mouse_sobre_botao(int mouse_x, int mouse_y, int botao_x, int botao_y, int largura_botao, int altura_botao) {
    return (mouse_x >= botao_x && mouse_x <= botao_x + largura_botao &&
        mouse_y >= botao_y && mouse_y <= botao_y + altura_botao);
}

bool tela_inicio(ALLEGRO_EVENT_QUEUE* event_queue) {
    // Usar a fonte embutida
    ALLEGRO_FONT* fonte = al_create_builtin_font();
    if (!fonte) {
        fprintf(stderr, "Falha ao criar a fonte embutida\n");
        return false;
    }

    // Carregar a imagem de fundo
    ALLEGRO_BITMAP* fundo = al_load_bitmap("fundo_tela_teste.png");
    if (!fundo) {
        fprintf(stderr, "Falha ao carregar a imagem de fundo\n");
        al_destroy_font(fonte);
        return false;
    }

    int largura_botao = 300, altura_botao = 80;
    int botao_x = (960 - largura_botao) / 2, botao_y = 540 / 2 + 100;
    bool iniciar_jogo = false;

    while (!iniciar_jogo) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_destroy_font(fonte);
            al_destroy_bitmap(fundo); // Destruir o bitmap ao fechar o jogo
            return false;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (mouse_sobre_botao(ev.mouse.x, ev.mouse.y, botao_x, botao_y, largura_botao, altura_botao)) {
                iniciar_jogo = true;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                iniciar_jogo = true;
            }
        }

        // Desenhar a tela de início com a imagem de fundo
        al_draw_bitmap(fundo, 0, 0, 0);  // Desenhar a imagem de fundo na posição (0, 0)

        // Desenhar o botão
        al_draw_filled_rectangle(botao_x, botao_y, botao_x + largura_botao, botao_y + altura_botao, al_map_rgb(100, 100, 255));
        al_draw_text(fonte, al_map_rgb(255, 255, 255), botao_x + largura_botao / 2, botao_y + altura_botao / 4, ALLEGRO_ALIGN_CENTRE, "Iniciar Jogo");

        // Exibir a mensagem de instrução
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 960 / 2, 540 / 2, ALLEGRO_ALIGN_CENTRE, "Pressione ENTER ou clique no botao");

        al_flip_display();
    }

    al_destroy_font(fonte);
    al_destroy_bitmap(fundo);  // Limpeza da imagem de fundo
    return true;
}
