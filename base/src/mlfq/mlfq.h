#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../file_manager/manager.h"
#include <stdbool.h>
struct process;
struct queue;

typedef struct queue Queue;
typedef struct process Process;

struct process{
    int pid;
    int priority;
    int state;
    char* name;
    int init_time;
    int cycles;
    int cycle_count;
    int wait;
    int ciclo_wait;
    int quantum;
    int primera_vez;
    bool entra_primera_vez;
    int waiting_delay;
    int salio_de_wait;
    int turnos_cpu;
    int interrupciones;
    int turnaround;
    int response;
    int active_time;
    Process* next;


};

struct queue{
    int quantum;
    Process* head;
    Process* tail;

};



Queue* init_queue(int number_queues, int q);
void display(Queue* array, int number_queues);
void insert_process(Queue* cola, int priority, Process* proceso, int pos);
void delete_process(Queue* cola, int num_queue,int id);
void add_process(Queue* queue, int num_process, InputFile* file_data, int cycle_count);
void list_destroy(Queue* queue, int num_queues);
void list_append(Queue* queue,int priority, Process* proceso, int se_resetea);
void simulation(Queue* queue, int num_queues, int num_procesos,  char* file, int S, FILE* output_file);
void change_priority(Queue* queue, int priority1, int priority2, Process* proceso);
int revisar_colas(Queue* queue,int number_queues);
int is_in_queue(Queue* queue, int pid);
void change_waiting(Queue* queue, int num_queues, int cycle_count, int running_process);
void reset_queue(Queue* queue, int num_queues);

