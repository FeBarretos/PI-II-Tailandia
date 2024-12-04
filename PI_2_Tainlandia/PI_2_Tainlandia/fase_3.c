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
    ALLEGRO_BITMAP* dialogo = al_load_bitmap("dialogo1.png");
    ALLEGRO_BITMAP* tfinal = al_load_bitmap("telafinal.png");
    ALLEGRO_BITMAP* vida = al_load_bitmap("vida_coracao.png");
    ALLEGRO_BITMAP* comojogar = al_load_bitmap("comojogar_poliedros.png");
    ALLEGRO_BITMAP* mapaar = al_load_bitmap("mapa_ar-octaedro.png");
    ALLEGRO_BITMAP* qar = al_load_bitmap("questaoar.png");
    ALLEGRO_BITMAP* mapafogo = al_load_bitmap("mapafogo.png");
    ALLEGRO_BITMAP* qfogo = al_load_bitmap("qfogo.png");
    ALLEGRO_BITMAP* mapaterra = al_load_bitmap("mapaterra.png");
    ALLEGRO_BITMAP* qterra = al_load_bitmap("qterra.png");
    ALLEGRO_BITMAP* mapaagua = al_load_bitmap("mapaagua.png");
    ALLEGRO_BITMAP* qagua = al_load_bitmap("qagua.png");
    if (!sprite || !background || !pergunta || !tfinal || !vida) {
        fprintf(stderr, "Falha ao carregar os bitmaps\n");
        return;
    }
    ALLEGRO_FONT* fonte = al_load_ttf_font("LiberationSans-Regular.ttf", 30, 0);
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

    //controle de pergunta
    bool question = false;
    bool question2 = false;
    bool question3 = false;
    bool question4 = false;
    bool question5 = false;
    


    //contador de vida
    extern int contVida;
    int tela = 0;

    // controle dos desenhos de vida
    bool coracao1 = true;
    bool coracao2 = true;
    bool coracao3 = true;


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
                    if (tela == 0) {
                        tela = 1;
                    }
                    if (tela == 1 && question) {
                        tela = 2;
                    }
                    if (tela == 3 && question2) {
                        tela = 4;
                    }
                    if (tela == 5 && question3) {
                        tela = 6;
                    }
                    if (tela == 7 && question4) {
                        tela = 8;
                    }
                    if (tela == 9 && question5) {
                        tela = 10;
                    }
                    if (tela == 11 && question5) {
                        contVida = 0;
                    }

                    break;
                    
                    
                    
                case ALLEGRO_KEY_2:
                     if(tela == 2 || tela == 3 ) {
                      tela = 3;
                      question = false;
                      pos_x = 450, pos_y = 400;  
                  }
                     else if (tela == 4 || tela == 5) {
                         tela = 5;
                         question2 = false;
                         pos_x = 350, pos_y = 200;
                     }
                     else if (tela == 6 || tela == 7) {
                         tela = 7;
                         question3 = false;
                         pos_x = 350, pos_y = 200;
                     }
                     else if (tela == 8 || tela == 9) {
                         tela = 9;
                         question4 = false;
                         pos_x = 450, pos_y = 400;
                     }
                     else if (tela == 10) {
                         tela = 11;
                         
                     }
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

            //colisão 
            if (tela >= 1 && tela <= 2) {

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

                if (question && tela >= 1 && tela <= 2) {
                    pos_y = 290;
                    pos_x = 450;
                }
            }
            else if (tela >= 3 && tela <= 4) {

                if (pos_y <= 275) {
                    pos_y = 275;
                }

                if (pos_x <= 175) {
                    pos_x = 175;
                }

                if (pos_x >= 735) {
                    pos_x = 735;
                }

                if (pos_y > 0 && pos_y <= 350 ) {
                    question2 = true;
                    
                }

                if (question2 ) {
                     pos_y = 350;
                     pos_x = 450;

                }
            }
            else if (tela >= 5 && tela <= 6) {

                if (pos_y <= 275) {
                    pos_y = 275;
                }

                if (pos_x <= 175) {
                    pos_x = 175;
                }

                if (pos_x >= 735) {
                    pos_x = 735;
                }

                if (pos_x >= 590 ) {
                    question3 = true;

                }

                if (question3) {
                    pos_y = 350;
                    pos_x = 590;

                }
            }
            else if (tela >= 7 && tela <= 8) {

                if (pos_y <= 300) {
                    pos_y = 300;
                }

                if (pos_x <= 200) {
                    pos_x = 200;
                }

                if (pos_x >= 735) {
                    pos_x = 735;
                }

                if (pos_x >= 650) {
                    question4 = true;

                }

                if (question4) {
                    pos_y = 350;
                    pos_x = 650;

                }
            }
            else if (tela >= 9 && tela <= 10) {

                if (pos_y <= 300) {
                    pos_y = 300;
                }

                if (pos_x <= 200) {
                    pos_x = 200;
                }

                if (pos_x >= 535) {
                    pos_x = 535;
                }

                if (pos_y <= 300) {
                    question5 = true;

                }

                if (question5) {
                    pos_y = 300;
                    pos_x = 450;

                }
            }
            

            // Encerra o loop do jogo
            if (contVida <= 0) {
                playing = false;
            }
            
            // Definir o tamanho desejado para o coração
            float escala_x = 0.15f; // % do tamanho original
            float escala_y = 0.15f; // % do tamanho original

            // Obter as dimensões da imagem original
            int largura_coracao = al_get_bitmap_width(vida);
            int altura_coracao = al_get_bitmap_height(vida);

            // Coordenadas para onde a imagem será desenhada
            float x1 = 10;  // Posição X coracao 1
            float x2 = 50;  // Posição X coracao 2
            float x3 = 90;  // Posição X coracao 3
            float y = 5;  // Posição Y dos corações

            al_clear_to_color(al_map_rgb(255, 255, 255));
            
               
                if (tela == 0) {
                    al_draw_bitmap(comojogar, 0, 0, 0);
                }
                else if (tela == 1 || tela == 2) {
                    al_draw_bitmap(background, 0, 0, 0);
   
                    if (question) {
                        al_draw_bitmap(dialogo, 250, 400, 0);
                        char question[] = "Aperte 'Enter' para falar";
                        al_draw_text(fonte, al_map_rgb(0, 0, 0), 480, 450, ALLEGRO_ALIGN_CENTER, question);
                    }
                    if (tela == 2) {
                        al_draw_bitmap(pergunta, 250, 400, 0);

                    }
                }
                else if (tela == 3 || tela == 4) {
                   al_draw_bitmap(mapaar, 0, 0, 0);

                   if (question2 && tela == 3) {
                       al_draw_bitmap(dialogo, 250, 240, 0);
                       char question[] = "Aperte 'Enter' para falar";
                       al_draw_text(fonte, al_map_rgb(0, 0, 0), 480, 290, ALLEGRO_ALIGN_CENTER, question);
                   }
                   if (tela == 4) {
                       al_draw_bitmap(qar, 250, 240, 0);

                   }
                }
                else if (tela == 5 || tela == 6) {
                    al_draw_bitmap(mapafogo, 0, 0, 0);

                    if (question3 && tela == 5) {
                        al_draw_bitmap(dialogo, 250, 240, 0);
                        char question[] = "Aperte 'Enter' para falar";
                        al_draw_text(fonte, al_map_rgb(0, 0, 0), 480, 290, ALLEGRO_ALIGN_CENTER, question);
                    }
                    if (tela == 6) {
                        al_draw_bitmap(qfogo, 250, 240, 0);

                    }

                }
                else if (tela == 7 || tela == 8) {
                    al_draw_bitmap(mapaterra, 0, 0, 0);

                    if (question4 && tela == 7) {
                        al_draw_bitmap(dialogo, 250, 240, 0);
                        char question[] = "Aperte 'Enter' para falar";
                        al_draw_text(fonte, al_map_rgb(0, 0, 0), 480, 290, ALLEGRO_ALIGN_CENTER, question);
                    }
                    if (tela == 8) {
                        al_draw_bitmap(qterra, 250, 240, 0);

                    }

                }
                else if (tela == 9 || tela == 10) {
                    al_draw_bitmap(mapaagua, 0, 0, 0);

                    if (question5 && tela == 9) {
                        al_draw_bitmap(dialogo, 250, 190, 0);
                        char question[] = "Aperte 'Enter' para falar";
                        al_draw_text(fonte, al_map_rgb(0, 0, 0), 480, 230, ALLEGRO_ALIGN_CENTER, question);
                    }
                    if (tela == 10) {
                        al_draw_bitmap(qagua, 250, 190, 0);

                    }

                }
                else if (tela == 11) {
                    al_draw_bitmap(tfinal, 0, 0, 0);
                }
         
            //desenho dos corações  
            if (contVida < 3) {
                coracao1 = false;
            }

            if (coracao1) {
                al_draw_scaled_bitmap(vida, 0, 0, largura_coracao, altura_coracao, x1, y, largura_coracao * escala_x, altura_coracao * escala_y, 0);
            }
            else {

            }
            if (contVida < 2) {
                coracao2 = false;
            }

            if (coracao2) {
                al_draw_scaled_bitmap(vida, 0, 0, largura_coracao, altura_coracao, x2, y, largura_coracao * escala_x, altura_coracao * escala_y, 0);
            }

            al_draw_scaled_bitmap(vida, 0, 0, largura_coracao, altura_coracao, x3, y, largura_coracao * escala_x, altura_coracao * escala_y, 0);
            //fim do desenho dos corações

            if (tela > 0 && tela <= 10) { 
                al_draw_bitmap_region(sprite, 60 * (int)frame, current_frame_y, sprite_width, sprite_height, pos_x, pos_y, 0);
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
    al_destroy_bitmap(vida);
    al_destroy_bitmap(dialogo);
    al_destroy_bitmap(comojogar);
    al_destroy_bitmap(mapaar);
    al_destroy_bitmap(qar);
    al_destroy_bitmap(mapafogo);
    al_destroy_bitmap(qfogo);
    al_destroy_bitmap(mapaterra);
    al_destroy_bitmap(qterra);
    al_destroy_bitmap(mapaagua);
    al_destroy_bitmap(qagua);
}