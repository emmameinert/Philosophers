## Philophers

Philosophers is a slightly changed project about the [known dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). 
Each philospher comes with one fork to a table. Everybody can only eat with a left and a right fork, otherwise the philosopher thinks or sleeps. 
The philosophers can not talk to each other and don't know what the others are doing.
The focus of the project is to build a simulation of this problem with certain parameters given by the user, without running into a deadlock.

<img width="226" alt="Screen Shot 2023-11-13 at 1 05 35 PM" src="https://github.com/emmameinert/Philo/assets/110816436/5da68db5-c468-45bf-a77c-e14b842562d2">
[(source)](https://en.wikipedia.org/wiki/Dining_philosophers_problem#/media/File:An_illustration_of_the_dining_philosophers_problem.png)

## Arguments

number_of_philosophers

time_to_die 

time_to_eat 

time_to_sleep

The last argument is optional:
[number_of_times_each_philosopher_must_eat]

An example input would be: ./philo 3 121 60 60 or ./philo 3 121 60 60 2

## Key learnings

- Multithreading
- Using mutexes
- Avoiding deadlocks
  
