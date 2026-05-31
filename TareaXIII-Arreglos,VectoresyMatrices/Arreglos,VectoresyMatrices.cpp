#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

const string NOMBRE_ESTUDIANTE = "Moises Farfan";

void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void encabezado() {
    cout << "========================================\n";
    cout << "Estudiante: " << NOMBRE_ESTUDIANTE << endl;
    cout << "Tarea: Arreglos, vectores y matrices\n";
    cout << "========================================\n\n";
}

// Ejercicio 1
void analisisTemperaturas() {
    encabezado();

    float temperaturas[7];
    float suma = 0;

    cout << "Ejercicio 1: Analisis de temperaturas\n\n";

    for (int i = 0; i < 7; i++) {
        cout << "Ingrese la temperatura del dia " << i + 1 << ": ";
        cin >> temperaturas[i];
        suma += temperaturas[i];
    }

    float alta = temperaturas[0];
    float baja = temperaturas[0];

    for (int i = 1; i < 7; i++) {
        if (temperaturas[i] > alta) {
            alta = temperaturas[i];
        }

        if (temperaturas[i] < baja) {
            baja = temperaturas[i];
        }
    }

    float promedio = suma / 7;
    int arribaPromedio = 0;
    int debajoPromedio = 0;

    for (int i = 0; i < 7; i++) {
        if (temperaturas[i] > promedio) {
            arribaPromedio++;
        } else if (temperaturas[i] < promedio) {
            debajoPromedio++;
        }
    }

    cout << fixed << setprecision(2);

    cout << "\nTemperaturas ingresadas:\n";
    for (int i = 0; i < 7; i++) {
        cout << "Dia " << i + 1 << ": " << temperaturas[i] << endl;
    }

    cout << "\nTemperatura mas alta: " << alta << endl;
    cout << "Temperatura mas baja: " << baja << endl;
    cout << "Promedio semanal: " << promedio << endl;
    cout << "Dias arriba del promedio: " << arribaPromedio << endl;
    cout << "Dias debajo del promedio: " << debajoPromedio << endl;
}

// Ejercicio 2
void detectorRepetidos() {
    encabezado();

    int numeros[10];
    bool existenRepetidos = false;

    cout << "Ejercicio 2: Detector de numeros repetidos\n\n";

    cout << "Ingrese 10 numeros enteros:\n";
    for (int i = 0; i < 10; i++) {
        cout << "Numero " << i + 1 << ": ";
        cin >> numeros[i];
    }

    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (numeros[i] == numeros[j]) {
                existenRepetidos = true;
            }
        }
    }

    if (existenRepetidos) {
        cout << "\nExisten numeros repetidos.\n";
        cout << "Numeros repetidos encontrados:\n";

        for (int i = 0; i < 10; i++) {
            bool yaMostrado = false;
            bool seRepite = false;

            for (int k = 0; k < i; k++) {
                if (numeros[k] == numeros[i]) {
                    yaMostrado = true;
                }
            }

            for (int j = i + 1; j < 10; j++) {
                if (numeros[i] == numeros[j]) {
                    seRepite = true;
                }
            }

            if (seRepite && !yaMostrado) {
                cout << numeros[i] << endl;
            }
        }
    } else {
        cout << "\nNo existen numeros repetidos.\n";
    }
}

// Ejercicio 3
void listaPalabras() {
    encabezado();

    vector<string> palabras;
    string palabra;

    cout << "Ejercicio 3: Lista dinamica de palabras\n\n";
    cout << "Ingrese palabras. Escriba 'fin' para terminar.\n\n";

    while (true) {
        cout << "Palabra: ";
        cin >> palabra;

        if (palabra == "fin") {
            break;
        }

        palabras.push_back(palabra);
    }

    if (palabras.empty()) {
        cout << "\nNo se ingresaron palabras.\n";
        return;
    }

    string palabraLarga = palabras[0];
    string palabraCorta = palabras[0];
    int masDeCinco = 0;

    for (int i = 0; i < palabras.size(); i++) {
        if (palabras[i].length() > palabraLarga.length()) {
            palabraLarga = palabras[i];
        }

        if (palabras[i].length() < palabraCorta.length()) {
            palabraCorta = palabras[i];
        }

        if (palabras[i].length() > 5) {
            masDeCinco++;
        }
    }

    cout << "\nCantidad total de palabras ingresadas: " << palabras.size() << endl;
    cout << "Palabra mas larga: " << palabraLarga << endl;
    cout << "Palabra mas corta: " << palabraCorta << endl;
    cout << "Palabras con mas de 5 letras: " << masDeCinco << endl;

    cout << "\nPalabras en orden inverso:\n";
    for (int i = palabras.size() - 1; i >= 0; i--) {
        cout << palabras[i] << endl;
    }
}

// Ejercicio 4
void eliminacionLogica() {
    encabezado();

    vector<int> original;
    vector<int> filtrado;
    int numero;

    cout << "Ejercicio 4: Eliminacion logica de datos\n\n";
    cout << "Ingrese numeros enteros positivos. Escriba 0 para terminar.\n\n";

    while (true) {
        cout << "Numero: ";
        cin >> numero;

        if (numero == 0) {
            break;
        }

        if (numero < 0) {
            cout << "Debe ingresar un numero positivo.\n";
        } else {
            original.push_back(numero);
        }
    }

    if (original.empty()) {
        cout << "\nNo se ingresaron numeros.\n";
        return;
    }

    cout << "\nVector original:\n";
    for (int i = 0; i < original.size(); i++) {
        cout << original[i] << " ";
    }

    int eliminar;
    cout << "\n\nNumero a eliminar: ";
    cin >> eliminar;

    for (int i = 0; i < original.size(); i++) {
        if (original[i] != eliminar) {
            filtrado.push_back(original[i]);
        }
    }

    cout << "\nVector resultante:\n";

    if (filtrado.empty()) {
        cout << "El vector quedo vacio.";
    } else {
        for (int i = 0; i < filtrado.size(); i++) {
            cout << filtrado[i] << " ";
        }
    }

    cout << endl;
}

// Ejercicio 5
void matrizNotas() {
    encabezado();

    float notas[4][3];

    cout << "Ejercicio 5: Matriz de notas\n\n";

    for (int i = 0; i < 4; i++) {
        cout << "Estudiante " << i + 1 << endl;

        for (int j = 0; j < 3; j++) {
            cout << "Ingrese nota de evaluacion " << j + 1 << ": ";
            cin >> notas[i][j];
        }

        cout << endl;
    }

    cout << fixed << setprecision(2);

    cout << "\nMatriz completa de notas:\n\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(8) << notas[i][j];
        }
        cout << endl;
    }

    float promediosEstudiantes[4];

    cout << "\nPromedio de cada estudiante:\n";
    for (int i = 0; i < 4; i++) {
        float suma = 0;

        for (int j = 0; j < 3; j++) {
            suma += notas[i][j];
        }

        promediosEstudiantes[i] = suma / 3;
        cout << "Estudiante " << i + 1 << ": " << promediosEstudiantes[i] << endl;
    }

    float promediosEvaluaciones[3];

    cout << "\nPromedio de cada evaluacion:\n";
    for (int j = 0; j < 3; j++) {
        float suma = 0;

        for (int i = 0; i < 4; i++) {
            suma += notas[i][j];
        }

        promediosEvaluaciones[j] = suma / 4;
        cout << "Evaluacion " << j + 1 << ": " << promediosEvaluaciones[j] << endl;
    }

    int mejorEstudiante = 0;
    for (int i = 1; i < 4; i++) {
        if (promediosEstudiantes[i] > promediosEstudiantes[mejorEstudiante]) {
            mejorEstudiante = i;
        }
    }

    int evaluacionMasBaja = 0;
    for (int j = 1; j < 3; j++) {
        if (promediosEvaluaciones[j] < promediosEvaluaciones[evaluacionMasBaja]) {
            evaluacionMasBaja = j;
        }
    }

    cout << "\nEstudiante con mejor promedio: Estudiante " 
         << mejorEstudiante + 1 
         << " con promedio de " 
         << promediosEstudiantes[mejorEstudiante] << endl;

    cout << "Evaluacion con promedio mas bajo: Evaluacion " 
         << evaluacionMasBaja + 1 
         << " con promedio de " 
         << promediosEvaluaciones[evaluacionMasBaja] << endl;
}

// Ejercicio 6
void busquedaMatriz() {
    encabezado();

    int matriz[3][3];
    int buscado;
    bool encontrado = false;

    cout << "Ejercicio 6: Busqueda de un valor en matriz\n\n";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Ingrese valor para fila " << i << ", columna " << j << ": ";
            cin >> matriz[i][j];
        }
    }

    cout << "\nMatriz ingresada:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nNumero a buscar: ";
    cin >> buscado;

    cout << "\n";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matriz[i][j] == buscado) {
                if (!encontrado) {
                    cout << "El numero aparece en:\n";
                }

                cout << "Fila " << i << ", columna " << j << endl;
                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        cout << "El numero no existe en la matriz.\n";
    }
}

// Ejercicio 7
void tableroPosiciones() {
    encabezado();

    int tablero[5][5] = {0};
    int fila, columna;

    cout << "Ejercicio 7: Tablero de posiciones\n\n";

    while (true) {
        cout << "Ingrese fila entre 0 y 4: ";
        cin >> fila;

        cout << "Ingrese columna entre 0 y 4: ";
        cin >> columna;

        if (fila >= 0 && fila < 5 && columna >= 0 && columna < 5) {
            break;
        } else {
            cout << "\nPosicion fuera de rango. Intente nuevamente.\n\n";
        }
    }

    tablero[fila][columna] = 1;

    cout << "\nTablero:\n\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int opcion;

    do {
        encabezado();

        cout << "MENU PRINCIPAL\n";
        cout << "1. Ejercicio 1 - Analisis de temperaturas\n";
        cout << "2. Ejercicio 2 - Detector de numeros repetidos\n";
        cout << "3. Ejercicio 3 - Lista dinamica de palabras\n";
        cout << "4. Ejercicio 4 - Eliminacion logica de datos\n";
        cout << "5. Ejercicio 5 - Matriz de notas\n";
        cout << "6. Ejercicio 6 - Busqueda en matriz\n";
        cout << "7. Ejercicio 7 - Tablero de posiciones\n";
        cout << "0. Salir\n\n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cout << "\n";

        switch (opcion) {
            case 1:
                analisisTemperaturas();
                pausar();
                break;

            case 2:
                detectorRepetidos();
                pausar();
                break;

            case 3:
                listaPalabras();
                pausar();
                break;

            case 4:
                eliminacionLogica();
                pausar();
                break;

            case 5:
                matrizNotas();
                pausar();
                break;

            case 6:
                busquedaMatriz();
                pausar();
                break;

            case 7:
                tableroPosiciones();
                pausar();
                break;

            case 0:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
                pausar();
                break;
        }

        cout << "\n\n";

    } while (opcion != 0);

    return 0;
}