// ═══════════════════════════════════════════════════════
//  main.cpp
//  Sistema de Administracion de Tienda en C++
//  Programacion 1
//
//  Estudiante : Moises Abinadí Farfan Gonzalez
//  Carne      : 9941-25-86
// ═══════════════════════════════════════════════════════

#include <iostream>
#include <cstring>
#include <stdexcept>
#include "estructuras.h"
#include "archivos.h"
#include "productos.h"
#include "ventas.h"
#include "reportes.h"
#include "utilidades.h"

using namespace std;

// ───────────────────────────────────────────────────────
//  DEFINICION de variables globales
//  (declaradas como extern en estructuras.h)
// ───────────────────────────────────────────────────────
Producto productos[MAX_PRODUCTOS];
int      totalProductos = 0;

Venta    ventas[MAX_VENTAS];
int      totalVentas = 0;

int ventasPorMes[MAX_MESES][MAX_VENTAS];
int conteoVentasMes[MAX_MESES] = {0};

// ───────────────────────────────────────────────────────
//  mostrarBienvenida()
//  Pantalla inicial con datos del estudiante
// ───────────────────────────────────────────────────────
void mostrarBienvenida() {
    cout << "========================================" << endl;
    cout << "   SISTEMA DE ADMINISTRACION DE TIENDA  " << endl;
    cout << "========================================" << endl;
    cout << "  Estudiante : Moises Abinadí Farfan Gonzalez" << endl;
    cout << "  Carne      : 9941-25-86"                     << endl;
    cout << "  Curso      : Programacion 1"                  << endl;
    cout << "========================================" << endl;
}

// ───────────────────────────────────────────────────────
//  mostrarMenuPrincipal()
// ───────────────────────────────────────────────────────
void mostrarMenuPrincipal() {
    cout << "\n========================================" << endl;
    cout << "            MENU PRINCIPAL              " << endl;
    cout << "========================================" << endl;
    cout << " 1. Gestion de Productos"                 << endl;
    cout << " 2. Proceso de Venta"                     << endl;
    cout << " 3. Reportes"                             << endl;
    cout << " 4. Utilidades del Sistema"               << endl;
    cout << " 5. Salir"                                << endl;
    cout << "========================================" << endl;
    cout << "Seleccione una opcion: ";
}

// ───────────────────────────────────────────────────────
//  main()
//  Ciclo principal del programa
// ───────────────────────────────────────────────────────
int main() {
    // Inicializar la matriz de ventas por mes a cero
    for (int m = 0; m < MAX_MESES; m++)
        for (int v = 0; v < MAX_VENTAS; v++)
            ventasPorMes[m][v] = 0;

    // Pantalla de bienvenida
    mostrarBienvenida();

    // Cargar datos desde archivos binarios
    cout << "\nIniciando sistema..." << endl;
    try {
        cargarProductos();
        cargarVentas();
        cout << "Datos cargados: "
             << totalProductos << " producto(s), "
             << totalVentas    << " venta(s)." << endl;
    } catch (const exception& e) {
        cerr << "Advertencia al cargar datos: " << e.what() << endl;
        cout << "Se iniciara con datos vacios." << endl;
    }

    // Ciclo principal
    int opcion = 0;

    do {
        mostrarMenuPrincipal();

        try {
            cin >> opcion;
            if (cin.fail())
                throw invalid_argument("Entrada no numerica. Ingrese un numero.");
            if (opcion < 1 || opcion > 5)
                throw out_of_range("Opcion fuera de rango. Ingrese del 1 al 5.");
        } catch (const invalid_argument& e) {
            cerr << "Error de entrada: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0;
            continue;
        } catch (const out_of_range& e) {
            cerr << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0;
            continue;
        } catch (const exception& e) {
            cerr << "Error inesperado: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0;
            continue;
        }

        switch (opcion) {
            case 1: menuGestionProductos(); break;
            case 2: menuProcesarVenta();    break;
            case 3: menuReportes();         break;
            case 4: menuUtilidades();       break;
            case 5:
                cout << "\n========================================" << endl;
                cout << "  Gracias por usar el sistema. Adios!   " << endl;
                cout << "  Moises Abinadí Farfan Gonzalez         " << endl;
                cout << "========================================" << endl;
                break;
        }

    } while (opcion != 5);

    return 0;
}
