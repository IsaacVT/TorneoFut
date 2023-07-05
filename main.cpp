// Librerias
#include <iostream>
#include "cargarEquipos.h"
#include "clasificatorias.h"
#include "arbolTorneo.h"

using namespace std;

// Prototipos
groups *iniciar(groups *game);
void imprimeNodo(groups *caja);
groups *limpiarLista(groups *cl);
bool verificaLista();
grpClasificacion *armarGrupos (groups *lista);
void imprimeGrupo();
grpClasificacion *limpiarTabla(grpClasificacion *cl);
void jugarClasificacion();
void limpiar();

// Menú principal
int main () {
    groups *grop = nullptr;
    grpClasificacion *clas = nullptr;
    int op = 0, seed;

    do {
        cout << "\n ---------- Simulador de liga de futbol ---------- \n" << endl;
        cout << "\t1. Cargar lista de equipos" << endl;
        cout << "\t2. Mostrar lista de equipos" << endl;
        cout << "\t3. Crear grupos de juego" << endl;
        cout << "\t4. Mostrar tabla de grupos" << endl;
        cout << "\t5. Jugar Torneo" << endl;
        cout << "\t6. Salir" << endl;
        cout << "\n\tOpcion : ";
        cin >> op;

        switch (op) {
            case 1:
                if (grop != nullptr)
                    if(verificaLista()) {
                        grop = limpiarLista(grop);
                        ejecutando = false;
                        grop = iniciar(grop);
                    }

                if (!ejecutando)
                        grop = iniciar(grop);
                break;
            case 2:
                if (grop != nullptr)
                    imprimeNodo(grop);
                else {
                    cout << "\nfatalError_#tarjetaAmarilla --- Posibles errores :" << endl;
                    cout << "- Aun no se carga la lista de equipos" << endl;
                }
                break;
            case 3:
                if (clas == nullptr && grop != nullptr) {
                    cout << "\n - Creando juego..........";
                    seed = rand();
                    srand(seed);
                    clas = armarGrupos(grop);
                    grop = limpiarLista(grop);
                    grop = iniciar(grop);
                    cout << "..........Juego creado -\n";
                } else {
                    cout << "\nfatalError_#posicionAdelantada --- Posibles errores :" << endl;
                    cout << "- Aun no se carga la lista de equipos" << endl;
                    cout << "- Ya hay un juego en curso\n" << endl;
                }
                break;
            case 4:
                if (clas != nullptr)
                    imprimeGrupo();
                else {
                    cout << "\nfatalError_#penal --- Posibles errores :" << endl;
                    cout << "- No hay un juego en curso\n" << endl;
                }
                break;
            case 5:
                if (clas != nullptr) {
                    jugarClasificacion();
                    clas = limpiarTabla(clas);
                    grop = limpiarLista(grop);
                    grop = iniciar(grop);
                } else {
                    cout << "\nfatalError_#tarjetaRoja --- Posibles errores :" << endl;
                    cout << "- No hay datos para jugar\n" << endl;
                }
                break;
            default:
                grop = limpiarLista(grop);
                clas = limpiarTabla(clas);
                op = -1;
                break;
        }

        limpiar();

    } while (op != -1);

    grop = nullptr;
    delete grop;
    clas = nullptr;
    delete clas;

    return 0;
}