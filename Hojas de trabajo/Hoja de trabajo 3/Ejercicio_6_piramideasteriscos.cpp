#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Ingrese un numero: ";
    cin >> n;

    int i = 1;

    while (i <= n) {
        int espacios = n - i;
        int j = 0;

        // Imprimir espacios
        while (j < espacios) {
            cout << " ";
            j++;
        }

        int k = 0;

        // Imprimir asteriscos
        while (k < i) {
            cout << "*";
            k++;
        }

        cout << endl;
        i++;
    }

    return 0;
}