#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char animal[30];
    int cant;
    int habitat;
    int idEspecie;
    char especie[20];
} registroArchivo;

typedef struct
{
    char nombreAnimal [30];
    int cantidad;
    int habitat;
// 1 - selva, 2- savana, 3-bosque, 4-mar
} animal;

typedef struct nodoArbol
{
    animal dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

typedef struct
{
    int idEspecie;
    char especie [20];
    // "Mamiferos", "Aves"
    // "Reptiles", "Peces",”Anfibios”
    nodoArbol * arbolDeAnimales;
} celdaEspecie;

//prototipados
nodoArbol*insertar(nodoArbol*arbol,registroArchivo aux);
nodoArbol*crearNodoArbol(registroArchivo dato);
int pasarDeArchivoToADA(celdaEspecie A[]);
void preorder(nodoArbol*arbol);
int buscarPosArreglo (celdaEspecie A[], registroArchivo aux, int posicion);
int agregarToArreglo(celdaEspecie A[],registroArchivo aux,int validosArreglo);
void mostrarArregloyArbol(celdaEspecie A[], int validos);
//fin prototipados
int main()
{
    celdaEspecie Arreglo[5];
    int validosArreglo=pasarDeArchivoToADA(Arreglo);
    mostrarArregloyArbol(Arreglo,validosArreglo);
    return 0;
}
nodoArbol*crearNodoArbol(registroArchivo dato)
{
    nodoArbol*aux=(nodoArbol*)malloc(sizeof(nodoArbol));
    aux->dato.cantidad=dato.cant;
    aux->dato.habitat=dato.habitat;
    strcpy(aux->dato.nombreAnimal,dato.animal);
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}
int pasarDeArchivoToADA(celdaEspecie A[])
{
    FILE*archi=fopen("animales.dat","rb");
    registroArchivo aux;
    int posicion, validosArreglo=0;
    while(fread(&aux,sizeof(registroArchivo),1,archi)>0)
    {

        posicion=buscarPosArreglo(A,aux,posicion);
        if(posicion==-1)
        {
            validosArreglo=agregarToArreglo(A,aux,validosArreglo);
            posicion=validosArreglo-1;
        }

        A[posicion].arbolDeAnimales=insertar(A[posicion].arbolDeAnimales,aux);
    }
    fclose(archi);
    return validosArreglo;
}
int buscarPosArreglo (celdaEspecie A[], registroArchivo aux, int posicion)
{
    int i=1;
    posicion=-1;
    while(i<6)
    {
        if(aux.idEspecie==A[i].idEspecie)
        {
            posicion=i;
        }
        i++;
    }
    return posicion;
}
int agregarToArreglo(celdaEspecie A[],registroArchivo aux,int validosArreglo)
{
    A[validosArreglo].idEspecie=aux.idEspecie;
    strcpy(A[validosArreglo].especie,aux.especie);
    A[validosArreglo].arbolDeAnimales = NULL;
    validosArreglo++;
    return validosArreglo;
}
nodoArbol*insertar(nodoArbol*arbol,registroArchivo aux)
{
    if(arbol==NULL)
    {
        nodoArbol*nn=crearNodoArbol(aux);
        arbol=nn;
    }
    else if(arbol->dato.cantidad>aux.cant)
    {
        arbol->izq=insertar(arbol->izq,aux);
    }
    else
    {
        arbol->der=insertar(arbol->der,aux);
    }
    return arbol;
}
void preorder(nodoArbol*arbol)
{
    if(arbol!=NULL)
    {
        puts(arbol->dato.nombreAnimal);
        printf("cantidad: %d\t", arbol->dato.cantidad);
        printf("habitat: %d\t",arbol->dato.habitat);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}
void mostrarArregloyArbol(celdaEspecie A[], int validos)
{
    for(int i=0; i<validos; i++)
    {

        printf("id de especie: %d\n",A[i].idEspecie);
        puts(A[i].especie);
        preorder(A[i].arbolDeAnimales);
        printf("\n");
    }
}
