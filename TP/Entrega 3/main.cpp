/*
[Temas trabajados tercera entrega: estructuras enlazadas, memoria dinámica]
Se debe desarrollar un algoritmo que permita que, a partir de los datos de los archivos
desarrollados en el punto anterior, se armen listas con sublistas donde las listas
representan las listas votadas y las sublistas representan cada voto
1. Describir la estructura de listas y sublistas que “soporten” los datos de la estructura
2. Definir claramente el orden de las listas y sublistas teniendo en cuenta los requerimientos
descriptos más abajo
3. Desarrollar un algoritmo que “levante” a memoria en pantalla cuántas mujeres y cuántos
varones votaron cada lista
4. Desarrollar un algoritmo que muestre por pantalla la secuencia de votos ordenados por
edad en años, indicando la edad y si es varón o mujer
*/
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define _cantCandid 25

struct sLista
{
  string nombre;
  string candidato[_cantCandid];
  int numeroLista;
  int totMujeres;
  int totHombres;
};

struct sLecLista
{
  string nombre;
  string candidato[_cantCandid];
  int numeroLista;
};

struct sVoto
{
  int lista_votada;
  string sexo_del_votante;
  int edad_del_votante;
};

struct sLecVoto
{
  int lista_votada;
  string sexo_del_votante;
  int edad_del_votante;
};

struct pVoto
{
  sVoto info;
  pVoto *pSig;
};

struct pLista
{
  sLista info;
  pLista *pSig;
  pVoto *pPrimero;
};

//Prototipos
pVoto *insertarOrdenadoVoto(pVoto *&cabLista, sVoto dato);
void cargarListas(char *arch, pLista *&lListas);
void leerLista(FILE *&fListas, sLista &rLista, bool &fin);
pLista *insertarOrdenadoLista(pLista *&cabLista, sLista dato);
void insertarListaNulosBlancos(string nombre_lista, int numero_lista, pLista *&lListas);
void cargarVotos(pLista *&lListas);
void leerVoto(FILE *&fVoto, sVoto &rVoto, bool &fin);
pVoto *buscar(pLista *pLis, int que, sVoto rVoto);
int definirNumeroLista(int valor_recibido);
void totalHombresMujeres(sLista &info, sVoto dato);
void mostrarHombresMujeres(pLista *info);
void mostrarLaListaConSublista(pLista *cabeza);
void recorrerSublista(pVoto *q);

int main()
{
  pLista *lListas = NULL;
  cargarListas("Listas.dat", lListas); //Genera una lista con la "lista de candidatos"
  cargarVotos(lListas);                //Genera sublistas con los votos en por orden de edad en cada nodo de la lista de Listas
  mostrarHombresMujeres(lListas);
  mostrarLaListaConSublista(lListas);
  return 0;
}

//Cargar archivo en memoria
void cargarListas(char *arch, pLista *&lListas)
{

  FILE *fListas = fopen(arch, "rb");
  sLista rLista;
  pLista *p;
  bool fin;
  if (fListas != NULL)
  {
    leerLista(fListas, rLista, fin);
    while (!fin)
    {
      p = insertarOrdenadoLista(lListas, rLista);
      p->info.totMujeres = 0;
      p->info.totHombres = 0;
      p->pPrimero = NULL;
      leerLista(fListas, rLista, fin);
    }
    fclose(fListas);
  }
  else
    cout << "No existe archivo Listas.dat" << endl;
  insertarListaNulosBlancos("Blanco", 0, lListas);
  insertarListaNulosBlancos("Nulo", 6, lListas);
}

//Leer Listas
void leerLista(FILE *&fListas, sLista &rLista, bool &fin)
{
  fread(&rLista, sizeof(rLista), 1, fListas);
  if (feof(fListas))
  {
    fin = true;
  }
  else
  {
    fin = false;
  }
}

//Agrega como listas los votos en blanco y nulos
void insertarListaNulosBlancos(string nombre_lista, int numero_lista, pLista *&lListas)
{
  sLista dato;
  dato.nombre = nombre_lista;
  for (int i; i < _cantCandid; i++)
  {
    dato.candidato[i] = "";
  }
  dato.numeroLista = numero_lista;
  pLista *p = new (pLista);
  p->info = dato;
  p->pSig = NULL;
  insertarOrdenadoLista(lListas, dato);
}

//INSERTAR NODO ORDENADO LISTAS
pLista *insertarOrdenadoLista(pLista *&cabLista, sLista dato)
{
  pLista *p = new (pLista);
  pLista *q;
  p->info = dato;
  p->pSig = NULL;
  if (cabLista == NULL)
  {
    cabLista = p;
  }
  else
  {
    if ((dato.numeroLista) < (p->info.numeroLista))
    {
      p->pSig = cabLista;
      cabLista = p;
    }
    else
    {
      q = cabLista;
      while ((q->pSig != NULL) && (dato.numeroLista > q->pSig->info.numeroLista))
      {
        q = q->pSig;
      }
      p->pSig = q->pSig;
      q->pSig = p;
    }
  }
  return p;
}

//Cargar archivo en memoria
void cargarVotos(pLista *&lListas)
{
  FILE *fVotos = fopen("Votos.dat", "rb");
  sVoto rVoto;

  bool fin;
  if (fVotos != NULL)
  {
    leerVoto(fVotos, rVoto, fin);
    while (!fin)
    {
      pVoto *q = NULL;
      q = buscar(lListas, rVoto.lista_votada, rVoto);
      insertarOrdenadoVoto(q, rVoto);
      leerVoto(fVotos, rVoto, fin);
    }
    fclose(fVotos);
  }
  else
    cout << "No existe archivo Votos.dat" << endl;
  insertarListaNulosBlancos("Blanco", 0, lListas);
  insertarListaNulosBlancos("Nulo", 6, lListas);
}

//Lee el archivo de votos
void leerVoto(FILE *&fVoto, sVoto &rVoto, bool &fin)
{
  fread(&rVoto, sizeof(rVoto), 1, fVoto);
  if (feof(fVoto))
    fin = true;
  else
    fin = false;
}

//INSERTAR NODO ORDENADO VOTOS
pVoto *insertarOrdenadoVoto(pVoto *&cabLista, sVoto dato)
{
  pVoto *p = new (pVoto);
  pVoto *q;
  p->info = dato;
  p->pSig = NULL;
  if (cabLista == NULL)
  {
    cabLista = p;
  }
  else if (dato.edad_del_votante < p->info.edad_del_votante)
  {
    p->pSig = cabLista;
    cabLista = p;
  }
  else
  {
    q = cabLista;
    while ((q->pSig != NULL) && (dato.edad_del_votante > q->pSig->info.edad_del_votante))
      q = q->pSig;
    p->pSig = q->pSig;
    q->pSig = p;
  };
  return p;
}

//Devuelve el puntero segun el "que" buscado
pVoto *buscar(pLista *pLis, int que, sVoto rVoto)
{
  pLista *p;
  p = pLis;
  pVoto *q = NULL;
  int numLista = definirNumeroLista(p->info.numeroLista);

  while ((p != NULL) && (numLista != p->info.numeroLista))
  {
    p = p->pSig;
  }
  if ((p != NULL) && (numLista == p->info.numeroLista))
  {
    q = p->pPrimero;
    totalHombresMujeres(p->info, rVoto);
    return q;
  }
  else
    return NULL;
}

//Unifica todos los votos de listas mayores a 5 (votos nulos) en una lista 6
int definirNumeroLista(int valor_recibido)
{
  if (valor_recibido > 5)
  {
    valor_recibido = 6;
  }
  return valor_recibido;
}

// Contabiliza cuantos hombres y mujeres votaron en cada lista
void totalHombresMujeres(sLista &info, sVoto dato)
{
  if (dato.sexo_del_votante == "H")
    info.totHombres++;
  if (dato.sexo_del_votante == "M")
    info.totMujeres++;
}

// Muestra los Hombres y Mujeres que votaron
void mostrarHombresMujeres(pLista *info)
{
  pLista *p = info;
  cout << "SE MUESTRAN HOMBRES Y MUJERES: " << endl;
  while (p != NULL)
  {
    if ((p->info.numeroLista > 0) && (p->info.numeroLista < 6))
    {
      cout << "Lista: " << p->info.numeroLista;
      cout << "El total de Hombres que votó es " << p->info.totHombres << endl;
      cout << "El total de Mujeres que votó es " << p->info.totMujeres << endl;
    }
    p = p->pSig;
  }
}

//recorre y muestra las listas
void mostrarLaListaConSublista(pLista *cabeza)
{
  pLista *p = cabeza;
  pVoto *q = NULL;

  cout << "La lista " << p->info.nombre << " fue votada por: " << endl;

  while (p != NULL)
  {
    recorrerSublista(q);
    p = p->pSig;
  }
}

//recorre las sublistas
void recorrerSublista(pVoto *q)
{
  string sexo = "";
  while (q != NULL)
  {
    if (q->info.sexo_del_votante == "H")
    {
      sexo = "Hombre";
    }
    else
    {
      sexo = "Mujer";
    }
    cout << sexo << " de " << q->info.edad_del_votante << " años." << endl;
    q = q->pSig;
  }
}