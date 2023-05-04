#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Reemplazar la implementación que realizó con listas enlazadas, para ello en vez de tener 
2 arreglos de tareas ahora tendrá 2 listas enlazadas (una para las tareas pendientes y otra 
para las  tareas realizadas) y cada vez que se marque como realizada tendrá que mover la 
tarea de la lista de tareas pendientes a la lista de tareas realizada

1. Reimplemente los puntos 1 a 5 del punto anterior utilizando las listas enlazadas. 
Modifique la interfaz de carga de tareas para que en vez de solicitar la cantidad de 
tareas al comienzo, al cabo de cada tarea pregunte al usuario si desea ingresar una nueva 
tarea o finalizar la carga.

2. Implemente también las funciones de búsquedas para que devuelvan el nodo correspondiente
a la tarea solicitada Cree también la interfaz de usuario de consulta de tareas */

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
    int realizada;
} typedef Tarea;

struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
} typedef Nodo;

typedef struct Nodo* Lista;

Lista CrearLista();
Lista CrearNodo();
void MostrarTareas(Lista tareas);
Lista CargarTarea(Lista tareasPendientes, int ID);

void Mostrar1Tarea(Tarea tarea);
void consultarEstadoTareas(Lista* listaTareasPendientes, Lista* listaTareasRealizadas);
void EstadoDeTareas(Lista tareasPendientes, Lista tareasRealizadas);
void BuscarTareaIDEnLasListas(Lista ListaTareas, Lista ListaTareasRealizadas, int ID); // Busca la tarea en ambas listas e informa el estado de la misma
int BuscarTareaID(Lista listaTareas, int ID); //Busca tarea en una sola lista en espesifico.
void liberarMemoria(Lista * ListaTareas);

int main(){
    //int cantidadTareas;   
    //cantidadTareas = CantTares();
    // Desarrollo la interfas para que el usuaio sea quien decida si seguira ingresando tareas o no 
    int respuesta, i =0;

    Lista tareasPendientes = CrearLista(); 
    Lista tareasRealizadas = CrearLista();

    srand(time(NULL));
    do{
        printf("\nDesea seguir cargando tareas?\n  1 : Si  0 : No\n");
        scanf("%d",&respuesta);

        if (respuesta){
            tareasPendientes = CargarTarea(tareasPendientes, i+1);
            i++;
        }         
    }while (respuesta);
    
    consultarEstadoTareas(&tareasPendientes, &tareasRealizadas); 
    EstadoDeTareas(tareasPendientes, tareasRealizadas);

    int IDaBuscar;
    printf("\nIngrese el ID de la tarea que desea Buscar...\n");
    scanf("%d",&IDaBuscar);
   
    BuscarTareaIDEnLasListas(tareasPendientes, tareasRealizadas, IDaBuscar);

    liberarMemoria(&tareasPendientes);
    liberarMemoria(&tareasRealizadas);

    return 0;
}

Lista CrearLista(){
    return NULL; //la cabecera de la lista apunte a NULL
}
//Lista = struct Nodo*
Lista CrearNodo(){ //particularizada para el problema se llama CrearTarea
    Lista newNodo = (Lista)malloc(sizeof(Nodo));

    //Una vez Creado el nodo me concentro en los datos que llevara
    int duracion = rand() % 90 +10;
    char *buff=(char*)malloc(sizeof(char)*100);
    fflush(stdin);//limpia consola de entrada
    printf("\nIngrese La descripcion de la tarea:");
    gets(buff);
    newNodo->T.Descripcion =(char *)malloc((strlen(buff)+1) * sizeof(char));
    strcpy( newNodo->T.Descripcion, buff);
    newNodo->T.Duracion = duracion;
    newNodo->Siguiente = NULL;
    free(buff);
    return newNodo;
}

Lista CargarTarea(Lista tareasPendientes, int ID){
    Lista nuevoNodo = CrearNodo();
    nuevoNodo->T.TareaID = ID;
    if (tareasPendientes){
        Lista auxiliar = tareasPendientes;
        while (auxiliar->Siguiente != NULL){
            auxiliar = auxiliar->Siguiente;
            //Si no es ultimo nodo sigo iterando hasta llegar a lo que necesito
        }
        //Una vez que estoy en el ultimo nodo puedo enlazar mi nuevo nodo
        auxiliar->Siguiente = nuevoNodo;
    }else{//Como mi lista no tiene ningun nodo directamente enlazo mi nuevo nodo al comienzo
        nuevoNodo->Siguiente = tareasPendientes;
        tareasPendientes = nuevoNodo;
    }
    return tareasPendientes;
}

void MostrarTareas(Lista tareas){
    Lista auxiliar = tareas;
    printf("\n\nMOSTRADO DE TODAS LAS TAREAS\n");
    if (auxiliar==NULL){
        printf("\nLa Lista se encuentra Vacia\n");
    }else{
        while(auxiliar != NULL){
            printf("\nID TAREA %d\n", auxiliar->T.TareaID);
            printf("   Tienen una duracion de: %d\n",auxiliar->T.Duracion);
            printf("   Descripcion: %s\n",auxiliar->T.Descripcion);
            auxiliar = auxiliar->Siguiente;
        }
    }    
}

void Mostrar1Tarea(Tarea tarea){
    printf("\nID TAREA %d\n", tarea.TareaID);
    printf("   Tienen una duracion de: %d\n",tarea.Duracion);
    printf("   Descripcion: %s\n",tarea.Descripcion);
}

void consultarEstadoTareas(Lista* listaTareasPendientes, Lista* listaTareasRealizadas){
    int realizada;
    Lista listaTareasPendientesAux = NULL;
    Nodo* puntProxNodoAux = NULL;
    printf("\n\n- Ahora analicemos cada tarea:\n");

    while(*listaTareasPendientes != NULL){
        puntProxNodoAux = (*listaTareasPendientes)->Siguiente;
        Mostrar1Tarea((*listaTareasPendientes)->T);
        do{
            printf("Fue realizada? 1: si, 0; no\n");
            scanf("%d", &realizada);

        }while(realizada != 0 && realizada != 1);
    
        if(realizada == 1){
            (*listaTareasPendientes)->Siguiente = *listaTareasRealizadas;
            // El puntero del nodo a agregar a la lista de tareas realizadas apuntará al último nodo agregado a dicha lista.
            *listaTareasRealizadas = *listaTareasPendientes;
            // La cabecera de la lista de tareas realizadas apunta al nodo recién agregado a la lista.
        }else{
            (*listaTareasPendientes)->Siguiente = listaTareasPendientesAux;
            // El puntero del nodo a agregar a la lista de tareas pendientes (auxiliar) apuntará al último nodo agregado a dicha lista.
            listaTareasPendientesAux = *listaTareasPendientes;
            // El puntero del nodo a agregar a la lista de tareas pendientes (auxiliar) apuntará al último nodo agregado a dicha lista.
        }
        // Se usa una lista auxiliar para tareas pendientes a fin de evitar tener que revincular nodos de la lista de tareas pendientes y considerar distintos casos donde el nodo que puede ser pasado a la lista de tareas realizadas esté o al principio, o en el medio, o al final de la lista de tareas pendientes original.
        *listaTareasPendientes = puntProxNodoAux;
    }
    *listaTareasPendientes = listaTareasPendientesAux;
}

void EstadoDeTareas(Lista tareasPendientes, Lista tareasRealizadas){
    printf("\n\n TAREAS PENDIENTES\n");
    MostrarTareas(tareasPendientes);
    printf("\n\n TAREAS REALIZADAS\n");
    MostrarTareas(tareasRealizadas);
}

int BuscarTareaID(Lista listaTareas, int ID){
    printf("\nBusqueda de la Tarea %d\n",ID);
    Lista auxiliar = listaTareas;
    int bandera = 0;

    while (auxiliar){
        if(auxiliar->T.TareaID == ID){
            printf("\nTarea Encontrada:\n");
            Mostrar1Tarea(auxiliar->T);
            bandera = 1;
        }
        auxiliar = auxiliar->Siguiente;
    }     
    return bandera;  
}

void BuscarTareaIDEnLasListas(Lista ListaTareas, Lista ListaTareasRealizadas, int ID){ 
    int estado = BuscarTareaID(ListaTareas, ID);
    if (estado){
        printf("Estado de la tarea:\n     PENDIENTE\n");
    }else{
        estado = BuscarTareaID(ListaTareasRealizadas, ID);
        printf("Estado de la tarea:\n     REALIZADA\n");
    }
}

void liberarMemoria(Lista * ListaTareas){
    Nodo* auxLiberarMemoria = NULL;
    while (ListaTareas){
        free((*ListaTareas)->T.Descripcion);
        auxLiberarMemoria = *ListaTareas;
        *ListaTareas = (*ListaTareas)->Siguiente;
        free(auxLiberarMemoria);
    }
}
