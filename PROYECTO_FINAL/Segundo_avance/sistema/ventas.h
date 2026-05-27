#ifndef VENTAS_H
#define VENTAS_H

// ═══════════════════════════════════════════════════════
//  ventas.h
//  Prototipos del Modulo 2 - Proceso de Venta
// ═══════════════════════════════════════════════════════

void   menuProcesarVenta();
void   procesarVenta();
double calcularDescuento(double subtotal, int totalArticulos);
double calcularIVA(double base);
double redondear(double valor, int decimales);
void   actualizarMatrizMes(int idxVenta);
void   obtenerFecha(char* buffer);

#endif
