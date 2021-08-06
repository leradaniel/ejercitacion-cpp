#include <iostream>
using namespace std;
//typedef char str30[30];

struct datos_persona
{
    string nombre;
    int fechaNac;
    int edad;
};

//typedef datos_persona
typedef datos_persona datos_grupos[50];
datos_grupos grupo;

int main()
{
    for (int i = 0; i < 50; i++)
    {
        grupo[i].nombre = "";
        grupo[i].fechaNac = 0;
        grupo[i].edad = 0;
    }
    int DD;
    int MM;
    int AAAA;
    cout << "Ingrese la fecha de nacimiento DD MM AAAA" << endl;
    cin >> DD >> MM >> AAAA;
    cout << AAAA;
    cout << MM;
    cout << DD;
}

//Esto de dif tiene todo.
/*
int diferenciaFechas(int dia1, int mes1, int anio1, int dia2, int mes2, int anio2) {
  int dif;

   dif = int((((anio1-anio2)*12+(mes1-mes2))*30+dia1-dia2)/360);
return dif;
}
*/
// funcion inicializa vector
