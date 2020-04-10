/* Adrian Argint 
	313 CB 		*/

#ifndef def
#define def


typedef struct history{
	char *str;
	struct history *urmHistory;
} THistory, *THC;

typedef struct card{
	char *number;
	char *pin;
	char *expiry_date;
	char *cvv;
	int balance;
	int status;// 0-NEW, 1-ACTIVE, 2-LOCKED
	int incercari;// incercari consecutive de a insera cardul
	THistory *urmHistory;
	struct card *urmCard;
}TCard, *TLC, **ALC; /*	TLC = TLista Carduri
						ALC = Adresa Lista Carduri */


typedef struct sublc{
	int no;
	TLC carduri;
	struct sublc *urm;
} LSC, *LC;  /* LSC= lista subcarduri
				LC = lista carduri (vector de LSC)	*/

#endif