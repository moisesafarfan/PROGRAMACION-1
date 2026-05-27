// ═══════════════════════════════════════════════════════
//  reportes.cpp
//  Modulo 3 - Reportes
//  Ordenamientos, busquedas y estadisticas del sistema
// ═══════════════════════════════════════════════════════

#include <iostream>
#include <cstring>
#include <stdexcept>
#include "estructuras.h"
#include "reportes.h"

using namespace std;

// Nombres de los meses para mostrar en reportes
const char* NOMBRES_MESES[12] = {
    "Enero", "Febrero", "Marzo",     "Abril",
    "Mayo",  "Junio",   "Julio",     "Agosto",
    "Septiembre", "Octubre", "Noviembre", "Diciembre"
};

// ───────────────────────────────────────────────────────
//  menuReportes()
//  Sub-menu del Modulo 3
// ───────────────────────────────────────────────────────
void menuReportes() {
    int opcion = 0;

    do {
        cout << "\n========================================" << endl;
        cout << "         MODULO 3 - REPORTES            " << endl;
        cout << "========================================" << endl;
        cout << " 1. Productos con menor stock" << endl;
        cout << " 2. Productos mas vendidos" << endl;
        cout << " 3. Ventas del dia" << endl;
        cout << " 4. Ventas por mes" << endl;
        cout << " 5. Ordenar productos (Bubble Sort)" << endl;
        cout << " 6. Ordenar productos (Selection Sort)" << endl;
        cout << " 0. Volver al menu principal" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";

        try {
            cin >> opcion;
            if (cin.fail()) throw invalid_argument("Entrada no numerica");
            if (opcion < 0 || opcion > 6) throw out_of_range("Opcion fuera de rango");
        } catch (const exception& e) {
            cout << "Error: " << e.what() << ". Ingrese 0-6." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
            continue;
        }

        int criterio;

        switch (opcion) {
            case 1: reporteMenorStock();   break;
            case 2: reporteMasVendidos();  break;
            case 3: reporteVentasDia();    break;
            case 4: reporteVentasMes();    break;
            case 5:
                cout << "\nCriterio de ordenamiento:" << endl;
                cout << " 1. Precio ascendente" << endl;
                cout << " 2. Precio descendente" << endl;
                cout << " 3. Stock ascendente" << endl;
                cout << " 4. Stock descendente" << endl;
                cout << " 5. Mas vendidos" << endl;
                cout << "Seleccione: ";
                try {
                    cin >> criterio;
                    if (cin.fail() || criterio < 1 || criterio > 5)
                        throw invalid_argument("Criterio invalido");
                    ordenarBubble(criterio);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                break;
            case 6:
                cout << "\nCriterio de ordenamiento:" << endl;
                cout << " 1. Precio ascendente" << endl;
                cout << " 2. Precio descendente" << endl;
                cout << " 3. Stock ascendente" << endl;
                cout << " 4. Stock descendente" << endl;
                cout << " 5. Mas vendidos" << endl;
                cout << "Seleccione: ";
                try {
                    cin >> criterio;
                    if (cin.fail() || criterio < 1 || criterio > 5)
                        throw invalid_argument("Criterio invalido");
                    ordenarSelection(criterio);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                break;
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
        }

    } while (opcion != 0);
}

// ───────────────────────────────────────────────────────
//  Funcion auxiliar: debeCambiar()
//  Decide si dos productos estan en orden incorrecto
//  segun el criterio dado
//  criterio: 1=precio asc, 2=precio desc,
//            3=stock asc,  4=stock desc, 5=mas vendidos
// ───────────────────────────────────────────────────────
static bool debeCambiar(const Producto& a, const Producto& b, int criterio) {
    switch (criterio) {
        case 1: return a.precio       > b.precio;
        case 2: return a.precio       < b.precio;
        case 3: return a.stock        > b.stock;
        case 4: return a.stock        < b.stock;
        case 5: return a.totalVendido < b.totalVendido;
        default: return false;
    }
}

// ───────────────────────────────────────────────────────
//  ordenarBubble()
//  Ordena el arreglo de productos con Bubble Sort
// ───────────────────────────────────────────────────────
void ordenarBubble(int criterio) {
    if (totalProductos <= 1) {
        cout << "No hay suficientes productos para ordenar." << endl;
        return;
    }

    // Algoritmo Bubble Sort
    for (int i = 0; i < totalProductos - 1; i++) {
        for (int j = 0; j < totalProductos - i - 1; j++) {
            if (debeCambiar(productos[j], productos[j + 1], criterio)) {
                // Intercambiar
                Producto temp  = productos[j];
                productos[j]   = productos[j + 1];
                productos[j+1] = temp;
            }
        }
    }

    // Mostrar resultado
    const char* criterioNombre[] = {
        "", "precio ascendente", "precio descendente",
        "stock ascendente", "stock descendente", "mas vendidos"
    };
    cout << "\nProductos ordenados por " << criterioNombre[criterio] << ":" << endl;
    cout << "COD  | NOMBRE                       | PRECIO   | STOCK | VENDIDOS" << endl;
    cout << "-----|------------------------------|----------|-------|----------" << endl;

    for (int i = 0; i < totalProductos; i++) {
        if (productos[i].activo) {
            cout.width(4);  cout << productos[i].codigo       << " | ";
            cout.width(28); cout << productos[i].nombre       << " | ";
            cout << "Q";
            cout.width(7);  cout << productos[i].precio       << " | ";
            cout.width(5);  cout << productos[i].stock        << " | ";
            cout.width(8);  cout << productos[i].totalVendido << endl;
        }
    }
}

// ───────────────────────────────────────────────────────
//  ordenarSelection()
//  Ordena el arreglo de productos con Selection Sort
// ───────────────────────────────────────────────────────
void ordenarSelection(int criterio) {
    if (totalProductos <= 1) {
        cout << "No hay suficientes productos para ordenar." << endl;
        return;
    }

    // Algoritmo Selection Sort
    for (int i = 0; i < totalProductos - 1; i++) {
        int minIdx = i;

        // Buscar el minimo (o maximo segun criterio) en la parte no ordenada
        for (int j = i + 1; j < totalProductos; j++) {
            if (debeCambiar(productos[minIdx], productos[j], criterio)) {
                minIdx = j;
            }
        }

        // Intercambiar si encontramos un elemento mejor
        if (minIdx != i) {
            Producto temp      = productos[i];
            productos[i]       = productos[minIdx];
            productos[minIdx]  = temp;
        }
    }

    // Mostrar resultado
    const char* criterioNombre[] = {
        "", "precio ascendente", "precio descendente",
        "stock ascendente", "stock descendente", "mas vendidos"
    };
    cout << "\nProductos ordenados por " << criterioNombre[criterio] << ":" << endl;
    cout << "COD  | NOMBRE                       | PRECIO   | STOCK | VENDIDOS" << endl;
    cout << "-----|------------------------------|----------|-------|----------" << endl;

    for (int i = 0; i < totalProductos; i++) {
        if (productos[i].activo) {
            cout.width(4);  cout << productos[i].codigo       << " | ";
            cout.width(28); cout << productos[i].nombre       << " | ";
            cout << "Q";
            cout.width(7);  cout << productos[i].precio       << " | ";
            cout.width(5);  cout << productos[i].stock        << " | ";
            cout.width(8);  cout << productos[i].totalVendido << endl;
        }
    }
}

// ───────────────────────────────────────────────────────
//  reporteMenorStock()
//  Muestra productos cuyo stock esta por debajo del umbral
// ───────────────────────────────────────────────────────
void reporteMenorStock() {
    int umbral;
    cout << "Mostrar productos con stock menor o igual a: ";
    try {
        cin >> umbral;
        if (cin.fail() || umbral < 0)
            throw invalid_argument("Umbral invalido");
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cout << "\n========================================" << endl;
    cout << "   PRODUCTOS CON STOCK <= " << umbral << endl;
    cout << "========================================" << endl;

    int encontrados = 0;
    for (int i = 0; i < totalProductos; i++) {
        if (productos[i].activo && productos[i].stock <= umbral) {
            cout << "["  << productos[i].codigo << "] "
                 << productos[i].nombre
                 << " - Stock: " << productos[i].stock << endl;
            encontrados++;
        }
    }

    if (encontrados == 0)
        cout << "No hay productos con stock <= " << umbral << endl;
    else
        cout << "\nTotal encontrados: " << encontrados << endl;
}

// ───────────────────────────────────────────────────────
//  reporteMasVendidos()
//  Muestra los 10 productos mas vendidos
// ───────────────────────────────────────────────────────
void reporteMasVendidos() {
    if (totalProductos == 0) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    // Copiar arreglo para no alterar el original
    Producto copia[MAX_PRODUCTOS];
    for (int i = 0; i < totalProductos; i++)
        copia[i] = productos[i];

    // Ordenar copia por totalVendido descendente (Bubble Sort)
    for (int i = 0; i < totalProductos - 1; i++) {
        for (int j = 0; j < totalProductos - i - 1; j++) {
            if (copia[j].totalVendido < copia[j + 1].totalVendido) {
                Producto temp = copia[j];
                copia[j]      = copia[j + 1];
                copia[j + 1]  = temp;
            }
        }
    }

    cout << "\n========================================" << endl;
    cout << "        TOP 10 PRODUCTOS MAS VENDIDOS   " << endl;
    cout << "========================================" << endl;
    cout << "#  | COD  | NOMBRE                       | VENDIDOS" << endl;
    cout << "---|-----|------------------------------|----------" << endl;

    int mostrados = 0;
    for (int i = 0; i < totalProductos && mostrados < 10; i++) {
        if (copia[i].activo && copia[i].totalVendido > 0) {
            cout.width(2);  cout << (mostrados + 1)       << " | ";
            cout.width(4);  cout << copia[i].codigo       << " | ";
            cout.width(28); cout << copia[i].nombre       << " | ";
            cout.width(8);  cout << copia[i].totalVendido << endl;
            mostrados++;
        }
    }

    if (mostrados == 0)
        cout << "Aun no hay ventas registradas." << endl;
}

// ───────────────────────────────────────────────────────
//  reporteVentasDia()
//  Muestra el total de ventas de una fecha especifica
// ───────────────────────────────────────────────────────
void reporteVentasDia() {
    char fecha[11];
    cout << "Ingrese la fecha (YYYY-MM-DD): ";
    cin.ignore();
    cin.getline(fecha, 11);

    double totalDia  = 0.0;
    int    cantVentas = 0;

    cout << "\n========================================" << endl;
    cout << "   VENTAS DEL DIA: " << fecha << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < totalVentas; i++) {
        if (strcmp(ventas[i].fecha, fecha) == 0) {
            cout << "Venta #" << ventas[i].id
                 << " | Total: Q" << ventas[i].total << endl;
            totalDia += ventas[i].total;
            cantVentas++;
        }
    }

    if (cantVentas == 0) {
        cout << "No hay ventas registradas para esa fecha." << endl;
    } else {
        cout << "----------------------------------------" << endl;
        cout << "Total de ventas   : " << cantVentas << endl;
        cout << "Total recaudado   : Q" << totalDia  << endl;
    }
}

// ───────────────────────────────────────────────────────
//  reporteVentasMes()
//  Usa la matriz ventasPorMes[12][MAX_VENTAS] para mostrar
//  el total recaudado por cada mes del anio
// ───────────────────────────────────────────────────────
void reporteVentasMes() {
    cout << "\n========================================" << endl;
    cout << "         VENTAS POR MES (MATRIZ)        " << endl;
    cout << "========================================" << endl;
    cout << "MES          | VENTAS | TOTAL RECAUDADO " << endl;
    cout << "-------------|--------|------------------" << endl;

    double totalAnio = 0.0;

    for (int mes = 0; mes < MAX_MESES; mes++) {
        double totalMes  = 0.0;
        int    numVentas = conteoVentasMes[mes];

        // Recorrer la fila del mes en la matriz
        for (int i = 0; i < numVentas; i++) {
            int idxVenta = ventasPorMes[mes][i];
            totalMes += ventas[idxVenta].total;
        }

        totalAnio += totalMes;

        cout.width(12); cout << NOMBRES_MESES[mes] << " | ";
        cout.width(6);  cout << numVentas           << " | ";
        cout << "Q";
        cout.width(15); cout << totalMes            << endl;
    }

    cout << "-------------|--------|------------------" << endl;
    cout << "TOTAL ANUAL  |        | Q" << totalAnio   << endl;
}
