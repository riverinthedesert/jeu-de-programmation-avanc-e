#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "fonctions_fichers.h"
#include "fonctions_SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


/**
    * \brief La fonction rafrachit l'écran en fonction de touche de clavier
    * \param abs abscisse de hunter 
    * \param ord ordonne de hunter
    */
    void refresh_graphics(int* abs,int* ord,char dir,char** G,char** G2,SDL_Rect* DestR_character,SDL_Rect* SrcR_character[4]){
    if((int)G[*ord/64][*abs/64]%16==7||(int)G2[*ord/64][*abs/64]%16==8)
    {
        switch(dir)
                {
                     case 'h':
                         *ord=*ord+64; 
                                     break;
                     case 'b':
                         *ord=*ord-64; 
                                     break;
                     case 'g':
                         *abs=*abs+64; 
                                     break;
                     case 'd':
                         *abs=*abs-64;
                                    break;
                    
                 }
    }
    if((int)G2[*ord/64][*abs/64]%16==3)
    {
        switch(dir)
                {
                     case 'h':
                         *ord=*ord+64; 
                                     break;
                     case 'b':
                         *ord=*ord-64; 
                                     break;
                     case 'g':
                         *abs=*abs+64; 
                                     break;
                     case 'd':
                         *abs=*abs-64;
                                    break;
                    
                 }
    }
    (*DestR_hunter).x =*abs;
    (*DestR_hunter).y =*ord;
    }
    
/**
    * \brief monster deplace automatique
    * \param abs abscisse de hunter 
    * \param ord ordonne de hunter
    */
    void move_monster(int* abs,int* ord,char dir,char** G,char** G2,SDL_Rect* DestR_monster){
        int t=rand()%4;
        switch(t)
                {
                     case 0:
                         *abs=*abs-64; 
                         dir='g';
                                     break;
                     case 1:
                         *ord=*ord-64; 
                         dir='h';
                                     break;
                     case 2:
                         *abs=*abs+64; 
                         dir='d';
                                     break;
                     case 3:
                         *ord=*ord+64; 
                         dir='b';
                                    break;
                 }
        
            if((int)G[*ord/64][*abs/64]%16==7||(int)G2[*ord/64][*abs/64]%16==3||(int)G2[*ord/64][*abs/64]%16==8)
            {
                switch(dir)
                    {
                     case 'h':
                         *ord=*ord+64; 
                                     break;
                     case 'b':
                         *ord=*ord-64; 
                                     break;
                     case 'g':
                         *abs=*abs+64; 
                                     break;
                     case 'd':
                         *abs=*abs-64;
                                    break;
                    }
            }
        (*DestR_monster).x =*abs;
        (*DestR_monster).y =*ord;
        }


int main(){
    int nbLig=0;
    int nbCol=0;
    char** G=allouer_tab_2D(nbLig,nbCol);
    char** G2=allouer_tab_2D(nbLig,nbCol);
    
    
    int abs=64;//abscisse de hunter 
    int ord=64;//ordonne de hunter
    char dir='b'; // quartre option g: gauche h:haut d:droite b:bas
    
    int abs1=640;
    int ord1=640;
    char dir1='d';
    srand(time(NULL));// Initialization
    // quartre option t=0: gauche t=1:haut t=2:droite t=3:bas
    
    
    SDL_Window* fenetre;  // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
        
    }
    
    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1024, 832, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
        
    }
    
    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    
    // Charger l’image
    SDL_Texture* fond= charger_image( "fond.bmp", ecran );
    
    //créer le terrain
    taille_fichier("terrain.txt",&nbLig,&nbCol);
    G=allouer_tab_2D(nbLig,nbCol);
    G=lire_fichier("terrain.txt");
    afficher_tab_2D(G,nbLig,nbCol);
    taille_fichier("fire.txt",&nbLig,&nbCol);
    G2=allouer_tab_2D(nbLig,nbCol);
    G2=lire_fichier("fire.txt");
    afficher_tab_2D(G2,nbLig,nbCol);
    
    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* pavage= charger_image_transparente("pavage.bmp", ecran,r,g,b);   
    SDL_Texture* character= charger_image_transparente("weapon.bmp", ecran,r,g,b); 
    SDL_Texture* monster= charger_image_transparente("eldritch.bmp", ecran,r,g,b);  
    SDL_Rect SrcR_pavage[13][15];
     for(int i=0; i<13; i++)
    {
        for(int j=0; j<15; j++)
        {  
            SrcR_pavage[i][j].x = j*32;
            SrcR_pavage[i][j].y = i*32;
            SrcR_pavage[i][j].w = 32; // Largeur du pavage
            SrcR_pavage[i][j].h = 32; // Hauteur du pavage
        }
    }
    SDL_Rect DestR_pavage[nbLig][nbCol];
    for(int i=0; i<nbLig; i++)
    {
        for(int j=0; j<nbCol; j++)
        {
            DestR_pavage[i][j].x =j*64;
            DestR_pavage[i][j].y =i*64;
            DestR_pavage[i][j].w = 64; // Largeur du pavage
            DestR_pavage[i][j].h = 64; // Hauteur du pavage
        }
        
    }
    SDL_Rect SrcR_character[4];
    for(int i=0; i<4; i++)
    {
        SrcR_character[i].x = 0;
        SrcR_character[i].y = i*49;
        SrcR_character[i].w = 39; // Largeur du pavage
        SrcR_character[i].h = 49; // Hauteur du pavage
    }
    SDL_Rect DestR_character;
    DestR_character.x =abs;
    DestR_character.y =ord;
    DestR_character.w = 64; // Largeur du hunter
    DestR_character.h = 64; // Hauteur du hunter
    SDL_Rect SrcR_monster;
    SrcR_monster.x = 0;
    SrcR_monster.y = 0;
    SrcR_monster.w = 236; // Largeur du monster
    SrcR_monster.h = 236; // Hauteur du monster
    SDL_Rect DestR_monster;
    DestR_monster.x =abs1;
    DestR_monster.y =ord1;
    DestR_monster.w = 64; // Largeur du monster
    DestR_monster.h = 64; // Hauteur du monster

    
    
    
    
    
    // Boucle principale
    while(!terminer)
    {
        int tempsfin = 0, tempsdebut = 0;
        // chrono début
        tempsdebut = SDL_GetTicks();
        while( SDL_PollEvent( &evenements ) )
        {
            switch(evenements.type)
            {
                case SDL_QUIT:terminer = true; 
                break;
                case SDL_KEYDOWN:

                switch(evenements.key.keysym.sym)
                {
                     case SDLK_UP:
                         ord=ord-64; 
                         dir='h';
                                     break;
                     case SDLK_DOWN:
                         ord=ord+64; 
                         dir='b';
                                     break;
                     case SDLK_LEFT:
                         abs=abs-64; 
                         dir='g';
                                     break;
                     case SDLK_RIGHT:
                         abs=abs+64;
                         dir='d';
                                    break;
                     case SDLK_q:
                         terminer = true;  break;
                    
                 }
            }
        }
        
        move_monster(&abs1,&ord1,dir1,G,G2,&DestR_monster);
        refresh_graphics(&abs,&ord,dir,G,G2,&DestR_character,&SrcR_character[4]);
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran,fond,NULL,NULL);

        for(int i=0; i<nbLig; i++)
        {
            for(int j=0;j<nbCol;j++)
            {

                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[(int)G[i][j]/16-3][(int)G[i][j]%16], &DestR_pavage[i][j]);
            }
        }
        for(int i=0; i<nbLig; i++)
        {
            for(int j=0;j<nbCol;j++)
            {

                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[(int)G2[i][j]/16-3][(int)G2[i][j]%16], &DestR_pavage[i][j]);
            }
        }
        SDL_RenderCopy(ecran,monster,&SrcR_monster,&DestR_monster);
        switch(dir)
                {
                     case 'h':
                         SDL_RenderCopy(ecran,character,&SrcR_character[3],&DestR_character);
                                     break;
                     case 'b':
                         SDL_RenderCopy(ecran,character,&SrcR_character[0],&DestR_character); 
                                     break;
                     case 'g':
                         SDL_RenderCopy(ecran,character,&SrcR_character[1],&DestR_character); 
                                     break;
                     case 'd':
                         SDL_RenderCopy(ecran,character,&SrcR_character[2],&DestR_character);
                                    break;
                    
                 }
        SDL_RenderPresent(ecran);  
        // chrono fin
        tempsfin = SDL_GetTicks();
        // attente 2500/30 - durée
        SDL_Delay(2500/30 - (tempsfin - tempsdebut));
    }
    
    // Quitter SDL
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    // Fermer la police et quitter SDL_ttf
    TTF_Quit();
    return 0;
}
