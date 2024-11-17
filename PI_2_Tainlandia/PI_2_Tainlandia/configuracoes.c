#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "configuracoes.h"

// Fun��o de configura��o
void configuracoes(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_SAMPLE_INSTANCE* musicInst) {
    ALLEGRO_BITMAP* tela_som_off = al_load_bitmap("tela som off.png");
    ALLEGRO_BITMAP* tela_som_on = al_load_bitmap("tela som on.png");
    if (!tela_som_off || !tela_som_on) {
        fprintf(stderr, "Falha ao carregar as imagens de fundo\n");
        return;
    }

    bool config = true;
    extern int Volume;  // Come�a com o volume m�ximo
    int som_ativo = 1;   // 1 = Som ON (j� iniciado)

    // Largura e altura dos bot�es
    int largura_botao = 100, altura_botao = 40;

    // Coordenadas dos bot�es
    int botao_som_x = 415, botao_som_y = 260;  // Bot�o de Som ON/OFF
    int botao_back_x = 415, botao_back_y = 355; // Bot�o "Voltar"

    while (config) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_destroy_bitmap(tela_som_off); // Destruir o bitmap ao fechar o jogo
            al_destroy_bitmap(tela_som_on);  // Destruir a imagem "som on"
            return;
        }

        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = ev.mouse.x;
            int mouse_y = ev.mouse.y;

            // Verificar se o clique foi sobre o bot�o "ON/OFF"
            if (mouse_sobre_botao(mouse_x, mouse_y, botao_som_x, botao_som_y, largura_botao, altura_botao)) {
                if (Volume == 1) {
                    // Diminuir o volume (volume = 0)
                    Volume = 0;  // Som mudo
                    al_draw_bitmap(tela_som_off, 0, 0, 0);  // Trocar a imagem para "Som OFF"
                }
                else {
                    // Aumentar o volume (volume = 1)
                    Volume = 1;  // Som m�ximo

                    al_draw_bitmap(tela_som_on, 0, 0, 0);   // Trocar a imagem para "Som ON"
                }
            }

            // Verificar se o clique foi sobre o bot�o "Voltar"
            else if (mouse_sobre_botao(mouse_x, mouse_y, botao_back_x, botao_back_y, largura_botao, altura_botao)) {
                config = false;  // Sair da tela de configura��es e voltar para o menu anterior
            }
        }

        // Atualizar a tela com a imagem de fundo apropriada
        al_flip_display();  // Atualiza a tela
    }

    al_destroy_bitmap(tela_som_off);  // Limpeza da imagem de fundo
    al_destroy_bitmap(tela_som_on);  // Limpeza da imagem de fundo

 }

