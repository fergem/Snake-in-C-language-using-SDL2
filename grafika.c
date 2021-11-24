#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "debugmalloc.h"

#include "grafika.h"


SDL_Color feher = { 255, 255, 255, 255 };
SDL_Color fekete = { 0, 0, 0, 255 };

void menuhatter_kirajzol(Grafika *g)
{
    SDL_Rect src = {0,0,KEPERNYO_SZELESSEGE,KEPERNYO_MAGASSAGA};
    SDL_Rect dest = {0,0,KEPERNYO_SZELESSEGE,KEPERNYO_MAGASSAGA};
    SDL_RenderCopy(g->renderer, g->hatter, &src, &dest);
}

void ujjatekkezdese_hatter_kirajzol(Grafika *g)
{
    SDL_Rect src = {0,0,KEPERNYO_SZELESSEGE,KEPERNYO_MAGASSAGA};
    SDL_Rect dest = {0,0,KEPERNYO_SZELESSEGE,KEPERNYO_MAGASSAGA};
    SDL_RenderCopy(g->renderer, g->hatter2, &src, &dest);
}

void ketjatekos_ujjatekkezdese_hatter_kirajzol(Grafika *g,Jatekosok jatekos,Jatekosok jatekos2)
{
    SDL_Rect src = {0,0,KEPERNYO_SZELESSEGE,KEPERNYO_MAGASSAGA};
    SDL_Rect dest = {0,0,KEPERNYO_SZELESSEGE,KEPERNYO_MAGASSAGA};
    SDL_RenderCopy(g->renderer, g->hatter3, &src, &dest);

}

void toplista_hatter_kirajzol(Grafika *g)
{
    SDL_Rect src = {0,0,KEPERNYO_SZELESSEGE,KEPERNYO_MAGASSAGA};
    SDL_Rect dest = {0,0,KEPERNYO_SZELESSEGE,KEPERNYO_MAGASSAGA};
    SDL_RenderCopy(g->renderer, g->hatter4, &src, &dest);
}

void palyat_lerajzol(Grafika *g)
{
    SDL_SetRenderDrawColor(g->renderer, fekete.r, fekete.g, fekete.b, fekete.a);
    SDL_RenderClear(g->renderer);
    rectangleRGBA(g->renderer,PALYA_SZELESSEG + 80,60,80,PALYA_MAGASSAG + 60,0,161,255,202);
}


void pontok_kiirasa(Jatekosok jatekos,Grafika *g)
{
    SDL_Rect hova = { 0, 0, 0, 0 };
    char str[128];
    sprintf(str, "Pontok:%2d", jatekos.pont);
    g->felirat = TTF_RenderUTF8_Blended(g->font,str,feher);
    g->felirat_t = SDL_CreateTextureFromSurface(g->renderer, g->felirat);

    hova.x = 420 - g->felirat->w/2;
    hova.y = 20;
    hova.w = g->felirat->w*2/3;
    hova.h = g->felirat->h*2/3;
    SDL_RenderCopy(g->renderer, g->felirat_t, NULL, &hova);
    SDL_FreeSurface(g->felirat);
    SDL_DestroyTexture(g->felirat_t);
}

void pontok_kiirasa_ketjatekos(Jatekosok jatekos,Jatekosok jatekos2,Grafika *g)
{
    SDL_Rect hova = { 0, 0, 0, 0 };
    char str[128];
    sprintf(str, "Zold pontok:%2d", jatekos.pont);
    g->felirat = TTF_RenderUTF8_Blended(g->font,str,feher);
    g->felirat_t = SDL_CreateTextureFromSurface(g->renderer, g->felirat);

    hova.x = 300 - g->felirat->w/2;
    hova.y = 20;
    hova.w = g->felirat->w*2/3;
    hova.h = g->felirat->h*2/3;
    SDL_RenderCopy(g->renderer, g->felirat_t, NULL, &hova);
    SDL_FreeSurface(g->felirat);
    SDL_DestroyTexture(g->felirat_t);

    char str2[128];
    sprintf(str2, "Piros pontok:%2d", jatekos2.pont);
    g->felirat = TTF_RenderUTF8_Blended(g->font,str2,feher);
    g->felirat_t = SDL_CreateTextureFromSurface(g->renderer, g->felirat);

    hova.x = 600 - g->felirat->w/2;
    hova.y = 20;
    hova.w = g->felirat->w*2/3;
    hova.h = g->felirat->h*2/3;
    SDL_RenderCopy(g->renderer, g->felirat_t, NULL, &hova);
    SDL_FreeSurface(g->felirat);
    SDL_DestroyTexture(g->felirat_t);
}

void nev_beker_szoveg(Grafika *g)
{
    SDL_Rect hova = { 0, 0, 0, 0 };

    g->felirat = TTF_RenderUTF8_Blended(g->font,"Add meg a neved",feher);
    g->felirat_t = SDL_CreateTextureFromSurface(g->renderer, g->felirat);

    hova.x = 400 - g->felirat->w/2;
    hova.y = 150;
    hova.w = g->felirat->w;
    hova.h = g->felirat->h;

    SDL_RenderCopy(g->renderer, g->felirat_t, NULL, &hova);
    SDL_FreeSurface(g->felirat);
    SDL_DestroyTexture(g->felirat_t);
}

void toplista_kiirasa(Jatekosok *jatekosok,Grafika *g)
{
    SDL_Rect hova = { 0, 0, 0, 0 };
    char str[150];
    for(int i = 0;i<10;i++)
    {
        sprintf(str, "Pont: %2d Nev: %s",jatekosok[i].pont,jatekosok[i].nev);
        g->felirat = TTF_RenderUTF8_Blended(g->font,str, fekete);
        g->felirat_t = SDL_CreateTextureFromSurface(g->renderer, g->felirat);
        hova.x = 300;
        hova.y = 250 + i*30;
        hova.w = g->felirat->w;
        hova.h = g->felirat->h;

        SDL_RenderCopy(g->renderer, g->felirat_t, NULL, &hova);
    }
}

bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer)
{
    /* Ez tartalmazza az aktualis szerkesztest */
    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';
    /* Ezt a kirajzolas kozben hasznaljuk */
    char textandcomposition[hossz + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    /* Max hasznalhato szelesseg */
    int maxw = teglalap.w - 2;
    int maxh = teglalap.h - 2;

    dest[0] = '\0';

    bool enter = false;
    bool kilep = false;

    SDL_StartTextInput();
    while (!kilep && !enter) {
        /* doboz kirajzolasa */
        boxRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r, hatter.g, hatter.b, 255);
        rectangleRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, szoveg.r, szoveg.g, szoveg.b, 255);
        /* szoveg kirajzolasa */
        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0') {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = { teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw, felirat->h < maxh ? felirat->h : maxh };
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        } else {
            w = 0;
        }
        /* kurzor kirajzolasa */
        if (w < maxw) {
            vlineRGBA(renderer, teglalap.x + w + 2, teglalap.y + 2, teglalap.y + teglalap.h - 3, szoveg.r, szoveg.g, szoveg.b, 192);
        }
        /* megjeleniti a képernyon az eddig rajzoltakat */
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            /* Kulonleges karakter */
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    int textlen = strlen(dest);
                    do {
                        if (textlen == 0) {
                            break;
                        }
                        if ((dest[textlen-1] & 0x80) == 0x00)   {
                            /* Egy bajt */
                            dest[textlen-1] = 0x00;
                            break;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0x80) {
                            /* Bajt, egy tobb-bajtos szekvenciabol */
                            dest[textlen-1] = 0x00;
                            textlen--;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0xC0) {
                            /* Egy tobb-bajtos szekvencia elso bajtja */
                            dest[textlen-1] = 0x00;
                            break;
                        }
                    } while(true);
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    enter = true;
                }
                break;

            /* A feldolgozott szoveg bemenete */
            case SDL_TEXTINPUT:
                if (strlen(dest) + strlen(event.text.text) < hossz) {
                    strcat(dest, event.text.text);
                }

                /* Az eddigi szerkesztes torolheto */
                composition[0] = '\0';
                break;

            /* Szoveg szerkesztese */
            case SDL_TEXTEDITING:
                strcpy(composition, event.edit.text);
                break;

             case SDL_QUIT:
                /* visszatesszuk a sorba ezt az eventet, mert
                 * sok mindent nem tudunk vele kezdeni*/
                SDL_PushEvent(&event);
                kilep = true;
                break;
        }
    }

    /* igaz jelzi a helyes beolvasast; = ha enter miatt allt meg a ciklus */
    SDL_StopTextInput();
    return enter;
}
