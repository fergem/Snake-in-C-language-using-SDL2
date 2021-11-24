#ifndef ALMA_H_INCLUDED
#define ALMA_H_INCLUDED
#include "debugmalloc.h"

typedef struct Alma
{
    int x,y;
}Alma;

#include "kigyo.h"
void almat_lerajzol(SDL_Renderer *renderer, Alma *alma);
void alma_generalas(Alma *alma);


#endif // ALMA_H_INCLUDED
