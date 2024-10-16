#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define INITIAL_WALLET 1000
#define NUM_GAMES 5

// Function prototypes
void displayMainMenu();
void displayGamesMenu();
int getCardValue();
void playNumberGuessingGame(int *wallet);
void playDiceGame(int *wallet);
void playCoinFlipGame(int *wallet);
void playBlackjack(int *wallet);
void playPoker(int *wallet);
void clearInputBuffer();
//Main menu
void displayMainMenu() {
    printf("\n--- Gambling Game Main Menu ---\n");
    printf("1. Play Games\n");
    printf("2. Check Wallet\n");
    printf("3. Deposit (Not implemented)\n");
    printf("4. Withdraw (Not implemented)\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}
//Game Menu
void displayGamesMenu() {
    printf("\n--- Games Menu ---\n");
    printf("1. Number Guessing\n");
    printf("2. Dice Game\n");
    printf("3. Coin Flip\n");
    printf("4. Blackjack\n");
    printf("5. Poker (Simplified)\n");
    printf("6. Back to Main Menu\n");
    printf("Enter your choice: ");
}
//card value
int getCardValue() {
    int card = rand() % 13 + 1;
    return (card > 10) ? 10 : card;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
//Number Guessing
void playNumberGuessingGame(int *wallet) {
    int bet, number, guess;
    printf("Enter your bet amount: ");
    scanf("%d", &bet);

    if (bet > *wallet) {
        printf("You don't have enough money to place this bet. Your current balance is %d.\n", *wallet);
        return;
    }

    number = rand() % 10 + 1;
    printf("Guess a number between 1 and 10: ");
    scanf("%d", &guess);

    if (guess == number) {
        printf("Congratulations! You guessed the right number. You win %d!\n", bet * 9);
        *wallet += bet * 9;
    } else {
        printf("Sorry, the correct number was %d. You lose your bet of %d.\n", number, bet);
        *wallet -= bet;
    }
}
//Dice Roll
void playDiceGame(int *wallet) {
    int bet, dice1, dice2;
    printf("Enter your bet amount: ");
    scanf("%d", &bet);

    if (bet > *wallet) {
        printf("You don't have enough money to place this bet. Your current balance is %d.\n", *wallet);
        return;
    }

    dice1 = rand() % 6 + 1;
    dice2 = rand() % 6 + 1;
    printf("You rolled a %d and a %d.\n", dice1, dice2);

    if (dice1 + dice2 > 7) {
        printf("You win! You get %f.\n", bet * 1.5);
        *wallet += bet * 1.5;
    } else {
        printf("You lose! You lose your bet of %d.\n", bet);
        *wallet -= bet;
    }
}
//coin Flip
void playCoinFlipGame(int *wallet) {
    int bet;
    char guess, result;
    printf("Enter your bet amount: ");
    scanf("%d", &bet);

    if (bet > *wallet) {
        printf("You don't have enough money to place this bet. Your current balance is %d.\n", *wallet);
        return;
    }

    printf("Guess the coin flip result (h for heads, t for tails): ");
    scanf(" %c", &guess);
    guess = tolower(guess);

    result = (rand() % 2 == 0) ? 'h' : 't';
    printf("The coin flip result is %c.\n", result);

    if (guess == result) {
        printf("Congratulations! You guessed right. You win %f!\n", bet * 1.9);
        *wallet += bet * 1.9;
    } else {
        printf("Sorry, you guessed wrong. You lose your bet of %d.\n", bet);
        *wallet -= bet;
    }
}
//blackjack
void playBlackjack(int *wallet) {
    int bet, playerTotal = 0, dealerTotal = 0;
    char choice;
    printf("Enter your bet amount: ");
    scanf("%d", &bet);

    if (bet > *wallet) {
        printf("You don't have enough money to place this bet. Your current balance is %d.\n", *wallet);
        return;
    }

    playerTotal = getCardValue() + getCardValue();
    dealerTotal = getCardValue() + getCardValue();

    printf("Your total is %d.\n", playerTotal);
    printf("The dealer has a %d showing.\n", dealerTotal - getCardValue());


    while (playerTotal < 21) {
        printf("Do you want to hit or stand? (h/s): ");
        scanf(" %c", &choice);
        choice = tolower(choice);

        if (choice == 'h') {
            playerTotal += getCardValue();
            printf("Your new total is %d.\n", playerTotal);
        } else if (choice == 's') {
            break;
        } else {
           printf("Invalid choice. Please enter 'h' or 's'.\n");
        }
    }

    while (dealerTotal < 17) {
        dealerTotal += getCardValue();
    }

    printf("Dealer's total is %d.\n", dealerTotal);

    if (playerTotal > 21) {
        printf("You bust! You lose your bet of %d.\n", bet);
        *wallet -= bet;
    } else if (dealerTotal > 21 || playerTotal > dealerTotal) {
        printf("You win! You get %d.\n", bet * 2);
        *wallet += bet * 2;
    } else if (playerTotal == dealerTotal){
        printf("It's a push! You get your bet back.\n");
    } else {
        printf("You lose! You lose your bet of %d.\n", bet);
        *wallet -= bet;
    }
}


void playPoker(int *wallet) {
    int bet;
    printf("Enter your bet amount: ");
    scanf("%d", &bet);

    if (bet > *wallet) {
        printf("You don't have enough money to place this bet. Your current balance is %d.\n", *wallet);
        return;
    }

    int playerHand = rand() % 10 + 1;
    int dealerHand = rand() % 10 + 1;

    printf("Your hand is %d. Dealer's hand is %d.\n", playerHand, dealerHand);

    if (playerHand > dealerHand) {
        printf("You win! You get %d.\n", bet * 2);
        *wallet += bet * 2;
    } else {
        printf("You lose! You lose your bet of %d.\n", bet);
        *wallet -= bet;
    }
}


int main() {
    int wallet = INITIAL_WALLET;
    srand(time(0));
    int running = 1;
    int choice;


    while (running) {
        displayMainMenu();
        scanf("%d", &choice);
        clearInputBuffer();  // Very important to clear the buffer here

        switch (choice) {
            case 1: { // Play Games
                int gameChoice;
                do {
                    displayGamesMenu();
                    scanf("%d", &gameChoice);
                    clearInputBuffer();


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
                        default:
                            printf("Invalid game choice.\n");
                    }
                } while (gameChoice != 6);
                break;
            }
            case 2:
                printf("Wallet balance: %d\n", wallet);
                break;
            case 3:
                printf("Deposit functionality is not implemented yet.\n");
                break;
            case 4:
                printf("Withdraw functionality is not implemented yet.\n");
                break;
            case 5:
                running = 0;
                break;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}