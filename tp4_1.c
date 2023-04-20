#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
};

// 1. Desarrollar una interfaz por consola donde se solicite al usuario (es decir el
// empleado) cuantas tareas debe cargar.
// 2. Tendrá que generar un arreglo de doble punteros dinámicamente del tipo Tarea
// con la cantidad de tareas solicitadas en el punto anterior.Recuerde inicializar
// los arreglos apuntando a NULL.
void BuscarTarea(struct Tarea **ListaTareas, int cantidadT, int idBuscado);
void buscarTareaPorDescripcion(struct Tarea **ListaTareas, int cantidadT,char *pClave);
int main()
{

    int cantidadT;
    char Descripcion[100];
    char pClave[100];
    int numTareasRealizadas = 0;
    int numTareasPendientes = 0;

    printf("indique cuantas tareas desea realizar:  ");
    +scanf("%d", &cantidadT);

    struct Tarea **ListaTareas = (struct Tarea **)malloc(cantidadT * sizeof(struct Tarea *));

    if (ListaTareas == NULL)
    {
        printf("No se pudo asignar memoria");
        return 1;
    }

    for (int i = 0; i < cantidadT; i++)
    {
        ListaTareas[i] = NULL;
    }

    // Carga de Tareas
    for (int i = 0; i < cantidadT; i++)
    {
        ListaTareas[i] = (struct Tarea *)malloc(sizeof(struct Tarea));
        ListaTareas[i]->TareaID = i + 1;
        printf("Tarea Nro #%d: \n", ListaTareas[i]->TareaID);
        printf("Ingrese la descripcion de la Tarea Nro%d : \n", ListaTareas[i]->TareaID);
        scanf("%s", Descripcion);
        ListaTareas[i]->Descripcion = (char *)malloc(sizeof(Descripcion)+1); // Reservamos memoria para un string con el mismo tamaño de la descripcion

        if (ListaTareas[i]->Descripcion == NULL)
        {
            printf("No se pudo asignar memoria");
            return 1;
        }
        strcpy(ListaTareas[i]->Descripcion, Descripcion);                            // Leemos el nombre del usuario y lo almacenamos en el vector de punteros
        printf("Ingrese la duracion de la tarea (10-100): \n");
        scanf("%d", &ListaTareas[i]->Duracion);
    }

    // mostrar Lista de Tareas

    // Mostrar la lista de Tareas y mover a un nuevo arreglo las Tareas ya completadas
    struct Tarea **tareasRealizadas = (struct Tarea **)malloc(cantidadT * sizeof(struct Tarea *));
    struct Tarea **tareasPendientes = (struct Tarea **)malloc(cantidadT * sizeof(struct Tarea *));

    printf("\nLos Tareas asignadas son:\n");
    for (int i = 0; i < cantidadT; i++)
    {
        printf("Tarea Nro %d: \n", i + 1);                         // Imprimimos el nro de cada tarea
        printf("Descripcion:  %s\n", ListaTareas[i]->Descripcion); // Imprimimos La Descripcion de cada tarea
        printf("Duracion:  %d\n", ListaTareas[i]->Duracion);       // Imprimimos la duracion de cada tarea
    }

    int idBuscado;
    printf("\nIngrese el Nro de tarea buscado: \t");
    scanf("%d", &idBuscado);

    // Buscar una tarea de la lista

    BuscarTarea(ListaTareas, cantidadT, idBuscado);
    
    
    printf("Ingrese una palabra clave para realizar la busqueda de Tarea/s: ");
    scanf("%s",&pClave);
    buscarTareaPorDescripcion(ListaTareas, cantidadT, pClave);
    
    
    
    
    
    
    // Enlistar las Tareas e ir Preguntando si la Tarea se realizó o no e ir sumando al contador de tareas realizadas o pendientes
    for (int i = 0; i < cantidadT; i++)
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
            numTareasRealizadas++;
            ListaTareas[i] = NULL;
            printf("\nLa Tareas realizadas son : \n Tarea Nro %d -- Descripcion: %s -- Duracion:  %d\n ", tareasRealizadas[i]->TareaID, tareasRealizadas[i]->Descripcion, tareasRealizadas[i]->Duracion);
        }
        else if (strcmp(respuesta, "No") == 0 || strcmp(respuesta, "no") == 0 || strcmp(respuesta, "NO") == 0 || strcmp(respuesta, "No") == 0)
        {
            tareasPendientes[i]->TareaID = ListaTareas[i]->TareaID;
            tareasPendientes[i]->Descripcion = ListaTareas[i]->Descripcion;
            tareasPendientes[i]->Duracion = ListaTareas[i]->Duracion;
            numTareasPendientes++;
            ListaTareas[i] = NULL;

            printf("\nLa Tareas Pendientes son :\n  Tarea Nro %d -- Descripcion: %s -- Duracion:  %d\n ", tareasPendientes[i]->TareaID, tareasPendientes[i]->Descripcion, tareasPendientes[i]->Duracion);
        }
    }

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


void buscarTareaPorDescripcion(struct Tarea **ListaTareas, int cantidadT,char *pClave)
{
    int encontradas = 0;

    for (int i = 0; i < cantidadT; i++)
    {
        if (strstr((*ListaTareas)[i].Descripcion, pClave) != NULL)
        {
            printf("Tarea ID: %d\n", ListaTareas[i]->TareaID);
            printf("Descripcion: %s\n", ListaTareas[i]->Descripcion);
            printf("Duracion: %d\n", ListaTareas[i]->Duracion);
            printf("---------------------\n");
            encontradas++;
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