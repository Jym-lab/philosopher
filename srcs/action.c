/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:59:52 by yjoo              #+#    #+#             */
/*   Updated: 2022/08/27 01:59:52 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks_m[philo->forks[LEFT]]);
	print_msg(philo, TYPE_FORK);
	pthread_mutex_lock(&philo->info->forks_m[philo->forks[RIGHT]]);
	print_msg(philo, TYPE_FORK);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->info->argv[TIME_TO_DIE];
	print_msg(philo, TYPE_EAT);
	ft_sleep(philo->info->argv[TIME_TO_EAT]);
	philo->eat_count++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->eat_mutex);
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, TYPE_SLEEP);
	pthread_mutex_unlock(&philo->info->forks_m[philo->forks[LEFT]]);
	pthread_mutex_unlock(&philo->info->forks_m[philo->forks[RIGHT]]);
	ft_sleep(philo->info->argv[TIME_TO_SLEEP]);
}

void	clear_info(t_info *info)
{
	clear_forks(info);
	pthread_mutex_destroy(&info->write_m);
	pthread_mutex_destroy(&info->dead_m);
}

void	clear_forks(t_info *info)
{
	int	i;

	if (info->forks_m)
	{
		i = 0;
		while (i < info->argv[NUM_OF_PHILO])
			pthread_mutex_destroy(&info->forks_m[i++]);
		if (info->philos)
		{
			i = 0;
			while (i < info->argv[NUM_OF_PHILO])
			{
				pthread_mutex_destroy(&info->philos[i].mutex);
				pthread_mutex_destroy(&info->philos[i++].eat_mutex);
			}
		}
		if (info->philos != 0)
			free(info->philos);
	}
}
