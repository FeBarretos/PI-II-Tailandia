#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "fase_2.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// Função da Fase 2
void fase_2(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_BITMAP* sprite = al_load_bitmap("personagem_jogavel.png");
    ALLEGRO_BITMAP* background = al_load_bitmap("mapa_coliseu.png");
    ALLEGRO_BITMAP* vaca = al_load_bitmap("vaca.png");
    ALLEGRO_BITMAP* vida = al_load_bitmap("vida_coracao.png");
    ALLEGRO_BITMAP* questaovaca = al_load_bitmap("questao1coliseu.png");
    ALLEGRO_BITMAP* questaocavalo = al_load_bitmap("questao2coliseu.png");

    if (!sprite || !background || !vaca || !vida || !questaovaca || !questaocavalo) {
        fprintf(stderr, "Falha ao carregar os bitmaps\n");
        return;
    }
    ALLEGRO_FONT* fonte = al_load_ttf_font("LiberationSans-Regular.ttf", 24, 0);
    if (!fonte) {
        fprintf(stderr, "Falha ao carregar a fonte\n");
        return;
    }


    // Obter dimensões do sprite
    int sprite_width = 60; // largura do sprite
    int sprite_height = 91; // altura do sprite

    // Dimensões do display
    int display_width = al_get_display_width(display);
    int display_height = al_get_display_height(display);

    // contador de vida e de erro
    extern int contVida;
    int contFase = 0;

    //controle de pergurnta
    bool perguntavaca = false;
    bool perguntacavalo = false;
    
    // Largura e altura dos botões (ajustar conforme necessário)
    int largura_botao = 400, altura_botao = 50;

    int botao_r1_x = 200, botao_r1_y = 200; // Coordenadas da resposta 1
    int botao_r2_x = 200, botao_r2_y = 300; // Coordenadas da resposta 2
    int botao_r3_x = 200, botao_r3_y = 350; // Coordenadas da resposta 3
    int botao_r4_x = 200, botao_r4_y = 450; // Coordenadas da resposta 4

    float frame = 0.f;
    int pos_x = 450, pos_y = 400;
    int current_frame_y = 210;
    int key[4] = { 0, 0, 0, 0 };
    double last_time = al_get_time();
    const float FRAME_DURATION = 1.0 / 60.0;


   
    bool playing = true;
    while (playing) {
        ALLEGRO_EVENT ev;
        while (al_get_next_event(event_queue, &ev)) {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                playing = false;
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_RIGHT: key[0] = 1; current_frame_y = 182; break;
                case ALLEGRO_KEY_LEFT: key[1] = 1; current_frame_y = 91; break;
                case ALLEGRO_KEY_DOWN: key[2] = 1; current_frame_y = 0; break;
                case ALLEGRO_KEY_UP: key[3] = 1; current_frame_y = 273; break;
                }
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_RIGHT: key[0] = 0; break;
                case ALLEGRO_KEY_LEFT: key[1] = 0; break;
                case ALLEGRO_KEY_DOWN: key[2] = 0; break;
                case ALLEGRO_KEY_UP: key[3] = 0; break;
                }
            }
            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                int mouse_x = ev.mouse.x;
                int mouse_y = ev.mouse.y;
                    

                if (perguntavaca) {
                    // Verificar se o clique foi sobre o botão "reposta 1"
                    if (mouse_sobre_botao(mouse_x, mouse_y, botao_r1_x, botao_r1_y, largura_botao, altura_botao)) {
                        printf("aa");
                        contVida--;
                        pos_x = 450;
                        perguntavaca = false;
                    }
                    // Verificar se o clique foi sobre o botão "reposta 2"
                    else if (mouse_sobre_botao(mouse_x, mouse_y, botao_r2_x, botao_r2_y, largura_botao, altura_botao)) {
                        printf("bb");
                        contFase = 1;
                        perguntavaca = false;
                        pos_x = 450;
                    }
                    // Verificar se o clique foi sobre o botão "reposta 3"
                    else if (mouse_sobre_botao(mouse_x, mouse_y, botao_r3_x, botao_r3_y, largura_botao, altura_botao)) {
                        printf("cc");
                        contVida--;
                        pos_x = 450;
                        perguntavaca = false;
                    }
                    // Verificar se o clique foi sobre o botão "reposta 4"
                    else if (mouse_sobre_botao(mouse_x, mouse_y, botao_r4_x, botao_r4_y, largura_botao, altura_botao)) {
                        printf("dd");
                        contVida--;
                        pos_x = 450;
                        perguntavaca = false;
                    }
                }
                else if (perguntacavalo) {
                    // Verificar se o clique foi sobre o botão "reposta 1 do cavalo"
                 if (mouse_sobre_botao(mouse_x, mouse_y, botao_r1_x, botao_r1_y, largura_botao, altura_botao)) {
                    printf("aa");
                    contVida--;
                    pos_x = 450;
                    perguntacavalo = false;
                }
                // Verificar se o clique foi sobre o botão "reposta 2 do cavalo"
                else if (mouse_sobre_botao(mouse_x, mouse_y, botao_r2_x, botao_r2_y, largura_botao, altura_botao)) {
                    printf("bb");
                    contVida--;
                    perguntacavalo = false;
                    pos_x = 450;
                }
                // Verificar se o clique foi sobre o botão "reposta 3 do cavalo"
                else if (mouse_sobre_botao(mouse_x, mouse_y, botao_r3_x, botao_r3_y, largura_botao, altura_botao)) {
                    printf("cc");
                    pos_x = 450;
                    perguntacavalo = false;
                    contFase = 2;
                }
                // Verificar se o clique foi sobre o botão "reposta 4 do cavalo"
                else if (mouse_sobre_botao(mouse_x, mouse_y, botao_r4_x, botao_r4_y, largura_botao, altura_botao)) {
                    printf("dd");
                    contVida--;
                    pos_x = 450;
                    perguntacavalo = false;
                    }
                }

            }
        }

        double current_time = al_get_time();
        if (current_time - last_time >= FRAME_DURATION) {
            // Atualiza a posição do sprite baseado nas teclas pressionadas
            if (key[0]) pos_x += 5; // Direita
            if (key[1]) pos_x -= 5; // Esquerda
            //if (key[2]) pos_y += 5; // Baixo
            //if (key[3]) pos_y -= 5; // Cima

            // Lógica de colisão com os limites do display
            if (pos_x < 0) pos_x = 0;
            if (pos_x > display_width - sprite_width) pos_x = display_width - sprite_width; // Limite direito
            if (pos_y < 0) pos_y = 0;
            if (pos_y > display_height - sprite_height) pos_y = display_height - sprite_height; // Limite inferior

            frame += 0.04f; // Atualiza a animação
            if (frame >= 4) {
                frame -= 4;
            }

            //colisão
            if (contFase == 0) {
                if (pos_x >= 200 && pos_x < 700) {
                    pos_y = 400;
                }
                else {
                    pos_y = 420;
                }
                if (pos_x > 719) {
                    pos_x = 720;
                }
            }
            //fim colisão
            //colisão após acertar a pergunta 1
            if (contFase == 1) {
                if (pos_x >= 200 && pos_x < 700) {
                    pos_y = 400;
                }
                else {
                    pos_y = 420;
                }
                if (pos_x >= 680) {
                    pos_x = 680;
                }
            }

            //pergunta vaca
            if (pos_x >= 690 && pos_x <= 720) {
             perguntavaca = true;
            }

          
           //prende o jogador na pergunta da vaca
            if (perguntavaca) {
                pos_x = 710;
            }

            //pergunta cavalo
            if (pos_x >= 0 && pos_x <= 180) {
                perguntacavalo = true;
            }

            //prende o jogador na pergunta do cavalo
            if (perguntacavalo) {
                pos_x = 180;
            }

            //passa de fase
            if (contFase >= 2) {
                fase_3(display, event_queue);
            }

            // Encerra o loop do jogo
            if (contVida <= 0) {
                playing = false;
            }


            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_bitmap(background, 0, 0, 0);

            //questão da vaca
            if (perguntavaca) {
                al_draw_bitmap(questaovaca, 0, 0, 0);
            }

            //questão da cavalo
            if (perguntacavalo) {
                al_draw_bitmap(questaocavalo, 0, 0, 0);
            }

            // Exibir texto das vidas
            char textoVidas[50];
            snprintf(textoVidas, 50, "        X %d", contVida);
            al_draw_text(fonte, al_map_rgb(255, 0, 0), 5, 45, ALLEGRO_ALIGN_LEFT, textoVidas);
            
            // Definir o tamanho desejado 
            float escala_x = 0.15f; // % do tamanho original
            float escala_y = 0.15f; // % do tamanho original

            float escala_xvaca = 0.35f; // % do tamanho original
            float escala_yvaca = 0.40f; // % do tamanho original

            // Obter as dimensões da imagem original
            int largura_coracao = al_get_bitmap_width(vida);
            int altura_coracao = al_get_bitmap_height(vida);
            int largura_vaca = al_get_bitmap_width(vaca);
            int altura_vaca = al_get_bitmap_height(vaca);

            // Coordenadas para onde a imagem será desenhada
            float x = 5;  // Posição X
            float y = 20;  // Posição Y
            float xvaca = 750;  // Posição X
            float yvaca = 350;  // Posição Y

            // Desenha o coração com a escala definida
            al_draw_scaled_bitmap(vida, 0, 0, largura_coracao, altura_coracao, x, y, largura_coracao * escala_x, altura_coracao * escala_y, 0);
            // Desenha a vaca com a escala definida
            al_draw_scaled_bitmap(vaca, 0, 0, largura_vaca, altura_vaca, xvaca, yvaca, largura_vaca * escala_xvaca, altura_vaca * escala_yvaca, 0);

            al_draw_bitmap_region(sprite, 60 * (int)frame, current_frame_y, sprite_width, sprite_height, pos_x, pos_y, 0);
            al_flip_display();
            last_time = current_time;


        }
    }
    al_destroy_bitmap(vida);
    al_destroy_bitmap(sprite);
    al_destroy_bitmap(background);
    al_destroy_bitmap(vaca);
    al_destroy_font(fonte);
    al_destroy_bitmap(questaovaca);
    al_destroy_bitmap(questaocavalo);

}