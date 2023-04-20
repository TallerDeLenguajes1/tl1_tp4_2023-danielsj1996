#include <stdio.h>
#include <stdlib.h>

struct Tarea {
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
};

// Función para buscar una tarea por su número de ID
struct Tarea* BuscarTarea(struct Tarea** tareas, int numTareas, int idBuscado) {
    struct Tarea* tareaEncontrada = NULL; // Se inicializa con NULL para indicar que la tarea no se encontró
    
    for (int i = 0; i < numTareas; i++) {
        if ((*tareas)[i].TareaID == idBuscado) {
            tareaEncontrada = &((*tareas)[i]); // Se obtiene la dirección de memoria de la tarea encontrada
            break; // Se sale del bucle una vez que se encuentra la tarea
        }
    }
    
    return tareaEncontrada;
}

int main() {
    // Ejemplo de uso de la función BuscarTarea
    
    // Se crea un arreglo de tareas
    struct Tarea tareas[3];
    
    // Se asignan valores a las tareas
    tareas[0].TareaID = 1;
    tareas[0].Descripcion = "Tarea 1";
    tareas[0].Duracion = 30;
    
    tareas[1].TareaID = 2;
    tareas[1].Descripcion = "Tarea 2";
    tareas[1].Duracion = 50;
    
    tareas[2].TareaID = 3;
    tareas[2].Descripcion = "Tarea 3";
    tareas[2].Duracion = 20;
    
    // Se crea un puntero doble a las tareas
    struct Tarea** punteroTareas = (struct Tarea**)&tareas;
    
    // Se busca una tarea por su número de ID
    int idBuscado = 2;
    struct Tarea* tareaEncontrada = BuscarTarea(punteroTareas, 3, idBuscado);
    
    if (tareaEncontrada != NULL) {
        printf("Tarea encontrada:\n");
        printf("ID: %d\n", tareaEncontrada->TareaID);
        printf("Descripción: %s\n", tareaEncontrada->Descripcion);
        printf("Duración: %d\n", tareaEncontrada->Duracion);
    } else {
        printf("No se encontró la tarea con ID: %d\n", idBuscado);
    }
    
    return 0;
}