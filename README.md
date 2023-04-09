# The Retro Cinema
## Tema aleasa - Cinematograf
### Clasele:
  * Time - Reprezinta ora si minutul la care incepe un film. 
  * TimeVector - Reprezinta un vector de tip Time si este corelata prin compunere cu clasa Time. 
  * Movie - Reprezinta titlul, tipul, genul si durata unui film.
  * MovieVector - Reprezinta un vector de tip Movie si este corelata prin compunere cu clasa Movie. 
  * Cinema - Reprezinta numele, locatia si numarul de locuri unui cinematograf.
  * CinemaVector -Reprezinta un vector de tip Cinema si este corelata prin compunere cu clasa Cinema. 
  * Program - Reprezinta fimul, cinematograful la care este ecranizat acesta, orele la care incepe si pretul unui bilet. Este corelata prin compunere cu clasele Movie, Cinema si TimeVector.
  * ProgramVector - Reprezinta un vector de tip Program si este corelata prin compunere cu clasa Program. 
  * Ticket - Reprezinta numarul de bilete si pretul unui bilet.
  * User - Reprezinta numele, prenumele, adresa de email si numarul de telefon al clientului.

### Functionalitati:
Programul permite realizarea unei rezervari de bilete la un cinema. Rezervarea se poate face in doua feluri:

1. Prin alegerea filmului dorit dintr-o lista, iar apoi a cinematografului la care ruleaza acel film.
2. Prin alegerea cinematografului preferat dintr-o lista, iar apoi a filmului dorit, daca ruleaza la acel cinema.

Odata ce au fost filmul si cinematograful, urmeaza alegerea orei de inceput si a numarului de bilete.

Apoi trebuie completate datele de identificare pentru realizarea rezervarii:
* nume;
* prenume;
* adresa de email;
* numar de telefon.

La final se afiseaza informatiile rezervarii si pretul total. Utilizatorul poate confirma rezervarea, caz in care aplicatia se finalizeaza sau o poate anula.

  