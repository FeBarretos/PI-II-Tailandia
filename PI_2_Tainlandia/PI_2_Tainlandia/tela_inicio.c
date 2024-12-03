#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "tela_inicio.h"
#include "configuracoes.h"
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
    ALLEGRO_BITMAP* comojogar = al_load_bitmap("comojogar.png");
    ALLEGRO_BITMAP* som_on = al_load_bitmap("tela som on.png");
    ALLEGRO_BITMAP* som_off = al_load_bitmap("tela som off.png");
    if (!fundo || !comojogar) {
        fprintf(stderr, "Falha ao carregar a imagem de fundo\n");
        return false;
    }
    //Carrega musica de fundo
    al_reserve_samples(1);
    ALLEGRO_SAMPLE* music = al_load_sample("music.ogg");
    if (!music) {
        fprintf(stderr, "Falha ao carregar a música!\n");
        return false;
    }
    ALLEGRO_SAMPLE_INSTANCE* musicInst = al_create_sample_instance(music);
    al_set_sample_instance_playmode(musicInst, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musicInst, al_get_default_mixer());

    // Largura e altura dos botões (ajustar conforme necessário)
    int largura_botao = 100, altura_botao = 40;

    // Coordenadas dos botões na imagem
    int botao_play_x = 415, botao_play_y = 190; // Coordenadas do botão "Play"
    int botao_settings_x = 415, botao_settings_y = 260; // Coordenadas do botão "Settings"
    int botao_quit_x = 415, botao_quit_y = 400; // Coordenadas do botão "Quit"
    int botao_howtplay_x = 415, botao_howtplay_y = 330; // Coordenadas do botão "como jogar"
    int botao_voltar_x = 415, botao_voltar_y = 470; // Coordenadas do botão "voltar da tela de como jgoar"
    int botao_somOn_x = 415, botao_somOn_y = 260; // Coordenadas do botão "som on"
    int botao_somOff_x = 415, botao_somOff_y = 260; // Coordenadas do botão "som off"
    int botao_ovoltar_x = 415, botao_ovoltar_y = 330; // Coordenadas do botão "voltar da som on"
    int botao_offvoltar_x = 415, botao_offvoltar_y = 330; // Coordenadas do botão "voltar da som off"
    //controle dos botões
    int tela1 = 0;

    int tocandomusic = 0;
    

    bool iniciar_jogo = false;
    bool rodando = true;

    
    if (tocandomusic == 0) {
        al_set_sample_instance_playing(musicInst, true);
    }
    if (tocandomusic == 1) {
        al_set_sample_instance_playing(musicInst, false);
    }

    

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
            if (tela1 == 0) {
                // Verificar se o clique foi sobre o botão "Play"
                if (mouse_sobre_botao(mouse_x, mouse_y, botao_play_x, botao_play_y, largura_botao, altura_botao)) {
                    iniciar_jogo = true;
                    rodando = false;  // Para sair do loop e iniciar o jogo
                }
                // Verificar se o clique foi sobre o botão "Settings"
                else if (mouse_sobre_botao(mouse_x, mouse_y, botao_settings_x, botao_settings_y, largura_botao, altura_botao)) {
                    tela1 = 2;
                }
                // Verificar se o clique foi sobre o botão "Como jogar"
                else if (mouse_sobre_botao(mouse_x, mouse_y, botao_howtplay_x, botao_howtplay_y, largura_botao, altura_botao)) {
                    tela1 = 1;  // Abre o menu de configurações
                }
                // Verificar se o clique foi sobre o botão "Quit"
                else if (mouse_sobre_botao(mouse_x, mouse_y, botao_quit_x, botao_quit_y, largura_botao, altura_botao)) {
                    rodando = false;  // Fecha o programa
                }
            }
            else if (tela1 == 1) {
                if (mouse_sobre_botao(mouse_x, mouse_y, botao_voltar_x, botao_voltar_y, largura_botao, altura_botao)) {
                    tela1 = 0;
                }
            }
            else if (tela1 == 2 ) {
                if (mouse_sobre_botao(mouse_x, mouse_y, botao_somOn_x, botao_somOn_y, largura_botao, altura_botao)) {
                    tela1 = 3;
                    tocandomusic = 1;
                    printf("%d", tocandomusic);
                    al_set_sample_instance_playing(musicInst, false);
                }
                        if (mouse_sobre_botao(mouse_x, mouse_y, botao_ovoltar_x, botao_ovoltar_y, largura_botao, altura_botao)) {
                            tela1 = 0;
                        
                    }
                
            }
            else if (tela1 == 3) {
                if (mouse_sobre_botao(mouse_x, mouse_y, botao_somOff_x, botao_somOff_y, largura_botao, altura_botao)) {
                    tela1 = 2;
                    tocandomusic = 0;
                    printf("%d", tocandomusic);
                    al_set_sample_instance_playing(musicInst, true);
                }
                    if (mouse_sobre_botao(mouse_x, mouse_y, botao_offvoltar_x, botao_offvoltar_y, largura_botao, altura_botao)) {
                        tela1 = 0;

                    }
                
            }
        }

            // Desenhar a tela de início com a imagem de fundo
            if (tela1 == 0) {
                al_draw_bitmap(fundo, 0, 0, 0);  // Desenhar a imagem de fundo na posição (0, 0)
            }
            else if (tela1 == 1) {
                al_draw_bitmap(comojogar, 0, 0, 0);  // Desenhar a imagem de fundo na posição (0, 0)
            }
            else if (tela1 == 2) {
                al_draw_bitmap(som_on, 0, 0, 0);  // Desenhar a imagem de fundo na posição (0, 0)
            }
            else if (tela1 == 3) {
                al_draw_bitmap(som_off, 0, 0, 0);  // Desenhar a imagem de fundo na posição (0, 0)
            }

            al_flip_display();
        }

        al_destroy_bitmap(fundo);  // Limpeza da imagem de fundo
        al_destroy_bitmap(comojogar);
        al_destroy_bitmap(som_on);
        al_destroy_bitmap(som_off);
        al_destroy_sample(music);
        al_destroy_sample_instance(musicInst);
        return iniciar_jogo;
    }
