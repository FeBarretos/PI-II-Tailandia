#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "jogo.h"

void jogo(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_BITMAP* sprite = al_load_bitmap("bonequinho.png");
    ALLEGRO_BITMAP* background = al_load_bitmap("fundo_teste.png");
    if (!sprite || !background) {
        fprintf(stderr, "Falha ao carregar os bitmaps\n");
        return;
    }

    float frame = 0.f;
    int pos_x = 250, pos_y = 400;
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
                case ALLEGRO_KEY_RIGHT: key[0] = 1; current_frame_y = 210; break;
                case ALLEGRO_KEY_LEFT: key[1] = 1; current_frame_y = 105; break;
                case ALLEGRO_KEY_DOWN: key[2] = 1; current_frame_y = 0; break;
                case ALLEGRO_KEY_UP: key[3] = 1; current_frame_y = 315; break;
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
            if (key[0]) pos_x += 10;
            if (key[1]) pos_x -= 10;
            if (key[2]) pos_y += 10;
            if (key[3]) pos_y -= 10;

            frame += 0.04f;
            if (frame > 4) {
                frame -= 4;
            }

            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap_region(sprite, 92 * (int)frame, current_frame_y, 92, 105, pos_x, pos_y, 0);
            al_flip_display();
            last_time = current_time;
        }
    }

    al_destroy_bitmap(sprite);
    al_destroy_bitmap(background);
}
