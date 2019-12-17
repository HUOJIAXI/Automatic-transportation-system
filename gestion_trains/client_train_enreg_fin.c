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
#define portlocal   0 //0
#define porteloigne 3306 //Faut correspondre au port de client
#define MAXCAR 80

int main(){
  printf("Appuyez sur la touche Entrée pour commencer\n");
  getchar();
  int sd; /* Socket de dialogue */
  struct sockaddr_in adrecriv ; // Adresse de l'ecrivain.
  struct sockaddr_in adrlect ; // Adresse du lecteur.
  char buff[MAXCAR]; //buffer en ecriture
  int position;
  char bufflect[MAXCAR]; //buffer pour la reception de data
  int inforecu; // nb de caracteres reçus
  int infoemis; // enregistre le nb de caracteres emis
  int identifiant;

  int status; 

  // création de la socket qui correspond à un point de dialogue
  sd=socket(AF_INET, SOCK_DGRAM, 0);

  if(sd < 0)
    {
      printf("Il existe l'erreur de creation d'une socket \n");
      exit(-1);
    }

  // definir l'adreese de l'écrivain
  adrecriv.sin_family=AF_INET;
  adrecriv.sin_port=0; 
  adrecriv.sin_addr.s_addr=inet_addr(adresseIPclient);

  //Associons une adresse a la socket du client afin que le serveur puisse lui repondre
  status=bind(sd,(const struct sockaddr *) &adrecriv, sizeof(adrecriv)); // Liasison entre la socket et (@Ip , #Port)
 if(status != 0)
    {
      printf("Il existe de liaison de socket\n");
      exit(-1);
    }

  //Definition de l'adresse du destinataire
  adrlect.sin_family=AF_INET;
  adrlect.sin_port=htons(porteloigne); //Affectation du port du serveur
  adrlect.sin_addr.s_addr=inet_addr(adresseIPdestination); //Affectation de l'adresse IP du serveur 

  do
  {

  printf(" \n Envoyez votre identifiant :");
  gets(buff);

  infoemis=sendto(sd, buff, strlen(buff)+1, 0, (const struct sockaddr *) &adrlect, sizeof(adrlect) );

  if (infoemis)
  printf("\n Bien emis. \n ");
  else printf("\n Il y a un probleme !!! \n ");

    if(strcmp(buff,"fin") == 0) 
  {
  printf("AU REVOIR !!\n");
  break;
  }

  inforecu=recvfrom(sd, bufflect, MAXCAR, 0,NULL,NULL);

  if (inforecu)
  printf("\n Recevoir la reponse du serveur : %s \n", bufflect);

  else printf("\n Il y a un probleme !!!\n");


  printf(" \n Envoyez position :");
  gets(buff);

  infoemis=sendto(sd, buff, strlen(buff)+1, 0, (const struct sockaddr *) &adrlect, sizeof(adrlect) );

  if (infoemis)
  printf("\n Bien emis. \n ");
  else printf("\n Il y a un probleme !!! \n ");

  inforecu=recvfrom(sd, bufflect, MAXCAR, 0,NULL,NULL);

  if (inforecu)
  printf("\n Recevoir la reponse du serveur : %s \n", bufflect);

  else printf("\n Il y a un probleme !!!\n");
  

  }
  while (strcmp(buff,"fin") && strcmp(bufflect,"fin")); 

  close(sd);

  return 1;
  } // La fin du programme