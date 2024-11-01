# 🎰 The Sting - A Casino Crime

<div align="center">

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.cppreference.com/w/c/language)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey.svg)](https://github.com/Satya-Siba-Nayak/The-Sting-crime)

A sophisticated command-line casino gaming system implemented in C, featuring multiple classic casino games. Experience the thrill of gambling without the risk!

[Features](#features) • [Games](#available-games) • [Installation](#installation) • [Usage](#usage) • [Contributing](#contributing)

</div>

## 📋 Table of Contents

- [Features](#features)
- [Available Games](#available-games)
- [Installation](#installation)
- [Usage](#usage)
- [Game Rules](#game-rules)
- [Contributing](#contributing)
- [License](#license)
- [Disclaimer](#disclaimer)

## ✨ Features

### Core Features
- 🎮 5 Classic Casino Games:
  - Number Guessing
  - Dice Game
  - Coin Flip
  - Blackjack
  - Poker
- 💰 Virtual Wallet System ($1,000 starting balance)
- 🎲 Realistic card deck implementation
- 📊 Real-time balance tracking
- ⚡ User-friendly command-line interface
- 🛡️ Robust input validation

### Betting System
- 💵 Initial Wallet: $1,000
- 📊 Minimum Bet: $10
- 💫 Maximum Bet: $500
- 📈 Real-time balance updates

## 🎮 Available Games

### 1. Number Guessing
- Guess a number between 1-10
- Win 9x your bet amount
- Perfect for beginners!

### 2. Dice Game
- Roll higher than 7 to win
- 1.5x payout on wins
- Based on classic craps

### 3. Coin Flip
- Choose heads or tails
- 1.9x payout on correct guess
- Simple yet exciting!

### 4. Blackjack
- Classic casino card game
- Beat the dealer without going over 21
- Full ASCII card display

### 5. Poker
- 5-card poker implementation
- Highest card wins
- Double your money on wins

## 📦 Installation

1. Clone the repository:
```bash
git clone https://github.com/Satya-Siba-Nayak/The-Sting-crime.git
cd The-Sting-crime
```

2. Compile the program:
```bash
# Using GCC
gcc -o casino main.c -Wall -Wextra

# Using Visual Studio Command Line
cl /W4 main.c /Fe:casino.exe
```

3. Run the program:
```bash
# Linux/macOS
./casino

# Windows
casino.exe
```

## 🎮 Usage

### Main Menu
```
=== Casino Royal ===
1. Play Games
2. Check Wallet
3. Deposit Funds
4. Withdraw Funds
5. Exit
```

### Game Selection
```
=== Games Menu ===
1. Number Guessing
2. Dice Game
3. Coin Flip
4. Blackjack
5. Poker
6. Return to Main Menu
```

## 🎲 Game Rules

### Blackjack
- Aim to get closer to 21 than the dealer
- Aces = 11 or 1
- Face cards = 10
- Number cards = Face value
- Dealer must hit on 16 and below

### Poker
- 5 cards dealt to each player
- Highest card wins
- Double your bet on winning
- Suits: Hearts (H), Diamonds (D), Clubs (C), Spades (S)

## 👥 Contributing

Feel free to contribute to this project:
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## ⚠️ Disclaimer

This software is for entertainment purposes only. No real commit spam money gambling is involved or should be used with this program.

---

<div align="center">
Created with ❤️ by <a href="https://github.com/Satya-Siba-Nayak">Satya Siba Nayak</a>

⭐ Star this repository if you find it helpful!
</div>