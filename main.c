#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// Constants 
#define INITIAL_WALLET 1000
#define MIN_BET 10
#define MAX_BET 500
#define MAX_CARDS 52
#define NUM_SUITS 4
#define NUM_RANKS 13

// Structures
typedef struct {
    int value;
    char suit;    // Using H, D, C, S for Hearts, Diamonds, Clubs, Spades
    char rank;
} Card;

typedef struct {
    Card cards[5];
    int numCards;
} Hand;

// Function prototypes
void initializeDeck(Card deck[]);
void shuffleDeck(Card deck[]);
void displayCard(Card card);
void displayHand(Hand* hand);
int getBet(int wallet);
void clearInputBuffer();
bool playAgain();

// Menu functions
void displayMainMenu();
void displayGamesMenu();
int getMenuChoice(int min, int max);

// Game functions
void playNumberGuessingGame(int* wallet);
void playDiceGame(int* wallet);
void playCoinFlipGame(int* wallet);
void playBlackjack(int* wallet);
void playPoker(int* wallet);
void depositFunds(int* wallet);
void withdrawFunds(int* wallet);


// Utility functions
void initializeDeck(Card deck[]) {
    const char suits[] = {'H', 'D', 'C', 'S'};  // ASCII-safe suit characters
    const char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    int index = 0;
    
    for (int s = 0; s < NUM_SUITS; s++) {
        for (int r = 0; r < NUM_RANKS; r++) {
            deck[index].suit = suits[s];
            deck[index].rank = ranks[r];
            deck[index].value = (r >= 9) ? 10 : (r + 1);
            if (r == 0) deck[index].value = 11; // Ace
            index++;
        }
    }
}

void shuffleDeck(Card deck[]) {
    for (int i = MAX_CARDS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

const char* getSuitSymbol(char suit) {
    switch(suit) {
        case 'H': return "<3";  // Hearts
        case 'D': return "<>";  // Diamonds
        case 'C': return "{}";  // Clubs
        case 'S': return "^";   // Spades
        default: return "?";
    }
}

void displayCard(Card card) {
    printf("[%c%s] ", card.rank, getSuitSymbol(card.suit));
}

void displayHand(Hand* hand) {
    for (int i = 0; i < hand->numCards; i++) {
        displayCard(hand->cards[i]);
    }
    printf("\n");
}

int getBet(int wallet) {
    int bet;
    do {
        printf("Enter bet amount ($%d-$%d): $", MIN_BET, MAX_BET);
        if (scanf("%d", &bet) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            bet = 0;
            continue;
        }
        clearInputBuffer();
        
        if (bet < MIN_BET || bet > MAX_BET) {
            printf("Invalid bet. Please bet between $%d and $%d.\n", MIN_BET, MAX_BET);
        } else if (bet > wallet) {
            printf("Insufficient funds. Your wallet: $%d\n", wallet);
        }
    } while (bet < MIN_BET || bet > MAX_BET || bet > wallet);
    
    return bet;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

bool playAgain() {
    char choice;
    do {
        printf("Play again? (y/n): ");
        scanf(" %c", &choice);
        clearInputBuffer();
        choice = tolower(choice);
        if (choice != 'y' && choice != 'n') {
            printf("Please enter 'y' or 'n'.\n");
        }
    } while (choice != 'y' && choice != 'n');
    return choice == 'y';
}

// Menu implementations
void displayMainMenu() {
    printf("\n=== Casino Royal ===\n");
    printf("1. Play Games\n");
    printf("2. Check Wallet\n");
    printf("3. Deposit Funds\n");
    printf("4. Withdraw Funds\n");
    printf("5. Exit\n");
}

void displayGamesMenu() {
    printf("\n=== Games Menu ===\n");
    printf("1. Number Guessing\n");
    printf("2. Dice Game\n");
    printf("3. Coin Flip\n");
    printf("4. Blackjack\n");
    printf("5. Poker\n");
    printf("6. Return to Main Menu\n");
}

int getMenuChoice(int min, int max) {
    int choice;
    do {
        printf("Enter your choice (%d-%d): ", min, max);
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            choice = -1;
            continue;
        }
        clearInputBuffer();
        
        if (choice < min || choice > max) {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice < min || choice > max);
    
    return choice;
}

// Game implementations
void playNumberGuessingGame(int* wallet) {
    printf("\n=== Number Guessing Game ===\n");
    printf("Guess a number between 1-10. Win 9x your bet!\n");
    
    do {
        int bet = getBet(*wallet);
        int number = rand() % 10 + 1;
        int guess;
        bool validInput = false;
        
        do {
            printf("Enter your guess (1-10): ");
            if (scanf("%d", &guess) != 1) {
                clearInputBuffer();
                printf("Invalid input. Please enter a number.\n");
                continue;
            }
            clearInputBuffer();
            
            if (guess < 1 || guess > 10) {
                printf("Please enter a number between 1 and 10.\n");
            } else {
                validInput = true;
            }
        } while (!validInput);
        
        if (guess == number) {
            int winnings = bet * 9;
            printf("Congratulations! The number was %d!\n", number);
            printf("You won $%d!\n", winnings);
            *wallet += winnings;
        } else {
            printf("Sorry, the number was %d.\n", number);
            printf("You lost $%d.\n", bet);
            *wallet -= bet;
        }
        
        printf("Current wallet: $%d\n", *wallet);
    } while (*wallet >= MIN_BET && playAgain());
}

void playBlackjack(int* wallet) {
    printf("\n=== Blackjack ===\n");
    Card deck[MAX_CARDS];
    Hand playerHand = {0};
    Hand dealerHand = {0};
    
    do {
        int bet = getBet(*wallet);
        initializeDeck(deck);
        shuffleDeck(deck);
        
        // Initial deal
        playerHand.cards[0] = deck[0];
        dealerHand.cards[0] = deck[1];
        playerHand.cards[1] = deck[2];
        dealerHand.cards[1] = deck[3];
        playerHand.numCards = dealerHand.numCards = 2;
        
        int cardIndex = 4;
        int playerTotal = playerHand.cards[0].value + playerHand.cards[1].value;
        //great so you are reading all of this !?
        int dealerTotal = dealerHand.cards[0].value + dealerHand.cards[1].value;
        
        printf("Your hand: ");
        displayHand(&playerHand);
        printf("Dealer shows: ");
        displayCard(dealerHand.cards[0]);
        printf("[??]\n");
        
        // Player's turn
        while (playerTotal < 21) {
            char choice;
            do {
                printf("Hit (h) or Stand (s)? ");
                scanf(" %c", &choice);
                clearInputBuffer();
                choice = tolower(choice);
                
                if (choice != 'h' && choice != 's') {
                    printf("Please enter 'h' or 's'.\n");
                }
            } while (choice != 'h' && choice != 's');
            
            if (choice == 'h') {
                playerHand.cards[playerHand.numCards] = deck[cardIndex++];
                playerHand.numCards++;
                playerTotal += playerHand.cards[playerHand.numCards-1].value;
                printf("Your hand: ");
                displayHand(&playerHand);
            } else {
                break;
            }
        }
        
        // Dealer's turn
        printf("Dealer's hand: ");
        displayHand(&dealerHand);
        
        while (dealerTotal < 17) {
            dealerHand.cards[dealerHand.numCards] = deck[cardIndex++];
            dealerHand.numCards++;
            dealerTotal += dealerHand.cards[dealerHand.numCards-1].value;
        }
        
        printf("Final hands:\n");
        printf("Your hand: ");
        displayHand(&playerHand);
        printf("Dealer's hand: ");
        displayHand(&dealerHand);
        
        // Determine winner
        if (playerTotal > 21) {
            printf("Bust! You lose $%d\n", bet);
            *wallet -= bet;
        } else if (dealerTotal > 21) {
            printf("Dealer busts! You win $%d\n", bet);
            *wallet += bet;
        } else if (playerTotal > dealerTotal) {
            printf("You win $%d!\n", bet);
            *wallet += bet;
        } else if (dealerTotal > playerTotal) {
            printf("Dealer wins! You lose $%d\n", bet);
            *wallet -= bet;
        } else {
            printf("Push! Bet returned.\n");
        }
        
        printf("Current wallet: $%d\n", *wallet);
    } while (*wallet >= MIN_BET && playAgain());
}
// Add these implementations before the main function:

void playDiceGame(int* wallet) {
    printf("\n=== Dice Game ===\n");
    printf("Roll higher than 7 to win 1.5x your bet!\n");
    
    do {
        int bet = getBet(*wallet);
        printf("Rolling the dice...\n");
        
        int dice1 = (rand() % 6) + 1;
        int dice2 = (rand() % 6) + 1;
        int total = dice1 + dice2;
        
        printf("You rolled: %d + %d = %d\n", dice1, dice2, total);
        
        if (total > 7) {
            int winnings = (int)(bet * 1.5);
            printf("Congratulations! You win $%d!\n", winnings);
            *wallet += winnings;
        } else {
            printf("Sorry, you lose $%d.\n", bet);
            *wallet -= bet;
        }
        
        printf("Current wallet: $%d\n", *wallet);
    } while (*wallet >= MIN_BET && playAgain());
}

void playCoinFlipGame(int* wallet) {
    printf("\n=== Coin Flip ===\n");
    printf("Guess heads or tails to win 1.9x your bet!\n");
    
    do {
        int bet = getBet(*wallet);
        char guess;
        bool validGuess = false;
        
        do {
            printf("Enter your guess (h for heads, t for tails): ");
            scanf(" %c", &guess);
            clearInputBuffer();
            guess = tolower(guess);
            
            if (guess != 'h' && guess != 't') {
                printf("Invalid input. Please enter 'h' or 't'.\n");
            } else {
                validGuess = true;
            }
        } while (!validGuess);
        
        char result = (rand() % 2) == 0 ? 'h' : 't';
        printf("The coin shows: %s\n", result == 'h' ? "heads" : "tails");
        
        if (guess == result) {
            int winnings = (int)(bet * 1.9);
            printf("Congratulations! You win $%d!\n", winnings);
            *wallet += winnings;
        } else {
            printf("Sorry, you lose $%d.\n", bet);
            *wallet -= bet;
        }
        
        printf("Current wallet: $%d\n", *wallet);
    } while (*wallet >= MIN_BET && playAgain());
}

void playPoker(int* wallet) {
    printf("\n=== Simple Poker ===\n");
    printf("Get a better hand than the dealer to win!\n");
    
    Card deck[MAX_CARDS];
    Hand playerHand = {0};
    Hand dealerHand = {0};
    
    do {
        int bet = getBet(*wallet);
        initializeDeck(deck);
        shuffleDeck(deck);
        
        // Deal 5 cards to each player
        for (int i = 0; i < 5; i++) {
            playerHand.cards[i] = deck[i];
            dealerHand.cards[i] = deck[i + 5];
        }
        playerHand.numCards = dealerHand.numCards = 5;
        
        // Show hands
        printf("\nYour hand: ");
        displayHand(&playerHand);
        printf("Dealer's hand: ");
        displayHand(&dealerHand);
        
        // Simple winning condition based on highest card
        int playerHighest = 0;
        int dealerHighest = 0;
        
        for (int i = 0; i < 5; i++) {
            if (playerHand.cards[i].value > playerHighest) {
                playerHighest = playerHand.cards[i].value;
            }
            if (dealerHand.cards[i].value > dealerHighest) {
                dealerHighest = dealerHand.cards[i].value;
            }
        }
        
        printf("\nYour highest card: ");
        for (int i = 0; i < 5; i++) {
            if (playerHand.cards[i].value == playerHighest) {
                displayCard(playerHand.cards[i]);
                break;
            }
        }
        
        printf("\nDealer's highest card: ");
        for (int i = 0; i < 5; i++) {
            if (dealerHand.cards[i].value == dealerHighest) {
                displayCard(dealerHand.cards[i]);
                break;
            }
        }
        printf("\n");
        
        if (playerHighest > dealerHighest) {
            printf("You win! You get $%d!\n", bet * 2);
            *wallet += bet * 2;
        } else if (playerHighest < dealerHighest) {
            printf("Dealer wins! You lose $%d.\n", bet);
            *wallet -= bet;
        } else {
            printf("It's a tie! Your bet is returned.\n");
        }
        
        printf("Current wallet: $%d\n", *wallet);
    } while (*wallet >= MIN_BET && playAgain());
}

void depositFunds(int* wallet) {
    int amount;
    printf("\n=== Deposit Funds ===\n");
    printf("Enter amount to deposit: $");
    if (scanf("%d", &amount) != 1) {
        clearInputBuffer();
        printf("Invalid input.\n");
        return;
    }
    clearInputBuffer();
    if (amount <= 0) {
        printf("Invalid amount.\n");
    } else {
        *wallet += amount;
        printf("Successfully deposited $%d. New balance: $%d\n", amount, *wallet);
    }
}

void withdrawFunds(int* wallet) {
    int amount;
    printf("\n=== Withdraw Funds ===\n");
    printf("Current balance: $%d\n", *wallet);
    printf("Enter amount to withdraw: $");
    if (scanf("%d", &amount) != 1) {
        clearInputBuffer();
        printf("Invalid input.\n");
        return;
    }
    clearInputBuffer();
    if (amount <= 0 || amount > *wallet) {
        printf("Invalid amount or insufficient funds.\n");
    } else {
        *wallet -= amount;
        printf("Successfully withdrew $%d. New balance: $%d\n", amount, *wallet);
    }
}

// Main function
int main() {
    int wallet = INITIAL_WALLET;
    srand((unsigned int)time(NULL));
    bool running = true;
    
    printf("Welcome to Casino Royal!\n");
    printf("Starting wallet: $%d\n", wallet);
    
    while (running) {
        displayMainMenu();
        int choice = getMenuChoice(1, 5);
        
        switch (choice) {
            case 1: {
                int gameChoice;
                do {
                    displayGamesMenu();
                    gameChoice = getMenuChoice(1, 6);

                    
                    switch (gameChoice) {
                        case 1:
                            playNumberGuessingGame(&wallet);
                            break;
                        case 2:
                            playDiceGame(&wallet);
                            break;
                        case 3:
                            playCoinFlipGame(&wallet);
                            break;
                        case 4:
                            playBlackjack(&wallet);
                            break;
                        case 5:
                            playPoker(&wallet);
                            break;
                        case 6:
                            break;
                    }
                } while (gameChoice != 6 && wallet >= MIN_BET);


                
                if (wallet < MIN_BET) {
                    printf("Insufficient funds to continue playing.\n");
                    printf("Please deposit more money to continue.\n");
                }
                break;
            }
            case 2:
                printf("Current wallet balance: $%d\n", wallet);
                break;
            case 3:
                depositFunds(&wallet);
                break;
            case 4:
                withdrawFunds(&wallet);
                break;

            case 5:
                printf("Thanks for playing! Final balance: $%d\n", wallet);
                running = false;
                break;
        }
    }
    
    return 0;
}