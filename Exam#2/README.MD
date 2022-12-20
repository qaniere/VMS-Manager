# SIF1015 - Examen final

Quentin Anière - ANIQ69280300

## Question 1 & 2 Programation

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
