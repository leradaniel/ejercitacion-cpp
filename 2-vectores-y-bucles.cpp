/*
Enunciado
Queremos conocer el promedio de edades de un conjunto de personas (este programa ya lo hicimos) y ALGO MÁS, para lo cual nos informan la edad de cada una de ellas mediante una lista que finaliza en 0.
Además se debe calcular y mostrar cuántas personas tienen una edad mayor al promedio y cuántas personas tienen una edad menor al promedio.

Pista:
   Para conocer el promedio, como ya sabemos, debemos leer todos los datos, sumar y contar.
   Pero, una vez que tenemos el promedio ¿qué hacemos?. Debemos comparar nuevamente todos los datos con el promedio y así contar cuántos superan y cuántos están por debajo.
  Pero, cómo comparamos si los datos ya "se fueron".
    ENTONCES, CUANDO LEEMOS LOS DATOS LOS PODEMOS IR GUARDANDO EN UN VECTOR, EL PRIMERO EN LA PRIMER CELDA, EL SEGUNDO EN LA SEGUNDA CELDA Y ASÍ SUCESIVAMENTE.
    Pero, entonces para comparar (una vez conocido el promedio) podemos recorrer el vector y comparar el contenido de celda por celda (recuerden que es la edad).
    BINGO, usamos un vector para guardar las edades y lo recorremos cuantas veces queremos.
*/
#include <iostream>
using namespace std;

int main()
{
  int contador, edad, suma_edades, mayores_al_promedio, menores_al_promedio;
  int v_edades[100];
  float prom;
  mayores_al_promedio = menores_al_promedio = suma_edades = contador = 0;

  do
  {
    cout << "Ingrese edad (0=fin)" << endl;
    cin >> edad;
    suma_edades = suma_edades + edad;
    v_edades[contador] = edad;
    contador++;
  } while (edad != 0);

  if (contador > 1)
  {
    contador = contador - 1;
    prom = suma_edades / contador;

    for (int i = 0; i < contador; i++)
    {
      if (v_edades[i] > prom)
      {
        mayores_al_promedio++;
      }
      else if (v_edades[i] < prom)
      {
        menores_al_promedio++;
      }
    }

    cout << "El promedio de las edades es " << prom << ". Hay " << mayores_al_promedio << " personas que superan el promedio y " << menores_al_promedio << " personas que estan por debajo del promedio de edad";
  }
  else
  {
    cout << ("No se ingresaron Edades") << endl;
  }

  return 0;
}
