// ═══════════════════════════════════════════════════════
//  reportes.cpp
//  Modulo 3 - Reportes
//  Ordenamientos (Bubble Sort y Selection Sort),
//  busquedas y estadisticas del sistema.
//  Usa la matriz ventasPorMes[12][MAX_VENTAS]
// ═══════════════════════════════════════════════════════

#include <iostream>
#include <cstring>
#include <stdexcept>
#include "estructuras.h"
#include "reportes.h"

using namespace std;

// Nombres de los meses para mostrar en reportes
const char* NOMBRES_MESES[12] = {
    "Enero",      "Febrero",  "Marzo",    "Abril",
    "Mayo",       "Junio",    "Julio",    "Agosto",
    "Septiembre", "Octubre",  "Noviembre","Diciembre"
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
        cout << " 1. Productos con menor stock"            << endl;
        cout << " 2. Productos mas vendidos (Top 10)"      << endl;
        cout << " 3. Ventas del dia"                       << endl;
        cout << " 4. Ventas por mes (matriz)"              << endl;
        cout << " 5. Ordenar productos - Bubble Sort"      << endl;
        cout << " 6. Ordenar productos - Selection Sort"   << endl;
        cout << " 0. Volver al menu principal"             << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";

        try {
            cin >> opcion;
            if (cin.fail())
                throw invalid_argument("Entrada no numerica");
            if (opcion < 0 || opcion > 6)
                throw out_of_range("Opcion invalida. Ingrese 0-6");
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
            continue;
        } catch (const out_of_range& e) {
            cerr << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
            continue;
        }

        int criterio = 0;

        switch (opcion) {
            case 1: reporteMenorStock();  break;
            case 2: reporteMasVendidos(); break;
            case 3: reporteVentasDia();   break;
            case 4: reporteVentasMes();   break;
            case 5:
            case 6:
                cout << "\nCriterio de ordenamiento:" << endl;
                cout << " 1. Precio ascendente"       << endl;
                cout << " 2. Precio descendente"      << endl;
                cout << " 3. Stock ascendente"        << endl;
                cout << " 4. Stock descendente"       << endl;
                cout << " 5. Mas vendidos"            << endl;
                cout << "Seleccione: ";
                try {
                    cin >> criterio;
                    if (cin.fail())
                        throw invalid_argument("Criterio invalido. Ingrese 1-5");
                    if (criterio < 1 || criterio > 5)
                        throw out_of_range("Criterio fuera de rango. Ingrese 1-5");
                    if (opcion == 5)
                        ordenarBubble(criterio);
                    else
                        ordenarSelection(criterio);
                } catch (const exception& e) {
                    cerr << "Error: " << e.what() << endl;
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
//  debeCambiar()
//  Funcion auxiliar para los algoritmos de ordenamiento.
//  Retorna true si los productos a y b estan en el
//  orden incorrecto segun el criterio.
//  criterio: 1=precio asc, 2=precio desc,
//            3=stock asc,  4=stock desc, 5=mas vendidos
// ───────────────────────────────────────────────────────
static bool debeCambiar(const Producto& a, const Producto& b, int criterio) {
    switch (criterio) {
        case 1: return a.precio       > b.precio;        // precio asc
        case 2: return a.precio       < b.precio;        // precio desc
        case 3: return a.stock        > b.stock;         // stock asc
        case 4: return a.stock        < b.stock;         // stock desc
        case 5: return a.totalVendido < b.totalVendido;  // mas vendidos
        default: return false;
    }
}

// ───────────────────────────────────────────────────────
//  mostrarTablaOrdenada()
//  Funcion auxiliar para mostrar el resultado
//  de cualquier ordenamiento
// ───────────────────────────────────────────────────────
static void mostrarTablaOrdenada(const char* criterioNombre) {
    cout << "\nProductos ordenados por: " << criterioNombre << endl;
    cout << "=========================================="
            "===================" << endl;
    cout << "COD  | NOMBRE                       | "
            "PRECIO    | STOCK | VENDIDOS" << endl;
    cout << "-----|------------------------------|"
            "----------|-------|----------" << endl;

    for (int i = 0; i < totalProductos; i++) {
        if (productos[i].activo) {
            cout.width(4);  cout << productos[i].codigo       << " | ";
            cout.width(28); cout << productos[i].nombre       << " | ";
            cout << "Q";
            cout.width(8);  cout << productos[i].precio       << " | ";
            cout.width(5);  cout << productos[i].stock        << " | ";
            cout.width(8);  cout << productos[i].totalVendido << endl;
        }
    }
    cout << "Total productos mostrados: " << totalProductos << endl;
}

// ───────────────────────────────────────────────────────
//  ordenarBubble()
//  Ordena el arreglo de productos usando Bubble Sort.
//  Compara elementos adyacentes e intercambia si estan
//  en el orden incorrecto. Repite hasta no haber cambios.
// ───────────────────────────────────────────────────────
void ordenarBubble(int criterio) {
    try {
        if (totalProductos == 0)
            throw runtime_error("No hay productos registrados para ordenar");
        if (totalProductos == 1) {
            cout << "Solo hay un producto, no es necesario ordenar." << endl;
            return;
        }

        // ── Algoritmo Bubble Sort ──
        // Cada pasada lleva el elemento mas grande al final
        bool huboCambio;
        for (int i = 0; i < totalProductos - 1; i++) {
            huboCambio = false;
            for (int j = 0; j < totalProductos - i - 1; j++) {
                if (debeCambiar(productos[j], productos[j + 1], criterio)) {
                    // Intercambiar productos[j] y productos[j+1]
                    Producto temp  = productos[j];
                    productos[j]   = productos[j + 1];
                    productos[j+1] = temp;
                    huboCambio = true;
                }
            }
            // Optimizacion: si no hubo cambios el arreglo ya esta ordenado
            if (!huboCambio) break;
        }

        const char* nombres[] = {
            "", "precio ascendente", "precio descendente",
            "stock ascendente", "stock descendente", "mas vendidos"
        };
        mostrarTablaOrdenada(nombres[criterio]);

    } catch (const exception& e) {
        cerr << "Error en Bubble Sort: " << e.what() << endl;
    }
}

// ───────────────────────────────────────────────────────
//  ordenarSelection()
//  Ordena el arreglo de productos usando Selection Sort.
//  Busca el elemento minimo en la parte no ordenada
//  y lo coloca en su posicion correcta.
// ───────────────────────────────────────────────────────
void ordenarSelection(int criterio) {
    try {
        if (totalProductos == 0)
            throw runtime_error("No hay productos registrados para ordenar");
        if (totalProductos == 1) {
            cout << "Solo hay un producto, no es necesario ordenar." << endl;
            return;
        }

        // ── Algoritmo Selection Sort ──
        for (int i = 0; i < totalProductos - 1; i++) {
            int minIdx = i;

            // Buscar el minimo en la parte no ordenada
            for (int j = i + 1; j < totalProductos; j++) {
                if (debeCambiar(productos[minIdx], productos[j], criterio))
                    minIdx = j;
            }

            // Intercambiar solo si encontramos un elemento mejor
            if (minIdx != i) {
                Producto temp      = productos[i];
                productos[i]       = productos[minIdx];
                productos[minIdx]  = temp;
            }
        }

        const char* nombres[] = {
            "", "precio ascendente", "precio descendente",
            "stock ascendente", "stock descendente", "mas vendidos"
        };
        mostrarTablaOrdenada(nombres[criterio]);

    } catch (const exception& e) {
        cerr << "Error en Selection Sort: " << e.what() << endl;
    }
}

// ───────────────────────────────────────────────────────
//  reporteMenorStock()
//  Muestra productos con stock menor o igual al umbral
// ───────────────────────────────────────────────────────
void reporteMenorStock() {
    try {
        if (totalProductos == 0)
            throw runtime_error("No hay productos registrados");

        int umbral;
        cout << "Mostrar productos con stock menor o igual a: ";
        cin >> umbral;
        if (cin.fail() || umbral < 0)
            throw invalid_argument("Umbral invalido. Debe ser un numero >= 0");

        cout << "\n========================================" << endl;
        cout << "   PRODUCTOS CON STOCK <= " << umbral       << endl;
        cout << "========================================" << endl;

        int encontrados = 0;
        for (int i = 0; i < totalProductos; i++) {
            if (productos[i].activo && productos[i].stock <= umbral) {
                cout << "  [" << productos[i].codigo << "] "
                     << productos[i].nombre
                     << " | Stock actual: " << productos[i].stock
                     << " | Precio: Q"     << productos[i].precio << endl;
                encontrados++;
            }
        }

        if (encontrados == 0)
            cout << "No hay productos con stock <= " << umbral << endl;
        else
            cout << "\nTotal encontrados: " << encontrados << endl;

    } catch (const exception& e) {
        cerr << "Error en reporte de stock: " << e.what() << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

// ───────────────────────────────────────────────────────
//  reporteMasVendidos()
//  Muestra el top 10 de productos mas vendidos
//  Usa una copia del arreglo para no alterar el original
// ───────────────────────────────────────────────────────
void reporteMasVendidos() {
    try {
        if (totalProductos == 0)
            throw runtime_error("No hay productos registrados");

        // Copiar arreglo para no alterar el orden original
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
        cout << "     TOP 10 - PRODUCTOS MAS VENDIDOS    " << endl;
        cout << "========================================" << endl;
        cout << " # | COD  | NOMBRE                       | VENDIDOS" << endl;
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
            cout << "  Aun no hay ventas registradas." << endl;
        else
            cout << "\nSe muestran los " << mostrados << " productos mas vendidos." << endl;

    } catch (const exception& e) {
        cerr << "Error en reporte de mas vendidos: " << e.what() << endl;
    }
}

// ───────────────────────────────────────────────────────
//  reporteVentasDia()
//  Muestra todas las ventas de una fecha especifica
// ───────────────────────────────────────────────────────
void reporteVentasDia() {
    try {
        if (totalVentas == 0)
            throw runtime_error("No hay ventas registradas en el sistema");

        char fecha[11];
        cout << "Ingrese la fecha (YYYY-MM-DD): ";
        cin.ignore();
        cin.getline(fecha, 11);

        if (strlen(fecha) != 10)
            throw invalid_argument("Formato de fecha invalido. Use YYYY-MM-DD");

        double totalDia   = 0.0;
        int    cantVentas = 0;

        cout << "\n========================================" << endl;
        cout << "   VENTAS DEL DIA: " << fecha               << endl;
        cout << "========================================" << endl;
        cout << " VENTA | PRODUCTOS | DESCUENTO | IVA    | TOTAL" << endl;
        cout << "-------|-----------|-----------|--------|--------" << endl;

        for (int i = 0; i < totalVentas; i++) {
            if (strcmp(ventas[i].fecha, fecha) == 0) {
                cout.width(6);  cout << ventas[i].id           << " | ";
                cout.width(9);  cout << ventas[i].numDetalles  << " | ";
                cout << "Q";
                cout.width(8);  cout << ventas[i].descuento    << " | ";
                cout << "Q";
                cout.width(6);  cout << ventas[i].iva          << " | ";
                cout << "Q";
                cout.width(6);  cout << ventas[i].total        << endl;
                totalDia += ventas[i].total;
                cantVentas++;
            }
        }

        if (cantVentas == 0) {
            cout << "  No hay ventas registradas para esa fecha." << endl;
        } else {
            cout << "========================================" << endl;
            cout << "Total ventas del dia : " << cantVentas   << endl;
            cout << "Total recaudado      : Q" << totalDia    << endl;
        }

    } catch (const exception& e) {
        cerr << "Error en reporte del dia: " << e.what() << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

// ───────────────────────────────────────────────────────
//  reporteVentasMes()
//  Usa la matriz ventasPorMes[12][MAX_VENTAS]
//  Cada fila = un mes, cada columna = indice de una venta
//  Muestra el total recaudado por mes y el total anual
// ───────────────────────────────────────────────────────
void reporteVentasMes() {
    try {
        cout << "\n========================================" << endl;
        cout << "    VENTAS POR MES  (matriz 12 x N)     " << endl;
        cout << "========================================" << endl;
        cout << "  La matriz ventasPorMes[12][N] almacena" << endl;
        cout << "  los indices de cada venta por mes."     << endl;
        cout << "========================================" << endl;
        cout << "MES           | N.VENTAS | RECAUDADO      " << endl;
        cout << "--------------|----------|----------------" << endl;

        double totalAnio    = 0.0;
        int    ventasTotal  = 0;
        bool   hayDatos     = false;

        for (int mes = 0; mes < MAX_MESES; mes++) {
            int    numVentas = conteoVentasMes[mes];
            double totalMes  = 0.0;

            // Recorrer la fila [mes] de la matriz
            for (int i = 0; i < numVentas; i++) {
                int idxVenta = ventasPorMes[mes][i];

                // Validar que el indice sea valido
                if (idxVenta < 0 || idxVenta >= totalVentas)
                    throw runtime_error("Indice invalido en matriz de ventas");

                totalMes += ventas[idxVenta].total;
            }

            totalAnio   += totalMes;
            ventasTotal += numVentas;

            if (numVentas > 0) hayDatos = true;

            cout.width(13); cout << NOMBRES_MESES[mes] << " | ";
            cout.width(8);  cout << numVentas           << " | ";
            cout << "Q";
            cout.width(13); cout << totalMes            << endl;
        }

        cout << "--------------|----------|----------------" << endl;
        cout << "TOTAL ANUAL   | ";
        cout.width(8); cout << ventasTotal << " | Q";
        cout.width(13); cout << totalAnio  << endl;

        if (!hayDatos)
            cout << "\nAun no hay ventas registradas en ningun mes." << endl;

    } catch (const exception& e) {
        cerr << "Error en reporte mensual: " << e.what() << endl;
    }
}
