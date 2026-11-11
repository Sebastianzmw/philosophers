/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhewong <zhewong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:02:29 by zhewong           #+#    #+#             */
/*   Updated: 2024/10/24 09:02:31 by zhewong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*result;

	result = malloc(bytes);
	if (result == NULL)
		error_exit("Error with the malloc");
	return (result);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK
			|| opcode == DESTROY))
		error_exit("the value for the mutex is invalid");
	else if (status == EINVAL && opcode == INIT)
		error_exit("the value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("the mutex is already locked by the current thread");
	else if (status == EPERM)
		error_exit("the mutex is already locked by another thread");
	else if (status == ENOMEM)
		error_exit("out of memory");
	else if (status == EBUSY)
		error_exit("the mutex is already locked by another thread");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("wrong opcode for mutex handle");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("the number of threads system-wide has reached a limit");
	else if (status == EPERM)
		error_exit("the caller does not have appropriate permission");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("the value specified by attr is invalid");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("the value for the thread is invalid");
	else if (status == ESRCH)
		error_exit("no thread with the given id exists");
	else if (status == EDEADLK)
		error_exit("the current thread already joined this thread");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("wrong opcode for thread handle");
}
