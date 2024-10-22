#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "jogo.h"

void jogo(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_BITMAP* sprite = al_load_bitmap("personagem_jogavel.png");
    ALLEGRO_BITMAP* background = al_load_bitmap("mapa1_sem_guarda.png");
    ALLEGRO_BITMAP* fase1 = al_load_bitmap("fundo_tela_teste.png");

    if (!sprite || !background || !fase1) {
        fprintf(stderr, "Falha ao carregar os bitmaps\n");
        return;
    }

    // Obter dimensões do sprite
    int sprite_width = 60; // largura do sprite
    int sprite_height = 91; // altura do sprite

    // Dimensões do display
    int display_width = al_get_display_width(display);
    int display_height = al_get_display_height(display);

    //controle de fundo
    ALLEGRO_BITMAP* fundo_atual = background;


    float frame = 0.f;
<<<<<<< Updated upstream
    int pos_x = 450, pos_y = 650;
=======
    int pos_x = 450, pos_y = 200;
>>>>>>> Stashed changes
    int current_frame_y = 210;
    int key[4] = { 0, 0, 0, 0 };
    double last_time = al_get_time();
    const float FRAME_DURATION = 1.0 / 60.0;

    int mapy = pos_y ;

    bool playing = true;
    bool playing2 = false;
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

            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap_region(sprite, 60 * (int)frame, current_frame_y, sprite_width, sprite_height, pos_x, pos_y, 0);
            al_flip_display();
            last_time = current_time;


            if (pos_y < 150 && pos_x > 400 && pos_x < 500) {
                
                playing = false;
                playing2 = true;
            }
           
        }
    }
    
    
    
    al_destroy_bitmap(sprite);
    al_destroy_bitmap(background);
    al_destroy_bitmap(fase1);
   
}
