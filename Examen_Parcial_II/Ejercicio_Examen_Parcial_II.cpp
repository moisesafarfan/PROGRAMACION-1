#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const string ARCHIVO = "ventas.txt";   //Alumno: Moisés Abinadí Farfan González

void mostrarMenu() {
    cout << "\n========================================" << endl;
    cout << "     SISTEMA DE CONTROL DE VENTAS" << endl;
    cout << "========================================" << endl;
    cout << "1. Registrar venta" << endl;
    cout << "2. Mostrar todas las ventas" << endl;
    cout << "3. Generar reporte (total vendido)" << endl;
    cout << "4. Buscar venta por producto" << endl;
    cout << "5. Salir" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Seleccione una opcion: ";
}

void registrarVenta() {
    string producto;
    string vendedor;
    int cantidad;
    double precioUnitario;

    cout << "\n--- Registrar nueva venta ---" << endl;

    cin.ignore();

    cout << "Nombre del producto : ";
    getline(cin, producto);

    cout << "Nombre del vendedor : ";
    getline(cin, vendedor);

    cout << "Cantidad vendida    : ";
    cin >> cantidad;

    cout << "Precio unitario (Q) : ";
    cin >> precioUnitario;

    // Validaciones basicas
    if (cantidad <= 0 || precioUnitario <= 0) {
        cout << "Error: cantidad y precio deben ser mayores a cero." << endl;
        return;
    }

    double total = cantidad * precioUnitario;

    // Guardar en archivo
    ofstream archivo(ARCHIVO, ios::app);

    if (archivo.is_open()) {
        archivo << producto << "," << vendedor << ","
                << cantidad << "," << precioUnitario << ","
                << total << endl;
        archivo.close();

        cout << "\nVenta registrada exitosamente!" << endl;
        cout << "Total de la venta: Q" << fixed << setprecision(2) << total << endl;
    } else {
        cout << "Error: no se pudo abrir el archivo." << endl;
    }
}

void mostrarVentas() {
    ifstream archivo(ARCHIVO);
    string linea;
    int contador = 0;

    cout << "\n--- Lista de ventas registradas ---" << endl;
    cout << left
         << setw(20) << "Producto"
         << setw(18) << "Vendedor"
         << setw(10) << "Cantidad"
         << setw(15) << "Precio Unit."
         << setw(12) << "Total"
         << endl;
    cout << string(75, '-') << endl;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            // Separar campos por coma
            int c1 = linea.find(",");
            int c2 = linea.find(",", c1 + 1);
            int c3 = linea.find(",", c2 + 1);
            int c4 = linea.find(",", c3 + 1);

            string producto  = linea.substr(0, c1);
            string vendedor  = linea.substr(c1 + 1, c2 - c1 - 1);
            string cantidad  = linea.substr(c2 + 1, c3 - c2 - 1);
            string precio    = linea.substr(c3 + 1, c4 - c3 - 1);
            string total     = linea.substr(c4 + 1);

            cout << left
                 << setw(20) << producto
                 << setw(18) << vendedor
                 << setw(10) << cantidad
                 << setw(15) << ("Q" + precio)
                 << setw(12) << ("Q" + total)
                 << endl;

            contador++;
        }

        archivo.close();

        if (contador == 0) {
            cout << "No hay ventas registradas aun." << endl;
        } else {
            cout << string(75, '-') << endl;
            cout << "Total de registros: " << contador << endl;
        }

    } else {
        cout << "No se encontro el archivo. Registre una venta primero." << endl;
    }
}

void generarReporte() {
    ifstream archivo(ARCHIVO);
    string linea;
    double totalGeneral = 0.0;
    int totalVentas = 0;
    double ventaMayor = 0.0;
    string productoEstrella = "";

    cout << "\n--- Reporte General de Ventas ---" << endl;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            // Extraer el total (ultimo campo)
            int c1 = linea.find(",");
            int c4 = linea.rfind(",");

            string producto = linea.substr(0, c1);
            double total    = stod(linea.substr(c4 + 1));

            totalGeneral += total;
            totalVentas++;

            // Detectar la venta mas alta
            if (total > ventaMayor) {
                ventaMayor = total;
                productoEstrella = producto;
            }
        }

        archivo.close();

        if (totalVentas == 0) {
            cout << "No hay ventas registradas para generar reporte." << endl;
        } else {
            cout << "Numero de ventas registradas : " << totalVentas << endl;
            cout << "Total general vendido        : Q"
                 << fixed << setprecision(2) << totalGeneral << endl;
            cout << "Promedio por venta           : Q"
                 << fixed << setprecision(2) << (totalGeneral / totalVentas) << endl;
            cout << "Venta mas alta               : Q"
                 << fixed << setprecision(2) << ventaMayor
                 << " (" << productoEstrella << ")" << endl;
        }

    } else {
        cout << "No se encontro el archivo. Registre una venta primero." << endl;
    }
}

void buscarVenta() {
    string busqueda;
    string linea;
    int encontrados = 0;

    cin.ignore();
    cout << "\nIngrese el nombre del producto a buscar: ";
    getline(cin, busqueda);

    ifstream archivo(ARCHIVO);

    cout << "\n--- Resultados de busqueda: \"" << busqueda << "\" ---" << endl;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            int c1 = linea.find(",");
            string producto = linea.substr(0, c1);

            // Busqueda sin distinguir mayusculas (comparacion simple)
            bool coincide = true;
            if (producto.size() < busqueda.size()) {
                coincide = false;
            } else {
                // Verificar si busqueda esta contenida en producto
                coincide = (producto.find(busqueda) != string::npos);
            }

            if (coincide) {
                int c2 = linea.find(",", c1 + 1);
                int c3 = linea.find(",", c2 + 1);
                int c4 = linea.find(",", c3 + 1);

                string vendedor = linea.substr(c1 + 1, c2 - c1 - 1);
                string cantidad = linea.substr(c2 + 1, c3 - c2 - 1);
                string precio   = linea.substr(c3 + 1, c4 - c3 - 1);
                string total    = linea.substr(c4 + 1);

                encontrados++;
                cout << "\nRegistro #" << encontrados << endl;
                cout << "  Producto  : " << producto << endl;
                cout << "  Vendedor  : " << vendedor << endl;
                cout << "  Cantidad  : " << cantidad << endl;
                cout << "  Precio    : Q" << precio << endl;
                cout << "  Total     : Q" << total << endl;
            }
        }

        archivo.close();

        if (encontrados == 0) {
            cout << "No se encontraron ventas con ese producto." << endl;
        } else {
            cout << "\nTotal de coincidencias: " << encontrados << endl;
        }

    } else {
        cout << "No se encontro el archivo. Registre una venta primero." << endl;
    }
}

int main() {
    int opcion = 0;

    cout << "Bienvenido al Sistema de Control de Ventas" << endl;

    do {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {
            registrarVenta();
        } else if (opcion == 2) {
            mostrarVentas();
        } else if (opcion == 3) {
            generarReporte();
        } else if (opcion == 4) {
            buscarVenta();
        } else if (opcion == 5) {
            cout << "\nCerrando sistema. Hasta luego!" << endl;
        } else {
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

    } while (opcion != 5);

    return 0;
}