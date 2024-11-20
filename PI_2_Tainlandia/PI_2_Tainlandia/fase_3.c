#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "fase_3.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// Função da Fase 3
void fase_3(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_BITMAP* sprite = al_load_bitmap("personagem_jogavel.png");
    ALLEGRO_BITMAP* background = al_load_bitmap("mapa_cosmo-dodecaedro.png");
    ALLEGRO_BITMAP* pergunta = al_load_bitmap("dialogo.png");
    ALLEGRO_BITMAP* tfinal = al_load_bitmap("telafinal.png");
    if (!sprite || !background || !pergunta || !tfinal) {
        fprintf(stderr, "Falha ao carregar os bitmaps\n");
        return;
    }
    ALLEGRO_FONT* fonte = al_load_ttf_font("LiberationSans-Regular.ttf", 30, 0);
    if (!fonte) {
        fprintf(stderr, "Falha ao carregar a fonte\n");
        return;
    }

    //controle da tela final
    bool terminou = true;

    //controle de enter
    int acabar = 0;

    // Obter dimensões do sprite
    int sprite_width = 60; // largura do sprite
    int sprite_height = 91; // altura do sprite

    // Dimensões do display
    int display_width = al_get_display_width(display);
    int display_height = al_get_display_height(display);

    //controle de pergunta
    bool question = false;
    bool press_enter = false;
    bool ganhou = false;

    //contador de vida
    extern int contVida;

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
                case ALLEGRO_KEY_ENTER: 
                    
                    
                    if (acabar == 0) {
                        press_enter = true, question = false, acabar++ ; break;
                    }
                    
                    else if (acabar == 1) {
                        contVida = 0;
                    }

                case ALLEGRO_KEY_2: ganhou = true;
                }
            }
            
            else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_RIGHT: key[0] = 0; break;
                case ALLEGRO_KEY_LEFT: key[1] = 0; break;
                case ALLEGRO_KEY_DOWN: key[2] = 0; break;
                case ALLEGRO_KEY_UP: key[3] = 0; break;
                case ALLEGRO_KEY_ENTER: acabar = 1 ; break;
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

            //colisão 
            if (pos_y <= 275) {
                pos_y = 275;
            }

            if (pos_x <= 375) {
                pos_x = 375;
            }

            if (pos_x >= 535) {
                pos_x = 535;
            }

            if (pos_y > 0 && pos_y <= 290) {
                question = true;
            }

            if (question) {
                pos_y = 290;
                pos_x = 450;
            }

            if (ganhou) {
                terminou = false;
            }
            // Encerra o loop do jogo
            if (contVida <= 0) {
                playing = false;
            }

            al_clear_to_color(al_map_rgb(255, 255, 255));
            if (terminou) {
                al_draw_bitmap(background, 0, 0, 0);


            
            if (question) {
                al_draw_bitmap(pergunta, 250, 400, 0);
                char question[] = "Aperte 'Enter' para falar";
                al_draw_text(fonte, al_map_rgb(255, 255, 255), 480, 450, ALLEGRO_ALIGN_CENTER, question);
            }
            if (press_enter) {
                al_draw_bitmap(pergunta, 250, 400, 0);
                char question1[] = "qual o resultado de 1 + 1?";
                al_draw_text(fonte, al_map_rgb(255, 255, 255), 480, 450, ALLEGRO_ALIGN_CENTER, question1);
            }
              
            al_draw_bitmap_region(sprite, 60 * (int)frame, current_frame_y, sprite_width, sprite_height, pos_x, pos_y, 0);
            }
            else {
                al_draw_bitmap(tfinal, 0, 0, 0);
            }
            al_flip_display();
            last_time = current_time;


        }
    }

    al_destroy_bitmap(sprite);
    al_destroy_bitmap(background);
    al_destroy_bitmap(pergunta);
    al_destroy_font(fonte);
    al_destroy_bitmap(tfinal);    
}