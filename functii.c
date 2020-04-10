/* Adrian Argint 
	313 CB 		*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "functii.h"


int sumcif(long long x){
	int sum = 0, digit;
	while (x != 0)
	{
		digit = x % 10;
		sum = sum + digit;
		x = x / 10;
	}
	return sum;
}

LC initializareLC(LC listaCarduri){
	listaCarduri = (LC) malloc(sizeof(LSC));
	if(!listaCarduri) return NULL;
	listaCarduri->no = 0;
	listaCarduri->urm = NULL;
	listaCarduri->carduri = NULL;
	return listaCarduri;
}


void add_card(TLC card, int poz, LC L){
	int i = 0;
	LC p = L;
	if(!L){
		L = initializareLC(L);
	}
	while(i < poz){
		p = p->urm;
		i++;
	}

	if(p->carduri){
		TLC ant = p->carduri;
		p->carduri = card;
		card->urmCard = ant;
	}
	else{
		p->carduri = card;
	}
}


void alocLC(LC *L, int no){
	int i = 0;
	LC aux, p, ant = NULL;
	p = *L;
	while(i <= no){
		if(!p){ //alocam daca nu e alocat deja
			aux = (LC) malloc(sizeof(LSC));
			if(!aux) return;
			aux->no = i;
			aux->urm = NULL;
			aux->carduri = NULL;

			if(!(*L)) {
				*L = aux;
				p = *L;
			}
			else{
				ant->urm = aux;
				p = aux;
			}
		}
		ant = p;
		p = p->urm;
		i++;
	}
}


TLC alocCard(char *number, char *pin, char *expiry_date, char *cvv){
	TLC aux;
	aux = (TLC) malloc(sizeof(TCard));
	if(!aux) return NULL;
	aux->number = (char*) malloc(17);
	aux->pin = (char*) malloc(5);
	aux->expiry_date = (char*) malloc(6);
	aux->cvv = (char*) malloc(4);
	memcpy(aux->number, number, 16);
	aux->number[16] = '\0';
	aux->pin[4] = '\0';
	aux->expiry_date[5] = '\0';
	aux->cvv[3] = '\0';
	memcpy(aux->pin, pin, 4);
	memcpy(aux->expiry_date, expiry_date, 5);
	memcpy(aux->cvv, cvv, 3);
	aux->balance = 0;
	aux->status = 0;
	aux->incercari = 0;
	aux->urmHistory = NULL;
	aux->urmCard = NULL;
	return aux;
}

void show_card(TLC card){
	if(!card) return;
	FILE *fout;
	fout = fopen("output.out", "a");
	fprintf(fout, "(card number: %s, PIN: %s, expiry date: %s,",
		card->number, card->pin, card->expiry_date);
	fprintf(fout, " CVV: %s, balance: %d, status: ",card->cvv, card->balance);
	if(card->status == 0) fprintf(fout, "NEW");
	else if (card->status == 1) fprintf(fout, "ACTIVE");
	else fprintf(fout, "LOCKED");
	fprintf(fout, ", history: [");

	if(!card->urmHistory){
		fprintf(fout, "])\n");
	}
	else{
		THC cardH = card->urmHistory;
		while(cardH){
			fprintf(fout, "(%s)", cardH->str);
			cardH = cardH->urmHistory;
			if(cardH)
				fprintf(fout, ", ");
			else
				fprintf(fout, "])\n");
		}
	}
	fclose(fout);
	card = NULL;	
}


void show (LC L){
	FILE *fout;
	fout = fopen("output.out", "a");
	int i;
	for(i = 0;L != NULL; L = L->urm, i++){
		if(L->carduri){
			fout = fopen("output.out", "a");
			fprintf(fout, "pos%d: [\n", i);
			fclose(fout);
			TLC card = L->carduri;
			while(card != NULL){
				show_card(card);
				card = card->urmCard;
			}
			fout = fopen("output.out", "a");
			fprintf(fout, "]\n");
			fclose(fout);
		}
		else{
			fout = fopen("output.out", "a");
			fprintf(fout, "pos%d: []\n", i);
			fclose(fout);
		}
	}
	fclose(fout);
}


TLC localizareCard(LC L, long long no){
	while(L){
		if(L->carduri){
			TLC card = L->carduri;
			while(card){
				if(atoll(card->number) == no)
					return card;
				card = card->urmCard;
			}
		}
		L = L->urm;
	}
	return NULL;
}


TLC alocCardRedim(TLC card){
	TLC aux;
	aux = (TLC) malloc(sizeof(TCard));
	if(!aux) return NULL;
	aux->number = (char*) malloc(17);
	aux->pin = (char*) malloc(5);
	aux->expiry_date = (char*) malloc(6);
	aux->cvv = (char*) malloc(4);
	strcpy(aux->number, card->number);
	strcpy(aux->pin, card->pin);
	strcpy(aux->expiry_date, card->expiry_date);
	strcpy(aux->cvv, card->cvv);
	aux->balance = card->balance;
	aux->status = card->status;
	aux->incercari = 0;
	aux->urmHistory = card->urmHistory;
	aux->urmCard = NULL;
	return aux;
}


LC redimensionareLista(LC listaCarduri, int no){
	LC listaNoua = NULL;
	int poz;
	while(listaCarduri){
		TLC card = listaCarduri->carduri;
		while(card){
			poz = sumcif(atoll(card->number)) % no;
			alocLC(&listaNoua, poz);
			TLC aux = alocCardRedim(card);
			card = card->urmCard;
			add_card(aux, poz, listaNoua);

		}
		listaCarduri = listaCarduri->urm;
	}
	return listaNoua;
}


void delete_card(LC *L, char *no){
	no[16] = '\0';
	LC lista = *L;

	//verificare daca este primul din sublista
	while(lista){
		TLC p = lista->carduri;
		TLC ant = NULL;
		if(p != NULL){
			if(strcmp(no, p->number) == 0){
				if(!ant) {
						lista->carduri = p->urmCard;
				}
				else{
					ant->urmCard=p->urmCard;
				}
				return;
			}
			else{
				ant = p;
				p = p->urmCard;
			}
			while(p){
				if(strcmp(p->number, no) == 0){
					ant->urmCard = p->urmCard;
					return;
				}
				ant = p;
				p = p->urmCard;
			}
		}
		lista = lista->urm;
	}
}

THC alocHistory(char *str){
	THC aux;
	aux = (THC) malloc(sizeof(THistory));
	if(!aux) return NULL;
	aux->str = (char *)malloc(strlen(str) + 1);
	if(!aux->str){
		free(aux);
		return NULL;
	}
	memcpy(aux->str, str, strlen(str) + 1);
	aux->str[strlen(str) + 1] = '\0'; // pentru a ma asigura
	aux->urmHistory = NULL;
	return aux;
}

void insert_card (TLC *card, char *pin){
	FILE *fout;
	fout = fopen("output.out", "a");
	//verificare ACTIVE/NOW
	if((*card)->status == 2){
		fprintf(fout, "The card is blocked. Please contact ");
		fprintf(fout, "the administrator.\n");
	}

	THC history;
	char *str;
	pin[strlen(pin) - 1] = '\0'; // pentru asigurare
	if(strcmp((*card)->pin, pin) || (*card)->incercari == 3){
		if((*card)->incercari != 3){
			fprintf(fout, "Invalid PIN\n");
		}
		(*card)->incercari++;
		//adaugare in history
		//mai intai "compunem" textul pt history
		// lungimea maxima a secventei
		str = (char*)malloc(35 + strlen(pin));
		strcpy(str, "FAIL, insert_card ");
		strcat(str, (*card)->number);
		strcat(str, " ");
		strcat(str, pin);

	}
	else {
		if((*card)->status == 0){
			fprintf(fout, "You must change your PIN.\n");
		}
		(*card)->incercari = 0;
		//adaugare in history
		str = (char*)malloc(42);
		strcpy(str, "SUCCESS, insert_card ");
		strcat(str, (*card)->number);
		strcat(str, " ");
		strcat(str, pin);
		(*card)->incercari = 0;
	}

	history = alocHistory(str);
	if((*card)->urmHistory)
		history->urmHistory = (*card)->urmHistory;

	(*card)->urmHistory = history;

	if((*card)->incercari == 3){
			fprintf(fout, "The card is blocked. Please ");
			fprintf(fout, "contact the administrator.\n");
			(*card)->status = 2;
		}
	fclose(fout);
}


void cancel(TLC card, char *no){
	char *str;
	str = (char *) malloc(33);
	strcpy(str, "SUCCESS, cancel ");
	strcat(str, no);
	str[32] = '\0';

	THC history;
	history = alocHistory(str);
	if(card->urmHistory)
		history->urmHistory = card->urmHistory;
	card->urmHistory = history;
}


void unblock_card(TLC *card){
	(*card)->incercari = 0;
	(*card)->status = 1;
}

int count_digits(int no){
	int count = 0;
	while(no != 0)
    {
        no /= 10;
        ++count;
    }
    return count;
}

void pin_change(TLC *card, char *pin){
	char *str;
	if(count_digits(atoi(pin)) != 4){
		FILE *fout;
		fout = fopen("output.out", "a");
		fprintf(fout, "Invalid PIN\n");
		fclose(fout);

		str = (char *) malloc(34 + strlen(pin) + 1);
		strcpy(str, "FAIL, pin_change ");
		strcat(str, (*card)->number);
		strcat(str, " ");
		strcat(str, pin);
		str[strlen(str) - 1] = '\0';
	}
	else{
		pin[4] = '\0';
		strcpy((*card)->pin, pin);
		(*card)->status = 1;
		str = (char *) malloc(37 + strlen(pin) + 1);
		strcpy(str, "SUCCESS, pin_change ");
		strcat(str, (*card)->number);
		strcat(str, " ");
		strcat(str, pin);
		str[strlen(str)] = '\0';
	}
	THC history;
	history = alocHistory(str);
	if((*card)->urmHistory)
		history->urmHistory = (*card)->urmHistory;
	(*card)->urmHistory = history;

}


void balance_inquiry(TLC *card){
	FILE *fout;
	fout = fopen("output.out", "a");
	fprintf(fout, "%d\n", (*card)->balance);
	fclose(fout);

	THC history;
	char *str;
	str = (char *)malloc(42);
	strcpy(str, "SUCCESS, balance_inquiry ");
	strcat(str, (*card)->number);
	str[42]= '\0';
	history = alocHistory(str);
	if((*card)->urmHistory)
		history->urmHistory = (*card)->urmHistory;
	(*card)->urmHistory = history;
}


void recharge(TLC *card, char *suma){
	FILE *fout;
	fout = fopen("output.out", "a");
	char *str;
	if(atoi(suma) % 10 != 0){
		fprintf(fout, "The added amount must be multiple of 10\n");
		str = (char*) malloc(32 + strlen(suma));
		strcpy(str, "FAIL, recharge ");
		strcat(str, (*card)->number);
		strcat(str, " ");
		strcat(str, suma);
	}
	else{
		(*card)->balance += atoi(suma);
		fprintf(fout, "%d\n", (*card)->balance);
		str = (char*) malloc(35 + strlen(suma));
		strcpy(str, "SUCCESS, recharge ");
		strcat(str, (*card)->number);
		strcat(str, " ");
		strcat(str, suma);
	}
	str[strlen(str) - 1] = '\0';
	THC history;
	history = alocHistory(str);
	if((*card)->urmHistory)
		history->urmHistory = (*card)->urmHistory;
	(*card)->urmHistory = history;
	fclose(fout);
}


void cash_withdrawal(TLC *card, char *suma){
	FILE *fout;
	fout = fopen("output.out", "a");
	char *str;
	if(atoi(suma) % 10 != 0){
		fprintf(fout, "The requested amount must be multiple of 10\n");
		str = (char*) malloc(39 + strlen(suma));
		strcpy(str, "FAIL, cash_withdrawal ");
		strcat(str, (*card)->number);
		strcat(str, " ");
		strcat(str, suma);
	}
	else if((*card)->balance < atoi(suma)){
			fprintf(fout, "Insufficient funds\n");
			str = (char*) malloc(39 + strlen(suma));
			strcpy(str, "FAIL, cash_withdrawal ");
			strcat(str, (*card)->number);
			strcat(str, " ");
			strcat(str, suma);
		}
	else{
		(*card)->balance -= atoi(suma);
		fprintf(fout, "%d\n", (*card)->balance);
		str = (char*) malloc(42 + strlen(suma));
		strcpy(str, "SUCCESS, cash_withdrawal ");
		strcat(str, (*card)->number);
		strcat(str, " ");
		strcat(str, suma);
	}
	str[strlen(str) - 1] = '\0';
	THC history;
	history = alocHistory(str);
	if((*card)->urmHistory)
		history->urmHistory = (*card)->urmHistory;
	(*card)->urmHistory = history;
	fclose(fout);

}


void transfer_funds(TLC *card1, TLC *card2, char *suma){
	FILE *fout;
	fout = fopen("output.out", "a");
	char *str;
	if(atoi(suma) % 10 != 0){
		fprintf(fout, "The transferred amount must be multiple of 10\n");
		str = (char*) malloc(55 + strlen(suma));
		strcpy(str, "FAIL, transfer_funds ");
		strcat(str, (*card1)->number);
		strcat(str, " ");
		strcat(str, (*card2)->number);
		strcat(str, " ");
		strcat(str, suma);
	}
	else if((*card1)->balance < atoi(suma)){
			fprintf(fout, "Insufficient funds\n");
			str = (char*) malloc(55 + strlen(suma));
			strcpy(str, "FAIL, transfer_funds ");
			strcat(str, (*card1)->number);
			strcat(str, " ");
			strcat(str, (*card2)->number);
			strcat(str, " ");
			strcat(str, suma);
		}
	else{
		(*card1)->balance -= atoi(suma);
		(*card2)->balance += atoi(suma);
		fprintf(fout, "%d\n", (*card1)->balance);
		str = (char*) malloc(58 + strlen(suma));
		strcpy(str, "SUCCESS, transfer_funds ");
		strcat(str, (*card1)->number);
		strcat(str, " ");
		strcat(str, (*card2)->number);
		strcat(str, " ");
		strcat(str, suma);
	}
	str[strlen(str) - 1] = '\0';
	THC history1;
	history1 = alocHistory(str);
	if((*card1)->urmHistory)
		history1->urmHistory = (*card1)->urmHistory;
	(*card1)->urmHistory = history1;
	if(str[0] == 'S'){
		THC history2;
		history2 = alocHistory(str);
		if((*card2)->urmHistory)
			history2->urmHistory = (*card2)->urmHistory;
		(*card2)->urmHistory = history2;
	}
	fclose(fout);
}


THC localizareHistory(TLC card1, TLC card2, char *suma){
	char *str;
	str = (char *)malloc(57 + strlen(suma));
	strcpy(str, "SUCCESS, transfer_funds ");
	strcat(str, card1->number);
	strcat(str, " ");
	strcat(str, card2->number);
	strcat(str, " ");
	strcat(str, suma);
	str[strlen(str) - 1] = '\0';
	if(strcmp(card2->urmHistory->str, str) == 0){
		return NULL;
	}
	else{
		THC history = card2->urmHistory;
		while(history->urmHistory){
			if(strcmp(history->urmHistory->str, str) == 0){
				break;
			}
			history = history->urmHistory;
		}
		return history;
	}
}

void reverse_transaction(TLC *card1, TLC *card2, char *suma){

	FILE *fout;
	fout = fopen("output.out", "a");
	if((*card2)->balance < atoi(suma)){
		fprintf(fout, "The transaction cannot be reversed\n");
	}
	else{
		(*card1)->balance += atoi(suma);
		(*card2)->balance -= atoi(suma);
		char *str;
		//fprintf(fout, "%d\n", (*card2)->balance - atoi(suma));
		str = (char *)malloc(63 + strlen(suma));
		strcpy(str, "SUCCESS, reverse_transaction ");
		strcat(str, (*card1)->number);
		strcat(str, " ");
		strcat(str, (*card2)->number);
		strcat(str, " ");
		strcat(str, suma);
		str[63 + strlen(suma) - 1]= '\0';
		THC history;
		history = alocHistory(str);
		if((*card1)->urmHistory)
			history->urmHistory = (*card1)->urmHistory;
		(*card1)->urmHistory = history;
		//sterg si din card2 history

		THC history2;
		history2 = localizareHistory(*card1, *card2, suma);
		if(history2)
			history2->urmHistory = history2->urmHistory->urmHistory;
		else{
			(*card2)->urmHistory = (*card2)->urmHistory->urmHistory;
		}
	}
	fclose(fout);
}

void DistrugeL(LC l){
	LC aux;
	TLC auxC, card;
	THC auxH, history;
	while(l){
		aux = l;
		card = l->carduri;
		while(card){
			auxC = card;
			history = card->urmHistory;
			while(history){
				auxH = history;
				history = history->urmHistory;
				free(auxH->str);
				free(auxH);
			}
			card = card->urmCard;
			free(auxC->number);
			free(auxC->pin);
			free(auxC->cvv);
			free(auxC->expiry_date);
			free(auxC);
		}
		l=l->urm;
		free(aux);
	}
}