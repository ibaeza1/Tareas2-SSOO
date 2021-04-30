#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mlfq.h"




int main(int argc, char **argv)
{




  Queue* queue = init_queue(atoi(argv[3]),atoi(argv[4]));
  /*Process* p1 = malloc(sizeof(Process));
  Process* p2 = malloc(sizeof(Process));
  Process* p3 = malloc(sizeof(Process));
  Process* p4 = malloc(sizeof(Process));

  p1 -> pid = 1;
  p1 -> priority = 0;
  p2 -> pid = 2;
  p3 -> pid = 3;
  p4 -> pid = 4;
  p2 -> priority = 1;
  p3 -> priority = 2;
  list_append(queue,1,p1,0);
  list_append(queue,1,p2,0);
  list_append(queue,1,p3,0);

  int cola = revisar_colas(queue,atoi(argv[3]));
  display(queue,atoi(argv[3]));
  printf("\n");
  reset_queue(queue,atoi(argv[3]));*/
  simulation(queue,atoi(argv[3]),3, argv[1], atoi(argv[5]));

  list_destroy(queue,atoi(argv[3]));
  

 
  free(queue);

}




















