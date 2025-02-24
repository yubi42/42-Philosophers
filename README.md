# Philosophers

## Introduction
Philosophers is a **42 School project** that explores the **dining philosophers problem**, a classic concurrency problem. The goal is to manage multiple philosophers who alternate between eating, thinking, and sleeping while avoiding deadlocks and race conditions.

## Features
- Implementation of the **dining philosophers problem**
- Multithreading using **pthread**
- Mutex-based synchronization to prevent race conditions
- Handling of starvation and death conditions
- Efficient resource management

## Rules
- There are `N` philosophers sitting around a circular table with `N` forks.
- A philosopher can **eat** only if they hold both the left and right fork.
- Philosophers alternate between **eating, sleeping, and thinking**.
- If a philosopher does not eat within a specified time, they **die**.

## Installation

### Prerequisites
- **gcc** (GNU Compiler Collection)
- **Make**
- **pthread** library (included in most Unix-based systems)

### Build
```sh
# Clone the repository
git clone https://github.com/yubi42/philosophers.git
cd philosophers

# Compile the program
make
```

### Run
```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

### Example
```sh
./philo 5 800 200 200
```
This runs a simulation with **5 philosophers**, where:
- Each philosopher dies if they don’t eat within **800ms**
- Each meal takes **200ms**
- Sleeping lasts **200ms**

## Contributors
- [jess](https://github.com/yubi42)


