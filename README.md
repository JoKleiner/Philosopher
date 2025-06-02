Philosophers (Philo) – 42 Project
About:
This project is a simulation of the Dining Philosophers Problem using threads in C. The goal is to manage multiple philosophers who eat, sleep, and think without creating deadlocks or race conditions.

Compile:
make

Run:
./philo <number_of_philosophers> <time_to_die time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

Example:
./philo 5 800 200 200
    5 = number of philosophers
    800 = time to die (ms)
    200 = time to eat (ms)
    200 = time to sleep (ms)

Optional last argument: how many times each philo must eat

How It Works:
    Each philosopher is a thread
    They pick up two forks (mutexes) to eat
    If they don’t eat in time, they die
    Program uses pthread, mutex, and usleep

Rules:
    No deadlocks
    No race conditions
    Accurate timing
