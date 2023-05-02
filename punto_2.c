#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//En la misma distribuidora del práctico anterior ahora surgió la necesidad de llevar 
//un control de las tareas realizadas por sus empleados. Usted forma parte del equipo 
//de programación que se encargará de hacer el módulo en cuestión (módulo ToDo)
//Tareas:
//Cada empleado tiene un listado de tareas a realizar.
//Las estructuras de datos necesarias son las siguientes:

//1.solicite al usuario (empleado) cuantas tareas debe cargar
//2.generar un arreglo de doble punteros dinámicamente del tipo Tarea con la cantidad de 
//tareas solicitadas en el punto anterior.inicializar los arreglos apuntando a NULL
//3.Desarrolle una interfaz de consola para cargar las tareas, ingresando su descripción 
//y duración. Usar reserva de memoria dinámica para la descripción.
//4. Una vez cargada todas las tareas. listar de a una las tareas y preguntar si se 
//realizó o no la misma. Si la respuesta es Si tiene que “mover” dicha tarea a otro 
//arreglo(tareas realizadas) que tendrá el mismo tamaño que el anterior. Una vez movida 
//la tarea ese casillero del vector tiene que apuntar a null
//5. Mostrar por pantalla las tareas realizadas y luego listar las pendientes.
//6. Cree un nuevo branch llamado busca-tarea e implemente una función de búsqueda de 
//tarea por N°id de nombre BuscarTarea. La misma devuelve la tarea solicitada.
//7. Vuelva al branch main e implemente también una nueva versión de la función
//BuscarTarea en donde la misma sea por palabra clave en vez de por Id. 
//Nota: Para realizar este punto, investigue el uso de la función strstr.
//8. Realizar el merge correspondiente y resuelva el conflicto producido.
//Finalmente modifique los nombres de las funciones a BuscaTareaPorId y otra
//BuscaTareaPorPalabra.
//9. Agregue una interfaz de usuario al programa principal que permita consultar
//tareas por id y palabra clave y mostrarlas por pantalla

typedef struct Tar{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; //entre 10 – 100
}Tarea; 

void CargaTarea(Tarea **TareasPendientes, int cantidad); //3.
void CambioTareas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant); //4.
void Mostrar(Tarea **TareaAMostrar, int cant); //5.
Tarea **BuscarPorID(Tarea **TareaPendiente, Tarea **TareaRealizada, int cant,  int id);//6.
Tarea **BuscarPorPalabra(Tarea **TareaPend, Tarea **TareaReal, int cant_t); //7.

int main (void){
    srand(time(NULL));
    int canti_tareas = 0;
    int id;

    //1.
    printf("Ingrese la cantidad de tareas a realizar: ");
    scanf("%d", &canti_tareas);
    fflush(stdin);

    Tarea **TareasPendientes = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);
    Tarea **TareasRealizadas = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);
    Tarea **TareaEncontrada = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);
    Tarea **BusqPalabra;

    //2.
    for(int i = 0; i < canti_tareas; i++){
        TareasPendientes[i] = NULL;
        TareasRealizadas[i] = NULL;
    }

    CargaTarea(TareasPendientes, canti_tareas);//3.
    CambioTareas(TareasPendientes, TareasRealizadas, canti_tareas);//4.
    printf("=====Tareas Pendientes===== \n");
    Mostrar(TareasPendientes, canti_tareas);//5.
    printf("\n=====Tareas Realizadas=====\n");
    Mostrar(TareasRealizadas, canti_tareas);//5.
    fflush(stdin);
    printf("\nIngrese el id de la tarea que quiere buscar: ");
    scanf("%d", &id);
    TareaEncontrada = BuscarPorID(TareasPendientes, TareasRealizadas, canti_tareas, id); //6.
    Mostrar(TareaEncontrada, canti_tareas); 
    BusqPalabra = BuscarPorPalabra(TareasPendientes, TareasRealizadas, canti_tareas);//7.
    Mostrar(BusqPalabra, canti_tareas);

    //Liberar memoria
    for(int i = 0; i < canti_tareas; i++){
        free(TareasPendientes[i]->Descripcion);
        free(TareasRealizadas[i]->Descripcion);
        free(TareasRealizadas[i]);
        free(TareasPendientes[i]);
    }
    free(TareasPendientes);
    free(TareasRealizadas); 

    return 0;
}
//3.
void CargaTarea(Tarea **TareasPendientes, int cantidad){
    for(int i=0; i<cantidad; i++){
        TareasPendientes[i] = (Tarea*) malloc(sizeof(Tarea));
        char strauxiliar[1000];
        TareasPendientes[i]->TareaID = 1 + i;
        printf("Ingrese la descripcion de la tarea %d: ", TareasPendientes[i]->TareaID);
        gets(strauxiliar);
        fflush(stdin);
        int len = strlen(strauxiliar);
        TareasPendientes[i]->Descripcion = (char *)malloc(sizeof(char) * len);
        strcpy(TareasPendientes[i]->Descripcion, strauxiliar);
        TareasPendientes[i]->Duracion = rand()%100 + 10;
        len = 0;
    }
}

//4.
void CambioTareas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant){
    char resultado;
    Tarea **TPendiente;
    Tarea **TRealizado;
    for(int j = 0; j < cant; j++){
        printf("La primera tarea es: %d, ya la realizo? [s/n] ", TareasPendientes[j]->TareaID);
        scanf("%c", &resultado);
        fflush(stdin);
        if (resultado == 's'){
            TareasRealizadas[j] = (Tarea *) malloc(sizeof(Tarea));
            TareasRealizadas[j]->TareaID = TareasPendientes[j]->TareaID;
            TareasRealizadas[j]->Duracion = TareasPendientes[j]->Duracion;
            TareasRealizadas[j]->Descripcion = (char *) malloc(sizeof(char) * strlen(TareasPendientes[j]->Descripcion));
            strcpy(TareasRealizadas[j]->Descripcion, TareasPendientes[j]->Descripcion);
            TareasPendientes[j] = NULL;
        }else{
            TareasRealizadas[j] = NULL;
        }
    }
}

//5.
void Mostrar(Tarea **TareaAMostrar, int cant){
    for(int i=0;i<cant;i++){
        if(TareaAMostrar[i] != NULL){
            printf("ID: %d\n",TareaAMostrar[i]->TareaID);
            printf("Duracion: %d\n",TareaAMostrar[i]->Duracion);
            printf("Descripcion: %s\n",TareaAMostrar[i]->Descripcion);
        }
    }
}

//7.
Tarea **BuscarPorPalabra(Tarea **TareaPend, Tarea **TareaReal, int cant_t){
    int boolean;
    Tarea **Aux = (Tarea**) malloc(sizeof(Tarea));
    char Cade[100];
    printf("Ingrese la palabra clave: ");
    scanf("%s", &Cade);
    fflush(stdin);
    for (int i = 0; i < cant_t; i++){
        if(TareaPend[i] != NULL){
            boolean = strcmp(TareaPend[i]->Descripcion, Cade);
            if(boolean == 0){
                Aux[i] = &(*TareaPend[i]);
                break;
            }else{
                Aux[i] = NULL;
            }
        }
    }
    for (int j = 0; j < cant_t; j++){
        if(TareaReal[j] != NULL){
            boolean = strcmp(TareaReal[j]->Descripcion, Cade);
            if(boolean == 0){
                Aux[j] = &(*TareaReal[j]);
                break;
            }else{
                Aux[j] = NULL;
            }
        }
    }
    return Aux;
}

//6.
Tarea **BuscarPorID(Tarea **TareaPendiente, Tarea **TareaRealizada, int cant, int id){
    Tarea **Aux;
    for(int i = 0; i < cant;i++){
        if(TareaPendiente[i] != NULL){
            if(TareaPendiente[i]->TareaID == id){
                Aux[i]=&(*TareaPendiente[i]);
            }else{
                Aux[i] = NULL;
            }
        }
        for(int j = 0; j<cant;j++){
            if (TareaRealizada[j] != NULL){
                if(TareaRealizada[j]->TareaID == id){
                    Aux[j]=&(*TareaRealizada[j]);
                }else{
                    Aux[j] = NULL;
                }
            }
        }
    }
    return Aux;
}