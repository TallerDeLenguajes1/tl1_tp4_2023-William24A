#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
};

typedef struct Tarea Tareas;

int main(){
    int can,dur;
    char burr[100];
    printf("Ingresar cantidad de tareas: ");
    scanf("%d", &can); //Reserva de memoria de un vector de punteros
    Tareas **tarea=(struct Tarea**)malloc(sizeof(struct Tarea*)*can);
    
    for(int i=0;i<can;i++){
        tarea[i]= NULL;
    }

    for(int i=0;i<can;i++){
        tarea[i]= malloc(sizeof(Tareas));//Muy importante hay que reservar memoria para que cada puntero apunte a una estructura 
        tarea[i]->TareaID=i+1;              //en el caso de arriba se le indica a donde debe apuntar 
        printf("Ingrese la duracion(10-100):");
        scanf("%d", &dur);
        fflush(stdin);
        tarea[i]->Duracion=dur;

        printf("Ingrese la descripcion de la tarea: ");
        gets(burr);
        fflush(stdin); //Tercera reserva de memoria
        tarea[i]->Descripcion = (char *) malloc(sizeof(char)*strlen(burr)+1);
        strcpy(tarea[i]->Descripcion, burr);
    }

    //poner al final
    for(int i=0;i<can;i++){ //Hay que limpiar todas las reservas
        free(tarea[i]->Descripcion);
        free(tarea[i]);
    }
    
    free(tarea);
    return 0;
}