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
struct Tarea* BuscarTareaporID(struct Tarea **tareas, int num, int idBuscado);
struct Tarea* buscarTareaPorDescripcion(struct Tarea **tareas, int num, char *pClave);
void PendientesORealizadas(struct Tarea **ListaTareas, struct Tarea **tareasRealizadas, int CantidadT, int numTRealizadas);

int main()
{

    int cantidadT, numTRealizadas, consulta, PendORea, IDoPclave, idBuscado;

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
        printf("Tarea ID #%d: \n", i + 1);
        CargarTarea(ListaTareas, i);
    }
    printf("\n");
    // mostrar Lista de Tareas
    printf("\nLos Tareas asignadas son:\n");
    for (int i = 0; i < cantidadT; i++)
    {
        mostrarTarea(ListaTareas, i);
    }
    printf("\n");

    fflush(stdin);

    // Enlistar las Tareas e ir Preguntando si la Tarea se realizó o no e ir sumando al contador de tareas realizadas o pendientes
    PendientesORealizadas(ListaTareas, tareasRealizadas, cantidadT, numTRealizadas);

    // Mostrar la lista de Tareas Pendientes de realizar luego de mover a un nuevo arreglo las ya finalizadas
    printf("\nLos Tareas aun Pendientes de realizar son:\n");
        for (int i = 0; i < cantidadT; i++){
        if (ListaTareas[i]!=NULL){
            mostrarTarea(ListaTareas,i);
        }
    }
    printf("Consultar tareas(1-Si,2-No): ");
    scanf("%d", &consulta);
    fflush(stdin);
    while (consulta == 1 && consulta != 0)
    {
        printf("Consultar de las realizadas(1) o pendientes(0): ");
        scanf("%d", &PendORea);
        fflush(stdin);
        printf("Consultar por ID(1) o por Palabra(0): ");
        scanf("%d", &IDoPclave);
        fflush(stdin);
        switch (IDoPclave)
        {
        case 0:
            printf("Ingrese la palabra a buscar: ");
            scanf("%s", &pClave);
            switch (PendORea)
            {
            case 0:
                porDescripcion = buscarTareaPorDescripcion(ListaTareas, cantidadT, pClave);
                break;
            case 1:
                porDescripcion = buscarTareaPorDescripcion(tareasRealizadas, cantidadT, pClave);
                break;
            }
            if (porDescripcion != NULL)
            {
                printf("Tarea buscada por palabra: \n");
                printf("ID: %d\n", porDescripcion->TareaID);
                printf("Descripcion: %s\n",porDescripcion->Descripcion);
                printf("Duracion: %d\n", porDescripcion->Duracion);
            }
            else
            {
                printf("Tarea no encontrada\n");
            }
            break;
        case 1:
            printf("Ingrese el ID de la tarea a buscar: ");
            scanf("%d", &idBuscado);
            fflush(stdin);
            switch (PendORea)
            {
            case 0:
                porID = BuscarTareaporID(ListaTareas, cantidadT, idBuscado);
                break;
            case 1:
                porID = BuscarTareaporID(tareasRealizadas, cantidadT, idBuscado);
                break;
            }
            if (porID != NULL)
            {
                printf("Tarea buscada por ID: \n");
                printf("ID: %d\n", porID->TareaID);
                printf("Descripcion: %s\n", porID->Descripcion);
                printf("Duracion: %d\n", porID->Duracion);
            }
            else
            {
                printf("\nTarea no encontrada\n");
            }
            break;
        default:
            printf("\nIngrese la opcion correcta\n");
            break;
        }
        printf("Consultar otra tarea(1-Si,2-No): ");
        scanf("%d", &consulta);
        fflush(stdin);
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
    ListaTareas[cantidadT]->TareaID = cantidadT + 1;
}

void mostrarTarea(struct Tarea **ListaTareas, int cantidadT)
{

    printf("ID: %d\n", ListaTareas[cantidadT]->TareaID);
    printf("Descripcion: %s\n", ListaTareas[cantidadT]->Descripcion);
    printf("Duracion: %d\n", ListaTareas[cantidadT]->Duracion);
}

struct Tarea* buscarTareaPorDescripcion(struct Tarea **tareas, int num, char *pClave){
   for (int i = 0; i < num; i++){
    if (tareas[i]!=NULL){
        if (strstr(tareas[i]->Descripcion, pClave) != NULL){
            return(tareas[i]);
        }
    }
   }
return NULL;
}

struct Tarea* BuscarTareaporID(struct Tarea **tareas, int num, int idBuscado){
   for (int i = 0; i < num; i++){
    if (tareas[i]!=NULL){
        if (tareas[i]->TareaID==idBuscado){
        return(tareas[i]);
        }
    }
   }
return NULL;
}
void PendientesORealizadas(struct Tarea **ListaTareas, struct Tarea **tareasRealizadas, int CantidadT, int numTRealizadas)
{

    for (int i = 0; i < CantidadT; i++)
    {

        printf("\nTarea Nro: %d, Descripcion: %s, Duracion:  %d \n ", ListaTareas[i]->TareaID, ListaTareas[i]->Descripcion, ListaTareas[i]->Duracion);

        char respuesta[10];
        printf("Se realizo la tarea %d (Si/No): ", i + 1);
        fflush(stdin);
        scanf("%s", &respuesta);

        if (strcmp(respuesta, "Si") == 0 || strcmp(respuesta, "si") == 0 || strcmp(respuesta, "SI") == 0 || strcmp(respuesta, "sI") == 0)
        {
            tareasRealizadas[numTRealizadas] = (struct Tarea *)malloc(sizeof(struct Tarea));
            tareasRealizadas[numTRealizadas] = ListaTareas[i];
            numTRealizadas++;
            ListaTareas[i] = NULL;
        }

    }
    printf("Tareas realizadas: \n");
    for (int i = 0; i < numTRealizadas; i++)
    {
        printf("ID: %d\n", tareasRealizadas[i]->TareaID);
        printf("Descripcion: %s\n", tareasRealizadas[i]->Descripcion);
        printf("Duracion: %d\n", tareasRealizadas[i]->Duracion);
    }
    printf("\n");
}