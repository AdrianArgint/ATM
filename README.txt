/* Adrian Argint 
	313 CB 		*/

Teme este impartita in main si functii, ambele fiind fisiere c. La inceput se
imparte inputul in vector de stringuri, iar prin switch se apeleaza functia
corespunzatoare. In "functii.c" exista cate o functie pt fiecare operatie din
enunt. Prima operatie (add card) se face prin alocarea de submultimi
corespunzatoare submultimii in care urmeaza a fi pus. Se aloca submultimiile
pana la numarul respectiv, se aloca celula cardului apoi se leaga. Cardul este
format din stringuri pentru nume, pin, data de expirare si cvv, soldul este un
numar intreg, statusul depinde de valoarea numarului din variabila "status"
(0-NEW, 1-ACTIVE, 2-LOCKED), urmand 2 pointeri spre istoric si cardul urmator.
Istoricul este sub forma de lista, string pentru text si pointer pentru
urmatorul istoric. la fel este si submultimea de carduri, adaugandu-i-se o
valoare intreaga pentru a le contoriza. Nu am idee de ce nu merge valgrind nici
la primul test. Local imi semnalizeaza eroare chiar si la o atribuire de genul
"count = 0" si nu am nici ce mai vaga idee. La fel, desi ma joc cu fopen si
fclose prea des probabil, imi da eroare la orice fopen si tot ce tine de acesta.