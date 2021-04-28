#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../file_manager/manager.h"

struct process;
struct aueue;

typedef struct queue Queue;
typedef struct process Process;

struct process{
    int pid;
    int priority;
    char* state;
    char* name;
    int init_time;
    int cycles;
    int cycle_count;
    int wait;
    int quantum;
    int waiting_delay;
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
void list_append(Queue* queue,int priority, Process* proceso);
void simulation(Queue* queue, int num_queues, int num_procesos,  char*file);
void change_priority(Queue* queue, int priority1, int priority2, Process* proceso);
int revisar_colas(Queue* queue,int number_queues);

