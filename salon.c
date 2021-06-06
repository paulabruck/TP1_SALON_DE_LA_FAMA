#include "salon.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CAMPOS_ENTRENADOR 2
#define CAMPOS_POKEMON 6
#define FORMATO_ENTRENADORES "%s;%d\n"
#define FORMATO_POKEMONES "%s;%d;%d;%d;%d;%d\n"
#define AMARILLO "\x1b[33m"
#define AZUL "\x1b[34m"
#define PURPURA "\x1b[35m"
#define CELESTE "\x1b[36m"
#define NORMAL "\x1b[0m"
#define ROJO "\x1b[31m"

const char SEPARADOR =';';

entrenador_t* reservar_memoria_entrenador(char** str_dividido,  entrenador_t* entrenador){
    entrenador= calloc(1, sizeof(entrenador_t));
    if(!entrenador){
        free(entrenador);
        return NULL;
    }
    strcpy(entrenador->nombre, str_dividido[0]);
    entrenador->victorias= atoi(str_dividido[1]);
    return entrenador;
}
pokemon_t* reservar_memoria_pokemones(char** str_dividido, pokemon_t* pokemon){
    pokemon= calloc(1, sizeof(pokemon_t));
    if(!pokemon){
        free(pokemon);
        return NULL;
    }
    strcpy(pokemon->nombre, str_dividido[0]);
    pokemon->nivel= atoi(str_dividido[1]);
    pokemon->defensa= atoi(str_dividido[2]);
    pokemon->fuerza= atoi(str_dividido[3]);
    pokemon->inteligencia= atoi(str_dividido[4]);
    pokemon->velocidad= atoi(str_dividido[5]);
    return pokemon;
}
salon_t* salon_leer_archivo(const char* nombre_archivo){
    if(!nombre_archivo){
        return NULL;
    }
    salon_t* salon= calloc(1, sizeof(salon_t));
    FILE* archivo;
    archivo = fopen(nombre_archivo, "r");
    if(!archivo){
        vtrfree(salon);
        return NULL;
    }    
    char* str= calloc(1, sizeof(char*));
    char** str_divido=NULL;

    entrenador_t* entrenador=NULL;
    entrenador_t* entrenador_aux;
    pokemon_t* pokemon=NULL;
    pokemon_t* pokemon_aux;
    salon->entrenadores=NULL;
    int i= -1;
    str= fgets_alloc(archivo);
    while (str!=NULL){
        str_divido=split(str, SEPARADOR);
        if(vtrlen(str_divido)== CAMPOS_ENTRENADOR){
            i++;
            entrenador_aux=  reservar_memoria_entrenador(str_divido, entrenador);
            salon->entrenadores= vtradd(salon->entrenadores, entrenador_aux);   
        }else if(vtrlen(str_divido)==CAMPOS_POKEMON){
            pokemon_aux= reservar_memoria_pokemones(str_divido, pokemon);
            salon->entrenadores[i]->equipo= vtradd(salon->entrenadores[i]->equipo, pokemon_aux);   
        }else{
            return NULL;
        }    
        free(str);
        vtrfree(str_divido);
        str= fgets_alloc(archivo);
    }
    free(str); 
    fclose(archivo);
    return salon;  
}    
int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    FILE* archivo;
    archivo = fopen(nombre_archivo, "w");
    if(!archivo){
        return -1;
    }   
    for(int i=0; i<vtrlen(salon->entrenadores);i++){
        fprintf(archivo, FORMATO_ENTRENADORES,salon->entrenadores[i]->nombre, salon->entrenadores[i]->victorias);
        for(int j=0; j<vtrlen(salon->entrenadores[i]->equipo);j++){
            fprintf(archivo, FORMATO_POKEMONES, salon->entrenadores[i]->equipo[j]->nombre, salon->entrenadores[i]->equipo[j]->nivel,
            salon->entrenadores[i]->equipo[j]->defensa, salon->entrenadores[i]->equipo[j]->fuerza, salon->entrenadores[i]->equipo[j]->inteligencia,
            salon->entrenadores[i]->equipo[j]->velocidad);
        }  
    }
    int cantidad_entrenadores=(int)vtrlen(salon->entrenadores);
    fclose(archivo);
    return cantidad_entrenadores;
}
salon_t* ordenar_entrenadores(salon_t* salon, int tamanio){
    entrenador_t* aux ;
     for(int i=0; i<tamanio;i++){
        for(int j=0; j<(tamanio-i-1);j++){
            if(salon->entrenadores[j]->victorias > salon->entrenadores[j+1]->victorias){
                aux = salon->entrenadores[j];
                salon->entrenadores[j]= salon->entrenadores[j+1];
                salon->entrenadores[j+1]= aux;
            }
        }
    }
    return salon;
}
salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!entrenador){
        return NULL;
    }
    if(!salon){
        return NULL;
    }
    salon->entrenadores = vtradd(salon->entrenadores, entrenador);
    int tamanio= (int)vtrlen(salon->entrenadores);
    ordenar_entrenadores(salon, tamanio);
    return salon;
}
entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias){
    size_t tamanio= vtrlen(salon->entrenadores);
    if(!tamanio){
        return NULL;
    }
    int i =0;
    entrenador_t** entrenador_aux= calloc(1, sizeof(entrenador_t*));
    while(i<tamanio){
        if(salon->entrenadores[i]->victorias >= cantidad_minima_victorias){
            entrenador_aux= vtradd(entrenador_aux, salon->entrenadores[i]);
        }
        i++;
    }
    return entrenador_aux;
}
void salon_mostrar_entrenador(entrenador_t* entrenador){
    printf("\n");
    printf(AZUL"NOMBRE ENTRENADOR:%s\n"NORMAL, entrenador->nombre);
    printf(PURPURA"LIGAS GANADAS: %i\n"NORMAL, entrenador->victorias);
    size_t tamanio= vtrlen(entrenador->equipo);
    int j=0;
    while(j< tamanio){
        printf(ROJO"EQUIPO DE POKEMONES: %s\n"NORMAL, (char*)entrenador->equipo[j]->nombre);
        printf(AMARILLO"NIVEL: %d\n"NORMAL, entrenador->equipo[j]->nivel);
        printf(AMARILLO"FUERZA: %d\n"NORMAL, entrenador->equipo[j]->fuerza);
        printf(AMARILLO"DEFENSA: %d\n"NORMAL, entrenador->equipo[j]->defensa);
        printf(AMARILLO"INTELIGENCIA: %d\n"NORMAL, entrenador->equipo[j]->inteligencia);
        printf(AMARILLO"VELOCIDAD: %d\n"NORMAL, entrenador->equipo[j]->velocidad);
        j++;
    } 
}
void salon_destruir(salon_t* salon){
    int i=0;
    size_t tamanio= vtrlen(salon->entrenadores);
    while(i<tamanio){
        vtrfree(salon->entrenadores[i]->equipo);
        free(salon->entrenadores[i]);
        i++;
    }
    free(salon->entrenadores);
    free(salon);
}
