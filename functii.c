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

// functie care returneaza cea mai mare putere a lui 2 mai mica sau egala cu n
int valoare_n(int n) {
  if (n <= 1) return 0;

  int power = 1;
  while (power * 2 <= n) {
    power *= 2;
  }
  return power;
}

// functie care calculeaza media punctelor unei echipe
float medie_echipe(team team) {
  float sum = 0;
  float rez = 0;

  for (int i = 0; i < team.nr_jucatori; i++) {
    sum = sum + team.jucatori[i].puncte;
  }
  rez = sum / team.nr_jucatori;
  return rez;
}

// functie pentru stergerea unui nod din lista pe baza unei conditii(media punctelor unei echipe)
void deleteNode(Node **head, float key) {
  Node *temp = *head, *prev = NULL;

  if (temp != NULL && medie_echipe(temp->val) == key) {
    *head = temp->next;
    free(temp);
    return;
  }
  while (temp != NULL && medie_echipe(temp->val) != key) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL) return;

  prev->next = temp->next;

  free(temp);
}

// functie pentru numararea nodurilor dintr-o lista 
int countNodes(Node *head) {
  int count = 0;
  Node *current = head;

  while (current != NULL) {
    count++;
    current = current->next;
  }

  return count;
}

// functie care reduce numarul de echipe din lista la o putere a lui 2
void reducere_echipe(Node **head, int nrteams) {
  int new_nr_teams = valoare_n(nrteams);
  Node *help = *head;
  float scor = 0;
  float min = 10;

  for (int i = 0; i < nrteams - new_nr_teams; i++) {
    min = 10;
    help = *head;
    while (help != NULL) {
      scor = medie_echipe(help->val);

      if (scor < min) min = scor;

      help = help->next;
    }
    deleteNode(head, min);
  }
  // printf("%d", countNodes(*head));
}

