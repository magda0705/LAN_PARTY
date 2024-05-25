#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FUNCTI_H

// definirea structurii de date pentru jucator
typedef struct data_player {
  char *nume;
  char *prenume;
  int puncte;
} player;

// definirea structurii de date a echipei
typedef struct data_team {
  int nr_jucatori;
  char *numele_echipei;
  player *jucatori;
} team;

// definirea structurii pentru lista(cum va arata)
typedef struct Node Node;
struct Node {
  team val;
  struct Node *next;
};

Node *createList(FILE *, int);
team data_team(FILE *file);
player data_player(FILE *file);
void afisare(Node *head, FILE *file);
int valoare_n(int);
float medie_echipe(team);
void deleteNode(Node **, float);
void reducere_echipe(Node **, int);
int countNodes(Node *);

// definirea structurii pentru meciul dintre 2 echipe
typedef struct match {
  team team_1;
  team team_2;
  struct match *next;
} match;

// definirea unei structuri de cozi
typedef struct Queue {
  Node *front;
  Node *rear;
} Queue;

void enQueue(Queue *, team);

// struct pentru definirea stivei
typedef struct Stack {
  team val;
  struct Stack *next;

} Stack;
void push(Stack **, team);

// struct pentru definire BST(Binary Search Tree)
typedef struct BST {
  team val;
  struct BST *left;
  struct BST *right;
} BST;

BST *newNode(team);
void afisareBSTDesc(BST *, FILE *, int, Stack **);
BST *insert(BST *, team);
void programarea_meciurilor(Node *, int, FILE *, Stack **, int *);

