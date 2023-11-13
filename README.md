# Spell Masters Game

## Introduction
Spell Masters is an interactive word-based game where players compete against a bot in a challenging spell duel. The game leverages a Minimax algorithm with Alpha-Beta pruning to create a smart and strategic gameplay experience. 

## Features
- Player vs. Bot gameplay.
- Intelligent bot powered by Minimax algorithm and Alpha-Beta pruning for optimal performance.
- Wide variety of words to choose from.
- Terminal-based UI for easy interaction.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
- C compiler (e.g., GCC)
- Basic knowledge of terminal commands

### Installing
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Spell_Masters.git 

to run program:

gcc -c main.c -o main.o
gcc -c utilities.c -o utilities.o
gcc -c pvp.c -o pvp.o
gcc -c pvb.c -o pvb.o
gcc -c botLogic.c -o botLogic.o
gcc main.o utilities.o pvp.o pvb.o botLogic.o -o spell_master
./spell_master
