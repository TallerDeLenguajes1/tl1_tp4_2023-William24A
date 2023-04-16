#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 â€“ 100
};

typedef struct Tarea Tareas;

void BuscaTareaPorPalabra(Tareas **C, int can);
void mostrarTarea(Tareas **C, int can);
void BuscaTareaPorId(Tareas **C, int can);

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
    
    system("cls");
    //interfas para buscar contenido
    int bus;
    printf("\nQuiere buscar tarea por ID marque 1.");
    printf("\nQuiere buscar tarea por palabra marque 2.");
    printf("\nSi no quiere buscar precione 0.\n");
   	printf("\nIngrese su opcion:");
    scanf("%d", &bus);
    fflush(stdin);
    system("cls");
    while(bus){
    	switch(bus){
    		case 1:
    			//Buscar tarea
    			BuscaTareaPorId(tarea, can);
    			printf("\n\nPresione entrer para continuar.");
    			getchar();
    			getchar();
    			system("cls");
    			break;
    		case 2:
    			//bucar tarea
    			BuscaTareaPorPalabra(tarea,can);
    			printf("\n\nPresione entrer para continuar.");
				getchar();
    			system("cls");
    			break;
    	}
    	printf("\nQuiere buscar tarea por ID marque 1.");
    	printf("\nQuiere buscar tarea por palabra marque 2.");
    	printf("\nSi no quiere buscar precione 0.\n");
    	printf("\nIngrese su opcion:");
    	scanf("%d", &bus);
    	fflush(stdin);
    	system("cls");
    }
    
    
    //Una vez cargada todas las tareas. Irá listando de a una las tareas y preguntando si se realizó o no la misma
	int j=0;
	for(i=0;i<can;i++){
		printf("\nTermino esta tarea %d 1(yes) 0(No):", tarea[i]->TareaID);
		scanf("%d",&dur);
		if(dur){
			terminada[j]=malloc(sizeof(Tareas));
			terminada[j]=tarea[i];
			tarea[i]=NULL;
			j++;
		}
	}
	
	printf("\n\nMostrar tareas terminadas");
	mostrarTarea(terminada, can);
	printf("\n\nMostrar tareas por terminar");
	mostrarTarea(tarea, can);
	
	
    //poner al final
    for(i=0;i<can;i++){ //Hay que limpiar todas las reservas
        free(tarea[i]);
        free(terminada[i]);
    }
    
    free(tarea);
    free(terminada);
    return 0;
}

void BuscaTareaPorPalabra(Tareas **C, int can){
	char cadena[100];
	int i,j=1;
	printf("\nIngrese palabra a buscar: ");
	gets(cadena);
	fflush(stdin);
	for(i=0;i<can;i++){
		if(strstr(C[i]->Descripcion, cadena)){
			printf("\nTarea existente");
			printf("\nID de tarea: %d", C[i]->TareaID);
			printf("\nDescripcion de tarea: %s", C[i]->Descripcion);
			j=0;
		}
	}
	if(j){
		printf("\nNo se encontraron tareas.");
	}	
}

void BuscaTareaPorId(Tareas **C, int can){
	int i,bus,f=1;
	printf("Ingrese el numero a buscar: ");
	scanf("%d",&bus);
	
	for(i=0;i<can && f ;i++){
		if(C[i]->TareaID == bus){
			printf("\nTarea existente");
			printf("\nID de tarea: %d", C[i]->TareaID);
			printf("\nDescripcion de tarea: %s", C[i]->Descripcion);
			f=0;
		}
	}
	
	if(f){
		printf("\nNo se encontro la taera.");
	}
}

void mostrarTarea(Tareas **C, int can){
	int i;
	for(i=0;i<can;i++){
		if(C[i]!=NULL){
			printf("\nID de tarea: %d", C[i]->TareaID);
			printf("\nDescripcion de tarea: %s", C[i]->Descripcion);	
		}
	}
}
