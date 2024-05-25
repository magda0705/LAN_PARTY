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

// functie pentru crearea unei cozi
Queue *createQueue() {
  Queue *q;
  q = (Queue *)malloc(sizeof(Queue));
  if (q == NULL) return NULL;
  q->front = q->rear = NULL;
  return q;
}

// functie pentru adaugarea elementelor in coada
void enQueue(Queue *q, team echipa) {
  Node *newNode = malloc(sizeof(Node));
  newNode->val = echipa;
  newNode->next = NULL;

  if (q->rear == NULL)
    q->rear = newNode;
  else {
    q->rear->next = newNode;
    q->rear = newNode;
  }

  if (q->front == NULL) q->front = q->rear;
}

// functie pentru afisarea continutului unei cozi
void printQueue(Queue *queue) {
  if (queue == NULL) {
    printf("Queue not initialized.\n");
    return;
  }

  Node *current = queue->front;
  if (current == NULL) {
    printf("Queue is empty.\n");
  } else {
    while (current != NULL) {
      printf("%s\n", current->val.numele_echipei);
      current = current->next;
    }
    printf("\n");
  }
}

//functie pentru eliminarea unui element din coada
void deQueue(Queue *queue) {
  if (queue->front == NULL) return;
  Node *temp = queue->front;
  queue->front = queue->front->next;
  if (queue->front == NULL) queue->rear = NULL;
}

//functie pentru adaugarea unui element in varful stivei
void push(Stack **top, team team) {
  Stack *newNode = (Stack *)malloc(sizeof(Stack));
  newNode->val = team;
  newNode->next = *top;
  *top = newNode;
}

//functie pentru calcularea punctelor unei echipe
float suma_puncte_echipa(team echipa) {
  float sum = 0;

  for (int i = 0; i < echipa.nr_jucatori; i++) {
    sum = sum + echipa.jucatori[i].puncte;
  }

  return sum / echipa.nr_jucatori;
}

//functie pentru impartirea echipelor dupa fiecare runda in ingingatori si pierzatori
void invingatori_pierzatori(FILE *file, Queue *queue, int runda) {
  Stack *invingatori = NULL, *pierzatori = NULL;
  while (queue->front != NULL) {
    Node *prima_echipa = queue->front;
    deQueue(queue);
    Node *adoua_echipa = queue->front;
    deQueue(queue);

    fprintf(file, "%-33s-%33s\r\n", prima_echipa->val.numele_echipei,
            adoua_echipa->val.numele_echipei);
    if (suma_puncte_echipa(prima_echipa->val) >
        suma_puncte_echipa(adoua_echipa->val)) {
      push(&pierzatori, adoua_echipa->val);
      push(&invingatori, prima_echipa->val);

    } else if (suma_puncte_echipa(prima_echipa->val) <=
               suma_puncte_echipa(adoua_echipa->val)) {
      push(&pierzatori, prima_echipa->val);
      push(&invingatori, adoua_echipa->val);
    }
  }
  fprintf(file, "\r\nWINNERS OF ROUND NO:%d\r\n", runda);
  while (invingatori != NULL) {
    fprintf(file, "%-34s-  %.2f\r\n", invingatori->val.numele_echipei,
            suma_puncte_echipa(invingatori->val) + runda);
    enQueue(queue, invingatori->val);
    invingatori = invingatori->next;
  }
}

//functie pentru salvarea echipelor de top intr o stiva
void saveTopTeams(Node *head, Stack **top) {
  Stack *tempStack = NULL;

  while (head != NULL) {
    push(top, head->val);
    head = head->next;
  }

  while (tempStack != NULL) {
    push(top, tempStack->val);
    tempStack = tempStack->next;
  }
}

// functie pentru programarea meciurilor si salvarea in top 8
void programarea_meciurilor(Node *head, int nrteams, FILE *file, Stack **top,
                            int *runda) {
  Queue *meciuri = createQueue();
  Stack *invingatori = NULL, *pierzatori = NULL;
  int nr_runde = 0;

  while (head != NULL) {
    enQueue(meciuri, head->val);
    head = head->next;
  }

  while (nrteams / 2) {
    nr_runde++;
    nrteams /= 2;
  }

  for (int i = 1; i <= nr_runde; i++) {
    fprintf(file, "\r\n--- ROUND NO:%d\r\n", i);
    invingatori_pierzatori(file, meciuri, i);

    // se salveaza top 8 echipe
    if (i == nr_runde - 3) {
      (*runda) = i;
      saveTopTeams(meciuri->front, top);
    }
  }
}

