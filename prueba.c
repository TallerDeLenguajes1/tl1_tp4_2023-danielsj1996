#include <stdio.h>
#include <string.h>

struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
};

// Función para buscar una tarea por descripción
void buscarTareaPorDescripcion(struct Tarea tareas[], int numTareas, const char *descripcion)
{
    int encontradas = 0;

    for (int i = 0; i < numTareas; i++)
    {
        if (strstr(tareas[i].Descripcion, descripcion) != NULL)
        {
            printf("Tarea ID: %d\n", tareas[i].TareaID);
            printf("Descripción: %s\n", tareas[i].Descripcion);
            printf("Duración: %d\n", tareas[i].Duracion);
            printf("---------------------\n");
            encontradas++;
        }
    }

    if (encontradas == 0)
    {
        printf("No se encontraron tareas con la descripción \"%s\"\n", descripcion);
    }
    else
    {
        printf("Se encontraron %d tarea(s) con la descripción \"%s\"\n", encontradas, descripcion);
    }
}

int main()
{
    // Ejemplo de arreglo de tareas
    struct Tarea tareas[] = {
        {1, "Realizar informe", 50},
        {2, "Enviar correo", 20},
        {3, "Revisar código", 30},
        {4, "Hacer presentación", 40},
        {5, "Planificar proyecto", 60},
    };

    int numTareas = sizeof(tareas) / sizeof(tareas[0]);

    // Realizar búsqueda por descripción
    buscarTareaPorDescripcion(tareas, numTareas, "correo");

    return 0;
}