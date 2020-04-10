/* Adrian Argint 
	313 CB 		*/

#ifndef functii
#define functii

int sumcif(long long x);

LC initializareLC(LC listaCarduri);

void add_card(TLC card, int poz, LC L);

void alocLC(LC *L, int no);

TLC alocCard(char *number, char *pin, char *expiry_date, char *cvv);

void show_card(TLC card);

void show (LC L);

TLC localizareCard(LC L, long long no);

TLC alocCardRedim(TLC card);

LC redimensionareLista(LC listaCarduri, int no);

void delete_card(LC *L, char *no);

void insert_card (TLC *card, char *pin);

void cancel(TLC card, char *no);

void unblock_card(TLC *card);

void pin_change(TLC *card, char *pin);

void balance_inquiry(TLC *card);

void recharge(TLC *card, char *suma);

void cash_withdrawal(TLC *card, char *suma);

void transfer_funds(TLC *card1, TLC *card, char *suma);

THC localizareHistory(TLC card1, TLC card2, char *suma);

void reverse_transaction(TLC *card1, TLC *card2, char *suma);

void DistrugeL(LC l);

#endif