#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

double calcularPromedio(const vector<double>& notas) {
    double suma = 0.0;
    for (int i = 0; i < (int)notas.size(); i++) {
        suma += notas[i];
    }
    return suma / notas.size();
}
                                                 //Nombre del estudiante: Moisés Abinadí Farfan González
string determinarEstado(double promedio) {
    if (promedio >= 61) {
        return "Aprobado";
    } else {
        return "Reprobado";
    }
}

string determinarCategoria(double promedio) {
    if (promedio >= 85 && promedio <= 100) {
        return "Excelente";
    } else if (promedio >= 70 && promedio <= 84) {
        return "Bueno";
    } else if (promedio >= 61 && promedio <= 69) {
        return "Regular";
    } else {
        return "Deficiente";
    }
}

void mostrarResultado(const string& nombre, const string& curso,
                      double promedio, const string& estado,
                      const string& categoria) {
    cout << endl;
    cout << "----- RESULTADO FINAL -----" << endl;
    cout << "Nombre    : " << nombre    << endl;
    cout << "Curso     : " << curso     << endl;
    cout << fixed << setprecision(2);
    cout << "Promedio  : " << promedio  << endl;
    cout << "Estado    : " << estado    << endl;
    cout << "Categoria : " << categoria << endl;
    cout << "---------------------------" << endl;
}

vector<double> ingresarNotas(int cantidad) {
    vector<double> notas;
    double nota;

    cout << endl;
    for (int i = 1; i <= cantidad; i++) {
        cout << "Ingrese la nota " << i << ": ";
        cin >> nota;

        while (nota < 0 || nota > 100) {
            cout << "  [!] Nota invalida. Debe estar entre 0 y 100." << endl;
            cout << "Ingrese la nota " << i << ": ";
            cin >> nota;
        }

        notas.push_back(nota);
    }

    return notas;
}

int main() {
    string nombre, curso;
    int cantidad;

    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, nombre);

    cout << "Ingrese el curso: ";
    getline(cin, curso);

    cout << "Ingrese la cantidad de notas: ";
    cin >> cantidad;

    while (cantidad <= 0) {
        cout << "  [!] La cantidad de notas debe ser mayor a 0." << endl;
        cout << "Ingrese la cantidad de notas: ";
        cin >> cantidad;
    }

    vector<double> notas = ingresarNotas(cantidad);

    double  promedio  = calcularPromedio(notas);
    string  estado    = determinarEstado(promedio);
    string  categoria = determinarCategoria(promedio);

    mostrarResultado(nombre, curso, promedio, estado, categoria);

    return 0;
}