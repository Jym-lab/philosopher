/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:17:31 by yjoo              #+#    #+#             */
/*   Updated: 2022/08/27 00:17:31 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_atoi(const char *nptr)
{
	int	result;
	int	minus;

	result = 0;
	minus = 1;
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n' || *nptr == '\r'
		|| *nptr == '\t' || *nptr == '\v')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			minus = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * minus);
}

static int	mutexes_init(t_info *info)
{
	int	i;

	pthread_mutex_init(&info->write_m, NULL);
	pthread_mutex_init(&info->dead_m, NULL);
	pthread_mutex_lock(&info->dead_m);
	info->forks_m = (pthread_mutex_t *)malloc(
			sizeof(*(info->forks_m)) * info->argv[NUM_OF_PHILO]);
	if (!info->forks_m)
		return (1);
	i = 0;
	while (i < info->argv[NUM_OF_PHILO])
		pthread_mutex_init(&info->forks_m[i++], NULL);
	return (0);
}

static void	philos_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->argv[NUM_OF_PHILO])
	{
		info->philos[i].is_eating = 0;
		info->philos[i].pid = i;
		info->philos[i].forks[LEFT] = i;
		info->philos[i].forks[RIGHT] = (i + 1) % info->argv[NUM_OF_PHILO];
		info->philos[i].eat_count = 0;
		info->philos[i].info = info;
		pthread_mutex_init(&info->philos[i].mutex, NULL);
		pthread_mutex_init(&info->philos[i].eat_mutex, NULL);
		pthread_mutex_lock(&info->philos[i].eat_mutex);
		i++;
	}
}

int	argv_init(t_info *info, int ac, char **av)
{
	info->argv[NUM_OF_PHILO] = ft_atoi(av[1]);
	info->argv[TIME_TO_DIE] = ft_atoi(av[2]);
	info->argv[TIME_TO_EAT] = ft_atoi(av[3]);
	info->argv[TIME_TO_SLEEP] = ft_atoi(av[4]);
	info->forks_m = NULL;
	info->philos = NULL;
	info->is_died = 0;
	if (ac == 6)
		info->argv[MUST_EAT] = ft_atoi(av[5]);
	else
		info->argv[MUST_EAT] = 0;
	if (info->argv[NUM_OF_PHILO] < 1
		|| (ac == 6 && info->argv[MUST_EAT] <= 0)
		|| info->argv[TIME_TO_DIE] <= 0 || info->argv[TIME_TO_EAT] <= 0
		|| info->argv[TIME_TO_SLEEP] <= 0)
		return (1);
	info->philos = malloc(sizeof(t_philo) * info->argv[NUM_OF_PHILO]);
	if (!info->philos)
		return (1);
	philos_init(info);
	return (mutexes_init(info));
}
