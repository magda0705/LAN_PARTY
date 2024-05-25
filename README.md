# [LAN_Party]-Documentație Cod Sursă

## Descrierea temei:
Facultatea de Automatica si Calculatoare prin LSAC organizează in fiecare semestru un LAN Party la care participă toți studenții care vor sa își testeze abilitățile la un anumit joc. Se dorește realizarea unei soluții software(program executabil) ce poate automatiza acest proces.

## Structuri de Date Principale
- `player`: Reprezintă un jucător, conținând nume, prenume și puncte.
- `team`: Reprezintă o echipă, conținând numele echipei, numărul de jucători și un vector de jucători.
- `Node`: Un nod folosit în liste, stive și cozi, care conține o echipă și un pointer către următorul nod.
- `Queue`: O coadă folosită pentru gestionarea echipelor în ordine FIFO (First In First Out).
- `Stack`: O stivă folosită pentru stocarea temporară a echipelor în ordine LIFO (Last In First Out).
- `BST`: Un arbore de căutare binară pentru gestionarea echipelor bazat pe punctaj.
- `AVLNode`: Un nod de arbore AVL echilibrat, utilizat pentru a menține echilibrul și eficiența operațiilor.

## Funcții

### `data_player(FILE *file)`
- **Descriere**: Citeste datele unui jucător dintr-un fișier.
- **Parametri**: `file` - pointer la fișierul de intrare.
- **Returnează**: O structură `player` completată cu date.

### `data_team(FILE *file)`
- **Descriere**: Citeste datele unei echipe, inclusiv informațiile despre jucătorii săi.
- **Parametri**: `file` - pointer la fișierul de intrare.
- **Returnează**: O structură `team` completată.

### `createList(FILE *file, int nrteams)`
- **Descriere**: Creează o listă legată de echipe citind date dintr-un fișier.
- **Parametri**: `file` - fișier de intrare, `nrteams` - numărul de echipe.
- **Returnează**: Un pointer la primul nod (`Node`) al listei create.

### `afisare(Node *head, FILE *file)`
- **Descriere**: Afișează toate echipele din lista legată într-un fișier.
- **Parametri**: `head` - primul nod al listei, `file` - fișierul de ieșire.

### `valoare_n(int n)`
- **Descriere**: Calculează cea mai mare putere a lui 2 mai mică sau egală cu `n`.
- **Parametri**: `n` - numărul de echipe.
- **Returnează**: Valoarea calculată.

### `medie_echipe(team team)`
- **Descriere**: Calculează media punctelor obținute de o echipă.
- **Parametri**: `team` - echipa pentru care se calculează media.
- **Returnează**: Media punctelor.

### `deleteNode(Node **head, float key)`
- **Descriere**: Șterge un nod din lista pe baza mediei punctelor.
- **Parametri**: `head` - pointer la primul nod, `key` - media punctelor pentru criteriul de ștergere.

### `countNodes(Node *head)`
- **Descriere**: Numără nodurile din lista legată.
- **Parametri**: `head` - primul nod al listei.
- **Returnează**: Numărul de noduri.

### `reducere_echipe(Node **head, int nrteams)`
- **Descriere**: Reduce numărul de echipe din listă la cea mai apropiată putere a lui 2.
- **Parametri**: `head` - pointer la lista de echipe, `nrteams` - numărul actual de echipe.

### `createQueue()`
- **Descriere**: Creează și inițializează o coadă.
- **Returnează**: Un pointer la coada creată.

### `enQueue(Queue *q, team echipa)`
- **Descriere**: Adaugă o echipă în coadă.
- **Parametri**: `q` - coada în care se adaugă, `echipa` - echipa adăugată.

### `printQueue(Queue *queue)`
- **Descriere**: Afișează conținutul unei cozi.
- **Parametri**: `queue` - coada de afișat.

### `deQueue(Queue *queue)`
- **Descriere**: Elimină elementul din fața cozii.
- **Parametri**: `queue` - coada din care se elimină.

### `push(Stack **top, team team)`
- **Descriere**: Adaugă o echipă în vârful stivei.
- **Parametri**: `top` - vârful stivei, `team` - echipa de adăugat.

### `suma_puncte_echipa(team echipa)`
- **Descriere**: Calculează suma punctelor unei echipe.
- **Parametri**: `echipa` - echipa pentru care se face calculul.
- **Returnează**: Suma punctelor.

### `invingatori_pierzatori(FILE *file, Queue *queue, int runda)`
- **Descriere**: Imparte echipele din coadă în învingători și pierzători după o rundă de competiție.
- **Parametri**: `file` - fișier pentru înregistrare, `queue` - coada cu echipele, `runda` - numărul rundei curente.

### Funcții pentru gestionarea AVL și BST
- **Descriere**: Include funcții pentru crearea, inserarea și afișarea nodurilor în arbori AVL și BST, gestionarea echilibrului și afișarea în ordine descrescătoare.

### Funcții pentru eliberarea memoriei
- **Descriere**: Include diverse funcții pentru eliberarea memoriei alocate dinamic pentru diferite structuri de date utilizate în program.

Această documentație ar trebui să ajute la înțelegerea și utilizarea eficientă a codului în contextele aplicative dorite.


### Cum poți verifica dacǎ ai lucrat corect?
Prin rularea comenzii: "./checker.sh" .
Pentru mai multe detalii despre checker, accesați acest link: https://github.com/sda-ab/lan-party-02-checker

### Cum poti compila programul?
Prin rularea fişierelor vom folosi comanda: "make" .

### Cerințele temei se regǎsesc în urmǎtorul link: https://ocw.cs.pub.ro/courses/sda-ab/tema1




