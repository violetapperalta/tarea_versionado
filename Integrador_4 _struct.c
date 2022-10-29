// Violeta Porcel de Peralta


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Macros (Para modificar la dimensión de los arreglos 1 única vez en caso de ser necesario. Lo que modifique en el macro, se modifica en todas las partes del código donde se repita.)

// Cantidad de electrodomésticos permitidos - Dimensión
#define MAX_REGISTROS 100

// Longitud código del producto
#define LEN_CODIGO 10

// Longitud descripción del producto
#define LEN_DESCRIPCION 30

// para manejos de los productos..
struct registro
{
    char codigo[LEN_CODIGO];
    char descripcion[LEN_DESCRIPCION];
    int stock;
};

// Funciones
void app_cls();
int app_menu(int _existentes);
int obtener_posicion(struct registro data, struct registro productos[MAX_REGISTROS]);
int codigo_existe(struct registro data, struct registro productos[MAX_REGISTROS]);
void mostrar_datos(int fila_actual, struct registro productos[MAX_REGISTROS]);

// Programa principal/main.
void main()
{
    // Productos en la matriz.
    int _fila_actual = 0;

    // Variable para opción de switch.
    int _opcion = 0;

    struct registro productos[MAX_REGISTROS];
    struct registro data;

    app_cls();

    do
    {
        _opcion = app_menu(_fila_actual);

        switch (_opcion)
        {
        // OPCIÓN 1: carga de productos
        case 1:
            app_cls();

            printf("** Carga de Producto ** \n\n");
            printf("*Ingrese el c%cdigo  ( 0 - exit) : ", 162);

            scanf("%s", &data.codigo);

            if (data.codigo[0] == '0') // Si el código ingresado es igual a 0, nos regresa al menu principal.
            {
                app_cls();
                break;
            }
            else
            { // Si el código ya existe, se muestra el siguiente mensaje:
                if (codigo_existe(data, &productos) == 1)
                {
                    printf("\n El codigo ( %s ) YA EXISTE!!! \n", data.codigo);

                    printf("\n Presione una tecla para continuar... \n");
                    getch();

                    app_cls();
                }
                else
                {
                    // Si no existe, se pide cargar el código.
                    for (int i = 0; i < sizeof(data.codigo); i++)
                    {
                        productos[_fila_actual].codigo[i] = data.codigo[i];
                    }

                    // Se ingresa la descripción.
                    printf("*Ingrese descripci%cn: ", 162);
                    scanf("%s", &data.descripcion);

                    for (int i = 0; i < sizeof(data.descripcion); i++)
                    {
                        productos[_fila_actual].descripcion[i] = data.descripcion[i]; // pedro
                    }

                    // Se ingresa la cantidad de stock.
                    printf("*Ingrese stock : ");
                    scanf("%d", &productos[_fila_actual].stock);

                    mostrar_datos(_fila_actual, &productos);

                    // Incremento índice de existentes en 1.
                    _fila_actual += 1;

                    printf("\n Presione una tecla para continuar... \n");
                    getch();

                    app_cls();
                }
            }

            break;
        // OPCIÓN 2: Modificar stock
        case 2:

            app_cls();

            int indice = -1;

            printf("** Modifica producto ** \n\n");
            printf("* Ingrese el c%cdigo ( 0 - Regresar al men%c ) : ", 162, 163);

            scanf("%s", &data.codigo);

            if (data.codigo[0] == '0') // Si el código ingresado es igual a 0, nos regresa al menu principal.
            {
                break;
            }
            else
            {
                indice = obtener_posicion(data, &productos); // esta función es para verificar si el código existe/no existe

                if (indice < 0)
                {

                    printf("\n El c%cdigo ( %s ) NO EXISTE!!! \n", 162, data.codigo);
                    printf("\n Presione una tecla para continuar... \n");
                    getch();
                }
                else
                {

                    mostrar_datos(indice, &productos);

                    // cargo stock...
                    printf("* Ingrese nuevo stock: ");
                    scanf("%d", &productos[indice].stock);
                }
            }
            app_cls();
            break;

        // OPCIÓN 3: Mostrar productos sin stock.
        case 3:
            app_cls();
            printf("* LISTADO DE PRODUCTOS con stock 0 \n\n");
            printf("* *C%cdigo  *Descripci%cn  *Stock \n\n", 162, 162);

            for (int i = 0; i < _fila_actual; i++)
            {
                if (productos[i].stock == 0)
                {

                    printf("%s", productos[i].codigo);
                    printf("\t");

                    printf("%s", productos[i].descripcion);
                    printf("\t");

                    printf("%d", productos[i].stock);

                    printf("\n");
                }
            }

            printf("\n Presione una tecla para continuar... \n");
            getch();

            app_cls();
            break;
        // OPCIÓN 4: Listar productos.
        case 4:

            app_cls();
            printf("* LISTADO DE PRODUCTOS \n\n");
            printf("* *C%cdigo  *Descripci%cn  *Stock \n\n", 162, 162);

            for (int i = 0; i < _fila_actual; i++)
            {

                printf("%s", productos[i].codigo);
                printf("\t");

                printf("%s", productos[i].descripcion);
                printf("\t");

                printf("%d", productos[i].stock);

                printf("\n");
            }

            printf("\n Presione una tecla para continuar... \n");
            getch();

            app_cls();
            break;

        case 5:
            printf(" Adi%cs!!! :) \n\n", 162);
            break;
        default:

            printf("\n Opci%cn de men%c inv%clida \n", 162, 163, 160, _opcion);
            printf("\n Presione una tecla para continuar... \n");
            getch();
            app_cls();

            _opcion = -1;

            break;
        }

    } while (_opcion != 5);
}

// Limpia la consola
void app_cls()
{
    system("@cls||clear");
}

// Presenta el menu cada vez que sea necesario. Se va a utilizar dentro de switch.
int app_menu(int _existentes)
{
    int resp = 0;

    printf("\n** APP Stock **");

    printf(" (Productos existentes: %d ) \n\n", _existentes);

    printf("1. Cargar Productos\n");
    printf("2. Modificar Stock\n");
    printf("3. Mostrar productos sin stock\n");
    printf("4. Listar productos\n");
    printf("5. Finalizar App\n");

    printf("\n Ingrese su elecci%cn:", 162);

    scanf("%d", &resp);

    return resp;
}

// Devuelve la fila en la tabla del código del producto  // Es para saber si el código existe/no existe
int obtener_posicion(struct registro data, struct registro productos[MAX_REGISTROS])
{
    int resp = -1; // no encontrado

    for (int i = 0; i < MAX_REGISTROS; i++) // Recorre las filas
    {
        resp = i;

        for (int j = 0; j < sizeof(data.codigo); j++) // recorre 2da dimensión o columnas.
        {
            if (data.codigo[j] != productos[i].codigo[j])
            {
                // todo coincide ?
                // entones "i" es la posicion...
                resp = -1;
                break;
            }
        }

        if (resp != -1)
        {
            break;
        }
    }
    return resp;
}

// Existe el código en la lista?
int codigo_existe(struct registro data, struct registro productos[MAX_REGISTROS])
{
    int resp = -1;

    for (int i = 0; i < MAX_REGISTROS; i++)
    {
        resp = 1;

        for (int j = 0; j < sizeof(data.codigo); j++)
        {
            if (data.codigo[j] != productos[i].codigo[j])
            {
                resp = -1;
                break;
            }
        }

        if (resp == 1)
        {
            break;
        }
    }

    return resp;
}

// Hace un printf de los datos
void mostrar_datos(int fila_actual, struct registro productos[MAX_REGISTROS])
{
    app_cls();

    printf("\n Datos producto \n");
    printf("----------------- \n");
    printf("C%cdigo : %s \n", 162, productos[fila_actual].codigo);
    printf("Nombre : %s \n", productos[fila_actual].descripcion);
    printf("Stock  : %d \n", productos[fila_actual].stock);
}