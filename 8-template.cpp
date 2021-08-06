/*
Enunciado
Desarrollar una función sumaVectores (se debe poder utilizar con números enteros y con números reales) vectores que reciba 2 vectores de igual dimensión y cuyo contenido sean números, y devuelva un tercer vector en cuyas celdas estén las sumas de las celdas de los vectores recibidos.
Ejemplo números enteros:
v1 | 15 | 12 | 6 |
v2 | 8 | 17 | 16 |
vs | 23 | 29 | 22 |
Ejemplo números reales:
v1 | 15.0 | 12.0 | 6.0 |
v2 | 8.0 | 17.0 | 16.0 |
vs | 23.0 | 29.0 | 22.0 |
Se pide:
Desarrollar una única función sumaVectores  mediante el uso de template
Desarrollar un programa que resuelva:
- para 2 vectores de números enteros (pueden ser constantes) y generar el vector suma de números enteros
- para 2 vectores de números reales (pueden ser constantes)  y generar el vector suma de números reales
*/
#include <iostream>
using namespace std;

#define _CANT 3

typedef int tVecInt[_CANT];
typedef float tVecFloat[_CANT];

template <typename X>
void sumaVector(X v1, X v2, X v3);

template <typename X>
void muestraVector(X v);

template <typename X>
void mostrarVector(X v1, X v2, X v3);

int main()
{
    tVecInt v1 = {2, 5, 7};
    tVecInt v2 = {1, 9, 3};
    tVecInt v3 = {0, 0, 0};
    tVecFloat v4 = {2.6, 1.8, 7.5};
    tVecFloat v5 = {3.3, 6.7, 8.8};
    tVecFloat v6 = {0.0, 0.0, 0.0};

    cout << endl
         << "Vectores Enteros" << endl;
    sumaVector<tVecInt>(v1, v2, v3);
    mostrarVector<tVecInt>(v1, v2, v3);

    cout << endl
         << "Vectores Flotantes" << endl;
    sumaVector<tVecFloat>(v4, v5, v6);
    mostrarVector<tVecFloat>(v4, v5, v6);
}

template <typename X>
void mostrarVector(X v1, X v2, X v3)
{
    cout << "Primer vector          : ";
    muestraVector<X>(v1);
    cout << "Segundo vector         : ";
    muestraVector<X>(v2);
    cout << "Suma de los vectores   : ";
    muestraVector<X>(v3);
}

template <typename X>
void sumaVector(X v1, X v2, X v3)
{
    for (int i = 0; i < _CANT; i++)
    {
        v3[i] = v2[i] + v1[i];
    }
}

template <typename X>
void muestraVector(X v)
{
    for (int i = 0; i < _CANT; i++)
    {
        cout << v[i] << "\t\t";
    }
    cout << endl;
}