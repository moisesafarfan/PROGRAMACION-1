#include <iostream>
using namespace std;

int main() {

    int opcion;
    int numero;
    int suma = 0;
    int contador = 0;
    int pares = 0;
    int impares = 0;
                                               //Moisés Abinadí Farfan González - 9941-25-86
    do {

        cout << "\n--- MENU ---\n";
        cout << "1. Registrar numeros\n";
        cout << "2. Mostrar estadisticas\n";
        cout << "3. Clasificar numeros\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;


        cout << "Nombre del estudiante: Moisés Abinadí Farfan González.\n";

        switch(opcion) {

            case 1:

                while(true) {

                    cout << "Ingrese un numero (0 para terminar): ";
                    cin >> numero;

                    if(numero == 0) {
                        break;
                    }

                    if(numero < 0) {
                        cout << "Error: no se permiten numeros negativos\n";
                        continue;
                    }

                    suma = suma + numero;
                    contador++;

                    if(numero % 2 == 0) {
                        pares++;
                    }
                    else {
                        impares++;
                    }

                }

            break;

            case 2:

                if(contador == 0) {
                    cout << "No hay datos registrados\n";
                }
                else {

                    double promedio = (double)suma / contador;

                    cout << "Total de numeros: " << contador << endl;
                    cout << "Suma total: " << suma << endl;
                    cout << "Promedio: " << promedio << endl;
                }

            break;

            case 3:

                if(contador == 0) {
                    cout << "No hay numeros para clasificar\n";
                }
                else {

                    if(pares >= 0 && impares >= 0) {

                        cout << "Numeros pares: " << pares << endl;
                        cout << "Numeros impares: " << impares << endl;

                    }

                }

            break;

            case 4:

                cout << "Saliendo del programa...\n";

            break;

            default:

                cout << "Opcion invalida\n";

        }

    } while(opcion != 4);

    return 0;

}