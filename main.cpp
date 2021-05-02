/*

The goal here is to make a simple blackjack game with user input. We're gonna 
follow the rules set from this source: 
https://www.blackjackapprenticeship.com/how-to-play-blackjack/

The game will break down into these steps:

1. Player bets money
2. Dealer deals cards to player
3. Player plays hand
4. Dealer plays hand
5. Repeat steps 2 through 5.
6. Declaring the Winner. 

As the player, the ultimate goal is to the beat the dealer.
How does the player beat the dealer?

1. The player draws a hand value that is greater than the dealer's hand value
2. The dealer draws a hand value over 21
3. The player draws a hand value of 21 on the first two cards
    when the dealer does not

How does the player lose to the dealer?

1. The player's hand value exceeds 21 at any point
2. The dealer's hand value is greater than yours at the end of the round

For now, let's
make it with just one user and the dealer. We also won't include betting
or wagers or any of that stuff.

Simplifying assumptions:
1. No splitting
2. One player only
3. Wagers with cash instead of chips
4. No double down
5. All aces are 11s.

Let's go into the rules with a bit more depth:

1. Player bets money
    we ask how much they wanna bet, and the computer lets the person
    input some dollar amount

2. Dealer deals cards to the player
    Player's initial card value is set

3a. Player plays hand (select option by pressing 1-3)
This step is the one that'll be repeated over and over again.

3b. Dealer plays hand

4. If somebody hasn't busted or won, compare card totals
    and declare a winner


Deck Specifications

    only four of each card in the deck
    contains Kings(K), Queens(Q), & Jacks(J) with numerical values of 10
    contain Ace(A) with numerical value of 11 
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "blackjack_header_functions.hpp"
//#include "BlackjackClass.hpp" for when implementing classes

// This vector represents all of the cards as numbers and serves as our
// "mathematical deck."

std::vector <int> cardvals = {
2, 2, 2, 2,
 3, 3, 3, 3, 
4, 4, 4, 4,
 5, 5, 5, 5,  
6, 6, 6, 6,
 7, 7, 7, 7, 
8, 8, 8, 8,
 9, 9, 9, 9, 
10, 10, 10, 10,
 10, 10, 10, 10,
10, 10, 10, 10,
 10, 10, 10, 10,
 11, 11, 11, 11};

// cards face value with respective suite C=>Clubs, D=>Diamonds, S=>Spades, & H=>Hearts
// ***Not matched with numerical values yet***
// std::vector <std::string> cards = { "AC" , "AH" , "AS" , "AD" ,"KC" , "KH" , "KS" , "KD" , 
// "QC" , "QH" , "QS" , "QD", "JC" , "JH" , "JS" , "JD" , "10C" , "10H" , "10S" , "10D" ,
// "9C" , "9H" , "9S" , "9D" ,"8C" , "8H" , "8S" , "8D" , "7C" , "7H" , "7S" , "7D" , 
// "6C" , "6H" , "6S" , "6D" , "5C" , "5H" , "5S" , "5D" , "4C" , "4H" , "4S" , "4D" , 
// "3C" ,"3H" , "3S" , "3D" , "2C" , "2H" , "2S" , "2D" };



// Here, we're initializing all of our variables. We set our vectors
// so we can fill them and manipulate them more easily later on.


std::vector <int> shuffled_cardvals = {};
std::vector <int> shell={};

std::vector <int> initialhand = {};
std::vector <int> dealerhand = {};
std::vector <int> playerhand = {};

double wager;
char input;
int option ;
int player_hitnumber;

int playerhand_total = 0;
int dealerhand_total = 0;


int main() {

    
    // Intro
    std::cout << "\n" << "Good Evening. This is Samuel L. Jackson. Welcome to BlackJack(son). \n";

    // Give the player the optoin to back out right away... if they're scared UwU
    std::cout << "Ready for the game of your life? If not, we totally get it your just not as bold as the 'Tabloid'! y/n\n";
    std::cin >> input;
    
    while(input == 'y') {
    std::cout << "What's your wager, MouthaFucka?\n";
    std::cin >> wager;
    


    //shuffle the cards and output the results
    shuffled_cardvals.clear(); //.clear the deck and both hands so we get a fresh start each go around.
    shuffle(cardvals);

    // These two lines let us see the shuffled_cardvals vector and exist for diagnostic purposses.
    // std::cout << "\n" << "Shuffled card values: " << "\n";
    // for(int i =  0; i < shuffled_cardvals.size(); i++)  {std::cout << shuffled_cardvals[i] << " ";}
    

    // Wake up, samurai, it's time to dual (duel) (deal) (deel) cards
    playerhand.clear();
    dealplayer(shuffled_cardvals);
    std::cout << "Player Hand: " << playerhand[0] << " " << playerhand[1];
    
    dealerhand.clear(); 
    dealdealer(shuffled_cardvals);
    // to make the game tougher and align with standard rules, we only show the player
    // the dealer's second card.
    std::cout << "Dealer's Second Card: " <<  dealerhand[1]; 

    if(playerhand[0] + playerhand[1] == 21 && dealerhand[0] + dealerhand[1] != 21) {

        std::cout << "\nyeetus deletus aka Big BLACKjack. God dammit, you've won.";
        std::cout << "\nYour earnings: " << wager * 1.5;
        std::cout << "\nWanna Play Again? y/n\n";
        std::cin >> input;
        
    }


    else if(playerhand[0] + playerhand[1] != 21 && dealerhand[0] + dealerhand[1] == 21) 

        {selectionMenu();}
        
        
    else if(playerhand[0] + playerhand[1] != 21 && dealerhand[0] + dealerhand[1] != 21) 

        {selectionMenu();}
       


    else if(playerhand[0] + playerhand[1] == 21 && dealerhand[0] + dealerhand[1] == 21) {

        std::cout << "\nPush. The Game will restart as both you and the dealer both got BLACKjack.";
        std::cout << "\nYour wager has been returned.";
        input = 'n';

    }

    }

    if(input == 'n') {std::cout << "Rog."; exit (EXIT_SUCCESS);}

return 0;
}

// Future Goals For Game
// Link the card values to the actual deck of strings
// Add in the case where the player can decide whether they want the Ace to be 11 or 1
// Make game playable to multiple players
// Implement Classes to Run the Game