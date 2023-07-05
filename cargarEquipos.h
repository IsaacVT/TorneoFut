#ifndef MAIN_CPP_CARGAREQUIPOS_H
#define MAIN_CPP_CARGAREQUIPOS_H

// Librerias
#include <iostream>
#include <fstream>  // Para archivo
#include <unistd.h> // Para la función random
#include <cstring>  // Para usar funciones con cadenas

using namespace std;

// Definimos el tamaño de los nombres
#define tam 25

// Estructura de las cajas de la pila
struct groups {
    char nombre[tam];
    int posGrp;
    int goles;

    // Pila, Cola
    groups *sig;

    // Árbol
    int posicion;
    groups *der;
    groups *izq;
    groups *padre;
};

// Ruta de los archivos
char ruta[50] = "..\\listasEquipos";
char nombreLista[50] = "";
bool ejecutando = false;

// Prototipos
groups *cargarGrupos(groups *g);
groups *crearGr(const char *name, int pos);
groups *enlazar(groups *g, groups *grp);
int posAleatorio();
groups *limpiarLista(groups *cl);
void limpiar();
bool borrarLista();

bool verificaLista() {
    char c;
    cout << "\n ------------------- Precaucion ------------------\n" << endl;
    cout << "Ya hay una lista cargada. Quieres sustituirla? s/n : ";
    cin >> c;

    return (c == 's' || c == 'S');
}

bool borrarLista() {
    char c;
    cout << "\n ------------------ ADVERTENCIA ------------------\n" << endl;
    cout << "Se borrara la lista - " << nombreLista << " - Continuar? s/n : ";
    cin >> c;

    return (c == 's' || c == 'S');
}

// Mostrar los archivos dentro de la carpeta "listaEquipos"
groups *iniciar(groups *game) {
    if (!ejecutando) {
        cout << "\n ----- Elije una lista de equipos ----- \n" << endl;

        char comando[50] = "dir ";
        char formato[50] = " /B /O";

        strcat(comando, ruta);
        strcat(comando, formato);

        system(comando);

        cout << "\nNOTA: Puedes agregar tu propia lista, consulta README" << endl;

        cout << "\n - Quiero cargar : ";
        cin >> nombreLista;
    }

    return cargarGrupos(game);
}

// Cargar el archivo
groups *cargarGrupos(groups *g) {
    ifstream archivo;
    ofstream archivofut;
    char rutaList[50] = "../listasEquipos/";
    char nombre[tam] = "";
    string nameEquipo;
    int conta = 1;

    // Borrar un archivo
    if (strncmp(nombreLista,"#delete_",8) == 0) {

        for (int i = 0; i < tam; ++i) {
            if (nombreLista[i+8] == '.')
                break;

            nombre[i] = nombreLista[i + 8];
        }

        strcpy(nombreLista, nombre);

        if (borrarLista()) {

            strcat(nombreLista, ".fut");
            strcat(rutaList, nombreLista);
            remove(rutaList);
            strcpy(nombreLista, "");

            cout << "\n\t--- Borrado exitoso ---\n";

        } else {
            cout << "\n\t--- Ten cuidado la proxima vez ---\n";
        }

    // Crear un archivo nuevo
    } else if (strncmp(nombreLista,"#new_",5) == 0) {

        for (int i = 0; i < tam; ++i) {
            if (nombreLista[i+5] == '\0')
                break;

            nombre[i] = nombreLista[i+5];
        }

        strcpy(nombreLista,nombre);
        strcat(nombreLista,".fut");
        strcat(rutaList, nombreLista);

        archivofut.open(rutaList,ios::out);

        cout << "\n --- Comando #new reconocido ---\n" << endl;
        system("pause");

        if (!archivo) {
            cout << "\n ----- La lista no pudo ser creada -----" << endl;
            strcpy(nombreLista, "");
            g = nullptr;
        } else {
            system("cls");
            cout << "\n ---------- Creando " << nombre << " ----------\n" << endl;
            getchar();

            for (int i = 0; i < 32; ++i) {
                cout << "\tNombre Equipo " << i + 1 << " : ";
                getline(cin,nameEquipo);

                if (nameEquipo != "\0")
                    archivofut << nameEquipo << endl;
                else
                    i--;
            }

            cout << "\n------------ Creacion Exitosa -----------" << endl;
            cout << "--- Ya puedes cargar la nueva lista -----\n" << endl;

            archivo.close();
        }

    // Abrir un archivo existente
    } else {
        strcat(rutaList, nombreLista);
        archivo.open(rutaList);

        if (!archivo) {
            cout << "\n ----- El archivo no existe -----" << endl;
            strcpy(nombreLista, "");
            g = nullptr;
        } else {
            if (!ejecutando)
                cout << "\n ----- Cargando Lista -----" << endl;

            while (!archivo.eof()) {
                for (int i = 0; i < tam; ++i) {
                    nombre[i] = archivo.get();

                    if (nombre[i] == '\n') {
                        for (int j = i; j < tam; ++j) {
                            nombre[j] = '\0';
                        }

                        // Creamos una lista de todos los equipos
                        g = enlazar(crearGr(nombre, conta++), g);

                        for (char &k: nombre) k = '\0';

                        i = -1;
                    }
                }
            }

            archivo.close();

            if (!ejecutando) {
                cout << "\n ----- Carga Exitosa -----" << endl;
                ejecutando = true;
            }
        }
    }

    return g;
}

// Crear caja
groups *crearGr(const char *name, int pos) {
    groups *gro = new groups;

    strcpy(gro->nombre, name);
    gro->posGrp = pos;
    gro->goles = 0;
    gro->der = nullptr;
    gro->izq = nullptr;
    gro->padre = nullptr;

    return gro;
}

// Enlazar cajas
groups *enlazar(groups *g, groups *grp) {
    if (g == nullptr)
        return nullptr;

    g->sig = grp;
    grp = g;

    return grp;
}

// Obtener dato de la pila
groups *obtenerDato(groups *lista) {
    groups *aux = lista, *temp = lista, *inicio = nullptr, *auxPos = aux->sig;
    int pos = posAleatorio();
    bool existe = false;

    while (auxPos != nullptr) {

        while (temp != nullptr && !existe) {

            if (pos == temp->posGrp) {
                existe = true;
                break;
            }

            temp = temp->sig;

            if (temp == nullptr && temp != inicio) {
                inicio = temp;
                temp = lista;
            } else if (temp == inicio) {
                pos = posAleatorio();
                temp = lista;
            }
        }

        if (auxPos->posGrp == pos) {
            aux->sig = auxPos->sig;
            auxPos->sig = nullptr;
            break;
        }

        aux = auxPos;
        auxPos = aux->sig;
    }

    return auxPos;
}

// Numero random
int posAleatorio () {
    int min = 1, max = 32;
    return min + rand() / (RAND_MAX / (max - min) +1);
}

// Imprime pila
void imprimeNodo (groups *caja) {
    if (caja == nullptr) {
        cout << "No hay lista cargada" << endl;
        return;
    }

    groups *aux = caja;

    limpiar();
    cout << "\n\t ---------- Lista de Equipos ---------- \n" << endl;

    while (aux != nullptr) {
        cout << "\t      Equipo " << aux->posGrp << "\t: " << aux->nombre << endl;
        aux = aux->sig;
    }
    cout << endl;
}

// Libera memoria
groups *limpiarLista(groups *cl) {
    groups *te = cl;

    while (cl != nullptr) {
        cl = cl->sig;
        te->sig = nullptr;
        delete te;
        te = cl;
    }

    return cl;
}

#endif //MAIN_CPP_CARGAREQUIPOS_H
