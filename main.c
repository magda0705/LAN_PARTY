#include "functii.h"

int main(int argc, char *argv[]) 
{
  FILE *cin = fopen(argv[1], "r");
  FILE *din = fopen(argv[2], "r");
  FILE *out = fopen(argv[3], "w");
  int task[5];
  for (int i = 0; i < 5; i++) fscanf(cin, "%d", &task[i]);

  int nrteams;
  fscanf(din, "%d", &nrteams);

  Node *lista = createList(din, nrteams);
  Stack *top = NULL;
  Stack *topTeams = NULL;
  int runda = 0;

  if (task[0] == 1 && task[1] == 0) {
    afisare(lista, out);
  }
return 0;
}
