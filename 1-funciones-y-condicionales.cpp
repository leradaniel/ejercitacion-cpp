/*
Enunciado
Resolver el siguiente problema:
Procesar las edades de un conjunto de personas de las cuales nos informan su nombre y fecha de nacimiento.
Se debe mostrar por pantalla:
- el nombre de la persona mayor;
- el nombre de la persona menor;
- cuántas personas tienen hasta 20 años;
- cuántas personas tienen entre 21 y 30 años;
- cuántas personas tienen más de 30 años
Supongan que no hay dos personas que hayan nacido el mismo día.
Pista 1: para conocer la edad en años de cada estudiante pueden usar la siguiente función (buscar el programa en los ejemplos publicados)
int diferenciaFechas(int dia1, int mes1, int anio1, int dia2, int mes2, int anio2) {
   int dif;
    dif = int((((anio1-anio2)*12+(mes1-mes2))*30+dia1-dia2)/360);
return dif;
}
Recibe 2 fechas y devuelve la cantidad de días entre ambas considerando que todos los meses tienen 30 días (es lo más que podemos hacer ahora, prometo que en poco tiempo van a poder mejorar esta función
Para que siempre devuelva un valor mayor a 0 (independientemente del orden que ingresan las fechas) al cálculo se le aplica la función "abs" que recibe un número y devuelve el valor positivo del número
Pista 2: para calcular cuántos años tiene cada estudiante deben comparar su fecha de nacimiento con la fecha del proceso, la cual se debe pedir al inicio del programa
Pista 3: si tienen dificultades para avanzar agendamos un encuentro virtual con el grupo y trabajamos para que puedan completar la tarea
Luego debe pasarlo a C++, compilarlo y probarlo.  Tengan en cuenta que PseInt arma el código a partir del pseudocódigo y no siempre puede resolver los tipos de las variables. En esos casos define un tipo de datos que denomina SIN_TIPO  y lo hace de tipo string.   Para este problema deben borrar esa línea y cambiar en todos los lugares que lo mencione (diga SIN_TIPO) por int o float.
*/
#include <iostream>
using namespace std;

// Declaraciones adelantadas de las funciones
bool fecha_valida(int dia, int mes, int ano);
int fecha_entero(int dia, int mes, int ano);
int calcular_edad(int dia, int dia_actual, int mes, int mes_actual, int ano, int ano_actual);

// ===========================================================comienzo del programa===============================
int main()
{
  int ano;
  int dia;
  //fechan = fecha en numero largo
  int fechan;
  int mayor = 29999999;
  int menor = 0;
  int mes = 0;
  //año mes y dia actual (fecha actual)
  int anoa = 0;
  int mesa = 0;
  int diaa = 0;

  int menor20 = 0;
  int menor30 = 0;
  int mayor30 = 0;
  int edad = 0;

  string nmayor;
  string nmenor;
  string nombre;
  cout << "Por favor ingrese la fecha actual (primero dìa, luego mes, luego año)" << endl;
  cin >> diaa >> mesa >> anoa;
  cout << "Por favor, ingrese el nombre (nombre=Salir=fin)" << endl;
  cin >> nombre;
  //cin >> dia;
  //cin >> mes;
  //cin >> ano;

  while (nombre != "salir")
  {
    cout << "Por favor, ingrese la fecha de nacimiento (primero dìa, luego mes, luego año)" << endl;
    cin >> dia;
    cin >> mes;
    cin >> ano;
    if (fecha_valida(dia, mes, ano) == true)
    {
      fechan = fecha_entero(dia, mes, ano);

      //calcula edad
      edad = calcular_edad(dia, diaa, mes, mesa, ano, anoa);

      if (edad < 20)
      {
        menor20++;
      }
      else if (edad <= 30)
      {
        menor30++;
      }
      else
      {
        mayor30++;
      }

      if (fechan > menor)
      {
        menor = fechan;
        nmenor = nombre;
      }
      if (fechan < mayor)
      {
        mayor = fechan;
        nmayor = nombre;
      }
      cout << "Por favor, ingrese otro nombre (nombre=salir=fin)" << endl;
      cin >> nombre;
      //cin >> dia;
      //cin >> mes;
      //cin >> ano;
    }
    else
    {
      cout << "Fecha Invalida" << endl;
      cout << "Por favor, ingrese nuevamente el nombre (nombre=salir=fin)" << endl;
      cin >> nombre;
      //cin >> dia;
      //cin >> mes;
      //cin >> ano;
    }
  }
  if (menor != 0)
  {
    cout << "El mayor es " << nmayor << " y el menor es " << nmenor << endl;
    cout << "Las personas menores a 20 son " << menor20 << ",ingresaron " << menor30 << " personas menores de 30 y mayores de 20, y " << mayor30 << " mayores a 30 ";
  }
  else
  {
    cout << "No se ingresaron edades" << endl;
  }
  system("PAUSE");
  return 0;
}

// define si la fecha es Valida
bool fecha_valida(int dia, int mes, int ano)
{
  bool biciesto;
  bool vdia;
  bool vfecha;
  bool vmes;
  vdia = false;
  vmes = false;
  if (ano % 4 == 0)
  {
    if (ano % 100 == 0)
    {
      if (ano % 400 == 0)
      {
        biciesto = true;
      }
      else
      {
        biciesto = false;
      }
    }
    else
    {
      biciesto = true;
    }
  }
  else
  {
    biciesto = false;
  }
  if (mes <= 12 && mes > 0)
  {
    vmes = true;
  }
  else
  {
    vmes = false;
  }
  if ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) && dia > 0 && dia < 32)
  {
    vdia = true;
  }
  else
  {
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 0 && dia < 31)
    {
      vdia = true;
    }
    else
    {
      if (mes == 2)
      {
        if (biciesto == true && dia > 0 && dia < 30)
        {
          vdia = true;
        }
        else
        {
          if (biciesto == false && dia > 0 && dia < 29)
          {
            vdia = true;
          }
        }
      }
    }
  }
  if (vmes == true && vdia == true)
  {
    vfecha = true;
  }
  else
  {
    vfecha = false;
  }
  return vfecha;
}

int calcular_edad(int dia, int dia_actual, int mes, int mes_actual, int ano, int ano_actual)
{
  //Calcula la edad con una fecha fija
  int edad = ano_actual - ano;
  if (mes_actual < mes)
  {
    edad--;
  }
  else
  {
    if (mes_actual == mes)
    {
      if (dia_actual < dia)
      {
        edad--;
      }
    }
  }
  return edad;
}

// transforma la fecha en un numero entero .Es necesario que primero se compruebe la validez de la fehca
int fecha_entero(int dia, int mes, int ano)
{
  int fecha;
  ano = ano * 10000;
  mes = mes * 100;
  fecha = dia + mes + ano;
  return fecha;
}