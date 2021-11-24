#ifndef GRAFIKA_H_INCLUDED
#define GRAFIKA_H_INCLUDED
#include <SDL2/SDL_ttf.h>
#define FONT "LiberationSerif-Regular.ttf"
#include "debugmalloc.h"

enum
{
    KEPERNYO_SZELESSEGE = 800,
    KEPERNYO_MAGASSAGA = 600,
    PALYA_SZELESSEG = 640,
    PALYA_MAGASSAG = 480,
    MEZOKSZAMA_X = 32,
    MEZOKSZAMA_Y = (MEZOKSZAMA_X/4*3),
    CELLA_MERET = (PALYA_SZELESSEG/MEZOKSZAMA_X)
};


typedef struct Grafika
{
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    SDL_Texture *hatter;
    SDL_Texture *hatter2;
    SDL_Texture *hatter3;
    SDL_Texture *hatter4;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
}Grafika;

#include "main.h"
void nev_beker_szoveg(Grafika *g);
void menuhatter_kirajzol(Grafika *g);
void ujjatekkezdese_hatter_kirajzol(Grafika *g);
void ketjatekos_ujjatekkezdese_hatter_kirajzol(Grafika *g,Jatekosok jatekos,Jatekosok jatekos2);
void toplista_hatter_kirajzol(Grafika *g);
void palyat_lerajzol(Grafika *g);
void pontok_kiirasa(Jatekosok jatekos,Grafika *g);
void pontok_kiirasa_ketjatekos(Jatekosok jatekos,Jatekosok jatekos2,Grafika *g);
void toplista_kiirasa(Jatekosok *jatekosok,Grafika *g);
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);
#endif // GRAFIKA_H_INCLUDED
