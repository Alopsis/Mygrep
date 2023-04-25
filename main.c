#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
void affichage_motif_couleur(char * motif , char * phrase){
    int i,j;
    char * ptr = strstr(phrase,motif);
    int indice = ptr - phrase;
    char temp[100];
    int acc = 0;
    printf("lindice = %d \n",indice);
    for(i=0;i<indice;i++){
        printf("%c",phrase[i]);
    }
    printf("\033[1;31m");
    for(i=indice;i<indice+strlen(motif);i++){
        printf("%c",phrase[i]);
    }

    
    for(j=i;phrase[j]!='\0';j++){
        temp[acc] = phrase[j];
        acc++;
    }
    printf("\n->%s\n \n",temp);
    /*
    while( strstr(temp,motif) != NULL){
        ptr = strstr(temp,motif);
        // marche po 
        indice = ptr - phrase;
        printf("Le prochain indice est dans %d caractere \n",indice);
        printf("\033[0m");
        for(i=0;i<indice ;i++){
            printf("[%c]",phrase[i]);
        }

        printf("\033[1;31m");
        for(i=indice;i<indice+strlen(motif);i++){
            printf("%c",phrase[i]);
        }
        for(j=i;phrase[j]!='\0';j++){
            temp[acc] = phrase[j];
            acc++;
            
        }

    }
    */

    printf("\033[0m");
    for(i=i;phrase[i]!='\0';i++){
        printf("%c",phrase[i]);
    }  

}



char * convertir_under(char * motif){
    int i;
    for (i = 0; motif[i]!='\0'; i++) {

        if(motif[i] >= 'A' && motif[i] <= 'Z') {
            motif[i] = motif[i] +32;
        } 
    }
    return motif;
}

void    lafonctionquirigolepas(char * motif,char * fichier ,int tab[],int nombreA , int nombreB,int nbfichier){
    FILE *fich;
    char ** phrases = (char ** ) malloc (5001 * sizeof(char *));            /* 5001 phrases max avec 500 caractere / phrase max*/
    char * phrase =(char *) malloc(500 * sizeof(char));
    char *result ;
    int ligne = 1;
    int optl = 0;
    int actu = 0;
    int i;
    int ii;
    int acuB;
    int actuB = 0;
    fich = fopen(fichier, "r");

    if (fich == NULL)
    {
        printf("Le fichier n'a pas pu s'ouvrirr ( %s ) \n", fichier);
        return;
    }
    if(tab[8] == 0 && tab[7] == 0 && nbfichier > 2 && tab[4] == 0){
        printf("\033[1;35m");
        printf("%s\n",fichier);
        printf("\033[0m");

    }

    if(tab[6] == 1) {
        motif = convertir_under(motif);
    }
    
    ii=0;
    if(tab[1] == 1){
        for (ii = 0; ii < 5001; ii++) {
            phrases[ii] = (char *)malloc(500 * sizeof(char));
        }
        ii = 0;
        while (fgets(phrases[ii], 5000, fich))
        {
            ii++;
        }
        fclose(fich);
        
        fich = fopen(fichier,"r");
        if (fich == NULL)
        {
            printf("Le fichier n'a pas pu s'ouvrir ( %s ) \n", fichier);
            for(i=0;i<5001;i++){
                free(phrases[i]);
            }
            free(phrases);
            return;
        }    
    }
    acuB = 0;
    while (fgets(phrase, 500, fich))
    {
        if(tab[1] == 1 && acuB+4  == ii){
            break;
        }
        result = strstr(phrase, motif);
        if ( tab[1] == 1){
            result = strstr(phrases[acuB+nombreB],motif);
        }
        if(tab[6] == 1){
            strcpy(phrase,convertir_under(phrase));
        }
        if (result != NULL && tab[10] == 0){
            optl++;
        }else if(result == NULL && tab[10] == 1){
            optl++;
        }
        if( result == NULL && tab[10] == 1){
            actu=1;
            actuB= nombreB;
        }
        if (result != NULL && tab[10] == 0 && tab[8] ==0 && tab[7] == 0 && tab[2] == 0 )
        {
            if(tab[1] == 1 && result != NULL){
                actuB = nombreB;
                printf("%s",phrases[acuB]);
            }
            actu = 1;
            
            if(tab[9] == 1 ){
                printf("\033[1;32m");
                printf("%d:",ligne);
                printf("\033[0m");
            }
            if(tab[1] == 0 ){
                affichage_motif_couleur(motif,phrase);
                //printf("->%s",phrase);
            }
        }else if ( result != NULL && acuB+4 <= ii){
            printf("%s",phrase);
        }
        else if (( tab[1] == 1 && actuB > 0 && actuB <= nombreB )){
            if(actuB == 1 ){
                affichage_motif_couleur(motif,phrases[acuB]);
            }else {
            printf("%s",phrases[acuB]);
            }
            actuB--;
        }
        else if((result == NULL && tab[10] == 1 && tab[8] == 0 && tab[7] == 0 && tab[2] == 0 )|| ( tab[0] == 1 && actu > 0 && actu <= nombreA)  ){
            actu++;
            if(tab[9] == 1){
                printf("%d:",ligne);
            }
            if(result == NULL ){
                printf("%s",phrase);
            }
            else {
                affichage_motif_couleur(motif,phrase);
            }
            
        }

        ligne++;
        acuB++;
    }
    if ( (optl != 0 && tab[8] == 1 )|| ( optl == 0 && tab[7] == 1 )){
        printf("%s",fichier);
    }
    if(tab[2] ==1){
        printf("%d \n",optl);
    }



    /*******************/
    /* fin de fonction */
    /*******************/
    for (ii = 0; ii < 5001; ii++) {
            free(phrases[ii]);
            phrases[ii] = NULL;
    }
    free(phrases);
    phrases = NULL;
    free(phrase);
    phrase = NULL;
}

int recup_nombre_fichier( char * argv[]){
    int i = 1;
    while(argv[optind+i] != NULL){
        i++;
    }  
    return i;
}



void affichage_help(){
            printf("Bienvenue sur l'aide ! \n\nLes options :\n -A num ( affiche les num lignes avant le motif )\n -B num ( affiche les num lignes apres le motif ) \n -c ( n'affiche pas les lignes avec le motif mais la somme des lignes avec )\n -e motif ( permet d'avoir un motif special )\n -h ( permet de ne pas afficher les noms de fichier )\n -H ( petit guide bien sympatique )\n -i ( permet d'ignorer la case ! )\n -L ( permet d'afficher les fichiers n'ayant pas le motif ) \n -l  ( permet d'afficher les fichiers contenant le motif )\n -n ( permet d'écrire la ligne ouù le motif est apparu ) \n -v ( selectionne les lignes n'ayant pas le motif ) \n\n\n");

}




void usage()
{
    printf("usage ||options|| <motif> <fichier> ");
    exit(0);
}



int main(int argc, char *argv[])
{
    /****************************/
    /* Declaration de variable !*/
    /****************************/
    int i = 1;                                                              /* var de boucle*/
    char *optstring = "A:B:ce:h:HiLlnv";                                    /* Gere les args des options*/
    int val;                                                                /* Va servir pour la switch */
    int *tab = (int *) calloc(11,sizeof(int));                              /* Contient les options cochées ou non */
    int nbA = 0;                                                            /* sert uniquement si A est en option */
    int nbB = 0;                                                            /* Sert uniquement si B est en option */
    char  * motif = (char *) malloc(50 * sizeof(char));                     /* va contenir le motif de notre suite */
    int nbfichier = 1;                                                      /* contient le nombre de fichier */
    /************************************/
    /* Fin de la déclaration de variable*/
    /************************************/



    if (argc < 2)
    {
        usage();
    }

    /**********************************************/
    /* Gestion des options choisies via le switch */
    /**********************************************/
    val = getopt(argc, argv, optstring);
    while (val != EOF)
    {
        switch (val)
        {
        case 'A':
            tab[0] = 1;
            nbA = atoi(optarg);
            break;
        case 'B':
            tab[1] = 1;
            nbB = atoi(optarg);
            break;
        case 'c':
            tab[2] = 1;
            break;
        case 'e':
            tab[3] = 1;
            strcpy(motif,optarg);
            break;
        case 'h':
            tab[4] = 1 ;
            break;
        case 'H':
            affichage_help();
            tab[5] = 1;
            exit(0);
        case 'i':
            tab[6] = 1;
            break;
        case 'L':
            tab[7] = 1;
            break;
        case 'l':
            tab[8] = 1;
            break;
        case 'n':
            tab[9] = 1;
            break;
        case 'v':
            tab[10] = 1;
            break;
        case '?':
            printf("Option inconnue\n");
            break;
        default:
            exit(0);
        }
        
        val = getopt(argc, argv, optstring);
    }
    /******************************************/


    /************************************************************/
    /* On recupere le nom de fichier dans la variable nbfichier */
    /************************************************************/
    nbfichier = recup_nombre_fichier(argv);
    /******************************************************/


    /*****************************************************/
    /* Gestion des cas qui diffèrent suivant les options */
    /*****************************************************/
    if(tab[3] == 1){
        while(argv[optind-1+i] != NULL){
            lafonctionquirigolepas(motif,argv[optind-1+i],tab,nbA,nbB,nbfichier);
            i++;
        }
    }else if ( tab[4] == 1){
        i=0;
        while(argv[optind+i] != NULL){
            lafonctionquirigolepas(argv[optind-1],argv[optind+i],tab,nbA,nbB,nbfichier);
            i++;
        }
    }
    else {
        while(argv[optind+i] != NULL){
            
            lafonctionquirigolepas(argv[optind],argv[optind+i],tab,nbA,nbB,nbfichier);
            i++;
        }
    }
    /*********************************************************/

    /*******************/
    /* Fin de fonction */
    /*******************/
    free(tab);
    free(motif);
    exit(0);
}