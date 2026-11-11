/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhewong <zhewong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:05:43 by zhewong           #+#    #+#             */
/*   Updated: 2024/10/18 13:05:48 by zhewong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <errno.h>
# include <unistd.h>
# include <sys/time.h>

# define DEBUG_MODE 1

typedef enum	e_status
{
	EATING,
	THINKING,
	SLEEPING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}				t_opcode;

typedef enum	e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}				t_time_code;

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

typedef struct	s_philo
{
	int			id;
	bool		full;
	long		meal_counter;
	long		last_meal_time; //time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id; //a philo is a thread
	t_mtx		philo_mutex;
	t_table		*table;
}				t_philo;

struct	s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals; 
	long		start_simulation;
	long		threads_running_nbr;
	bool		end_simulation; //phile dies or meal finished
	bool		all_threads_ready;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
};

void	error_exit(const char *error);
void	parse_input(t_table *table, char **argv);
void	*safe_malloc(size_t byte);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode);
void	data_init(t_table *table);
long	gettime(t_time_code time_code);
void	percise_usleep(long usec, t_table *table);
void	write_status(t_philo_status status, t_philo *philo, bool debug);


void	wait_all_threads(t_table *table);
bool	all_threads_are_running(t_mtx *mutex, long *threads,
			long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);
void	clean(t_table *table);

void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex,  long *dest, long value);
bool	simulation_finished(t_table *table);
void	*monitor_dinner(void *data);
void	meal_start(t_table	*table);
void	*meal_simulation(void *data);
void	thinking(t_philo *philo, bool pre_simulation);
void	de_synchronize_philos(t_philo *philo);

#endif