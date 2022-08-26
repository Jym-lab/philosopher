/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:12:31 by yjoo              #+#    #+#             */
/*   Updated: 2022/08/26 22:12:31 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*monitor_count(void *info_v)
{
	t_info	*info;
	int		i;
	int		total;

	info = (t_info *)info_v;
	total = 0;
	while (total < info->argv[MUST_EAT])
	{
		i = 0;
		while (i < info->argv[NUM_OF_PHILO])
			pthread_mutex_lock(&info->philos[i++].eat_mutex);
		total++;
	}
	print_msg(&info->philos[0], TYPE_OVER);
	pthread_mutex_unlock(&info->dead_m);
	return ((void *)0);
}

static void	*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo *)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			print_msg(philo, TYPE_DIED);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->info->dead_m);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(100);
	}
}

static void	*routine(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)philo_v;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->info->argv[TIME_TO_DIE];
	if (pthread_create(&tid, NULL, monitor, philo_v) != 0)
		return ((void *)1);
	pthread_detach(tid);
	while (1)
	{
		if (philo->info->argv[NUM_OF_PHILO] > 1)
		{
			take_forks(philo);
			philo_eat(philo);
			philo_sleep(philo);
		}
		else
			ft_sleep(100);
		print_msg(philo, TYPE_THINK);
	}
	return ((void *)0);
}

static int	threads_start(t_info *info)
{
	int			i;
	pthread_t	tid;

	info->start = get_time();
	if (info->argv[MUST_EAT] > 0)
	{
		if (pthread_create(&tid, NULL, monitor_count, (void *)info) != 0)
			return (1);
		pthread_detach(tid);
	}
	i = 0;
	while (i < info->argv[NUM_OF_PHILO])
	{
		if (pthread_create(&tid, NULL, routine,
				(void *)(&info->philos[i])) != 0)
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
		err_msg("Usage: ./philo [number_of_philosopher] [time_to_die] [time_to_eat] \
[time_to_sleep] ([number_of_times_each_philosopher_must_eat])");
	if (argv_init(&info, ac, av))
		err_msg("philo init error");
	if (threads_start(&info))
		err_msg("thread error");
	pthread_mutex_lock(&info.dead_m);
	pthread_mutex_unlock(&info.dead_m);
	clear_info(&info);
	return (0);
}
