# [LAN_Party] - Documentație Cod

## Descrierea temei
LSAC organizează un LAN Party pentru studenții Facultății de Automatică și Calculatoare, unde aceștia își pot testa abilitățile într-un joc. Se dorește realizarea unei soluții software pentru automatizarea acestui proces.

## Structuri de Date Principale
- `player`: Reprezintă un jucător (nume, prenume, puncte).
- `team`: Reprezintă o echipă (numele echipei, nr. jucători, pointer la `player`).
- `Node`: Nod din liste, stive, cozi (conține o echipă, pointer la următorul nod).
- `Queue`: Coadă pentru gestionarea echipelor.
- `Stack`: Stivă pentru stocarea temporară a echipelor.
- `BST`: Arbore de căutare binară pentru echipe (bazat pe punctaj).
- `AVLNode`: Nod AVL echilibrat pentru eficiență.

## Funcții

### `data_player(FILE *file)`
- Citește datele unui jucător dintr-un fișier.
- **Parametri**: `file` - pointer la fișierul de intrare.
- **Returnează**: Structură `player` completată.

### `data_team(FILE *file)`
- Citește datele unei echipe, inclusiv jucătorii.
- **Parametri**: `file` - pointer la fișierul de intrare.
- **Returnează**: Structură `team` completată.

### `createList(FILE *file, int nrteams)`
- Creează o listă legată de echipe dintr-un fișier.
- **Parametri**: `file` - fișier de intrare, `nrteams` - număr de echipe.
- **Returnează**: Pointer la primul nod al listei (`Node`).

### `afisare(Node *head, FILE *file)`
- Afișează echipele din lista legată într-un fișier.
- **Parametri**: `head` - primul nod al listei, `file` - fișierul de ieșire.

### `valoare_n(int n)`
- Calculează cea mai mare putere a lui 2 ≤ `n`.
- **Parametri**: `n` - număr de echipe.
- **Returnează**: Valoarea calculată.

### `medie_echipe(team team)`
- Calculează media punctelor unei echipe.
- **Parametri**: `team` - echipa pentru care se calculează media.
- **Returnează**: Media punctelor.

### `deleteNode(Node **head, float key)`
- Șterge un nod din listă pe baza mediei punctelor.
- **Parametri**: `head` - pointer la primul nod, `key` - media punctelor.

### `countNodes(Node *head)`
- Numără nodurile din lista legată.
- **Parametri**: `head` - primul nod al listei.
- **Returnează**: Numărul de noduri.

### `reducere_echipe(Node **head, int nrteams)`
- Reduce numărul de echipe la cea mai apropiată putere a lui 2.
- **Parametri**: `head` - pointer la lista de echipe, `nrteams` - numărul actual de echipe.

### `createQueue()`
- Creează și inițializează o coadă.
- **Returnează**: Pointer la coada creată.

### `enQueue(Queue *q, team echipa)`
- Adaugă o echipă în coadă.
- **Parametri**: `q` - coada, `echipa` - echipa adăugată.

### `printQueue(Queue *queue)`
- Afișează conținutul cozii.
- **Parametri**: `queue` - coada de afișat.

### `deQueue(Queue *queue)`
- Elimină elementul din fața cozii.
- **Parametri**: `queue` - coada din care se elimină.

### `push(Stack **top, team team)`
- Adaugă o echipă în vârful stivei.
- **Parametri**: `top` - vârful stivei, `team` - echipa de adăugat.

### `suma_puncte_echipa(team echipa)`
- Calculează suma punctelor unei echipe.
- **Parametri**: `echipa` - echipa pentru care se face calculul.
- **Returnează**: Suma punctelor.

### `invingatori_pierzatori(FILE *file, Queue *queue, int runda)`
- Împarte echipele în învingători și pierzători după o rundă.
- **Parametri**: `file` - fișier pentru înregistrare, `queue` - coada cu echipele, `runda` - numărul rundei.

### Funcții pentru AVL și BST
- Creează, inserează și afișează noduri în AVL și BST, mențin echilibrul și afișează în ordine descrescătoare.

### Funcții pentru eliberarea memoriei
- Eliberează memoria alocată dinamic pentru structuri de date.

## Verificare
Rulare comanda: `./checker.sh`. Detalii: [checker link](https://github.com/sda-ab/lan-party-02-checker).

## Compilare
Rulare comanda: `make`.

## Cerințe temă
Detalii: [tema link](https://ocw.cs.pub.ro/courses/sda-ab/tema1).

## Contact
Email: maria.magdalena.ion7@gmail.com  
Telefon: +40728627921
