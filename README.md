# 🎰 Casino Royal

<div align="center">

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.cppreference.com/w/c/language)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey.svg)](https://github.com/yourusername/casino-royal)

A sophisticated command-line casino gaming system implemented in C, featuring multiple classic casino games with realistic odds, comprehensive betting mechanics, and an intuitive user interface.

[Features](#features) • [Games](#available-games) • [Installation](#installation) • [Usage](#usage) • [Architecture](#architecture) • [Contributing](#contributing)

</div>

## 📋 Table of Contents

- [Features](#features)
- [Available Games](#available-games)
- [Technical Requirements](#technical-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Game Rules](#game-rules)
- [Architecture](#architecture)
- [Development](#development)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)
- [Disclaimer](#disclaimer)

## ✨ Features

### Core Features
- 🎮 Multiple classic casino games in one application
- 💰 Comprehensive wallet management system
- 🎲 Realistic card deck implementation with shuffling
- 📊 Real-time balance tracking
- ⚡ Fast and responsive command-line interface
- 🛡️ Input validation and error handling
- 🔄 Continuous game flow with play-again options

### Wallet System
- 💵 Starting balance: $1,000
- 📊 Betting range: $10 - $500
- 📈 Real-time balance updates
- 🏦 (Coming soon: Deposit/withdrawal system)

### Technical Features
- 🔧 Modular code architecture
- 🎴 Advanced card game mechanics
- 🎲 True random number generation
- 📝 Comprehensive input validation
- 🔍 Memory-efficient design
- 🛠️ Easy to extend and modify

## 🎮 Available Games

### 1. Number Guessing
```
=== Number Guessing Game ===
Guess a number between 1-10. Win 9x your bet!
Enter bet amount ($10-$500): $100
Enter your guess (1-10): 7
```
- **Odds**: 1 in 10
- **Payout**: 9x bet amount
- **Strategy**: Pure luck-based game

### 2. Dice Game
```
=== Dice Game ===
Roll higher than 7 to win 1.5x your bet!
Rolling the dice...
You rolled: 4 + 5 = 9
Congratulations! You win $150!
```
- **Odds**: 41.67% chance to win
- **Payout**: 1.5x bet amount
- **Strategy**: Statistical probability game

### 3. Coin Flip
```
=== Coin Flip ===
Guess heads or tails to win 1.9x your bet!
Enter your guess (h for heads, t for tails): h
The coin shows: heads
Congratulations! You win $190!
```
- **Odds**: 50% chance
- **Payout**: 1.9x bet amount
- **Strategy**: Simple probability game

### 4. Blackjack
```
=== Blackjack ===
Your hand: [A♥] [J♣]
Dealer shows: [7♠] [??]
Hit (h) or Stand (s)?
```
- **Features**:
  - Full deck implementation
  - ASCII card display
  - Hit/Stand options
  - Dealer AI
- **Rules**:
  - Beat the dealer's hand without going over 21
  - Aces worth 1 or 11
  - Face cards worth 10
  - Dealer must hit on 16 and below
- **Payout**: 1:1 on wins

### 5. Simple Poker
```
=== Simple Poker ===
Your hand: [K♠] [Q♥] [J♦] [10♣] [9♠]
Dealer's hand: [K♣] [Q♦] [J♥] [8♠] [7♣]
```
- **Features**:
  - 5-card poker
  - Full deck visualization
  - Hand comparison system
- **Payout**: 2x bet amount on win

## 🔧 Technical Requirements

### System Requirements
- Operating System:
  - Linux (Any modern distribution)
  - Windows 7 or higher
  - macOS 10.12 or higher
- Memory: Minimum 1MB RAM
- Disk Space: 1MB free space

### Development Requirements
- C Compiler (one of the following):
  ```bash
  # GCC (Linux/macOS)
  gcc --version  # Required: 4.8.1 or higher

  # Microsoft Visual C++ (Windows)
  cl.exe /?     # Visual Studio 2015 or higher

  # Clang
  clang --version  # 3.3 or higher
  ```
- Required Libraries:
  ```c
  #include <stdio.h>    // Standard I/O operations
  #include <stdlib.h>   // Standard library functions
  #include <time.h>     // Time operations for RNG
  #include <ctype.h>    // Character type functions
  #include <stdbool.h>  // Boolean type
  #include <string.h>   // String operations
  ```

## 📦 Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/casino-royal.git
cd casino-royal
```

2. Compile the program:
```bash
# Using GCC
gcc -o casino_royal main.c -Wall -Wextra

# Using Clang
clang -o casino_royal main.c -Wall -Wextra

# Using Visual Studio Command Line
cl /W4 main.c /Fe:casino_royal.exe
```

3. Run the program:
```bash
# Linux/macOS
./casino_royal

# Windows
casino_royal.exe
```

## 🎮 Usage

### Main Menu Navigation
```
=== Casino Royal ===
1. Play Games
2. Check Wallet
3. Deposit Funds
4. Withdraw Funds
5. Exit
```

### Games Menu
```
=== Games Menu ===
1. Number Guessing
2. Dice Game
3. Coin Flip
4. Blackjack
5. Poker
6. Return to Main Menu
```

### Basic Commands
- Enter numerical choices for menu selection
- Use 'y' or 'n' for yes/no prompts
- Use 'h' or 's' for hit/stand in Blackjack
- Press Ctrl+C to exit at any time

## 🏗️ Architecture

### Component Structure
```
casino_royal/
├── main.c             # Main program file
├── structures/        # Data structures
│   ├── Card.h        # Card structure
│   └── Hand.h        # Hand structure
├── games/            # Game implementations
├── utils/            # Utility functions
└── tests/            # Test files
```

### Key Components

#### Card Structure
```c
typedef struct {
    int value;        // Numerical value
    char suit;        // H, D, C, S
    char rank;        // A, 2-10, J, Q, K
} Card;
```

#### Hand Structure
```c
typedef struct {
    Card cards[5];    // Array of cards
    int numCards;     // Current number of cards
} Hand;
```

### Memory Management
- Static array allocation for cards
- No dynamic memory allocation
- Efficient memory usage
- Zero memory leaks

## 🛠️ Development

### Code Style Guide
- Indentation: 4 spaces
- Function names: camelCase
- Constants: UPPER_CASE
- Variables: camelCase
- Comprehensive comments
- Clear function documentation

### Adding New Games
1. Create game function:
```c
void playNewGame(int* wallet) {
    printf("\n=== New Game ===\n");
    // Game implementation
}
```

2. Update games menu
3. Add function prototype
4. Implement game logic
5. Add test cases

## 🧪 Testing

### Manual Testing
```bash
# Compile with debug flags
gcc -o casino_royal main.c -DDEBUG -Wall -Wextra

# Run with test mode
./casino_royal --test
```

### Test Cases
- Input validation
- Boundary conditions
- Game logic verification
- Memory usage monitoring
- Error handling

## 👥 Contributing

### Getting Started
1. Fork the repository
2. Create feature branch
3. Commit changes
4. Push to branch
5. Open pull request

### Contribution Guidelines
- Follow existing code style
- Add unit tests
- Update documentation
- Test thoroughly
- Keep PRs focused

### Development Process
1. Choose an issue to work on
2. Discuss approach in issue
3. Implement solution
4. Add tests
5. Submit PR

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## ⚠️ Disclaimer

This software is:
- For entertainment purposes only
- Not for real money gambling
- A simulation/educational tool
- Not affiliated with any real casino
- Not to be used by minors

## 🤝 Support

- Report bugs via Issues
- Request features via Discussions
- Email: support@example.com

---

<div align="center">
Made with ❤️ by [Satya siba Nayak]

Star ⭐ this repository if you find it helpful!
</div>