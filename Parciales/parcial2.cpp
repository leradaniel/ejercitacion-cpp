/*
Temas evaluados: Resolución de problemas, abstracción, estructuras de datos, accesos
Problema
Para una distribuidora mayorista de golosinas se debe desarrollar una aplicación que permita administrar adecuadamente los productos que comercializa, de acuerdo a las compras realizadas.
Dispone de los siguientes flujos de datos:
PRODUCTOS: se trata de un archivo que contiene un registro por cada producto con los siguientes datos (código de producto (alfanumérico de 6 caracteres), descripción (alfabético de 50 caracteres). Está ordenado por código de producto
COMPRAS: se trata de un archivo que contiene un registro por cada compra con los siguientes datos (código de producto (alfanumérico de 6 caracteres), fecha de compra (numérico), cantidad, precio unitario (es el precio pagado cada vez que se compra). Cada producto puede tener 0, 1 o varias compras. Está ordenado por fecha de compra
A partir de los archivos mencionados se deben generar una estructura en memoria que permita resolver lo pedido: recorrer rápidamente las compras de cada producto. Tener en cuenta que es importante conocer el total pagado (cantidad por precio unitario de cada compra). Para esto deben diseñar la estructura incluyendo este valor, el cual deberán calcular mientras ingresan las compras.
Se pide:
1. (2 pts) Desarrollar en C++ toda la estructura de datos requeridas para este problema: registro de archivos, listas en memoria, etc.
2. (3 pts) Desarrollar las funciones de carga de los archivos en memoria en la estructura pensada en función del listado a realizar. Tener en cuenta que deben desarrollar dos funciones: cargaProducto y cargaCompras
3. (2 ptos) Desarrollar el main() del programa, teniendo en cuenta que solo debe definir variables y llamar a los procesos (debidamente parametrizados)
4. (3 ptos) Desarrollar una función que reciba un puntero a la estructura cargada y muestre en pantalla todos los productos (1 línea por producto) que incluya la cantidad de compras realizadas y el valor total pagado. PISTA: PENSAR LA ESTRUCTURA DE PRODUCTOS CON ESTOS CAMPOS
Usar las funciones de librería propuestas en la materia
Funciones para usar archivos:
Variable de archivo = abrirArchivoLectura(nombre físico archivo)
cerrarArchivo(variable de archivo)
LeerArchivo(variable de archivo, variable de registro, variable booleana que indica fin)
Funciones para usar listas:
Puntero = insertarLista(puntero lista, dato a insertar)
Puntero = buscarLista(puntero lista, clave a buscar)
*/
#include <cstdlib>
#include <iostream>
#include <string.h>
using namespace std;

typedef char str6[7];
typedef char str50[51];

//Estructuras (Lectura)
struct tRegProducto
{
    str6 codigo;
    str50 descripcion;
};

struct tRegCompra
{
    str6 codigo;
    int fechaCompraAAAAMMDD;
    int cantidad;
    int precio;
};

//Estructuras (para Nodos)
struct tDatoProducto
{
    str6 codigo;
    str50 descripcion;
    int cantComprasRealizadas;
    int totalPagado;
};

struct tDatoCompra
{
    int fechaCompraAAAAMMDD;
    int cantidad;
    int precio;
};

//Nodo (compra)
struct pNodoCompra
{
    tDatoCompra info;
    pNodoCompra *pSig;
};

//Nodo (producto con sublista compra)
struct pNodoProducto
{
    tDatoProducto info;
    pNodoProducto *pSig;
    pNodoCompra *pPrimer;
};

//Prototipos
void cargarProducto(char *, pNodoProducto *&);
pNodoProducto *insertarOrdenadoListaProducto(pNodoProducto *&, tDatoProducto);
void cargarCompras(char *, pNodoProducto *);
pNodoProducto *buscarListaProducto(pNodoProducto *, str6);
pNodoCompra *insertarOrdenadoListaCompra(pNodoCompra *&, tDatoCompra);
void mostrarTodosProductos(pNodoProducto *);

int main()
{
    pNodoProducto *listaProducto = NULL;
    cargarProducto("productos.dat", listaProducto);
    cargarCompras("compras.dat", listaProducto);
    mostrarTodosProductos(listaProducto);
    return 0;
}

//Función que carga del archivo productos.dat en la lista
void cargarProducto(char *archivoOrigen, pNodoProducto *&listaProducto)
{
    FILE *f = fopen(archivoOrigen, "rb");
    tRegProducto reg;
    tDatoProducto dato;
    pNodoProducto *p;
    fread(&reg, sizeof(reg), 1, f);
    while (!feof(f))
    {
        strcpy(dato.codigo, reg.codigo);
        strcpy(dato.descripcion, reg.descripcion);
        p = insertarOrdenadoListaProducto(listaProducto, dato);
        //Se inicializa la información agregada que se completa luego con la sublista
        p->info.cantComprasRealizadas = 0;
        p->info.totalPagado = 0;
        p->pPrimer = NULL;
        fread(&reg, sizeof(reg), 1, f);
    }
    fclose(f);
}

//Función que inserta la lista de manera ordenada segun el codigo de producto
pNodoProducto *insertarOrdenadoListaProducto(pNodoProducto *&listaProducto_recibida, tDatoProducto dato)
{
    pNodoProducto *p = new (pNodoProducto);
    pNodoProducto *q;
    p->info = dato;
    p->pSig = NULL;
    if (listaProducto_recibida == NULL)
    {
        listaProducto_recibida = p;
    }
    else
    {
        //Ordenado por codigo
        if ((strcmp(dato.codigo, listaProducto_recibida->info.codigo) < 0))
        {
            p->pSig = listaProducto_recibida;
            listaProducto_recibida = p;
        }
        else
        {
            q = listaProducto_recibida;
            while ((q->pSig != NULL) && ((strcmp(dato.codigo, q->pSig->info.codigo) > 0)))
            {
                q = q->pSig;
            }
            p->pSig = q->pSig;
            q->pSig = p;
        }
    }
    return p;
}

//Función que carga como sublista las compras en la lista correspondiente
void cargarCompras(char *archivoOrigen, pNodoProducto *listaProducto)
{
    FILE *f = fopen(archivoOrigen, "rb");
    tRegCompra reg;
    tDatoCompra dato;
    pNodoProducto *p;
    pNodoCompra *q;
    fread(&reg, sizeof(reg), 1, f);
    while (!feof(f))
    {
        p = buscarListaProducto(listaProducto, reg.codigo);
        if (p != NULL) //Si se encuentra la lista con el mismo código
        {
            dato.fechaCompraAAAAMMDD = reg.fechaCompraAAAAMMDD;
            dato.cantidad = reg.cantidad;
            dato.precio = reg.precio;
            q = insertarOrdenadoListaCompra(p->pPrimer, dato);
            p->info.cantComprasRealizadas++;                      //Se actualiza la cantidad de compras realizadas. Independientemente de la cantidad que se compre, la transacción de compra es una sola.
            p->info.totalPagado += (dato.precio * dato.cantidad); //Se suma al total recaudado el precio de ese producto multiplicado a la cantidad que se compra.
        }
        else
        {
            cout << "La compra está asociada a un producto inexistente, de código: " << reg.codigo << endl;
        }
    }
    fclose(f);
}

//Función que busca y devuelve la lista cuyo codigo de producto coincida con el de una sublista compra
pNodoProducto *buscarListaProducto(pNodoProducto *pLista, str6 codigoBuscado)
{
    //Cabecera
    pNodoProducto *p;
    p = pLista;

    //Loop que recorre y busca una coincidencia entre los codigos de producto de la compra y de la lista
    while ((p != NULL) && (strcmp(codigoBuscado, p->info.codigo) != 0))
    {
        p = p->pSig;
    }

    if ((p != NULL) && (strcmp(codigoBuscado, p->info.codigo) == 0))
    {
        return p; //Se devuelve la lista con la coincidencia
    }
    else
    {
        return NULL; //No hubo coincidencia
    }
}

//Función que inserta una sublista compra en una lista producto ordenado por la fecha de compra
pNodoCompra *insertarOrdenadoListaCompra(pNodoCompra *&listaCompra_recibida, tDatoCompra dato)
{
    pNodoCompra *p = new (pNodoCompra);
    pNodoCompra *q;
    p->info = dato;
    p->pSig = NULL;
    if (listaCompra_recibida == NULL)
    {
        listaCompra_recibida = p;
    }
    else
    {
        //Ordenado por la fecha de compra
        if (dato.fechaCompraAAAAMMDD < listaCompra_recibida->info.fechaCompraAAAAMMDD)
        {
            p->pSig = listaCompra_recibida;
            listaCompra_recibida = p;
        }
        else
        {
            q = listaCompra_recibida;
            while ((q->pSig != NULL) && (dato.fechaCompraAAAAMMDD > q->pSig->info.fechaCompraAAAAMMDD))
            {
                q = q->pSig;
            }
            p->pSig = q->pSig;
            q->pSig = p;
        }
    }
    return p;
}

//Función que muestra todos los productos, con la cantidad de compras realizadas y valor total pagado
void mostrarTodosProductos(pNodoProducto *listaProducto)
{
    cout << "=====================================" << endl;
    cout << "A continuación se van a mostrar todos los productos, junto a la cantidad de compras realizadas y el valor total pagado de cada uno." << endl;
    cout << "=====================================" << endl;
    pNodoProducto *p = listaProducto; //Cabecera
    //Mientras que la lista no sea nula
    while (p != NULL)
    {
        cout << "Producto " << p->info.codigo << ": " << p->info.descripcion << ". Tiene la cantidad de " << p->info.cantComprasRealizadas << " compras realizadas y un total pagado de $" << p->info.totalPagado << "." << endl
             << endl;
        p = p->pSig; //Se carga la siguiente lista de productos
    }
}