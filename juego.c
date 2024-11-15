#include <SDL3/SDL.h>
#include <stdio.h> 
#include <stdlib.h> 
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
const int filas = altura_ventana / tamaño_celdas ;
const int columnas = ancho_ventana / tamaño_celdas ;

// Función para inicializar.
bool inicializar_SDL () {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf ("Error al inicializar SDL: %s \n ", SDL_GetError()) ;
        return false ; 
    }

    return true ;
}

// Función para crear una ventana.
bool crear_ventana (SDL_Window ** ventana) {
    * ventana = SDL_CreateWindow("cobra.io", ancho_ventana, altura_ventana, SDL_WINDOW_MINIMIZED) ;
    if (ventana == NULL ) {
        printf ("Error al crear la ventana: %s \n ", SDL_GetError()) ;
        SDL_Quit () ;
        return false ; 
    }
    return true;
}

// Función para crear el renderizador.
bool crear_renderizador ( SDL_Renderer ** renderizador,SDL_Window ** ventana ) {
    SDL_Renderer *renderizador = SDL_CreateRenderer(ventana, NULL) ;
    if (renderizador == NULL ) {
        printf ("Error al crear el renderizador: %s \n ", SDL_GetError()) ;
        SDL_DestroyWindow (ventana) ;
        SDL_Quit () ;
        return false ; 
    } 
    return true ;
}

// Función para dibujar las celdas.
void dibujar_tablero (SDL_Renderer ** renderizador){
    for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                SDL_Rect celda = { j * tamaño_celdas, i * tamaño_celdas, tamaño_celdas, tamaño_celdas };
                SDL_SetRenderDrawColor(renderizador, 0, 0, 200, 180); // Color azul, medio transparente.
                SDL_RenderFillRect(renderizador, &celda);
            }
        }


}

// Dibujar la serpiente y localización.



// Dibujar la comida y localización.

int main () {
    // Inicializamos.
    if ( inicializar_SDL () != true ) {
        printf ("Error al inicializar SDL: %s \n ", SDL_GetError()) ;
        return 0 ; // Sale si lo cumple.
    } 

    // LLamamos la función de la ventana.
    SDL_Window *ventana2 ;
    if ( crear_ventana(&ventana2) != true) {
        printf ("Error al crear la ventana: %s \n ", SDL_GetError()) ;
        return 0 ; // Sale si lo cumple.
    } 
    
    // LLamamos la función del renderizador.
    SDL_Renderer * renderizador2 ;
    if ( crear_renderizador(&renderizador2, &ventana2) != true) {
        printf ("Error al crear la ventana: %s \n ", SDL_GetError()) ;
        return 0 ; // Sale si lo cumple.
    } 

        // Dibujamos las celdas/tablero.
        dibujar_tablero(&renderizador2) ;
        // Dibujamos la serpiente y su localización.

        //Dibujamos la comida y su localización.


    // 


    // Finalizar el programa y liberar recursos.
    SDL_DestroyRenderer (renderizador2) ;
    SDL_DestroyWindow (ventana2);
    SDL_Quit() ;



    return 0;
}



/*
    Menu del juego: apariencia, colores, boton de jugar, mejor tiempo, etc.
*/ 



