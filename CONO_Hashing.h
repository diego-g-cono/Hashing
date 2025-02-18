#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NCasillas 25
static char *vacio = "          ";
static char *borrado = "**********";
typedef char** Diccionario;

Diccionario crear ();
void destruirTablaHash (Diccionario);
void suprime (char*, Diccionario);
int h(char*);
int localiza (char*, Diccionario);
int localiza1 (char*, Diccionario);
int miembro (char*, Diccionario);
void inserta (char*, Diccionario);