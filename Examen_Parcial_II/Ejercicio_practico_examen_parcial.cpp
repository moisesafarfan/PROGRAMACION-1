#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

                      // Nombre del alumno: Moises Abinadi Farfan Gonzalez

double calcularSubtotal(int cantidad, double precioUnitario) {
    return cantidad * precioUnitario;
}

double calcularDescuento(double subtotal, int tipoPago) {
    double descuento = 0;
    if (subtotal >= 500) {
        descuento = subtotal * 0.05;
    }
    if (tipoPago == 1 && subtotal >= 300) {
        descuento += subtotal * 0.02;
    }
    return descuento;
}

double calcularTotal(double subtotal, double descuento) {
    return subtotal - descuento;
}

string obtenerTipoPago(int tipo) {
    switch (tipo) {
        case 1: return "Efectivo";
        case 2: return "Tarjeta";
        case 3: return "Transferencia";
        default: return "Desconocido";
    }
}


void mostrarMenu() {
    cout << "\n========================================" << endl;
    cout << "    SISTEMA DE CONTROL DE VENTAS" << endl;
    cout << "========================================" << endl;
    cout << "  1. Registrar una venta" << endl;
    cout << "  2. Mostrar todas las ventas" << endl;
    cout << "  3. Generar reporte general" << endl;
    cout << "  4. Buscar ventas por monto" << endl;
    cout << "  5. Salir del sistema" << endl;
    cout << "========================================" << endl;
    cout << "  Seleccione una opcion: ";
}

void registrarVenta() {
    string cliente, producto;
    int cantidad, tipoPago;
    double precioUnitario;

    cout << "\n--- REGISTRAR VENTA ---" << endl;
    cout << "Ingrese 0 en cantidad para cancelar." << endl;

    cout << "Nombre del cliente: ";
    cin.ignore();
    getline(cin, cliente);

    cout << "Nombre del producto: ";
    getline(cin, producto);

    while (true) {
        cout << "Cantidad: ";
        cin >> cantidad;
        if (cantidad == 0) {
            cout << "Registro cancelado." << endl;
            break;
        }
        if (cantidad > 0) break;
        cout << "[Error] La cantidad debe ser mayor que 0." << endl;
    }
    if (cantidad == 0) return;

    while (true) {
        cout << "Precio unitario (Q): ";
        cin >> precioUnitario;
        if (precioUnitario > 0) break;
        cout << "[Error] El precio debe ser mayor que 0." << endl;
    }

    while (true) {
        cout << "Tipo de pago (1=Efectivo, 2=Tarjeta, 3=Transferencia): ";
        cin >> tipoPago;
        if (tipoPago >= 1 && tipoPago <= 3) break;
        cout << "[Error] Tipo de pago invalido. Ingrese 1, 2 o 3." << endl;
        continue;
    }

    double subtotal  = calcularSubtotal(cantidad, precioUnitario);
    double descuento = calcularDescuento(subtotal, tipoPago);
    double total     = calcularTotal(subtotal, descuento);
    string pago      = obtenerTipoPago(tipoPago);

    ofstream archivo("ventas.txt", ios::app);
    if (!archivo) {
        cout << "[Error] No se pudo abrir el archivo de ventas." << endl;
        return;
    }
    archivo << fixed << setprecision(2);
    archivo << cliente << "," << producto << "," << cantidad << ","
            << precioUnitario << "," << subtotal << ","
            << descuento << "," << total << "," << pago << "\n";
    archivo.close();

    cout << "\n--- RESUMEN DE VENTA ---" << endl;
    cout << "Cliente   : " << cliente << endl;
    cout << "Producto  : " << producto << endl;
    cout << "Cantidad  : " << cantidad << endl;
    cout << "Precio    : Q" << fixed << setprecision(2) << precioUnitario << endl;
    cout << "Subtotal  : Q" << subtotal << endl;
    cout << "Descuento : Q" << descuento << endl;
    cout << "Total     : Q" << total << endl;
    cout << "Pago      : " << pago << endl;
    cout << "Venta registrada exitosamente." << endl;
}

void parsearLinea(const string& linea, string campos[], int& idx) {
    idx = 0;
    string temp = "";
    for (int i = 0; i < (int)linea.size(); i++) {
        if (linea[i] == ',' && idx < 7) {
            campos[idx++] = temp;
            temp = "";
        } else {
            temp += linea[i];
        }
    }
    campos[idx] = temp;
}

void mostrarTodasLasVentas() {
    ifstream archivo("ventas.txt");
    if (!archivo) {
        cout << "\n[Aviso] No hay ventas registradas aun." << endl;
        return;
    }

    string linea;
    int contador = 1;
    bool hayVentas = false;

    cout << "\n========================================" << endl;
    cout << "        TODAS LAS VENTAS" << endl;
    cout << "========================================" << endl;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        
        if (!linea.empty() && linea[linea.size() - 1] == '\r')
            linea.erase(linea.size() - 1);

        string campos[8];
        int idx = 0;
        parsearLinea(linea, campos, idx);

        if (idx != 7) continue;

        hayVentas = true;
        cout << "\nVenta #" << contador++ << endl;
        cout << "  Cliente   : " << campos[0] << endl;
        cout << "  Producto  : " << campos[1] << endl;
        cout << "  Cantidad  : " << campos[2] << endl;
        cout << "  Precio    : Q" << campos[3] << endl;
        cout << "  Subtotal  : Q" << campos[4] << endl;
        cout << "  Descuento : Q" << campos[5] << endl;
        cout << "  Total     : Q" << campos[6] << endl;
        cout << "  Pago      : " << campos[7] << endl;
    }

    if (!hayVentas) {
        cout << "No hay ventas registradas." << endl;
    }

    archivo.close();
}

void generarReporte() {
    ifstream archivo("ventas.txt");
    if (!archivo) {
        cout << "\n[Aviso] No hay ventas registradas aun." << endl;
        return;
    }

    string linea;
    int totalVentas = 0;
    double sumaTotal = 0;
    int efectivo = 0, tarjeta = 0, transferencia = 0;
    int conDescuento = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        if (!linea.empty() && linea[linea.size() - 1] == '\r')
            linea.erase(linea.size() - 1);

        string campos[8];
        int idx = 0;
        parsearLinea(linea, campos, idx);

        if (idx != 7) continue;
        if (campos[5].empty() || campos[6].empty()) continue;

        totalVentas++;
        double total     = stod(campos[6]);
        double descuento = stod(campos[5]);
        sumaTotal += total;

        if (campos[7] == "Efectivo")           efectivo++;
        else if (campos[7] == "Tarjeta")       tarjeta++;
        else if (campos[7] == "Transferencia") transferencia++;

        if (descuento > 0) conDescuento++;
    }
    archivo.close();

    if (totalVentas == 0) {
        cout << "\n[Aviso] No hay ventas validas en el archivo." << endl;
        return;
    }

    double promedio = sumaTotal / totalVentas;

    cout << "\n========================================" << endl;
    cout << "         REPORTE GENERAL" << endl;
    cout << "========================================" << endl;
    cout << fixed << setprecision(2);
    cout << "Total de ventas registradas : " << totalVentas << endl;
    cout << "Suma total vendida          : Q" << sumaTotal << endl;
    cout << "Promedio de venta           : Q" << promedio << endl;
    cout << "Ventas en Efectivo          : " << efectivo << endl;
    cout << "Ventas en Tarjeta           : " << tarjeta << endl;
    cout << "Ventas en Transferencia     : " << transferencia << endl;
    cout << "Ventas con descuento        : " << conDescuento << endl;
}

void buscarPorMonto() {
    double montoMinimo;
    cout << "\nMostrar ventas mayores o iguales a Q: ";
    cin >> montoMinimo;

    ifstream archivo("ventas.txt");
    if (!archivo) {
        cout << "\n[Aviso] No hay ventas registradas aun." << endl;
        return;
    }

    string linea;
    bool encontrado = false;
    int contador = 1;

    cout << "\n========================================" << endl;
    cout << "  Ventas >= Q" << fixed << setprecision(2) << montoMinimo << endl;
    cout << "========================================" << endl;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        if (!linea.empty() && linea[linea.size() - 1] == '\r')
            linea.erase(linea.size() - 1);

        string campos[8];
        int idx = 0;
        parsearLinea(linea, campos, idx);

        if (idx != 7 || campos[6].empty()) continue;

        double total = stod(campos[6]);

        if (total < montoMinimo) continue;

        encontrado = true;
        cout << "\nVenta #" << contador++ << endl;
        cout << "  Cliente   : " << campos[0] << endl;
        cout << "  Producto  : " << campos[1] << endl;
        cout << "  Total     : Q" << fixed << setprecision(2) << total << endl;
        cout << "  Pago      : " << campos[7] << endl;
    }

    if (!encontrado) {
        cout << "No se encontraron ventas con ese monto." << endl;
    }

    archivo.close();
}



int main() {
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarVenta();
                break;
            case 2:
                mostrarTodasLasVentas();
                break;
            case 3:
                generarReporte();
                break;
            case 4:
                buscarPorMonto();
                break;
            case 5:
                cout << "\nSaliendo del sistema. Hasta luego!" << endl;
                break;
            default:
                cout << "\n[Error] Opcion invalida. Intente de nuevo." << endl;
                continue;
        }

    } while (opcion != 5);

    return 0;
}