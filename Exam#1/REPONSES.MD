SIF1015 - Autonme 2022
Quentin ANIERE - ANIQ69280300

QUESTION 1

A) Pour cette question, j'ai ajouté un entier 'ram_size' qui permet d'afficher la quantité de RAM allouée à la machine et un unsigned short 'ram' qui permet de stocker la valeur de la RAM à la structure VM_INFOS. J'ai ensuite ajouté une fonction "modify_ram" qui prend en paramètre le numéro de VM et la quantité de RAM à allouer. Cette fonction va ensuite modifier la valeur de la RAM de la VM en question. Pour l'instant, cette fonction n'est pas géré via un thread.

B) Pour gèrer cette fonctionalité via un thread, je vais appeler la fonction à l'aide de pthread. J'utilise une structure afin de passer les deux arguments à la fonction. Ensuite, je crée un thread qui va appeler la fonction "modify_ram" avec les arguments passés dans la structure. Pour gèrer la concurence et l'exclussion mutuelle, je fais appel aux sémaphores.

QUESTION 2

Le problème lié aux thread est le risque que deux thread utilisent la même ressource au même moment. En lecture, les problèmes occasionés sont minimes mais en écriture cela devient plus problématique. Pour gèrer cela, mon programme utilise les sémaphores. Lors de l'initialisation, mon sémaphore vaut 1, quand un thread veut accéder une ressource protègée par un sémaphore, il décremente sa valeur de 1. Une fois qu'il a finit avec la ressource protégée, il incrémente la valeur du sémaphore de 1. Ainsi, si un autre thread veut accéder à la ressource protégée, il va attendre que le sémaphore vaille 1 au moins  avant de pouvoir accéder à la ressource. Ainsi, on évite les problèmes de concurence et on garantit l'intégrité des données.

QUESTION 3

Il serait possible de modifier le lancement du thread "modify_ram" avec une forte priorité : Cela permettrait d'être certain qu'avant d'éxecuter une autre tâche, le thread "modify_ram" ait finit d'éxecuter sa tâche. Cela permet notamment de garantir que la RAM allouée à la VM est bien celle demandée par l'utilisateur avant d'éxecuter une autre tâche comme des calculs