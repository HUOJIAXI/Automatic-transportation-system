/* Ce script doit être exécuté avec le programme serveur_train_enreg*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h> 
#include <unistd.h>

#define adresseIPdestination "127.0.0.1"
#define adresseIPclient "127.0.0.1"
#define portlocal   0
#define porteloigne 3306
#define MAXCAR 80

int main()
{
printf("Appuyez sur la touche Entrée pour commencer\n");
getchar();
int sd; 
struct sockaddr_in adrecriv ; 
struct sockaddr_in adrlect ; 
char buff[MAXCAR]; 
int position;
int Eoa;
char bufflect[MAXCAR]; 
int inforecu; 
int infoemis; 
int posi;

int status; 

sd=socket(AF_INET, SOCK_DGRAM, 0); 
if(sd < 0)
    {
      printf("Il existe l'erreur de creation d'une socket \n");
      exit(-1);
    }



adrecriv.sin_family=AF_INET;
adrecriv.sin_port=0;
adrecriv.sin_addr.s_addr=inet_addr(adresseIPclient); 

status=bind(sd,(const struct sockaddr *) &adrecriv, sizeof(adrecriv));

if(status != 0)
    {
      printf("Il existe de liaison de socket\n");
      exit(-1);
    }

adrlect.sin_family=AF_INET;
adrlect.sin_port=htons(porteloigne); 
adrlect.sin_addr.s_addr=inet_addr(adresseIPdestination); 

do
{

printf(" \n Envoyez votre position :");
gets(buff);
posi=atoi(buff);

infoemis=sendto(sd, buff, strlen(buff)+1, 0, (const struct sockaddr *) &adrlect, sizeof(adrlect) );

if (infoemis)
printf("\n Bien emis! \n ");
else printf("\n Il y a un probleme !!! \n ");

if(posi == 0) 
{
	printf("AU REVOIR !!\n");
	break;
}



inforecu=recvfrom(sd, bufflect, MAXCAR, 0,NULL,NULL);

if (inforecu)
printf("\n Recevoir la reponse du serveur : %s \n", bufflect);

else printf("\n Il y a un probleme !!!\n");

/*printf(" \n Envoyez votre EOA :");
gets(buff);

infoemis=sendto(sd, buff, strlen(buff)+1, 0, (const struct sockaddr *) &adrlect, sizeof(adrlect) );

if (infoemis)
printf("\n Bien emis! \n ");
else printf("\n Il y a un probleme !!! \n ");
*/

inforecu=recvfrom(sd, bufflect, MAXCAR, 0,NULL,NULL);

if (inforecu)
printf("\n Recevoir la reponse du serveur : %s \n", bufflect);

else printf("\n Il y a un probleme !!!\n");



}
while (strcmp(buff,"fin") && strcmp(bufflect,"fin"));

//Fermeture de ma socket
close(sd);

return 1;
} // La fin du programme
