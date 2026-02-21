#include <iostream>
using namespace std;

int main () {
	double montoinicial;
	double porcentaje;
	double resultado;

cout << "Ingresa una cantidad inicial: ";
cin >> montoinicial;

cout << "Ingresa un porcentaje inicial: ";
cin >> porcentaje;

resultado = montoinicial + (montoinicial * porcentaje / 100);
cout << "El resultado es: " << resultado << endl;

return 0;

}
