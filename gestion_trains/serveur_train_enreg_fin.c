/* Ce script doit être exécuté au premier, et il fonctionne comme le serveur (RBC), 
le client va l'envoyer les information de train par la connexion de sockets.
Ce script permet enregistrer les informations de trains.
Par exemple, les positions des différents trains et les met à jour au fur et à mesure de leur évolution.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h> 
#include <unistd.h>

//Definition du port du serveur (Le client va connecter au serveur par ce port)
#define portserveur 3306 // Faut correspondre au port de client(On peut choisir le port aléatoirement)
//Definition de la taille maximale des chaines de caracteres
#define MAXCAR 80 // Faut dépasser 6.
#define N 100 //Le nombre de train sur la ligne

// l'information de train
struct train{
    int num;  //le numéro de train (1, 2, 3...)
    char ID[MAXCAR]; // l'identifiant de train
    int position;  // Position de train
    int End;       // EOA de train
}tr[N],*p,tr1[N],*p1;

int main()
{
printf("Appuyez sur la touche Entrée pour commencer\n");
getchar();// Ce méthode est pour evider les caractères de fichier MEMO tronqués apparaissent après la réexécution de ce script.
int sd; /* Socket de dialogue */
int identifiant; // identifiant du train
int posi;// position du train
int eoa;//EOA de train
FILE *fp; // Le pointer de fichier qui enregistre l'information de train
FILE *fpn;

int repeat_check[N]; 
int i;
p=tr;
p1=tr1;

fclose(fp);

struct sockaddr_in adrecriv ; // Adresse du client

struct sockaddr_in adrlect ; // Adresse du serveur

char bufflect[MAXCAR]; // Buffer en reception
char buff[MAXCAR]; // Buffer en emission
char ges[MAXCAR];

int inforecu; //Permet d'enregistrer le nombre d'octets recus
int infoemis; //Permet d'enregistrer le nombre d'octes emis

int taille; //Permet de recuperer la taille en octets de l'adresse d'un client
int status; //code status renvoye par une fonction. Si vaut -1 c'est qu'il y a une erreur du systeme

// Creation de la socket qui correspond a un point de dialogue
sd=socket(AF_INET, SOCK_DGRAM, 0); 
/* Creation de socket, 
AF_INET détermine la combinaison de l’adresse ipv4 (32 bits) et du numéro de port (16 bits).
SOCK_DGRAM détermine l'utilisation de service UDP
Protocol = 0 : Le protocole par défaut correspondant au deuxième type de paramètre est automatiquement sélectionné. Dans ce cas, prototype = IPPROTO_UDP
*/
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

if(status != 0)
    {
      printf("Il existe l'erreur de creation d'une socket \n");
      exit(-1);
    }

printf("\n Attente la reponse du serveur \n\n");

//Reception de data

int j = 1;
int flag = 0;

do
{
flag = 0;
taille=sizeof(adrecriv); 

inforecu=recvfrom(sd, bufflect, MAXCAR, 0,(struct sockaddr *) &adrecriv,(socklen_t *)&taille); 
printf("\n Adresse IP du client : %s \n", inet_ntoa(adrecriv.sin_addr));

if (inforecu)
printf("\n L'identifiant recu par le serveur : '%s' \n", bufflect);

else printf("\n Il y a un probleme !!!\n");
strcpy(ges,bufflect);
if(strcmp(bufflect, "fin") == 0) 
{
	printf("AU REVOIR !!\n");
	break;
}
printf("\n L'identifiant de ce train est %s: \n",bufflect);

printf("\nSaisir la reponse du serveur :");
strcpy(buff,"Bien reçu");
infoemis=sendto(sd,buff, strlen(buff)+1,0, (const struct sockaddr *) &adrecriv, sizeof(adrecriv));

taille=sizeof(adrecriv); 

inforecu=recvfrom(sd, bufflect, MAXCAR, 0,(struct sockaddr *) &adrecriv,(socklen_t *)&taille); 

printf("\n L'adresse IP du client : %s \n", inet_ntoa(adrecriv.sin_addr));

if (inforecu)
printf("\n La position recu par le serveur : '%s' \n", bufflect);

else printf("\n Il y a un probleme !!!\n");
posi=atoi(bufflect); // String -> int

for(int k = 0; k < N ; k++)
{
  if( posi == repeat_check[k])
  {
    flag = 1;
    break;
  }
}

repeat_check[j-1] = posi;

if(flag == 1)
{
  printf("Pour des raisons de sécurité, il ne peut y avoir qu’un seul train par canton.\n");
  strcpy(buff,"Renoyez svp"); // Demander le client de renvoyer la position correcte.
  infoemis=sendto(sd,buff, strlen(buff)+1,0, (const struct sockaddr *) &adrecriv, sizeof(adrecriv));
  continue;
}

else{
printf("\n la position de ce train est %d: \n",posi);

strcpy(buff,"Bien reçu"); // envoyer le reponse automatiquement
infoemis=sendto(sd,buff, strlen(buff)+1,0, (const struct sockaddr *) &adrecriv, sizeof(adrecriv));
printf("\nBien emis \n");
}


if( (fp=fopen("MEMO.txt", "w+")) == NULL ){
    printf("Erreur sur l'ouverture de fichier, veuillez vous sortir!\n");
    getchar();
    exit(1);
}
fread(tr, sizeof(struct train), N, fp);

p=p+(j-1);
p->num = j;
strcpy(p->ID, ges);
p->position=posi;
p->End=100;

/* Sauvegarder les informations des trains en utilisant le pointer d'un fichier */

fwrite(tr, sizeof(struct train), N, fp);
p=p-(j-1);
rewind(fp);


fread(tr1, sizeof(struct train), N, fp);
printf("\nN° de train   Localisation\n") ;       
for(i=0; i<j; i++,p1++){
    printf("%s\t\t%d\n", p1->ID, p1->position);
}
printf("\n");
p1=p1-j;  //Retourner au premier
j++;
fclose(fp);

}while (strcmp(bufflect, "fin") &&strcmp(buff,"fin"));

int m;
int min = 100;



fread(tr, sizeof(struct train), N, fp);
fread(tr1, sizeof(struct train), N, fp);
for(i=0; i<N; i++,p1++)
{
  min = 100;
  //min = p->position - p1->position;
  for(m=0; m<N; m++,p++)
  {
    if(min > (p->position - p1->position) && (p->position - p1->position) > 0)
      {
        min = p->position - p1->position;
        p1->End = p->position - 1;
      }
  }
  p = p - N;
  //p1->End=min - 1;
}

p1=p1-N;
rewind(fp);
fclose(fp);

fpn = fopen("MEMO.txt", "wb");  // Vider le fichier initial
fclose(fpn);
 
fpn = fopen("MEMO.txt", "w+"); 
printf("\nN° de train   Localisation     EOA\n") ;    

for(i=0; i<N; i++,p1++){
  if(p1->num !=0)
printf("%s\t\t%d\t\t%d\n", p1->ID, p1->position, p1->End);
fwrite(tr1, sizeof(struct train), N, fpn);
  } // Remplir le fichier initial

    p1=p1-N;
    rewind(fpn);
    fclose(fpn);



close(sd);

printf("\n Terminer ce programme qui enregistre l'information de train!!! \n");

return 1;
} 