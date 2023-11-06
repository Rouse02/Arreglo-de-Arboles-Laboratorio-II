#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

///DEFINE DE ESPECIES
#define DIM 30
#define NOMBRE_ARCHIVO  "animales.dat"

///ESTRUCTURAS:
typedef struct {
   char animal[30];
   int cant;
   int habitat;
   int idEspecie;
   char especie[20];
} registroArchivo;

typedef struct {
    char nombreAnimal [30];
	int cantidad;
	int habitat;
} animal;

typedef struct { /// 1 - selva, 2- savana, 3-bosque, 4-mar
   animal animales;
   struct nodoArbol * izq;
   struct nodoArbol * der;
} nodoArbol;

typedef struct { /// "Mamiferos", "Aves", "Reptiles", "Peces" y "Anfibios"
   int idEspecie;
   char especie [20];
   nodoArbol * arbolDeAnimales;
} celdaEspecie;

///Prototipado
nodoArbol *crearNodoArbol(nodoArbol *ptrArbol, animal infoAnimales);
nodoArbol *insertarAnimalEnArbol(nodoArbol *ptrArbol, animal infoAnimal);
int buscarEspecie(celdaEspecie arregloEspecies[], int validos, char especieBuscada[]);
/**--------------------------------------------------------------------------------**/
int main(){

    /*Debug: Mostrar el Archivo de Animales.dat*/
    char nombreArchivoAnimales[] = {"animales.dat"};
    //mostrarArchivo(nombreArchivoAnimales);

    /*Declaración e inicialización del ArregloDeEspecies*/
    celdaEspecie arregloEspecies[DIM];
    int validosArregloEspecies = 0;
    inicializarArregloEspecies(arregloEspecies);
    //mostrarArregloDeEspecies(arregloEspecies, validosArregloEspecies);

    /*Pasar la información del Archivo al ArregloEspecies*/
    pasarDeArchivoToTDA(arregloEspecies, &validosArregloEspecies, nombreArchivoAnimales);
//    mostrarArregloDeEspecies(arregloEspecies, validosArregloEspecies);

    /*Pasar todas las especies a un Archivo particular*/
    int indiceEspecie;

    char especieAves[] = {"Aves.bin"};
    char nombreEspecieAves[] = {"Aves"};
    indiceEspecie = buscarEspecie(arregloEspecies, validosArregloEspecies, nombreEspecieAves);
    cargarArchivoConAnimales(especieAves, arregloEspecies[indiceEspecie].arbolDeAnimales);
    printf("MOSTRANDO ARCHIVO DE AVES \n\n");
    mostrarArchivoAnimales(especieAves);

    char especieMamiferos[] = {"Mamiferos.bin"};
    char nombreEspecieMamiferos[] = {"Mamiferos"};
    indiceEspecie = buscarEspecie(arregloEspecies, validosArregloEspecies, nombreEspecieMamiferos);
    cargarArchivoConAnimales(especieMamiferos, arregloEspecies[indiceEspecie].arbolDeAnimales);
    printf("MOSTRANDO ARCHIVO DE MAMIFEROS \n\n");
    mostrarArchivoAnimales(especieMamiferos);

    char especieReptiles[] = {"Reptiles.bin"};
    char nombreEspecieReptiles[] = {"Reptiles"};
    indiceEspecie = buscarEspecie(arregloEspecies, validosArregloEspecies, nombreEspecieReptiles);
    cargarArchivoConAnimales(especieReptiles, arregloEspecies[indiceEspecie].arbolDeAnimales);
    printf("MOSTRANDO ARCHIVO DE REPTILES \n\n");
    mostrarArchivoAnimales(especieReptiles);

    char especiePeces[] = {"Peces.bin"};
    char nombreEspeciePeces[] = {"Peces"};
    indiceEspecie = buscarEspecie(arregloEspecies, validosArregloEspecies, nombreEspeciePeces);
    cargarArchivoConAnimales(especiePeces, arregloEspecies[indiceEspecie].arbolDeAnimales);
    printf("MOSTRANDO ARCHIVO DE PECES \n\n");
    mostrarArchivoAnimales(especiePeces);
}
/**--------------------------------------------------------------------------------**/
///FUNCIONES

void mostrarArchivo(char nombreArchivoAnimales[]){

    FILE *ptrArchivo = fopen(nombreArchivoAnimales, "rb");
    registroArchivo registro;
    int contadorAnimales = 0;
    if(ptrArchivo == NULL) printf("\nError al abrir el Archivo \n\n");

    else {
        while(fread(&registro, sizeof(registroArchivo), 1, ptrArchivo) == 1) {

            mostrarRegistro(registro);
            contadorAnimales++;
        }

        fclose(ptrArchivo);
    }

    printf("Cantidad de animales mostrados: %i \n\n", contadorAnimales);
}

void mostrarRegistro(registroArchivo registro){
    printf("\n.................................................\n");
    printf("ESPECIE: %s\n", registro.especie);
    printf("ID ESPECIE: %i\n\n", registro.idEspecie);
    printf("ANIMAL: %s\n", registro.animal);
    printf("CANTIDAD: %i\n", registro.cant);
    printf("HABITAT: %i", registro.habitat);
    printf("\n.................................................\n");
}

void inicializarArbol(nodoArbol **ptrArbol){

    *ptrArbol = NULL;
}

nodoArbol *crearNodoArbol(nodoArbol *ptrArbol, animal infoAnimales) {

    nodoArbol *nuevoNodo = (nodoArbol *) malloc(sizeof(nodoArbol));

    strcpy(nuevoNodo->animales.nombreAnimal, infoAnimales.nombreAnimal);
    nuevoNodo->animales.cantidad = infoAnimales.cantidad;
    nuevoNodo->animales.habitat = infoAnimales.habitat;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;

    return nuevoNodo;
}

nodoArbol *insertarAnimalEnArbol(nodoArbol *ptrArbol, animal infoAnimal) {

    if(ptrArbol == NULL) ptrArbol = crearNodoArbol(ptrArbol, infoAnimal);

    else {
        if(infoAnimal.cantidad > ptrArbol->animales.cantidad) ptrArbol->der = insertarAnimalEnArbol(ptrArbol->der, infoAnimal);

        else ptrArbol->izq = insertarAnimalEnArbol(ptrArbol->izq, infoAnimal);
    }
    return ptrArbol;
}

void inicializarArregloEspecies(celdaEspecie arregloEspecies[]) {

    for(int i = 0; i < DIM; i++) {

        strcpy(arregloEspecies[i].especie, " ");
        arregloEspecies[i].idEspecie = -1;
        inicializarArbol(&(arregloEspecies[i].arbolDeAnimales));
    }
}

void mostrarArbolInOrden(nodoArbol *ptrArbol) {

    if(ptrArbol != NULL) {
        mostrarArbolInOrden(ptrArbol->izq);
        printf("Nombre Animal: %s\n", ptrArbol->animales.nombreAnimal);
        printf("Cantidad Animales: %i\n", ptrArbol->animales.cantidad);
        printf("Nro Habitat: %i\n\n", ptrArbol->animales.habitat);
        mostrarArbolInOrden(ptrArbol->der);
    }
}

void mostrarArregloDeEspecies(celdaEspecie arregloEspecies[], int validos) {

    for(int i = 0; i < validos; i++) {

        printf("...................................................................\n");
        printf("\nARREGLO EN LA POSICION: |%i| \n\n", i);
        printf("Nombre Especie: %s \n", arregloEspecies[i].especie);
        printf("ID Especie: %i \n\n", arregloEspecies[i].idEspecie);

        if(arregloEspecies[i].arbolDeAnimales == NULL) printf("No hay animales registrados\n");

        else {
            printf("ARBOL DE ANIMALES DE LA ESPECIE: |%s| \n\n", arregloEspecies[i].especie);
            mostrarArbolInOrden(arregloEspecies[i].arbolDeAnimales);
            printf("...................................................................\n");
        }
    }
}

int buscarEspecie(celdaEspecie arregloEspecies[], int validos, char especieBuscada[]) {

    for(int i = 0; i < validos; i++) if(strcmp(arregloEspecies[i].especie, especieBuscada) == 0) return i;

    return -1;
}

void copiarInfoAnimal(registroArchivo infoRegistroArchivo, animal *infoAnimal) {

    strcpy(infoAnimal->nombreAnimal, infoRegistroArchivo.animal);
    infoAnimal->cantidad = infoRegistroArchivo.cant;
    infoAnimal->habitat = infoRegistroArchivo.habitat;
}

void crearEspecie(celdaEspecie arregloEspecies[], int *validos, registroArchivo infoRegistroArchivo) {

    if(*validos == DIM) printf("ERROR: No hay mas espacio para almacenar una especie nueva\n\n");

    else {
        int resultadoBusquedaEspecie = buscarEspecie(arregloEspecies, *validos, infoRegistroArchivo.especie);

        if (resultadoBusquedaEspecie != -1) {

            animal infoAnimal;
            copiarInfoAnimal(infoRegistroArchivo, &infoAnimal);

            arregloEspecies[resultadoBusquedaEspecie].arbolDeAnimales = insertarAnimalEnArbol(arregloEspecies[resultadoBusquedaEspecie].arbolDeAnimales, infoAnimal);

        }else {
            strcpy(arregloEspecies[*validos].especie, infoRegistroArchivo.especie);
            arregloEspecies[*validos].idEspecie = infoRegistroArchivo.idEspecie;

            animal infoAnimal;
            copiarInfoAnimal(infoRegistroArchivo, &infoAnimal);

            arregloEspecies[*validos].arbolDeAnimales = insertarAnimalEnArbol(arregloEspecies[*validos].arbolDeAnimales, infoAnimal);

            (*validos)++;
        }
    }
}

void pasarDeArchivoToTDA(celdaEspecie arregloEspecies[], int *validos, char nombreArchivo[]) {

    FILE *ptrArchivo = fopen(nombreArchivo, "rb");
    if(ptrArchivo == NULL) printf("Error al abrir el Archivo\n\n");

    else {
        registroArchivo auxRegistroArchivo;

        while(fread(&auxRegistroArchivo, sizeof(registroArchivo), 1, ptrArchivo) == 1) crearEspecie(arregloEspecies, validos, auxRegistroArchivo);

        fclose(ptrArchivo);
    }
}

void cargarArchivoConAnimales(char nombreArchivoEspecie[], nodoArbol *ptrArbol) {

    if(ptrArbol != NULL) {
        cargarArchivoConAnimales(nombreArchivoEspecie, ptrArbol->izq);
        ingresandoAnimalesAlArchivo(nombreArchivoEspecie, ptrArbol->animales);
        cargarArchivoConAnimales(nombreArchivoEspecie, ptrArbol->der);
    }
}

void ingresandoAnimalesAlArchivo(char nombreArchivoEspecie[], animal infoAnimales) {

    FILE *ptrArchivo = fopen(nombreArchivoEspecie, "ab");

    if(ptrArchivo == NULL) printf("Error al abrir el Archivo\n\n");

    else {
        fwrite(&infoAnimales, sizeof(animal), 1, ptrArchivo);

        fclose(ptrArchivo);
    }
}

void mostrarArchivoAnimales(char nombreArchivoAnimales[]) {

    FILE *ptrArchivo = fopen(nombreArchivoAnimales, "rb");
    animal infoAnimal;

    if(ptrArchivo == NULL) printf("\nError al abrir el Archivo \n\n");

    else {
        while(fread(&infoAnimal, sizeof(animal), 1, ptrArchivo) == 1) {

            printf("Animal: %s \n", infoAnimal.nombreAnimal);
            printf("Cantidad Animales: %i \n", infoAnimal.cantidad);
            printf("Nro Habitat: %i \n\n", infoAnimal.habitat);
        }

        fclose(ptrArchivo);
    }
}


