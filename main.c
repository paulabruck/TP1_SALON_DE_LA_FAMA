#include "salon.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

#define AMARILLO "\x1b[33m"
#define AZUL "\x1b[34m"
#define PURPURA "\x1b[35m"
#define CELESTE "\x1b[36m"
#define NORMAL "\x1b[0m"

#define NOMBRE_ARCHIVO "salon_original.sal"
#define NOMBRE_ARCHIVO_MODIFICADO "salon_modificado.sal"

int main(){
    printf(CELESTE"Crear un salon usando el archivo 'salon_original.sal'\n"NORMAL);
    salon_t* salon=salon_leer_archivo(NOMBRE_ARCHIVO);    
    if(!salon){
        salon_destruir(salon);
        return -1;
    }
    
    printf(CELESTE"\nObtener los entrenadores con al menos 3 ligas ganadas y mostrarlos por pantalla.\n"NORMAL);
    int cantidad_minima_victorias= 3;
    entrenador_t** entrenador=salon_obtener_entrenadores_mas_ganadores(salon,cantidad_minima_victorias);
    size_t tamanio= vtrlen(entrenador);
    int i=0;
    while(i<tamanio){
        salon_mostrar_entrenador(entrenador[i]);
        i++;
    }
    free(entrenador);
    
    printf(CELESTE"\nAgregar 2 entrenadores al salon con 5 y 7 victorias respectivamente.\n"NORMAL);
    entrenador_t* entrenador_1 = calloc(1, sizeof(entrenador_t));
    entrenador_t* entrenador_2 = calloc(1, sizeof(entrenador_t));
    strcpy(entrenador_1->nombre, "entrenador_1");
    strcpy(entrenador_2->nombre, "entrenador_2");
    entrenador_1->victorias = 5;
    entrenador_2->victorias = 7;
    entrenador_1->equipo = NULL;
    entrenador_2->equipo = NULL;
    salon = salon_agregar_entrenador(salon, entrenador_1);
    salon = salon_agregar_entrenador(salon, entrenador_2);
     
    printf(CELESTE"\nObtener los entrenadores con al menos 5 ligas ganadas y mostrarlos por pantalla.\n"NORMAL);
    cantidad_minima_victorias= 5;
    entrenador=salon_obtener_entrenadores_mas_ganadores(salon,cantidad_minima_victorias);
    tamanio= vtrlen(entrenador);
    int j=0; 
    while(j<tamanio){
        salon_mostrar_entrenador(entrenador[j]);
        j++;
    }
    free(entrenador);
    
    printf(CELESTE"\nGuardar el salon a un nuevo archivo 'salon_modificado.sal'\n"NORMAL);
   
    salon_guardar_archivo(salon, NOMBRE_ARCHIVO_MODIFICADO);    
   
    printf(CELESTE"\nSalir con valor de retorno 0\n"NORMAL);
    salon_destruir(salon);
    return 0;
    
}
