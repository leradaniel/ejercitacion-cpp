/*
Enunciado: 
Para una compañía que alquila elementos de buceo se debe realizar un algoritmo para realizar el control de los equipos.Los datos a procesar son: 
Equipos de buceo, se disponen de 20 tipos de equipos con los siguientes datos: código (3 caracteres), tipo de equipo (número entre 1 y 3); descripción (50 caracteres); stock, valor diario de alquiler. Esta información está ordenada por código y finaliza con un código en “0” (en caso que se procese de un archivo, finaliza cuando termina el archivo). ESTOS SON DATOS INICIALES DE LOS EQUIPOS (NO HAY EQUIPOS ALQUILADOS EN EL MOMENTO DE PROCESAR ESTOS DATOS) 
Alquileres/devoluciones, por cada alquiler o devolución se dispone de los siguientes datos: código (3 caracteres), tipo de operación (A – alquiler, D – devolución), fecha del alquiler y fecha de devolución (la fecha de devolución está en 0 cuando se trata de un alquiler), DNI (documento del cliente). Esta información está ordenada por fecha y finaliza con un código en “0” (en caso que se procese de un archivo, finaliza cuando termina el archivo). EN CASO DE DEVOLUCIÓN DEBEN ESTAR LAS DOS FECHAS (PERMITE CALCULAR EL MONTO DEL ALQUILER) 
Se pide 
A – (2pts) Desarrollar la estructura de datos para todo el problema y completar la función main principal (presentada más abajo) que invoca a las distintas funciones solicitadas/agregadas para resolver el problema. Desarrollar la función de ingreso de datos de equipos para alquiler. 
Int main () { 
// definir las variables para autos y aquellas que considere necesarias 
inicializarEquipos(); // completar parámetros 
ingresarEquipos() ; // completar parámetros 
procesarAlquileres(); // completar parámetros punto B 
mostrarEquiposPtoC() ; // completar parámetros 
listadoOrdenadoEquiposPtoD(); // completar parámetros 
} 
B – (3 pts) Desarrollar una función para procesar los alquileres/devoluciones que mantenga actualizada la cantidad equipos con que cuenta la empresa, muestre para cada devolución el valor a cobrar al cliente (TENER EN CUENTA QUE ESTÁN LAS FECHAS DE ALQUILER Y DEVOLUCIÓN) y al final de proceso muestre el total facturado por la empresa. Para calcular el monto a cobrar se debe multiplicar el valor diario del equipo por la cantidad de días alquilados (calcular mediante la función diferencia –ver al final). Tener en cuenta actualizar el stock y cantidad de equipos alquilados, en todos los casos. 
C – (2 ptos) Desarrollar una función que muestre en la pantalla todos los equipos con la cantidad en stock y la cantidad de equipos alquilados (por cada equipo la compañía dispone la siguiente cantidad de equipos=stock + alquilados) y al final del listado el total por cada tipo de equipo (entre 1 y 3). 
D – (3 pts p/posibilidad de promocionar) Desarrollar una función que emita un listado ordenado en forma decreciente por cantidad de alquileres de cada equipo, que contenga la descripción, la cantidad de veces que se alquiló el equipo y la cantidad en stock actualmente. 
Resuelva favoreciendo uso de módulos (además de los solicitados) con los parámetros que corresponda en cada caso. En caso de necesitar utilice las funciones desarrolladas en la clase sin hacerlas nuevamente. Para resolver en computadora se adjunta archivos con datos y la estructura general del programa con las funciones para leer los datos de archivos de texto y búsqueda y ordenamiento mediante “templates”. 
struct tFecha { 
int dia; 
int mes; 
int anio; } ; 
int diferenciaFechas(tFecha f1, tFecha f2) { 
int abs((f1.anio-f2.anio)*12 +(f1.mes-f2.mes)*30 + (f1.dia-f2.dia)); 
return dif; 
} 
Fecha f1 = {16,7,2020}; 
tFecha f2 = {5,5,2020}; 
int cantDias = diferenciaFechas(f1, f2);
*/
#include <iostream>
#include <string>
using namespace std;

#define _CANTTIPOSEQUIPOS 20

struct tFecha
{
    int dia;
    int mes;
    int anio;
};

typedef char codigo[4];
typedef char descripcion[5];

struct tEquipo_de_buceo
{
    codigo codigo_3_digitos;
    int tipo_de_equipo;
    descripcion descripcion_50_digitos;
    int stock;
    int en_alquiler;
    int veces_que_fue_alquilado;
    int valor_diario;
};

typedef tEquipo_de_buceo equipos_de_buceo[_CANTTIPOSEQUIPOS];

void inicializarEquipos(equipos_de_buceo, int);
int ingresarEquipos(equipos_de_buceo, int);
void procesarAlquileres(equipos_de_buceo, int);
int buscarIndiceEquipo(char codigo_recibido[4], equipos_de_buceo, int);
int diferenciaFechas(tFecha, tFecha);
void mostrarEquiposPtoC(equipos_de_buceo, int);
void listadoOrdenadoEquiposPtoD(equipos_de_buceo, int);
void ordenar_vector(equipos_de_buceo, int);
void intercambiar_vector(equipos_de_buceo, int, int);
void mostrarVectorDrecreciente(equipos_de_buceo, int);

int main()
{
    equipos_de_buceo equipos;
    int cantidad_equipos_registrados = 0;
    // definir las variables para autos y aquellas que considere necesarias
    inicializarEquipos(equipos, _CANTTIPOSEQUIPOS);                             // completar parámetros
    cantidad_equipos_registrados = ingresarEquipos(equipos, _CANTTIPOSEQUIPOS); // completar parámetros
    procesarAlquileres(equipos, cantidad_equipos_registrados);                  // completar parámetros punto B
    mostrarEquiposPtoC(equipos, cantidad_equipos_registrados);                  // completar parámetros
    listadoOrdenadoEquiposPtoD(equipos, cantidad_equipos_registrados);          // completar parámetros
}

void inicializarEquipos(equipos_de_buceo vector_recibido, int tamanio_del_vector)
{
    for (int i = 0; i < tamanio_del_vector; i++)
    {
        strcpy_s(vector_recibido[i].codigo_3_digitos, "");
        vector_recibido[i].tipo_de_equipo = 0;
        strcpy_s(vector_recibido[i].descripcion_50_digitos, "");
        vector_recibido[i].stock = 0;
        vector_recibido[i].en_alquiler = 0;
        vector_recibido[i].veces_que_fue_alquilado = 0;
        vector_recibido[i].valor_diario = 0;
    }
}

int ingresarEquipos(equipos_de_buceo vector_recibido, int tamanio_del_vector)
{
    char codigo_ingresado[4];
    int i = 0;
    cout << "=============================================" << endl;
    cout << "INICIO DE PROCESO: REGISTRAR EQUIPOS DE BUCEO" << endl;
    cout << "=============================================" << endl;
    cout << "Ingrese el código del equipo de buceo (3 caracteres alfanumericos). Para finalizar, ingrese 0." << endl;
    cin >> codigo_ingresado;
    while (_stricmp("0", codigo_ingresado) != 0 && i < tamanio_del_vector)
    {
        strcpy_s(vector_recibido[i].codigo_3_digitos, codigo_ingresado);
        cout << "Ingrese el tipo de equipo (1, 2 o 3)." << endl;
        cin >> vector_recibido[i].tipo_de_equipo;
        cout << "Ingrese una descripción para el equipo (hasta 50 carácteres)." << endl;
        //cin >> vector_recibido[i].descripcion_50_digitos;
        getline(cin, vector_recibido[i].descripcion_50_digitos);
        cout << "Ingrese la cantidad de stock para el equipo." << endl;
        cin >> vector_recibido[i].stock;
        cout << "Ingrese el precio a cobrar de forma diaria en pesos ($)." << endl;
        cin >> vector_recibido[i].valor_diario;
        i++;
        if (i < tamanio_del_vector)
        {
            cout << "Ingrese el código del equipo de buceo (3 caracteres alfanumericos). Para finalizar, ingrese 0." << endl;
            cin >> codigo_ingresado;
        }
    }
    cout << "Ingresó un total de " << i << " equipos." << endl
         << endl;
    return i;
}

void procesarAlquileres(equipos_de_buceo vector_recibido, int tamanio_del_vector)
{
    int indice_del_equipo;
    int total_facturado = 0;
    tFecha fecha_alquiler;
    tFecha fecha_devolucion;
    int dni = 0;
    int dias_alquilado;
    int valor_a_cobrar;
    char codigo_ingresado[4];
    string operacion_ingresada = "";
    cout << "=====================================================" << endl;
    cout << "INICIO DE PROCESO: PROCESAR ALQUILERES Y DEVOLUCIONES" << endl;
    cout << "=====================================================" << endl;
    cout << "Ingrese el código del equipo de buceo a procesar (3 caracteres alfanumericos). Para finalizar, ingrese 0." << endl;
    cin >> codigo_ingresado;
    while (_stricmp("0", codigo_ingresado) != 0)
    {
        indice_del_equipo = buscarIndiceEquipo(codigo_ingresado, vector_recibido, tamanio_del_vector);
        cout << "Ingrese [A] si se trata de un alquiler o [D] si se trata de una devolución:" << endl;
        cin >> operacion_ingresada;
        if (operacion_ingresada == "A")
        {
            cout << "Ingrese la fecha del alquiler en formato DD MM AAAA, separados por un espacio:" << endl;
            cin >> fecha_alquiler.dia >> fecha_alquiler.mes >> fecha_alquiler.anio;
            fecha_devolucion.dia = 0;
            fecha_devolucion.mes = 0;
            fecha_devolucion.anio = 0;
            cout << "Ingrese el DNI del cliente:" << endl;
            cin >> dni;
            vector_recibido[indice_del_equipo].stock--;
            vector_recibido[indice_del_equipo].en_alquiler++;
            vector_recibido[indice_del_equipo].veces_que_fue_alquilado++;
            cout << "El equipo fue alquilado." << endl;
        }
        else if (operacion_ingresada == "D")
        {
            cout << "Ingrese la fecha del alquiler en formato DD MM AAAA, separados por un espacio:" << endl;
            cin >> fecha_alquiler.dia >> fecha_alquiler.mes >> fecha_alquiler.anio;
            cout << "Ingrese la fecha de la devolución en formato DD MM AAAA, separados por un espacio:" << endl;
            cin >> fecha_devolucion.dia >> fecha_devolucion.mes >> fecha_devolucion.anio;
            cout << "Ingrese el DNI del cliente:" << endl;
            cin >> dni;
            dias_alquilado = diferenciaFechas(fecha_devolucion, fecha_alquiler);
            valor_a_cobrar = dias_alquilado * vector_recibido[indice_del_equipo].valor_diario;
            vector_recibido[indice_del_equipo].stock++;
            vector_recibido[indice_del_equipo].en_alquiler--;
            cout << "El equipo fue devuelto." << endl;
            cout << "Por la cantidad de " << dias_alquilado << " días y a un precio diario de $" << vector_recibido[indice_del_equipo].valor_diario << " se cobrará $" << valor_a_cobrar << "." << endl;
            total_facturado += valor_a_cobrar;
        }
        else
        {
            cout << "¡ERROR! ¡RECUERDE QUE SOLAMENTE DEBE INGRESAR [A] O [D] SEGÚN CORRESPONDA!" << endl;
        }
        cout << "Ingrese el próximo código del equipo de buceo a procesar (3 caracteres alfanumericos). Para finalizar, ingrese 0." << endl;
        cin >> codigo_ingresado;
    }
    cout << "El total facturado por la empresa es de $" << total_facturado << "." << endl
         << endl;
}

int buscarIndiceEquipo(char codigo_recibido[4], equipos_de_buceo vector_recibido, int tamanio_del_vector)
{
    for (int i = 0; i < tamanio_del_vector; i++)
    {
        if (_stricmp(codigo_recibido, vector_recibido[i].codigo_3_digitos) == 0)
        {
            return i;
        }
    }
}

int diferenciaFechas(tFecha f1, tFecha f2)
{
    int dif = abs((f1.anio - f2.anio) * 12 + (f1.mes - f2.mes) * 30 + (f1.dia - f2.dia));
    return dif;
}

void mostrarEquiposPtoC(equipos_de_buceo vector_recibido, int tamanio_del_vector)
{
    int equipos_alquilados_tipo_1 = 0;
    int equipos_alquilados_tipo_2 = 0;
    int equipos_alquilados_tipo_3 = 0;
    cout << "=====================================================" << endl;
    cout << "INICIO DE PROCESO: MOSTRAR EQUIPOS (STOCK+ALQUILADOS)" << endl;
    cout << "=====================================================" << endl;
    for (int i = 0; i < tamanio_del_vector; i++)
    {
        cout << "Equipo con el código " << vector_recibido[i].codigo_3_digitos << ":" << endl;
        cout << "Cantidad en stock: " << vector_recibido[i].stock << "." << endl;
        cout << "Cantidad actualmente en alquiler: " << vector_recibido[i].en_alquiler << "." << endl;
        cout << "Cantidad total: " << vector_recibido[i].stock + vector_recibido[i].en_alquiler << "." << endl;
        switch (vector_recibido[i].tipo_de_equipo)
        {
        case 1:
            equipos_alquilados_tipo_1 += vector_recibido[i].en_alquiler;
            break;
        case 2:
            equipos_alquilados_tipo_2 += vector_recibido[i].en_alquiler;
            break;
        case 3:
            equipos_alquilados_tipo_3 += vector_recibido[i].en_alquiler;
            break;
        default:
            break;
        }
    }

    cout << endl
         << "Total de equipos de tipo 1 actualmente alquilados: " << equipos_alquilados_tipo_1;
    cout << endl
         << "Total de equipos de tipo 2 actualmente alquilados: " << equipos_alquilados_tipo_2;
    cout << endl
         << "Total de equipos de tipo 3 actualmente alquilados: " << equipos_alquilados_tipo_3 << endl;
}

void listadoOrdenadoEquiposPtoD(equipos_de_buceo vector_recibido, int tamanio_del_vector)
{
    ordenar_vector(vector_recibido, tamanio_del_vector);
    mostrarVectorDrecreciente(vector_recibido, tamanio_del_vector);
}

//Ordena decreciente, de mayor a menor
void ordenar_vector(equipos_de_buceo vector_recibido, int tamanio_del_vector)
{
    int indice_minimo;
    for (int indice_actual = 0; indice_actual < tamanio_del_vector; indice_actual++)
    {
        indice_minimo = indice_actual;
        for (int indice_recorrido = indice_actual; indice_recorrido < tamanio_del_vector; indice_recorrido++)
        {
            if (vector_recibido[indice_recorrido].veces_que_fue_alquilado > vector_recibido[indice_minimo].veces_que_fue_alquilado)
            {
                indice_minimo = indice_recorrido;
            }
        }
        intercambiar_vector(vector_recibido, indice_actual, indice_minimo);
    }
}

void intercambiar_vector(equipos_de_buceo vector_recibido, int indice_mayor, int indice_menor)
{
    tEquipo_de_buceo auxiliar;

    strcpy_s(auxiliar.codigo_3_digitos, vector_recibido[indice_mayor].codigo_3_digitos);
    auxiliar.tipo_de_equipo = vector_recibido[indice_mayor].tipo_de_equipo;
    strcpy_s(auxiliar.descripcion_50_digitos, vector_recibido[indice_mayor].descripcion_50_digitos);
    auxiliar.stock = vector_recibido[indice_mayor].stock;
    auxiliar.en_alquiler = vector_recibido[indice_mayor].en_alquiler;
    auxiliar.veces_que_fue_alquilado = vector_recibido[indice_mayor].veces_que_fue_alquilado;
    auxiliar.valor_diario = vector_recibido[indice_mayor].valor_diario;

    strcpy_s(vector_recibido[indice_mayor].codigo_3_digitos, vector_recibido[indice_menor].codigo_3_digitos);
    vector_recibido[indice_mayor].tipo_de_equipo = vector_recibido[indice_menor].tipo_de_equipo;
    strcpy_s(vector_recibido[indice_mayor].descripcion_50_digitos, vector_recibido[indice_menor].descripcion_50_digitos);
    vector_recibido[indice_mayor].stock = vector_recibido[indice_menor].stock;
    vector_recibido[indice_mayor].en_alquiler = vector_recibido[indice_menor].en_alquiler;
    vector_recibido[indice_mayor].veces_que_fue_alquilado = vector_recibido[indice_menor].veces_que_fue_alquilado;
    vector_recibido[indice_mayor].valor_diario = vector_recibido[indice_menor].valor_diario;

    strcpy_s(vector_recibido[indice_menor].codigo_3_digitos, auxiliar.codigo_3_digitos);
    vector_recibido[indice_menor].tipo_de_equipo = auxiliar.tipo_de_equipo;
    strcpy_s(vector_recibido[indice_menor].descripcion_50_digitos, auxiliar.descripcion_50_digitos);
    vector_recibido[indice_menor].stock = auxiliar.stock;
    vector_recibido[indice_menor].en_alquiler = auxiliar.en_alquiler;
    vector_recibido[indice_menor].veces_que_fue_alquilado = auxiliar.veces_que_fue_alquilado;
    vector_recibido[indice_menor].valor_diario = auxiliar.valor_diario;
}

void mostrarVectorDrecreciente(equipos_de_buceo vector_recibido, int tamanio_del_vector)
{
    cout << "============================================================" << endl;
    cout << "INICIO DE PROCESO: VECTOR DECRECIENTE SEGÚN TOTAL ALQUILADOS" << endl;
    cout << "============================================================" << endl;
    for (int i = 0; i < tamanio_del_vector; i++)
    {
        cout << "Equipo con el código " << vector_recibido[i].codigo_3_digitos << ":" << endl;
        cout << "Cantidad total de alquileres que tuvo: " << vector_recibido[i].veces_que_fue_alquilado << "." << endl;
        cout << "Descripción: " << vector_recibido[i].descripcion_50_digitos << "." << endl;
        cout << "Actualmente en stock: " << vector_recibido[i].stock << "." << endl;
    }
}