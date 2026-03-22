
#include <iostream>
using namespace std; 

main () {

int numero;
int suma = 0;

cout << "Ingrese un numero ( 0 para terminar ): ";
cin >> numero;

while (numero !=0){
    suma = suma + numero;


cout << "Ingrese otro numero (0 para terminar): ";

cin >> numero; 

}
cout << "La suma total es: " << suma << endl;

return 0;

}