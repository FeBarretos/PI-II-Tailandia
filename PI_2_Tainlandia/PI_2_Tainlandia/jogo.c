#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "jogo.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


void jogo(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_BITMAP* sprite = al_load_bitmap("personagem_jogavel.png");
    ALLEGRO_BITMAP* background = al_load_bitmap("mapa1_bhaskara.png");
    ALLEGRO_BITMAP* vida = al_load_bitmap("vida_coracao.png");
    ALLEGRO_BITMAP* caixa_dialogo = al_load_bitmap("caixa_dialogo.png");
    if (!sprite || !background || !vida || !caixa_dialogo) {
        fprintf(stderr, "Falha ao carregar os bitmaps\n");
        return;
    }
    ALLEGRO_FONT* fonte = al_load_ttf_font("LiberationSans-Regular.ttf", 24, 0);
    if (!fonte) {
        fprintf(stderr, "Falha ao carregar a fonte\n");
        return ;
    }

    // contador de vida e de erro
    extern int contVida;
    int contFase = 0;

    // controle de pergunta
    bool mostrando_pergunta = false;
    bool mostrando_pergunta2 = false;
    bool mostrando_pergunta3 = false;

    //controle de respostas
    bool mostrando_resposta1 = false;
    bool mostrando_resposta2 = false;
    bool mostrando_resposta3 = false;

    bool mostrando_resposta4 = false;
    bool mostrando_resposta5 = false;
    bool mostrando_resposta6 = false;

    bool mostrando_resposta7 = false;
    bool mostrando_resposta8 = false;
    bool mostrando_resposta9 = false;

    
    // Variáveis para mensagens contextuais
    char mensagem[50] = "";
    double tempoMensagem = 0;

   

    // Obter dimensões do sprite
    int sprite_width = 60; // largura do sprite
    int sprite_height = 91; // altura do sprite

    // Dimensões do display
    int display_width = al_get_display_width(display);
    int display_height = al_get_display_height(display);

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
        }

        double current_time = al_get_time();
        if (current_time - last_time >= FRAME_DURATION) {
            // Atualiza a posição do sprite baseado nas teclas pressionadas
            if (key[0]) pos_x += 5; // Direita
            if (key[1]) pos_x -= 5; // Esquerda
            if (key[2]) pos_y += 5; // Baixo
            if (key[3]) pos_y -= 5; // Cima

            // Lógica de colisão com os limites do display
            if (pos_x < 0) pos_x = 0;
            if (pos_x > display_width - sprite_width) pos_x = display_width - sprite_width; // Limite direito
            if (pos_y < 0) pos_y = 0;
            if (pos_y > display_height - sprite_height) pos_y = display_height - sprite_height; // Limite inferior

            frame += 0.04f; // Atualiza a animação
            if (frame >= 4) {
                frame -= 4;
            }

            //porta 1
            if (pos_y < 125 && pos_x > 200 && pos_x < 300) {
                if (contFase == 1) {
                    contFase = 2;
                    pos_x = 450;
                    pos_y = 600;
                    printf("%d", contFase);
                }
                else {
                    pos_x = 450;
                    pos_y = 600;
                    contVida--;
                }
            }

            //porta 2
            if (pos_y < 125 && pos_x > 400 && pos_x < 500) {
                if (contFase == 0) {
                    contFase = 1;
                    pos_x = 450;
                    pos_y = 600;
                    printf("%d", contFase);
                }
                else {
                    pos_x = 450;
                    pos_y = 600;
                    contVida--;

                }
            }

            //porta 3
            if (pos_y < 125 && pos_x > 600 && pos_x < 700) {
                if (contFase == 2) {
                    fase_2(display, event_queue);
                }
                else {
                    pos_x = 450;
                    pos_y = 600;
                    contVida--;

                }
            }
            // Encerra o loop do jogo
            if (contVida <= 0) {
                playing = false;  
            }
            //evita colidir com a parede
            if(pos_y <= 124) {
                pos_y = 124;
            }

            if (pos_x <= 100) {
                pos_x = 100;
            }

            if (pos_x >= 800) {
                pos_x = 800;
            }
            // colisão com o bhaskara
            if (pos_y >= 325 && pos_y < 370 && pos_x > 270 && pos_x < 340) {
                pos_y = 350;
            }
            //pergunta 1 
            if (pos_y > 325 && pos_y < 370  && pos_x > 270 && pos_x < 340 && contFase == 0) {
                mostrando_pergunta = true;
            }
            else {
                mostrando_pergunta = false;
            }
           
            //pergunta 2
            if (pos_y > 325 && pos_y < 370 && pos_x > 270 && pos_x < 340 && contFase == 1) {
                mostrando_pergunta2 = true;
            }
            else {
                mostrando_pergunta2 = false;
            }

            //pergunta 3 
            if (pos_y > 325 && pos_y < 370 && pos_x > 270 && pos_x < 340 && contFase == 2) {
                mostrando_pergunta3 = true;
            }
            else {
                mostrando_pergunta3 = false;
            }


            //mostra respostas da pergunta 1
            if (contFase == 0) {
                if (pos_y > 150 && pos_y < 240 && pos_x > 200 && pos_x < 300) {
                    mostrando_resposta1 = true;
                }
                else {
                    mostrando_resposta1 = false;
                }

                //mostra respostas da pergunta 2
                if (pos_y > 150 && pos_y < 240 && pos_x > 400 && pos_x < 500) {
                    mostrando_resposta2 = true;
                }
                else {
                    mostrando_resposta2 = false;
                }

                //mostra respostas da pergunta 3
                if (pos_y > 150 && pos_y < 240 && pos_x > 600 && pos_x < 700) {
                    mostrando_resposta3 = true;
                }
                else {
                    mostrando_resposta3 = false;
                }
            }

            
            if (contFase == 1) {
                //mostra respostas da pergunta 4
                if (pos_y > 150 && pos_y < 240 && pos_x > 200 && pos_x < 300) {
                    mostrando_resposta4 = true;
                }
                else {
                    mostrando_resposta4 = false;
                }

                //mostra respostas da pergunta 5
                if (pos_y > 150 && pos_y < 240 && pos_x > 400 && pos_x < 500) {
                    mostrando_resposta5 = true;
                }
                else {
                    mostrando_resposta5 = false;
                }

                //mostra respostas da pergunta 6
                if (pos_y > 150 && pos_y < 240 && pos_x > 600 && pos_x < 700) {
                    mostrando_resposta6 = true;
                }
                else {
                    mostrando_resposta6 = false;
                }
            }

            if (contFase == 2) {
                //mostra respostas da pergunta 7
                if (pos_y > 150 && pos_y < 240 && pos_x > 200 && pos_x < 300) {
                    mostrando_resposta7 = true;
                }
                else {
                    mostrando_resposta7 = false;
                }

                //mostra respostas da pergunta 8
                if (pos_y > 150 && pos_y < 240 && pos_x > 400 && pos_x < 500) {
                    mostrando_resposta8 = true;
                }
                else {
                    mostrando_resposta8 = false;
                }

                //mostra respostas da pergunta 9
                if (pos_y > 150 && pos_y < 240 && pos_x > 600 && pos_x < 700) {
                    mostrando_resposta9 = true;
                }
                else {
                    mostrando_resposta9 = false;
                }
            }

            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_bitmap(background, 0, 0, 0);

           
            if (mostrando_pergunta) {
                al_draw_bitmap(caixa_dialogo, 0, 0, 0);
                // Exibi a pergunta
                char textoPergunta1[] = "Questao 1 - Usando Bhaskara, qual o resultado da equacao?";
                char ctextoPergunta1[] = "3x(ao quadrado) - 15x + 12 = 0";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 265, ALLEGRO_ALIGN_CENTER, textoPergunta1);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 285, ALLEGRO_ALIGN_CENTER, ctextoPergunta1);
            }

            if (mostrando_pergunta2) {
                al_draw_bitmap(caixa_dialogo, 0, 0, 0);
                // Exibi a pergunta
                char textoPergunta2[] = "Questao 2 - Usando Bhaskara, qual o resultado da equacao?";
                char ctextoPergunta2[] = "x(ao quadrado) + 5x - 14 = 0";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 265, ALLEGRO_ALIGN_CENTER, textoPergunta2);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 285, ALLEGRO_ALIGN_CENTER, ctextoPergunta2);
            }

            if (mostrando_pergunta3) {
                al_draw_bitmap(caixa_dialogo, 0, 0, 0);
                // Exibi a pergunta
                char textoPergunta3[] = "Questao 3 - Usando Bhaskara, qual o resultado da equacao?";
                char ctextoPergunta3[] = "x(ao quadrado) + 2x - 15 = 0";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 265, ALLEGRO_ALIGN_CENTER, textoPergunta3);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 285, ALLEGRO_ALIGN_CENTER, ctextoPergunta3);
            }
           
           //mostra respostas primeira pergunta
            if (mostrando_resposta1) {
                al_draw_bitmap(caixa_dialogo, 0, 100, 0);
                char reposta1[] = "seria 6 e 12 ?";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 365, ALLEGRO_ALIGN_CENTER,reposta1);
            }
            
           
            if (mostrando_resposta2) {
                al_draw_bitmap(caixa_dialogo, 0, 100, 0);
                char reposta2[] = "seria 1 e 4 ?";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 365, ALLEGRO_ALIGN_CENTER, reposta2);
            }
          
            if (mostrando_resposta3) {
                al_draw_bitmap(caixa_dialogo, 0, 100, 0);
                char reposta3[] = "seria 5 e 4 ?";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 365, ALLEGRO_ALIGN_CENTER, reposta3);
            }

            //mostra respostas segunda pergunta
            if (mostrando_resposta4) {
                al_draw_bitmap(caixa_dialogo, 0, 100, 0);
                char reposta4[] = "seria 2 e -7 ?";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 365, ALLEGRO_ALIGN_CENTER, reposta4);
            }


            if (mostrando_resposta5) {
                al_draw_bitmap(caixa_dialogo, 0, 100, 0);
                char reposta5[] = "seria 1 e -7 ?";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 365, ALLEGRO_ALIGN_CENTER, reposta5);
            }

            if (mostrando_resposta6) {
                al_draw_bitmap(caixa_dialogo, 0, 100, 0);
                char reposta6[] = "seria 7 e 9 ?";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 365, ALLEGRO_ALIGN_CENTER, reposta6);
            }

            //mostra respostas terceira pergunta
            if (mostrando_resposta7) {
                al_draw_bitmap(caixa_dialogo, 0, 100, 0);
                char reposta7[] = "seria 7 e –8 ?";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 365, ALLEGRO_ALIGN_CENTER, reposta7);
            }


            if (mostrando_resposta8) {
                al_draw_bitmap(caixa_dialogo, 0, 100, 0);
                char reposta8[] = "seria -9 e 4 ?";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 365, ALLEGRO_ALIGN_CENTER, reposta8);
            }

            if (mostrando_resposta9) {
                al_draw_bitmap(caixa_dialogo, 0, 100, 0);
                char reposta9[] = "seria 3 e -5 ?";
                al_draw_text(fonte, al_map_rgb(0, 0, 0), 590, 365, ALLEGRO_ALIGN_CENTER, reposta9);
            }

            // Exibir texto das vidas
            char textoVidas[50];
            snprintf(textoVidas, 50, "        X %d", contVida);
            al_draw_text(fonte, al_map_rgb(255, 0, 0), 5, 35, ALLEGRO_ALIGN_LEFT, textoVidas);

            // Definir o tamanho desejado para o coração
            float escala_x = 0.15f; // 20% do tamanho original
            float escala_y = 0.15f; // 20% do tamanho original

            // Obter as dimensões da imagem original
            int largura_coracao = al_get_bitmap_width(vida);
            int altura_coracao = al_get_bitmap_height(vida);

            // Coordenadas para onde a imagem será desenhada
            float x = 10;  // Posição X
            float y = 5;  // Posição Y

            // Desenhar o coração com a escala definida
            al_draw_scaled_bitmap(vida, 0, 0, largura_coracao, altura_coracao, x, y, largura_coracao * escala_x, altura_coracao * escala_y, 0);



            al_draw_bitmap_region(sprite, 60 * (int)frame, current_frame_y, sprite_width, sprite_height, pos_x, pos_y, 0);
            al_flip_display();
            last_time = current_time;

        }
    }
    al_destroy_bitmap(vida);
    al_destroy_bitmap(sprite);
    al_destroy_bitmap(background);
    al_destroy_bitmap(caixa_dialogo);
    al_destroy_font(fonte);
}