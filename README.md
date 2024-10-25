# Casino Royal 🎰

A text-based casino gaming system implemented in C, featuring multiple classic casino games with a simple betting interface and wallet management system.

## Features

- 🎮 Multiple Casino Games:
  - Number Guessing (1-10)
  - Dice Rolling
  - Coin Flip
  - Blackjack
  - Simple Poker

- 💰 Wallet System:
  - Starting balance: $1,000
  - Minimum bet: $10
  - Maximum bet: $500
  - Real-time balance tracking
  - (Coming soon: Deposit and withdrawal functionality)

- 🎲 Game Features:
  - Full deck of cards implementation
  - ASCII-based card display
  - Shuffling mechanism
  - Basic betting system
  - Win/loss tracking

## Game Rules

### Number Guessing
- Guess a number between 1-10
- Win 9x your bet for correct guesses

### Dice Game
- Roll two dice
- Win 1.5x your bet if total is higher than 7

### Coin Flip
- Choose heads or tails
- Win 1.9x your bet for correct guesses

### Blackjack
- Classic blackjack rules
- Player vs Dealer
- Hit or Stand options
- Dealer must hit on 16 and below

### Simple Poker
- 5-card poker
- Highest card wins
- Double your bet on winning

## Technical Details

### Prerequisites
- C compiler (GCC recommended)
- Standard C libraries:
  - stdio.h
  - stdlib.h
  - time.h
  - ctype.h
  - stdbool.h
  - string.h

### Compilation
```bash
gcc -o casino_royal main.c
```

### Running the Program
```bash
./casino_royal
```

## Code Structure

- Card and Hand structures for card games
- Modular design with separate functions for each game
- Menu-driven interface
- Input validation and error handling
- Clean user interface with ASCII graphics

## Future Enhancements

- [ ] Implement deposit and withdrawal system
- [ ] Add more sophisticated poker hand evaluations
- [ ] Implement split and double down in Blackjack
- [ ] Add multiplayer support
- [ ] Include game statistics and history
- [ ] Add more casino games (Roulette, Slots, etc.)

## Contributing

Feel free to contribute to this project by:
1. Forking the repository
2. Creating your feature branch
3. Committing your changes
4. Pushing to the branch
5. Opening a Pull Request

## License

This project is available under the MIT License. Feel free to use, modify, and distribute as you see fit.

## Disclaimer

This is a simulation game for entertainment purposes only. No real money is involved or should be used with this program.