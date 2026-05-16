#include <iostream>
#include <fstream>

using namespace std;

// ===============================
// STRUCT
// ===============================
struct Producto {
    int codigo;
    char nombre[40];
    char categoria[30];
    int stock;
    float precio;
    bool activo;
};

// ===============================
// DECLARACION DE FUNCIONES
// ===============================
void menu();
void registrarProducto();
void listarProductos();
void mostrarEncabezado();
void pausarSistema();

// ===============================
// MAIN
// ===============================
int main() {
    menu();
    return 0;                           //Nombre del alumno: Moisés Abinadí Farfan González
}

// ===============================
// ENCABEZADO
// ===============================
void mostrarEncabezado() {
    cout << "\n===============================";
    cout << "\n SISTEMA DE VENTAS E INVENTARIO";
    cout << "\n===============================\n";
}

// ===============================
// PAUSAR SISTEMA
// ===============================
void pausarSistema() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// ===============================
// MENU
// ===============================
void menu() {
    int opcion;
    do {
        mostrarEncabezado();
        cout << "\n1. Registrar producto";
        cout << "\n2. Listar productos";
        cout << "\n3. Salir";
        cout << "\n\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarProducto();
                break;
            case 2:
                listarProductos();
                break;
            case 3:
                cout << "\nSistema cerrado. Hasta luego.\n";
                break;
            default:
                cout << "\nOpcion invalida. Intente de nuevo.\n";
                pausarSistema();
        }
    } while (opcion != 3);
}

// ===============================
// REGISTRAR PRODUCTO
// ===============================
void registrarProducto() {
    Producto p;
    ofstream archivo("productos.dat", ios::binary | ios::app);

    if (!archivo) {
        cout << "\nError: No se pudo abrir el archivo.\n";
        return;
    }

    cout << "\n======== REGISTRAR PRODUCTO ========";
    cout << "\nCodigo: ";
    cin >> p.codigo;
    cin.ignore();

    cout << "Nombre: ";
    cin.getline(p.nombre, 40);

    cout << "Categoria: ";
    cin.getline(p.categoria, 30);

    cout << "Stock: ";
    cin >> p.stock;

    cout << "Precio: ";
    cin >> p.precio;

    // El campo activo siempre se guarda como true
    p.activo = true;

    // Escritura binaria
    archivo.write((char*)&p, sizeof(p));
    archivo.close();

    cout << "\nProducto registrado correctamente.\n";
    pausarSistema();
}

// ===============================
// LISTAR PRODUCTOS
// ===============================
void listarProductos() {
    Producto p;
    ifstream archivo("productos.dat", ios::binary);

    if (!archivo) {
        cout << "\nNo hay productos almacenados.\n";
        pausarSistema();
        return;
    }

    cout << "\n========== LISTADO DE PRODUCTOS ==========\n";

    bool hayProductos = false;

    while (archivo.read((char*)&p, sizeof(p))) {
        hayProductos = true;
        cout << "\n------------------------------------------";
        cout << "\nCodigo   : " << p.codigo;
        cout << "\nNombre   : " << p.nombre;
        cout << "\nCategoria: " << p.categoria;
        cout << "\nStock    : " << p.stock << " unidades";
        cout << "\nPrecio   : Q" << p.precio;
        cout << "\n------------------------------------------";
    }

    if (!hayProductos) {
        cout << "\nNo hay productos registrados aun.\n";
    }

    archivo.close();
    pausarSistema();
}