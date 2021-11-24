#ifndef KIGYO_H_INCLUDED
#define KIGYO_H_INCLUDED
#include "debugmalloc.h"

typedef struct Test
{
    int x,y;
    struct Test *kov;

}Test;

typedef enum Irany{JOBBRA,BALRA,FEL,LE}Irany;

#include "alma.h"
#include "main.h"

void testet_ad_hozza(Test *kigyo);
void kigyo_mozgas(Test *kigyo,Irany i);
void kigyot_lerak(int KEZDOPONTX,int KEZDOPONTY,Test **fej,int meret);
void fej_mozgas(Test *kigyo,Irany i);
void kigyot_lerajzol(Test *kigyo,Test *kigyo2,SDL_Renderer *renderer);
void billentyu_kezel(SDL_Event e,Irany *i1,Irany *i2,Irany *ei1,Irany *ei2,State *state);
bool utkozes(Test *kigyo,Test *kigyo2,Alma *alma, Jatekosok *jatekos);
void felszabadit(Test *kigyo);

#endif // KIGYO_H_INCLUDED
