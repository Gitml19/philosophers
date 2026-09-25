*This project has been created as part of the 42 curriculum by makoon.*

# Philosophers

## Description

The **Philosophers** project is part of the 42 curriculum and introduces the fundamentals of concurrent programming in C.

The project is based on the classic **Dining Philosophers Problem**. Several philosophers sit around a table and alternate between three states:

- Thinking
- Eating
- Sleeping

Each philosopher needs two forks to eat. Since forks are shared between neighboring philosophers, the program must carefully manage concurrent access to shared resources.

The main objectives of this project are to understand:

- Threads and concurrency
- Mutexes
- Race conditions
- Synchronization
- Deadlock prevention
- Shared resources
- Precise time management

The mandatory part uses one thread per philosopher and one mutex per fork, as required by the subject.

---

## How It Works

Each philosopher is represented by a separate thread.

The philosophers are placed around a circular table.

To eat, a philosopher must acquire both forks next to them.

Once both forks have been acquired, the philosopher:

- Takes the first fork.
- Takes the second fork.
- Eats for time_to_eat milliseconds.
- Releases both forks.
- Sleeps for time_to_sleep milliseconds.
- Starts thinking again.

If a philosopher does not start eating within time_to_die milliseconds after their last meal, they die and the simulation stops.

### Threads and Mutexes

Each philosopher runs in its own thread.

Forks are shared resources, so each fork is protected by a mutex. This prevents two philosophers from accessing the same fork simultaneously.

The program also uses mutexes to protect shared simulation state and console output.

A dedicated monitor thread continuously checks the philosophers' states and detects when a philosopher has died or when the simulation can stop because all philosophers have eaten enough times.


### Time Management

The simulation uses gettimeofday() to obtain the current time in milliseconds.
```
long get_time(void);
```
A custom precise_sleep() function is also used instead of relying exclusively on usleep(). It repeatedly checks the elapsed time in order to obtain more precise delays.

Each log message contains:

timestamp philosopher_id message

For example:
```
0 1 is thinking
1 1 has taken a fork
1 1 has taken a fork
1 1 is eating
201 1 is sleeping
301 1 is thinking
```
### Simulation Monitoring

A dedicated monitoring thread checks each philosopher periodically.

It verifies whether:

A philosopher has exceeded time_to_die.
The simulation has already been stopped.
All philosophers have reached the required number of meals.

When a philosopher dies, the monitor prints the death message and signals the end of the simulation.

If the optional meal limit is provided, the simulation can also stop once every philosopher has eaten enough times.

---

## Instructions

### Compilation

The project is compiled using the provided Makefile.

Build the program with:
```bash
make
```

Clean object files:
```bash
make clean
```

Remove object files and the executable:
```bash
make fclean
```

Recompile the project from scratch:
```bash
make re
```

The project must be compiled with:
```
-Wall -Wextra -Werror
```

### Usage

Run the program with:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
```

An optional fifth argument specifies how many times each philosopher must eat:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat
```
| Argument                                    | Description                                                               |
| ------------------------------------------- | ------------------------------------------------------------------------- |
| `number_of_philosophers`                    | Number of philosophers and forks                                          |
| `time_to_die`                               | Maximum time in milliseconds a philosopher can go without starting a meal |
| `time_to_eat`                               | Time spent eating in milliseconds                                         |
| `time_to_sleep`                             | Time spent sleeping in milliseconds                                       |
| `number_of_times_each_philosopher_must_eat` | Optional number of meals required before stopping                         |


These arguments correspond to the mandatory project specification.

Examples

**Basic simulation**

```bash
./philo 5 800 200 200
```
This starts a simulation with:

- 5 philosophers
- 800 ms before starvation
- 200 ms eating time
- 200 ms sleeping time

**Simulation with a meal limit**
```bash
./philo 5 800 200 200 7
```

The simulation stops once every philosopher has eaten 7 times.

**A philosopher should die**
```bash
./philo 1 800 200 200
```

With only one philosopher, there is only one fork available, so the philosopher cannot acquire two forks and will eventually die.

---

## Output Format

Each state change is printed using the following format:
```
timestamp_in_ms philosopher_id message
```
Possible messages are:
```
has taken a fork
is eating
is sleeping
is thinking
died
```
For example:
```
0 1 is thinking
0 2 is thinking
1 1 has taken a fork
1 1 has taken a fork
1 1 is eating
201 1 is sleeping
```
The project specification requires state messages not to overlap and requires the death message to be displayed within the specified timing constraints.

---

## Project Structure
```
philo/
│
├── Makefile
├── philo.h
│
├── main.c
├── init.c
├── routine.c
├── thread.c
├── utils.c
└── parsing.c
```
The project is divided into several responsibilities.

### Initialization

The initialization code is responsible for:

- Parsing the program arguments
- Initializing the simulation data
- Creating philosophers
- Creating and initializing fork mutexes
- Initializing shared mutexes
- Philosopher Routine

Each philosopher thread repeatedly performs the following cycle:

       ┌───────────┐
       │  Thinking │
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │ Take forks│
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │   Eating  │
       └─────┬─────┘
             │
             ▼
       ┌───────────┐
       │  Sleeping │
       └─────┬─────┘
             │
             └──────────────► Thinking
### Monitoring

The monitor thread continuously checks the state of each philosopher and determines whether the simulation should stop.

### Cleanup

When the simulation ends, the program joins the threads, destroys the mutexes and frees dynamically allocated memory.

### Synchronization

Synchronization is one of the main challenges of this project.

The program uses mutexes to protect shared resources such as:

- Forks
- Console output
- Simulation state

For example, output is protected by a mutex so that messages from different threads do not overlap.

The simulation state is also protected when the monitor checks whether the simulation has ended.

---

## Testing

The project should be tested with different numbers of philosophers and different timing values.

**Normal simulation**
```bash
./philo 5 800 200 200
```
Expected behavior:

Philosophers repeatedly eat, sleep and think.
No philosopher should die if the timing allows everyone to eat.

**Very small time_to_die**
```bash
./philo 5 100 200 200
```
Expected behavior:

At least one philosopher should eventually die because time_to_die is shorter than the time required to eat.

**One philosopher**
```bash
./philo 1 800 200 200
```
Expected behavior:

The philosopher can only access one fork.
They cannot eat.
The philosopher eventually dies.

**Two philosophers**
```bash
./philo 2 800 200 200
```
This is an important synchronization case because the two philosophers share both forks.

**Meal limit**
```bash
./philo 5 800 200 200 5
```
Expected behavior:

The simulation stops once every philosopher has eaten 5 times.

**Stress test**
```bash
./philo 100 800 200 200
```
This can be used to observe the behavior of the program with a larger number of threads.

---

## Race Conditions and Deadlocks

The main synchronization challenges are:

### Race conditions

A race condition can occur when multiple threads access shared data at the same time.

Mutexes are used to protect shared resources and simulation state.

### Deadlocks

A deadlock can occur when philosophers wait indefinitely for resources held by each other.

The implementation therefore needs to carefully control fork acquisition and release so that the simulation can continue.

### Output synchronization

Several philosopher threads can attempt to print at the same time.

A dedicated write mutex is used to ensure that output messages remain consistent.

---

## Memory Management

All dynamically allocated memory must be released before the program exits.

The cleanup process includes:

- Destroying fork mutexes
- Destroying shared mutexes
- Freeing the fork array
- Freeing the philosopher array

This is handled by the cleanup functions in the project.

Memory leaks can be checked using tools such as Valgrind:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200
```
---

## Resources

### Documentation

- [pthread_create() — Linux man page](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_join() — POSIX](https://www.man7.org/linux/man-pages/man3/pthread_join.3p.html)
- [pthreads — Linux man page](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [42 Philosophers — Functions Used](https://42-cursus.gitbook.io/guide/3-rank-03/philosophers/functions-used)
- [Dijkstra — Distributed Arbitration](https://www.cs.utexas.edu/~EWD/transcriptions/EWD07xx/EWD752.html)
- [pthread_mutex_lock — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html)
- [gettimeofday — Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [usleep — Linux man page](https://man7.org/linux/man-pages/man3/usleep.3.html)

---

## AI Usage

AI was used as a learning and documentation support tool during this project.

It was used for:

- Understanding thread synchronization concepts.
- Reviewing the use of POSIX threads and mutexes.
- Finding potential edge cases for testing.
- Understanding timing and synchronization issues.
- Structuring and improving the project documentation.

---

## Author

makoon

42 Paris