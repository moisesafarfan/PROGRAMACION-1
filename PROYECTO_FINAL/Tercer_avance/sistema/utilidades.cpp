// ═══════════════════════════════════════════════════════
//  utilidades.cpp
//  Modulo 4 - Utilidades del Sistema
//  Exportar reporte, reiniciar inventario, estadisticas
// ═══════════════════════════════════════════════════════

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <stdexcept>
#include "estructuras.h"
#include "archivos.h"
#include "utilidades.h"

using namespace std;

const char* MESES_UTIL[12] = {
    "Enero", "Febrero", "Marzo",     "Abril",
    "Mayo",  "Junio",   "Julio",     "Agosto",
    "Septiembre", "Octubre", "Noviembre", "Diciembre"
};

// ───────────────────────────────────────────────────────
//  menuUtilidades()
//  Sub-menu del Modulo 4
// ───────────────────────────────────────────────────────
void menuUtilidades() {
    int opcion = 0;

    do {
        cout << "\n========================================" << endl;
        cout << "     MODULO 4 - UTILIDADES DEL SISTEMA  " << endl;
        cout << "========================================" << endl;
        cout << " 1. Exportar reporte a .txt" << endl;
        cout << " 2. Reiniciar inventario" << endl;
        cout << " 3. Estadisticas generales" << endl;
        cout << " 0. Volver al menu principal" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";

        try {
            cin >> opcion;
            if (cin.fail()) throw invalid_argument("Entrada no numerica");
            if (opcion < 0 || opcion > 3) throw out_of_range("Opcion fuera de rango");
        } catch (const exception& e) {
            cout << "Error: " << e.what() << ". Ingrese 0-3." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1: exportarReporte();     break;
            case 2: reiniciarInventario(); break;
            case 3: mostrarEstadisticas(); break;
            case 0: cout << "Volviendo al menu principal..." << endl; break;
        }

    } while (opcion != 0);
}

// ───────────────────────────────────────────────────────
//  exportarReporte()
//  Genera reporte.txt con productos y resumen de ventas
// ───────────────────────────────────────────────────────
void exportarReporte() {
    try {
        ofstream archivo(FILE_REPORTE);
        if (!archivo.is_open())
            throw runtime_error("No se pudo crear reporte.txt");

        // Encabezado con fecha y hora actual
        time_t ahora = time(0);
        char* fechaHora = ctime(&ahora);

        archivo << "========================================" << endl;
        archivo << "   REPORTE DEL SISTEMA - TIENDA         " << endl;
        archivo << "========================================" << endl;
        archivo << "Generado: " << fechaHora;
        archivo << endl;

        // Sección de productos
        archivo << "----------------------------------------" << endl;
        archivo << "  INVENTARIO DE PRODUCTOS               " << endl;
        archivo << "----------------------------------------" << endl;

        int activos = 0;
        for (int i = 0; i < totalProductos; i++) {
            if (productos[i].activo) {
                archivo << "["  << productos[i].codigo    << "] "
                        << productos[i].nombre    << endl;
                archivo << "  Categoria : " << productos[i].categoria << endl;
                archivo << "  Precio    : Q" << productos[i].precio   << endl;
                archivo << "  Stock     : " << productos[i].stock     << endl;
                archivo << "  Vendidos  : " << productos[i].totalVendido << endl;
                activos++;
            }
        }
        archivo << "\nTotal productos activos: " << activos << endl;
        archivo << endl;

        // Sección de ventas
        archivo << "----------------------------------------" << endl;
        archivo << "  RESUMEN DE VENTAS                     " << endl;
        archivo << "----------------------------------------" << endl;

        double totalGeneral = 0.0;
        for (int i = 0; i < totalVentas; i++) {
            archivo << "Venta #" << ventas[i].id
                    << " | Fecha: " << ventas[i].fecha
                    << " | Total: Q" << ventas[i].total << endl;
            totalGeneral += ventas[i].total;
        }

        archivo << "\nTotal de ventas    : " << totalVentas    << endl;
        archivo << "Total recaudado    : Q" << totalGeneral   << endl;
        archivo << endl;

        // Sección de ventas por mes
        archivo << "----------------------------------------" << endl;
        archivo << "  VENTAS POR MES                        " << endl;
        archivo << "----------------------------------------" << endl;

        for (int mes = 0; mes < MAX_MESES; mes++) {
            double totalMes = 0.0;
            for (int i = 0; i < conteoVentasMes[mes]; i++) {
                int idx = ventasPorMes[mes][i];
                totalMes += ventas[idx].total;
            }
            archivo << MESES_UTIL[mes] << ": "
                    << conteoVentasMes[mes] << " ventas"
                    << " | Q" << totalMes << endl;
        }

        archivo << endl;
        archivo << "========================================" << endl;
        archivo << "           FIN DEL REPORTE              " << endl;
        archivo << "========================================" << endl;

        archivo.close();
        cout << "\nReporte exportado correctamente en '" << FILE_REPORTE << "'" << endl;

    } catch (const exception& e) {
        cout << "Error al exportar: " << e.what() << endl;
    }
}

// ───────────────────────────────────────────────────────
//  reiniciarInventario()
//  Pone el stock de todos los productos en 0
//  Requiere que el usuario escriba "CONFIRMAR"
// ───────────────────────────────────────────────────────
void reiniciarInventario() {
    cout << "\n!!! ADVERTENCIA !!!" << endl;
    cout << "Esta accion pondra el stock de TODOS los productos en 0." << endl;
    cout << "Escriba CONFIRMAR para continuar: ";

    char confirmacion[20];
    cin.ignore();
    cin.getline(confirmacion, 20);

    if (strcmp(confirmacion, "CONFIRMAR") == 0) {
        for (int i = 0; i < totalProductos; i++) {
            productos[i].stock = 0;
        }
        guardarProductos();
        cout << "Inventario reiniciado. Todos los stocks fueron puestos en 0." << endl;
    } else {
        cout << "Operacion cancelada. No se realizaron cambios." << endl;
    }
}

// ───────────────────────────────────────────────────────
//  mostrarEstadisticas()
//  Muestra un resumen general del estado del sistema
// ───────────────────────────────────────────────────────
void mostrarEstadisticas() {
    cout << "\n========================================" << endl;
    cout << "       ESTADISTICAS GENERALES           " << endl;
    cout << "========================================" << endl;

    // Contar productos activos y calcular valor del inventario
    int    activosCount  = 0;
    double valorInventario = 0.0;
    int    stockTotal    = 0;
    int    sinStock      = 0;

    for (int i = 0; i < totalProductos; i++) {
        if (productos[i].activo) {
            activosCount++;
            valorInventario += productos[i].precio * productos[i].stock;
            stockTotal      += productos[i].stock;
            if (productos[i].stock == 0) sinStock++;
        }
    }

    // Calcular total recaudado
    double totalRecaudado = 0.0;
    double mayorVenta     = 0.0;
    for (int i = 0; i < totalVentas; i++) {
        totalRecaudado += ventas[i].total;
        if (ventas[i].total > mayorVenta)
            mayorVenta = ventas[i].total;
    }

    double promedioVenta = (totalVentas > 0) ? totalRecaudado / totalVentas : 0.0;

    cout << "--- Productos ---" << endl;
    cout << "Total registrados   : " << totalProductos  << endl;
    cout << "Productos activos   : " << activosCount    << endl;
    cout << "Productos sin stock : " << sinStock        << endl;
    cout << "Unidades en stock   : " << stockTotal      << endl;
    cout << "Valor del inventario: Q" << valorInventario << endl;

    cout << "\n--- Ventas ---" << endl;
    cout << "Total de ventas     : " << totalVentas     << endl;
    cout << "Total recaudado     : Q" << totalRecaudado  << endl;
    cout << "Promedio por venta  : Q" << promedioVenta   << endl;
    cout << "Venta mas alta      : Q" << mayorVenta      << endl;
    cout << "========================================" << endl;
}
