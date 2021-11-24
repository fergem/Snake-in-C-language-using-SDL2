#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "kigyo.h"
#include "alma.h"
#include "debugmalloc.h"



void kigyot_lerak(int KEZDOPONTX,int KEZDOPONTY,Test **fej,int meret)
{
    *fej = malloc(sizeof(Test));
    Test *p = *fej;
    for(int i = 0;i<meret;i++)
    {
        p->kov = malloc(sizeof(Test));
        p->x = KEZDOPONTX - i;
        p->y = KEZDOPONTY;
        p = p->kov;
    }
    p->x = KEZDOPONTX - meret;
    p->y = KEZDOPONTY;
    p->kov = NULL;
}

void kigyot_lerajzol(Test *kigyo,Test *kigyo2,SDL_Renderer *renderer)
{

    for (Test *p = kigyo;p != NULL; p = p->kov)
    {
        SDL_Rect kigyo_cella =
        {
            p->x * 20 + 80,
            p->y * 20 + 60,
            20, 20
        };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &(kigyo_cella));

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &(kigyo_cella));

    }
    if(kigyo2 != NULL)
    {
        for (Test *p = kigyo2;p != NULL; p = p->kov)
        {
            SDL_Rect kigyo_cella =
            {
                p->x * 20 + 80,
                p->y * 20 + 60,
                20, 20
            };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &(kigyo_cella));

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &(kigyo_cella));

        }
    }
}

void kigyo_mozgas(Test *kigyo,Irany i)
{
    Test *ptr = kigyo;
    int tmpx1,tmpx2,tmpy1,tmpy2;
    tmpx1 = ptr->x;
    tmpy1 = ptr->y;
    for(ptr = kigyo; ptr->kov != NULL; ptr = ptr->kov)
    {
        tmpx2 = ptr->kov->x;
        ptr->kov->x = tmpx1;
        tmpx1 = tmpx2;

        tmpy2 = ptr->kov->y;
        ptr->kov->y = tmpy1;
        tmpy1 = tmpy2;
    }
    fej_mozgas(kigyo,i);
}

void fej_mozgas(Test *kigyo,Irany i)
{
    switch(i)
    {
        case JOBBRA:
            kigyo->x++;
            break;
        case BALRA:
            kigyo->x--;
            break;
        case FEL:
            kigyo->y--;
            break;
        case LE:
            kigyo->y++;
            break;
    }
}

void billentyu_kezel(SDL_Event e,Irany *i1,Irany *i2,Irany *ei1,Irany *ei2,State *state)
{
    if(*state == EGYJATEKOSMOD)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_a:
                if(*ei1 != JOBBRA)
                    *i1 = BALRA;
                break;
            case SDLK_d:
                if(*ei1 != BALRA)
                    *i1 = JOBBRA;
                break;
            case SDLK_w:
                if(*ei1 != LE)
                    *i1 = FEL;
                break;
            case SDLK_s:
                if(*ei1 != FEL)
                    *i1 = LE;
                break;
        }
    }
    if(*state == KETJATEKOSMOD)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_a:
                if(*ei1 != JOBBRA)
                    *i1 = BALRA;
                break;
            case SDLK_d:
                if(*ei1 != BALRA)
                    *i1 = JOBBRA;
                break;
            case SDLK_w:
                if(*ei1 != LE)
                    *i1 = FEL;
                break;
            case SDLK_s:
                if(*ei1 != FEL)
                    *i1 = LE;
                break;
            case SDLK_LEFT:
                if(*ei2 != JOBBRA)
                    *i2 = BALRA;
                break;
            case SDLK_RIGHT:
                if(*ei2 != BALRA)
                    *i2 = JOBBRA;
                break;
            case SDLK_UP:
                if(*ei2 != LE)
                    *i2 = FEL;
                break;
            case SDLK_DOWN:
                if(*ei2 != FEL)
                    *i2 = LE;
                break;
        }
    }
}

void testet_ad_hozza(Test *kigyo)
{
    Test *uj;
    uj = (Test*) malloc(sizeof(Test));

    Test *mozgo = kigyo;
    while (mozgo->kov != NULL)
        mozgo = mozgo->kov;
    mozgo->kov = uj;
    uj->x = mozgo->x;
    uj->y = mozgo->y;
    uj->kov = NULL;
}

bool utkozes(Test *kigyo,Test *kigyo2,Alma *alma, Jatekosok *jatekos)
{
    bool jatekvege = false;

    if(kigyo->x == (alma->x/20) && kigyo->y == (alma->y/20))
        {
            testet_ad_hozza(kigyo);
            alma_generalas(alma);
            jatekos->pont++;
        }

    if(kigyo->x<0 || kigyo->x>31 || kigyo->y<0 || kigyo->y>23)
        jatekvege = true;

    Test *mozgo = kigyo->kov;
    while (mozgo != NULL)
    {
        if(kigyo->x == mozgo->x && kigyo->y == mozgo->y)
            jatekvege = true;
        mozgo = mozgo->kov;
    }

    if(kigyo2 != NULL)
    {
        while (kigyo2 != NULL)
        {
            if(kigyo->x == kigyo2->x && kigyo->y == kigyo2->y)
                jatekvege = true;
            kigyo2 = kigyo2->kov;
        }
    }
    return jatekvege;
}

void felszabadit(Test *kigyo)
{
    Test *iter = kigyo;
    while (iter != NULL)
    {
        Test *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}
