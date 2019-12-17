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
}tr1[N],*p1;
 
int main()
{
	int find = 0;
	int flag = 0;
	printf("La lecture de EOA pour le train: \n");
	char buf[MAXCAR]; 
	gets(buf);
	FILE* fp = fopen("MEMO.txt", "r");   
	FILE* fpn;

	p1=tr1;
 
	int i = 0;
	rewind(fp);
	fread(tr1, sizeof(struct train), N, fp);
	for(i=0; i<N; i++,p1++){
  
    	if(strcmp(p1->ID ,buf)==0) 
    	{
		printf("La fin d'autorisation de mouvement de ce train: %d\n", p1->End);
		flag = 1;
    	}
    	else
    	{
      		continue;
	}

	}
	if(flag == 0)
		printf("Je ne trouve pas votre train désolé. :( ");
	p1=p1-N;
	rewind(fp);
	fclose(fp);

}