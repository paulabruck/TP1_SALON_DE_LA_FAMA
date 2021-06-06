#include "pa2mm.h"
#include "util.h"
#include <string.h>
#include "salon.h"

////////// Vectores

void vtrlen_cuenta_los_punteros_de_un_vector(){
    void* vector[] = {(void*)1,(void*)2,(void*)3,(void*)4,(void*)5,NULL};

    pa2m_afirmar(vtrlen(vector)==5, "vtrlen devuelve la cantidad de punteros no nulos de un vector de punteros.");
    pa2m_afirmar(vtrlen(NULL)==0, "vtrlen de un vector nulo es 0.");
}

void vtradd_agrega_punteros_a_un_vector(){
    void** vtr = NULL;

    pa2m_afirmar((vtr = vtradd(vtr, (void*)1)) != NULL, "vtradd de un vector nulo resulta en un nuevo vector.");
    pa2m_afirmar(vtrlen(vtr)==1, "el nuevo vector tiene longitud 1.");

    pa2m_afirmar((vtr = vtradd(vtr, (void*)2)), "vtradd de otro elemento en el vector resulta en un vector no nulo.");
    pa2m_afirmar(vtrlen(vtr)==2, "el nuevo vector tiene longitud 2.");

    pa2m_afirmar((vtr = vtradd(vtr, (void*)3)), "vtradd de otro elemento en el vector resulta en un vector no nulo.");
    pa2m_afirmar(vtrlen(vtr)==3, "el nuevo vector tiene longitud 3.");

    pa2m_afirmar(vtr[0]==(void*)1, "El primer elemento del vector es el primer elemento agregado.");
    pa2m_afirmar(vtr[1]==(void*)2, "El segundo elemento del vector es el segundo elemento agregado.");
    pa2m_afirmar(vtr[2]==(void*)3, "El tercer elemento del vector es el tercer elemento agregado.");
    free(vtr);
}

void split_divide_un_string_en_un_vector(){
    const char* texto = "Pikachu;999;1";

    char** elementos = NULL;

    pa2m_afirmar((elementos = split(texto, ';')) != NULL, "split sobre un texto no vacío resulta en un vector de elementos");
    pa2m_afirmar(vtrlen(elementos)==3, "Se obtuvo un vector de 3 elementos");

    pa2m_afirmar(strcmp(elementos[0], "Pikachu")==0, "El primer elemento es Pikachu");
    pa2m_afirmar(strcmp(elementos[1], "999")==0, "El segundo elemento es 999");
    pa2m_afirmar(strcmp(elementos[2], "1")==0, "El tercer elemento es 1");

    vtrfree(elementos);
}

void split_devuelve_un_vector_con_el_mismo_string_si_no_existe_el_separador(){
    const char* texto = "Pikachu9991";
    char** elementos = NULL;

    pa2m_afirmar((elementos = split(texto, ';')) != NULL, "split sobre un texto sin separador devuelve un vector");
    pa2m_afirmar(vtrlen(elementos)==1, "Se obtuvo un vector de 1 elemento");

    pa2m_afirmar(strcmp(elementos[0], texto)==0, "El unico elemento del vector es el string completo");

    vtrfree(elementos);
}

void split_divide_correctamente_campos_vacios(){
    const char* texto = "Pikachu;;1;";
    char** elementos = NULL;

    pa2m_afirmar((elementos = split(texto, ';')) != NULL, "split sobre un texto con campos vacíos devuelve un vector");
    pa2m_afirmar(vtrlen(elementos)==4, "Se obtuvo un vector de 4 elementos");

    pa2m_afirmar(strcmp(elementos[0], "Pikachu")==0, "El primer elemento del vector es el primer elemento del string");
    pa2m_afirmar(strcmp(elementos[1], "")==0, "El segundo elemento del vector es un elemento vacío");
    pa2m_afirmar(strcmp(elementos[2], "1")==0, "El tercer elemento del vector es un el tercer elemento del string");
    pa2m_afirmar(strcmp(elementos[3], "")==0, "El cuarto elemento del vector es un elemento vacío");

    vtrfree(elementos);
}

void split_de_un_string_vacio_devuelve_null(){
    pa2m_afirmar(split("", ';')==NULL, "Split de un string vacío es null");
}

void split_de_null_devuelve_null(){
    pa2m_afirmar(split(NULL, ';')==NULL, "Split de un string null es null");
}

void pruebas_vectores(){
    pa2m_nuevo_grupo("Pruebas de vectores");

    pa2m_nuevo_grupo("vtrlen:");
    vtrlen_cuenta_los_punteros_de_un_vector();

    pa2m_nuevo_grupo("vtradd:");
    vtradd_agrega_punteros_a_un_vector();

    pa2m_nuevo_grupo("split:");
    split_divide_un_string_en_un_vector();
    split_devuelve_un_vector_con_el_mismo_string_si_no_existe_el_separador();
    split_divide_correctamente_campos_vacios();
    split_de_un_string_vacio_devuelve_null();
    split_de_null_devuelve_null();
}

////////// Archivos

void fgets_alloc_lee_lineas_completas(){
    FILE* archivo = fopen("archivos_prueba/una_linea.txt", "r");

    if(!archivo){
        pa2m_afirmar(0, "No se pudo abrir el archivo una_linea.txt");
        return;
    }

    char* linea = NULL;

    pa2m_afirmar((linea = fgets_alloc(archivo))!=NULL, "Puedo leer una línea completa de un archivo de texto.");
    pa2m_afirmar((strcmp(linea, "abcdefghijklmnopqrstuvwxyz1234567890\n"))==0, "La línea se leyó completa");
    free(linea);

    pa2m_afirmar((linea = fgets_alloc(archivo))==NULL, "No puedo leer una segunda línea.");

    fclose(archivo);
}

void fgets_alloc_lee_lineas_hasta_finalizar_el_archivo(){
    FILE* archivo = fopen("archivos_prueba/numeros.txt", "r");

    if(!archivo){
        pa2m_afirmar(0, "No se pudo abrir el archivo numeros.txt");
        return;
    }

    char* linea = NULL;

    pa2m_afirmar((linea = fgets_alloc(archivo))!=NULL, "Puedo leer la primer línea de un archivo de 3 lineas.");
    pa2m_afirmar((strcmp(linea, "0\n"))==0, "La línea se leyó completa");
    free(linea);

    pa2m_afirmar((linea = fgets_alloc(archivo))!=NULL, "Puedo leer la segunda línea.");
    pa2m_afirmar((strcmp(linea, "1\n"))==0, "La línea se leyó completa");
    free(linea);

    pa2m_afirmar((linea = fgets_alloc(archivo))!=NULL, "Puedo leer la tercer línea.");
    pa2m_afirmar((strcmp(linea, "2"))==0, "La última línea se leyó completa");
    free(linea);

    fclose(archivo);
}

void fgets_alloc_lee_lineas_muy_largas(){
    FILE* archivo = fopen("archivos_prueba/linea_larga.txt", "r");
    char* linea_larga = "asdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwuasdhajkshdklasjdhjkasdasgfjklsdfgafhajklgfjksdgfwuefuwgfkusgfiu4789r2g34ryof4rybwe8rwiyrnwieyrcnlwflacnerufhaevuhfkaeiyfaihfoawiehrfnlaciwehrilawecrfnweyhnflahfnoviahfmocawhefiomacweofhxoaweihfnoaiweyraweriuaweioruaioweurioaweuriaweuriwu";

    if(!archivo){
        pa2m_afirmar(0, "No se pudo abrir el archivo linea_larga.txt");
        return;
    }

    char* linea = NULL;

    pa2m_afirmar((linea = fgets_alloc(archivo))!=NULL, "Puedo leer una línea de un archivo con una línea larga de texto");
    pa2m_afirmar((strcmp(linea, linea_larga))==0, "La línea se leyó completa");
    free(linea);

    fclose(archivo);
}

void pruebas_archivos(){

    pa2m_nuevo_grupo("Pruebas de archivos");
    pa2m_nuevo_grupo("fgets_alloc");

    fgets_alloc_lee_lineas_completas();
    fgets_alloc_lee_lineas_hasta_finalizar_el_archivo();
    fgets_alloc_lee_lineas_muy_largas();
}

////////// Salon

int verificar_entrenador(entrenador_t* entrenador, const char* nombre, int victorias, int cantidad_pokemon){
    return strcmp(entrenador->nombre, nombre)==0 &&
        entrenador->victorias == victorias &&
        vtrlen(entrenador->equipo)==cantidad_pokemon;
}

int verificar_pokemon(pokemon_t* pokemon, const char* nombre, int nivel, int def, int str, int itg, int spd){
    return strcmp(pokemon->nombre, nombre)==0 &&
        pokemon->nivel == nivel &&
        pokemon->defensa == def &&
        pokemon->fuerza == str &&
        pokemon->inteligencia == itg &&
        pokemon->velocidad == spd;
}

void salon_leer_archivo_inexistente_devuelve_null(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("archivos_prueba/asdasdasdasdasdasdasd.asd")) == NULL, "Leer un archivo inexistente devuelve un salon nulo.");
}

void salon_leer_archivo_carga_correctamente_un_archivo_con_1e_y_1p(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("archivos_prueba/salon_1e_1p.txt")) != NULL, "Puedo leer un archivo con 1 entrenador y 1 pokemon");

    pa2m_afirmar(vtrlen(salon->entrenadores)==1, "El salon resultante tiene 1 entrenador");

    entrenador_t* entrenador = salon->entrenadores[0];
    pa2m_afirmar(verificar_entrenador(entrenador, "entrenador1", 33, 1), "El primer entrenador se llama entrenador1, tiene 33 victorias y 1 pokemon");

    pokemon_t* pokemon = entrenador->equipo[0];
    pa2m_afirmar(verificar_pokemon(pokemon, "pokemon1", 1, 2, 3, 4, 5), "El pokemon se llama pokemon1, tiene nivel 1, defensa 2, fuerza 3, inteligencia 4 y velocidad 5");

    salon_destruir(salon);
}

void salon_leer_archivo_carga_correctamente_un_archivo_con_3e_sin_p(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("archivos_prueba/salon_3e.txt")) != NULL, "Puedo leer un archivo con 3 entrenadores sin pokemon");

    pa2m_afirmar(vtrlen(salon->entrenadores)==3, "El salon resultante tiene 3 entrenadores");

    entrenador_t* entrenador1 = salon->entrenadores[0];
    pa2m_afirmar(verificar_entrenador(entrenador1, "entrenador1", 1, 0), "El primer entrenador se llama entrenador1, tiene 1 victoria y 0 pokemon");

    entrenador_t* entrenador2 = salon->entrenadores[1];
    pa2m_afirmar(verificar_entrenador(entrenador2, "entrenador2", 2, 0), "El segundo entrenador se llama entrenador2, tiene 2 victorias y 0 pokemon");

    entrenador_t* entrenador3 = salon->entrenadores[2];
    pa2m_afirmar(verificar_entrenador(entrenador3, "entrenador3", 3, 0), "El tercer entrenador se llama entrenador3, tiene 3 victorias y 0 pokemon");

    salon_destruir(salon);
}

void salon_leer_archivo_carga_correctamente_un_archivo_con_2e_y_2p(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("archivos_prueba/salon_2e_2p.txt")) != NULL, "Puedo leer un archivo con 2 entrenadores y 2 pokemon cada uno");

    pa2m_afirmar(vtrlen(salon->entrenadores)==2, "El salon resultante tiene 2 entrenadores");

    entrenador_t* entrenador1 = salon->entrenadores[0];
    pa2m_afirmar(verificar_entrenador(entrenador1, "entrenador1", 33, 2), "El primer entrenador se llama entrenador1, tiene 33 victorias y 2 pokemon");

    pokemon_t* pokemon1 = entrenador1->equipo[0];
    pa2m_afirmar(verificar_pokemon(pokemon1, "pokemon1", 1, 2, 3, 4, 5), "El primer pokemon se llama pokemon1, tiene nivel 1, defensa 2, fuerza 3, inteligencia 4 y velocidad 5");

    pokemon_t* pokemon2 = entrenador1->equipo[1];
    pa2m_afirmar(verificar_pokemon(pokemon2, "pokemon2", 5, 4, 3, 2, 1), "El segundo pokemon se llama pokemon2, tiene nivel 5, defensa 4, fuerza 3, inteligencia 2 y velocidad 1");

    entrenador_t* entrenador2 = salon->entrenadores[1];
    pa2m_afirmar(verificar_entrenador(entrenador2, "entrenador2", 38, 2), "El primer entrenador se llama entrenador1, tiene 38 victorias y 2 pokemon");

    pokemon_t* pokemon3 = entrenador2->equipo[0];
    pa2m_afirmar(verificar_pokemon(pokemon3, "pokemon3", 6, 7, 8, 9, 10), "El primer pokemon se llama pokemon3, tiene nivel 6, defensa 7, fuerza 8, inteligencia 9 y velocidad 10");

    pokemon_t* pokemon4 = entrenador2->equipo[1];
    pa2m_afirmar(verificar_pokemon(pokemon4, "pokemon4", 11, 12, 130, 14, 15), "El segundo pokemon se llama pokemon4, tiene nivel 11, defensa 12, fuerza 130, inteligencia 14 y velocidad 15");

    salon_destruir(salon);
}

void salon_agregar_entrenador_agrega_un_entrenador_null_devuelve_null(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("archivos_prueba/salon_3e.txt")) != NULL, "Leo un archivo de salon");

    pa2m_afirmar(vtrlen(salon->entrenadores)==3, "El salon tiene 3 entrenadores");

    entrenador_t* entrenador_null = NULL;

    pa2m_afirmar(salon_agregar_entrenador(salon, entrenador_null) == NULL, "No puedo agregar un entrenador nulo al salon");

    pa2m_afirmar(vtrlen(salon->entrenadores)==3, "El salon sigue teniendo  3 entrenadores");

    salon_destruir(salon);
}

void salon_agregar_entrenador_a_salon_null_devuelve_null(){
    salon_t* salon = NULL;

    entrenador_t entrenador;

    pa2m_afirmar(salon_agregar_entrenador(salon, &entrenador) == NULL, "No puedo agregar un entrenador a un salon NULL.");
}

void salon_agregar_entrenador_agrega_un_entrenador_en_orden(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("archivos_prueba/salon_3e.txt")) != NULL, "Leo un archivo de salon");

    pa2m_afirmar(vtrlen(salon->entrenadores)==3, "El salon tiene 3 entrenadores");

    entrenador_t* entrenador1 = calloc(1, sizeof(entrenador_t));
    entrenador1->victorias = 0;

    pa2m_afirmar(salon_agregar_entrenador(salon, entrenador1) == salon, "Puedo agregar un entrenador con 0 victorias al salon");

    pa2m_afirmar(vtrlen(salon->entrenadores)==4, "El salon tiene 4 entrenadores");

    pa2m_afirmar(salon->entrenadores[0] == entrenador1, "El entrenador se insertó en la primer posición");

    entrenador_t* entrenador2 = calloc(1, sizeof(entrenador_t));
    entrenador2->victorias = 10;

    pa2m_afirmar(salon_agregar_entrenador(salon, entrenador2) == salon, "Puedo agregar un entrenador con 10 victorias al salon");

    pa2m_afirmar(vtrlen(salon->entrenadores)==5, "El salon tiene 5 entrenadores");
    pa2m_afirmar(salon->entrenadores[4] == entrenador2, "El entrenador se insertó en la ultima posición");

    entrenador_t* entrenador3 = calloc(1, sizeof(entrenador_t));
    entrenador3->victorias = 3;

    pa2m_afirmar(salon_agregar_entrenador(salon, entrenador3) == salon, "Puedo agregar un entrenador con 3 victorias al salon");

    pa2m_afirmar(vtrlen(salon->entrenadores)==6, "El salon tiene 6 entrenadores");
    pa2m_afirmar(salon->entrenadores[4] == entrenador3, "El entrenador se insertó en la posición esperada");

    salon_destruir(salon);
}

void salon_obtener_entrenadores_obtiene_entrenadores_segun_victorias(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("archivos_prueba/salon_6e.txt")) != NULL, "Leo un archivo de salon");

    entrenador_t** entrenadores = NULL;

    pa2m_afirmar((entrenadores = salon_obtener_entrenadores_mas_ganadores(salon, 5)), "Puedo obtener los entrenadores que ganaron 5 o mas ligas");

    pa2m_afirmar(vtrlen(entrenadores)==3, "La cantidad de entrenadores encontrados es 3");

    entrenador_t** entrenadores2 = NULL;
    entrenadores2 = salon_obtener_entrenadores_mas_ganadores(salon, 150);
    pa2m_afirmar(vtrlen(entrenadores2)==0, "La cantidad de entrenadores que ganaron por lo menos 150 ligas es 0");

    free(entrenadores);
    free(entrenadores2);
    salon_destruir(salon);
}

void salon_guardar_archivo_guarda_los_entrenadores_a_un_archivo(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("archivos_prueba/salon_2e_2p.txt")) != NULL, "Puedo leer un archivo con 2 entrenadores y 2 pokemon cada uno");

    pa2m_afirmar((salon_guardar_archivo(salon, "salon_temporal.test")) == 2, "Puedo guardar el salon a un archivo y devuelve 2 (la cantidad de entrenadores)");

    salon_destruir(salon);

    pa2m_afirmar((salon = salon_leer_archivo("salon_temporal.test")) != NULL, "Puedo leer el archivo recien escrito");

    pa2m_afirmar(vtrlen(salon->entrenadores)==2, "El salon resultante tiene 2 entrenadores");

    entrenador_t* entrenador1 = salon->entrenadores[0];
    pa2m_afirmar(verificar_entrenador(entrenador1, "entrenador1", 33, 2), "El primer entrenador se llama entrenador1, tiene 33 victorias y 2 pokemon");

    pokemon_t* pokemon1 = entrenador1->equipo[0];
    pa2m_afirmar(verificar_pokemon(pokemon1, "pokemon1", 1, 2, 3, 4, 5), "El primer pokemon se llama pokemon1, tiene nivel 1, defensa 2, fuerza 3, inteligencia 4 y velocidad 5");

    pokemon_t* pokemon2 = entrenador1->equipo[1];
    pa2m_afirmar(verificar_pokemon(pokemon2, "pokemon2", 5, 4, 3, 2, 1), "El segundo pokemon se llama pokemon2, tiene nivel 5, defensa 4, fuerza 3, inteligencia 2 y velocidad 1");

    entrenador_t* entrenador2 = salon->entrenadores[1];
    pa2m_afirmar(verificar_entrenador(entrenador2, "entrenador2", 38, 2), "El primer entrenador se llama entrenador1, tiene 38 victorias y 2 pokemon");

    pokemon_t* pokemon3 = entrenador2->equipo[0];
    pa2m_afirmar(verificar_pokemon(pokemon3, "pokemon3", 6, 7, 8, 9, 10), "El primer pokemon se llama pokemon3, tiene nivel 6, defensa 7, fuerza 8, inteligencia 9 y velocidad 10");

    pokemon_t* pokemon4 = entrenador2->equipo[1];
    pa2m_afirmar(verificar_pokemon(pokemon4, "pokemon4", 11, 12, 130, 14, 15), "El segundo pokemon se llama pokemon4, tiene nivel 11, defensa 12, fuerza 130, inteligencia 14 y velocidad 15");

    salon_destruir(salon);
}

void pruebas_salon(){

    pa2m_nuevo_grupo("Pruebas de salon");

    pa2m_nuevo_grupo("salon_leer_archivo inexistente");
    salon_leer_archivo_inexistente_devuelve_null();

    pa2m_nuevo_grupo("salon_leer_archivo 1 entrenador con 1 pokemon");
    salon_leer_archivo_carga_correctamente_un_archivo_con_1e_y_1p();

    pa2m_nuevo_grupo("salon_leer_archivo 3 entrenadores sin pokemon");
    salon_leer_archivo_carga_correctamente_un_archivo_con_3e_sin_p();

    pa2m_nuevo_grupo("salon_leer_archivo 2 entrenadores con 2 pokemon cada uno");
    salon_leer_archivo_carga_correctamente_un_archivo_con_2e_y_2p();

    pa2m_nuevo_grupo("salon_agregar_entrenador devuelve null al agregar entrenadores nulos");
    salon_agregar_entrenador_agrega_un_entrenador_null_devuelve_null();

    pa2m_nuevo_grupo("salon_agregar_entrenador devuelve null si el salon es null");
    salon_agregar_entrenador_a_salon_null_devuelve_null();

    pa2m_nuevo_grupo("salon_agregar_entrenador agrega un entrenador de forma ordenada segun las victorias");
    salon_agregar_entrenador_agrega_un_entrenador_en_orden();

    pa2m_nuevo_grupo("salon_obtener_entrenadores obtiene los entrenadores segun las victorias especificadas");
    salon_obtener_entrenadores_obtiene_entrenadores_segun_victorias();

    pa2m_nuevo_grupo("salon_guardar_archivo guarda un archivo con los datos del salon");
    salon_guardar_archivo_guarda_los_entrenadores_a_un_archivo();
    
    
}

int main(){

    pruebas_vectores();

    pruebas_archivos();

    pruebas_salon();


    return pa2m_mostrar_reporte();
}
