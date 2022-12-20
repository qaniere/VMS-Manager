# SIF1015 - Examen final

Quentin Anière - ANIQ69280300

## Partie 1 & 2 - Programation

Le serveur écoute des clients, qui peuvent lui envoyer des transactions.

Une transaction se compose ainsi :
```
S <filepath>
```

Le serveur boucle sur une FIFO concurrente, et attend des transactions. Il les traite une par une, et répond au client avec les informations suivantes :
```
  * Numéro d'INODE
  * Nombre de liens
  * Taille du fichier (octets)
  * Nombre de blocs 
```

Il renvoie au client un message d'erreur si le fichier n'existe pas.

Instructions de compilation et d'utilisation à la page suivante

## Partie 3 
### Question A

La commande *ls –l /proc/756990/fd* affiche tous les descripteur de fichier ouverts par le processus 756990. 

On observe que 4 descripteurs sont des pts (pseudo-terminal slave), ce qui signifie que le processus utilise l'affichage console.

On observe également 7 descripteurs qui sont des sockets, c'est via ces descripteurs que le serveur communique avec les clients.

### Question B

Certaines plages mémoires du thread main sont les mêmes que celles des threads lancés car ils partagent la même mémoire pour certaines données, comme les variables globales, les constantes par exemple.

### Question C

La liste des fichiers ouvertes est différente, on peut remarquer que certains descripteurs de fichier de type socket on disparu. Cela signifie que ces sockets ont été fermées, soit par le serveur, soit par le client, en raison d'une erreur ou d'une déconnexion.

\pagebreak

### Compilation
#### Serveur

#### Avec makefile

```bash
make server
```

#### Sans makefile

```bash
gcc -o server server.c 
```

#### Client

#### Avec makefile

```bash
make client
```

#### Sans makefile

```bash
gcc -o client client.c 
```

### Utilisation

#### Serveur

#### Avec makefile

```bash
make launch-server
```

#### Sans makefile

```bash
./server
```

#### Client

#### Avec makefile

```bash
make launch-client
```

#### Sans makefile

```bash
./client
```

#### Options

Pour choisir le port (client et serveur) :

#### Avec makefile

```bash
make launch-< server | client > port=< port >
```

#### Sans makefile

```bash
./< server | client > < port >
```
