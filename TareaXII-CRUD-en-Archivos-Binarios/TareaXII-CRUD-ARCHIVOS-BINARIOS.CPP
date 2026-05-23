#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

struct Producto {
    int codigo;
    char nombre[50];                                     //Nombre del alumno: Moisés Abinadí Farfan González
    float precio;
    int stock;
    bool activo;
};

const char ARCHIVO[] = "productos.dat";
const float IVA = 0.12;

// Prototipos
void menuPrincipal();
void menuProductos();
void registrarProducto();
void listarProductos();
void buscarPorCodigo();
void buscarPorNombre();
void modificarPrecio();
void actualizarStock();
void eliminarProducto();
void procesoVenta();
bool existeCodigo(int codigo);

int main() {
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int opcion;

    do {
        cout << "\n===== SISTEMA DE VENTAS E INVENTARIO =====\n";
        cout << "1. Gestion de productos\n";
        cout << "2. Proceso de venta\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                menuProductos();
                break;
            case 2:
                procesoVenta();
                break;
            case 3:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 3);
}

void menuProductos() {
    int opcion;

    do {
        cout << "\n===== GESTION DE PRODUCTOS =====\n";
        cout << "1. Registrar producto\n";                  //Nombre del alumno: Moisés Abinadí Farfan González
        cout << "2. Listar productos activos\n";
        cout << "3. Buscar producto por codigo\n";
        cout << "4. Buscar producto por nombre\n";
        cout << "5. Modificar precio\n";
        cout << "6. Actualizar stock\n";
        cout << "7. Eliminar / desactivar producto\n";
        cout << "8. Regresar al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarProducto(); break;
            case 2: listarProductos(); break;
            case 3: buscarPorCodigo(); break;
            case 4: buscarPorNombre(); break;
            case 5: modificarPrecio(); break;
            case 6: actualizarStock(); break;
            case 7: eliminarProducto(); break;
            case 8: break;
            default: cout << "Opcion invalida.\n";
        }

    } while (opcion != 8);
}

bool existeCodigo(int codigo) {
    Producto p;
    ifstream archivo(ARCHIVO, ios::binary);

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void registrarProducto() {
    Producto p;

    cout << "\nIngrese codigo del producto: ";
    cin >> p.codigo;

    if (existeCodigo(p.codigo)) {
        cout << "Ya existe un producto activo con ese codigo.\n";
        return;
    }

    cin.ignore();
    cout << "Ingrese nombre del producto: ";
    cin.getline(p.nombre, 50);

    cout << "Ingrese precio: ";
    cin >> p.precio;

    cout << "Ingrese stock: ";
    cin >> p.stock;

    if (p.precio <= 0 || p.stock < 0) {
        cout << "Datos invalidos. Precio debe ser mayor a 0 y stock no puede ser negativo.\n";
        return;
    }

    p.activo = true;

    ofstream archivo(ARCHIVO, ios::binary | ios::app);
    archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));
    archivo.close();

    cout << "Producto registrado correctamente.\n";
}

void listarProductos() {
    Producto p;
    ifstream archivo(ARCHIVO, ios::binary);

    if (!archivo) {
        cout << "No hay productos registrados.\n";
        return;
    }

    cout << "\n===== PRODUCTOS ACTIVOS =====\n";

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.activo) {
            cout << "Codigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << fixed << setprecision(2) << p.precio << endl;
            cout << "Stock: " << p.stock << endl;
            cout << "--------------------------\n";
        }
    }

    archivo.close();
}

void buscarPorCodigo() {
    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo a buscar: ";
    cin >> codigo;

    ifstream archivo(ARCHIVO, ios::binary);

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            cout << "\nProducto encontrado:\n";
            cout << "Codigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << fixed << setprecision(2) << p.precio << endl;
            cout << "Stock: " << p.stock << endl;
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

void buscarPorNombre() {
    Producto p;
    char nombreBuscar[50];
    bool encontrado = false;

    cin.ignore();
    cout << "\nIngrese nombre a buscar: ";
    cin.getline(nombreBuscar, 50);

    ifstream archivo(ARCHIVO, ios::binary);

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (strcmp(p.nombre, nombreBuscar) == 0 && p.activo) {
            cout << "\nProducto encontrado:\n";
            cout << "Codigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << fixed << setprecision(2) << p.precio << endl;
            cout << "Stock: " << p.stock << endl;
            encontrado = true;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

void modificarPrecio() {
    Producto p;
    int codigo;
    float nuevoPrecio;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto: ";
    cin >> codigo;

    fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            cout << "Precio actual: Q" << p.precio << endl;
            cout << "Ingrese nuevo precio: ";
            cin >> nuevoPrecio;

            if (nuevoPrecio <= 0) {
                cout << "Precio invalido.\n";
                archivo.close();
                return;
            }

            p.precio = nuevoPrecio;

            archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));

            cout << "Precio actualizado correctamente.\n";
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

void actualizarStock() {
    Producto p;
    int codigo, nuevoStock;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto: ";
    cin >> codigo;

    fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            cout << "Stock actual: " << p.stock << endl;
            cout << "Ingrese nuevo stock: ";
            cin >> nuevoStock;

            if (nuevoStock < 0) {
                cout << "Stock invalido.\n";
                archivo.close();
                return;
            }

            p.stock = nuevoStock;

            archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));

            cout << "Stock actualizado correctamente.\n";
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

void eliminarProducto() {
    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto a desactivar: ";
    cin >> codigo;

    fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            p.activo = false;

            archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));

            cout << "Producto desactivado correctamente.\n";
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

void procesoVenta() {
    Producto p;
    int codigo, cantidad;
    bool encontrado = false;

    cout << "\n===== PROCESO DE VENTA =====\n";
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    fstream archivo(ARCHIVO, ios::binary | ios::in | ios::out);

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            encontrado = true;

            cout << "\nProducto: " << p.nombre << endl;
            cout << "Precio: Q" << fixed << setprecision(2) << p.precio << endl;
            cout << "Stock disponible: " << p.stock << endl;

            cout << "Ingrese cantidad a vender: ";
            cin >> cantidad;

            if (cantidad <= 0) {
                cout << "Cantidad invalida.\n";
                archivo.close();
                return;
            }

            if (cantidad > p.stock) {
                cout << "Stock insuficiente.\n";
                archivo.close();
                return;
            }

            float subtotal = p.precio * cantidad;
            float iva = subtotal * IVA;
            float total = subtotal + iva;

            p.stock -= cantidad;

            archivo.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
            archivo.write(reinterpret_cast<char*>(&p), sizeof(Producto));

            cout << "\n===== FACTURA BASICA =====\n";
            cout << "Producto: " << p.nombre << endl;
            cout << "Cantidad: " << cantidad << endl;
            cout << "Subtotal: Q" << subtotal << endl;
            cout << "IVA 12%: Q" << iva << endl;
            cout << "Total: Q" << total << endl;
            cout << "Stock actualizado: " << p.stock << endl;

            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}