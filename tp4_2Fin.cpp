#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
	int TareaID; //Numerado en ciclo iterativo
	char *Descripcion; //
	int Duracion; // entre 10 � 100
};

struct Nodo{
	Tarea T;
	Nodo *Siguiente;
};

typedef struct Nodo Lista;
typedef struct Tarea Tarea;

Lista* crearLista();
Lista* CrearNodo(int x, char y[100], int dur);
void insertar(Lista** L, int x, char y[100], int dur);
void mostrarLista(Lista* L);
void tareasTerminadas(Lista** terminadas, Lista** noTerminadas, Lista* lista);
void buscarTarea(Lista* lista);
void buscarID(Lista* lista, int op);
void buscarPalabra(Lista* lista, char cadena[100]);
void ingresarDatos(Lista** lista,int *i);

int main(){
	Lista* nueva= crearLista();
	Lista* term=crearLista();
	Lista* noTerm=crearLista();
	int i=0, op;
	char cadena[100];
	do{
		system("cls");
		printf("\nSISTEMA DE GESTION DE TAREAS.");
		printf("\nTareas ingresadas hasta el momento: %d", i);
		printf("\n\n1-Para ingresar nuevas tareas presione.");
		printf("\n2-Para buscar tareas.");
		printf("\n3-Para seleccionar tareas terminadas y no terminadas.");
		printf("\n0-Para salir.");
		printf("\n\nRespuesta:");
		scanf("%d",&op);
		fflush(stdin);
		switch(op){
			case 1:
				system("cls");
				ingresarDatos(&nueva,&i);
				break;
			case 2:
				system("cls");
				if(i){
					buscarTarea(nueva);
				}else{
					printf("\nNo ingreso tareas.");
					printf("\nPresione enter para continuar.");
					getchar();	
				}
				
				break;
			case 3:
				system("cls");
				tareasTerminadas(&term,&noTerm,nueva);
				system("cls");
				printf("Tareas terminadas: ");
				mostrarLista(term);
				printf("\nTareas no terminadas: ");
				mostrarLista(noTerm);
				printf("\nPresione entere para continuar.");
				getchar();
				getchar();
				break;
			case 0:
				system("cls");
				printf("Saliendo ... presione enter para continuar.");
				getchar();
				break;		
		}
		system("cls");
	}while(op != 0);	
	return 0;
}

Lista* crearLista(){
	return NULL;
}

Lista * CrearNodo(int x, char y[100], int dur)
{
	Lista* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));//Debo hacer reserva de memoria para tarea?
	nuevoNodo->T.TareaID=x;
	nuevoNodo->T.Descripcion= (char*)malloc(sizeof(char)*strlen(y)+1);
	strcpy(nuevoNodo->T.Descripcion, y);
	nuevoNodo->T.Duracion=dur;
	nuevoNodo->Siguiente= NULL;
	return nuevoNodo;
}

void insertar(Lista** L, int x, char y[100], int dur){
	Lista * nuevoNodo= CrearNodo(x,y,dur);
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

void tareasTerminadas(Lista** terminadas, Lista** noTerminadas, Lista* lista){
	Lista* aux=lista;
	int resp;

	while(aux){
		printf("Terminaste la tarea %d? 1(yes) 0(no): ", aux->T.TareaID);
		scanf("%d", &resp);
	
		if(resp){
			insertar(terminadas, aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
		}else{
			insertar(noTerminadas, aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
		}	
		aux=aux->Siguiente;	
	}
}


void buscarTarea(Lista* lista){
	int op;
	char cadena[100];
	do{
		printf("\nQuiere buscar por id o por palabra?");
		printf("\nPor ID presione 1.");
		printf("\nPor palabra presione 2.");
		printf("\nPara salir presione 0.");
		printf("\nRespuests:");
		scanf("%d",&op);
		fflush(stdin);
		switch(op){
			case 1:
				system("cls");
				printf("Usted quiere buscar por ID");
				printf("\nIngrese el id a buscar:");
				scanf("%d", &op);
				fflush(stdin);
				buscarID(lista, op);
				printf("\nPresione enter para continuar.");
				getchar();
				break;
			case 2:
				system("cls");
				printf("Usted quiere buscar por palabra");
				printf("\nIngrese la palabra a buscar:");
				gets(cadena);
				fflush(stdin);
				buscarPalabra(lista, cadena);
				printf("\nPresione enter para continuar.");
				getchar();
				break;
			case 0:
				system("cls");
				printf("Saliendo ... presione enter para continuar.");
				getchar();
				break;		
		}
		system("cls");
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

void ingresarDatos(Lista** lista, int *i){
	int dur,can;
	char cad[100];
	do{
		system("cls");
		printf("Ingrese tarea\n");
		
		do{
			printf("Ingrese el tiempo de duracion de la tarea(10-100) %d:", *(i)+1);
			scanf("%d", &dur);
			fflush(stdin);
		}while(dur<10 || dur>100);
	
		printf("Ingrese la descripcion de la tarea: ");
		fgets(cad, 100, stdin);
		fflush(stdin);
		insertar(lista,*(i)+1,cad,dur);
		*(i)=*(i)+1;
		system("cls");
		printf("Se cargo la tarea.\n");
		printf("Desea ingresar otra tarea? yes(1) no(0)\n");
		scanf("%d",&can);
	}while(can!=0);
}
