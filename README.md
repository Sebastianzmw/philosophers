# philosophers

A solution to the dining philosophers problem using POSIX threads and mutexes, written at 42 Kuala Lumpur (2024).

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_each]
./philo 5 800 200 200 7
```

## How it works
- Each philosopher is a thread, and each fork is a mutex
- A separate monitor thread checks whether anyone has starved and stops the simulation as soon as someone does
- All shared state (last meal time, meal counter, "simulation finished" flag) is read and written under mutexes, which prevents **data races**
- Odd and even philosophers pick up their forks in opposite order and start slightly out of step, which prevents **deadlocks** and evens out access to the forks
- A precise sleep (`usleep` in short steps against `gettimeofday`) keeps timing accurate to the millisecond
- Every `pthread_*` call is wrapped with error handling

## Build
```sh
make
```
