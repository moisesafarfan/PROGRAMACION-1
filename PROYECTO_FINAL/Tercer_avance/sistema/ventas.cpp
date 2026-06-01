// ═══════════════════════════════════════════════════════
//  ventas.cpp
//  Modulo 2 - Proceso de Venta
//  Crear venta, validar stock, calcular totales,
//  aplicar IVA y descuentos, guardar en ventas.dat
// ═══════════════════════════════════════════════════════

#include <iostream>
#include <cstring>
#include <cmath>
#include <ctime>
#include <stdexcept>
#include "estructuras.h"
#include "archivos.h"
#include "productos.h"
#include "ventas.h"

using namespace std;

// ───────────────────────────────────────────────────────
//  obtenerFecha()
//  Obtiene la fecha actual del sistema en formato YYYY-MM-DD
// ───────────────────────────────────────────────────────
void obtenerFecha(char* buffer) {
    time_t ahora = time(0);
    tm* t = localtime(&ahora);
    // formato: YYYY-MM-DD
    sprintf(buffer, "%04d-%02d-%02d",
            t->tm_year + 1900,
            t->tm_mon + 1,
            t->tm_mday);
}

// ───────────────────────────────────────────────────────
//  redondear()
//  Redondea un valor a N decimales
// ───────────────────────────────────────────────────────
double redondear(double valor, int decimales) {
    double factor = pow(10.0, decimales);
    return round(valor * factor) / factor;
}

// ───────────────────────────────────────────────────────
//  calcularDescuento()
//  Aplica descuentos segun las reglas del sistema:
//  - 5% si subtotal > Q500
//  - 3% adicional si totalArticulos % 5 == 0
// ───────────────────────────────────────────────────────
double calcularDescuento(double subtotal, int totalArticulos) {
    double descuento = 0.0;

    if (subtotal > LIMITE_DESC)
        descuento += subtotal * DESC_MONTO;     // 5%

    if (totalArticulos > 0 && totalArticulos % 5 == 0)
        descuento += subtotal * DESC_BONO;      // 3%

    return descuento;
}

// ───────────────────────────────────────────────────────
//  calcularIVA()
//  Calcula el IVA (12%) sobre la base despues de descuentos
// ───────────────────────────────────────────────────────
double calcularIVA(double base) {
    return base * IVA_RATE;
}

// ───────────────────────────────────────────────────────
//  actualizarMatrizMes()
//  Agrega el indice de la venta a la matriz ventasPorMes
// ───────────────────────────────────────────────────────
void actualizarMatrizMes(int idxVenta) {
    int mes = ventas[idxVenta].mes;
    if (mes >= 0 && mes < MAX_MESES) {
        int cuenta = conteoVentasMes[mes];
        if (cuenta < MAX_VENTAS) {
            ventasPorMes[mes][cuenta] = idxVenta;
            conteoVentasMes[mes]++;
        }
    }
}

// ───────────────────────────────────────────────────────
//  menuProcesarVenta()
//  Sub-menu del Modulo 2
// ───────────────────────────────────────────────────────
void menuProcesarVenta() {
    int opcion = 0;

    do {
        cout << "\n========================================" << endl;
        cout << "      MODULO 2 - PROCESO DE VENTA       " << endl;
        cout << "========================================" << endl;
        cout << " 1. Crear nueva venta" << endl;
        cout << " 0. Volver al menu principal" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";

        try {
            cin >> opcion;
            if (cin.fail()) throw invalid_argument("Entrada no numerica");
            if (opcion < 0 || opcion > 1) throw out_of_range("Opcion fuera de rango");
        } catch (const exception& e) {
            cout << "Error: " << e.what() << ". Ingrese 0 o 1." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1: procesarVenta(); break;
            case 0: cout << "Volviendo al menu principal..." << endl; break;
        }

    } while (opcion != 0);
}

// ───────────────────────────────────────────────────────
//  procesarVenta()
//  Flujo completo de una venta:
//  1. Seleccionar productos
//  2. Validar stock
//  3. Calcular subtotal, descuento, IVA y total
//  4. Mostrar ticket
//  5. Descontar stock y guardar
// ───────────────────────────────────────────────────────
void procesarVenta() {
    try {
        if (totalProductos == 0)
            throw runtime_error("No hay productos registrados en el sistema");

        if (totalVentas >= MAX_VENTAS)
            throw runtime_error("Se alcanzo el limite maximo de ventas");

        // Inicializar nueva venta
        Venta nuevaVenta;
        nuevaVenta.id            = totalVentas + 1;
        nuevaVenta.numDetalles   = 0;
        nuevaVenta.totalArticulos = 0;
        nuevaVenta.subtotal      = 0.0;
        nuevaVenta.descuento     = 0.0;
        nuevaVenta.iva           = 0.0;
        nuevaVenta.total         = 0.0;

        // Fecha y mes actuales
        obtenerFecha(nuevaVenta.fecha);
        time_t ahora = time(0);
        tm* t = localtime(&ahora);
        nuevaVenta.mes = t->tm_mon;     // 0=enero, 11=diciembre

        cout << "\n========================================" << endl;
        cout << "   NUEVA VENTA #" << nuevaVenta.id << "  |  " << nuevaVenta.fecha << endl;
        cout << "========================================" << endl;

        // Mostrar productos disponibles
        listarProductos();

        // ── Ciclo para agregar productos ──
        char continuar = 's';

        while ((continuar == 's' || continuar == 'S') &&
                nuevaVenta.numDetalles < MAX_DETALLE) {

            int codProducto, cantidad;

            try {
                cout << "\nIngrese el codigo del producto: ";
                cin >> codProducto;
                if (cin.fail()) throw invalid_argument("Codigo invalido");

                int idx = buscarPorCodigo(codProducto);
                if (idx == -1)
                    throw runtime_error("Producto no encontrado");

                cout << "Producto : " << productos[idx].nombre << endl;
                cout << "Precio   : Q" << productos[idx].precio << endl;
                cout << "Stock    : " << productos[idx].stock << endl;

                cout << "Cantidad : ";
                cin >> cantidad;
                if (cin.fail() || cantidad <= 0)
                    throw invalid_argument("La cantidad debe ser mayor a 0");

                if (productos[idx].stock < cantidad)
                    throw runtime_error("Stock insuficiente. Disponible: " +
                                        to_string(productos[idx].stock));

                // Agregar detalle a la venta
                DetalleVenta det;
                det.idProducto  = productos[idx].codigo;
                strcpy(det.nombre, productos[idx].nombre);
                det.cantidad    = cantidad;
                det.precioUnit  = productos[idx].precio;
                det.subtotalDet = cantidad * productos[idx].precio;

                nuevaVenta.detalles[nuevaVenta.numDetalles] = det;
                nuevaVenta.numDetalles++;
                nuevaVenta.subtotal       += det.subtotalDet;
                nuevaVenta.totalArticulos += cantidad;

                cout << "Agregado: " << cantidad << " x "
                     << productos[idx].nombre
                     << " = Q" << det.subtotalDet << endl;

            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }

            if (nuevaVenta.numDetalles < MAX_DETALLE) {
                cout << "\nAgregar otro producto? (s/n): ";
                cin >> continuar;
            } else {
                cout << "Se alcanzo el maximo de productos por venta." << endl;
                continuar = 'n';
            }
        }

        // Verificar que se agrego al menos un producto
        if (nuevaVenta.numDetalles == 0)
            throw runtime_error("La venta no tiene productos. Operacion cancelada.");

        // ── Calcular descuentos, IVA y total ──
        nuevaVenta.descuento = calcularDescuento(nuevaVenta.subtotal,
                                                  nuevaVenta.totalArticulos);
        double base          = nuevaVenta.subtotal - nuevaVenta.descuento;
        nuevaVenta.iva       = calcularIVA(base);
        nuevaVenta.total     = redondear(base + nuevaVenta.iva, 2);

        // ── Mostrar ticket ──
        cout << "\n========================================" << endl;
        cout << "              TICKET DE VENTA           " << endl;
        cout << "========================================" << endl;
        cout << "Venta #" << nuevaVenta.id
             << "  Fecha: " << nuevaVenta.fecha << endl;
        cout << "----------------------------------------" << endl;

        for (int i = 0; i < nuevaVenta.numDetalles; i++) {
            DetalleVenta& d = nuevaVenta.detalles[i];
            cout << d.cantidad << " x " << d.nombre
                 << " (Q" << d.precioUnit << ")"
                 << "  = Q" << d.subtotalDet << endl;
        }

        cout << "----------------------------------------" << endl;
        cout << "Subtotal   : Q" << nuevaVenta.subtotal      << endl;

        if (nuevaVenta.descuento > 0) {
            cout << "Descuento  : -Q" << nuevaVenta.descuento << endl;
            if (nuevaVenta.subtotal > LIMITE_DESC)
                cout << "  (5% por compra mayor a Q500)" << endl;
            if (nuevaVenta.totalArticulos % 5 == 0)
                cout << "  (3% bono por multiplo de 5 articulos)" << endl;
        }

        cout << "IVA (12%)  : Q" << nuevaVenta.iva   << endl;
        cout << "TOTAL      : Q" << nuevaVenta.total  << endl;
        cout << "========================================" << endl;

        // Confirmar venta
        char confirmar;
        cout << "Confirmar venta? (s/n): ";
        cin >> confirmar;

        if (confirmar != 's' && confirmar != 'S') {
            cout << "Venta cancelada." << endl;
            return;
        }

        // ── Descontar stock y actualizar totalVendido ──
        for (int i = 0; i < nuevaVenta.numDetalles; i++) {
            int idx = buscarPorCodigo(nuevaVenta.detalles[i].idProducto);
            if (idx != -1) {
                productos[idx].stock        -= nuevaVenta.detalles[i].cantidad;
                productos[idx].totalVendido += nuevaVenta.detalles[i].cantidad;
            }
        }

        // ── Guardar venta y productos ──
        ventas[totalVentas] = nuevaVenta;
        actualizarMatrizMes(totalVentas);
        totalVentas++;

        guardarVentas();
        guardarProductos();

        cout << "\nVenta registrada exitosamente." << endl;

    } catch (const exception& e) {
        cout << "Error en la venta: " << e.what() << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}
