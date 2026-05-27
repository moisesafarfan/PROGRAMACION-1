#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// ═══════════════════════════════════════════════════════
//  estructuras.h
//  Define las estructuras de datos, constantes y
//  variables globales que usa todo el sistema.
// ═══════════════════════════════════════════════════════

// ───────────────────────────────────────────────────────
//  CONSTANTES DEL SISTEMA
// ───────────────────────────────────────────────────────
const int    MAX_PRODUCTOS  = 500;
const int    MAX_VENTAS     = 1000;
const int    MAX_DETALLE    = 20;       // max productos por venta
const int    MAX_MESES      = 12;

const double IVA_RATE       = 0.12;    // 12% IVA
const double DESC_MONTO     = 0.05;    // 5% si subtotal > Q500
const double DESC_BONO      = 0.03;    // 3% si articulos % 5 == 0
const double LIMITE_DESC    = 500.0;   // umbral para descuento

const char FILE_PRODUCTOS[] = "productos.dat";
const char FILE_VENTAS[]    = "ventas.dat";
const char FILE_REPORTE[]   = "reporte.txt";

// ───────────────────────────────────────────────────────
//  STRUCT: Producto
//  Representa cada articulo registrado en la tienda
// ───────────────────────────────────────────────────────
struct Producto {
    int    codigo;          // identificador unico
    char   nombre[60];      // nombre del producto
    char   categoria[30];   // ej: "Electronica", "Ropa"
    double precio;          // precio unitario en quetzales
    int    stock;           // unidades disponibles
    int    totalVendido;    // acumulado de unidades vendidas
    bool   activo;          // false = eliminado logicamente
};

// ───────────────────────────────────────────────────────
//  STRUCT: DetalleVenta
//  Representa una linea dentro de una venta
// ───────────────────────────────────────────────────────
struct DetalleVenta {
    int    idProducto;      // codigo del producto vendido
    char   nombre[60];      // nombre al momento de la venta
    int    cantidad;        // unidades compradas
    double precioUnit;      // precio al momento de la venta
    double subtotalDet;     // cantidad x precioUnit
};

// ───────────────────────────────────────────────────────
//  STRUCT: Venta
//  Representa una transaccion completa
// ───────────────────────────────────────────────────────
struct Venta {
    int          id;                    // numero de venta
    char         fecha[11];             // formato "YYYY-MM-DD"
    int          mes;                   // 0=enero ... 11=diciembre
    DetalleVenta detalles[MAX_DETALLE]; // productos de la venta
    int          numDetalles;           // cuantos productos tiene
    int          totalArticulos;        // suma de cantidades
    double       subtotal;              // antes de descuentos
    double       descuento;             // monto de descuento aplicado
    double       iva;                   // monto de IVA (12%)
    double       total;                 // total final redondeado
};

// ───────────────────────────────────────────────────────
//  VARIABLES GLOBALES
//  Declaradas aqui, definidas en main.cpp
// ───────────────────────────────────────────────────────
extern Producto productos[MAX_PRODUCTOS];
extern int      totalProductos;

extern Venta    ventas[MAX_VENTAS];
extern int      totalVentas;

// Matriz de ventas por mes: guarda IDs de ventas por mes
extern int ventasPorMes[MAX_MESES][MAX_VENTAS];
extern int conteoVentasMes[MAX_MESES];

#endif
