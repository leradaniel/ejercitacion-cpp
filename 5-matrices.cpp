/*
Enunciado
Se deben procesar las actividades desarrolladas por los estudiantes de un curso en un periodo determinado. Para esto se informa el área y el número de actividad.
Las áreas están codificadas mediante el siguiente código (pueden estar fijas en el programa en un vector): CS, CN, PDL, MA, MS, PL, EF, TX, IG.
Las actividades están numeradas desde 1 hasta 10.
Los datos recibidos son:
Nombre del/la estudiante
Por cada tarea entregada 
Fecha
Código de Área
Número de tarea
Esta información corresponde a un único estudiante. No tiene un orden establecido, esto quiere decir que se informa en cualquier orden.
Se pide mostrar una tabla que represente "gráficamente" el estado de avance del estudiante. La tabla debe ser más o menos como la siguiente
Área      CS, CN, PDL, MA, MS, PL, EF, TX, IG.         TOTAL
1            SI  SI      SI                                                       3
2            SI  SI                                                                 2
3
4                             SI                                                     1
5
6
....
TOTAL      2    2      2
Pistas:
1. pensar (o adaptar de la clase) una función que "convierta" el código de un área a un valor 0-(n-1)
2. no dejar filas y/o columnas sin utilizar, para lo cual "pensar" cómo "adaptar" el número de tarea para que comience en 0
3. pensar (o adaptar) una función que reciba una matriz y un número de fila) y devuelva la cantidad (o suma) de valores en esa fila. Idem columna. 
4. escribir una función que reciba el vector de códigos de área y pida por teclado la información del estudiante, calcule y procese
5. la función propuesta en la pista 3 puede "contar" la cantidad de SI en la fila y/o columna
6. primero procesar todos los datos, armar la matriz y luego recorrer la matriz para mostrar los pedido
*/
#include <iostream>
using namespace std;

//Constantes
#define _CANTAREAS 9
#define _CANTTAREAS 10

typedef string tCodArea[_CANTAREAS];
typedef bool tTareaArea[_CANTAREAS][_CANTTAREAS];

void inicializar_matriz(tTareaArea &mTareaArea);
void ingresoDatos(tCodArea vCodArea, tTareaArea &mTareaArea, string &nombre);
void registrarTarea(tCodArea vCodArea, tTareaArea &mTareaArea);
void mostrarFicha(string nombre, tCodArea vCodArea, tTareaArea mTareaArea);
int sumarAreasDeTarea(tTareaArea mTareaArea, int tarea);
int sumarTareasDeArea(tTareaArea mTareaArea, int area);

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    string nombre;
    tCodArea vCodArea{{"CS_"}, {"CN_"}, {"PDL"}, {"MA_"}, {"MS_"}, {"PL_"}, {"EF_"}, {"TX_"}, {"IG_"}};
    tTareaArea mTareaArea;
    inicializar_matriz(mTareaArea);
    ingresoDatos(vCodArea, mTareaArea, nombre);
    mostrarFicha(nombre, vCodArea, mTareaArea);
}
//INICIALIZAR MATRIZ PENDIENTE
void inicializar_matriz(tTareaArea &mTareaArea)
{
    for (int i = 0; i < _CANTAREAS; i++)
    {
        for (int j = 0; j < _CANTTAREAS; j++)
        {
            mTareaArea[i][j] = false;
        }
    }
}
//OBTENER NUMERO DE AREA
int obtenerNarea(tCodArea vCodArea, string area)
{
    int i = 0;
    while (vCodArea[i] != area)
    {
        i++;
    }
    return i;
}
//suma tareas del area
int sumarTareasDeArea(tTareaArea mTareaArea, int area)
{
    int suma = 0;
    for (int i = 0; i < _CANTTAREAS; i++)
    {
        if (mTareaArea[area][i] == true)
        {
            suma++;
        }
    }
    return suma;
}

//Suma areas de tarea
int sumarAreasDeTarea(tTareaArea mTareaArea, int tarea)
{
    int suma = 0;
    for (int i = 0; i < _CANTAREAS; i++)
    {
        if (mTareaArea[i][tarea] == true)
        {
            suma++;
        }
    }
    return suma;
}

void ingresoDatos(tCodArea vCodArea, tTareaArea &mTareaArea, string &nombre)
{
    cout << "Ingrese el nombre del alumno" << endl;
    cin >> nombre;

    registrarTarea(vCodArea, mTareaArea);
}

void registrarTarea(tCodArea vCodArea, tTareaArea &mTareaArea)
{
    string area;
    int tarea;
    int nArea;
    string fecha;

    cout << "Ingrese el area (Salir para terminar)" << endl;
    cin >> area;

    while (area != "salir")
    {
        cout << "Ingrese el nro de tarea" << endl;
        cin >> tarea;

        nArea = obtenerNarea(vCodArea, area);
        mTareaArea[nArea][tarea - 1] = true;

        cout << "Ingrese la fecha" << endl;
        cin >> fecha;

        cout << "Ingrese el area (Salir para terminar)" << endl;
        cin >> area;
    }
}

void mostrarFicha(string nombre, tCodArea vCodArea, tTareaArea mTareaArea)
{
    cout << endl
         << "Grilla de tareas entregadas del alumno: " << nombre << endl
         << endl;
    // Titulos de AREA
    int c;
    cout << "Área  ";
    for (int i = 0; i < _CANTAREAS; i++)
    {
        cout << "  " << vCodArea[i];
    }
    cout << "   TOTAL" << endl;
    cout << endl;

    for (int i = 0; i < _CANTTAREAS; i++)
    {
        c = (i + 1);
        if (c < 10)
        {
            cout << " ";
        }
        cout << c << "     ";
        for (int j = 0; j < _CANTAREAS; j++)
        {
            if (mTareaArea[j][i] == true)
            {
                cout << " SI  ";
            }
            else
            {
                cout << "     ";
            }
        }
        cout << "   " << sumarAreasDeTarea(mTareaArea, i) << endl;
    }

    cout << endl;
    cout << "TOTAL    ";
    for (int i = 0; i < _CANTAREAS; i++)
    {
        cout << sumarTareasDeArea(mTareaArea, i) << "    ";
    }
}