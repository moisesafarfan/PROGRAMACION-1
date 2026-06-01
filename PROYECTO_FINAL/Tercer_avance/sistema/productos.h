#ifndef PRODUCTOS_H
#define PRODUCTOS_H

// ═══════════════════════════════════════════════════════
//  productos.h
//  Prototipos del Modulo 1 - Gestion de Productos
// ═══════════════════════════════════════════════════════

void menuGestionProductos();
void registrarProducto();
void listarProductos();
int  buscarPorCodigo(int cod);
int  buscarPorNombre(const char* nombre);
void actualizarStock(int cod, int nuevoStock);
void modificarPrecio(int cod, double nuevoPrecio);
void eliminarProducto(int cod);

#endif
