#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
	int TareaID; //Numerado en ciclo iterativo
	char *Descripcion; //
	int Duracion; // entre 10 – 100
};

struct Nodo{
	Tarea T;
	Nodo *Siguiente;
};

typedef struct Nodo Lista;
typedef struct Tarea Tarea;

Lista* crearLista();
void insertar(Lista** L, int x, char y[100], int dur);
void mostrarLista(Lista* L);
void tareasTerminadas(Lista** terminadas, Lista* lista);
void borrarTarea(Lista** lista, int id);
void buscarTarea(Lista* lista);
void buscarID(Lista* lista, int op);
void buscarPalabra(Lista* lista, char cadena[100]);

int main(){
	Lista* lista=crearLista();
	Lista* term=crearLista();

	int can, i=0, dur;
	char cad[100];

	do{
		printf("Ingrese tarea\n");
		printf("Ingrese el tiempo de duracion de la tarea(10-100) %d:", i+1);
		scanf("%d", &dur);
		fflush(stdin);
		printf("Ingrese la descripcion de la tarea: ");
		fgets(cad, 100, stdin);
		fflush(stdin);
		insertar(&lista,i+1,cad,dur);
		i++;
		system("cls");
		printf("Se cargo la tarea.\n");
		printf("Desea ingresar otra tarea? yes(1) no(0)\n");
		scanf("%d",&can);
	}while(can!=0);
	
	mostrarLista(lista);
	buscarTarea(lista);
	tareasTerminadas(&term,lista);
	printf("\nTareas terminadas:");
	mostrarLista(term);
	printf("\n\nTareas no terminadas:");
	mostrarLista(lista);

	return 0;
}

Lista* crearLista(){
	return NULL;
}

void insertar(Lista** L, int x, char y[100], int dur){
	Lista* nuevoNodo;
	
	nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));//Debo hacer reserva de memoria para tarea?
	
	nuevoNodo->T.TareaID=x;
	nuevoNodo->T.Descripcion= (char*)malloc(sizeof(char)*strlen(y)+1);
	strcpy(nuevoNodo->T.Descripcion, y);
	nuevoNodo->T.Duracion=dur;
	
	nuevoNodo->Siguiente= *L;
	
	*L = nuevoNodo;	
}	

void mostrarLista(Lista* L){
	Lista* aux=L;
	
	if(aux==NULL){
		printf("\nNO tiene tareas.\n");
	}
	
	while(aux != NULL){
		printf("\nID: %d", aux->T.TareaID);
		printf("\nTiempo de duracion de tarea: %d", aux->T.Duracion);
		printf("\nDescripcion de tarea: %s", aux->T.Descripcion);
		printf("\n");
		aux= aux->Siguiente;
	}
}

void tareasTerminadas(Lista** terminadas, Lista* lista){
	Lista* aux=lista;
	int resp;

	while(aux){
		printf("Terminaste la tarea %d? 1(yes) 0(no): ", aux->T.TareaID);
		scanf("%d", &resp);
	
		if(resp){
			insertar(terminadas, aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
			borrarTarea(&lista, aux->T.TareaID);
		}
	
		aux=aux->Siguiente;	
	}
}

void borrarTarea(Lista** lista, int id){
	Lista* aux = *lista;
	Lista* auxfin = NULL;
	
	while(aux && aux->T.TareaID != id){
		auxfin = aux;
		aux = aux->Siguiente;
	}
	
	if(aux){
		if(*lista==aux){
			*lista = aux->Siguiente;
		}else{
			auxfin->Siguiente = aux->Siguiente;					
		}
		free(aux->T.Descripcion);
		free(aux);
	}
}

void buscarTarea(Lista* lista){
	int op;
	char cadena[100];
	do{
		printf("\nQuiere buscar por id o por palabra?");
		printf("\nPor ID presione 1.");
		printf("\nPor palabra presione 2.");
		printf("\nRespuests:");
		scanf("%d",&op);
		fflush(stdin);
		if(op==1){
			system("cls");
			printf("Usted quiere buscar por ID");
			printf("\nIngrese el id a buscar:");
			scanf("%d", &op);
			fflush(stdin);
			buscarID(lista, op);
			printf("\nPresione enter para continuar.");
			getchar();
			getchar();
		}else{
			system("cls");
			printf("Usted quiere buscar por palabra");
			printf("\nIngrese la palabra a buscar:");
			gets(cadena);
			fflush(stdin);
			buscarPalabra(lista, cadena);
			printf("\nPresione enter para continuar.");
			getchar();
		}
		system("cls");
		printf("Quiere buscar otra Tarea? yes(1) no(0):");
		scanf("%d", &op);
	}while(op != 0);
}

void buscarID(Lista* lista, int op){
	Lista* aux=lista;
	while(aux && aux->T.TareaID != op){
		aux=aux->Siguiente;
	}
	if(aux){
		printf("\nID: %d", aux->T.TareaID);
		printf("\nTiempo de duracion de tarea: %d", aux->T.Duracion);
		printf("\nDescripcion de tarea: %s", aux->T.Descripcion);
		printf("\n");
	}else{
		printf("\nNo se encontro el ID buscado.");
	}
}

void buscarPalabra(Lista* lista, char cadena[100]){
	Lista* aux=lista;
	int i=1;
	while(aux){
		if(strstr(aux->T.Descripcion, cadena)){
			printf("\nID: %d", aux->T.TareaID);
			printf("\nTiempo de duracion de tarea: %d", aux->T.Duracion);
			printf("\nDescripcion de tarea: %s", aux->T.Descripcion);
			printf("\n");
			i=0;	
		}
		aux=aux->Siguiente;
	}
	
	if(i){
		printf("\nNo se encontro el ID buscado.");
	}
	
}
