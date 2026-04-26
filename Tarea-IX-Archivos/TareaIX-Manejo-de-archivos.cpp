#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Nombre del archivo donde se guardan los datos
const string ARCHIVO = "usuarios.txt";

void mostrarMenu() {
    cout << "\n==============================" << endl;
    cout << "   GESTION DE USUARIOS" << endl;
    cout << "==============================" << endl;
    cout << "1. Guardar usuario" << endl;
    cout << "2. Mostrar usuarios" << endl;
    cout << "3. Salir" << endl;
    cout << "------------------------------" << endl;
    cout << "Seleccione una opcion: ";
}

void guardarUsuario() {                                // Alumno: Moisés Abinadí Farfan González
    // Variables para almacenar los datos del usuario
    string nombre;
    string posicion;
    int edad;

    cout << "\n--- Ingresar nuevo usuario ---" << endl;

    // Limpiar el buffer antes de usar getline
    cin.ignore();

    cout << "Nombre completo: ";
    getline(cin, nombre);

    cout << "Posicion en la empresa: ";
    getline(cin, posicion);

    cout << "Edad: ";
    cin >> edad;

    // Validar que la edad sea un valor positivo
    if (edad <= 0 || edad > 120) {
        cout << "Error: edad no valida." << endl;
        return;
    }

    ofstream archivo(ARCHIVO, ios::app);

    if (archivo.is_open()) {
        // Guardar los datos separados por coma
        archivo << nombre << "," << posicion << "," << edad << endl;
        archivo.close();
        cout << "\nUsuario guardado correctamente!" << endl;
    } else {
        cout << "Error: no se pudo abrir el archivo." << endl;
    }
}

void mostrarUsuarios() {
    ifstream archivo(ARCHIVO);
    string linea;
    int contador = 0;

    cout << "\n--- Lista de usuarios registrados ---" << endl;

    if (archivo.is_open()) {
        // Leer linea por linea
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            // Separar los campos usando la coma como delimitador
            int coma1 = linea.find(",");
            int coma2 = linea.find(",", coma1 + 1);

            string nombre   = linea.substr(0, coma1);
            string posicion = linea.substr(coma1 + 1, coma2 - coma1 - 1);
            string edad     = linea.substr(coma2 + 1);

            contador++;
            cout << "\nUsuario #" << contador << endl;
            cout << "  Nombre  : " << nombre << endl;
            cout << "  Posicion: " << posicion << endl;
            cout << "  Edad    : " << edad << " años" << endl;
        }

        archivo.close();

        // Verificar si habia algun registro
        if (contador == 0) {
            cout << "No hay usuarios registrados aun." << endl;
        } else {
            cout << "\nTotal de usuarios: " << contador << endl;
        }

    } else {
        cout << "No se encontro el archivo. Aun no hay usuarios guardados." << endl;
    }
}

int main() {
    int opcion = 0;

    cout << "Bienvenido al sistema de gestion de usuarios" << endl;

    // Ciclo principal del programa
    do {
        mostrarMenu();
        cin >> opcion;

        // Condicional para ejecutar la opcion elegida
        if (opcion == 1) {
            guardarUsuario();
        } else if (opcion == 2) {
            mostrarUsuarios();
        } else if (opcion == 3) {
            cout << "\nSaliendo del programa. Hasta luego!" << endl;
        } else {
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

    } while (opcion != 3);

    return 0;
}