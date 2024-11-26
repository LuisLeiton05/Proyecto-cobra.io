# Proyecto-cobra.io

## Descripción del Proyecto:

Cobra.io es una recreación del juego retro Snake, desarrollado en el lenguaje de programación C y utilizando la biblioteca gráfica SDL (Simple DirectMedia Layer).

El proyecto incluye:

    - Un menú interactivo con opciones para jugar y consultar el récord de puntuaciones.

    - Un tablero dinámico donde se desarrolla el juego.

Este proyecto combina lógica de programación, el manejo de una interfaz gráfica y ofrece una experiencia entretenida. 

## Dependencias:
Lista de herramientas como bibliocas y archivos necesarios para ejecutar el proyecto:

    - SDL2 (se utilizó esta versión).

    - SDL_ttf (extensión de SLD2, para trabajar con fuentes TrueType(TTF)).

    - Crang.ttf (tipo de letra utilizada en el menú).

## Instalación de las dependencias:
    - Primero, utilizar el siguiente comando para actualizar la lista de paquetes disponibles desde los repositorios configurados:

    sudo apt update

    - Ahora, instalamos SDL, versión SDL2 con el siguiente comando:

    sudo apt-get install libsdl2-dev

    - Posteriormente, descargar la siguiente biblioteca que es una extensión de SDL2 y permite trabajar con fuentes TrueType (TTF) para renderizar texto:
    
    sudo apt install libsdl2-ttf-dev

    - Abrir el siguiente enlace: https://www.dafont.com/crang.font

    Una vez dentro de este, presionar donde dice “Download” para descagar un archivo comprimido. Ir a descargas o donde se haya guardado el archivo, lo extraemos y quedará una carpeta llamada “crang”, dentro está el archivo “Crang.ttf”. Asegurarse que este último esté en la misma carpeta en donde se va a compilar y ejecutar el código del archivo “juego.c” (se puede mover o copiar).

## Pasos para ejecución:
    - Finalmente se debe compilar con el siguiente comando:

    gcc -Wall juego.c -o ejecutable -lSDL2 -lSDL2_ttf

    - Para ejecutar el archivo generado por el comando anterior:

    ./ejecutable