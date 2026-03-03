//Fecha:  jueves 30 Octubre 2025 
//Autor: Ana Roncal

#include <iostream>
#include <iomanip>
#include "funcionesArbolBinario.h"
#include "ArbolBinario.h"
#include "../BibliotecaCola/Cola.h"
#include "../BibliotecaCola/funcionesCola.h"
#include "../BibliotecaPila/Pila.h"
#include "../BibliotecaPila/funcionesPila.h"

using namespace std;

void construir(struct ArbolBinario &arbol) {
    arbol.raiz = nullptr;
}

bool esArbolVacio(const struct ArbolBinario &arbol) {
    return arbol.raiz == nullptr;
}

bool esNodoVacio(const struct NodoArbolBinario *nodo) {
    return nodo == nullptr;
}

void plantarArbolBinario(struct ArbolBinario &arbol, const struct ArbolBinario &izquierda,
                         const struct ElementoArbolBinario &elemento, const struct ArbolBinario &derecha) {
    plantarNodoArbolBinario(arbol.raiz, izquierda.raiz, elemento, derecha.raiz);
}

void plantarNodoArbolBinario(struct NodoArbolBinario *&nodo, struct NodoArbolBinario *izquierda,
                             const struct ElementoArbolBinario &elemento, struct NodoArbolBinario *derecha) {
    struct NodoArbolBinario *nuevo = new struct NodoArbolBinario;
    nuevo->derecha = derecha;
    nuevo->izquierda = izquierda;
    nuevo->elemento = elemento;
    nuevo->padre = nullptr; //inicializo el nodo padre
    nodo = nuevo;
}

void imprimirNodo(struct NodoArbolBinario *raiz) {
    cout << setw(5) << raiz->elemento.tipo << "(" << raiz->elemento.numero << ")";
}

void recorrerPreOrden(const struct ArbolBinario &arbol) {
    recorrerPreOrdenRecursivo(arbol.raiz);
}

void recorrerPreOrdenRecursivo(struct NodoArbolBinario *nodo) {
    if (not esNodoVacio(nodo)) {
        imprimirNodo(nodo);
        recorrerPreOrdenRecursivo(nodo->izquierda);
        recorrerPreOrdenRecursivo(nodo->derecha);
    }
}

void recorrerEnOrden(const struct ArbolBinario &arbol) {
    recorrerEnOrdenRecursivo(arbol.raiz);
}

/*Va mostrar el árbol en orden */
void recorrerEnOrdenRecursivo(struct NodoArbolBinario *nodo) {
    if (not esNodoVacio(nodo)) {
        recorrerEnOrdenRecursivo(nodo->izquierda);
        imprimirNodo(nodo);
        recorrerEnOrdenRecursivo(nodo->derecha);
    }
}

void recorrerPostOrden(const struct ArbolBinario &arbol) {
    recorrerPostOrdenRecursivo(arbol.raiz);
}

void recorrerPostOrdenRecursivo(struct NodoArbolBinario *nodo) {
    if (not esNodoVacio(nodo)) {
        recorrerPostOrdenRecursivo(nodo->izquierda);
        recorrerPostOrdenRecursivo(nodo->derecha);
        imprimirNodo(nodo);
    }
}

int altura(const struct ArbolBinario &arbol) {
    return alturaRecursivo(arbol.raiz);
}

int alturaRecursivo(struct NodoArbolBinario *nodo) {
    if (esNodoVacio(nodo))
        return 0;
    else if (esNodoVacio(nodo->izquierda) and esNodoVacio(nodo->derecha))
        return 1;
    else
        return 1 + maximo(alturaRecursivo(nodo->izquierda), alturaRecursivo(nodo->derecha));
}

int maximo(int a, int b) {
    return a >= b ? a : b;
}

int numeroHojas(const struct ArbolBinario &arbol) {
    return numeroHojasRecursivo(arbol.raiz);
}

int numeroHojasRecursivo(struct NodoArbolBinario *nodo) {
    if (esNodoVacio(nodo))
        return 0;
    else if (esNodoVacio(nodo->izquierda) and esNodoVacio(nodo->derecha))
        return 1;
    else
        return numeroHojasRecursivo(nodo->izquierda) + numeroHojasRecursivo(nodo->derecha);
}


int numeroNodos(const struct ArbolBinario &arbol) {
    return numeroNodosRecursivo(arbol.raiz);
}

int numeroNodosRecursivo(struct NodoArbolBinario *nodo) {
    if (esNodoVacio(nodo))
        return 0;
    else
        return 1 + numeroNodosRecursivo(nodo->izquierda) + numeroNodosRecursivo(nodo->derecha);
}

bool esEquilibrado(const struct ArbolBinario &arbol) {
    return esEquilibradoRecursivo(arbol.raiz);
}

bool esEquilibradoRecursivo(struct NodoArbolBinario *nodo) {

    if (esNodoVacio(nodo))
        return true;
    else {
        int alturaHijoIzquierdo = alturaRecursivo(nodo->izquierda);
        int alturaHijoDerecho = alturaRecursivo(nodo->derecha);
        int diferencia = abs(alturaHijoIzquierdo - alturaHijoDerecho);
        return diferencia <= 1 and esEquilibradoRecursivo(nodo->izquierda) and
               esEquilibradoRecursivo(nodo->derecha);
    }
}

void destruirArbolBinario(struct ArbolBinario & arbol){
    destruirRecursivo(arbol.raiz);
    arbol.raiz = nullptr;
}

void destruirRecursivo(struct NodoArbolBinario * nodo){
    if(not (esNodoVacio(nodo))){
        destruirRecursivo(nodo->izquierda);
        destruirRecursivo(nodo->derecha);
        delete nodo;
    }
}

/*Nuevas funciones usando Pilas y Colas */
/*recorre el árbol por niveles usando una cola y con cambio de línea*/
void recorridoPorNivelCambioLinea(const struct ArbolBinario & arbol) {
    struct Cola cola; /*Se usa una cola para acceder a los nodos*/
    construirCola(cola);
    int i = 1;
    cout << "Nivel " << i++ << ": ";
    if (not esArbolVacio(arbol)) {
        encolar(cola, arbol.raiz);
        encolar(cola, nullptr);
        while (not esColaVacia(cola)) {
            struct NodoArbolBinario * nodo = desencolar(cola);
            if (nodo == nullptr) {
                cout << endl;
                if (not esColaVacia(cola)) {
                    cout << "Nivel " << i++ << ": ";
                    encolar(cola, nullptr);
                }
            } else {
                imprimirNodo(nodo);
                if (not esNodoVacio(nodo->izquierda)) {
                    encolar(cola, nodo->izquierda);
                }
                if (not esNodoVacio(nodo->derecha)) {
                    encolar(cola, nodo->derecha);
                }
            }
        }
    }
    destruir(cola);
}

/*recorre el arbol por niveles usando una cola*/
void recorridoPorNivel(const struct ArbolBinario & arbol){
    struct Cola cola; /*Se usa una cola para acceder a los nodos*/
    construirCola(cola);

    if(not esArbolVacio(arbol)){
        encolar(cola, arbol.raiz);
        while(not esColaVacia(cola)){
            struct NodoArbolBinario * nodo = desencolar(cola);
            imprimirNodo(nodo);
            if (not esNodoVacio(nodo->izquierda)){
                encolar(cola, nodo->izquierda);
            }
            if (not esNodoVacio(nodo->derecha)){
                encolar(cola, nodo->derecha);
            }
        }
    }
    destruir(cola);
}

void insertarEnCumulo(struct ArbolBinario & cumulo, int dato) {

    struct ArbolBinario hijo, arbolVacio;
    construir(hijo);
    construir(arbolVacio);

    struct Cola cola; /*Se usa una cola para acceder a los nodos*/
    construirCola(cola);
    struct NodoArbolBinario * encontrado = nullptr;
    if(not esArbolVacio(cumulo)){
        plantarArbolBinario(hijo, arbolVacio, {dato}, arbolVacio);
        encolar(cola, cumulo.raiz);
        while(not esColaVacia(cola)){
            struct NodoArbolBinario * nodo = desencolar(cola);

            if (esNodoVacio(nodo->izquierda) or esNodoVacio(nodo->derecha)) {
                encontrado = nodo;
                break;
            }
            if (not esNodoVacio(nodo->izquierda)){
                encolar(cola, nodo->izquierda);
            }
            if (not esNodoVacio(nodo->derecha)){
                encolar(cola, nodo->derecha);
            }
        }
    }
    else {
        plantarArbolBinario(cumulo, arbolVacio, {dato}, arbolVacio);
    }
    destruir(cola);

    if (encontrado) {
        hijo.raiz->padre = encontrado;
        if (esNodoVacio(encontrado->izquierda))
            encontrado->izquierda = hijo.raiz;
        else
            if(esNodoVacio(encontrado->derecha))
                encontrado->derecha = hijo.raiz;
    }
    flotar(hijo.raiz);
}

void flotar(struct NodoArbolBinario *nodo) {
    // Sube mientras haya padre
    if (not esNodoVacio(nodo))
    while (nodo->padre != nullptr and nodo->elemento.numero < nodo->padre->elemento.numero) {
        // Intercambia el dato del nodo con el dato de su padre
        intercambiarDatos(nodo, nodo->padre);
        // Mueve el puntero nodo al padre para continuar la subida
        nodo = nodo->padre;
    }
}

void intercambiarDatos(struct NodoArbolBinario * nodo1, struct NodoArbolBinario * nodo2) {
    int temp = nodo1->elemento.numero;
    nodo1->elemento.numero = nodo2->elemento.numero;
    nodo2->elemento.numero = temp;
}
