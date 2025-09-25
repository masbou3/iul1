#define _POSIX_C_SOURCE 200809L 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include "decoupe.h"
#define NBMOTSMAX 20


int Decoupe(char Chaine[], char *pMots[])
{
  char *p;
  int NbMots=0;

  p=Chaine;	/* On commence par le début */
  /* Tant que la fin de la chaîne n'est pas atteinte et qu'on ne déborde pas */
  while ((*p)!='\0' && NbMots<NBMOTSMAX)
  {
    while ((*p)==' ' && (*p)!='\0') p++; /* Recherche du début du mot */
    if ((*p)=='\0') break;	/* Fin de chaîne atteinte */
    pMots[NbMots++]=p;		/* Rangement de l'adresse du 1er caractère du mot */
    while ((*p)!=' ' && (*p)!='\0') p++; /* Recherche de la fin du mot */
    if ((*p)=='\0') break;	/* Fin de chaîne atteinte */
    *p='\0';			/* Marquage de la fin du mot */
    p++;			/* Passage au caractère suivant */
  }
  pMots[NbMots]=NULL;		/* Dernière adresse */
  return NbMots;
}
/*
void afficher_infos() {
    
    printf("PID=%d, PPID=%d\n", (int)getpid(),(int)getppid());
    printf("PGRP=%d, UID=%d\n", (int)getpgrp(), (int)getuid());
    printf("GID=%d, USR=%s\n", (int)getgid(), getlogin());

}

int main() {
    printf("Infos du processus courant : \n");
    afficher_infos();
    return 0;
}
    

int main() {
    pid_t pid=fork();
    if(pid==-1){
        perror("erreur d'ouverture du fichier fils : ");
        exit(0);
    }
    if(pid==0){
        printf( "\n ----les infos du fils sont : ----\n");

        afficher_infos();
        printf( "\n [FILS] mon code de retour est 1  \n");

        exit(1);
    }
    else {
        int status;
        wait(&status);
        printf( "\n ----les infos du pere sont : ----\n");

        afficher_infos();
        printf( "\n [PERE] mon code de retour est 2  \n");
        exit(2);
    }

int main() {
    pid_t pid=fork();
    if(pid==-1){
        perror("erreur d'ouverture du fichier fils : ");
        exit(0);
    }
    if(pid==0){
        printf( "\n ---- JE LANCE LS -AL ----\n");
        execlp("ls","ls","-al",NULL);
        perror( "ls");


        exit(1);
    }
    else {
        int status;
        wait(&status);
        printf( "\n ----  AUJOURD'HUI NOUS SOMME LE : ----\n");
        execlp("date","date",NULL);
        perror( "date ");
        exit(2);
    }
         //---- question 1 exo 3 ----
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Problrme du au manque d'entree: %s \n", argv[0]);
        exit(1);
    }
    
    for (int i = 1; i < argc; i++) {
        
        pid_t pid=fork();
        if(pid==-1){
            perror("erreur d'ouverture du fichier fils : ");
            exit(0);
        }
        if(pid==0){
            char *pMots[NBMOTSMAX+1];
            Decoupe(argv[i], pMots);

            printf( "[%d] Je lance %s\n ",(int)getpid() , argv[i]);
            
            execvp(pMots[0], pMots);
            perror( "execvp");


            exit(2);
        }
        else {
            printf("[%d] j'ai delegue %s a %d\n",getpid() , argv[i] , pid);
            

            int status;
            wait(&status);
            printf("[%d] %d termine.\n", getpid(), pid);
            
        }    
    }
    return 0;
}
    */  
    //---- question 2 exo 3 ----
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Problrme du au manque d'entree: %s \n", argv[0]);
        exit(1);
    }
    pid_t pid_parent = getpid();

    pid_t fils[argc - 1];
    
    for (int i = 1; i < argc; i++) {
        
        pid_t pid=fork();
        if(pid==-1){
            perror("erreur d'ouverture du fichier fils : ");
            exit(0);
        }
        if(pid==0){
            char *pMots[NBMOTSMAX+1];
            Decoupe(argv[i], pMots);

            printf( "[%d] Je lance %s\n ",(int)getpid() , argv[i]);
            
            execvp(pMots[0], pMots);
            perror( "execvp");


            exit(2);
        }
        else {
            fils[i - 1] = pid;
            printf("[%d] j'ai delegue %s a %d\n",pid_parent , argv[i] , pid);
            

         
            
        }    
        for (int i = 0; i < argc - 1; i++) {
            int status;
            pid_t pid_termine = wait(&status);
            if (pid_termine > 0) {
            
            printf("[%d] %d termine.\n", pid_parent, pid_termine);
            }

    }
    }
    return 0;
}