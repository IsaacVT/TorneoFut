#ifndef MAIN_CPP_ARBOLTORNEO_H
#define MAIN_CPP_ARBOLTORNEO_H

// Librerias
#include <iostream>
#include <cstring>  // Para usar funciones con cadenas
#include "clasificatorias.h"
#include "cargarEquipos.h"

using namespace std;

// Prototipos
void intercambiarBloques(grpClasificacion *bloc);
void ordenarBloque(groups &b1, groups &b2);
groups *crearNodo (int n, groups *padre);
void insertarNodo (groups *&arbol, int n, groups *padre);
void jugarTorneo();
groups *torneo();
void mostrarArbol (groups *arbol, int cont);
groups *simularPartidos(groups *arbolGrp);
bool buscarNombre (groups *arbol, int n);
void titulo(int grp);
void liberar(groups *arbol);
void limpiar();

// Variables globales
groups *flotante = nullptr;
groups *fin1 = nullptr;
groups *fin2 = nullptr;
groups *fin3 = nullptr;
groups *fin4 = nullptr;
groups *finalTorneo = nullptr;
bool final = false;
int grupo = 1;

// Clasificatorias
void jugarClasificacion() {
    grpClasificacion *a = temporal;
    limpiar();
    cout << "\n ----------------------- Jugando Clasificatorias --------------------- \n" << endl;
    while (a != nullptr) {
        cout << "\n\t ----- Grupo " << a->numGrupo << " ----- " << endl;
        cout << "\t" << a->g1->nombre << " --- Goles : ";
        cin >> a->g1->goles;

        cout << "\t" << a->g2->nombre << " --- Goles : ";
        cin >> a->g2->goles;

        cout << "\t" << a->g3->nombre << " --- Goles : ";
        cin >> a->g3->goles;

        cout << "\t" << a->g4->nombre << " --- Goles : ";
        cin >> a->g4->goles;

        intercambiarBloques(a);

        a = a->sig;
    }

    cout << "\n - Solo pasaran los mejores 2 equipos de cada grupo -" << endl;
    imprimeGrupo();
    jugarTorneo();
}

// Ordenar los elementos de cada grupo
void intercambiarBloques(grpClasificacion *bloc) {
    ordenarBloque(*bloc->g1, *bloc->g2);
    ordenarBloque(*bloc->g1, *bloc->g3);
    ordenarBloque(*bloc->g1, *bloc->g4);

    ordenarBloque(*bloc->g2, *bloc->g1);
    ordenarBloque(*bloc->g2, *bloc->g3);
    ordenarBloque(*bloc->g2, *bloc->g4);

    ordenarBloque(*bloc->g3, *bloc->g1);
    ordenarBloque(*bloc->g3, *bloc->g2);
    ordenarBloque(*bloc->g3, *bloc->g4);

    ordenarBloque(*bloc->g4, *bloc->g1);
    ordenarBloque(*bloc->g4, *bloc->g2);
    ordenarBloque(*bloc->g4, *bloc->g3);
}

// Intercambiar bloques
void ordenarBloque(groups &b1, groups &b2) {
    groups aux;
    if (b1.goles > b2.goles) {
        aux = b1;
        b1 = b2;
        b2 = aux;
    }
}

// Armar Torneo
void jugarTorneo(){
    temporal2 = temporal;

    fin1 = torneo();
    fin2 = torneo();
    fin3 = torneo();
    fin4 = torneo();

    cout << "\n\n\t ------- Fin de la clasificatoria ------" << endl;
    cout << "\n\t - Comenzaran los partidos por la copa -\n" << endl;

    simularPartidos(fin1);
    simularPartidos(fin2);
    simularPartidos(fin3);
    simularPartidos(fin4);

    final = true;
    finalTorneo = torneo();
    finalTorneo = simularPartidos(finalTorneo);

    titulo(6);
    cout << "\t\t - El equipo " << finalTorneo->nombre << " se lleva la copa -\n" << endl;
    cout << "\n\t ----------------- Felicidades, el torneo a concluido --------------- \n" << endl;
    cout << "\n\t ------- Se limpiaran todos los datos a excepcion de la lista ------- \n" << endl;
    grupo = 1;

    liberar(fin1);
    liberar(fin2);
    liberar(fin3);
    liberar(fin4);
    liberar(finalTorneo);
}

// Jugar Torneo
groups *simularPartidos(groups *arbolGrp) {
    int arPos1[4];
    int vuelta[] = {4,2};
    int conta = 0;

    if (arbolGrp != nullptr) {

        titulo(grupo);
        mostrarArbol(arbolGrp, 0);

        for (int i = 0; i < 2; ++i) {

            cout << "\n\n\t ------------------ Resultado del Partido ------------------\n" << endl;

            if (conta == 0){
                arPos1[0] = 1;
                arPos1[1] = 3;
                arPos1[2] = 5;
                arPos1[3] = 7;
            } else {
                arPos1[0] = 2;
                arPos1[1] = 6;
                arPos1[2] = 0;
                arPos1[3] = 0;
            }

            for (int j = 0; j < vuelta[conta]; ++j) {

                if (buscarNombre(arbolGrp,arPos1[j])) {
                    cout << "\t\t\t" << flotante->nombre << " --- Goles : ";
                    cin >> flotante->goles;

                    if (j == 0 || j == 2)
                        cout << "\n\t\t\t   ----- vs -----\n" << endl;
                    else
                        cout << "\n" << endl;
                }

                if (j == 1 || j == 3) {
                    if (flotante->goles > flotante->padre->izq->goles)
                        strcpy(flotante->padre->nombre, flotante->nombre);
                    else
                        strcpy(flotante->padre->nombre, flotante->padre->izq->nombre);
                }
            }

            titulo(grupo);
            mostrarArbol(arbolGrp,0);

            conta++;
        }
    }

    grupo++;
    return arbolGrp;
}

// Buscar nodo en el árbol
bool buscarNombre(groups *arbol, int n) {
    if (arbol != nullptr) {

        if (n > arbol->posicion) {
            return buscarNombre(arbol->der,n);

        } else if (n < arbol->posicion) {
            return buscarNombre(arbol->izq,n);

        } else {
            flotante = arbol;
            return true;
        }

    } else
        return false;
}

// Crear árboles para el torneo
groups *torneo() {
    int arPos[] = {4, 2, 1, 3, 6, 5, 7};
    groups *arb = nullptr;

    for (int arPo : arPos) {
        insertarNodo(arb, arPo, nullptr);
    }

    return arb;
}

// Crear ramas del árbol
void insertarNodo (groups *&arbol, int n, groups *padre) {

    if (arbol != nullptr) {

        int valorRaiz = arbol->posicion;

        if (n < valorRaiz) insertarNodo(arbol->izq, n, arbol);
        else insertarNodo(arbol->der, n, arbol);

    } else {
        groups *nuevo_nodo = crearNodo(n, padre);
        arbol = nuevo_nodo;
    }
}

// Crear nodo del árbol
groups *crearNodo (int n, groups *padre) {

    auto *nuevo_nodo = new groups;

    if (n == 4 || n == 2 || n == 6) strcpy(nuevo_nodo->nombre,"-vs-");

    if (!final) {
        if (n == 1 || n == 5) strcpy(nuevo_nodo->nombre,temporal2->g1->nombre);
        if (n == 3 || n == 7) strcpy(nuevo_nodo->nombre,temporal2->g2->nombre);
        if (n == 6 || n == 7) temporal2 = temporal2->sig;
    } else {
        if (n == 1) strcpy(nuevo_nodo->nombre,fin1->nombre);
        if (n == 3) strcpy(nuevo_nodo->nombre,fin2->nombre);
        if (n == 5) strcpy(nuevo_nodo->nombre,fin3->nombre);
        if (n == 7) strcpy(nuevo_nodo->nombre,fin4->nombre);
    }

    nuevo_nodo->sig = nullptr;
    nuevo_nodo->goles = 0;
    nuevo_nodo->posicion = n;
    nuevo_nodo->der = nullptr;
    nuevo_nodo->izq = nullptr;
    nuevo_nodo->padre = padre;

    return nuevo_nodo;
}

// Visualizar árbol
void mostrarArbol (groups *arbol, int cont) {

    if (arbol != nullptr) {

        mostrarArbol(arbol->der,cont+1);

        for (int i = -1; i < cont; ++i) {

            if (cont == 0) cout << "\t\t";

            if (arbol->padre != nullptr) {
                if (strlen(arbol->padre->nombre) < 5) cout << "\t\t";
                else cout << "\t\t\t";
            }
        }

        cout << arbol->nombre << endl;

        mostrarArbol(arbol->izq,cont+1);

    } else  // Si el árbol esta vacío
        return;
}

// Titulo para cada árbol
void titulo(int grp) {
    limpiar();
    switch (grp) {
        case 1:
            cout << "\n\t ------------------------------ Grupo 1 ------------------------------ \n" << endl;
            break;
        case 2:
            cout << "\n\t ------------------------------ Grupo 2 ------------------------------ \n" << endl;
            break;
        case 3:
            cout << "\n\t ------------------------------ Grupo 3 ------------------------------ \n" << endl;
            break;
        case 4:
            cout << "\n\t ------------------------------ Grupo 4 ------------------------------ \n" << endl;
            break;
        case 5:
            cout << "\n\t ------------------------ Partidos de la Final ----------------------- \n" << endl;
            break;
        case 6:
            cout << "\n\t ---------------------------- Fin del Torneo ------------------------- \n" << endl;
            break;
    }
}

// Liberar memoria
void liberar(groups *arbol) {
    if(arbol != nullptr) {
        liberar(arbol->izq);
        liberar(arbol->der);
        delete(arbol);
    }
}

// Limpiar pantalla
void limpiar() {
    cout << "\n   ";
    system("pause");
    system("cls");
}

#endif //MAIN_CPP_ARBOLTORNEO_H
