Un README.txt que contenga:
• Una breve explicación de la solución imlplementada,
En este trabajo practico lo primero que hicimos fue crear las funciones de la biblioteca utiles.h con el fin de luego poder utilizarlas
en salon.c para asi crear otras nuevas funciones que luego finalmente aplicamos en el main.c. En casi todas las funciones tuvimos que 
usar memoria dinamica y asi fuimos aprendiendo a reservar memoria y a liberarla de manera correcta. El objetivo final era lo que hicimos 
en el main.c probar las funciones que habiamos hecho previamente creando un salon , mostrando por pantalla los entrenadores con ciertas
caracteristicas , agregando nuevos entrenadores y finalmente guardando todo el salon en nuevo archivo.

• Cualquier aclaración que necesite hacer acerca de la implementación realizada (decisiones de diseño) y que
su corrector necesite saber al corregir su trabajo.


• Un breve desarrollo de los siguientes temas teóricos:
1. Heap y stack: ¿Para qué y cómo se utiliza cada uno?

EL heap y el stack son areas de la memoria . El stack es una seccion de memoria estatica de un programa en ejecucion
donde de manera automatica se definen los ambitos de las funciones,se almacenan todas las variables locales y parametros
de las funciones que se encuentran en ejecucion, la memoria se reserva sola por el sistema operativo que la usa para pasar
informacion entre las distintas funciones que se ejecutan en un programa mientras que en el heap es reservada y 
controlada por el programador quien debe solicitarla de manera explicita al sistema operativo , esto ocurre ya que no se sabe 
con anticipacion la cantidad de memoria a ser reservada hasta el momento en que se necesita reservarla. En el heap es donde se 
encuntra la memoria dinamica y se usa mediante el uso de las funciones de la biblioteca standar de stdlib.h malloc(), realloc() y 
free().


2. Malloc/Realloc/Free: ¿Cómo y para qué se utilizan?

Malloc se utiliza para decirle al sistema operativo que se quiere utilizar memoria dinamica del heap, permite reservar la memoria ,
se encuentar dentro de la biblioteca de stdlib.h y al usarla devuelve un puntero a la memoria reservada. La memoria en este caso 
se inicializa.

Realloc es una funcion que se utiliza para solicitar mas memoria de la que ya le pedimos a malloc.Esta funcion nos puede devolver 
tres resultados. El primero seria que al pedirle que nos agrande el bloque de memoria nos devuleva el mismo bloque agrandado. El 
segundo caso seria que al pedirle que me agrande el bloque , al no poder agrandarlo me devuelva un bloque distinto al que yo le pase
pero con el tamaño solicitado. Y el tercer caso seria que no pueda darnos lo que le pedimos , osea que no pueda hacer ni el primer ni 
el segundo caso y entonces nos salta error.

Free se utiliza cuando una zona de memoria reservada previamente con malloc, calloc o realloc ya no se necesita y la funcion free 
lo que hace es liberar esa memoria . Es muy importante no olvidarse despues de reservar memoria usar free() al final de uso para 
liberarla.