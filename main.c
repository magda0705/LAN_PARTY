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
  if (task[1] == 1) {
    reducere_echipe(&lista, nrteams);
    afisare(lista, out);
  }
  if (task[2] == 1) {
    programarea_meciurilor(lista, nrteams, out, &top, &runda);
  }
  if (task[3] == 1) {
    BST *root = NULL;
    while (top != NULL) {
      root = insert(root, top->val);
      top = top->next;
    }
    fprintf(out, "\r\nTOP 8 TEAMS:\r\n");
    afisareBSTDesc(root, out, runda, &topTeams);
    while (topTeams != NULL) {
      push(&top, topTeams->val);
      topTeams = topTeams->next;
    }
  }

  if (task[4] == 1) {
    AVLNode *root = NULL;
    while (top != NULL) {
      root = insertAVLNode(root, top->val);
      top = top->next;
    }
    printAVL(root, out);
  }

   //eliberarea memoriei
  void freeAllMemory(listHead, queue, stack, bstRoot, avlRoot);
  return 0;
}

