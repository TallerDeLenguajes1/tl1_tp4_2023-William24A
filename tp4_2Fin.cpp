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
void insertar(Lista** L, Lista* nuevoNodo);
void mostrarLista(Lista* L);
Lista* tareasTerminadas(Lista** terminadas, Lista** noTerminadas, Lista** EnProceso, Lista** lista);
void buscarTarea(Lista* lista);
void buscarID(Lista* lista, int op);
void buscarPalabra(Lista* lista, char cadena[100]);
void ingresarDatos(Lista** lista, int *id, int *i);
Lista* EliminarTarea(Lista** lista, int id);
void mostrarDatos(Lista* lista);
Lista* modificarEstado(Lista** terminada, Lista** noTerminada, Lista** enProceso, int elim);

int main(){
	Lista* nueva= crearLista();
	Lista* term=crearLista();
	Lista* noTerm=crearLista();
	Lista* enPro=crearLista();
	Lista* Nodo;

	int i=0,id=0, op, elim;
	char cadena[100];
	do{
		system("cls");
		printf("\nSISTEMA DE GESTION DE TAREAS.");
		printf("\nTareas ingresadas hasta el momento: %d", i);
		printf("\n\n1-Para ingresar nuevas tareas presione.");
		printf("\n2-Para buscar tareas.");
		printf("\n3-Para describir el estado de la tarea o modificar.");
		printf("\n4-Mostrar datos sobre tareas pendientes.");
		printf("\n0-Para salir.");
		printf("\n\nRespuesta:");
		scanf("%d",&op);
		fflush(stdin);
		switch(op){
			case 1:
				system("cls");
				ingresarDatos(&nueva,&i,&id);
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
				if(nueva==NULL && (term || noTerm || enPro)){
					printf("Mostrar tareas");
					printf("\nTareas terminadas: ");
					mostrarLista(term);
					printf("\nTareas no terminadas: ");
					mostrarLista(noTerm);
					printf("\nTareas en proceso: ");
					mostrarLista(enPro);
					printf("\n Desea seleccionar alguna tarea tarea: 1(si) 0(no):");
					scanf("%d", &elim);
					if(elim){
						printf("Desea Mover o Eliminar: ");
						printf("\n1- Mover ");
						printf("\n0- Eliminar ");
						printf("\nRespuesta: ");
						scanf("%d", &elim);
						Nodo=modificarEstado(&term,&noTerm,&enPro, elim);
						if(Nodo){
							free(Nodo->T.Descripcion);
							free(Nodo);
							if(elim==0){
								i--;
							}	
						}
					}
					
					
				}else{
					nueva=tareasTerminadas(&term,&noTerm,&enPro,&nueva);
					system("cls");
					printf("Tareas terminadas: ");
					mostrarLista(term);
					printf("\nTareas no terminadas: ");
					mostrarLista(noTerm);
					printf("\nTareas en proceso: ");
					mostrarLista(enPro);	
				}
				
				printf("\nPresione entere para continuar.");
				getchar();
				getchar();
				break;
			case 4:
				if(noTerm){
					mostrarDatos(noTerm);
				}else{
					system("cls");
					printf("Debe describir el estado de la tarea.\n");
				}
				
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
	return 0;
}
//Crear Lista vacia
Lista* crearLista(){
	return NULL;
}
//Crear nodo
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
//Insertar nodo a la lista
void insertar(Lista** L, Lista* nuevoNodo){
	nuevoNodo->Siguiente= *L;
	*L = nuevoNodo;	
}
//mostrar lista
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
//escribir si es que una tarea esta terminada o no o en proceso
Lista* tareasTerminadas(Lista** terminadas, Lista** noTerminadas, Lista** EnProceso, Lista** lista){
	Lista* aux=*lista;
	Lista* aux2;
	
	int resp;

	while(aux){
		
		system("cls");
		printf("Describa el estado de la tarea %d: ", aux->T.TareaID);
		printf("\n1-Tarea terminada.");
		printf("\n2-Tarea No terminada.");
		printf("\n3-Tarea en proceso.");
		printf("\nRespuesta:");
		scanf("%d", &resp);
		
		aux2=EliminarTarea(&aux,aux->T.TareaID);
		switch(resp){
			case 1:
				insertar(terminadas, aux2);
				break;
			case 2:
				insertar(noTerminadas, aux2);
				break;
			case 3:
				insertar(EnProceso, aux2);
				break;
		}	
				
	}
	return aux;
}

//Pregunta cual metodo usar para buscar
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
//Buscar por id
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
//Buscar por palabra que contenga la descripcion
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
//Ingresar datos al nodo
void ingresarDatos(Lista** lista, int *id, int *i){
	int dur,can;
	
	char cad[100];
	do{
		*(i)=*(i)+1;
		system("cls");
		printf("Ingrese tarea\n");
		
		do{
			printf("Ingrese el tiempo de duracion de la tarea(10-100) %d:", *(id)+1);
			scanf("%d", &dur);
			fflush(stdin);
		}while(dur<10 || dur>100);
	
		printf("Ingrese la descripcion de la tarea: ");
		fgets(cad, 100, stdin);
		fflush(stdin);
		insertar(lista, CrearNodo(*(id)+1,cad,dur));
		*(id)=*(id)+1;
		system("cls");
		printf("Se cargo la tarea.\n");
		printf("Desea ingresar otra tarea? yes(1) no(0)\n");
		scanf("%d",&can);
	}while(can!=0);
}
//devuele el nodo para eliminar
Lista* EliminarTarea(Lista** lista, int id){
	Lista* aux= *lista;
	Lista* auxAnterior= *lista;
	
	while(aux && aux->T.TareaID != id){
		auxAnterior=aux;
		aux=aux->Siguiente;
	}
	
	if(aux){
		if(aux == *lista){
			*lista =aux->Siguiente;
		}else{
			auxAnterior->Siguiente=aux->Siguiente;
		}
		aux->Siguiente=NULL;
	}
	return aux;
}

void mostrarDatos(Lista* lista){
	Lista* aux= lista;
	int sumar=0, i=0;
	while(aux){
		sumar+= lista->T.Duracion;
		aux=aux->Siguiente;
		i++;
	}
	system("cls");
	printf("La cantidad de tareas que tiene pendiente son: %d", i);
	printf("\nLa cantidad de tiempo de todas las tareas es: %d", sumar);
}

Lista* modificarEstado(Lista** terminada, Lista** noTerminada, Lista** enProceso, int elim){
	Lista* aux;
	int id, op;
	//system("cls"); 
	printf("Ingrese el ID que desea modificar: ");
	scanf("%d", &id);
	aux=EliminarTarea(noTerminada, id);
	system("cls");
	if(aux){
		if(elim){
			printf("\nA donde desea mover esta tarea");
			printf("\n1-Tareas en proceso");
			printf("\n2-Tareas terminadas");
			printf("\nRespuesta:");
			scanf("%d", &op);
			switch(op){
				case 1:
					insertar(enProceso, aux);
					break;
				case 2:
					insertar(terminada, aux);
					break;
			}
		}
	}else{
		aux=EliminarTarea(enProceso, id);
		if(aux){
				if(elim){
					printf("\nA donde desea mover esta tarea");
					printf("\n1-Tareas no terminadas");
					printf("\n2-Tareas terminadas");
					printf("\nRespuesta:");
					scanf("%d", &op);
					switch(op){
						case 1:
							insertar(noTerminada, aux);
							break;
						case 2:
							insertar(terminada, aux);
							break;
					}
				}
			
		}else{
			aux=EliminarTarea(terminada, id);
			if(elim){
				printf("\nA donde desea mover esta tarea");
				printf("\n1-Tareas en proceso");
				printf("\n2-Tareas no terminadas");
				printf("\nRespuesta:");
				scanf("%d", &op);
				switch(op){
					case 1:
						insertar(enProceso, aux);
						break;
					case 2:
						insertar(noTerminada, aux);
						break;
				}
			}
		}
	}
	return aux;
}
