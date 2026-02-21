#include <iostream>
#include <string>
using namespace std;

int main () {

	string primernombre;
	char inicialprimapellido;
	int edad;
	float estatura;
	double prodprecio;

cout << "Ingresa tu primer nombre: ";
cin >> primernombre ;  

cout << "Ingresa la letra inical de tu primer apellido: ";
cin >> inicialprimapellido;

cout << "¿Cuál es tu edad? ";
cin >> edad;

cout << "¿Cuál es tu estatura? ";
cin >> estatura;

cout << "¿Cuál es el precio del carro? ";
cin >> prodprecio;

cout << "Nombre:" <<" " <<primernombre <<" " << inicialprimapellido << endl;

cout << "Estatura:" <<" " << estatura << endl;

cout << "Edad: " << edad << endl; 

cout << "Precio del carro:" <<" " << prodprecio <<endl;

return 0;

}