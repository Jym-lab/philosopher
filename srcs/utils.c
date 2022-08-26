/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:20:04 by yjoo              #+#    #+#             */
/*   Updated: 2022/08/27 00:20:04 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	err_msg(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

static char	*get_message(int type)
{
	if (type == TYPE_EAT)
		return (" is eating\n");
	else if (type == TYPE_SLEEP)
		return (" is sleeping\n");
	else if (type == TYPE_FORK)
		return (" has taken a fork\n");
	else if (type == TYPE_THINK)
		return (" is thinking\n");
	else if (type == TYPE_OVER)
		return (" must eat count reached\n");
	return (" died\n");
}

void	print_msg(t_philo *philo, int type)
{
	static int	is_died = 0;

	pthread_mutex_lock(&philo->info->write_m);
	if (!is_died)
	{
		printf("%ld\t", get_time() - philo->info->start);
		if (type != TYPE_OVER)
			printf("%d", philo->pid + 1);
		if (type >= TYPE_DIED)
			is_died = 1;
		printf("%s", get_message(type));
	}
	pthread_mutex_unlock(&philo->info->write_m);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(int ms)
{
	time_t	wait;

	wait = get_time() + ms;
	while (wait > get_time())
		usleep(100);
}
