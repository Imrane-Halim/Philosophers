# 🍝 Philosophers - A Dining Philosophers Implementation 🤔

## 📚 Overview
This project is an implementation of the classic dining philosophers problem in C, exploring concurrent programming concepts including mutual exclusion, deadlock prevention, and thread synchronization.

## 🎯 The Challenge
The dining philosophers problem illustrates challenges in resource allocation and concurrent algorithm design:
- Multiple philosophers sit at a round table
- A large bowl of spaghetti sits in the middle
- Philosophers alternate between eating, thinking, and sleeping
- Each philosopher needs two forks to eat
- Forks are shared between adjacent philosophers
- The goal is to prevent philosophers from starving while avoiding deadlocks

## 🛠️ Technical Requirements
- Written in C
- No global variables
- Implements threading and mutex locks
- Handles race conditions
- Precise timing management
- Death detection within 10ms

## 🏃‍♂️ How to Run

### Compilation
```bash
make
```

### Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

`number_of_philosophers`: Number of philosophers at the table
`time_to_die`: Time in milliseconds until a philosopher dies without eating
`time_to_eat`: Time in milliseconds it takes to eat
`time_to_sleep`: Time in milliseconds philosophers spend sleeping
`number_of_times_each_philosopher_must_eat`: [Optional] Program stops when all philosophers eat this many times

### 🎮 Example Usage

```bash
./philo 5 800 200 200
./philo 4 410 200 200 5
```

### 🔍 Program Output
The program displays state changes in the following format:

- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`