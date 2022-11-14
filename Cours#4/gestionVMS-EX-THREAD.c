

// MODIFICATIONS IMPLEMENTATION THREAD et EXCLUSION MUTUELLE: 

// ETAPE 1

// Ajout de la declaration d'une struct paramX dans gestionListeChaineeVMS.h pour 
// le passage de parametre au thread executeFile() et modifier
// le prototype de la fonction threadee executeFile()

struct paramX{
	int noVM;
	char nomfich[100];
	};
	
void executeFile(struct paramX* param);

// ETAPE 2

// Implementation des threads dans la fonction readTrans() du fichier gestionVMS.c

// Declarer un compteur de thread et une liste de tid au debut de la fonction readTrans()

	pthread_t tid[1000];
	int nbThread = 0;



		//Branchement selon le type de transaction
			case 'X':
			case 'x':{
				//Extraction des paramètres
				int noVM = atoi(strtok_r(NULL, " ", &sp));
				char *nomfich = strtok_r(NULL, "\n", &sp);
				//executeFile(noVM, nomfich); // Executer le code binaire du fichier nomFich sur la VM noVM
				
				// Creer un thread qui fait executeFile() de facon concurrente
				
				struct paramX *ptr = (struct paramX*) malloc(sizeof(struct paramX));
				ptr->noVM = noVM;
				strcpy(ptr->nomfich,(const char *)nomfich);
				
				//Appel de la fonction associée
				pthread_create(&tid[nbThread++], NULL, executeFile, ptr);
				
				// faire un pthread_join() sur la liste des tid apres la boucle de gestion des transactions
				
				
		}
		
// Attendre la terminaison des threads apres avoir termine de traiter toutes les transactions

	for(i=0; i<nbThread;i++)
	  pthread_join(&tid[i], NULL);
  
  // ETAPE 3
  
  // Modifer l'entete de la fonction threadee executeFile() et la reception des parametres dans le fichier gestionListeChaineeVMS.c
  
  void executeFile(struct paramX* param){
  
	char sourcefname[100]; 
	int noVM;
	
	noVM = param ->noVM;
	strcpy(sourcefname,(const char*)param->nomfich);
	free(param);
	
	// ETAPE 4
	// Ajouter 2 semaphores semH et semQ  pour l'acces en Exclusion mutuelle au pointeur de debut et fin de la liste chainee de VM
		// Dans l'entete de la fonction main()
		// ex de Declaration
		// sem_t semH, semQ;
	
		// Initialisation dans le main()
		// ex d'initialisation
		// sem_init(&semH, 0, 1);

	
	// Ajouter un semaphore semVM dans la struct noeudVM  pour l'acces en Exclusion mutuelle de chaque noeud de la liste des VM
	
	
	
	
	// ETAPE 5
	// Declarer semH  et semQ global et initialiser dans le main() (voir exemple plus haut)
	// Initialiser semVM lors de la creation d'un noeud (d'une VM) de la liste de VM et detruire (sem_destroy()) lors sa suppression 
	
	
	// ETAPE 6 
	// Implementation de l'exclusion mutuelle  dans la fonction threadee executeFile() et findItem()

	/* Memory Storage */
/* 65536 locations */
	uint16_t *  memory;
	uint16_t origin;
	uint16_t PC_START;
	
/* Register Storage */
	uint16_t reg[R_COUNT];
	
    struct noeudVM * ptr =  findItem(noVM); // si ptr non NULL, noeud verrouille
	
    if(ptr == NULL)
    {
        printf("Virtual Machine unavailable\n");
        //return(0);
		pthread_exit(0);
    }	
	memory = ptr->VM.ptrDebutVM;
    if (!read_image_file(memory, sourcefname, &origin))
    {
        printf("Failed to load image: %s\n", sourcefname);
        //return(0);
		sem_post(&ptr->semVM); // liberer le noeud verrouille
		pthread_exit(0);
    }
	
    while(ptr->VM.busy != 0){ // wait for the VM, toujours utile ????? 
    }
	// Acquiring access to the VM
    ptr->VM.busy = 1;
    
    /* Setup */
    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    /* set the PC to starting position */
    /* at  ptr->VM.ptrDebutVM + 0x3000 is the default  */
    //enum { PC_START = origin };
    PC_START = origin;
    reg[R_PC] = PC_START;

    int running = 1;
    while (running)
    {
        /* FETCH */
        uint16_t instr = mem_read(memory, reg[R_PC]++);
// printf("\n instr = %x", instr);
        uint16_t op = instr >> 12;
	
// printf("\n exe op = %x", op);

        switch (op)
        {
            case OP_ADD:
                /* ADD */
                {
                    /* destination register (DR) */
                    uint16_t r0 = (instr >> 9) & 0x7;
                    /* first operand (SR1) */
                    uint16_t r1 = (instr >> 6) & 0x7;
                    /* whether we are in immediate mode */
                    uint16_t imm_flag = (instr >> 5) & 0x1;
                
                    if (imm_flag)
                    {
                        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                        reg[r0] = reg[r1] + imm5;
                    }
                    else
                    {
                        uint16_t r2 = instr & 0x7;
                        reg[r0] = reg[r1] + reg[r2];
// VOIR A GERER L'ACCES EN EXCLUSION MUTUELLE A LA CONSOLE
 printf("\n add reg[r0] (sum) = %d", reg[r0]);
 //printf("\t add reg[r1] (sum avant) = %d", reg[r1]);
 //printf("\t add reg[r2] (valeur ajoutee) = %d", reg[r2]);
                    }
                
                    update_flags(reg, r0);
                }

                break;
            case OP_AND:
                /* AND */
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t r1 = (instr >> 6) & 0x7;
                    uint16_t imm_flag = (instr >> 5) & 0x1;
                
                    if (imm_flag)
                    {
                        uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                        reg[r0] = reg[r1] & imm5;
                    }
                    else
                    {
                        uint16_t r2 = instr & 0x7;
                        reg[r0] = reg[r1] & reg[r2];
                    }
                    update_flags(reg, r0);
                }

                break;
            case OP_NOT:
                /* NOT */
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t r1 = (instr >> 6) & 0x7;
                
                    reg[r0] = ~reg[r1];
                    update_flags(reg, r0);
                }

                break;
            case OP_BR:
                /* BR */
                {
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                    uint16_t cond_flag = (instr >> 9) & 0x7;
                    if (cond_flag & reg[R_COND])
                    {
                        reg[R_PC] += pc_offset;
                    }
                }

                break;
            case OP_JMP:
                /* JMP */
                {
                    /* Also handles RET */
                    uint16_t r1 = (instr >> 6) & 0x7;
                    reg[R_PC] = reg[r1];
                }

                break;
            case OP_JSR:
                /* JSR */
                {
                    uint16_t long_flag = (instr >> 11) & 1;
                    reg[R_R7] = reg[R_PC];
                    if (long_flag)
                    {
                        uint16_t long_pc_offset = sign_extend(instr & 0x7FF, 11);
                        reg[R_PC] += long_pc_offset;  /* JSR */
                    }
                    else
                    {
                        uint16_t r1 = (instr >> 6) & 0x7;
                        reg[R_PC] = reg[r1]; /* JSRR */
                    }
                    break;
                }

                break;
            case OP_LD:
                /* LD */
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                    reg[r0] = mem_read(memory, reg[R_PC] + pc_offset);
                    update_flags(reg, r0);
                }

                break;
            case OP_LDI:
                /* LDI */
                {
                    /* destination register (DR) */
                    uint16_t r0 = (instr >> 9) & 0x7;
                    /* PCoffset 9*/
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                    /* add pc_offset to the current PC, look at that memory location to get the final address */
                    reg[r0] = mem_read(memory, mem_read(memory, reg[R_PC] + pc_offset));
                    update_flags(reg, r0);
                }

                break;
            case OP_LDR:
                /* LDR */
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t r1 = (instr >> 6) & 0x7;
                    uint16_t offset = sign_extend(instr & 0x3F, 6);
                    reg[r0] = mem_read(memory, reg[r1] + offset);
                    update_flags(reg, r0);
                }

                break;
            case OP_LEA:
                /* LEA */
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                    reg[r0] = reg[R_PC] + pc_offset;
                    update_flags(reg, r0);
                }

                break;
            case OP_ST:
                /* ST */
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                    mem_write(memory, reg[R_PC] + pc_offset, reg[r0]);
                }

                break;
            case OP_STI:
                /* STI */
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);
                    mem_write(memory, mem_read(memory, reg[R_PC] + pc_offset), reg[r0]);
                }

                break;
            case OP_STR:
                /* STR */
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t r1 = (instr >> 6) & 0x7;
                    uint16_t offset = sign_extend(instr & 0x3F, 6);
                    mem_write(memory, reg[r1] + offset, reg[r0]);
                }

                break;
            case OP_TRAP:
                /* TRAP */
                switch (instr & 0xFF)
                {
                    case TRAP_GETC:
                        /* TRAP GETC */
                        /* read a single ASCII char */
                        reg[R_R0] = (uint16_t)getchar();

                        break;
                    case TRAP_OUT:
                        /* TRAP OUT */
                        putc((char)reg[R_R0], stdout);
                        fflush(stdout);

                        break;
                    case TRAP_PUTS:
                        /* TRAP PUTS */
                        {
                            /* one char per word */
                            uint16_t* c = memory + reg[R_R0];
                            while (*c)
                            {
                                putc((char)*c, stdout);
                                ++c;
                            }
                            fflush(stdout);
                        }

                        break;
                    case TRAP_IN:
                        /* TRAP IN */
                        {
                            printf("Enter a character: ");
                            char c = getchar();
                            putc(c, stdout);
                            reg[R_R0] = (uint16_t)c;
                        }

                        break;
                    case TRAP_PUTSP:
                        /* TRAP PUTSP */
                        {
                            /* one char per byte (two bytes per word)
                               here we need to swap back to
                               big endian format */
                            uint16_t* c = memory + reg[R_R0];
                            while (*c)
                            {
                                char char1 = (*c) & 0xFF;
                                putc(char1, stdout);
                                char char2 = (*c) >> 8;
                                if (char2) putc(char2, stdout);
                                ++c;
                            }
                            fflush(stdout);
                        }

                        break;
                    case TRAP_HALT:
                        /* TRAP HALT */
                        puts("\n HALT");
                        fflush(stdout);
                        running = 0;

                        break;
                }

                break;
            case OP_RES:
            case OP_RTI:
            default:
                /* BAD OPCODE */
                abort();

                break;
        }
    }
    ptr->VM.busy = 0;
    /* Shutdown */
    restore_input_buffering();
	sem_post(&ptr->semVM); // deverrouiller le noeud de la VM qui a terminee l'execution
    //return(1);
	pthread_exit(1);
}

struct noeudVM * findItem(const int no){
	//La liste est vide
	sem_wait(&semH);
	sem_wait(&semQ)
	if ((head==NULL)&&(queue==NULL))
	{
		sem_post(&semQ);
		sem_post(&semH)
		return NULL;
	}

	//Pointeur de navigation
	sem_wait(&head->semVM); // verrouille noeud de tete
	struct noeudVM * ptr = head;
	sem_post(&semQ);
	sem_post(&semH)
	

	if(ptr->VM.noVM==no) // premier noeudVM
		return ptr; // retourner le noeud de tete verrouille
		
	if(ptr->suivant!=NULL){
		sem_wait(&ptr->suivant->semVM); // verrouille noeud suivant de ptr
	}
	else{ // ptr->suivant==NULL no invalide
		sem_post(&ptr->semVM); // deverrouille noeud de tete 
	}
	//Tant qu'un item suivant existe
	while (ptr->suivant!=NULL){
		//Déplacement du pointeur de navigation
		struct noeud* optr = ptr;
	
		ptr=ptr->suivant;
		sem_post(&optr->semVM); 

		//Est-ce l'item recherché?
		if (ptr->VM.noVM==no){
			return ptr; // retourner le noeud verrouille
		}
		if(ptr->suivant!=NULL){
			sem_wait(&ptr->suivant->semVM);
		}
		else{ // ptr->suivant==NULL no invalide
			sem_post(&ptr->semVM); // deverrouille dernier noeud verrouille
		}		
	}
	//On retourne un pointeur NULL
	return NULL;
}
	