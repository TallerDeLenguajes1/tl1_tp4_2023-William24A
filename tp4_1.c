#include <stdio.h>

struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion;
int Duracion; // entre 10 – 100
};

int main(){
    int can;
    printf("Ingresar cantidad de tareas: ");
    scanf("%d", &can);

    return 0;
}