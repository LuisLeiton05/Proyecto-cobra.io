#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Tamaño de la ventana (menu).
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Definimos los parámetros a usar en las funciones (tablero).
const int ancho_ventana =  750 ;
const int altura_ventana = 375 ;
const int tamaño_celdas = 19;
const int filas = altura_ventana / tamaño_celdas ;
const int columnas = ancho_ventana / tamaño_celdas ;

// Inicializar variable para el puntaje mas alto (menu).
int highscore = 0 ;

// Función para inicializar (tablero).
bool inicializar_SDL () {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf ("Error al inicializar SDL: %s \n ", SDL_GetError()) ;
        return false ; 
    }

    return true ;
}

// Función para crear una ventana (tablero).
bool crear_ventana (SDL_Window ** ventana) {
    * ventana = SDL_CreateWindow("cobra.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ancho_ventana, altura_ventana, SDL_WINDOW_SHOWN) ;
    if ( * ventana == NULL ) {
        printf ("Error al crear la ventana: %s \n ", SDL_GetError()) ;
        SDL_Quit () ;
        return false ; 
    }
    return true;
}

// Función para crear el renderizador (tablero).
bool crear_renderizador ( SDL_Renderer ** renderizador,SDL_Window * ventana ) {
    * renderizador = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED) ;
    if (renderizador == NULL ) {
        printf ("Error al crear el renderizador: %s \n ", SDL_GetError()) ;
        SDL_DestroyWindow (ventana) ;
        SDL_Quit () ;
        return false ; 
    } 
    return true ;
}

// Función para dibujar las celdas (tablero).
void dibujar_tablero (SDL_Renderer * renderizador){
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            SDL_Rect celda = { j * tamaño_celdas, i * tamaño_celdas, tamaño_celdas, tamaño_celdas };

            // Alternar colores. 
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
                SDL_SetRenderDrawColor(renderizador, 80, 80, 80, 255); // Gris oscuro.
            } else {
                SDL_SetRenderDrawColor(renderizador, 128, 128, 128, 255); // Gris claro.
            }
        
            SDL_RenderFillRect(renderizador, &celda);

        // Dibuja el borde de la celda para un estilo retro.
        SDL_SetRenderDrawColor(renderizador, 80, 80, 80,255); // Bordes de las celdas.
        SDL_RenderDrawRect(renderizador, &celda);  // Dibuja solo el borde de la celda.
        }
    }
}

// Función para dibujar la serpiente y localización (tablero).
void dibujar_serpiente (int size, SDL_Point *tamano_serpiente, SDL_Renderer * renderizador ) {
    for (int i = 0; i < size; i++) {
        SDL_Rect rect = { tamano_serpiente[i].x * tamaño_celdas, tamano_serpiente[i].y * tamaño_celdas, tamaño_celdas, tamaño_celdas };
        SDL_SetRenderDrawColor(renderizador, 0, 255, 0, 255); // Color verde para la serpiente
        SDL_RenderFillRect(renderizador, &rect);
    }

}

// Función para dibujar la comida y su localización (tablero).
void dibujar_comida (SDL_Renderer * renderizador) {
    // Definir la posición de la comida.
    SDL_Point comida ;
    comida.x = rand() % columnas;
    comida.y = rand() % filas;

    SDL_Rect rect = { comida.x * tamaño_celdas, comida.y * tamaño_celdas, tamaño_celdas, tamaño_celdas };
    SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255); // Color rojo para la comida
    SDL_RenderFillRect(renderizador, &rect);

}
// Función para cargar el highscore desde un archivo (tablero).
void loadHighscore() {
    FILE *file = fopen("highscore.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &highscore);
        fclose(file);
    }
}
// Función para guardar el puntaje mas alto en un archivo (tablero).
void saveHighscore() {
    FILE *file = fopen("highscore.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", highscore);
        fclose(file);
    }
}

int main() {
    // Inicializar SDL y SDL_ttf.
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1) {
        printf("Error al inicializar SDL o SDL_ttf: %s\n", SDL_GetError());
        return 1;
    }

    // Crear la ventana.
    SDL_Window* ventana = SDL_CreateWindow("Cobra.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) ;
    if (ventana == NULL) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crear el renderizador.
    SDL_Renderer* renderizador = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (renderizador == NULL) {
        printf("Error al crear el renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    // Cargar el highscore desde el archivo.
    loadHighscore();

    // Configurar color de fondo.
    SDL_SetRenderDrawColor(renderizador, 173, 255, 47, 255); // Verde claro.

    // Cargar fuente para el título 
    TTF_Font* fuente = TTF_OpenFont("Crang.ttf", 48);  // Título más grande.
    if (fuente == NULL) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderizador);
        SDL_DestroyWindow(ventana);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Crear fuente más pequeña para el botón
    TTF_Font* fuenteBoton = TTF_OpenFont("Crang.ttf", 30);  
    if (fuenteBoton == NULL) {
        printf("Error al cargar la fuente del botón: %s\n", TTF_GetError());
        TTF_CloseFont(fuente);
        SDL_DestroyRenderer(renderizador);
        SDL_DestroyWindow(ventana);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Cargar fuente más pequeña para el puntaje más alto.
    TTF_Font* fuentePequena = TTF_OpenFont("Crang.ttf", 18);  
    if (fuentePequena == NULL) {
        printf("Error al cargar la fuente para highscore: %s\n", TTF_GetError());
        TTF_CloseFont(fuenteBoton);
        TTF_CloseFont(fuente);
        SDL_DestroyRenderer(renderizador);
        SDL_DestroyWindow(ventana);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Crear texto "cobra.io" (Título)
    SDL_Color colorNegro = {0, 0, 0, 255};
    SDL_Surface* superficieTitulo = TTF_RenderText_Solid(fuente, "cobra.io", colorNegro);
    if (superficieTitulo == NULL) {
        printf("Error al crear la superficie para el título: %s\n", TTF_GetError());
        TTF_CloseFont(fuentePequena);
        TTF_CloseFont(fuenteBoton);
        TTF_CloseFont(fuente);
        SDL_DestroyRenderer(renderizador);
        SDL_DestroyWindow(ventana);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texturaTitulo = SDL_CreateTextureFromSurface(renderizador, superficieTitulo);
    SDL_Rect rectTitulo = {SCREEN_WIDTH / 2 - superficieTitulo->w / 2, 100, superficieTitulo->w, superficieTitulo->h};
    
    // Crear texto "PRESS TO START" para el botón
    SDL_Surface* superficieBoton = TTF_RenderText_Solid(fuenteBoton, "JUGAR", colorNegro);
    SDL_Texture* texturaBoton = SDL_CreateTextureFromSurface(renderizador, superficieBoton);
    SDL_Rect rectBoton = {SCREEN_WIDTH / 2 - superficieBoton->w / 2, 350, superficieBoton->w, superficieBoton->h};
    
    // Crear texto para mostrar el highscore (en la esquina)
    char highscoreText[20];
    snprintf(highscoreText, sizeof(highscoreText), "RECORD: %d", highscore);
    SDL_Surface* superficieHighscore = TTF_RenderText_Solid(fuentePequena, highscoreText, colorNegro);
    SDL_Texture* texturaHighscore = SDL_CreateTextureFromSurface(renderizador, superficieHighscore);
    SDL_Rect rectHighscore = {SCREEN_WIDTH - superficieHighscore->w - 20, 20, superficieHighscore->w, superficieHighscore->h};

    // Bucle principal del juego.
    int enEjecucion = 1;
    SDL_Event evento;
    while (enEjecucion) {
        // Manejar eventos
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                enEjecucion = 0; // Salir del juego.
            } else if (evento.type == SDL_MOUSEBUTTONDOWN) {
            // Verificar si el clic fue dentro del área del botón
            int x = evento.button.x;
            int y = evento.button.y;
            if (x >= rectBoton.x && x <= rectBoton.x + rectBoton.w &&
                y >= rectBoton.y && y <= rectBoton.y + rectBoton.h) {
                // Al hacer clic en el botón "JUGAR"
                // Cerramos la vetana del menu.
                SDL_DestroyRenderer(renderizador);
                SDL_DestroyWindow(ventana);
                enEjecucion = 0 ;

                // LLamamos la función de la ventana.
                SDL_Window *ventana2 ;
                if ( !crear_ventana(&ventana2) ) {
                    printf ("Error al crear la ventana: %s \n ", SDL_GetError()) ;
                    return 0 ; // Sale si lo cumple.
                } 
                
                // LLamamos la función del renderizador.
                SDL_Renderer * renderizador2 ;
                if ( !crear_renderizador(&renderizador2, ventana2) ) {
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


                // Funcionalidad del juego.
                    // Por el momento que se duerma para poder ver la ventana.
                    SDL_Delay(10000) ; // Quitarlo.
                    // Movimiento continuo de la serpiente.

                    // Movimiento con las teclas.

                    // Control de choques, cuando se pierde volver al menu.

                    // Crecer al comer.

                    // Funciones referentes al  tiempo.

                    // Aumentar la velocidad al pasar 1 min.

                    // Mostrar tiempo en el tablero.

                    // Actualización de puntaje.

                // Finalizar el programa y liberar recursos (ventana tablero).
                free (tamano_serpiente) ;
                SDL_DestroyRenderer (renderizador2) ;
                SDL_DestroyWindow (ventana2);
                SDL_Quit() ;
                
                // enEjecucion = 0;  // Para salir del bucle.
                }
            }
        }


        // Dibujar fondo
        SDL_SetRenderDrawColor(renderizador, 173, 255, 47, 255);
        SDL_RenderClear(renderizador);

        // Dibujar título "cobra.io"
        SDL_RenderCopy(renderizador, texturaTitulo, NULL, &rectTitulo);
        
        // Dibujar highscore en la esquina
        SDL_RenderCopy(renderizador, texturaHighscore, NULL, &rectHighscore);

        // Dibujar botón "JUGAR"
        SDL_RenderCopy(renderizador, texturaBoton, NULL, &rectBoton);

        // Actualizar pantalla
        SDL_RenderPresent(renderizador);
    }
 // Liberar recursos del menu.
    SDL_DestroyTexture(texturaTitulo);
    SDL_FreeSurface(superficieTitulo);
    SDL_DestroyTexture(texturaBoton);
    SDL_FreeSurface(superficieBoton);
    SDL_DestroyTexture(texturaHighscore);
    SDL_FreeSurface(superficieHighscore);
    TTF_CloseFont(fuente);
    TTF_CloseFont(fuenteBoton);
    TTF_CloseFont(fuentePequena);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(ventana);
    TTF_Quit();
    SDL_Quit();


    return 0;
}

