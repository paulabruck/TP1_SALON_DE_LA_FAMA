#ifndef SALON_H
#define SALON_H

#define MAX_NOMBRE_POKEMON    10
#define MAX_NOMBRE_ENTRENADOR 30

typedef struct{
    char nombre[MAX_NOMBRE_POKEMON];
    int nivel;
    int fuerza;
    int inteligencia;
    int velocidad;
    int defensa;
}pokemon_t;

typedef struct{
    char nombre[MAX_NOMBRE_ENTRENADOR];
    int victorias;
    pokemon_t** equipo;
}entrenador_t;

typedef struct{
    entrenador_t** entrenadores;
}salon_t;

/**
 * Lee archivo y lo carga en memoria.
 *
 * Si no puede leer el archivo o hay un error, devuelve NULL.
 */
salon_t* salon_leer_archivo(const char* nombre_archivo);

/**
 * Guarda el salon a un archivo.
 *
 * Devuelve la cantidad de entrenadores guardados o -1 en caso de error.
 */
int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo);

/**
 * Agrega un entrenador al salon.
 *
 * El entrenador, como todos los pokemon del mismo, deben residir en memoria
 * dinámica y debe ser posible de liberar todo usando free. Una vez agregado al
 * salon, el salon toma posesión de dicha memoria y pasa a ser su
 * responsabilidad liberarla.
 *
 * Devuelve el salon o NULL en caso de error.
 */
salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador);

/**
 * Busca en el salon entrenadores que hayan ganado por lo menos cantidad_minima_victorias batallas.
 *
 * Devuelve un vector de entrenadores a liberar por el usuario usando free o NULL en caso de error.
 */
entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias);

/**
 * Muestra por pantalla los datos de un entrenador y sus pokemon.
 */
void salon_mostrar_entrenador(entrenador_t* entrenador);

/**
 * Libera toda la memoria utilizada por el salon, los entrenadores y todos los pokemon.
 */
void salon_destruir(salon_t* salon);

#endif /* SALON_H */
