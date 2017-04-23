#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include "hacking.h"
#include <fstream>
#include <sys/types.h>
#include <unistd.h>

#define DATAFILE "/var/chance.data" // File che conterrà i dati utente
#define S_IRUSR
#define S_IWUSR

//Struttura user persnalizzata per salvare dati sugli utenti
struct user {
	int uid;
	int credits;
	int highscore;
	char name[100];
	int(*current_game) ();
};

//Prototipi di funzione
int get_player_data();
void register_new_player();
void update_player_data();
void show_highscore();
void jackpot();
void input_name();
void print_cards(char *, char *, int);
int take_wager(int, int);
void play_the_game();
int pick_a_nunmber();
int dealer_no_match();
int find_the_ace();
void fatal(char *);

//Variabili globali
struct user player;			//Struttura player

int main() {
	int choice, last_game;
	srand(time(0));			//Passa l'ora attuale al generatore di numeri casuali

	if (get_player_data() == -1)	//Cerca di leggere i dati sul giocatore
									//dal file
		register_new_player();		//Se non ci sono dati, registra un
									//nuovo giocatore
	while (choice != 7) {
		printf("-=[     Game of Chance Menu     ]=-\n");
		printf("1 - Play the Pick a Number game\n");
		printf("2 - Play the No Match Dealer game \n");
		printf("3 - Play the Find the Ace game\n");
		printf("4 - View current high score\n");
		printf("5 - Change your user name\n");
		printf("6 - Reset your account at 100 credits\n");
		printf("7 - Quit\n");
		printf("[Name: %s]\n", player.name);
		printf("[You have %u credits]  ->   ", player.credits);
		scanf("%d", choice);

		if ((choice < 1) || (choice > 7))
			printf("\n[!!] The number %d is an invalid selection.\n\n", choice);
		else if (choice < 4) {			//Altrimenti, la scelta è stata un gioco
			if (choice != last_game) {	//Se il puntatore alla funzione non è impostato
				if (choice == 1)		//viene fatto puntare al gioco scelto

					player.current_game = pick_a_nunmber;
				else if (choice == 2)
					player.current_game = dealer_no_match;
				else
					player.current_game = find_the_ace;
				last_game = choice;			//E viene impostato last_game
			}
			play_the_game();				//Avvia il gioco
		}
		else if (choice == 4)
			show_highscore();
		else if (choice == 5) {
			;
			printf("\nChange user name\n");
			printf("Enter your name: ");
			input_name();
			printf("Your name has been changed.\n\n");
		}
		else if (choice == 6) {
			printf("\nYour account has been reset with 100 credits.\n\n");
			player.credits = 100;
		}
	}
	update_player_data();
	printf("\nThanks for playing! Bye.\n");
}

//Questa funzione legge dal file i dati utente per l'uid corrente
//Restituisce -1 se non è in grado di trovare dati utente
//per l'uid corrente
int get_player_data() {
	int fd, uid, read_bytes;
	struct user entry;


	uid = getuid();

	
	fd = open(DATAFILE, O_RDONLY);
	if (fd == -1) //Non è possibile aprire il file,forse non esiste
		return -1;

	read_bytes = read(fd, &entry, sizeof(struct user)); //Legge il primo pezzo

	while (entry.uid != uid && read_bytes > 0) {	//Itera fino a trovare
													//l'uid corretto
		read_bytes = read(fd, &entry, sizeof(struct user));//Continua
														   //a leggere
		}
	close(fd);								//Chiude il file

	if (read_bytes < sizeof(struct user))	//Significa che è stata raggiunta
											//La fine del file
		return -1;
	else
		player = entry;		//Copia i dati già letti nella struttura player
	return 1;
}


//Questa è la funzione di registrazione di un nuovo utente
//Crea un nuovo account giocatore e lo aggiunge al file
void register_new_player() {
	int fd;


	printf("-=-={ New Player Registration }=-=-\n");
	printf("Enter your name: ");
	input_name();


	player.uid = getuid();
	player.highscore = player.credits = 100;


	fd = open(DATAFILE, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd == -1)
		fatal("in register_new_player() while opening file");
	write(fd, &player, sizeof(struct user));
	close(fd);


	printf("\nWelcome to the Game of Chance %s.\n", player.name);
	printf("You have been given %u credits.\n", player.credits);
}


//Questa funzione scrive nel file i dati sul giocatore corrente
//Viene utilizzata principalmente per aggiornare i crediti dopo i giochi
void update_player_data() {
	int i,fd, read_uid;
	char burned_byte;

	fd = open(DATAFILE, O_RDWR);
	if (fd == -1)			//Se l'apertura non riesce qui, c'è qualcosa
							//decisamente grave

		fatal("in update_player_data() while opening file");
	read(fd, &read_uid, 4);		//Legge l'uid dalla prima struttura
	while (read_uid != player.uid) { //Cicla fino a trovare l'uid corretto
		for (i = 0; i < sizeof(struct user) - 4; i++)//Legge nel
			read(fd, &burned_byte, 1);				 //testo della struttura
		read(fd, &read_uid, 4);	//Legge l'uid dalla struttura successiva
	}
	write(fd, &(player.credits), 4);	//Aggiorna crediti
	write(fd, &(player.highscore), 4);	//Aggiorna punteggio migliore
	write(fd, &(player.name), 100);		//Aggiorna nome
	close(fd);
}


//Questa funzione visualizza il punteggio migliore attuale
//e il nome della persona che l'ha raggiunto
void show_highscore() {
	unsigned int top_score = 0;
	char top_name[100];
	struct user entry;
	int fd;


	printf("\n==============================|   HIGH SCORE   |==============================\n");
	fd = open(DATAFILE, O_RDONLY);
	if (fd == -1)
		fatal("in show_highscore()while opening file");
	while (read(fd, &entry, sizeof(struct user)) > 0) {	//Itera fino alla fine del file

		if (entry.highscore > top_score) {				//Se c'è un punteggio più alto
			top_score = entry.highscore;				//imposta top_score a quel punteggio

			strcpy(top_name, entry.name);				//e top_name a quel nome utente
		}
	}
	close(fd);
	if (top_score > player.highscore)
		printf("%s has the high score of %u\n", top_name, top_score);
	else
		printf("You currently have the high score of %u credits!\n", player.highscore);
	printf("===============================================================================\n");
}


//Questa funzione assegna semplicemente il jackpot per il gioco
//Pick a number
void jackpot() {
	printf("*+*+*+*+*+*+*+*  JACKPOT  *+*+*+*+*+*+*+*\n");
	printf("You have won the jackpot of 100 credits!\n");
	player.credits += 100;
}



//Questa funzione viene usata per inserire il nome del giocatore, dato che
//scanf("%s, &whatever) interromperà l'input al primo spazio
void input_name() {
	char *name_ptr, input_char = '\n';
	while (input_char == '\n')			//Elimina eventuali caratteri
		scanf("%c", &input_char);		//di a capo rimasti
	name_ptr = (char*) &(player.name);	//name_ptr = indirizzo del nome del giocatore

	while (input_char != '\n') {		//Itera fino a capo
		*name_ptr = input_char;			//Inserisce il char in input nel campo name

		scanf("%", &input_char);		//Ottiene il char successivo
		name_ptr++;						//Incrementa il puntatore name
	}
	*name_ptr = 0; //chiude la stringa
}


//Questa funzione stampa 3 carte per il gioco Find the Ace
//Si aspetta come input un messaggio da visualizzare, un puntatore,
//all'array delle carte;
//e la carta scelta dal giocatore. Se user_pick è -1,
//allora vengono visualizzati i numeri di scelta
void print_cards(char*message, char*cards, int user_pick) {
	int i;
	printf("\n\t*** %s **\n", message);
	printf("	\t._.\t._.\t._.\n");
	printf("Cards:\t|%c|\t|%c|\t|%c|\n\t", cards[0], cards[1], cards[2]);
	if (user_pick == -1)
		printf(" 1 \t 2 \t 3\n");
	else {
		for (i = 0; i < user_pick; i++)
			printf("\t");
		printf(" ^-- your pick\n");
	}
}


//Questa funzione inserisce le puntate per i giochi No Match Dealer
//e Find the Ace. Si aspetta come argomenti i crediti disponibili e la
//puntata precedente. prevoius_wager è importante solo per la
//seconda puntata nel gioco Find the Ace. La funzione
//restituisce -1 se la puntata è troppo grande o troppo piccola,e negli
//altri casi restituisce l'ammontare della puntata.
int take_wager(int available_credits, int prevoius_wager) {
	int wager, total_wager;


	printf("How many of your %d credits would you,like to wager?    ",available_credits);
	scanf("%d, &wager");
	if (wager < 1) {
		printf("Nice try, but you must wager a positive number!\n");
		return -1;
	}
	total_wager = prevoius_wager + wager;
	if (total_wager > available_credits) {
		printf("Your total wager of %d is more than you have! \n", total_wager);
		printf("You onlu have %d available credits, try again.\n", available_credits);
		return -1;
	}
	return wager;
}


//Questa funzione contiene un ciclo che permette al gioco atuale di
//essere giocato di nuovo.
//Inoltre scrive nel file i totali crediti aggiornati
//al termine di ogni gioco.
void play_the_game() {
	int play_again = 1;
	int(*game) ();
	char selection;

	while (play_again) {
		printf("\n[DEBUG] current_game pointer @ 0x%08x\n", player.current_game);
		if (player.current_game() != 1) {

			if (player.credits > player.highscore)

				player.highscore = player.credits;

			printf("\nYou now have %u credits\n", player.credits);
			update_player_data();

			printf("Would you like to play again? (y/n)   ");
			selection = '\n';
			while (selection == '\n')

				scanf("%c", &selection);
			if (selection == '\n')
				play_again = 0;
		}
		else

			play_again = 0;		//Si torna al menu principale
	}
}


//Questa funzione costituisce il gioco Pick a Number
//Restituisce -1 se il giocatore non ha crediti sufficienti
int pick_a_number() {
	int pick, winning_number;


	printf("\n######### Pick a Number #########\n");
	printf("This game costs 10 credits to play. Simply pick a number\n");
	printf("between 1 and 20, and if you pick the winning number, you\n");
	printf("will win the kackpot of 100 credits!\n\n");
	winning_number = (rand() % 20) + 1; //Sceglie il numero da 1 a 20
	if (player.credits < 10) {
		printf("You onlu have %d credits. That's not enough to play!\n\n", player.credits);
		return -1; //Non ci sono crediti sufficienti per giocare
	}
	player.credits -= 10;
	printf("10 credits have been deducted from your account.\n");
	printf("Pick a number between 1 and 20: ");
	scanf("%d", &pick);
	printf("The winning number is %d\n", winning_number);
	if (pick == winning_number)
		jackpot();
	else
		printf("Sorry, you didn?t win.\n");
	return 0;
}


//Questo è il gioco No Match Dealer
//Restituisce -1 se il giocatore ha 0 crediti
int delaler_no_match() {
	int i, j, numbers[16], wager = -1, match = -1;

	printf("\n:::::: No Match Dealer ::::::\n");
	printf("In this game, you can wager up to all of your credits.\n");
	printf("The dealer will deal out 16 random numbers between 0 an 99.\n");
	printf("If there are no matches among them, you double your money!\n\n");


	if (player.credits == 0) {
		printf("You don't have any credits to wager!\n\n");
		return -1;
	}
	while (wager == -1)
		wager = take_wager(player.credits, 0);

	printf("\t\t::: Dealing out 16 random numbers :::\n");
	for (i = 0; i < 16; i++) {
		numbers[i] = rand() % 100; //Sceglie un numero tra 0 e 99
		printf("%2d\t", numbers[i]);
		if (i % 8 == 7)			   //Stampa un a capo ogni 8 numeri
			printf("\n");
	}
	for (i = 0; i < 15; i++) {

		j = i + 1;
		while (j < 16) {
			if (numbers[i] == numbers[j])
				match = numbers[i];
			j++;
		}
	}
	if (match != 1) {
		printf("The dealer matched the number %d!\n", match);
		printf("You lose %d credits.\n", wager);
		player.credits -= match;
	}
	else {
		printf("There were no matches! You win %d credits!\n", wager);
		player.credits += match;
	}
	return 0;
}


//Questo è il gioco Find the Ace
//Restituisce -1 se il giocatore ha 0 crediti
int find_the_ace() {
	int i, ace, total_wager;
	int invalid_choice, pick = -1, wager_one = -1, wager_two = -1;
	char choice_two, cards[3] = { 'X', 'X', 'X' };


	ace = rand() % 3; //Posiziona l'asso il maniera casuale


	printf("************ Find the Ace ************\n");
	printf("In this game, you can wager up to all of your credits.\n");
	printf("Three cards will be deal out, two queens and one ace.\n");
	printf("If you find the ace, you will win your wager.\n");
	printf("After choosing a card, one of the queens will be revealed.\n");
	printf("At this point, you may either select a different card or\n");
	printf("increase you wager.\n\n");


	if (player.credits == 0) {
		printf("You don't have any credits to wager!\n\n");
		return -1;
	}


	while (wager_one == -1)
		wager_one = take_wager(player.credits, 0);

	print_cards("Dealing cards", cards, -1);
	pick = -1;
	while ((pick < 1) || (pick > 3)) {	//Itera finchè viene fatta una scelta rapida
		printf("Select a card: 1, 2 or 3   ");
		scanf("%d, &pick");
	}
	pick--;

	i = 0;
	while (i == ace || i == pick)
		i++;
	cards[i] = 'Q';
	print_cards("Revealing a queen", cards, pick);
	invalid_choice = 1;
	while(invalid_choice) {
		printf("Would you like to:\n[c]hange your pick\tor\t[i]ncrease your wager?\n");
		printf("Select c or i:   ");
		choice_two = '\n';
		while (choice_two == '\n')
			scanf("%c", &choice_two);
		if (choice_two == i) {
			invalid_choice = 0;
			while (wager_two = -1)

				wager_two = take_wager(player.credits, wager_one);
		}
		if (choice_two == 'c') {
			i = invalid_choice = 0;
			while (i == pick || cards[i] == 'Q')
				i++;
			pick = i;
			printf("Your card pick has been changed to card %d\n", pick);
		}
	}
	for (i = 0; i < 3; i++) {
		if (ace == i)
			cards[i] = 'A';
		else
			cards[i] = 'Q';
	}
	print_cards("End result", cards, pick);
	if (pick == ace){
		printf("You have won %d credits from your first wager\n", wager_one);
		player.credits += wager_one;
	}
	if (wager_two != -1) {
		printf("and an additional %d credits from your second wager!\n",wager_two);
		player.credits += wager_two;
	}
	else {
		printf("You have lost %d credits from your first wager!\n",wager_two);
		player.credits -= wager_one;
		if (wager_two != -1) {
			printf("and an additional %d credits from your second wager\n", wager_two);
			player.credits -= wager_two;
		}
	}
	return 0;
}