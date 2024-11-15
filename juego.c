
/*
    Logica del juego: movimiento de la serpiente , choques, crecimiento, comida, etc.
*/ 




/*
    Interfaz del juego: visualizacion de la serpiente (forma), comida, tablero, etc.
*/ 
#include <SDL3/SDL.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>

//Definimos los parámetros a usar en las funciones:
const int ancho_ventana =  750 ;
const int altura_ventana = 375 ;
const int tamaño_celdas = 19;
const int filas = altura_ventana / tamaño_celdas ;
const int columnas = ancho_ventana / tamaño_celdas ;

// Función para inicializar.
bool inicializar_SDL () {
    if ( SDL_Init(SDL_INIT_VIDEO) != true ) {
        printf ("Error al inicializar SDL: %s \n ", SDL_GetError()) ;
        return false ; 
    }

    return true ;
}

// Función para crear una ventana.
bool crear_ventana (SDL_Window ** ventana) {
    * ventana = SDL_CreateWindow("cobra.io", ancho_ventana, altura_ventana, 0) ;
    if ( * ventana == NULL ) {
        printf ("Error al crear la ventana: %s \n ", SDL_GetError()) ;
        SDL_Quit () ;
        return false ; 
    }
    return true;
}

// Función para crear el renderizador.
bool crear_renderizador ( SDL_Renderer ** renderizador,SDL_Window * ventana ) {
    * renderizador = SDL_CreateRenderer(ventana, NULL) ;
    if (renderizador == NULL ) {
        printf ("Error al crear el renderizador: %s \n ", SDL_GetError()) ;
        SDL_DestroyWindow (ventana) ;
        SDL_Quit () ;
        return false ; 
    } 
    return true ;
}

// Función para dibujar las celdas.
void dibujar_tablero (SDL_Renderer * renderizador){
    for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                SDL_FRect celda = { j * tamaño_celdas, i * tamaño_celdas, tamaño_celdas, tamaño_celdas };

                // Alternar colores. 
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
                    SDL_SetRenderDrawColor(renderizador, 0, 0, 110, 100); // azul oscuro.
                } else {
                    SDL_SetRenderDrawColor(renderizador, 0, 0, 150, 100); // azul claro.
                }
            
                SDL_RenderFillRect(renderizador, &celda);

            // Dibuja el borde de la celda para un estilo retro.
            SDL_SetRenderDrawColor(renderizador, 0, 0, 90,255); // Bordes de las celdas, negros.
            SDL_RenderRect(renderizador, &celda);  // Dibuja solo el borde de la celda.
            }

    }
}

// Función para dibujar la serpiente y localización.
void dibujar_serpiente (int size, SDL_Point *tamano_serpiente, SDL_Renderer * renderizador ) {
    for (int i = 0; i < size; i++) {
        SDL_FRect rect = { tamano_serpiente[i].x * tamaño_celdas, tamano_serpiente[i].y * tamaño_celdas, tamaño_celdas, tamaño_celdas };
        SDL_SetRenderDrawColor(renderizador, 0, 255, 0, 255); // Color verde para la serpiente
        SDL_RenderFillRect(renderizador, &rect);
    }

}

// Función para dibujar la comida y su localización.
void dibujar_comida (SDL_Renderer * renderizador) {
    // Definir la posición de la comida.
    SDL_Point comida ;
    comida.x = rand() % columnas;
    comida.y = rand() % filas;

    SDL_FRect rect = { comida.x * tamaño_celdas, comida.y * tamaño_celdas, tamaño_celdas, tamaño_celdas };
    SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255); // Color rojo para la comida
    SDL_RenderFillRect(renderizador, &rect);

}


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
    if ( crear_renderizador(&renderizador2, ventana2) != true) {
        printf ("Error al crear la ventana: %s \n ", SDL_GetError()) ;
        return 0 ; // Sale si lo cumple.
    } 

        // Dibujamos las celdas/tablero.
        dibujar_tablero(renderizador2) ;

        // Dibujamos la serpiente y su localización.
        int size = 1;
        SDL_Point *tamano_serpiente = (SDL_Point *)malloc(size * sizeof(SDL_Point)) ;
        tamano_serpiente[0].x = 5 ;
        tamano_serpiente[0].y = 5 ; // Posición inicial-
        dibujar_serpiente(size, tamano_serpiente, renderizador2);

        //Dibujamos la comida y su localización.
        dibujar_comida(renderizador2) ;

        // Mostramos todo junto.
        SDL_RenderPresent(renderizador2) ;


    // Bucle del juego.
        // Por el momento que se duerma para poder ver la ventana.
        SDL_Delay(10000) ;

    // Finalizar el programa y liberar recursos.
    free (tamano_serpiente) ;
    SDL_DestroyRenderer (renderizador2) ;
    SDL_DestroyWindow (ventana2);
    SDL_Quit() ;

    return 0;
}



/*
    Menu del juego: apariencia, colores, boton de jugar, mejor tiempo, etc.
*/ 
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

// Tamaño de la ventana
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Estructura para el puntaje más alto
int highscore = 0;

// Función para cargar el highscore desde un archivo
void loadHighscore() {
    FILE *file = fopen("highscore.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &highscore);
        fclose(file);
    }
}
// Función para guardar el highscore en un archivo
void saveHighscore() {
    FILE *file = fopen("highscore.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", highscore);
        fclose(file);
    }
}

int main(int argc, char* argv[]) {
    // Inicializar SDL y SDL_ttf
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1) {
        printf("Error al inicializar SDL o SDL_ttf: %s\n", SDL_GetError());
        return 1;
    }

 // Crear la ventana
    SDL_Window* ventana = SDL_CreateWindow("Cobra.io", SDL_WINDOWPOS_CENTERED, >
    if (ventana == NULL) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crear el renderizador
    SDL_Renderer* renderizador = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_A>
    if (renderizador == NULL) {
        printf("Error al crear el renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }
  // Cargar el highscore desde el archivo
    loadHighscore();

    // Configurar color de fondo
    SDL_SetRenderDrawColor(renderizador, 173, 255, 47, 255); // Verde claro

