#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Mascota {
    string nombre;     // Nombre del alumno: Moises Abinadi Farfan Gonzalez
    string especie;
    string raza;
    int edad;
    float peso;
};

bool mascotaRegistrada = false;

void registrarMascota(Mascota &m) {
    cout << "\n--- Registrar Mascota ---\n";
    cout << "Nombre: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, m.nombre);
    cout << "Especie (perro/gato/otro): ";
    getline(cin, m.especie);
    cout << "Raza: ";
    getline(cin, m.raza);
    cout << "Edad (años): ";
    cin >> m.edad;
    cout << "Peso (kg): ";
    cin >> m.peso;
    mascotaRegistrada = true;
    cout << "\n✓ Mascota registrada exitosamente.\n";
}

void mostrarMascota(const Mascota &m) {
    if (!mascotaRegistrada) {
        cout << "\n⚠ No hay ninguna mascota registrada.\n";
        return;
    }
    cout << "\n--- Información de la Mascota ---\n";
    cout << "Nombre  : " << m.nombre << "\n";
    cout << "Especie : " << m.especie << "\n";
    cout << "Raza    : " << m.raza << "\n";
    cout << "Edad    : " << m.edad << " años\n";
    cout << "Peso    : " << m.peso << " kg\n";
}

void calcularEdadEquivalente(const Mascota &m) {
    if (!mascotaRegistrada) {
        cout << "\n⚠ No hay ninguna mascota registrada.\n";
        return;
    }
    int edadHumana = m.edad * 7;
    cout << "\n--- Edad Equivalente en Años Humanos ---\n";
    cout << m.nombre << " tiene " << m.edad << " año(s).\n";
    cout << "Equivalente humano: " << edadHumana << " años.\n";
}

void clasificarPorPeso(const Mascota &m) {
    if (!mascotaRegistrada) {
        cout << "\n⚠ No hay ninguna mascota registrada.\n";
        return;
    }
    cout << "\n--- Clasificación por Peso ---\n";
    cout << m.nombre << " pesa " << m.peso << " kg: ";
    if (m.peso < 5)
        cout << "Mascota pequeña.\n";
    else if (m.peso <= 20)
        cout << "Mascota mediana.\n";
    else
        cout << "Mascota grande.\n";
}

void modificarDatos(Mascota &m) {
    if (!mascotaRegistrada) {
        cout << "\n⚠ No hay ninguna mascota registrada.\n";
        return;
    }
    int opcion;
    cout << "\n--- Modificar Datos ---\n";
    cout << "1. Nombre\n";
    cout << "2. Especie\n";
    cout << "3. Raza\n";
    cout << "4. Edad\n";
    cout << "5. Peso\n";
    cout << "Seleccione el dato a modificar: ";
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (opcion) {
        case 1:
            cout << "Nuevo nombre: ";
            getline(cin, m.nombre);
            break;
        case 2:
            cout << "Nueva especie: ";
            getline(cin, m.especie);
            break;
        case 3:
            cout << "Nueva raza: ";
            getline(cin, m.raza);
            break;
        case 4:
            cout << "Nueva edad: ";
            cin >> m.edad;
            break;
        case 5:
            cout << "Nuevo peso: ";
            cin >> m.peso;
            break;
        default:
            cout << "Opción no válida.\n";
            return;
    }
    cout << "✓ Dato modificado exitosamente.\n";
}

int main() {
    Mascota mascota;
    int opcion;

    do {
        cout << "\n===== REGISTRO DE MASCOTA =====\n";
        cout << "1. Registrar mascota\n";
        cout << "2. Mostrar mascota\n";
        cout << "3. Calcular edad equivalente\n";
        cout << "4. Clasificar por peso\n";
        cout << "5. Modificar datos\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarMascota(mascota);        break;
            case 2: mostrarMascota(mascota);           break;
            case 3: calcularEdadEquivalente(mascota);  break;
            case 4: clasificarPorPeso(mascota);        break;
            case 5: modificarDatos(mascota);           break;
            case 6: cout << "\nHasta luego.\n";        break;
            default: cout << "\nOpción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 6);

    return 0;
}