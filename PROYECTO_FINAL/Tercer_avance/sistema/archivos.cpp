// ═══════════════════════════════════════════════════════
//  archivos.cpp
//  Lee y escribe productos.dat y ventas.dat
// ═══════════════════════════════════════════════════════

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "estructuras.h"
#include "archivos.h"

using namespace std;

// ───────────────────────────────────────────────────────
//  cargarProductos()
//  Lee todos los productos guardados en productos.dat
//  Si el archivo no existe lo crea vacio
// ───────────────────────────────────────────────────────
void cargarProductos() {
    try {
        ifstream archivo(FILE_PRODUCTOS, ios::binary);

        // Si no existe, lo creamos vacio y salimos
        if (!archivo.is_open()) {
            ofstream crear(FILE_PRODUCTOS, ios::binary);
            if (!crear.is_open())
                throw runtime_error("No se pudo crear productos.dat");
            crear.close();
            totalProductos = 0;
            return;
        }

        totalProductos = 0;
        Producto p;

        // Leer producto por producto hasta el final del archivo
        while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
            if (totalProductos < MAX_PRODUCTOS) {
                productos[totalProductos] = p;
                totalProductos++;
            }
        }

        archivo.close();

    } catch (const exception& e) {
        cerr << "Error al cargar productos: " << e.what() << endl;
        totalProductos = 0;
    }
}

// ───────────────────────────────────────────────────────
//  guardarProductos()
//  Escribe todo el arreglo de productos en productos.dat
// ───────────────────────────────────────────────────────
void guardarProductos() {
    try {
        ofstream archivo(FILE_PRODUCTOS, ios::binary | ios::trunc);

        if (!archivo.is_open())
            throw runtime_error("No se pudo abrir productos.dat para escritura");

        for (int i = 0; i < totalProductos; i++) {
            archivo.write(reinterpret_cast<const char*>(&productos[i]), sizeof(Producto));
        }

        archivo.close();

    } catch (const exception& e) {
        cerr << "Error al guardar productos: " << e.what() << endl;
    }
}

// ───────────────────────────────────────────────────────
//  cargarVentas()
//  Lee todas las ventas guardadas en ventas.dat
// ───────────────────────────────────────────────────────
void cargarVentas() {
    try {
        ifstream archivo(FILE_VENTAS, ios::binary);

        if (!archivo.is_open()) {
            ofstream crear(FILE_VENTAS, ios::binary);
            if (!crear.is_open())
                throw runtime_error("No se pudo crear ventas.dat");
            crear.close();
            totalVentas = 0;
            return;
        }

        totalVentas = 0;
        Venta v;

        while (archivo.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
            if (totalVentas < MAX_VENTAS) {
                ventas[totalVentas] = v;

                // Reconstruir la matriz de ventas por mes
                if (v.mes >= 0 && v.mes < MAX_MESES) {
                    int idx = conteoVentasMes[v.mes];
                    if (idx < MAX_VENTAS) {
                        ventasPorMes[v.mes][idx] = totalVentas;
                        conteoVentasMes[v.mes]++;
                    }
                }

                totalVentas++;
            }
        }

        archivo.close();

    } catch (const exception& e) {
        cerr << "Error al cargar ventas: " << e.what() << endl;
        totalVentas = 0;
    }
}

// ───────────────────────────────────────────────────────
//  guardarVentas()
//  Escribe todo el arreglo de ventas en ventas.dat
// ───────────────────────────────────────────────────────
void guardarVentas() {
    try {
        ofstream archivo(FILE_VENTAS, ios::binary | ios::trunc);

        if (!archivo.is_open())
            throw runtime_error("No se pudo abrir ventas.dat para escritura");

        for (int i = 0; i < totalVentas; i++) {
            archivo.write(reinterpret_cast<const char*>(&ventas[i]), sizeof(Venta));
        }

        archivo.close();

    } catch (const exception& e) {
        cerr << "Error al guardar ventas: " << e.what() << endl;
    }
}
