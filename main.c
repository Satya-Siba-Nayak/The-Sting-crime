#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

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
    char suit;
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

// Utility functions
void initializeDeck(Card deck[]) {
    char suits[] = {'♥', '♦', '♣', '♠'};
    char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
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

void displayCard(Card card) {
    printf("[%c%c]", card.rank, card.suit);
}

void displayHand(Hand* hand) {
    for (int i = 0; i < hand->numCards; i++) {
        displayCard(hand->cards[i]);
        printf(" ");
    }
    printf("\n");
}

int getBet(int wallet) {
    int bet;
    do {
        printf("Enter bet amount ($%d-$%d): $", MIN_BET, MAX_BET);
        scanf("%d", &bet);
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
    printf("Play again? (y/n): ");
    scanf(" %c", &choice);
    clearInputBuffer();
    return tolower(choice) == 'y';
}

// Menu implementations
void displayMainMenu() {
    printf("\n=== 🎰 Casino Royal ===\n");
    printf("1. Play Games\n");
    printf("2. Check Wallet\n");
    printf("3. Deposit Funds\n");
    printf("4. Withdraw Funds\n");
    printf("5. Exit\n");
}

void displayGamesMenu() {
    printf("\n=== 🎲 Games Menu ===\n");
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
        scanf("%d", &choice);
        clearInputBuffer();
        
        if (choice < min || choice > max) {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice < min || choice > max);
    
    return choice;
}

// Game implementations
void playNumberGuessingGame(int* wallet) {
    printf("\n=== 🔢 Number Guessing Game ===\n");
    printf("Guess a number between 1-10. Win 9x your bet!\n");
    
    do {
        int bet = getBet(*wallet);
        int number = rand() % 10 + 1;
        int guess;
        
        printf("Enter your guess (1-10): ");
        scanf("%d", &guess);
        clearInputBuffer();
        
        if (guess == number) {
            int winnings = bet * 9;
            printf("🎉 Congratulations! The number was %d!\n", number);
            printf("You won $%d!\n", winnings);
            *wallet += winnings;
        } else {
            printf("❌ Sorry, the number was %d.\n", number);
            printf("You lost $%d.\n", bet);
            *wallet -= bet;
        }
        
        printf("Current wallet: $%d\n", *wallet);
    } while (*wallet >= MIN_BET && playAgain());
}

void playBlackjack(int* wallet) {
    printf("\n=== ♠️ Blackjack ===\n");
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
        int dealerTotal = dealerHand.cards[0].value + dealerHand.cards[1].value;
        
        printf("Your hand: ");
        displayHand(&playerHand);
        printf("Dealer shows: [%c%c] [??]\n", 
               dealerHand.cards[0].rank, dealerHand.cards[0].suit);
        
        // Player's turn
        while (playerTotal < 21) {
            char choice;
            printf("Hit (h) or Stand (s)? ");
            scanf(" %c", &choice);
            clearInputBuffer();
            
            if (tolower(choice) == 'h') {
                playerHand.cards[playerHand.numCards] = deck[cardIndex++];
                playerHand.numCards++;
                playerTotal += playerHand.cards[playerHand.numCards-1].value;
                printf("Your hand: ");
                displayHand(&playerHand);
            } else if (tolower(choice) == 's') {
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

// Main function
int main() {
    int wallet = INITIAL_WALLET;
    srand(time(0));
    bool running = true;
    
    printf("Welcome to Casino Royal! 🎰\n");
    printf("Starting wallet: $%d\n", wallet);
    
    while (running) {
        displayMainMenu();
        int choice = getMenuChoice(1, 5);
        
        switch (choice) {
            case 1: {
                do {
                    displayGamesMenu();
                    int gameChoice = getMenuChoice(1, 6);
                    
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
                } while (choice != 6 && wallet >= MIN_BET);
                
                if (wallet < MIN_BET) {
                    printf("❌ Insufficient funds to continue playing.\n");
                    printf("Please deposit more money to continue.\n");
                }
                break;
            }
            case 2:
                printf("💰 Current wallet balance: $%d\n", wallet);
                break;
            case 3:
                printf("Deposit functionality coming soon!\n");
                break;
            case 4:
                printf("Withdraw functionality coming soon!\n");
                break;
            case 5:
                printf("Thanks for playing! Final balance: $%d\n", wallet);
                running = false;
                break;
        }
    }
    
    return 0;
}