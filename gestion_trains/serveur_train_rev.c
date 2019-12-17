#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //Définir la structure de données sockaddr_in
#include <netdb.h>      //Fournir des fonctions pour définir et obtenir des noms de domaine
#include <arpa/inet.h> //Fournir une fonction de traduction d'adresse IP
#include <string.h> 
#include <unistd.h>

#define portserveur   3306
#define MAXCAR 80
#define N 100

struct train{
    int num;  //l'identifiant de train
    char ID[MAXCAR];
    int position;  //Position de train
    int End;
}tr[N],*p,tr1[N],*p1;

int main()
{
printf("Appuyez sur la touche Entrée pour commencer\n");
getchar();
int sd; /* Socket de dialogue */
int identifiant; // identifiant du train
int posi;// position du train
int eoa;
FILE *fp;
int i;
p=tr;
p1=tr1;
int flag=0;
int n=0;
int m = 0;

struct sockaddr_in adrecriv ; // Adresse du client

struct sockaddr_in adrlect ; // Adresse du serveur

char bufflect[MAXCAR]; // Buffer en reception
char buff[MAXCAR]; // Buffer en emission

int inforecu; //Permet de memoriser le nombre d'octets recus
int infoemis; //Permet de memoriser le nb d'octes emis

int taille;
int status; 

sd=socket(AF_INET, SOCK_DGRAM, 0); /* Indique que je cree une socket utilisant UDP sur internet */
if(sd < 0)
    {
      printf("Il existe l'erreur de creation d'une socket \n");
      exit(-1);
    }


//Definition de l'adresse du serveur
adrlect.sin_family=AF_INET;
adrlect.sin_port=htons(portserveur); //Affectation du port du serveur. On pourra le voir au niveau system par la commande "netstat -an"
adrlect.sin_addr.s_addr=INADDR_ANY; // Indique que le serveur recoit les data envoye a n'imporete laquelle de ses adresses IP


// Associer cette adresse a la socket du lecteur pour qu'il puisse recevoir des data

status=bind(sd, (const struct sockaddr *) &adrlect, sizeof(adrlect));

if(status < 0)
    {
      printf("Il existe l'erreur de creation d'une socket \n");
      exit(-1);
    }


printf("\n Attente la reponse du serveur !!! \n\n");

//Reception de data

do
{
flag = 0; // Initialiser l'autorisation de mouvement

taille=sizeof(adrecriv); 

inforecu=recvfrom(sd, bufflect, MAXCAR, 0,(struct sockaddr *) &adrecriv,(socklen_t *)&taille); 

printf("\n L'adresse IP du client : %s \n", inet_ntoa(adrecriv.sin_addr));

if (inforecu)
printf("\n La position recu par le serveur : '%s' \n", bufflect);

else printf("\n Il y a un probleme !!!\n");
posi=atoi(bufflect);

if(posi == 0) 
{
    printf("AU REVOIR !!\n");
    break;
}

printf("\n La position de ce train est %d: \n",posi);

strcpy(buff,"Bien reçu");
infoemis=sendto(sd,buff, strlen(buff)+1,0, (const struct sockaddr *) &adrecriv, sizeof(adrecriv));

/*
taille=sizeof(adrecriv); 
inforecu=recvfrom(sd, bufflect, MAXCAR, 0,(struct sockaddr *) &adrecriv,(socklen_t *)&taille); 

printf("\n Adresse IP du client : %s \n", inet_ntoa(adrecriv.sin_addr));

if (inforecu)
printf("\n La EOA recu par le serveur : '%s' \n", bufflect);

else printf("\n Il y a un probleme !!!\n");
eoa=atoi(bufflect);
printf("\n La EOA de ce train est %d: \n",eoa);

printf("\nMessage emis \n");
*/


if( (fp=fopen("MEMO.txt", "r")) == NULL ){
    printf("Erreur sur l'ouverture de fichier, veuillez vous sortir! \n");
    getchar();
    exit(1);
}
n=posi;

fread(tr1, sizeof(struct train), N, fp);
printf("\nN° de train   Localisation     EOA\n") ;  

for(i=0; i<N; i++,p1++){
	if(p1->num == 0) continue;
	else
	{
    printf("%s\t\t%d\t\t%d\n", p1->ID, p1->position, p1->End);
    if(0==(p1->position-n)) 
      flag = 2;

    else if(0<(p1->position-n)&&(p1->position-n)<2) 
      flag = 1;
    else continue;
}
/* comparaison parmi la fin d’autorisation de mouvement, la localisation d’un train qui fait l’enquête et les localisations des train qui existent dans la ligne */
}
printf("\n");
p1=p1-N;
rewind(fp);
fclose(fp);

if(flag==1)
 strcpy(buff,"Passage interdit");
else if(flag==2)
 strcpy(buff,"Un seul train par canton.");
 else
 strcpy(buff,"Passage permit");

 infoemis=sendto(sd,buff, strlen(buff)+1,0, (const struct sockaddr *) &adrecriv, sizeof(adrecriv));

}

while (strcmp(bufflect, "fin") &&strcmp(buff,"fin"));

//Fermeture de socket

close(sd);

printf("\n Terminer ce programme qui enregistrel'information de train!!!\n");

return 1;
} // La fin du programme