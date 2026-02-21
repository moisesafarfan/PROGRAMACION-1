#include <iostream>
using namespace std;

int main() {

    float estatura;
    float peso;
    float imc;

    cout << "Ingrese su estatura en metros: ";
    cin >> estatura;

    cout << "Ingrese su peso en kilogramos: ";
    cin >> peso;

    imc = peso / (estatura * estatura);

    cout << "Su IMC es: " << imc << endl;

    return 0;
}