# **Philosophers**
The Philosopher Dining Simulation project is a challenge within the 42 School curriculum aimed at deepening students' understanding of concurrency, synchronization, and resource management in C. The goal is to simulate the classic "Dining Philosophers" problem, where philosophers alternately think and eat, sharing a limited number of forks.

## **Task**
The task was to implement a program that simulates the dining philosophers problem. The program needs to handle various tasks such as:

- Creating and managing multiple philosopher threads.
- Ensuring that philosophers can only eat when they have both left and right forks.
- Preventing deadlocks and ensuring that all philosophers get a chance to eat.
- Handling synchronization using mutexes to protect shared resources.

**Key objectives included:**

- Implementing a program that simulates philosophers sitting at a table, each needing two forks to eat.
- Ensuring the program correctly handles edge cases, such as starvation and deadlocks.
- Demonstrating a deep understanding of thread management, mutexes, and condition variables.

## **Key Achievements**

- Successful Thread Management: Implemented a robust solution that handles the creation and management of philosopher threads, ensuring proper execution and termination.
- Efficient Synchronization: Developed a reliable mechanism using mutexes to manage access to shared forks, preventing race conditions and deadlocks.
- Comprehensive Error Handling: Integrated extensive error checking and handling to manage edge cases and unexpected scenarios, ensuring the program operates reliably in various conditions.

## **Installation**

To install the project, follow these steps:

1. Clone the repository: git clone **`git@github.com:jakobsitory/03_philosophers_42CC.git`**
2. Navigate to the project directory: **`cd 03_philosophers_42CC`**
3. Build the project: **`make`**

## **Usage**
The philosopher program should be executed as follows:
```bash
./philosopher number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
For example:
```bash
./philosopher 5 800 200 200
```
_This command starts the simulation with 5 philosophers, where each philosopher has 800ms to live without eating, takes 200ms to eat, and 200ms to sleep._
