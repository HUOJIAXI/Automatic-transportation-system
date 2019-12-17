#include<stdlib.h>
#include<stdio.h>

int main()
{
	int choix = 0;
	printf("Initialiser l'information de train: \n");
	system("open -a Terminal.app ~/Desktop/STA/gestion_trains_par_RBC_HUO_ZHANG/serveur_train_enreg_fin");
	system("open -a Terminal.app ~/Desktop/STA/gestion_trains_par_RBC_HUO_ZHANG/client_train_enreg_fin");
	while(1)
	{
		printf("1. La suppression d'un train d'un RBC: \n");
		printf("2. La mise à jour de la position du train: \n");
		printf("3. La lecture de la fin d'autorisation de mouvement d'un train: \n");
		printf("4. La mise à jour de la fin d'autorisation de mouvement d'un train: \n");
		printf("5. L'enqêute d'autorisation d'un nouveau train: \n");

		printf("Veuillez vous saisir votre numero du choix: \n");
		scanf("%d", &choix);
		switch(choix)
		{
			case 1:
				system("open -a Terminal.app ~/Desktop/STA/gestion_trains_par_RBC_HUO_ZHANG/sup_train_fin");
				
				break;
			case 2:
				system("open -a Terminal.app ~/Desktop/STA/gestion_trains_par_RBC_HUO_ZHANG/mis_a_jour_local_fin");
				break;
			case 3:
				system("open -a Terminal.app ~/Desktop/STA/gestion_trains_par_RBC_HUO_ZHANG/Lecture_train_EOA");
				break;
			case 4:
				system("open -a Terminal.app ~/Desktop/STA/gestion_trains_par_RBC_HUO_ZHANG/mis_a_jour_eoa_fin");
				break;
			case 5:
				system("open -a Terminal.app ~/Desktop/STA/gestion_trains_par_RBC_HUO_ZHANG/serveur_train_rev");
				system("open -a Terminal.app ~/Desktop/STA/gestion_trains_par_RBC_HUO_ZHANG/client_train_rev");
				break;
		}

		printf("Veuillez vous sortir? 0: Sortez, 1: Restez\n");
		int fin;
		scanf("%d", &fin);
		if(fin == 0) break;
	}

}