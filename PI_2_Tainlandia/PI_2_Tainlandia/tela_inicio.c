#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "tela_inicio.h"
#include "configuracoes.h"

// Função para verificar se o mouse está sobre um botão
bool mouse_sobre_botao(int mouse_x, int mouse_y, int botao_x, int botao_y, int largura_botao, int altura_botao) {
    return (mouse_x >= botao_x && mouse_x <= botao_x + largura_botao &&
        mouse_y >= botao_y && mouse_y <= botao_y + altura_botao);
}

// Função para ajustar o volume da música
void ajustar_volume(ALLEGRO_SAMPLE_INSTANCE* musicInst, int volume) {
    if (volume == 1) {
        al_set_sample_instance_gain(musicInst, 1.0); // Som máximo
    }
    else if (volume == 0) {
        al_set_sample_instance_gain(musicInst, 0.0); // Som mudo
    }
}

bool tela_inicio(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue, int volume) {
    // Inicializar add-ons de imagens e áudio
    if (!al_init_image_addon()) {
        fprintf(stderr, "Falha ao inicializar o add-on de imagens\n");
        return false;
    }
    if (!al_install_audio() || !al_init_acodec_addon()) {
        fprintf(stderr, "Falha ao inicializar o sistema de áudio\n");
        return false;
    }

    // Carregar a imagem de fundo
    ALLEGRO_BITMAP* background = al_load_bitmap("images/tela_inicial.png");
    if (!background) {
        fprintf(stderr, "Falha ao carregar a imagem de fundo\n");
        return false;
    }

    // Carregar a música de fundo
    ALLEGRO_SAMPLE* music = al_load_sample("music.ogg");
    if (!music) {
        fprintf(stderr, "Falha ao carregar a música de fundo\n");
        al_destroy_bitmap(background);
        return false;
    }

    // Criar instância de música
    ALLEGRO_SAMPLE_INSTANCE* musicInst = al_create_sample_instance(music);
    if (!musicInst) {
        fprintf(stderr, "Falha ao criar instância de música\n");
        al_destroy_bitmap(background);
        al_destroy_sample(music);
        return false;
    }

    al_set_sample_instance_playmode(musicInst, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musicInst, al_get_default_mixer());

    // Reproduzir a música
    al_play_sample_instance(musicInst);

    // Ajustar volume de acordo com a variável volume
    ajustar_volume(musicInst, volume);

    // Largura e altura dos botões
    int largura_botao = 210, altura_botao = 50;

    // Coordenadas dos botões na imagem
    int botao_play_x = 365, botao_play_y = 200;
    int botao_settings_x = 365, botao_settings_y = 270;
    int botao_como_jogar_x = 365, botao_como_jogar_y = 340;
    int botao_quit_x = 365, botao_quit_y = 410;

    bool iniciar_jogo = false;
    bool rodando = true;

    while (rodando) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            rodando = false;  // Fecha o programa ao clicar para fechar a janela
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = ev.mouse.x;
            int mouse_y = ev.mouse.y;

            if (mouse_sobre_botao(mouse_x, mouse_y, botao_play_x, botao_play_y, largura_botao, altura_botao)) {
                iniciar_jogo = true;
                rodando = false;
            }
            else if (mouse_sobre_botao(mouse_x, mouse_y, botao_settings_x, botao_settings_y, largura_botao, altura_botao)) {
                configuracoes(event_queue);  // Passar a event_queue para a tela de configurações
            }
            else if (mouse_sobre_botao(mouse_x, mouse_y, botao_como_jogar_x, botao_como_jogar_y, largura_botao, altura_botao)) {
                como_jogar(display, event_queue);  // Passar o display corretamente
            }
            else if (mouse_sobre_botao(mouse_x, mouse_y, botao_quit_x, botao_quit_y, largura_botao, altura_botao)) {
                rodando = false;
            }
        }

        // Atualizar a tela
        al_draw_bitmap(background, 0, 0, 0);  // Desenhar a imagem de fundo na posição (0, 0)
        al_flip_display();
    }

    // Liberação de recursos
    al_destroy_bitmap(background);
    al_destroy_sample_instance(musicInst);
    al_destroy_sample(music);

    return iniciar_jogo;
}
