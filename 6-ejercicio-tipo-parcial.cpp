/*
Enunciado
Pistas:
1. usar todo lo aprendido en el curso
2. ver y trabajar a partir del ejercicio resuelto en esta semana
Un comercio mayorista de golosinas cuenta con 10 vendedores y vende 2.000 artículos. Necesita conocer el total de vendido de cada artículo y cuál es la comisión pagada por las ventas de cada artículo vendido en el periodo procesado.
Para poder realizar el análisis se cuenta con las siguientes fuentes de datos:
a. Por cada vendedor: código de vendedor (1 a 10), porcentaje de comisión (numérico entre 1 y 100).
b. Por cada venta: fecha de venta (numérico en formato AAAAMMDD), código de vendedor (1 a 10), código de artículo (1 a 200), cantidad vendida, importe cobrado. Tener en cuenta que cada artículo se vende muchas veces y cada vendedor vende muchos artículos (finalizan los datos cuando se ingresa una fecha en cero). La información está ordenada por fecha.
Se pide:
(a) (2pts) desarrollar toda la estructura de datos (ED) requerida para este problema.
(b) (1pts) desarrollar la función main que incluya el llamado a los módulos de ingreso de datos requeridos e invoca a las distintas funciones solicitadas/agregadas para resolver el problema.
(c) (3pts) desarrollar las funciones de ingreso de los datos.
(d) (1,5pts) desarrollar una función que, dado un valor que corresponde a un importe y un porcentaje, devuelva el valor que resulta de aplicar el porcentaje al importe. Escriba la cabecera en C++ con sus parámetros e invoque donde corresponda al problema.
(e) (2,5pts) desarrollar una función que reciba el código de un artículo y muestre por pantalla cuántas veces se vendió, el monto total de las ventas de ese artículo y la comisión pagada por ese artículo.
Resuelva favoreciendo uso de módulos (además de los solicitados) con los parámetros que corresponda en cada caso. En caso de necesitar utilice las funciones desarrolladas en la clase sin hacerlas nuevamente.
*/
#include <iostream>
using namespace std;

#define _CANTVENDEDORES 10
#define _CANTARTICULOS 200
#define _CANTVENTAS 2000

//estructuras
struct sVentas
{
  int fecha;
  int codArticulo;
  int cantVendida;
  double importeCobrado;
  int vendedor;
};

struct sArticulos
{
  int codArticulo;
  double precioUnitario;
  int cantVendida;
};

//definicion de tipo
typedef sVentas vVentas[_CANTVENTAS];
typedef int vVendedor[_CANTVENDEDORES];

//Funciones
void cargaVendedores(vVendedor &vendedores);
int cargaVentas(vVentas &ventas);
void inicializarVentas(vVentas &ventas);
int comision(int vendedor, vVendedor vendedores);
double calculoComision(double importe, int comision);
void ordenar(vVentas vector, int desde, int hasta);
int colocar(vVentas vector, int desde, int hasta);
void mostrarArticulo(int codigo, vVendedor vendedores, vVentas ventas, int ultima);

int main() {
  vVendedor vendedores;
  vVentas ventas;
  cargaVendedores(vendedores);
  inicializarVentas(ventas);
  int codigo=0;
  int ultimaVenta = cargaVentas(ventas);
  ordenar(ventas, 0, ultimaVenta);
  cout << "Ingrese el codigo de articulo cuyas estadisticas quiere consultar (Cero para salir): ";
  cin >> codigo;
  while (codigo!=0)
  {
    mostrarArticulo(codigo, vendedores, ventas, ultimaVenta);
    cout << "Ingrese el codigo de articulo cuyas estadisticas quiere consultar (Cero para salir): ";
    cin >> codigo;
  }
}

void cargaVendedores(vVendedor &vendedores)
{
  for (int i=0;i<_CANTVENDEDORES;i++)
  {
    cout << "Ingrese la comision del vendedor " << i+1 << endl;
    cin >> vendedores[i];
  }
}

int cargaVentas(vVentas &ventas)
{
  int sec = 0;
  cout << endl << "Ingrese la fecha de la venta (0 para finalizar)" << endl;
  cin >> ventas[sec].fecha;
  while (ventas[sec].fecha != 0)
  {
    cout << "Ingrese el codigo de articulo" << endl;
    cin >> ventas[sec].codArticulo;
    cout << "Ingrese la cantidad vendida" << endl;
    cin >> ventas[sec].cantVendida;
    cout << "Ingrese el importe cobrado" << endl;
    cin >> ventas[sec].importeCobrado;
    cout << "Ingrese el vendedor" << endl;
    cin >> ventas[sec].vendedor;
    while (ventas[sec].vendedor>_CANTVENDEDORES)
    {
      cout << "Vendedor inexistente, el codigo de vendedor no puede ser mayor a " << _CANTVENDEDORES << endl;
      cout << "Ingrese el vendedor" << endl;
      cin >> ventas[sec].vendedor;
    }
    sec++;
    cout << endl << "Ingrese la fecha de la venta (0 para finalizar)" << endl;
    cin >> ventas[sec].fecha;
  }
  sec--;
  return sec;
}

//inicializar ventas
void inicializarVentas(vVentas &ventas)
{
  for (int i=0;i<_CANTVENTAS;i++)
    {
      ventas[i].fecha = 0;
      ventas[i].codArticulo = 0;
      ventas[i].cantVendida = 0;
      ventas[i].importeCobrado = 0;
      ventas[i].vendedor = 0;
    }
}

double calculoComision(double importe, int comision)
{
  double valorComision = importe * comision / 100;
  return valorComision;
}

//Definir comision
int comision(int vendedor, vVendedor vendedores)
{
  return vendedores[vendedor-1];
}

//Mostrar el artículo
void mostrarArticulo(int codigo, vVendedor vendedores, vVentas ventas, int ultima)
{
  int acumCantidad = 0;
  double acumImporte = 0;
  double acumComision = 0;

  for (int x=0;x<=ultima;x++)
  {
    if (ventas[x].codArticulo == codigo)
      {
        acumCantidad += ventas[x].cantVendida;
        acumImporte += ventas[x].importeCobrado;
        acumComision += calculoComision(ventas[x].importeCobrado, comision(ventas[x].vendedor,vendedores));
      }
    else if (ventas[x].codArticulo > codigo)
    {
      break;
    }
  }
  cout << "\n\n" << "El articulo " << codigo << " tiene " << acumCantidad << " vendidas por $" << acumImporte << " lo cual genero una comision de $" << acumComision  << endl << endl ;
}

// ALGORITMO DE BUSQUEDA -- INICIO

void ordenar(vVentas vector, int desde, int hasta)
{
  int pivote;
  if (desde < hasta)
  {
    pivote = colocar(vector, desde, hasta);
    ordenar(vector, desde, pivote - 1);
    ordenar(vector, pivote + 1, hasta);
  }
}

int colocar(vVentas vector, int desde, int hasta)
{
  int i;
  int pivote, valor_pivote;
  sVentas temp;
  pivote = desde;
  valor_pivote= vector[pivote].codArticulo;
  
  for(i=desde+1; i<=hasta; i++){
    if(vector[i].codArticulo < valor_pivote){
      pivote++; 
      temp=vector[i];
      vector[i]=vector[pivote];
      vector[pivote]=temp;
      }
    }
  temp=vector[desde];
  vector[desde]=vector[pivote];
  vector[pivote]=temp;
  
  return pivote;
}