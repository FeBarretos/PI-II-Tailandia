#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "tela_inicio.h"
#include "configuracoes.h"
#include "como_jogar.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

// Função para verificar se o mouse está sobre um botão
bool mouse_sobre_botao(int mouse_x, int mouse_y, int botao_x, int botao_y, int largura_botao, int altura_botao) {
    return (mouse_x >= botao_x && mouse_x <= botao_x + largura_botao &&
        mouse_y >= botao_y && mouse_y <= botao_y + altura_botao);
}

bool tela_inicio(ALLEGRO_EVENT_QUEUE* event_queue) {
    // Carregar a imagem de fundo
    ALLEGRO_BITMAP* fundo = al_load_bitmap("tela inicial.png");
    if (!fundo) {
        fprintf(stderr, "Falha ao carregar a imagem de fundo\n");
        return false;
    }
    //Carrega musica de fundo
    al_reserve_samples(1);
    ALLEGRO_SAMPLE* music = al_load_sample("music.ogg");
    ALLEGRO_SAMPLE_INSTANCE* musicInst = al_create_sample_instance(music);
    al_set_sample_instance_playmode(musicInst, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musicInst, al_get_default_mixer());

    // Largura e altura dos botões (ajustar conforme necessário)
    int largura_botao = 100, altura_botao = 40;

    // Coordenadas dos botões na imagem
    int botao_play_x = 365, botao_play_y = 200;
    int botao_settings_x = 365, botao_settings_y = 270;
    int botao_como_jogar_x = 365, botao_como_jogar_y = 340;
    int botao_quit_x = 365, botao_quit_y = 410;

    bool iniciar_jogo = false;
    bool rodando = true;

    al_play_sample_instance(musicInst);
    while (rodando) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            al_destroy_bitmap(fundo); // Destruir o bitmap ao fechar o jogo
            al_destroy_sample(music);
            al_destroy_sample_instance(musicInst);
            return false;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = ev.mouse.x;
            int mouse_y = ev.mouse.y;

            // Verificar se o clique foi sobre o botão "Play"
            if (mouse_sobre_botao(mouse_x, mouse_y, botao_play_x, botao_play_y, largura_botao, altura_botao)) {
                iniciar_jogo = true;
                rodando = false;  // Para sair do loop e iniciar o jogo
            }
            // Verificar se o clique foi sobre o botão "Settings"
            else if (mouse_sobre_botao(mouse_x, mouse_y, botao_settings_x, botao_settings_y, largura_botao, altura_botao)) {
                configuracoes(event_queue);  // Abre o menu de configurações
            }
            else if (mouse_sobre_botao(mouse_x, mouse_y, botao_como_jogar_x, botao_como_jogar_y, largura_botao, altura_botao)) {
                como_jogar(fundo, event_queue);  // Passar o display corretamente
            }
            // Verificar se o clique foi sobre o botão "Quit"
            else if (mouse_sobre_botao(mouse_x, mouse_y, botao_quit_x, botao_quit_y, largura_botao, altura_botao)) {
                rodando = false;  // Fecha o programa
            }
        }

        // Desenhar a tela de início com a imagem de fundo
        al_draw_bitmap(fundo, 0, 0, 0);  // Desenhar a imagem de fundo na posição (0, 0)
        al_flip_display();
    }

    al_destroy_bitmap(fundo);  // Limpeza da imagem de fundo
    al_destroy_sample(music);
    al_destroy_sample_instance(musicInst);

    return iniciar_jogo;
}
