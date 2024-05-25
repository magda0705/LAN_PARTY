#include "functii.h"

//citirea datelor unui jucator
player data_player(FILE *file)

{
  player player;
  player.nume = (char *)malloc(50);
  fscanf(file, "%s", player.nume);
  player.prenume = (char *)malloc(50);
  fscanf(file, "%s", player.prenume);
  fscanf(file, "%d", &player.puncte);
  return player;
}

//citirea datelor despre o echipa
team data_team(FILE *file) {
  team team;

  fscanf(file, "%d ", &team.nr_jucatori);
  team.numele_echipei = (char *)malloc(50);
  fgets(team.numele_echipei, 50, file);

  if (team.numele_echipei[strlen(team.numele_echipei) - 3] == ' ')
    team.numele_echipei[strlen(team.numele_echipei) - 3] = '\0';
  else
    team.numele_echipei[strlen(team.numele_echipei) - 2] = '\0';
  team.jucatori = (player *)malloc(team.nr_jucatori * sizeof(player));
  for (int i = 0; i < team.nr_jucatori; i++)
    team.jucatori[i] = data_player(file);

  return team;
}

// crearea unei liste
Node *createList(FILE *file, int nrteams) {
  Node *head = NULL;
  Node *newNode = NULL;
  for (int i = 0; i < nrteams; i++) {
    newNode = malloc(sizeof(Node));
    newNode->val = data_team(file);
    newNode->next = head;
    head = newNode;
  }
  return head;
}

// afisarea unei liste
void afisare(Node *head, FILE *file) {
  while (head != NULL) {
    fprintf(file, "%s\r\n", head->val.numele_echipei);
    head = head->next;
  }
}

