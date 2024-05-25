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

// functie pentru insert BST
BST *newNode(team val) {
  BST *new = (BST *)malloc(sizeof(BST));
  new->val = val;
  new->left = new->right = NULL;
  return new;
}

//functie care afiseaza BST-ul in ordine descrescatoare si salveaza echipele in stiva
void afisareBSTDesc(BST *root, FILE *file, int runda, Stack **top) {
  if (root != NULL) {
    afisareBSTDesc(root->right, file, runda, top);
    fprintf(file, "%-33s -  %.2f\r\n", root->val.numele_echipei,
            suma_puncte_echipa(root->val) + runda);
    push(top, root->val);
    afisareBSTDesc(root->left, file, runda, top);
  }
}

//functie care insereaza un nou nod in BST
BST *insert(BST *node, team val) {
  if (node == NULL) return newNode(val);

  if (suma_puncte_echipa(val) < suma_puncte_echipa(node->val))
    node->left = insert(node->left, val);
  else if (suma_puncte_echipa(val) > suma_puncte_echipa(node->val))
    node->right = insert(node->right, val);
  else if (strcmp(val.numele_echipei, node->val.numele_echipei) > 0)
    node->right = insert(node->right, val);
  else
    node->left = insert(node->left, val);

  return node;
}

//functie care creaza un nou nod pentru AVL
AVLNode *creareAVLNode(team val) {
  AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));

  node->val = val;
  node->score = medie_echipe(val);
  node->left = node->right = NULL;
  node->height = 1;
  return node;
}

//functie care returneaza inaltimea unui nod
int height(AVLNode *node) { return (node == NULL) ? 0 : node->height; }

//functie care calculeaza factorul de echilibru al unui nod
int getBalance(AVLNode *node) {
  if (node == NULL) return 0;
  return height(node->left) - height(node->right);
}

AVLNode *rightRotate(AVLNode *y) {
  AVLNode *x = y->left;
  AVLNode *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = 1 + (height(y->left) > height(y->right) ? height(y->left)
                                                      : height(y->right));
  x->height = 1 + (height(x->left) > height(x->right) ? height(x->left)
                                                      : height(x->right));

  return x;
}

//functie care roteste la dreapta in AVL
AVLNode *leftRotate(AVLNode *x) {
  AVLNode *y = x->right;
  AVLNode *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = 1 + (height(x->left) > height(x->right) ? height(x->left)
                                                      : height(x->right));
  y->height = 1 + (height(y->left) > height(y->right) ? height(y->left)
                                                      : height(y->right));

  return y;
}

//functie care insereaza un nou nod in AVL si il echilibreaza
AVLNode *insertAVLNode(AVLNode *node, team val) {
  if (node == NULL) return creareAVLNode(val);

  float score = medie_echipe(val);

  if (score > node->score)
    node->left = insertAVLNode(node->left, val);
  else if (score < node->score)
    node->right = insertAVLNode(node->right, val);
  else {
    if (strcmp(val.numele_echipei, node->val.numele_echipei) > 0)
      node->left = insertAVLNode(node->left, val);
    else
      node->right = insertAVLNode(node->right, val);
  }

  node->height =
      1 + (height(node->left) > height(node->right) ? height(node->left)
                                                    : height(node->right));

  int balance = getBalance(node);

  if (balance > 1 && score > node->left->score) return rightRotate(node);

  if (balance < -1 && score < node->right->score) return leftRotate(node);

  if (balance > 1 && score < node->left->score) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && score > node->right->score) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

//functie pentru afisare AVL
void printAVL(AVLNode *root, FILE *f) {
  fprintf(f, "\r\nTHE LEVEL 2 TEAMS ARE:\r\n");
  fprintf(f, "%s\r\n", root->left->left->val.numele_echipei);
  fprintf(f, "%s\r\n", root->left->right->val.numele_echipei);
  fprintf(f, "%s\r\n", root->right->left->val.numele_echipei);
  fprintf(f, "%s\r\n", root->right->right->val.numele_echipei);
}

//functii pentru eliberarea memoriei
void freePlayer(player p) {
  free(p.nume);
  free(p.prenume);
}

void freeTeam(team t) {
  for (int i = 0; i < t.nr_jucatori; i++) {
    freePlayer(t.jucatori[i]);
  }
  free(t.jucatori);
  free(t.numele_echipei);
}

void freeList(Node *head) {
  Node *temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    freeTeam(temp->val);
    free(temp);
  }
}

void freeQueue(Queue *q) {
  while (q->front != NULL) {
    Node *temp = q->front;
    q->front = q->front->next;
    freeTeam(temp->val);
    free(temp);
  }
  free(q);
}

void freeStack(Stack *top) {
  Stack *temp;
  while (top != NULL) {
    temp = top;
    top = top->next;
    freeTeam(temp->val);
    free(temp);
  }
}

void freeBST(BST *root) {
  if (root == NULL) return;
  freeBST(root->left);
  freeBST(root->right);
  freeTeam(root->val);
  free(root);
}

void freeAVL(AVLNode *root) {
  if (root == NULL) return;
  freeAVL(root->left);
  freeAVL(root->right);
  freeTeam(root->val);
  free(root);
}

// functie care contine toate functiile de eliberare a memoriei
void freeAllMemory(Node *listHead, Queue *queue, Stack *stack, BST *bstRoot,
                   AVLNode *avlRoot) {
  freeList(listHead);
  freeQueue(queue);
  freeStack(stack);
  freeBST(bstRoot);
  freeAVL(avlRoot);
}

