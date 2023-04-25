#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int iteracion = 0;
struct Tarea
{
    int TareaID;       // Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} typedef Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *inicilizarLista();
Tarea NuevaTarea(char *buff);
Nodo *CrearNodo(Tarea nTarea);
void controlarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas, Nodo **tareasEnProceso);
void agregarTareaAlinicio(Nodo **tarea, Tarea nTarea); //
void listarTareas(Nodo *tareas);
void AgregarTarea_A_OtraLista(Nodo **lista, Nodo *tarea);
Nodo *BuscaTareaPorPalabra(Nodo *tareasPendientes, Nodo *tareasRealizadas, Nodo *tareasEnProceso, char *buff);
Nodo *BuscaTareaPorId(Nodo *tareasPendientes, Nodo *tareasRealizadas, Nodo *tareasEnProceso);
void mostraTareaUnica(Nodo *tarea);
void liberMemoriaGeneral(Nodo *tarea);
void menu(Nodo **tareasPendientess, Nodo **tareasRealizadass, Nodo **tareasEnProcesoo, char *buff);
void EliminarTarea(Nodo *tarea);
void MostrarDatos(Nodo *lista);
Nodo *QuitarTarea(Nodo **lista, int id);
void MoverTareas(Nodo **tareasPendientess, Nodo **tareasRealizadass, Nodo **tareasEnProcesoo, Nodo *Mover, int bandera);

//>>>>>>>>>>>>>>>>><<   AQUI MAIN >>>>>>>>>>>>>>>>>>>>>>>>>>>>

int main(void)
{
    char *buff = (char *)malloc(sizeof(char) * 100);
    int opcion;
    Nodo *tareasPendientes = inicilizarLista();
    Nodo *tareasRealizadas = inicilizarLista();
    Nodo *tareasEnProceso = inicilizarLista();
    menu(&tareasPendientes, &tareasRealizadas, &tareasEnProceso, buff);
    liberMemoriaGeneral(tareasPendientes);
    liberMemoriaGeneral(tareasRealizadas);
    free(buff);
    return 0;
}

// >>>>>>>>>>>>>>>>>> FIN MAIN >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

Nodo *inicilizarLista()
{
    return (NULL);
}

/////   FUNCIONES NUEVAS ////
void agregarTareaAlinicio(Nodo **tarea, Tarea nTarea)
{
    Nodo *NuevaTarea;
    NuevaTarea = CrearNodo(nTarea);
    NuevaTarea->Siguiente = *tarea;
    *tarea = NuevaTarea;
}

Nodo *CrearNodo(Tarea nTarea)
{
    Nodo *NuevoNodo;
    NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    NuevoNodo->T = nTarea;
    NuevoNodo->Siguiente = NULL;
    return NuevoNodo;
}

Tarea NuevaTarea(char *buff)
{
    Tarea nTarea;
    int duracion;
    printf("ingrese la descripcion de la tarea %d: \n",iteracion+1);
    fflush(stdin);
    gets(buff);
    nTarea.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(nTarea.Descripcion, buff);
    fflush(stdin);
    printf("Ingrese el tiempo de duracion de la Tarea : \n");
    scanf("%d",&duracion);
    nTarea.Duracion = duracion;
    nTarea.TareaID = iteracion+1;
    iteracion++;
    return nTarea;
}

void controlarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas, Nodo **tareasEnProceso)
{
    Nodo *auxTareasPendientes = *tareasPendientes;
    Nodo *auxTareasRealizadas = *tareasRealizadas;
    Nodo *auxtareasEnProceso = *tareasEnProceso;
    Nodo *Eliminar, *Mover;
    int id, bandera = 0;
    int operacion;
    puts("\nCONTROL DE TAREAS");
    do
    {
        puts("\n\tTAREAS PENDIENTES\n\n");
        listarTareas(*tareasPendientes);
        puts("\n\tTAREAS REALIZADAS\n\n");
        listarTareas(*tareasRealizadas);
        puts("\n\tTAREAS EN PROCESO\n\n");
        listarTareas(*tareasEnProceso);
        puts("\nindique el ID de la tarea a modificar");
        fflush(stdin);
        scanf("%d", &id);
        printf("\nindique la operacion (1 = eliminar, 2 = mover, 3 = nada ): ");
        fflush(stdin);
        scanf("%d", &operacion);

        if (operacion == 1)
        {
            Eliminar = QuitarTarea(tareasPendientes, id);

            if (Eliminar == NULL)
                Eliminar = QuitarTarea(tareasEnProceso, id);

            if (Eliminar == NULL)
                Eliminar = QuitarTarea(tareasRealizadas, id);

            EliminarTarea(Eliminar);
        }
        else
        {
            if (operacion == 2)
            {
                Mover = QuitarTarea(tareasPendientes, id);

                if (Mover == NULL)
                {
                    Mover = QuitarTarea(tareasEnProceso, id);
                    bandera++;
                }

                if (Mover == NULL)
                {

                    Mover = QuitarTarea(tareasRealizadas, id);
                    bandera++;
                }

                MoverTareas(tareasPendientes, tareasRealizadas, tareasEnProceso, Mover, bandera);
                bandera = 0;
            }
        }
        puts("\nDesea Modificar otra tarea ( si=1  0=no )");
        fflush(stdin);
        scanf("%d", &operacion);
    } while (operacion == 1);
}

void listarTareas(Nodo *tareas)
{
    Nodo *auxTareas = tareas;
    int bandera = 0;
    while (auxTareas != NULL)
    {
        printf("\nID tarea: %d\n", auxTareas->T.TareaID);
        printf("Descripcion: %s\n", auxTareas->T.Descripcion);
        printf("Duracion: %d min\n", auxTareas->T.Duracion);
        auxTareas = auxTareas->Siguiente;
        puts("===============================");
        bandera++;
    }
    if (bandera == 0)
    {
        printf("\t\tSin Tareas\n");
    }
}
void AgregarTarea_A_OtraLista(Nodo **Lista, Nodo *tarea)
{
    tarea->Siguiente = *Lista;
    *Lista = tarea;
    puts("movimiento Exitoso");
}

Nodo *BuscaTareaPorId(Nodo *tareasPendientes, Nodo *tareasRealizadas, Nodo *tareasEnProceso)
{
    Nodo *auxPendientes = tareasPendientes;
    Nodo *auxRealizadas = tareasRealizadas;
    Nodo *auxEnProceso = tareasEnProceso;
    int id;
    printf("\nIgrese el id a buscar: ");
    fflush(stdin);
    scanf("%d", &id);

    while (auxPendientes != NULL)
    {
        if (id == auxPendientes->T.TareaID)
        {
            return (auxPendientes);
        }
        auxPendientes = auxPendientes->Siguiente;
    }

    while (auxRealizadas != NULL)
    {
        if (auxRealizadas->T.TareaID == id)
        {
            return (auxRealizadas);
        }
        auxRealizadas = auxRealizadas->Siguiente;
    }
    while (auxEnProceso != NULL)
    {
        if (id == auxEnProceso->T.TareaID)
        {
            return (auxEnProceso);
        }
        auxEnProceso = auxEnProceso->Siguiente;
    }
    return (NULL);
}
Nodo *BuscaTareaPorPalabra(Nodo *tareasPendientes, Nodo *tareasRealizadas, Nodo *tareasEnProceso, char *buff)
{
    Nodo *auxPendientes = tareasPendientes;
    Nodo *auxRealizadas = tareasRealizadas;
    Nodo *auxEnProceso = tareasEnProceso;
    puts("\ningrese la una palabra clave a buscar: ");
    fflush(stdin);
    gets(buff);

    while (auxPendientes != NULL)
    {
        if (strstr(auxPendientes->T.Descripcion, buff) != NULL)
        {
            return (auxPendientes);
        }
        auxPendientes = auxPendientes->Siguiente;
    }

    while (tareasRealizadas != NULL)
    {
        if (strstr(tareasRealizadas->T.Descripcion, buff) != NULL)
        {
            return (tareasRealizadas);
        }
        tareasRealizadas = tareasRealizadas->Siguiente;
    }
    while (auxEnProceso != NULL)
    {
        if (strstr(auxEnProceso->T.Descripcion, buff) != NULL)
        {
            return (auxEnProceso);
        }
        auxEnProceso = auxEnProceso->Siguiente;
    }
    return (NULL);
}

void mostraTareaUnica(Nodo *tarea)
{
    if (tarea != NULL)
    {
        printf("\n\tTarea encontrada\n");
        printf("ID: %d\n", tarea->T.TareaID);
        printf("Descripcion: %s\n", tarea->T.Descripcion);
        printf("Duracion: %d min\n", tarea->T.Duracion);
    }
    else
    {
        puts("\nID o Palabra clave no encontrada/o\n");
    }
}

void liberMemoriaGeneral(Nodo *tarea)
{
    Nodo *auxTarea = tarea;
    Nodo *TareaAnterior = tarea;
    Nodo *TareaActual = tarea;
    while (auxTarea != NULL) // libero las descripciones
    {
        if (auxTarea->T.Descripcion != NULL)
        {
            free(auxTarea->T.Descripcion);
        }
        auxTarea = auxTarea->Siguiente;
    }

    while (TareaActual != NULL) // libero los nodos
    {
        TareaAnterior = TareaActual;
        TareaActual = TareaActual->Siguiente;
        free(TareaAnterior);
    }
}
void MostrarDatos(Nodo *lista)
{
    Nodo *auxLista = lista;
    int CantTareas = 0;
    int CantTiempo = 0;
    while (auxLista != NULL)
    {
        CantTareas++;
        CantTiempo += auxLista->T.Duracion;
        auxLista = auxLista->Siguiente;
    }
    printf("Cantidad de Tareas: %d\n", CantTareas);
    printf("Tiempo total: %d min \n", CantTiempo);
}
void EliminarTarea(Nodo *tarea)
{
    if (tarea != NULL)
    {
        if (tarea->T.Descripcion)
            free(tarea->T.Descripcion);
        free(tarea); // se elimina el nodo
        puts("\nEliminacion Exitosa");
    }
    if (tarea == NULL)
        puts("\nError al eliminar, La tarea no existe!");
}

void menu(Nodo **tareasPendientess, Nodo **tareasRealizadass, Nodo **tareasEnProcesoo, char *buff)
{
    Nodo *tareasPendientes = *tareasPendientess;
    Nodo *tareasRealizadas = *tareasRealizadass;
    Nodo *tareasEnProceso = *tareasEnProcesoo;
    Nodo *busquedaID;
    Nodo *busquedaPorPalabra;
    int opcion;
    do
    {
        puts("\n\n\t\t\t(1)- Agreagar una nueva tarea");
        puts("\t\t\t(2)- controlar tareas");
        puts("\t\t\t(3)- listar tareas");
        puts("\t\t\t(4)- Buscar Tareas por Id");
        puts("\t\t\t(5)- Buscar Tareas por palabra clave");
        puts("\t\t\t(6)- Info General de las 3 listas");
        puts("\t\t\t(7)- salir");
        fflush(stdin);
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            do
            {
                Tarea nTarea = NuevaTarea(buff);
                agregarTareaAlinicio(&tareasPendientes, nTarea);
                puts("Desea agregar otra Tarea (Si=1 o No=0)");
                fflush(stdin);
                scanf("%d", &opcion);

            } while (opcion == 1);

            break;
        case 2:
            controlarTareas(&tareasPendientes, &tareasRealizadas, &tareasEnProceso);
            break;
        case 3:
            puts("\tTAREAS PENDIENTES\n");
            listarTareas(tareasPendientes);
            puts("\n\n\tTAREAS REALIZADAS\n\n");
            listarTareas(tareasRealizadas);
            puts("\n\n\tTAREAS EN PROCESO\n\n");
            listarTareas(tareasEnProceso);
            break;
        case 4:
            busquedaID = BuscaTareaPorId(tareasPendientes, tareasRealizadas, tareasEnProceso);
            mostraTareaUnica(busquedaID);

            break;
        case 5:

            busquedaPorPalabra = BuscaTareaPorPalabra(tareasPendientes, tareasRealizadas, tareasEnProceso, buff);
            mostraTareaUnica(busquedaPorPalabra);
            break;
        case 6:
            puts("\tTAREAS PENDIENTES\n");
            MostrarDatos(tareasPendientes);
            puts("\n\n\tTAREAS REALIZADAS\n\n");
            MostrarDatos(tareasRealizadas);
            puts("\n\n\tTAREAS EN PROCESO\n\n");
            MostrarDatos(tareasEnProceso);
            break;
        }

    } while (opcion != 7);
}

Nodo *QuitarTarea(Nodo **lista, int id)
{
    Nodo *auxTareaActual = *lista;
    Nodo *auxTareaAnterior = *lista;

    while (auxTareaActual != NULL && auxTareaActual->T.TareaID != id)
    {
        auxTareaAnterior = auxTareaActual;
        auxTareaActual = auxTareaActual->Siguiente;
    }
    if (auxTareaActual != NULL)
    {
        if (*lista == auxTareaActual)
        {
            *lista = auxTareaActual->Siguiente;
        }
        else
        {
            auxTareaAnterior->Siguiente = auxTareaActual->Siguiente;
        }
        auxTareaActual->Siguiente = NULL;
    }

    return auxTareaActual; // retorna el nodo que se va a sacar;
}
void MoverTareas(Nodo **tareasPendientess, Nodo **tareasRealizadass, Nodo **tareasEnProcesoo, Nodo *Mover, int bandera)
{
    int opcionlista;
    switch (bandera)
    {
    case 0:
        puts("\nindique a que lista desea mover (1 = Tareas en Proceso, 2 = Tareas Realizadas )");
        scanf("%d", &opcionlista);

        if (opcionlista == 1)
        {
            AgregarTarea_A_OtraLista(tareasEnProcesoo, Mover);
        }
        else
        {
            if (opcionlista == 2)
            {
                AgregarTarea_A_OtraLista(tareasRealizadass, Mover);
            }
        }

        break;
    case 1:
        puts("\nindique a que lista desea mover (1 = Tareas Pendientes, 2 = Tareas Realizadas )");
        scanf("%d", &opcionlista);
        if (opcionlista == 1)
        {
            AgregarTarea_A_OtraLista(tareasPendientess, Mover);
        }
        else
        {
            if (opcionlista == 2)
            {
                AgregarTarea_A_OtraLista(tareasRealizadass, Mover);
            }
        }
        break;
    case 2:
        puts("\nindique a que lista desea mover (1 = Tareas en Proceso, 2 = Tareas Pendientes )");
        scanf("%d", &opcionlista);
        if (opcionlista == 1)
        {
            AgregarTarea_A_OtraLista(tareasEnProcesoo, Mover);
        }
        else
        {
            if (opcionlista == 2)
            {
                AgregarTarea_A_OtraLista(tareasPendientess, Mover);
            }
        }
        break;
    }
}