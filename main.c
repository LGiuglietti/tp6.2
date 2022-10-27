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
void iniciadoDeArregloArboles(celdaEspecie A[]);
nodoArbol*insertar(nodoArbol*arbol,nodoArbol*aux);
nodoArbol*crearNodoArbol(registroArchivo dato);
void pasarDeArchivoToADA(celdaEspecie*A[]);
void preorder(nodoArbol*arbol);
//fin prototipados
int main()
{
    celdaEspecie Arreglo[5];
    iniciadoDeArregloArboles(Arreglo);
    strcpy(Arreglo[0].especie,"Mamiferos");
    strcpy(Arreglo[0].especie,"Aves");
    strcpy(Arreglo[0].especie,"Reptiles");
    strcpy(Arreglo[0].especie,"Peces");
    strcpy(Arreglo[0].especie,"Anfibios");
    pasarDeArchivoToADA(Arreglo);
    for(int i=0;i<5;i++)
    {
        printf("subindice de arreglo:%d\n", i);
        puts(Arreglo[i].especie);
        printf("id de especie: %d\n",Arreglo[i].idEspecie);
        preorder(Arreglo[i].arbolDeAnimales);
        printf("\n");
    }
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
void pasarDeArchivoToADA(celdaEspecie*A[])
{
    FILE*archi=fopen("animales.dat","r");
    registroArchivo aux;
    int i=0;
    while(fread(&aux,sizeof(registroArchivo),1,archi)>0)
    {
        while(i<5)
        {
            if(strcmpi(A[i]->especie,aux.especie)==0)
            {
                strcpy(A[i]->especie,aux.especie);
                A[i]->idEspecie=aux.idEspecie;
                nodoArbol*dato=crearNodoArbol(aux);
                A[i]->arbolDeAnimales=insertar(A[i]->arbolDeAnimales,dato);
                i++;
            }
            else
            {
                i++;
            }
        }
        i=0;
    }
    fclose(archi);
}
nodoArbol*insertar(nodoArbol*arbol,nodoArbol*aux)
{
    if(arbol==NULL)
    {
        arbol=aux;
    }
    else if(arbol->dato.cantidad>aux->dato.cantidad)
    {
        insertar(arbol->izq,aux);
    }
    else
    {
        insertar(arbol->der,aux);
    }
    return arbol;
}
void iniciadoDeArregloArboles(celdaEspecie A[])
{
    for(int i=0; i<5; i++)
    {
        A[i].arbolDeAnimales=NULL;
    }
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
