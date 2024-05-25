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
