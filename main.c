#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>

#include "debugmalloc.h"

#include "main.h"
#include "kigyo.h"
#include "grafika.h"
#include "alma.h"

Gomb egyjatekos =
{
    .rect = { .x = 350, .y = 200, .w = 400, .h = 75 }
};
Gomb ketjatekos =
{
    .rect = { .x = 350, .y = 325, .w = 400, .h = 75 }
};
Gomb ujjatek =
{
    .rect = { .x = 30, .y = 250, .w = 300, .h = 90 }
};
Gomb menube =
{
    .rect = { .x = 30, .y = 350, .w = 300, .h = 90 }
};
Gomb toplistabolmenube =
{
    .rect = { .x = 225, .y = 25, .w = 350, .h = 100 }
};
Gomb menuboltoplistaba =
{
    .rect = { .x = 350, .y =450, .w = 400, .h = 75 }
};
Gomb ketjatekos_ujjatek =
{
    .rect = { .x = 100 , .y =375, .w = 250, .h = 150 }
};
Gomb ketjatekos_menube =
{
    .rect = { .x = 450 , .y =375, .w = 250, .h = 150 }
};

void gomb_tortenes(Gomb *gmb, const SDL_Event *e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        if(e->button.button == SDL_BUTTON_LEFT
            && e->button.x >= gmb->rect.x && e->button.x <= (gmb->rect.x + gmb->rect.w)
            && e->button.y >= gmb->rect.y && e->button.y <= (gmb->rect.y + gmb->rect.h))
                gmb->lenyomva = true;

    }
}

bool gombnyomas(Gomb *gmb)
{
    if(gmb->lenyomva)
    {
        gmb->lenyomva = false;
        return true;
    }
    return false;
}



void pontok_mentese(Jatekosok *jatekosok)
{
    FILE* fp;
    fp = fopen("toplista.txt", "w");
    for(int i = 0;i<10;i++)
        fprintf(fp, "Pont: %2d Nev: %s\n", jatekosok[i].pont, jatekosok[i].nev);

    fclose(fp);

}

bool rekord_e(Jatekosok *jatekosok,Jatekosok jatekos)
{
    int tmp = jatekos.pont;
    char tmp2[128];
    strcpy(tmp2,jatekos.nev);

    bool bennevan = false;
    for(int i = 0; i < 10; i++)
    {
        if(jatekos.pont > jatekosok[i].pont)
            bennevan = true;
        if(bennevan)
        {
            int temp1 = jatekosok[i].pont;
            jatekosok[i].pont = tmp;
            tmp  = temp1;

            char temp2[128];
            strcpy(temp2,jatekosok[i].nev);
            strcpy(jatekosok[i].nev,tmp2);
            strcpy(tmp2,temp2);
        }
    }
    return bennevan;
}

void pontok_beolvas(Jatekosok *jatekosok)
{
    FILE* fp;
    fp = fopen("toplista.txt", "r");
    for(int i = 0;i<10;i++)
        fscanf(fp, "Pont: %2d Nev: %s\n",&(jatekosok[i].pont),&(jatekosok[i].nev));

    fclose(fp);
}


void sdl_init(int szeles, int magas,Grafika *g)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Kigyos Jatek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }

    SDL_RenderClear(renderer);

    g->window = window;
    g->renderer = renderer;
}

Uint32 idozit(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

int main(int argc, char* args[])
{
    Grafika g;
    sdl_init(KEPERNYO_SZELESSEGE, KEPERNYO_MAGASSAGA, &g);

    TTF_Init();
    g.font = TTF_OpenFont(FONT, 30);
    if (!g.font)
    {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }

    Jatekosok jatekos;
    Jatekosok jatekos2;
    Jatekosok jatekosok[10];
    pontok_beolvas(jatekosok);
    srand(time(NULL));
    SDL_TimerID id = SDL_AddTimer(150, idozit, NULL);

    Test *kigyo;
    Test *kigyo2;
    Irany irany;
    Irany irany2;
    irany2 = JOBBRA;
    irany = JOBBRA;

    Irany eloirany = irany;
    Irany eloirany2 = irany2;

    Alma alma;
    Gyoztes gyoztes = nincs;

    g.hatter = IMG_LoadTexture(g.renderer, "snake background.png");


    if (g.hatter == NULL)
    {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }

    State state = MENUBEN;

    bool elsore = true;

    while(state != KILEPES)
    {
        SDL_Event e;
        SDL_WaitEvent(&e);

        if(state == MENUBEN)
        {
            if(e.type == SDL_QUIT)
                state = KILEPES;


            gomb_tortenes(&egyjatekos, &e);
            gomb_tortenes(&ketjatekos,&e);
            gomb_tortenes(&menuboltoplistaba,&e);

            menuhatter_kirajzol(&g);
            if(gombnyomas(&egyjatekos))
            {
                jatekos.pont = 0;
                irany = JOBBRA;
                state = EGYJATEKOSMOD;
                kigyot_lerak(10,10,&kigyo,5);
                alma_generalas(&alma);
            }
            if(gombnyomas(&ketjatekos))
            {

                irany = JOBBRA;
                irany2 = JOBBRA;
                jatekos.pont = 0;
                jatekos2.pont = 0;
                state = KETJATEKOSMOD;
                kigyot_lerak(10,10,&kigyo,5);
                kigyot_lerak(10,20,&kigyo2,5);
                alma_generalas(&alma);
            }
            if(gombnyomas(&menuboltoplistaba))
            {
                state = TOPLISTA;
                g.hatter4 = IMG_LoadTexture(g.renderer, "toplistahatter.png");
                if (g.hatter4 == NULL)
                {
                    SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
                    exit(1);
                }
            }
        }
        else if(state == NEVBEIRAS)
        {
            felszabadit(kigyo);
            kigyo = NULL;
            palyat_lerajzol(&g);
            nev_beker_szoveg(&g);
            SDL_Rect r = { 200, 200, 400, 40 };
            input_text(jatekos.nev,20,r,(SDL_Color){ 0, 0, 0, 255 },(SDL_Color){ 255, 255, 255, 255 },g.font,g.renderer);
            state = UJJATEKKEZDESE;
        }
        else if(state == EGYJATEKOSMOD)
        {
            switch (e.type)
            {
                case SDL_USEREVENT:
                    eloirany = irany;
                    palyat_lerajzol(&g);
                    pontok_kiirasa(jatekos,&g);
                    almat_lerajzol(g.renderer,&alma);
                    kigyot_lerajzol(kigyo,NULL,g.renderer);
                    kigyo_mozgas(kigyo,eloirany);
                    if(utkozes(kigyo,NULL,&alma,&jatekos))
                        state = NEVBEIRAS;

                    break;
                case SDL_KEYDOWN:
                    billentyu_kezel(e,&irany,&irany2,&eloirany,&eloirany2,&state);
                    break;

            }
            elsore = true;
        }

        else if(state == KETJATEKOSMOD)
        {
            switch (e.type)
            {
                case SDL_USEREVENT:
                    eloirany = irany;
                    eloirany2 = irany2;
                    palyat_lerajzol(&g);
                    almat_lerajzol(g.renderer,&alma);
                    pontok_kiirasa_ketjatekos(jatekos,jatekos2,&g);
                    kigyot_lerajzol(kigyo,kigyo2,g.renderer);
                    kigyo_mozgas(kigyo,eloirany);
                    kigyo_mozgas(kigyo2,eloirany2);
                    if(utkozes(kigyo,kigyo2,&alma,&jatekos))
                    {
                        gyoztes = piros;
                        state = KETJATEKOSUJJATEKKEZDESE;
                    }
                    if(utkozes(kigyo2,kigyo,&alma,&jatekos2))
                    {
                        if(gyoztes == piros)
                        {
                            if(jatekos.pont>jatekos2.pont)
                                gyoztes = zold;
                            else if(jatekos2.pont>jatekos.pont)
                                gyoztes = piros;
                            else
                                gyoztes = dontetlen;
                        }
                        else
                            gyoztes = zold;

                        state = KETJATEKOSUJJATEKKEZDESE;
                    }
                    break;
                case SDL_KEYDOWN:
                    billentyu_kezel(e,&irany,&irany2,&eloirany,&eloirany2,&state);
                    break;

            }
            elsore = true;
        }
        else if(state == UJJATEKKEZDESE)
        {
            gomb_tortenes(&ujjatek,&e);
            gomb_tortenes(&menube,&e);

            if(elsore)
            {
                if(rekord_e(jatekosok,jatekos))
                    g.hatter2 = IMG_LoadTexture(g.renderer, "vegejateknak2rekord.png");
                else
                    g.hatter2 = IMG_LoadTexture(g.renderer, "vegejateknak2.png");


                if (g.hatter2 == NULL)
                {
                    SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
                    exit(1);
                }
                elsore = false;
            }

            pontok_mentese(jatekosok);
            ujjatekkezdese_hatter_kirajzol(&g);

            if(gombnyomas(&ujjatek))
            {
                state = EGYJATEKOSMOD;
                irany = JOBBRA;
                kigyot_lerak(10,10,&kigyo,5);
                alma_generalas(&alma);
                jatekos.pont = 0;
                SDL_DestroyTexture(g.hatter2);
            }
            if(gombnyomas(&menube))
            {
                state = MENUBEN;
                jatekos.pont = 0;
                SDL_DestroyTexture(g.hatter2);
            }
            if(e.type == SDL_QUIT)
            {
                state = KILEPES;
                SDL_DestroyTexture(g.hatter2);
            }

        }
        else if(state == KETJATEKOSUJJATEKKEZDESE)
        {
            if(gyoztes == piros)
            {
                g.hatter3 = IMG_LoadTexture(g.renderer, "Vegejateknakkettoszemelyespirosnyert.png");
                if (g.hatter3 == NULL)
                {
                    SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
                    exit(1);
                }
                gyoztes = nincs;
                felszabadit(kigyo);
                felszabadit(kigyo2);
                kigyo = NULL;
                kigyo2 = NULL;
            }
            else if(gyoztes == zold)
            {
                g.hatter3 = IMG_LoadTexture(g.renderer, "Vegejateknakkettoszemelyeszoldnyert.png");
                if (g.hatter3 == NULL)
                {
                    SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
                    exit(1);
                }
                gyoztes = nincs;
                felszabadit(kigyo);
                felszabadit(kigyo2);
                kigyo = NULL;
                kigyo2 = NULL;
            }
            else if(gyoztes == dontetlen)
            {
                g.hatter3 = IMG_LoadTexture(g.renderer, "Vegejateknakkettoszemelyes.png");
                if (g.hatter3 == NULL)
                {
                    SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
                    exit(1);
                }
                gyoztes = nincs;
                felszabadit(kigyo);
                felszabadit(kigyo2);
                kigyo = NULL;
                kigyo2 = NULL;
            }

            gomb_tortenes(&ketjatekos_ujjatek,&e);
            gomb_tortenes(&ketjatekos_menube,&e);

            ketjatekos_ujjatekkezdese_hatter_kirajzol(&g,jatekos,jatekos2);

            if(gombnyomas(&ketjatekos_ujjatek))
            {
                state = KETJATEKOSMOD;
                irany = JOBBRA;
                irany2 = JOBBRA;
                kigyot_lerak(10,10,&kigyo,5);
                kigyot_lerak(10,20,&kigyo2,5);
                alma_generalas(&alma);
                jatekos.pont = 0;
                jatekos2.pont = 0;
                SDL_DestroyTexture(g.hatter3);
            }
            if(gombnyomas(&ketjatekos_menube))
            {
                state = MENUBEN;
                jatekos.pont = 0;
                jatekos2.pont = 0;
                SDL_DestroyTexture(g.hatter3);
            }
            if(e.type == SDL_QUIT)
            {
                state = KILEPES;
                SDL_DestroyTexture(g.hatter3);
            }
        }
        else if(state == TOPLISTA)
        {
            gomb_tortenes(&toplistabolmenube,&e);

            toplista_hatter_kirajzol(&g);
            toplista_kiirasa(jatekosok,&g);

            if(gombnyomas(&toplistabolmenube))
                {
                    SDL_DestroyTexture(g.hatter4);
                    state=MENUBEN;
                }
            if(e.type == SDL_QUIT)
            {
                state = KILEPES;
                SDL_DestroyTexture(g.hatter4);
            }
        }
        SDL_RenderPresent(g.renderer);

        if(state == KILEPES)
        {
            SDL_DestroyWindow(g.window);
            g.window = NULL;

            SDL_DestroyRenderer(g.renderer);
            g.renderer = NULL;

            SDL_DestroyTexture(g.hatter);

            TTF_CloseFont(g.font);

            SDL_Quit();
        }
    }
    SDL_RemoveTimer(id);
    return 0;
}


