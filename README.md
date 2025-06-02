# Philosophers (Philo) – 42 Project
About:<br />
This project is a simulation of the Dining Philosophers Problem using threads in C. The goal is to manage multiple philosophers who eat, sleep, and think without creating deadlocks or race conditions.
<br/><br/>

**Compile:**

    make

**Run:**

    ./philo 5 800 200 200 6

**Example:**<br />
    5 = number of philosophers<br />
    800 = time to die (ms)<br />
    200 = time to eat (ms)<br />
    200 = time to sleep (ms)<br />
    6 = how many times each philo must eat (optional)
<br/><br/>

**How it works:**
    Each philosopher is a thread
    They pick up two forks (mutexes) to eat
    If they don’t eat in time, they die
    Program uses pthread, mutex, and usleep

**Rules:**
    No deadlocks
    No race conditions
    Accurate timing
