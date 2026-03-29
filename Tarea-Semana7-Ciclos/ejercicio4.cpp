#include <iostream>
using namespace std;

int main() {

    int seleccion = 0;
    int total = 0;
    int contMalo = 0;
    int contRegular = 0;
    int contBueno = 0;
    int contExcelente = 0;

    do {                      // Nombre del estudiante: Moisés Abinadí Farfan González
        
        cout << "Ingrese calificacion (1=Malo, 2=Regular, 3=Bueno, 4=Excelente, 0=Salir): ";
        cin >> seleccion;
        
        switch (seleccion) {
            case 1:
                contMalo++;
                total++;
                break;
            case 2:
                contRegular++;
                total++;
                break;
            case 3:
                contBueno++;
                total++;
                break;
            case 4:
                contExcelente++;
                total++;
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }

    } while (seleccion != 0); 

    if (total == 0) {
        cout << "No se registraron respuestas." << endl;
    } else {
        cout << "Total de respuestas: " << total << endl;
        cout << "Malo:      " << contMalo << endl;
        cout << "Regular:   " << contRegular << endl;
        cout << "Bueno:     " << contBueno << endl;
        cout << "Excelente: " << contExcelente << endl;
    }

    return 0;
}

