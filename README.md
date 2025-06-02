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

**How it works:**<br />
    Each philosopher is a thread<br />
    They pick up two forks (mutexes) to eat<br />
    If they don’t eat in time, they die<br />
    Program uses pthread, mutex, and usleep<br />

**Rules:**<br />
    No deadlocks<br />
    No race conditions<br />
    Accurate timing<br />
