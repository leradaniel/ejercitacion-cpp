/*
[Temas trabajados primera entrega: arreglos]
Se debe desarrollar un algoritmo para distribuir las bancas de acuerdo al conteo de votos
1. Describir la estructura necesaria para la resolución del problema
2. Mostrar por pantalla una tabla indicando claramente los números de lista, nombre de la
lista, la cantidad de votos de cada lista y porcentaje entre los votos válidos, ordenado de
mayor a menor, la cantidad de votos nulos y de votos en blanco
3. Mostrar por pantalla una tabla como la del ejemplo de más arriba, indicando claramente
para cada lista los nombres de los candidatos que obtienen banca
4. Mostrar por pantalla, para cada lista la cantidad de votos por rango de edades hasta 18
años hasta 30 años hasta 50 años más de 50 años
*/
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

#define _cantCandid 25
#define _cantListas 5
#define _cantBancas 5
#define _maxBancas _cantListas *_cantBancas

struct sLista
{
    string nombre;                 // Nombre de la lista
    string candidato[_cantCandid]; // Nombres de los candidatos
    int cantHasta18;               // Cantidad de votos <=18 a�os
    int cantHasta30;               // Cantidad de votos 19 a 30 a�os
    int cantHasta50;               // Cantidad de votos 31 a 50 a�os
    int cantMasDe50;               // Cantidad de votos >=51 a�os
    int porcentaje;                // Porcentaje de votos sacados sobre el total
    int banca[_cantBancas];        // Calculo D'Hont para Bancas 1 a 5
    int cantBancas;                // Cantidad de bancas obtenidas
};

struct sVoto
{
    int lista_votada;
    string sexo_del_votante;
    int edad_del_votante;
};

struct sBanca
{
    int indLista;     // Indice de la Lista en el vector de Listas
    int votosBanca;   // Votos correspondiente a la banca
    string candidato; // Candidato asignado para la banca
};

typedef sLista tVlistas[_cantListas];
typedef sBanca tVbancas[_maxBancas];

void inicializarListas(tVlistas v, int max);
void analisisDhont(tVlistas v, tVbancas vB, int total, int max, int blancos, int nulos);
void calcularPorcentaje(tVlistas v, int total, int max);
void ordenarPorPorcentaje(tVlistas v, int tope);
void calcularBancas(tVlistas v, tVbancas vB, int max);
void inicializarBancas(tVbancas v, int tope);
void ordenarBancas(tVbancas v, int tope);
void mostrarTabla(tVlistas v, int max, int votosEnBlanco, int votosNulos);
void mostrarLista(tVbancas vB, int max);
void mostrarEdadListas(tVlistas V, int cant);
void parsearListas(string cadena, sLista &lista, int &indiceAnt, int &i);
void procesarListas(char *ori, tVlistas v, int tope);
int pasarPalabraNro(string ori);
void pasarPalabra(char *dest, string ori);
void procesarVotos(char *, int &, int &, int &, tVlistas);
void parsearVotos(string, sVoto &, int &, int &);
void distribuirVoto(sVoto, int &, int &, int &, tVlistas);
int calcularRangoEdad(int);

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    tVlistas vListas;                         // Vector con todas las listas
    tVbancas vBancas;                         // Vector para manejar Bancas
    int votosBlancos = 0;                     // Contador de votos en blanco
    int votosNulos = 0;                       // Contador de votos nulos
    int votosTotales = 0;                     // Contador de todos los votos validos
    char archivo_nombres[12] = "nombres.csv"; // Listado de nombres de los candidatos
    char archivo_votos[10] = "votos.csv";     // Listado de Votos a procesar

    inicializarListas(vListas, _cantListas);
    inicializarBancas(vBancas, _maxBancas);

    cout << "TRABAJO PRACTICO ANUAL - PRIMER ENTREGA - GRUPO 8" << endl
         << endl;

    procesarListas(archivo_nombres, vListas, _cantListas);
    procesarVotos(archivo_votos, votosTotales, votosBlancos, votosNulos, vListas);

    // Ejecucion de los puntos 2 y 3
    analisisDhont(vListas, vBancas, votosTotales, _cantListas, votosBlancos, votosNulos);

    // Ejecucion del punto 4
    mostrarEdadListas(vListas, _cantListas);
}

void inicializarListas(tVlistas v, int max)
{
    for (int i = 0; i < max; i++)
    {
        v[i].nombre = "";
        for (int j = 0; j < _cantCandid; j++)
        {
            v[i].candidato[j] = "";
        }
        v[i].cantHasta18 = 0;
        v[i].cantHasta30 = 0;
        v[i].cantHasta50 = 0;
        v[i].cantMasDe50 = 0;
        v[i].porcentaje = 0;
        for (int j = 0; j < _cantBancas; j++)
        {
            v[i].banca[j] = 0;
        }
        v[i].cantBancas = 0;
    }
}

/*
- Calcula el porcentaje que sac� cada lista en base a los votos validos
- Ordena las listas por porcentaje sacado (decreciente)
- Calcula cuantas bancas saca cada lista
- Muestra la tabla con los totales de cada lista para cada banca segun analisis D'Hont
- Muesta la lista de los candidatos que obtienen banca  
*/
void analisisDhont(tVlistas v, tVbancas vB, int total, int max, int blancos, int nulos)
{
    sLista listaAux;
    calcularPorcentaje(v, total, max);
    ordenarPorPorcentaje(v, max);
    calcularBancas(v, vB, max);
    mostrarTabla(v, max, blancos, nulos);
    mostrarLista(vB, _cantBancas);
}

void calcularPorcentaje(tVlistas v, int total, int max)
{
    int porc = 0;
    for (int i = 0; i < max; i++)
    {
        v[i].porcentaje = round((v[i].cantHasta18 + v[i].cantHasta30 + v[i].cantHasta50 + v[i].cantMasDe50) * 100 / total);
    }
}

void ordenarPorPorcentaje(tVlistas v, int tope)
{

    sLista aux;
    int maximo;

    for (int i = 0; i < tope; i++)
    {
        maximo = i;
        for (int j = i + 1; j < tope; j++)
        {
            if (v[j].porcentaje > v[maximo].porcentaje)
            {
                maximo = j;
            }
        }
        aux = v[i];
        v[i] = v[maximo];
        v[maximo] = aux;
    };
}

void calcularBancas(tVlistas v, tVbancas vB, int max)
{
    int j = 0;
    int totalLista = 0;

    for (int i = 0; i < max; i++)
    {
        totalLista = v[i].cantHasta18 + v[i].cantHasta30 + v[i].cantHasta50 + v[i].cantMasDe50;
        for (int k = 0; k < _cantBancas; k++)
        {
            vB[j].indLista = i;
            vB[j].votosBanca = round(totalLista / (k + 1));
            vB[j].candidato = v[i].candidato[k];
            v[i].banca[k] = vB[j].votosBanca;
            j++;
        }
    }

    ordenarBancas(vB, j);

    for (int i = 0; i < _cantBancas; i++)
    {
        v[vB[i].indLista].cantBancas++;
    }
}

void inicializarBancas(tVbancas v, int tope)
{
    for (int i = 0; i < tope; i++)
    {
        v[i].indLista = 0;
        v[i].votosBanca = 0;
        v[i].candidato = "";
    }
}

void ordenarBancas(tVbancas v, int tope)
{

    sBanca aux;
    int maximo;

    for (int i = 0; i < tope - 1; i++)
    {
        maximo = i;
        for (int j = i + 1; j < tope - 1; j++)
        {
            if (v[j].votosBanca > v[maximo].votosBanca)
            {
                maximo = j;
            }
        }
        aux = v[i];
        v[i] = v[maximo];
        v[maximo] = aux;
    };
}

void mostrarTabla(tVlistas v, int max, int votosEnBlanco, int votosNulos)
{

    printf("%-20s   %11s   %10s  %7s   %7s   %7s   %7s   %7s   %7s \n\n", "Lista", "Total Votos", "Porcentaje", "Banca 1", "Banca 2", "Banca 3", "Banca 4", "Banca 5", "Ganan:");
    for (int i = 0; i < max; i++)
    {

        printf("%-20s   %11i   %9i%%  %7i   %7i   %7i   %7i   %7i    ", v[i].nombre.c_str(), v[i].banca[0], v[i].porcentaje, v[i].banca[0], v[i].banca[1], v[i].banca[2], v[i].banca[3], v[i].banca[4]);

        if (v[i].porcentaje < 3)
        {
            cout << "OBTUVO MENOS DEL 3%, QUEDA DESCARTADA" << endl;
        }
        else
        {
            if (v[i].cantBancas == 0)
            {
                cout << "NO OBTUVO BANCAS" << endl;
            }
            else
            {
                cout << "OBTUVO " << v[i].cantBancas << " BANCA(S)" << endl;
            }
        }
    }
    printf("%-20s   %11i \n", "Votos en blanco", votosEnBlanco);
    printf("%-20s   %11i \n", "Votos nulos", votosNulos);
    cout << endl
         << endl;
}

void mostrarLista(tVbancas vB, int max)
{
    cout << "GANADORES - Obtienen banca: " << endl
         << endl;
    for (int i = 0; i < max; i++)
    {
        cout << "Banca " << i + 1 << " - " << vB[i].candidato << endl;
    }
    cout << endl
         << endl;
}

void mostrarEdadListas(tVlistas V, int cant)
{
    int i = 0;
    while (i < cant)
    {
        cout << "Votos por rango de edad de lista " << V[i].nombre << endl;
        cout << "Votantes hasta 18 a�os:      " << V[i].cantHasta18 << endl;
        cout << "Votantes entre 18 y 30 a�os: " << V[i].cantHasta30 << endl;
        cout << "Votantes entre 30 y 50 a�os: " << V[i].cantHasta50 << endl;
        cout << "Votantes Mayores de 50 a�os: " << V[i].cantMasDe50 << endl;
        cout << endl;

        i++;
    }
}

void procesarListas(char *ori, tVlistas v, int tope)
{

    sLista lista;
    string cadena;
    int indiceAnt = 0;
    int indCand = 0;

    ifstream fe(ori);
    while (getline(fe, cadena))
    {
        parsearListas(cadena, lista, indiceAnt, indCand);

        v[indiceAnt].nombre = lista.nombre;
        v[indiceAnt].candidato[indCand - 1] = lista.candidato[indCand - 1];
    }
    fe.close();
}

void parsearListas(string cadena, sLista &lista, int &indiceAnt, int &i)
{

    int primero;
    int ultimo;
    int k = 0;
    string palabra[20];
    int indice = 0;

    primero = 0;
    ultimo = 0;
    while (ultimo < cadena.size())
    {
        ultimo = cadena.find(";", primero);
        if (ultimo == -1)
            ultimo = cadena.size();
        palabra[k] = cadena.substr(primero, ultimo - primero) + '\0';
        k++;
        primero = ultimo + 1;
    }
    indice = pasarPalabraNro(palabra[0]);
    if (indice != indiceAnt)
    {
        i = 0;
        indiceAnt = indice;
    }
    lista.nombre = palabra[1];
    lista.candidato[i] = palabra[2];
    i = i + 1;
}

int pasarPalabraNro(string ori)
{
    int resultado;
    char dest[255];
    pasarPalabra(dest, ori);
    resultado = atoi(dest);
    return resultado;
}

void pasarPalabra(char *dest, string ori)
{

    int i = 0;
    while (i <= ori.size())
    {
        dest[i] = ori[i];
        i++;
    }
    dest[i] = '\0';
}

void procesarVotos(char *archivo_votos_recibido, int &votosTotales, int &votosBlancos, int &votosNulos, tVlistas listas_recibida)
{
    string cadena;
    sVoto votante;
    int indice_anterior = 0;
    int indice_votante = 0;
    ifstream archivo_votos(archivo_votos_recibido);
    while (getline(archivo_votos, cadena))
    {
        parsearVotos(cadena, votante, indice_anterior, indice_votante);
        distribuirVoto(votante, votosTotales, votosBlancos, votosNulos, listas_recibida);
    }
    archivo_votos.close();
}

void parsearVotos(string cadena, sVoto &votante_recibido, int &indice_anterior, int &i)
{
    int primero = 0;
    int ultimo = 0;
    int k = 0;
    string palabra[3];
    int indice = 0;
    while (ultimo < cadena.size())
    {
        ultimo = cadena.find(";", primero);
        if (ultimo == -1)
            ultimo = cadena.size();
        palabra[k] = cadena.substr(primero, ultimo - primero) + '\0';
        k++;
        primero = ultimo + 1;
    }
    votante_recibido.lista_votada = stoi(palabra[0]);
    votante_recibido.sexo_del_votante = palabra[1];
    votante_recibido.edad_del_votante = stoi(palabra[2]);
    i = i + 1;
}

void distribuirVoto(sVoto voto_recibido, int &votosTotales, int &votosBlancos, int &votosNulos, tVlistas listas)
{
    votosTotales++;
    int rango_de_edad = 0;
    if (voto_recibido.lista_votada == 0)
    {
        votosBlancos++;
    }
    else if (voto_recibido.lista_votada > 0 && voto_recibido.lista_votada <= _cantListas)
    {
        rango_de_edad = calcularRangoEdad(voto_recibido.edad_del_votante);
        switch (rango_de_edad)
        {
        case 1: //<= 18
            listas[voto_recibido.lista_votada - 1].cantHasta18++;
            break;
        case 2: //<= 30
            listas[voto_recibido.lista_votada - 1].cantHasta30++;
            break;
        case 3: //<= 50
            listas[voto_recibido.lista_votada - 1].cantHasta50++;
            break;
        case 4: //> 50
            listas[voto_recibido.lista_votada - 1].cantMasDe50++;
            break;
        default:
            break;
        }
    }
    else
    {
        votosNulos++;
    }
}

int calcularRangoEdad(int edad_recibida)
{
    int rangoEdad = 0;
    if (edad_recibida <= 18)
    {
        rangoEdad = 1;
    }
    else if (edad_recibida <= 30)
    {
        rangoEdad = 2;
    }
    else if (edad_recibida <= 50)
    {
        rangoEdad = 3;
    }
    else if (edad_recibida > 50)
    {
        rangoEdad = 4;
    }
    return rangoEdad;
}