#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h> 
#include <unistd.h>

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
		int find = 0;
	int END = 0;
	char buf[MAXCAR]; 
	printf("Mettre à jour sa EOA d'un trains :\n");
	//gets(buf);

	//printf("Veuillez saisir la nouvelle EOA:\n");
	//scanf("%d", &END);

	FILE* fp = fopen("MEMO.txt", "r");     //Fichier initial
	FILE* fpn;

	p1=tr1;
	p=tr;

	int m;
	int i;
	int min = 100;
	int max;
	int flag;

	fread(tr, sizeof(struct train), N, fp);
	fread(tr1, sizeof(struct train), N, fp);

	for(i=0; i<N; i++,p1++)
	{
		if(p1->num != 0){
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
	}

	p1=p1-N;

	max = p1->position;
	p1 = p1 + 1;
	for(i = 0; i < N; i++,p1++)
	{
		if(p1->position > max)
			
			{
				max = p1->position;
				flag = i;
			}
	}

	p1 = p1-N;

	p1 = p1 + flag;
	p1->End = 100;

	p1 = p1 - flag;

	rewind(fp);
	fclose(fp);

	fpn = fopen("MEMO.txt", "wb");  // Vider le fichier initial
	fclose(fpn);

	p1--;
	printf("\nN° de train   Localisation     EOA\n") ;  
	fpn = fopen("MEMO.txt", "w+");  
    for(i=0; i<N; i++,p1++){
    	if(p1->num !=0)
			printf("%s\t\t%d\t\t%d\n", p1->ID, p1->position, p1->End);
		fwrite(tr1, sizeof(struct train), N, fpn);
		
	}
		p1=p1-N;
		rewind(fpn);
		fclose(fpn);
}