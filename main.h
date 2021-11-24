#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdbool.h>
#include "debugmalloc.h"


typedef enum State
{
        MENUBEN,
        EGYJATEKOSMOD,
        KETJATEKOSMOD,
        TOPLISTA,
        UJJATEKKEZDESE,
        NEVBEIRAS,
        KETJATEKOSUJJATEKKEZDESE,
        KILEPES
}State;

typedef enum Gyoztes
{
    nincs,
    piros,
    zold,
    dontetlen
}Gyoztes;

typedef struct Jatekosok
{
    char nev[128];
    int pont;

}Jatekosok;


typedef struct Gomb
{
    SDL_Rect rect;
    bool lenyomva;
}Gomb;

#include "grafika.h"
void sdl_init(int szeles, int magas,Grafika *g);
void pontok_beolvas(Jatekosok *jatekosok);
bool rekord_e(Jatekosok *jatekosok,Jatekosok jatekos);
void pontok_mentese(Jatekosok *jatekos);
bool gombnyomas(Gomb *btn);
void gomb_tortenes(Gomb *gmb, const SDL_Event *ev);
Uint32 idozit(Uint32 ms, void *param);
#endif // MAIN_H_INCLUDED
