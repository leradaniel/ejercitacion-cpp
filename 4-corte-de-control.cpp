/*
Enunciado
Procesar un conjunto de personas de las cuales conocemos su nombre y fecha de nacimiento. Se debe
Mostrar por pantalla nos nombres y las fechas de nacimiento ordenado por edad.
Mostrar por pantalla la cantidad de personas por edad
Pistas:
1. usar la función dif (de las tareas anteriores) para calcular la edad.
2. con los datos recibidos armar un vector que contenga nombre, fecha y edad
3. ordenar el vector por el campo edad para poder resolver lo pedido.
4. para mostrar por pantalla a la personas resolver una función mostrar que reciba el vector y desde dónde debe recorrer para mostrar (en el caso de mostrar todos se debe invocar a la función indicando que debe recorrer desde la posición 0)
5. el total por edad se debe mostrar luego de cada grupo
6. no resolver funciones de más. La información está validada, por lo tanto no la deben validar

Ejemplo: para 5 personas que tienen 25 y 27 años, se debe mostrar el siguiente listado:
Juana 25
Angel 25
Mario 25
Total 25 = 3
Laura 27
Graciela 27
Total 27 = 2
*/
#include <iostream>
using namespace std;

//Definir estructuras
struct Spersona
{
    string nombre;
    int pdia;
    int pmes;
    int pano;
    int edad;
};
struct contador_edades
{
    int edad;
    int cantidad;
};

//Definir tipos
typedef Spersona Tpersona[50];

//Definir funcion
int diferenciaFechas(int dia1, int mes1, int anio1, int dia2, int mes2, int anio2);
void inicializarVector(Tpersona &Vpersona);
void ordenarVector(Tpersona &Vpersona, int ind);
int pedirVector(Tpersona &Vpersona, int DD, int MM, int AAAA);
void intercambiar_vector(Tpersona &Vpersona, int x, int minimo);
void corteEdad(Tpersona Vpersona, int ind);
void mostrarPersonas(Tpersona Vpersona, int pIni, int pFin);

int main()
{
    //Definir Variables
    int DD;
    int MM;
    int AAAA;
    int ind;
    int j = 0;
    Tpersona Vpersona;

    inicializarVector(Vpersona);

    cout << "Por favor ingrese la fecha actual DD MM AAAA" << endl;
    cin >> DD >> MM >> AAAA;

    ind = pedirVector(Vpersona, DD, MM, AAAA);
    ordenarVector(Vpersona, ind);
    corteEdad(Vpersona, ind);

    return 0;
}

//incializar vector
void inicializarVector(Tpersona &Vpersona)
{
    for (int i = 0; i < 50; i++)
    {
        Vpersona[i].nombre = "";
        Vpersona[i].pdia = 0;
        Vpersona[i].pmes = 0;
        Vpersona[i].pano = 0;
        Vpersona[i].edad = 0;
    }
}

//Pedir vector
int pedirVector(Tpersona &Vpersona, int DD, int MM, int AAAA)
{
    int ind = 0;
    cout << "Ingrese el nombre (salir, para terminar)" << endl;
    cin >> Vpersona[ind].nombre;
    while ((Vpersona[ind].nombre != "salir") && (ind < 50))
    {
        cout << "Ingrese la fecha de nacimiento DD MM AAAA" << endl;
        cin >> Vpersona[ind].pdia >> Vpersona[ind].pmes >> Vpersona[ind].pano;

        Vpersona[ind].edad = diferenciaFechas(DD, MM, AAAA, Vpersona[ind].pdia, Vpersona[ind].pmes, Vpersona[ind].pano);

        ind++;

        cout << "ingrese un nuevo nombre (salir, para terminar)" << endl;
        cin >> Vpersona[ind].nombre;
    }
    return ind;
}

// Define funcion para conseguir la edad
int diferenciaFechas(int dia1, int mes1, int anio1, int dia2, int mes2, int anio2)
{
    int dif;

    dif = int((((anio1 - anio2) * 12 + (mes1 - mes2)) * 30 + dia1 - dia2) / 360);
    return dif;
}

//Ordenar Vector
void ordenarVector(Tpersona &Vpersona, int ind)
{
    int minimo;
    for (int x = 0; x < ind; x++)
    {
        minimo = x;
        for (int y = x; y < ind; y++)
        {
            if (Vpersona[y].edad < Vpersona[minimo].edad)
                minimo = y;
        }
        intercambiar_vector(Vpersona, x, minimo);
    }
}

//esto define ordenar vector
void intercambiar_vector(Tpersona &Vpersona, int x, int minimo)
{
    Spersona auxPersona;

    auxPersona.nombre = Vpersona[x].nombre;
    auxPersona.pano = Vpersona[x].pano;
    auxPersona.pmes = Vpersona[x].pmes;
    auxPersona.pdia = Vpersona[x].pdia;
    auxPersona.edad = Vpersona[x].edad;

    Vpersona[x].nombre = Vpersona[minimo].nombre;
    Vpersona[x].pano = Vpersona[minimo].pano;
    Vpersona[x].pmes = Vpersona[minimo].pmes;
    Vpersona[x].pdia = Vpersona[minimo].pdia;
    Vpersona[x].edad = Vpersona[minimo].edad;

    Vpersona[minimo].nombre = auxPersona.nombre;
    Vpersona[minimo].pano = auxPersona.pano;
    Vpersona[minimo].pmes = auxPersona.pmes;
    Vpersona[minimo].pdia = auxPersona.pdia;
    Vpersona[minimo].edad = auxPersona.edad;
}

//Mostrar personas
void corteEdad(Tpersona Vpersona, int ind)
{
    int pIni = 0;
    int pFin = 0;
    int auxEdad = Vpersona[0].edad;

    for (int i = 0; i < ind; i++)
    {
        if (auxEdad != Vpersona[i].edad)
        {
            pIni = pFin;
            pFin = i;
            mostrarPersonas(Vpersona, pIni, pFin);
            auxEdad = Vpersona[i].edad;
        }
    }
    pIni = pFin;
    pFin = ind;
    mostrarPersonas(Vpersona, pIni, pFin);
}

void mostrarPersonas(Tpersona Vpersona, int pIni, int pFin)
{
    int cont = 0;
    for (int i = pIni; i < pFin; i++)
    {
        cout << "Nombre: " << Vpersona[i].nombre;
        cout << ". Fecha de nacimiento: ";
        cout << Vpersona[i].pdia << "/" << Vpersona[i].pmes << "/" << Vpersona[i].pano;
        cout << ". Edad: " << Vpersona[i].edad << "." << endl;
        cont++;
    }
    cout << "Cantidad de personas de " << Vpersona[pIni].edad << " Años: " << cont << endl
         << endl;
}