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

//Se crea el diccionario en la memoria dinamica
Diccionario crear()
{
    Diccionario dict;
    dict = (char**)malloc(sizeof(char*)*NCasillas);
    for (int i = 0; i < NCasillas; i++)
    {
        dict[i] = (char*)malloc(sizeof(char)*25);
        dict[i] = vacio;
    }
    return dict;
}

//Funcion de hash que devuelve el lugar donde se debe insertar el valor
int h(char *cadena)
{
    int i = 0, suma = 0, hash = 0;
    while(cadena[i] != '\0')
    {
        suma = suma + (int) cadena[i];
        i++;
    }

    hash = suma%NCasillas;
    return hash;
}

//Esta funcion se utiliza para saber si un elemento ya es miembro de la tabla
int localiza(char*cadena, Diccionario dict)
{
    int i = 0, inicial = 0;
    inicial = h(cadena);
    while (i<NCasillas && strcmp(dict[(inicial+i)%NCasillas], cadena) != 0 && strcmp(dict[(inicial+i)%NCasillas],vacio) != 0)
    {
        i++;
    }
    return (inicial+i)%NCasillas;
}
//Esta funcion encuentra el sector para insertar el valor
int localiza1(char*cadena, Diccionario dict)
{
    int i = 0, inicial = 0;
    inicial = h(cadena);
    while (i<NCasillas && strcmp(dict[(inicial+i)%NCasillas], cadena) != 0 && strcmp(dict[(inicial+i)%NCasillas], vacio) != 0 && strcmp(dict[(inicial+i)%NCasillas],borrado) != 0)
    {
        i++;
    }
    return (inicial+i)%NCasillas;
}

//Funcion que booleana que notifica si un elemento es miembro o no
int miembro(char*cadena, Diccionario dict)
{
    if (strcmp(dict[localiza(cadena, dict)], cadena) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Funcion para insertar elementos
void insertar(char*cadena, Diccionario dict)
{
    int contenedor = 0;
    //Me fijo si el elemento ya es miembro
    if (strcmp(dict[localiza(cadena, dict)], cadena) == 0)
    {
        printf("Ya es miembro\n");
        return;
    }
    contenedor = localiza1(cadena, dict);
    //Si hay un lugar vacío inserto el elemento
    if(strcmp(dict[contenedor],vacio) == 0 || strcmp(dict[contenedor], borrado) == 0)
    {
        dict[contenedor] = cadena;
    }
    else
    {
        printf("Tabla llena\n");
    }
}

//Coloca BORRADO en el lugar del elemento
void suprime(char*cadena, Diccionario dict)
{
    int contenedor = 0;
    contenedor = localiza(cadena, dict);
    if(strcmp(dict[contenedor], cadena) == 0)
    {
        dict[contenedor] = borrado;
    }
}

//Libera la memoria dinamica
void destruirTablaHash(Diccionario dict)
{
    for (int i = 0; i < NCasillas; i++)
    {
        free(dict[i]);
    }
    free(dict); 
}

int main()
{
    Diccionario dict;
    dict = crear();

    char *cadena;
    cadena = (char*)malloc(sizeof(char)*10);
    printf("Ingrese la primer cadena: ");
    fgets(cadena, 9, stdin);
    insertar(cadena, dict);
    
    char *cadena2;
    cadena2 = (char*)malloc(sizeof(char)*10);
    printf("Ingrese la segunda cadena: ");
    fgets(cadena2, 9, stdin);
    insertar(cadena2, dict);
    
    char *cadena3;
    cadena3 = (char*)malloc(sizeof(char)*10);
    printf("Ingrese la tercer cadena: ");
    fgets(cadena3, 9, stdin);
    insertar(cadena3, dict);

    printf("Se suprime la segunda cadena\n");
    suprime(cadena2, dict);
    printf("Ingrese la cuarta cadena: ");
    fgets(cadena2, 9, stdin);
    insertar(cadena2, dict);
    printf("Se suprime la tercer cadena\n");
    suprime(cadena3, dict);
    printf("Ingrese la quinta cadena: ");
    fgets(cadena3, 9, stdin);
    insertar(cadena3, dict);
    
    printf("Verifique que una cadena esta en la tabla: ");
    char *cadena4;
    cadena4 = (char*)malloc(sizeof(char)*10);
    fgets(cadena4, 9, stdin);
    if (miembro(cadena4, dict) == 1)
    {
        printf("Es miembro\n");
    }
    else
    {
        printf("No es miembro\n");
    }

    printf("La lista es: \n");
    for (int i = 0; i < NCasillas; i++)
    {
        printf("%d. %s\n", i, dict[i]);
    }
    
    destruirTablaHash(dict);
    free(cadena);
    free(cadena2);
    free(cadena3);
    free(cadena4);

    return 0;
}