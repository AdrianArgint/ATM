/* Adrian Argint 
	313 CB 		*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "functii.h"

int main()
{
	//resetare output.out
	FILE *fout;
	fout = fopen("output.out", "w");
	fclose(fout);


	FILE *fin;
	fin = fopen("input.in", "r");
	if(!fin) {
		fprintf(stderr, "File not found!\n");
		return -2;
	}



	int nr_max_carduri;
	fscanf(fin, "%d", &nr_max_carduri);

	//Citim toate operatiile intr-o matrice
	int line_count;
	line_count = 0;
	char input[1000][1000], buf[1000];
	while (fgets(buf, 1000, fin)) {
	    strcpy(input[line_count], buf);
	   	line_count++;
  	}

  	//Impartim pe cuvinte intr-o matrice noua
  	char result[1000][1000];
  	char *token;
	int numar = 0, i;
	for (i = 0; i < line_count; ++i)
	{
		token = strtok(input[i], " ");
		while (token != NULL){
			if(strcmp(token, "\n"))
		 	{
		 		strcpy(result[numar], token);
		 		numar++;
		 	}
		 	token = strtok(NULL, " ");
		}
	}
	//Apeluri de functii
	fclose(fin);
	LC listaCarduri = NULL;
	TLC card;
	int nr_curent_carduri = 0;
	for (i = 0; i < numar; ++i)
	{
		int poz;
		switch(result[i][0]){
			case 'a':
				// verificare existenta
				if(localizareCard(listaCarduri, atoll(result[i+1]))) {
					FILE *fout;
					fout = fopen("output.out", "a");
					fprintf(fout, "The card already exists\n");
					fclose(fout);
					i += 4;
					break;
				}

				//verificare depasire nr_max_carduri
				if(nr_curent_carduri == nr_max_carduri){
					nr_max_carduri *= 2;
					listaCarduri = redimensionareLista(listaCarduri,
									 nr_max_carduri);
				}

				poz = sumcif(atoll(result[i+1])) % nr_max_carduri;
				alocLC(&listaCarduri, poz); //alocam celule LSC daca este cazul
				card=alocCard(result[i+1],result[i+2],result[i+3],result[i+4]);
				add_card(card, poz, listaCarduri);
				i = i + 4;
				nr_curent_carduri++;
				break;

			case 's':
				if(atoll(result[i+1])){
					show_card(localizareCard(listaCarduri, atoll(result[i+1])));
					i++;
				}
				else{
					show(listaCarduri);
				}
				break;	

			case 'd':
				delete_card(&listaCarduri, result[i+1]);
				i++;
				nr_curent_carduri--;
				break;

			case 'i': 
				card = localizareCard(listaCarduri, atoll(result[i+1]));
				insert_card(&card, result[i+2]);
				i += 2;
				break;

			case 'c':
				card = localizareCard(listaCarduri, atoll(result[i+1]));
				if(result[i][2] == 's'){
					cash_withdrawal(&card, result[i+2]);
					i += 2;
					break;
				}
				cancel(card, result[i+1]);
				i++;
				break;

			case 'u':
				card = localizareCard(listaCarduri, atoll(result[i+1]));
				unblock_card(&card);
				i++;
				break;

			case 'p':
				card = localizareCard(listaCarduri, atoll(result[i+1]));
				pin_change(&card, result[i+2]);
				i += 2;
				break;

			case 'b':
				card = localizareCard(listaCarduri, atoll(result[i+1]));
				balance_inquiry(&card);
				i++;
				break;

			case 'r':
				card = localizareCard(listaCarduri, atoll(result[i+1]));
				if(result[i][2] == 'v'){
					TLC card2;
					card2 = localizareCard(listaCarduri, atoll(result[i+2]));
					reverse_transaction(&card, &card2, result[i+3]);
					i += 3;
					break;
				}
				recharge(&card, result[i+2]);
				i += 2;
				break;

			case 't':
				card = localizareCard(listaCarduri, atoll(result[i+1]));
				TLC card2 = localizareCard(listaCarduri, atoll(result[i+2]));
				transfer_funds(&card, &card2, result[i+3]);
				i += 3;
				break;

			default:
				i++;
				break;
		}
	}

	DistrugeL(listaCarduri);
	return 0;
}
