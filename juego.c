#include <SDL3/SDL.h>

#include <stdio.h> 
#include <stdbool.h>


/*
    Logica del juego: movimiento de la serpiente , choques, crecimiento, comida, etc.
*/ 



/*
    Interfaz del juego: visualizacion de la serpiente (forma), comida, tablero, etc.
*/ 

//Definimos los parámetros a usar en las funciones:
const int ancho_ventana =  640 ;
const int altura_ventana = 480 ;
const int tamaño_celdas = 20 ;

// Función para inicializar.
bool inicializar_SDL () {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf ("Error al inicializar SDL: %s \n ", SDL_GetError()) ;
        return 1 ; 
    }

    return 0;
}

int main () {
    // Inicializamos.
    if ( inicializar_SDL != 0 ) {
        printf ("Error al inicializar SDL: %s \n ", SDL_GetError()) ;
        return 0 ; // Sale si lo cumple.
    } 

    // Crear una ventana donde irá todo.
    SDL_Window * ventana = SDL_CreateWindow("cobra.io", ancho_ventana, altura_ventana, SDL_WINDOW_MINIMIZED) ;
    if (ventana == NULL ) {
        printf ("Error al crear la ventana: %s \n ", SDL_GetError()) ;
        SDL_DestroyWindow (ventana);
        SDL_Quit () ;
        return 0 ; // Sale si lo cumple.
    } 
    




    // Finalizar el programa.
    SDL_DestroyWindow (ventana);
    SDL_Quit() ;

    return 0;
}



/*
    Menu del juego: apariencia, colores, boton de jugar, mejor tiempo, etc.
*/ 



