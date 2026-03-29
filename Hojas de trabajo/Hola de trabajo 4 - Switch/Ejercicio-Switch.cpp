#include <iostream>
using namespace std;

int main() {

    int opcion;

    do {
        cout << "  1. Números del 1 al 5 " << endl;
        cout << "  2. Números pares del 2 al 10" << endl;
        cout << "  3. Positivo o negativo" << endl;
        cout << "  4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin  >> opcion;

        switch (opcion) {

            case 1:
                cout << "\n>> Números del 1 al 5:" << endl;
                for (int i = 1; i <= 5; i++) {
                    cout << "   " << i << endl;
                }
                break;

            case 2:
                cout << "\n>> Números pares del 2 al 10:" << endl;
                for (int i = 2; i <= 10; i += 2) {
                    cout << "   " << i << endl;
                }
                break;

            case 3: {
                double numero;
                cout << "\nIngrese un número: ";
                cin  >> numero;

                if (numero > 0) {
                    cout << ">> El número " << numero << " es POSITIVO." << endl;
                } else if (numero < 0) {
                    cout << ">> El número " << numero << " es NEGATIVO." << endl;
                } else {
                    cout << ">> El número ingresado es CERO." << endl;
                }
                break;
            }

            case 4:
        
                cout << "Nombre del estudiante: Moisés Abinadí Farfan González1" << endl;
                break;

            default:
                cout << "\n[ERROR] Opción inválida. Por favor elija entre 1 y 4." << endl;
                continue;
        }

    } while (opcion != 4);

    return 0;
}