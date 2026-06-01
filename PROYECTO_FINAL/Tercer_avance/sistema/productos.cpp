// ═══════════════════════════════════════════════════════
//  productos.cpp
//  Modulo 1 - Gestion de Productos
//  Registrar, listar, buscar, modificar y eliminar
// ═══════════════════════════════════════════════════════

#include <iostream>
#include <cstring>
#include <cctype>
#include <stdexcept>
#include "estructuras.h"
#include "archivos.h"
#include "productos.h"

using namespace std;

// ───────────────────────────────────────────────────────
//  menuGestionProductos()
//  Muestra el sub-menu del Modulo 1
// ───────────────────────────────────────────────────────
void menuGestionProductos() {
    int opcion = 0;

    do {
        cout << "\n========================================" << endl;
        cout << "     MODULO 1 - GESTION DE PRODUCTOS    " << endl;
        cout << "========================================" << endl;
        cout << " 1. Registrar producto" << endl;
        cout << " 2. Listar productos" << endl;
        cout << " 3. Buscar por codigo" << endl;
        cout << " 4. Buscar por nombre" << endl;
        cout << " 5. Actualizar stock" << endl;
        cout << " 6. Modificar precio" << endl;
        cout << " 7. Eliminar producto" << endl;
        cout << " 0. Volver al menu principal" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";

        try {
            cin >> opcion;
            if (cin.fail()) throw invalid_argument("Entrada no numerica");
            if (opcion < 0 || opcion > 7) throw out_of_range("Opcion fuera de rango");
        } catch (const exception& e) {
            cout << "Error: " << e.what() << ". Ingrese 0-7." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
            continue;
        }

        int cod;
        int nuevoStock;
        double nuevoPrecio;
        char nombre[60];
        int idx;

        switch (opcion) {
            case 1: registrarProducto();    break;
            case 2: listarProductos();      break;
            case 3:
                cout << "Ingrese el codigo a buscar: ";
                try {
                    cin >> cod;
                    if (cin.fail()) throw invalid_argument("Codigo invalido");
                    idx = buscarPorCodigo(cod);
                    if (idx == -1) {
                        cout << "Producto no encontrado." << endl;
                    } else {
                        cout << "\n--- Producto encontrado ---" << endl;
                        cout << "Codigo   : " << productos[idx].codigo    << endl;
                        cout << "Nombre   : " << productos[idx].nombre    << endl;
                        cout << "Categoria: " << productos[idx].categoria << endl;
                        cout << "Precio   : Q" << productos[idx].precio   << endl;
                        cout << "Stock    : " << productos[idx].stock     << endl;
                    }
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                break;
            case 4:
                cout << "Ingrese el nombre a buscar: ";
                cin.ignore();
                cin.getline(nombre, 60);
                idx = buscarPorNombre(nombre);
                if (idx == -1) {
                    cout << "Producto no encontrado." << endl;
                } else {
                    cout << "\n--- Producto encontrado ---" << endl;
                    cout << "Codigo   : " << productos[idx].codigo    << endl;
                    cout << "Nombre   : " << productos[idx].nombre    << endl;
                    cout << "Categoria: " << productos[idx].categoria << endl;
                    cout << "Precio   : Q" << productos[idx].precio   << endl;
                    cout << "Stock    : " << productos[idx].stock     << endl;
                }
                break;
            case 5:
                cout << "Ingrese el codigo del producto: ";
                try {
                    cin >> cod;
                    if (cin.fail()) throw invalid_argument("Codigo invalido");
                    cout << "Ingrese el nuevo stock: ";
                    cin >> nuevoStock;
                    if (cin.fail()) throw invalid_argument("Stock invalido");
                    actualizarStock(cod, nuevoStock);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                break;
            case 6:
                cout << "Ingrese el codigo del producto: ";
                try {
                    cin >> cod;
                    if (cin.fail()) throw invalid_argument("Codigo invalido");
                    cout << "Ingrese el nuevo precio: Q";
                    cin >> nuevoPrecio;
                    if (cin.fail()) throw invalid_argument("Precio invalido");
                    modificarPrecio(cod, nuevoPrecio);
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                break;
            case 7:
                cout << "Ingrese el codigo del producto a eliminar: ";
                try {
                    cin >> cod;
                    if (cin.fail()) throw invalid_argument("Codigo invalido");
                    eliminarProducto(cod);
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
//  registrarProducto()
//  Pide datos al usuario y guarda un nuevo producto
// ───────────────────────────────────────────────────────
void registrarProducto() {
    try {
        if (totalProductos >= MAX_PRODUCTOS)
            throw runtime_error("Se alcanzo el limite maximo de productos");

        Producto nuevo;

        cout << "\n--- Registrar nuevo producto ---" << endl;

        // Codigo
        cout << "Codigo (numero entero): ";
        cin >> nuevo.codigo;
        if (cin.fail()) throw invalid_argument("El codigo debe ser un numero entero");

        // Verificar que el codigo no exista
        if (buscarPorCodigo(nuevo.codigo) != -1)
            throw runtime_error("Ya existe un producto con ese codigo");

        // Nombre
        cout << "Nombre: ";
        cin.ignore();
        cin.getline(nuevo.nombre, 60);
        if (strlen(nuevo.nombre) == 0)
            throw invalid_argument("El nombre no puede estar vacio");

        // Categoria
        cout << "Categoria (ej. Electronica, Ropa, Alimentos): ";
        cin.getline(nuevo.categoria, 30);
        if (strlen(nuevo.categoria) == 0)
            throw invalid_argument("La categoria no puede estar vacia");

        // Precio
        cout << "Precio (Q): ";
        cin >> nuevo.precio;
        if (cin.fail() || nuevo.precio <= 0)
            throw invalid_argument("El precio debe ser mayor a 0");

        // Stock
        cout << "Stock inicial: ";
        cin >> nuevo.stock;
        if (cin.fail() || nuevo.stock < 0)
            throw invalid_argument("El stock no puede ser negativo");

        // Valores iniciales
        nuevo.totalVendido = 0;
        nuevo.activo       = true;

        // Agregar al arreglo y guardar
        productos[totalProductos] = nuevo;
        totalProductos++;
        guardarProductos();

        cout << "\nProducto registrado exitosamente." << endl;

    } catch (const exception& e) {
        cout << "Error al registrar: " << e.what() << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

// ───────────────────────────────────────────────────────
//  listarProductos()
//  Muestra todos los productos activos en pantalla
// ───────────────────────────────────────────────────────
void listarProductos() {
    cout << "\n========================================" << endl;
    cout << "         LISTADO DE PRODUCTOS           " << endl;
    cout << "========================================" << endl;

    if (totalProductos == 0) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    int encontrados = 0;
    cout << "COD  | NOMBRE                       | CATEGORIA      | PRECIO   | STOCK" << endl;
    cout << "-----|------------------------------|----------------|----------|------" << endl;

    for (int i = 0; i < totalProductos; i++) {
        if (productos[i].activo) {
            cout.width(4);  cout << productos[i].codigo    << " | ";
            cout.width(28); cout << productos[i].nombre    << " | ";
            cout.width(14); cout << productos[i].categoria << " | ";
            cout << "Q";
            cout.width(7);  cout << productos[i].precio    << " | ";
            cout.width(5);  cout << productos[i].stock     << endl;
            encontrados++;
        }
    }

    if (encontrados == 0)
        cout << "No hay productos activos." << endl;
    else
        cout << "\nTotal de productos activos: " << encontrados << endl;
}

// ───────────────────────────────────────────────────────
//  buscarPorCodigo()
//  Busqueda directa por codigo
//  Retorna el indice en el arreglo o -1 si no existe
// ───────────────────────────────────────────────────────
int buscarPorCodigo(int cod) {
    for (int i = 0; i < totalProductos; i++) {
        if (productos[i].codigo == cod && productos[i].activo)
            return i;
    }
    return -1;
}

// ───────────────────────────────────────────────────────
//  buscarPorNombre()
//  Busqueda secuencial por nombre (sin importar mayusculas)
//  Retorna el indice del primer resultado o -1
// ───────────────────────────────────────────────────────
int buscarPorNombre(const char* nombre) {
    // Convertir busqueda a minusculas para comparar
    char busqueda[60];
    int i = 0;
    while (nombre[i] && i < 59) {
        busqueda[i] = tolower(nombre[i]);
        i++;
    }
    busqueda[i] = '\0';

    for (int j = 0; j < totalProductos; j++) {
        if (!productos[j].activo) continue;

        // Convertir nombre del producto a minusculas
        char nombreLower[60];
        int k = 0;
        while (productos[j].nombre[k] && k < 59) {
            nombreLower[k] = tolower(productos[j].nombre[k]);
            k++;
        }
        nombreLower[k] = '\0';

        // Busqueda secuencial: ver si busqueda esta contenida en el nombre
        if (strstr(nombreLower, busqueda) != NULL)
            return j;
    }
    return -1;
}

// ───────────────────────────────────────────────────────
//  actualizarStock()
//  Cambia el stock de un producto por su codigo
// ───────────────────────────────────────────────────────
void actualizarStock(int cod, int nuevoStock) {
    try {
        if (nuevoStock < 0)
            throw invalid_argument("El stock no puede ser negativo");

        int idx = buscarPorCodigo(cod);
        if (idx == -1)
            throw runtime_error("Producto no encontrado");

        productos[idx].stock = nuevoStock;
        guardarProductos();
        cout << "Stock actualizado correctamente." << endl;

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// ───────────────────────────────────────────────────────
//  modificarPrecio()
//  Cambia el precio de un producto por su codigo
// ───────────────────────────────────────────────────────
void modificarPrecio(int cod, double nuevoPrecio) {
    try {
        if (nuevoPrecio <= 0)
            throw invalid_argument("El precio debe ser mayor a 0");

        int idx = buscarPorCodigo(cod);
        if (idx == -1)
            throw runtime_error("Producto no encontrado");

        productos[idx].precio = nuevoPrecio;
        guardarProductos();
        cout << "Precio actualizado correctamente." << endl;

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// ───────────────────────────────────────────────────────
//  eliminarProducto()
//  Desactiva un producto (eliminacion logica)
//  El registro permanece en el archivo pero no se muestra
// ───────────────────────────────────────────────────────
void eliminarProducto(int cod) {
    try {
        int idx = buscarPorCodigo(cod);
        if (idx == -1)
            throw runtime_error("Producto no encontrado");

        char confirmacion;
        cout << "Esta seguro que desea eliminar '"
             << productos[idx].nombre << "'? (s/n): ";
        cin >> confirmacion;

        if (confirmacion == 's' || confirmacion == 'S') {
            productos[idx].activo = false;
            guardarProductos();
            cout << "Producto desactivado correctamente." << endl;
        } else {
            cout << "Operacion cancelada." << endl;
        }

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}
