# SIF1015 - Devoir #2 
# Manuel utilisateur

## Description

Ce projet est la suite logique du devoir 1. La gestion de la liste chaînée des VMS est la même. Ce qui change c'est la façon dont les transactions sont lues : avant c'était à partir d'un fichier texte, maintenant c'est à partir de sockets.

Un client, via son interface graphique compose une transaction qui est constituée d'opérations. La transaction est envoyée au serveur qui la traite et retourne le résultat à l'utilisateur.

## Compilation

### Serveur

#### Avec makefile

```bash
make server
```

#### Sans makefile

```bash
gcc -o server server.c 
```

### Client

#### Avec makefile

```bash
make client
```

#### Sans makefile

```bash
gcc -o client client.c 
```

## Utilisation

### Serveur

#### Avec makefile

```bash
make launch-server
```

#### Sans makefile

```bash
./server
```

### Client

#### Avec makefile

```bash
make launch-client
```

#### Sans makefile

```bash
./client
```

## Opérations possibles

 * A - Ajouter une VMS
 * L x - y - Lister les VMS avec un identifiant compris entre x et y
 * E x - Éliminer une VMS avec un identifiant x
 * X x y - Exécuter le code binare compris dans le fichier y sur la VMS x
