#include <iostream>
using namespace std;

int main() {

int nota = 0;
int sumatotal = 0;
double promedio;
int contador =  0;
int aprueba = 0;
int reprueba = 0;

for (contador = 0; contador <=4; contador++)
{
    cout << "Ingresar nota: ";
    cin >> nota;

    if (nota >= 61) { 
        aprueba= aprueba+ 1;}

        else{
            reprueba = reprueba + 1;}
        

    sumatotal = nota + sumatotal;
}

cout << "Suma total: " << sumatotal << endl;


promedio = sumatotal / 5.0;

cout << "Promedio: " << promedio << endl;
cout << "Notas aprobadas: " << aprueba << endl;
cout << "Notas reprobadas: " << reprueba << endl;

if (promedio >= 61){
  cout << "Resultado final: Aprueba";
}
else{ cout << "Resultado final: Reprueba ";}


return 0;

}