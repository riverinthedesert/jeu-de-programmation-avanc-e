#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "fonctions_fichers.h"
#include "fonctions_SDL.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



int main(){
    //ex1
    int nbLig=0;
    int nbCol=0;
    char** G=allouer_tab_2D(nbLig,nbCol);
    char** G2=allouer_tab_2D(nbLig,nbCol);
    
    
    int abs=64;//abscisse de hunter 
    int ord=64;//ordonne de hunter
//     char dir;//direction de hunter
    
    //ex3
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
    SDL_Texture* hunter= charger_image_transparente("hunter.bmp", ecran,r,g,b); 
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
    SDL_Rect SrcR_hunter;
    SrcR_hunter.x = 0;
    SrcR_hunter.y = 0;
    SrcR_hunter.w = 750; // Largeur du hunter
    SrcR_hunter.h = 1000; // Hauteur du hunter
    SDL_Rect DestR_hunter;
    DestR_hunter.x =abs;
    DestR_hunter.y =ord;
    DestR_hunter.w = 64; // Largeur du hunter
    DestR_hunter.h = 64; // Hauteur du hunter
    
    /**
    * \brief La fonction rafrachit l'écran en fonction de touche de clavier
    * \param abs abscisse de hunter 
    * \param ord ordonne de hunter
    */
    void refresh_graphics(int abs,int ord){
    if(abs<64)
        {
            abs=64;
        }
    if(abs>896)
        {
            abs=896;
        }
    if(ord<64)
        {
            ord=64;
        }
    if(ord>704)
        {
            ord=704;
        }
    DestR_hunter.x =abs;
    DestR_hunter.y =ord;
    }
    
    
    
    
    
    // Boucle principale
    while(!terminer)
    {
        while( SDL_PollEvent( &evenements ) )
            switch(evenements.type)
            {
                case SDL_QUIT:terminer = true; 
                break;
                case SDL_KEYDOWN:

                switch(evenements.key.keysym.sym)
                {
                     case SDLK_UP:
                         ord=ord-64; 
                                     break;
                     case SDLK_DOWN:
                         ord=ord+64; 
                                     break;
                     case SDLK_LEFT:
                         abs=abs-64; 
                                     break;
                     case SDLK_RIGHT:
                         abs=abs+64;
                                    break;
                     case SDLK_q:
                         terminer = true;  break;
                    
                 }
            }
        refresh_graphics(abs,ord);
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
        SDL_RenderCopy(ecran,hunter,&SrcR_hunter,&DestR_hunter);
        SDL_RenderPresent(ecran);  
    }
    
    // Quitter SDL
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    // Fermer la police et quitter SDL_ttf
    TTF_Quit();
    return 0;
}
