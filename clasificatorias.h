#ifndef MAIN_CPP_CLASIFICATORIAS_H
#define MAIN_CPP_CLASIFICATORIAS_H

// Librerias
#include <iostream>
#include "cargarEquipos.h"

using namespace std;

// Limite para crear los grupos
#define limitGrp 9

// Estructura de los grupos
struct grpClasificacion {
    int numGrupo;
    groups *g1;
    groups *g2;
    groups *g3;
    groups *g4;
    grpClasificacion *sig;
};

// Variables globales
grpClasificacion *temporal;
grpClasificacion *temporal2;

// Prototipos
grpClasificacion *crear (groups *list, int numG);
grpClasificacion *unirGrp(grpClasificacion *g, grpClasificacion *grp);
groups *obtenerDato(groups *lista);

// Crear una cola con los grupos
grpClasificacion *armarGrupos (groups *lista) {
    grpClasificacion *tablas = nullptr;
    int n = 1;

    while (lista != nullptr && n < limitGrp) {
        tablas = unirGrp(crear(lista, n++), tablas);
    }

    return tablas;
}

// Crear grupo
grpClasificacion *crear (groups *list, int numG) {
    if (list == nullptr)
        return nullptr;

    auto *g = new grpClasificacion;

    g->numGrupo = numG;
    g->sig = nullptr;

    if (numG < limitGrp-1) {
        g->g1 = obtenerDato(list);
        g->g2 = obtenerDato(list);
        g->g3 = obtenerDato(list);
        g->g4 = obtenerDato(list);
    } else {
        g->g1 = list;
        list = list->sig;
        g->g2 = list;
        list = list->sig;
        g->g3 = list;
        list = list->sig;
        g->g4 = list;
    }

    g->g1->sig = nullptr;
    g->g2->sig = nullptr;
    g->g3->sig = nullptr;
    g->g4->sig = nullptr;

    return g;
}

// Enlazar grupos
grpClasificacion *unirGrp(grpClasificacion *g, grpClasificacion *grp) {
    g->sig = nullptr;

    if (grp == nullptr)
        temporal = g;
    else
        grp->sig = g;

    grp = g;

    return grp;
}

// Mostrar grupos
void imprimeGrupo() {
    grpClasificacion *a = temporal;

    if (a == nullptr) {
        cout << "No existen equipos aun" << endl;
        return;
    }

    limpiar();
    cout << "\n\t ---- Grupos para clasificatoria ----- " << endl;

    while (a != nullptr) {
        cout << "\n\n .----------------- Grupo " << a->numGrupo << " ------------------" << endl;
        cout << " |" << endl;
        cout << " |\t" << a->g1->nombre << " --- Goles : " << a->g1->goles << endl;
        cout << " |\t" << a->g2->nombre << " --- Goles : " << a->g2->goles << endl;
        cout << " |\t" << a->g3->nombre << " --- Goles : " << a->g3->goles << endl;
        cout << " |\t" << a->g4->nombre << " --- Goles : " << a->g4->goles << endl;
        cout << " |" << endl;
        cout << " *--------------------------------------------" << endl;
        a = a->sig;
    }
}

// Liberar memoria
grpClasificacion *limpiarTabla(grpClasificacion *cl) {
    grpClasificacion *te = cl;

    temporal = nullptr;
    while (cl != nullptr) {
        cl = cl->sig;
        te->sig = nullptr;
        delete te;
        te = cl;
    }

    return cl;
}

#endif //MAIN_CPP_CLASIFICATORIAS_H
