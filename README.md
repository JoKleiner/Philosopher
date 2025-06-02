# Philosophers (Philo) – 42 Project
**About:**<br />
This project simulates the Dining Philosophers Problem using threads and mutexes in C.<br />
Philosophers sit around a table. Each needs two forks to eat. They take forks, eat, sleep, then think, and repeat. The challenge is to make sure they don’t all try to use the same forks at once (race conditions) or get stuck waiting forever (deadlocks).<br />
We use threads and mutexes to manage this safely.
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
