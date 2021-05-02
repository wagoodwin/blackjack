#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

// this "extern" business allows us to access variables between
// the header and source file.

extern std::vector <std::string> cards;
extern std::vector <int> shuffled_cardvals;
extern std::vector <int> initialhand;
extern std::vector <int> shell;
extern std::vector <int> playerhand;
extern std::vector <int> dealerhand;
extern double wager;
extern int option;
extern char input;

extern int player_hitnumber;
extern int dealer_hitnumber;

extern int playerhand_total;
extern int dealerhand_total;


int selectionMenu();
void dealer_turn();
void DetermineWinner(int playerhand_total, int dealerhand_total);
std::vector <int> shuffle(std::vector <int> x);
std::vector <int> dealplayer(std::vector <int> x);
std::vector <int> dealdealer(std::vector <int> x);




std::vector <int> shuffle(std::vector <int> x) {

    // First, generate a random seed for the card shuffling process.
    // If we don't do this step, every time we call random_shuffle(),
    // we'll get the same order of cards for our shuffled deck, making
    // it not very random.
    
    std::srand(std::time(0));

    // Next, shuffle the cards and their face values. We're using
    // a predefined language.

    std::random_shuffle(x.begin(), x.end());

    // Now systematically add on to the shuuffled_cardvals 
    // vector with .push_back.

    for(int i =  0; i < x.size(); i++) {shuffled_cardvals.push_back(x[i]);}


    return shuffled_cardvals;

}


  std::vector <int> dealplayer(std::vector <int> x) {

      // x is the vector you want to pull stuff out of. 
      // For us, that's shuffled_cardvals.

      // We're often using the .push_back() function, as it's
      // super nice for expanding empty vectors and filling
      // those vectors with values.

    for(int i = 0; i < 2; i++) {playerhand.push_back(x[i]);}
    std::cout << "\n";
    // Diagnostic output
    //for(int i =  0; i < initialhand.size(); i++) {std::cout << initialhand[i] << " ";}

    return playerhand;

  }

    std::vector <int> dealdealer(std::vector <int> x) {

        for(int i = 2; i < 4; i++) {dealerhand.push_back(x[i]);}
        std::cout << "\n";
        // Diagnostic output
        //for(int i =  0; i < initialhand.size(); i++) {std::cout << initialhand[i] << " ";}
        return dealerhand;
        
  }


// selectionMenu is our Grand Pubah function. It's the central hub
// that takes you to different functions based on the option you choose.

int selectionMenu() {

    int option = 2;
    int select = 2;

    // you can only surrender on your first hand. Thus, we don't want to show
    // that show message on the second option. This conditional below
    // allows us to show the message on the first option and then only show
    // hit or stand optios afterwards.

    
        std::cout << "\nPlease Select An Option: Stand(1), Hit(2), or Surrender(3)\n";
        std::cin >> option;
    

        switch(option) {
        
            case 1:
            
                //playerhand_total = 0; //resets players total hand value
                //dealerhand_total = 0;
                dealer_turn();
                playerhand_total=0;
                dealerhand_total=0;
                

                // Here, we're calculating the dealer and player's total hand values by summing up the 
                // values in their respective hands.

                for(int i =0; i < playerhand.size(); i++){playerhand_total = playerhand_total + playerhand[i];}
                for(int i =0; i < dealerhand.size(); i++){dealerhand_total = dealerhand_total + dealerhand[i];}
                
                std::cout << "Stand\n";

                DetermineWinner(playerhand_total,dealerhand_total);
                
        
                break;

            case 2:

                //playerhand_total = 0; // add this line to reset the player's total face value in the event of a surrender

                // An old problem we had was that the player couldn't beat the dealer
                // if the player had a higher card values.

                // If you press anything other than 2, option != 2, so the while
                // loop would stop, breaking the code. This phenomenon would only happen
                // after you pressed 2. Here's why:

                // We make the player press "option" INSIDE case 2. If the player 
                // sets option = 1, the computer will loop around, check the while()
                // statement, and exit out of the code because the condition of option == 1
                // is no longer met. That's why the computer won't execute instructions
                // after pressing hit once.

            
                while(select==2){
                    for(int player_hitnumber = 0; select == 2; player_hitnumber = 1 + player_hitnumber){
                        
                        std::cout << "Hit\n";
                        playerhand.push_back(shuffled_cardvals[4 + player_hitnumber]);

                        // Diagnostic stuff again the code below. Just let us see playerhit_number
                        // and certain values of playerhand.
                        // std::cout << "RADDA " << player_hitnumber;
                        // std::cout << "\n" << playerhand[ 2 + player_hitnumber] << "\n";

                        playerhand_total = 0;


                        
                        for(int i =0; i < playerhand.size(); i++) 
                            playerhand_total = playerhand_total + playerhand[i];
                            

                        if(playerhand_total > 21) {
                            std::cout << "\nBUST. You lose all your wager and have brought dishonor to your family\n";
                            exit (EXIT_SUCCESS); // DON'T QUESTION THIS. NOTHING TO SEE HERE.(just ends game automatically)
                            }


                        else{std::cout << "\nYour total is " << playerhand_total <<"\n"; std::cout << "Stand(1) or Hit(2)\n";
                            std::cin >> select;}
                            // if you unput select = 1, it'll take you out of the internal while loop, but it'll keep you
                            // in case 2. You'll then follow the instructions below, which involve determining the winner.
                    
                    }
                }

                // ends the hitting pocecss(out of inner while(select==2)) and begins the dealer turn and finally determines 
                // the winner of the game based off of the dealer and player hand totals
                std::cout << "Stand\n";
                
                //playerhand_total = 0; //resets players total hand value
                //dealerhand_total = 0;
                dealer_turn();
                playerhand_total=0;
                dealerhand_total=0;
                
                for(int i =0; i < playerhand.size(); i++){playerhand_total = playerhand_total + playerhand[i];}
                for(int i =0; i < dealerhand.size(); i++){dealerhand_total = dealerhand_total + dealerhand[i];}
                
                

                DetermineWinner(playerhand_total,dealerhand_total);
                
                break;
            
            case 3:

                // Here's our surrender option. If you select 3, your wager will be set to 0.5, and the 
                // game will restart. Note again that you're only allowed to surrender on the first deal.

                playerhand_total = 0;
                for(int i =0; i < playerhand.size(); i++){playerhand_total = playerhand_total + playerhand[i];}

                std::cout << "Surrender\n";
                wager = wager * 0.5;
            
                std::cout << "Considering that you're a coward, we've deprived you of half of your wager: " << wager; 
                std::cout << "\nAnd we have also restarted the game.";
    
                break;
            
            default: // default case which ensures you choose an option of either 1,2,3
                for(int i =0; i < playerhand.size(); i++)
                    playerhand_total = playerhand_total + playerhand[i];
                std::cout << "\nInvalid Input. Nice job, ass. You broke the rules. Pwease start over.\n";
        }

        // og plan was to carry over option number to all functions but we strayed from that idea 
        // would take alittle time to rework function as anything other than int function()
        return option;
} 



void dealer_turn() {

    dealerhand_total = 0; // Sets dealerhand = 0. Otherwise, the code will
    // remember the dealerhand_total from the previous hand and add to it.
    // If the dealer's hands on two runs are <0 5> and <6 10>, you end
    // getting dealerhand_total = 5 and then dealerhand_total = 21
    // instead of dealerhand_total = 5 and dealerhand_total = 16.

    int dealer_hitnumber = 0;

     for(int i = 0; i < dealerhand.size(); i++)
        dealerhand_total = dealerhand_total + dealerhand[i];
     // This dealerhand_total will be saved and mess up the dealerhand_total for an individual round
     // if we don't set it equal to 0 above.


     // we want the dealer AI to hit everytime the total is less 16. 
     while(dealerhand_total < 16 && option != 3){

         dealerhand_total = 0; // Again gotta reset dealerhand_total.

         
         // Establishes a counter for dealer_hitnumber
         dealer_hitnumber = dealer_hitnumber + 1;

         /* 
            The code below fills up the dealerhand vector.
            Here's an explanation of each term in brackets:

            4: Moves us to the 5th index of the vector so we don't redistribute
            previous numbers in the vector (analagous to redealing previous cards).

            player_hitnumber: moves us past the index where the player hit so we 
            avoid redrawing a card the player already drew
            
            dealer_hitnumber: this one's the actual index for the hand. Every time
            the dealer hits, dealer_hitnumber increments by 1 as set up above. That
            new dealer_hitnumber gets passed to our .push_back function.

            -1: Sets us back to the fourth index of the vector. I don't remember
            why we did this, honestly.
         */
        
         dealerhand.push_back(shuffled_cardvals[4 + player_hitnumber  + dealer_hitnumber - 1]); 

         for(int i =0; i < dealerhand.size(); i++)
            dealerhand_total = dealerhand_total + dealerhand[i];
         
     }   

}


// DETERMINE WINNER


void DetermineWinner(int playerhand_total, int dealerhand_total){

    // This part's pretty self-explanatory. In DetermineWinner(),
    // we take the player and dealer's hand totals (as well as total cards)
    // and compare them,determining the winner.

    // Due to a wide variety of possible end scenarios, this code got long.


if(playerhand_total <= 21 && dealerhand_total <= 21){

    if(dealerhand_total < playerhand_total) {
        std::cout << "\nPlayer hand total: " << playerhand_total;
        std::cout << "\nDealer hand total: " << dealerhand_total;
        std::cout << "\nCongrats; You've Won our brazy BlAcKjAcK Duel. Your payout is " << wager * 1.5;     
        std::cout << "\nWanna Play Again? y/n\n";
        std::cin >> input; }
    
    else if(dealerhand_total > playerhand_total) {
        std::cout << "\nPlayer hand total: " << playerhand_total;
        std::cout << "\nDealer hand total: " << dealerhand_total;
        std::cout << "\nDamn; you're kinda ass. Your payout is 0 dollars.";
        std::cout << "\nWanna Play Again? y/n\n";
        std::cin >> input; }
}



else if(playerhand_total == 21 and dealerhand_total == 21) {

        if(playerhand.size() > dealerhand.size()) {
            std::cout << "\nPlayer hand total: " << playerhand_total;
            std::cout << "\nNumber of cards player has: " << playerhand.size();
            std::cout << "\nDealer hand total: " << dealerhand_total;
            std::cout << "\nNumber of cards dealer has: " << dealerhand.size();
            std::cout << "\nur bad.";
            std::cout << " You lost all your money.";
            std::cout << "\nWanna Play Again? y/n\n";
            std::cin >> input; }

    

        else if(playerhand.size() < dealerhand.size()) {
            std::cout << "\nPlayer hand total: " << playerhand_total;
            std::cout << "\nNumber of cards player has: " << playerhand.size();
            std::cout << "\nDealer hand total: " << dealerhand_total;
            std::cout << "\nNumber of cards dealer has: " << dealerhand.size();
            std::cout << "\nCongrats; You've Won our brazy BlAcKjAcK Duel. Your payout is " << 1.5 * wager;
            std::cout << "\nWanna Play Again? y/n\n";
            std::cin >> input; }
        
        else {
            std::cout << "\nGood God. Dealer and Player got 21 with the same number ";
            std::cout << "of cards in their hand. You keep your wager: " << wager;
            input = 'n';
            
        }
}

else if(playerhand_total == dealerhand_total) { 
        std::cout << "\nPlayer hand total: " << playerhand_total;
        std::cout << "\nDealer hand total: " << dealerhand_total;    
        std::cout << "\nTie";
        std::cout << "\nKeep your wager:" << wager;
        std::cout << "\nWanna Play Again? y/n\n";
        std::cin >> input;}
         
else if(dealerhand_total > 21){
            std::cout << "\nPlayer hand total: " << playerhand_total;
            std::cout << "\nDealer hand total: " << dealerhand_total;
            std::cout << "\nDealer BUst u winm. Your payout is " << 1.5 * wager; 
            std::cout << "\nWanna Play Again? y/n\n";
            std::cin >> input;}


}


