/*
Enunciado
Modificar el ejercicio propuesto en la clase para:
o	mostrar las categorías ordenadas por promedio de salario
o	para cada categoría mostrar el empleado que percibe el salario mayor (suponer único).
Sugerencia: agregar a al estructura de categoría salario mayor y nombre del empleado
Enunciado de la clase
Procesar los datos de personas que contienen el nombre, la edad, la categoría y el salario (sin un orden establecido).
La información está en un archivo de texto donde cada línea contiene los datos de un empleado y los datos están separados por el carácter punto y coma (;). La información fue generada mediante una planilla de cálculo y exportada a formato plano (csv)
Se pide:
Mostrar los empleados ordenados por categoría y nombre (aquellos de la misma categoría deben estar ordenados por nombre).
Mostrar al finalizar cada categoría la cantidad de empleados y el salario total de la categoría.
Mostrar al finalizar el proceso una tabla con los totales de cada categoría y el promedio de salarios en cada una.
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#define _CANTPERSONAS 50
#define _CANTCATEGORIAS 6
/*
procesa los datos de empleados (nombre, edad, categoria y salario),
los muestra por pantalla ordenados por categoria / nombre
al final muestra los totales por categoria

la información la obtiene de un archivo de texto con campos separados por ; 
y separa  en los datos en 4 campos, 2 numéricos y 2 cadenas de caracter
y los guarda en un vector de registros

version 6 junio 2020

*/

using namespace std;

typedef char str2[2];
typedef char str60[60];
typedef char str120[120];

// acá se debe definir el diseño del registro para procesar
struct tRPersona
{
    str60 nbe;
    int edad;
    str2 categoria;
    int salario;
};

typedef tRPersona tVPersonas[_CANTPERSONAS];

struct tRCategoria
{
    str2 categoria;
    int cantidad;
    int total;
    float promedio;
    int mayorSalarioV;
    str60 maxVendedor;
};

typedef tRCategoria tVCategoria[_CANTCATEGORIAS];

void inicializarPersonas(tVPersonas, int);
void cargaPersonas(char *ori, tVPersonas, int &);

void muestraPersonas(tVPersonas, int);
void muestraCategorias(tVCategoria, int);
void ordenarPersona(tVPersonas, int);
int buscarCat(tVCategoria, int, str2);
void traer(tVPersonas, tRPersona &, int, int &, bool &);

void parsear(string cadena, tRPersona &per);
void pasarPalabra(char *dest, string ori);
int pasarPalabraNro(string ori);
double pasarPalabraNroDoble(string ori);
void ordenarPromedio(tVCategoria v, int cant);
void muestraCategoriasProm(tVCategoria vCat, int cant);

int main()
{
    /* este es el convertidor lee de un archivo de texto los campos separados 
   por el símbolo ; 
   los pasa a un vector y luego los procesa
  */

    tVPersonas vPer;
    int cantPer = _CANTPERSONAS;

    inicializarPersonas(vPer, cantPer);
    cargaPersonas("valores.csv", vPer, cantPer);
    ordenarPersona(vPer, cantPer);
    muestraPersonas(vPer, cantPer);
}

void inicializarPersonas(tVPersonas v, int cant)
{
    for (int i = 0; i < cant; i++)
    {
        strcpy(v[i].nbe, " ");
        v[i].edad = 0;
        strcpy(v[i].categoria, " ");
        v[i].salario = 0;
    }
}

void traer(tVPersonas v, tRPersona &r, int cant, int &ptro, bool &fin)
{
    if (ptro < cant)
    {
        r = v[ptro];
        ptro++;
        fin = false;
    }
    else
        fin = true;
}

void muestraPersonas(tVPersonas v, int cant)
{
    tRPersona r;
    bool fin;
    int ptro = 0;
    int totalSalario = 0;
    str2 catAnt;
    int totalCat;
    int cantCat;
    int maxSalVend;

    int iCat;
    tVCategoria vCat = {{"A", 0, 0, 0.0, 0}, {"B", 0, 0, 0.0, 0}, {"C", 0, 0, 0.0, 0}, {"D", 0, 0, 0.0, 0}, {"E", 0, 0, 0.0, 0}, {"F", 0, 0, 0.0, 0}};

    printf("Datos de personas ordenadas por categoria /nombre\n"),
        printf("%40s %5s %5s %10s\n", "Nombre", "Edad", "Cat.", "Salario");
    printf("%-40s %5s %5s %10s\n", "=======================================", "====", "====", "=======");
    traer(v, r, cant, ptro, fin);
    while (!fin)
    {
        memcpy(catAnt, r.categoria, sizeof(catAnt));
        totalCat = 0;
        cantCat = 0;
        int maxSalVend = 0;
        iCat = buscarCat(vCat, 6, r.categoria);
        while ((!fin) && (strcmp(catAnt, r.categoria) == 0))
        {
            printf("%-40s %5d %1s    %10d\n", r.nbe, r.edad, r.categoria, r.salario);
            totalCat = totalCat + r.salario;
            cantCat++;
            if (maxSalVend < r.salario)
            {
                vCat[iCat].mayorSalarioV = r.salario;
                strcpy(vCat[iCat].maxVendedor, r.nbe);
                maxSalVend = r.salario;
            }
            traer(v, r, cant, ptro, fin);
        }
        vCat[iCat].promedio = 1.0 * totalCat / cantCat;

        printf("Categoria: %2s;                                     cantidad=%2d    total=%10d\n",
               catAnt, cantCat, totalCat);
        vCat[iCat].total = totalCat;
        vCat[iCat].cantidad = cantCat;
        totalSalario = totalSalario + totalCat;
    }
    printf("Total salario %48d\n", totalSalario);
    muestraCategorias(vCat, 6);

    ordenarPromedio(vCat, 6);
    muestraCategoriasProm(vCat, 6);
}

void cargaPersonas(char *ori, tVPersonas v, int &tope)
{
    /*   Obtiene la información del archivo de texto, donde los campos están
  separados por el símbolo punto y coma y
  arma un vector de registros 
  Acá se debe modificar de acuerdo a cada caso     */
    tRPersona per;
    string cadena;
    int i = 0;
    //  Abre un entrada de entrada cadena de caracteres
    ifstream fe(ori);

    cout << "Procesa personas desde el archivo de texto " << ori << " a " << endl;
    cout << "El archivo origen es un texto que tiene nombre;edad;categoria;salario " << endl;
    cout << "separado por el simbolo ; sin encabezado" << endl;
    cout << "=============================================================" << endl;
    while ((i < tope) && (getline(fe, cadena)))
    {                         // detecta la marca de fin de archivo
        parsear(cadena, per); // separa los campos, los devuelve en el registro de acuerdo al tipo de datos

        // se pasan los campos al vector
        memcpy(v[i].nbe, per.nbe, sizeof(v[i].nbe));
        v[i].edad = per.edad;
        memcpy(v[i].categoria, per.categoria, sizeof(v[i].categoria));
        v[i].salario = per.salario;
        i++;
    }
    fe.close();
    tope = i;
}

int buscarCat(tVCategoria v, int cant, str2 que)
{
    int i = 0;
    while ((i < cant) && (strcmp(que, v[i].categoria) != 0))
        i++;
    if (i == cant)
        i = -1;
    return i;
}

void muestraCategorias(tVCategoria vCat, int cant)
{
    int totalCategoria = 0;
    printf("\n  Totales por categoria\n");
    printf("%10s %5s %10s %10s\n", "Categoria", "Cant.", "Total", "Promedio");
    printf("%10s %5s %10s  %10s\n", "=========", "=====", "==========", "==========");
    for (int i = 0; i < cant; i++)
        if (vCat[i].total != 0)
        {
            printf("%10s %5d %10d  %5.2f\n", vCat[i].categoria, vCat[i].cantidad,
                   vCat[i].total, 1.0 * vCat[i].total / vCat[i].cantidad);
            totalCategoria = totalCategoria + vCat[i].total;
        }
    printf("%10s %5d\n", "Total", totalCategoria);
}

void ordenarPersona(tVPersonas v, int cant)
{
    int min;
    tRPersona aux;

    for (int i = 0; i < cant; i++)
    {
        min = i;
        for (int j = i + 1; j < cant; j++)
        {
            if (strcmp(v[min].categoria, v[j].categoria) > 0)
                min = j;
            else if ((strcmp(v[min].categoria, v[j].categoria) == 0) && (strcmp(v[min].nbe, v[j].nbe) > 0))
                min = j;
        }
        aux = v[i];
        v[i] = v[min];
        v[min] = aux;
    }
}

void ordenarPromedio(tVCategoria v, int cant)
{
    int min;
    tRCategoria aux;

    for (int i = 0; i < cant; i++)
    {
        min = i;
        for (int j = i + 1; j < cant; j++)
        {
            if (v[min].promedio > v[j].promedio)
                min = j;
            else if (v[min].promedio == v[j].promedio)
                min = j;
        }
        aux = v[i];
        v[i] = v[min];
        v[min] = aux;
    }
}

void muestraCategoriasProm(tVCategoria vCat, int cant)
{
    int totalCategoria = 0;
    printf("\n  Totales por categoria ordenado por Promedio\n");
    printf("%10s %5s %10s %10s %20s %10s\n", "Categoria", "Cant.", "Total", "Promedio", "Nombre Empleado", "Salario");
    printf("%10s %5s %10s  %10s %20s %10s\n", "=========", "=====", "==========", "==========", "====================", "===========");
    for (int i = 0; i < cant; i++)
        if (vCat[i].total != 0)
        {
            printf("%10s %5d %10d  %5.2f %21s %6.2d\n", vCat[i].categoria, vCat[i].cantidad,
                   vCat[i].total, 1.0 * vCat[i].total / vCat[i].cantidad, vCat[i].maxVendedor, vCat[i].mayorSalarioV);
            totalCategoria = totalCategoria + vCat[i].total;
        }
    printf("%10s %5d\n", "Total", totalCategoria);
}

void parsear(string cadena, tRPersona &per)
{
    // este proceso separa los campos de a línea del
    // archivo de texto buscando los símbolos ;
    // y arma un vector de cadenas de caracteres
    // luego convierte cada campo de acuerdo al tipo
    // y devuelve el registro

    int primero;
    int ultimo;
    int k = 0;
    string palabra[20];
    // int len;

    primero = 0;
    ultimo = 0;
    while (ultimo < cadena.size())
    {
        ultimo = cadena.find(";", primero);
        // en caso de finalizar la frase, indica que
        // el último coincide con el tamaño de la frase
        if (ultimo == -1)
            ultimo = cadena.size();
        // arma un vector de las palabras, las extrae de la cadena, le agrega marca de
        // fin de palabra
        palabra[k] = cadena.substr(primero, ultimo - primero) + '\0';
        k++;
        // avanza para buscar el próximo ;
        primero = ultimo + 1;
    }
    //  acá se modifica de acuerdo a cada caso
    pasarPalabra(per.nbe, palabra[0]);
    per.edad = pasarPalabraNro(palabra[1]);
    pasarPalabra(per.categoria, palabra[2]);
    per.salario = pasarPalabraNro(palabra[3]);
}; // separa los campos, los devuelve en el registro de acuerdo al tipo de datos

void pasarPalabra(char *dest, string ori)
{
    //  pasa el campo de tipo cadena al campo cadenas
    //  del registro

    int i = 0;
    while (i <= ori.size())
    {
        dest[i] = ori[i];
        i++;
    }
    dest[i] = '\0';
}

int pasarPalabraNro(string ori)
{
    // convierte el campo cadena de caracteres en entero
    // para los casos que se requiera en el registro
    int resultado;
    char dest[255];
    pasarPalabra(dest, ori); // primero pasa el campo a una variable simple
    resultado = atoi(dest);
    return resultado;
}

double pasarPalabraNroDoble(string ori)
{
    // convierte el campo cadena de caracteres en entero
    // para los casos que se requiera en el registro
    int resultado;
    char dest[255];
    pasarPalabra(dest, ori); // primero pasa el campo a una variable simple
    resultado = atof(dest);
    return resultado;
}