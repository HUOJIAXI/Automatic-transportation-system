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

void misajour( )
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

	fpn = fopen("MEMO.txt", "w+");  
	printf("\nN° de train   Localisation     EOA\n") ;  
    for(i=0; i<N; i++,p1++){
    	if(p1->num !=0)
			printf("%s\t\t%d\t\t%d\n", p1->ID, p1->position, p1->End);
		fwrite(tr1, sizeof(struct train), N, fpn);
		
	}
		p1=p1-N;
		rewind(fpn);
		fclose(fpn);
}
 
int main()
{
	int find = 0;
	int local = 0;
	int flag = 0;
	printf("Veuillez saisir l'identifiant de train que vous voulez mettre à jour sa localisation :\n");
	char buf[MAXCAR]; 
	//printf("input train to change :\n");
	gets(buf);

	printf("Veuillez saisir la nouvelle localisation:\n");
	scanf("%d", &local);

	FILE* fp = fopen("MEMO.txt", "r");     //filepath里是原内容 
	FILE* fpn;
	//FILE* fpt = fopen("temp.txt", "r");
	//char train[N][MAXCAR] = {"TGV134","TGV083","TER203"};
	//p=tr;
	p1=tr1;
	p=tr;
 
	//FILE* fpt = fopen("temp.txt", "w");    //将filepath文件第n行内容删除后存入temp.txt中 
	int i = 0;
	int numero = 0;

	rewind(fp);
	fread(tr1, sizeof(struct train), N, fp);
	//printf("\nN° de train   Localisation\n") ;
	for(i=0; i<N; i++,p1++){
  
    	if(strcmp(p1->ID ,buf)==0) 
    	{
    	flag = 1;
		p->num = p1->num;
		strcpy(p->ID,p1->ID);
		if(p1->position == local)
		{
			numero = i;
			flag = 2;
			break;
		}
		p->position=local;
		p->End=p1->End;
		p=p+1;
		//printf("%s\t\t%d\n", p1->ID, local);
    	}
    	else
    	{
		p->num = p1->num;

		if(p1->position == local)
		{
			numero = i;
			flag = 2;
			break;
		}

		strcpy(p->ID,p1->ID);
		p->position=p1->position;
		p->End=p1->End;
		p=p+1;
	}

		//fwrite(tr, sizeof(struct train), N, fpt);
	}
	printf("\n");
	if(flag == 0)
		{
			printf("Je ne trouve pas votre train désolé. :( \n");
			exit(-1);
		}


		if(flag == 2)
	{
		printf("\nPour des raisons de sécurité, il ne peut y avoir qu’un seul train par canton. \n");
		printf("\nCollision avec le train : %s\n\n", p1->ID);
		p1 = p1 - (numero-1);
		exit(-1);
	}

	p1=p1-N;

	rewind(fp);
	fclose(fp);

	fpn = fopen("MEMO.txt", "wb");   
	fclose(fpn);
 
    //fread(tr, sizeof(struct train), N, fpn);
	fpn = fopen("MEMO.txt", "w+");  
    for(i=0; i<N; i++,p++){
		//fwrite(tr, sizeof(struct train), N-1, fpn);
		fwrite(tr, sizeof(struct train), N, fpn);
		
	}
		p=p-N;
		rewind(fpn);
		fclose(fpn);
	//rewind(fpn)

misajour();

}
