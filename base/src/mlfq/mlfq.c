




#include "mlfq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "../file_manager/manager.h"


/*
READY = 0;
RUNNING = 1;
WAITING = 2;
FINISH = 3;
*/
int cola_wait = 1000;
bool salio_wait = false;

Queue* init_queue(int number_queues, int q){
	Queue* queue = malloc(number_queues * sizeof(Queue));
	
	int i = 0;
	for (i = 0; i < number_queues; i++)
  	{
		queue[i].head = NULL;
		queue[i].tail = NULL;
		queue[i].quantum = (number_queues - (number_queues - (i+1))) *q;
	}

  return queue;
}

void add_process(Queue* queue, int num_process, InputFile* file_data, int cycle_count){

	
	/*añadir procesos a la primera cola todos con estado ready
	int num_process1;
	FILE* file1 = fopen(file,"r");
	fscanf(file1, "%d", &num_process1);
	fclose(file1);
	printf("NUM PROCESOS [%d]\n", num_process1);
	InputFile* file_data = read_file(file);
	
	for (int i = 0; i < num_process1; i++)
	{
		
		printf("LINEA [%d] - PID [%d] - INIT TIME [%d] \n",i,atoi(file_data ->lines[i][1]),atoi(file_data ->lines[i][2]) );
	}
	
	char** temp;
	for (int i = 0; i < num_process; i++)
	{
		for (int j = i+1; j < num_process; j++)
		{
			if (atoi(file_data ->lines[i][2]) > atoi(file_data ->lines[j][2]))
			{
			printf("devug\n");
				temp = file_data ->lines[i];    
               	file_data ->lines[i] = file_data ->lines[j];    
               	file_data ->lines[j] = temp;   
			}
		}
	}
	printf("\n");
	printf("LINEA [%d] - PID [%d] - INIT TIME [%d] \n",0,atoi(file_data ->lines[0][1]),atoi(file_data ->lines[0][2]) );*/
	
	for (int i = 0; i < num_process; i++)
	{
		if (atoi(file_data -> lines[i][2]) == cycle_count && is_in_queue(queue, atoi(file_data -> lines[i][1])) == 0)
		{
				
			Process* process = malloc(sizeof(Process));
			process -> pid = atoi(file_data -> lines[i][1]);
			process -> state = 0;
			process -> init_time = atoi(file_data -> lines[i][2]);
			process -> name = file_data -> lines[i][0];
			process -> cycles = atoi(file_data -> lines[i][3]);
			process -> cycle_count = atoi(file_data -> lines[i][3]);
			process -> wait = atoi(file_data -> lines[i][4]);
			process -> waiting_delay = atoi(file_data -> lines[i][5]);
			process -> priority = 0;
			process -> quantum = queue[0].quantum;
			process -> salio_de_wait = 1;
			process -> ciclo_wait = 0;
			process -> next = NULL;
			process -> interrupciones = 0;
			process -> turnos_cpu = 0;
			process -> turnaround = 0;
			process -> response = 0;
			process -> active_time = 0;
			process -> entra_primera_vez = false;
			process -> primera_vez = 0;
			
			list_append(queue,0,process,0);
		}
	
	}
	
}

int is_in_queue(Queue* queue, int pid){
	Process* temp = queue[0].head;
	int esta = 0;
	while (temp != NULL)
	{
		if (temp -> pid == pid)
		{
			esta = 1;
			break;
		}
		temp = temp -> next;
	}

	return esta;
}

void change_priority(Queue* queue, int priority1, int priority2, Process* proceso){
	
						
	Process* temp = queue[priority1].head, *prev;
	Process* temp2 = queue[priority2].head;
	

	if (priority1 == 0 && priority2 == 0)
	{
		Process* temp3 = proceso;
		int id_aux = proceso -> pid;
		
		delete_process(queue,0,id_aux);
		temp3 -> pid = id_aux;
		list_append(queue,0,temp3,0);

	}else{
		if (temp != NULL && temp -> pid == proceso -> pid)
		{
			queue[priority1].head = temp -> next;
			
		}else{
			while (temp != NULL && temp -> pid != proceso -> pid)
			{
				prev = temp;
				temp = temp -> next;
			}

			if (temp == NULL)
			{
				printf("el nodo no esta \n");
			}else{
				prev -> next = temp -> next;
				
			}
									
			
		}

		proceso -> next = NULL;
		if (temp2 == NULL)
		{
			/* code */
			queue[priority2].head = proceso;
		}else
		{
			while (temp2 -> next != NULL)
			{
				temp2 = temp2 -> next;
			}
			
			temp2 -> next =proceso;
			
			
		}
	
	

	}

	



	
}

int revisar_colas(Queue* queue,int number_queues){
	int cola = -1;
	for (int i = 0; i < number_queues; i++)
	{
		/* code */
		Process* temp = queue[i].head;
		while (temp != NULL)
		{
			
			if (temp == NULL )
			{
				/* code */
				break;
			}
			if(temp -> state == 2){
				
				temp = temp -> next;
			}else{
				
				cola = i;
				break;
			}
		}
		if (cola != -1)
		{
			break;
		}
		
		


		
	}
	
	return cola;

}

void display(Queue* array, int number_queues){
	int i = 0;
	for (i = 0; i < number_queues; i++)
        {
		Process* temp = array[i].head;
		printf("cola de quantum %d \n", array[i].quantum);

		if (temp == NULL)
        {
			printf("array[%d] has no elements\n", i);
		}
        else
        {
			printf("array[%d] has elements-: ", i);
			while (temp != NULL)
            {
				printf("pid= %d - init_time = %d ------ state = %d ------- \t", temp->pid,temp->init_time,temp->state);
				temp = temp->next;
			}
			printf("\n");
		}
		free(temp);
	}

}

void list_append(Queue* queue,int priority, Process* proceso, int se_resetea)
{
	Process* temp = queue[priority].head;
	if (se_resetea == 0)
	{
		proceso -> next = NULL;
	}
	
	
	
	// Si la lista está vacía entonces queda como el primer elemento
	if(queue[priority].head == NULL)
	{
		
		queue[priority].head = proceso;
		return;
	}
	// Sino, se pone como el siguiente del ultimo
	while (temp -> next != NULL)
	{

		temp = temp -> next;
	}
	temp -> next = proceso;

}

void insert_process(Queue* cola, int priority, Process* proceso, int pos){
	Process* proceso_aux;
	int i=0;
	if (pos == 0)
	{
		proceso->next = cola[priority].head;
		cola[priority].head = proceso;
	}else{

    Process* prev = NULL;
    for ( proceso_aux = cola[priority].head; proceso_aux != NULL; (proceso_aux = proceso_aux->next), i += 1) {

        if (i >= pos){

            break;
		}

        prev = proceso_aux;

    }

		proceso -> next = proceso_aux;

		if (prev != NULL)
		{
			prev -> next  = proceso;
			/* code */

		}else{
			cola[priority].head = proceso;
		}

		
	}


	

}

void delete_process(Queue* cola, int num_queue,int id){
	Process* temp = cola[num_queue].head, *prev;
	
	if (temp != NULL && temp -> pid == id)
	{
		
		cola[num_queue].head = temp -> next;
		
	}else{
		
		while (temp != NULL && temp -> pid != id )
		{
			prev = temp;
			temp = temp -> next;
		}

		if (temp == NULL)
		{
			printf("el nodo no esta \n");
		}else{
			prev -> next = temp -> next;
			
		}
		
		
	}
	

}

void list_destroy(Queue* queue, int num_queues)
{
  // Liberamos los nodos
  for (int i = 0; i < num_queues; i++)
  {
	  /* code */
	  if(queue[i].head)
  {
    Process* curr = queue[i].head-> next;
    Process* prev = queue[i].head;

    while(curr)
    {
      free(prev);
      prev = curr;
      curr = curr -> next;
    }
    free(prev);
  }
  // Liberamos la lista en si

  }
  
  
}


void change_waiting(Queue* queue, int num_queues, int cycle_count, int running_process){
	
	for (int i = 0; i < num_queues; i++)
	{
		Process* temp = queue[i].head;
		if (temp == NULL)
		{	
			
			continue;
		}else{
			while (temp != NULL)
			{
				if(temp -> state == 2 && (cycle_count - temp -> ciclo_wait) >= temp -> waiting_delay) 
				{
					printf("EL PROCESO DE PID [%d] SALE DEL ESTADO WAIT Y EMPIEZA A CORRER - ", temp -> pid);
					temp -> state = 0;
					temp -> salio_de_wait = 1;
					if (temp -> priority <= cola_wait)
					{
						cola_wait = temp -> priority;
					}
					salio_wait = true;
					

				}
				temp = temp->next;
			}
			
		}
		
	}
}

void reset_queue(Queue* queue, int num_queues){
	int cambio = 0;
	for (int i = 1; i < num_queues; i++)
	{
		Process* temp = queue[i].head;
		

		
		
		while (temp != NULL)
		{	
			if (temp == NULL)
			{
				break;
			}else{
				int id_aux = temp -> pid;
				int priority_aux = temp -> priority;

				
				
				
				if (temp -> state != 1)
				{
					
					temp -> quantum = queue[0].quantum;
					temp -> priority = 0;
					
					change_priority(queue,priority_aux,0,temp);
					cambio = 1;
					


					
				}
				if (cambio == 1)
				{
					temp = queue[i].head;
				}else{
					temp = temp -> next;
					
				}
				
				
				}
			
		cambio = 0;
			
		}
		




			
		}

		
		
	
	
}

void simulation(Queue* queue, int num_queues, int num_procesos,  char* file, int S, FILE* output_file){
	/*ABRO EL ARCHIVO PARA SACAR LA PRIMERA LINEA*/
	int num_process1;
	FILE* file1 = fopen(file,"r");
	fscanf(file1, "%d", &num_process1);
	fclose(file1);
	printf("NUM PROCESOS [%d]\n", num_process1); /*NUMERO DE PORCESOS*/
	InputFile* file_data = read_file(file);

	/*ESTO ES PARA ORDENAR LOS PROCESOS DE MENOR INIT TIME A MAYOR INIT TIME*/
	char** temp;
	for (int i = 0; i < num_process1; i++)
	{
		for (int j = i+1; j < num_process1; j++)
		{
			if (atoi(file_data ->lines[i][2]) > atoi(file_data ->lines[j][2]))
			{

				temp = file_data ->lines[i];    
               	file_data ->lines[i] = file_data ->lines[j];    
               	file_data ->lines[j] = temp;   
			}
			
		}
		
	}

/*AGREGO TODOS LOS PROCESOS QUE LLEGAN EN TIEMPO 0 A LA COLA
	for (int i = 0; i < num_process1; i++)
	{
		if (atoi(file_data -> lines[i][2]) == 0){
			Process* process = malloc(sizeof(Process));
			process -> pid = atoi(file_data -> lines[0][1]);
			process -> state = 0;
			process -> init_time = atoi(file_data -> lines[0][2]);
			process -> name = file_data -> lines[0][0];
			process -> cycles = atoi(file_data -> lines[0][3]);
			process -> cycle_count = atoi(file_data -> lines[0][3]);
			process -> wait = atoi(file_data -> lines[0][4]);
			process -> waiting_delay = atoi(file_data -> lines[0][5]);
			process -> priority = 0;
			process -> quantum = queue[0].quantum;
			process -> next = NULL;
			
			insert_process(queue,0,process,0);

		}

	}*/
	
	int primer_proceso = atoi(file_data -> lines[0][2]);
	int cycle_count = 0;
	int process_count = 0;
	int running_process = 0;
	int reset = 0;
	int ciclos_extra = 0;

	while (process_count <= num_process1 ) /*WHILE PARA CONTAR CUANTOS PROCESOS QUEDAN EN LA COLA*/
	{
		int queue_counter = 0;
		printf("QUEDAN [%d] PROCESOS \n \n", process_count);

		if (process_count == num_process1)/*SI SE ACABAN LOS PROCESOS SE SALE DEL WHILE*/
		{
			break;
		}
		
		while (queue_counter < num_queues) /*WHILE PARA CAMBIAR DE COLA*/
		{
			if (process_count == num_process1) /*SI SE ACABAN LOS PROCESOS SE SALE DEL WHILE*/
			{
				break;
			}

			printf("ENTRANDO A LA COLA [%d] Y QUANTUM [%d] \n", queue_counter, queue[queue_counter].quantum);
			printf("\n");
			Process* temp = queue[queue_counter].head;

			

			
 			if(temp == NULL && cycle_count < primer_proceso) /* SI AUN NO LLEGA NINGUN PROCESO SE SUMA UN CICLO */
			{
				printf("\n ############ CICLO [%d] ###########\n \n ", cycle_count);
				cycle_count += 1;

			}else if(temp == NULL && cycle_count == primer_proceso) /* SE AÑADEN TODOS LOS PROCESOS QUE LLEGAN PRIMERO */
			{	
				for (int i = 0; i < num_process1; i++)
					{
						if (atoi(file_data -> lines[i][2]) == primer_proceso)
						{
							Process* process = malloc(sizeof(Process));
							process -> pid = atoi(file_data -> lines[i][1]);
							process -> state = 0;
							process -> init_time = atoi(file_data -> lines[i][2]);
							process -> name = file_data -> lines[i][0];
							process -> cycles = atoi(file_data -> lines[i][3]);
							process -> cycle_count = atoi(file_data -> lines[i][3]);
							process -> wait = atoi(file_data -> lines[i][4]);
							process -> waiting_delay = atoi(file_data -> lines[i][5]);
							process -> priority = 0;
							process -> quantum = queue[0].quantum;
							process -> salio_de_wait = 1;
							process -> ciclo_wait = 0;
							process -> next = NULL;
							process -> interrupciones = 0;
							process -> turnos_cpu = 0;
							process -> turnaround = 0;
							process -> response = 0;
							process -> active_time = 0;
							process -> entra_primera_vez = false;
							process -> primera_vez = 0;
							
							list_append(queue,0,process,0);

						}

					}

			}else
			{
				if ((temp == NULL || (temp ->state == 2 && temp -> next == NULL))&& cycle_count > primer_proceso) /*SI NO HAY NINGÚN PROCESO A LA COLA SE CAMBIA DE COLA*/
				{
					printf("\n ############ CICLO [%d] ###########7\n \n ", cycle_count);
					queue_counter += 1;
					
					if (cycle_count == S || (cycle_count - reset) == S)
					{
						printf("$$$$$$$$$$$ SE RESETEA LA COLA $$$$$$$$$$$$$$$$ \n");
						reset_queue(queue,num_queues);
						running_process = 0;
						queue_counter = 0;
						reset = cycle_count;
						printf("LA COLA SE VE ASI: \n \n");
						display(queue,num_queues);
					}
					
					
					add_process(queue,num_procesos,file_data,cycle_count);
					change_waiting(queue,num_queues,cycle_count,running_process);
					printf("\n");

				}

				
				while (temp != NULL)
				{

					/*ESTE IF ES PARA REVISAR SI HAY PROCESOS EN COLAS DE MAYOR PRIORIDAD. SI HAY PROCESOS EN COLAS ANTERIORES Y NO HAY NINGUN PROCESO
					CORRIENDO SE SUBE DE COLA*/
					
					change_waiting(queue,num_queues,cycle_count,running_process);
					if (salio_wait == true)
					{
						if(cola_wait <= temp -> priority){
							queue_counter = cola_wait;
							salio_wait = false;
							cola_wait = 1000;
							break;
						}
					}
					

					int hay_procesos = revisar_colas(queue,num_queues);
					if (hay_procesos < queue_counter && running_process == 0 && hay_procesos != -1)
					{
						
						queue_counter = hay_procesos;
						break;
					}

					/*SE VAN AGERGANDO LOS PROCESOS A MEDIDA QUE LLEGA EL CICLO QUE LES TOQUE*/
					add_process(queue,num_procesos,file_data,cycle_count);

					printf("\n ############ CICLO [%d] ###########\n \n ", cycle_count);

					

					if (temp -> state == 2 && (cycle_count - temp -> ciclo_wait) < temp -> waiting_delay) /*SI SE ESTA EN ESTADO WAIT SE PASA AL SIGUIENTE */
					{	
						printf("EL PROCESO [%d] ESTA ESPERANDO \n",temp -> pid );
						temp -> state = 2;
						temp = temp -> next;
						if (temp != NULL && temp -> state != 2)
						{
							printf("EL PROCESO DE PID [%d] SIGUE CORRIENDO - ", temp -> pid);
							running_process = 1; /*MUESTRA QUE HAY UN PROCESO CORRIENDO ASI QUE NO SE PUEDE CAMBIAR DE COLA SI ES QUE HAY UN PROCESO DE MAYOR PRIORIDAD*/
							temp -> cycle_count -= 1; /*SE DISMINUYE EN 1 LA CANTIDAD DE CICLOS QUE LE QUEDAN AL PROCESO*/
							temp -> quantum -= 1; /*DISMINUYE EN 1 LA CANTIDAD DE QUANTUM QUE LE QUEDA AL PROCESO*/
							printf("LE QUEDAN [%d] CICLOS Y UN QUANTUM DE [%d] \n", temp -> cycle_count,temp -> quantum );
						}
						

						
						printf("\n");
						printf("LA COLA SE VE ASI: \n \n");
						display(queue,num_queues);
						

					}else if (temp -> cycle_count > 0 && temp -> quantum > 0 && (temp -> state == 1 || temp -> state == 0)) /*ESTE IF REVISA SI LA CANTIDAD DE CICLOS AUN NO SE ACABA Y AÚN QUEDA QUANTUM*/
					{	

						if ((temp -> cycles - temp -> cycle_count) == temp -> wait && temp -> wait != 0  && temp -> salio_de_wait == 1)/*ENTRA A ESTADO WAIT*/
						{
							
							printf("EL PROCESO [%d] DEBE ESPERAR\n \n ", temp -> pid);
							Process* se_cambia = temp; /*SE CREA UN PROCESO AUXILIAR*/
							int id_aux = temp -> pid;
							int priority = temp -> priority;
							se_cambia -> pid = id_aux;
							if (priority == 0)
							{
								se_cambia -> priority = 0;
								se_cambia -> quantum = queue[0].quantum;
							}else{
								se_cambia -> priority = queue_counter-1;
								se_cambia -> quantum = queue[queue_counter-1].quantum;
							}
							se_cambia -> state = 2;
							se_cambia -> ciclo_wait = cycle_count;
							se_cambia -> salio_de_wait = 0;
							se_cambia -> cycles = temp -> cycle_count;
							running_process = 0;
							change_priority(queue,priority,se_cambia -> priority,se_cambia);
							temp = temp -> next; /*SE PASA AL PROCESO SIGUIENTE*/
							printf("LA COLA SE VE ASI: \n \n");
							display(queue,num_queues);

						
							
						}else{
							if (temp -> state == 0)
							{
								temp -> turnos_cpu += 1;
								if (temp -> entra_primera_vez == false)
								{
									temp -> primera_vez = cycle_count - temp -> init_time;
									temp -> entra_primera_vez = true;
								}
								
								
							}
							temp -> active_time += 1;
							
							printf("EL PROCESO DE PID [%d] SIGUE CORRIENDO - ", temp -> pid);
							temp -> state = 1;
							running_process = 1; /*MUESTRA QUE HAY UN PROCESO CORRIENDO ASI QUE NO SE PUEDE CAMBIAR DE COLA SI ES QUE HAY UN PROCESO DE MAYOR PRIORIDAD*/
							temp -> cycle_count -= 1; /*SE DISMINUYE EN 1 LA CANTIDAD DE CICLOS QUE LE QUEDAN AL PROCESO*/
							temp -> quantum -= 1; /*DISMINUYE EN 1 LA CANTIDAD DE QUANTUM QUE LE QUEDA AL PROCESO*/
							printf("LE QUEDAN [%d] CICLOS Y UN QUANTUM DE [%d] \n", temp -> cycle_count,temp -> quantum );
							printf("\n");
							printf("LA COLA SE VE ASI: \n \n");
							display(queue,num_queues);

						}

					/*ESTE IF ES PARA VER SI SE ACABAN LOS CICLOS CUANDO HAY QUANTUM O CUANDO EL QUANTUM Y LOS CICLOS SE ACABAN
					AL MISMO TIEMPO*/
					}else if (((temp -> cycle_count == 0 && temp -> quantum > 0) || (temp -> cycle_count == 0 && temp -> quantum == 0)) && temp -> state == 1)
					{
						
						temp -> state = 3;
						int id_aux = temp -> pid;
						printf("NUMERO DE INTERRUPCIONES DEL PROCESO [%d] : [%d]  --- \n",id_aux, temp -> interrupciones);
						printf("NUMERO DE TURNOS DE CPU PROCESO [%d] : [%d]  --- \n",id_aux, temp -> turnos_cpu);
						printf("TURNAROUND TIME PROCESO [%d] : [%d]  --- \n",id_aux, cycle_count - temp -> init_time);
						printf("RESPONSE PROCESO [%d] : [%d]  --- \n",id_aux, temp -> primera_vez);
						printf("WAITING TIME PROCESO [%d] : [%d]  --- \n",id_aux, (cycle_count - temp -> init_time - temp -> active_time));
						printf("EL PROCESO DE PID [%d] TERMINO Y ESTA SIENDO ELIMINADO \n \n", id_aux);
						printf("QUEDAN [%d] PROCESOS \n \n", process_count);
						printf("LA COLA SE VE ASI: \n \n");
						fprintf(output_file,"%s,%d,%d,%d,%d,%d\n",temp -> name,temp -> turnos_cpu,temp -> interrupciones,cycle_count - temp -> init_time, temp -> primera_vez,(cycle_count - temp -> init_time - temp -> active_time));
						running_process = 0;
						display(queue,num_queues);

						temp = temp -> next; /*SE PASA AL SIGUIENTE PROCESO*/
						 /*SE BORRA EL PROCESO DE LA COLA*/
						process_count += 1; 

						if (temp != NULL && temp -> state != 2)
						{
							printf("EL PROCESO DE PID [%d] SIGUE CORRIENDO - ", temp -> pid);
							running_process = 1; /*MUESTRA QUE HAY UN PROCESO CORRIENDO ASI QUE NO SE PUEDE CAMBIAR DE COLA SI ES QUE HAY UN PROCESO DE MAYOR PRIORIDAD*/
							temp -> cycle_count -= 1; /*SE DISMINUYE EN 1 LA CANTIDAD DE CICLOS QUE LE QUEDAN AL PROCESO*/
							temp -> quantum -= 1; /*DISMINUYE EN 1 LA CANTIDAD DE QUANTUM QUE LE QUEDA AL PROCESO*/
							printf("LE QUEDAN [%d] CICLOS Y UN QUANTUM DE [%d] \n", temp -> cycle_count,temp -> quantum );
						}
						/*SE AUMENTA EN 1 EL CONTADOR DE PROCESOS CUANDO SALE UN PROCESO*/

					/*ESTE IF DICE SI AUN QUEDAN CICLOS PERO NO QUANTUM*/
					}else if(temp -> cycle_count > 0 && temp -> quantum == 0 && temp -> state == 1){

	
						Process* se_cambia = temp; /*SE CREA UN PROCESO AUXILIAR*/
						int id_aux = temp -> pid;
						se_cambia -> pid = id_aux;
						se_cambia -> priority += 1;
						se_cambia -> quantum = queue[temp -> priority].quantum;
						se_cambia -> interrupciones += 1;
						se_cambia -> state = 0;
						temp = temp -> next; /*SE PASA AL PROCESO SIGUIENTE*/
						printf("EL PROCESO DE PID [%d] CAMBIA DE PRIORIDAD - AHORA SU QUANTUM ES [%d] Y SU PRIORIDAD ES [%d] \n \n", se_cambia -> pid,se_cambia -> quantum,se_cambia -> priority );
						change_priority(queue,queue_counter,se_cambia -> priority,se_cambia); /*SE CAMBIA LA PRIORIDAD A UNA MENOS Y SE BAJA UNA COLA*/
						running_process = 0;
						
						printf("LA COLA SE VE ASI: \n \n");
						display(queue,num_queues);
						if (temp != NULL && temp -> state != 2)
						{
							printf("EL PROCESO DE PID [%d] SIGUE CORRIENDO - ", temp -> pid);
							running_process = 1; /*MUESTRA QUE HAY UN PROCESO CORRIENDO ASI QUE NO SE PUEDE CAMBIAR DE COLA SI ES QUE HAY UN PROCESO DE MAYOR PRIORIDAD*/
							temp -> cycle_count -= 1; /*SE DISMINUYE EN 1 LA CANTIDAD DE CICLOS QUE LE QUEDAN AL PROCESO*/
							temp -> quantum -= 1; /*DISMINUYE EN 1 LA CANTIDAD DE QUANTUM QUE LE QUEDA AL PROCESO*/
							printf("LE QUEDAN [%d] CICLOS Y UN QUANTUM DE [%d] \n", temp -> cycle_count,temp -> quantum );
						}
						

					}
					cycle_count += 1;
					if (cycle_count == S || (cycle_count - reset) == S)
					{
						printf("$$$$$$$$$$$ SE RESETEA LA COLA $$$$$$$$$$$$$$$$ \n");
						
						reset_queue(queue,num_queues);
						Process* temp2 = queue[0].head;
						if (temp2 != NULL)
						{
							while (temp2 != NULL)
							{
								if (temp2 -> state != 1)
								{
									temp2 -> quantum = queue[0].quantum;
									
								}
								temp2 = temp2 -> next;

							}							
						}
						free(temp2);
						
						
						
						
						running_process = 0;
						queue_counter = 0;
						
						reset = cycle_count;
						printf("LA COLA SE VE ASI: \n \n");
						display(queue,num_queues);
					}
					
					 /*CUANDO SE PASA POR TODOS LOS IFS SE COMPLETA UN CICLO Y SE SUMA AL CONTADOR DE CICLOS*/
				}
				
			}
			
		}
		
	}

}