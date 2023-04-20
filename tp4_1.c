#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
};

void CargarTarea(struct Tarea **ListaTareas, int num);
void mostrarTarea(struct Tarea **ListaTareas, int num);
void BuscarTarea(struct Tarea **ListaTareas, int cantidadT, int idBuscado);
struct Tarea *buscarTareaPorDescripcion(struct Tarea **ListaTareas, int cantidadT, char *pClave);
void PendientesORealizadas(struct Tarea **ListaTareas, struct Tarea **tareasRealizadas, struct Tarea **tareasPendientes, int CantidadT, int numTRealizadas, int numTPendientes);

int main()
{

    int cantidadT, numTRealizadas = 0, numTPendientes = 0;

    char pClave[100];
    struct Tarea *porID = NULL;
    struct Tarea *porDescripcion = NULL;

    printf("indique cuantas tareas desea realizar:  ");
    scanf("%d", &cantidadT);
    fflush(stdin);
    struct Tarea **tareasRealizadas = (struct Tarea **)malloc(cantidadT * sizeof(struct Tarea *));
    struct Tarea **tareasPendientes = (struct Tarea **)malloc(cantidadT * sizeof(struct Tarea *));

    struct Tarea **ListaTareas = (struct Tarea **)malloc(cantidadT * sizeof(struct Tarea *));
    if (ListaTareas == NULL)
    {
        printf("No se pudo asignar memoria");
        return 1;
    }
    // Inicializa las tareas
    for (int i = 0; i < cantidadT; i++)
    {
        ListaTareas[i] = NULL;
    }

    // Carga de Tareas
    for (int i = 0; i < cantidadT; i++)
    {
        printf("Tarea #%d: \n", i + 1);
        CargarTarea(ListaTareas, i);
    }
    printf("\n");
    // mostrar Lista de Tareas
    for (int i = 0; i < cantidadT; i++)
    {
        mostrarTarea(ListaTareas, i);
    }
    printf("\n");
    // Mostrar la lista de Tareas y mover a un nuevo arreglo las Tareas ya completadas

    int idBuscado;
    printf("\nIngrese el Nro de tarea buscado: \t");
    scanf("%d", &idBuscado);

    // Buscar una tarea de la lista por id

    BuscarTarea(ListaTareas, cantidadT, idBuscado);
    PendientesORealizadas(ListaTareas, tareasRealizadas, tareasPendientes, cantidadT, numTRealizadas, numTPendientes);

    // Buscar una tarea de la lista por id
    printf("Ingrese una palabra clave para realizar la busqueda de Tarea/s: ");
    scanf("%s", &pClave);
    fflush(stdin);
    porDescripcion = buscarTareaPorDescripcion(ListaTareas, cantidadT, pClave);
    if (porDescripcion != NULL)
    {

        printf("Tarea Buscada por palabra: \n");
        printf("ID: %d \n", porDescripcion->TareaID);
        printf("Descripcion: %s \n", porDescripcion->Descripcion);
        printf("Duracion: %d \n", porDescripcion->Duracion);
    }
    else
    {
        printf("Tarea no encontrada \n");
    }

    // Enlistar las Tareas e ir Preguntando si la Tarea se realizó o no e ir sumando al contador de tareas realizadas o pendientes

    // Liberamos la memoria reservada para cada uno de los strings
    for (int i = 0; i < cantidadT; i++)
    {
        free(ListaTareas[i]->Descripcion); // Liberar memoria de la descripción
        free(ListaTareas[i]);
        free(tareasPendientes[i]);
        free(tareasRealizadas[i]);
    }
    free(ListaTareas);
    free(tareasRealizadas);
    free(tareasRealizadas);

    return 0;
}

void CargarTarea(struct Tarea **ListaTareas, int cantidadT)
{
    char Descripcion[100];
    ListaTareas[cantidadT] = (struct Tarea *)malloc(sizeof(struct Tarea));
    fflush(stdin);
    printf("Ingrese la descripcion de la Tarea: \n");
    fflush(stdin);
    scanf("%s", Descripcion);
    ListaTareas[cantidadT]->Descripcion = (char *)malloc(sizeof(Descripcion) + 1); // Reservamos memoria para un string con el mismo tamaño de la descripcion
    strcpy(ListaTareas[cantidadT]->Descripcion, Descripcion);                      // Leemos el nombre del usuario y lo almacenamos en el vector de punteros
    printf("Ingrese la duracion de la tarea (entre 10-100 min): \n");
    fflush(stdin);
    scanf("%d", &ListaTareas[cantidadT]->Duracion);
    ListaTareas[cantidadT]->TareaID=+1;
}

void mostrarTarea(struct Tarea **ListaTareas, int cantidadT)
{
    printf("\nLos Tareas asignadas son:\n");
    printf("ID: %d\n", ListaTareas[cantidadT]->TareaID);
    printf("Descripcion: %s\n", ListaTareas[cantidadT]->Descripcion);
    printf("Duracion: %d\n", ListaTareas[cantidadT]->Duracion);
}

void BuscarTarea(struct Tarea **ListaTareas, int cantidadT, int idBuscado)
{

    for (int i = 0; i < cantidadT; i++)
    {

        if (ListaTareas[i]->TareaID == idBuscado)
        {
            printf("Tarea encontrada: \n");
            printf("ID: %d \n", ListaTareas[i]->TareaID);
            printf("Descripcion: %s \n", ListaTareas[i]->Descripcion);
            printf("Duracion: %d \n", ListaTareas[i]->Duracion);
        }
    }
}

struct Tarea *buscarTareaPorDescripcion(struct Tarea **ListaTareas, int cantidadT, char *pClave)
{

    int encontradas = 0;
    for (int i = 0; i < cantidadT; i++)
    {
        if (ListaTareas[i] != NULL)
        {
            if (strstr(ListaTareas[i]->Descripcion, pClave) != NULL)
            {
                return (ListaTareas[i]);
                encontradas++;
            }
        }

        if (encontradas == 0)
        {
            printf("No se encontraron tareas con la descripcion \"%s\"\n", pClave);
        }
        else
        {
            printf("Se encontraron %d tarea(s) con la descripcion \"%s\"\n", encontradas, pClave);
        }
    }
}
void PendientesORealizadas(struct Tarea **ListaTareas, struct Tarea **tareasRealizadas, struct Tarea **tareasPendientes, int CantidadT, int numTRealizadas, int numTPendientes)
{
    for (int i = 0; i < CantidadT; i++)
    {

        printf("\nTarea Nro: %d, Descripcion: %s, Duracion:  %d \n ", ListaTareas[i]->TareaID, ListaTareas[i]->Descripcion, ListaTareas[i]->Duracion);

        char respuesta[10];
        printf("Se realizo la tarea %d (Si/No): ", i + 1);
        scanf("%s", respuesta);

        if (strcmp(respuesta, "Si") == 0 || strcmp(respuesta, "si") == 0 || strcmp(respuesta, "SI") == 0 || strcmp(respuesta, "sI") == 0)
        {
            tareasRealizadas[i]->TareaID = ListaTareas[i]->TareaID;
            tareasRealizadas[i]->Descripcion = ListaTareas[i]->Descripcion;
            tareasRealizadas[i]->Duracion = ListaTareas[i]->Duracion;
            numTRealizadas++;
            ListaTareas[i] = NULL;
            printf("\nLa Tareas realizadas son : \n Tarea Nro %d -- Descripcion: %s -- Duracion:  %d\n ", tareasRealizadas[i]->TareaID, tareasRealizadas[i]->Descripcion, tareasRealizadas[i]->Duracion);
        }
        else if (strcmp(respuesta, "No") == 0 || strcmp(respuesta, "no") == 0 || strcmp(respuesta, "NO") == 0 || strcmp(respuesta, "No") == 0)
        {
            tareasPendientes[i]->TareaID = ListaTareas[i]->TareaID;
            tareasPendientes[i]->Descripcion = ListaTareas[i]->Descripcion;
            tareasPendientes[i]->Duracion = ListaTareas[i]->Duracion;
            numTPendientes++;
            ListaTareas[i] = NULL;

            printf("\nLa Tareas Pendientes son :\n  Tarea Nro %d -- Descripcion: %s -- Duracion:  %d\n ", tareasPendientes[i]->TareaID, tareasPendientes[i]->Descripcion, tareasPendientes[i]->Duracion);
        }
    }
}