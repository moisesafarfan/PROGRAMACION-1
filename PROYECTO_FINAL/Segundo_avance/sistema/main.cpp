// ═══════════════════════════════════════════════════════
//  main.cpp
//  Sistema de Administracion de Tienda en C++
//  Punto de entrada del programa
//  Programacion 1
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
//  mostrarMenuPrincipal()
// ───────────────────────────────────────────────────────
void mostrarMenuPrincipal() {
    cout << "\n========================================" << endl;
    cout << "    SISTEMA DE ADMINISTRACION DE TIENDA " << endl;
    cout << "========================================" << endl;
    cout << " 1. Gestion de Productos" << endl;
    cout << " 2. Proceso de Venta" << endl;
    cout << " 3. Reportes" << endl;
    cout << " 4. Utilidades del Sistema" << endl;
    cout << " 5. Salir" << endl;
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

    // Cargar datos desde archivos binarios
    cout << "Iniciando sistema..." << endl;
    try {
        cargarProductos();
        cargarVentas();
        cout << "Datos cargados: "
             << totalProductos << " producto(s), "
             << totalVentas    << " venta(s)." << endl;
    } catch (const exception& e) {
        cout << "Advertencia al cargar datos: " << e.what() << endl;
        cout << "Se iniciara con datos vacios." << endl;
    }

    // Ciclo principal
    int opcion = 0;

    do {
        mostrarMenuPrincipal();

        try {
            cin >> opcion;
            if (cin.fail()) throw invalid_argument("Entrada no numerica");
            if (opcion < 1 || opcion > 5) throw out_of_range("Ingrese una opcion del 1 al 5");
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
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
            case 5: cout << "\nHasta luego." << endl; break;
        }

    } while (opcion != 5);

    return 0;
}
