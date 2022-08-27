/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:13:57 by yjoo              #+#    #+#             */
/*   Updated: 2022/08/26 22:13:57 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

# define NUM_OF_PHILO 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define MUST_EAT 4
# define LEFT 0
# define RIGHT 1
# define TYPE_EAT 	0
# define TYPE_SLEEP 1
# define TYPE_FORK 	2
# define TYPE_THINK	3
# define TYPE_DIED 	4
# define TYPE_OVER 	5

typedef struct s_philo
{
	int				pid;
	int				is_eating;
	int				forks[2];
	int				eat_count;
	time_t			limit;
	time_t			last_eat;
	struct s_info	*info;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_mutex;
}	t_philo;

typedef struct s_info
{
	int				argv[5];
	int				is_died;
	time_t			start;
	t_philo			*philos;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	dead_m;
}	t_info;

void	err_msg(char *msg);
void	print_msg(t_philo *philo, int type);
void	ft_sleep(int ms);
void	clear_info(t_info *info);
void	clear_forks(t_info *info);

int		take_forks(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		argv_init(t_info *info, int ac, char **av);

time_t	get_time(void);

#endif
