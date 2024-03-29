#### Sima Alexandru 312CA 2022-2023
# Tema #2 - Simulator de Octave


--------------------------------------------------------------------------------
## Fisiere

- `main.c`: Contine functia `main`, in care se aloca vectorii care sa stocheze
    matricele si dimensiunile acestora, apoi se citeste de la tastatura o
    comanda si se apeleaza functia corespunzatoare din `comenzi.c`.

- `alocari.c`: Contine functii pentru alocarea, copierea si eliberarea unei
matrice, cat si pentru inserarea/stergerea unei matrice intr-un vector.

- `comenzi.c`: Contine functii pentru comenzi care sa faca citirea parametrilor
acestora, validarea lor si realizarea operatiiolr necesare.

- `operatii.c`: Contine diferite operatii pe matrice: citirea, afisarea,
partitionarea, suma elementelor, produsul si ridicarea la putere.

- `strassen.c`: Contine functii pentru calcularea produsului a 2 matrice
folosind **algoritmul lui Strassen**.


    Pentru fiecare fisier sursa (mai putin `main.c`) exista si un fisier antet,
in care sunt declarate functiile apelate si in alte fisiere.


--------------------------------------------------------------------------------
## Conventii
- Toti vectorii sunt indexati de la 0.

- Functiile care returneaza rezultatul sub forma unei noi matrice vor intoarce
*NULL*, daca a intervenit o eroare si vor dealoca doar obiectele alocate in
interiorul acestora, lasand nemodificate valorile pe care le-a primit ca
parametru.

- Functiile care aloca dinamic obiecte, dar nu le intorc, vor intoarce un cod
de eroare (asemanator functiei main: 0 - OK, 1 - a intervenit o eroare).


--------------------------------------------------------------------------------
## Functionalitate

Programul citeste o serie de comenzi de forma
"`litera_comanda` [*`parametri...`*]", pentru a opera pe o lista de matrice 
tinuta in memorie. Pentru a retine matricele, am folosit 3 vectori alocati 
dinamic: unul care retine adresa propriu-zisa a matricei, unul pentru a retine 
numarul de linii si unul pentru coloane.

Comenzile disponibile sunt urmatoarele:

- L `nr_linii` `nr_coloane`: aloca o noua matrice cu dimensiunile specificate,
apoi citeste de la tastatura `nr_linii * nr_coloane` elemente pe care le
retine in matrice, apoi adauga matricea la finalul listei (redimensionand cei 3
vectori ai listei).

- D `indice`: Afiseaza dimensiunile unei matrice din lista, citindu-le din
vectorii de linii si de coloane. Afiseaza o eroare daca matricea nu exista.

- P `indice`: Afiseaza o matrice din lista. Afiseaza o eroare daca matricea nu
exista.

- C `indice` `nr_linii` `lista_linii...` `nr_coloane` `lista_coloane...`:
Inlocuieste matricea selectata cu una noua, formata dupa urmatoarea regula:
    "elementul de pe linia *i* si coloana *j* va fi egal cu cel de pe pozitia 
*lista_linii[i]* si *lista_coloane[j]* din matricea veche."

- M `indice_1` `indice_2`: Inmulteste 2 matrice si ataseaza rezultatul la
finalul listei. Afiseaza o eroare daca macar o matrice nu exista sau daca cele 2
nu au dimensiunile corespunzatoare (numarul de coloane al primeia este diferit
de numarul de linii al celei de-a 2-a).

- O: Sorteaza matricele din lista, dupa suma elementelor sale. Pentru aceasta,
se aloca temporar un vector in care sa se retina sumele, apoi se sorteaza prin
selectie lista de matrice, interschimbandu-se toate valorile corespunzatoare
matricelor (adresa, dimensiunile si suma).

- T `indice`: Transpune matricea selectata. Pentru aceasta, se aloca o noua
matrice cu dimensiunile inversate, se copiaza in aceasta elementele pe pozitiile
transpuse, se elibereaza vechea matrice si in locul ei este retinuta cea noua in
lista. Afiseaza o eroare daca matricea nu exista.

- R `indice` `exponent`: Ridica matricea aleasa la puterea `exponent`, folosind
algoritmul de **exponentiere in timp logaritmic** (explicat mai jos). Rezultatul
este retinut in locul matricei initiale. Afiseaza o eroare daca matricea nu
exista, exponentul este negativ sau matricea nu este patratica (caz in care nu
poate fi ridicata la o putere).

- F `indice`: Sterge matricea selectata din lista (pe care apoi o scurteaza).
Afiseaza o eroare daca matricea nu exista.

- Q: Elibereaza toate resursele alocate (matricele, apoi vectorii cu care se
retine lista) si termina programul.

- S `indice_1` `indice_2`: Calculeaza produsul a 2 matrici cu dimensiuni puteri
ale lui 2 (garantat din cerinta), folosind **algoritmul lui Strassen** (explicat 
mai jos).


### Ridicarea la putere in timp logaritmic

Conceptual, algoritmul functioneaza astfel:
- Se scrie exponentul in binar (ca suma de puteri ale lui 2)
- Fiecare bit de 1 reprezinta `x^(2^p)`, care se obtine din ridicari la 
patrat ale lui x (sau ale unui factor anterior).
- La final, se inmultesc toti factorii.
`````````````````````````````````````
Exemplu:
k = 11 = 0b1011
x^k = x^(0b1000) * x^(0b10) * x^(0b1)
`````````````````````````````````````

Implementarea este realizata iterativ, folosindu-se 3 variabile
auxiliare `x`, `y` si `aux`.
- `x` ia initial valoarea bazei, apoi se ridica la patrat pentru fiecare bit din
exponent.
- `y` este initial elementul neutru (In), si se inmulteste cu `x` pentru fiecare
bit de 1 al exponentului (va fi, pe rand, fiecare factor din exemplul de mai 
sus).
- `aux` este folosit pentru a atribui celorlaltor variabile noile
valori, fara a le leakui pe cele vechi.
- Pentru a se parcurge acesti biti, exponentul se imparte succesiv la 2 si se
verifica restul.
- Rezultatul operatiei este `x * y`.


### Algoritmul lui Strassen
- Algoritmul lui Strassen realizeaza produsul a 2 matrice cu dimensiuni puteri
ale lui 2.

#### Partitionare
- Intai se partitioneaza cele 2 matrice in cate 4 cadrane, impartite ca mai jos.
Pentru aceasta, am folosit bitii codificarii cadranului si operatia `C` de 
redimensionare.
- Primul bit se refera la linii, ultimul la coloane.
- Daca un bit este 0, se iau primele `n` linii/coloane (incepand de la 0).
- Daca un bit este 1, se iau ultimele `n` linii/coloane (incepand de la `n`).
```````````````````````````````````
00 | 01
-------
10 | 11

De exemplu, cadranul 2 = 0b10 are 
ultimele (bit = 1) linii si primele 
(bit = 0) coloane.
```````````````````````````````````

#### Matrice ajutatoare
- Urmatorul pas reprezinta constructia unor matrice ajutatoare.
- Aceste matrice sunt produse dintre o suma de 1-2 cadrane din prima matrice si
1-2 din a 2-a.
- Deoarece cadranele au dimensiunile reduse la jumatate, aceste produse se pot
calcula recursiv, folosind tot algoritmul lui Strassen, pana cand se ajunge la 2
matrice 1x1, caz in care produsul lor este produsul celor 2 elemente.
- Pentru a nu ramane valori leakuite, toate sumele de cadrane necesare au fost 
calculate si memorate inainte de a fi inmultite, folosind o functie de generat 
sume partiale.
- Functia ia un vector de matrice si 3 stringuri si returneaza un alt vector de
matrice, care va contine matricele cu indicii din primul string, la care se 
aduna/scad (in functie de semnele din stringul 3) matricele corespunzatoare din
stringul 2.
````````````````````````````````````````````````````
Exemplu:
A[4] = {...}
generare_sume(A, "0123", "0101", "++--")
va genera:
{A[0] + A[0], A[1] + A[1], A[2] - A[0], A[3] - A[1]}
````````````````````````````````````````````````````

### Reconstructie
- Folosind functia de generat sume partiale, din matricele ajutatoare se mai
genereaza niste matrice intermediare, cu ajutorul carora se vor forma cadranele
matricei-rezultat.
- La final, matricea se compune din cele 4 cadrane ale sale, folosindu-se
aceeasi proprietate a cadranului ca si la **partitionare**.
