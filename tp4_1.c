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
    int can,dur,i;
    char burr[100];
    printf("Ingresar cantidad de tareas: ");
    scanf("%d", &can); //Reserva de memoria de un vector de punteros
    Tareas **tarea=(struct Tarea**)malloc(sizeof(struct Tarea*)*can);
    Tareas **terminada=(struct Tarea**)malloc(sizeof(struct Tarea*)*can);
    
    for(i=0;i<can;i++){
        tarea[i]= NULL;
        terminada[i]=NULL;
    }

    for(i=0;i<can;i++){
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
    
    //Una vez cargada todas las tareas. Ir� listando de a una las tareas y preguntando si se realiz� o no la misma
	int j=0;
	for(i=0;i<can;i++){
		printf("Termino esta tarea %d 1(yes) 0(No):", tarea[i]->TareaID);
		scanf("%d",&dur);
		if(dur){
			terminada[j]=malloc(sizeof(Tareas));
			terminada[j]=tarea[i];
			tarea[i]=NULL;
			j++;
		}
	}
	
	printf("\n\nMostrar tareas terminadas");
	for(i=0;i<can;i++){
		if(terminada[i]!=NULL){
			printf("\nID de tarea: %d", terminada[i]->TareaID);
			printf("\nDescripcion de tarea: %s", terminada[i]->Descripcion);	
		}
	}
	
	printf("\n\nMostrar tareas por terminar");
	for(i=0;i<can;i++){
		if(tarea[i]!=NULL){
			printf("\nID de tarea: %d", tarea[i]->TareaID);
			printf("\nDescripcion de tarea: %s", tarea[i]->Descripcion);	
		}
	}
    //poner al final
    for(i=0;i<can;i++){ //Hay que limpiar todas las reservas
        free(tarea[i]);
        free(terminada[i]);
    }
    
    free(tarea);
    free(terminada);
    return 0;
}
