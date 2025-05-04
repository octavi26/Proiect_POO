# 3D Render Engine

### Descriere
Aplicatie urmareste sa simuleze un sistem Ray-Tracing pentru a afisa intr-o fereastra diferite forme in spatiu. Practic, programul genereaza o imagine a carei pixeli sunt modificati in fiecare frame cu o valuare de gri in functie de de ce geometrie se afla in fata obiectului camera.
Mai precis, obiectul camera reprezinta un punct in spatiu si un plan direct in fata sa la o distanta (in cod numita FOV) fixa pe care se afla intr-un grid alte puncte. Camera genereaza niste raze din centrul sau catre fiecare punct din planul mentionat pentru fiecare pixel. Aceste raze au scopul de a verifica daca lovesc figura geometrica, prin a teste pe de-a lungul ei o serie de puncte pana cand unul dintre aceste indeplineste relatiile matematice suficiente pentru a determina ca se afla in interiorul formei. Apoi, daca raza aferenta pixelului curent se intersecteaza cu geometria formei, pixelul ia o valoare de luminozitate in functie de cat de departe este de o sursa de lumina, cat si in functie de puterea sursei respective.

### Tema 0

- [X] Nume proiect (poate fi schimbat ulterior)
- [X] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [X] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi
- [X] constructori de inițializare cu parametri
- [X] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [X] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [X] cât mai multe `const` (unde este cazul)
- [X] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [X] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [X] tag de `git`: de exemplu `v0.1`
- [X] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [ ] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [X] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [X] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [X] apelarea constructorului din clasa de bază din constructori din derivate
  - [X] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [X] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [X] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [ ] smart pointers (recomandat, opțional)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [X] funcții și atribute `static`
- [X] STL
- [X] cât mai multe `const`
- [X] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [X] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
- [X] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

0. Biblioteci necesare pe Linux (presupunem sistem de operare bazat pe Debian)
```sh
sudo apt-get update && \
  sudo apt-get install libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev \
    libfreetype6-dev
```

Dacă lipsesc și alte biblioteci, ștergeți folder-ul de build de la pasul 1 și reconfigurați proiectul după ce ați instalat ce lipsea.

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.

3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit
