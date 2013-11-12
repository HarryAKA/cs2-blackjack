// CS1022 - Homework 2, Blackjack
// Plays a single hand of blackjack with one player against the dealer.
// Author: Harry Kran-Annexstein, krananha@mail.uc.edu
// Date: September 12, 2013

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

// Define a type that represends the 4 suits of a deck of cards
enum suit_t {
  HEARTS,
  SPADES,
  DIAMONDS,
  CLUBS
};

// Defines a structure that represents a single card, including the
// card's suit, rank, and a bool that indicates if the card
// has been dealt or not.
struct card_t {
  // Card suit
  suit_t suit;
  // 1 = Ace
  // 2 - 10, number card of corresponding value
  // 11 = jack, 12 = queen, 13 = king
  int rank;
  // false if still in the deck, true if dealt to a player
  bool dealt;
};

// A single, standard deck of 52 playing cards.
const int DECK_SIZE = 52;
// Point value for all face cards (Jack, Queen, King)
const int FACECARD_VALUE = 10; 
// Winning point value.
const int WIN_VALUE = 21;
// Additional point value for first Ace, unless it causes point value > 21. 
const int ACE_VALUE = 10; 
// Max dealer_value total, must be less than to Hit.
const int DEALER_MAX = 17; 
/**
 * Initialize the deck so that all cards exist, and are not yet dealt.
 * @param the uninitialized deck of cards, an array of size DECK_SIZE
 */
void init_deck(card_t deck[]) {
  int pos = 0;
  for (int s = 0; s < 4; s++) {
    for (int rank = 1; rank <= 13; rank++) {
      deck[pos].suit = (suit_t) s;
      deck[pos].rank = rank;
      deck[pos].dealt = false;
      pos++;
    }
  }
}

int getRandomCard(card_t deck[]){
  int ret = rand() % DECK_SIZE;
  while(deck[ret].dealt){
    ret = rand() % DECK_SIZE;
  }
  // ret must be an index that has not been dealt
  deck[ret].dealt = true;
  return ret;
}

string getSuit(suit_t s){
  switch(s){
    case HEARTS: return "Hearts";
    case SPADES: return "Spades";
    case DIAMONDS: return "Diamonds";
    case CLUBS: return "Clubs";
  }
}

string getRank(int r){
  switch(r){
    case 1: return "Ace";
    case 2: return "Two";
    case 3: return "Three";
    case 4: return "Four";
    case 5: return "Five";
    case 6: return "Six";
    case 7: return "Seven";
    case 8: return "Eight";
    case 9: return "Nine";
    case 10: return "Ten";
    case 11: return "Jack";
    case 12: return "Queen";
    case 13: return "King";
  }
}

int getValue(vector<int> &hand, card_t deck[]){
  int value = 0;
	bool ace = false;
  for(int i=0; i < hand.size(); i++){
    int card_rank = deck[hand[i]].rank;
		if(card_rank == 1){
			value++;
			ace = true;}
    else if((card_rank > 1)&&(card_rank < 11)){
      value += card_rank;}
    else if(card_rank > 10){
      value += FACECARD_VALUE;}
  }
	if((ace) && (value+ACE_VALUE <= 21)){
		value += ACE_VALUE;}
  return value;
}



void printHand(vector<int> &hand, card_t deck[], bool player){
  if(player){ 
		cout << "Player Hand: \n";}
  else{
		cout << "Dealer Hand: \n";}
  for(int i = 0; i < hand.size(); i++){
    int deck_index = hand[i];
    cout << getRank(deck[deck_index].rank) << " of ";
    cout << getSuit(deck[deck_index].suit) << endl;
  }
  cout << "=>Total Value: " << getValue(hand, deck) << "\n"  << endl;
}

int winCheck(int player_value, int dealer_value){
	if((player_value == WIN_VALUE)&&(dealer_value == WIN_VALUE)){
		return 1;}
	else if((player_value > WIN_VALUE)&&(dealer_value <= WIN_VALUE)){
		return 2;}
	else if((dealer_value > WIN_VALUE)&&(player_value <= WIN_VALUE)){
		return 3;}
	else if(player_value > dealer_value){
		return 4;}
	else if(dealer_value > player_value){
		return 5;}
	else if(dealer_value == player_value){
		return 1;}
	else{
		return 0;}
}

string winResult(int r){
	switch(r){
	case 1: return "** Push, Nobody Wins! ** \n";
	case 2: return "** Player Bust, Dealer Wins! ** \n";
	case 3: return "** Dealer Bust, Player Wins! ** \n";
	case 4: return "** Player Wins! ** \n";
	case 5: return "** Dealer Wins! ** \n";
	}
}

int main() {
	cout << "|| WELCOME TO BLACKJACK || \n";
  // Seed the random number generator
  srand(time(NULL));
  // To get a random integer call, rand()
  // the value will be between 0 and RAND_MAX.

  // Declare and initialize the deck of cards.
  card_t deck[DECK_SIZE];
  init_deck(deck);
	int player_value = 0;
	int dealer_value = 0;
	int win = 0; //win is flag that indicates no winner or type of win
	bool pstay = false;
	bool dstay = false;
  // TODO(you): Finish the program.
  vector<int> player_hand;
  vector<int> dealer_hand;
  player_hand.push_back(getRandomCard(deck));
  dealer_hand.push_back(getRandomCard(deck)); 
  printHand(dealer_hand, deck, false);
  player_hand.push_back(getRandomCard(deck));
  dealer_hand.push_back(getRandomCard(deck));
  printHand(player_hand, deck, true);
	player_value = getValue(player_hand, deck);
	dealer_value = getValue(dealer_hand, deck);
  while(!pstay){
		string H = "H";
		string S = "S";
		cout << "(H)it or (S)tay?" << endl;
		string decision;
		cin >> decision;
		while((H.compare(decision) != 0)&&(S.compare(decision) != 0)){
			cout << "Please enter 'H' for Hit or 'S' for Stay:" << endl;
			cin >> decision;}
		if(S.compare(decision) == 0){
			cout << "Player Stays. Final ";			
			pstay = true;}
		else {
      cout<< "Player Hits." << endl;
		  player_hand.push_back(getRandomCard(deck));
		  player_value = getValue(player_hand, deck);}
		if(player_value >= WIN_VALUE){
			pstay = true;}
		else{
			printHand(player_hand, deck, true);}
	} // end player turn while loop
  if(player_value > WIN_VALUE){
		win = winCheck(player_value, dealer_value);
		cout << winResult(win) << endl;
		cout << "Final Hands:" << endl;
		printHand(dealer_hand, deck, false);
		printHand(player_hand, deck, true);
		return 0;
	}
	printHand(dealer_hand, deck, false);
	while(dealer_value < DEALER_MAX){
		  cout << "Dealer Hits. \n" << endl;
      dealer_hand.push_back(getRandomCard(deck));
		  dealer_value = getValue(dealer_hand, deck);
			if(dealer_value < DEALER_MAX){
				printHand(dealer_hand, deck, false);}
	}	// end dealer turn while loop
	win = winCheck(player_value, dealer_value);
	cout << winResult(win) << endl;
	cout << "Final Hands:" << endl;
	printHand(dealer_hand, deck, false);
	printHand(player_hand, deck, true);
	return 0;
}
