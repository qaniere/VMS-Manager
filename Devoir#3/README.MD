# SIF1015 - Devoir #2 
# Manuel utilisateur

Projet réalisé par Julio Bangadebia et Quentin Anière

## Description


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

### Options

Pour choisir le port (client et serveur) :

#### Avec makefile

```bash
make launch-< server | client > port=< port >
```

#### Sans makefile

```bash
./< server | client > < port >
```

## Opérations possibles

 * A - Ajouter une VMS
 * L x - y - Lister les VMS avec un identifiant compris entre x et y
 * E x - Éliminer une VMS avec un identifiant x
 * X x y - Exécuter le code binare compris dans le fichier y sur la VMS x

## Fonctionnement
