#include <SDL2/SDL.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "alma.h"
#include "main.h"


const SDL_Color PIROS = { .r = 255, .g = 0, .b = 0, .a = 255 };
const SDL_Color BORDO =  { .r = 162, .g = 4, .b = 4, .a = 255 };


void almat_lerajzol(SDL_Renderer *renderer, Alma *alma)
{
    SDL_Rect alma_cella =
    {
        alma->x+80  ,  alma->y+60 ,
        CELLA_MERET, CELLA_MERET
    };
    SDL_SetRenderDrawColor(renderer, PIROS.r, PIROS.g, PIROS.b, PIROS.a);
    SDL_RenderFillRect(renderer, &alma_cella);
    SDL_SetRenderDrawColor(renderer, BORDO.r, BORDO.g, BORDO.b, BORDO.r);
    SDL_RenderDrawRect(renderer, &alma_cella);

}

void alma_generalas(Alma *alma)
{
    alma->x = ((rand() % MEZOKSZAMA_X)*CELLA_MERET);
    alma->y = ((rand() % MEZOKSZAMA_Y)*CELLA_MERET);
}

