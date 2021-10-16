/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahssaini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:43:38 by ahssaini          #+#    #+#             */
/*   Updated: 2021/10/12 16:43:40 by ahssaini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 6 && ac != 5)
	{
		printf("check argument\n");
		return (1);
	}
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
			{
				printf("check argument\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args_again(int ac, char **av)
{	
	int	i;
	int	err;
	int	tmp;

	i = 2;
	err = 0;
	while (i < ac)
	{
		tmp = ft_atoi(av[i], &err);
		if (err == 1)
			return (0);
		i++;
	}
	return (1);
}

void	initial_philo(t_vars *vars, int i)
{
	vars->philo[i].vars = vars;
	vars->philo[i].index = i;
	vars->philo[i].right_fork = (i + 1) % vars->nbr_philo;
	vars->philo[i].meal_nbr = 0;
	vars->philo[i].is_full = 0;
}

t_vars	*vars_init(int ac, char **av)
{
	t_vars			*vars;

	if (check_args_again(ac, av))
	{	
		vars = (t_vars *)malloc(sizeof(t_vars));
		vars->nbr_philo = ft_atoi(av[1], 0);
		vars->time_to_die = ft_atoi(av[2], 0);
		vars->time_to_eat = ft_atoi(av[3], 0);
		vars->time_to_sleep = ft_atoi(av[4], 0);
		if (ac == 6)
			vars->nbr_must_eat = ft_atoi(av[5], 0);
		else
			vars->nbr_must_eat = -1;
		vars->philo_finished_eating = 0;
		vars->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		vars->nbr_philo);
		vars->philo = (t_philo *)malloc(sizeof(t_philo) * vars->nbr_philo);
		pthread_mutex_init(&vars->mutex_print, NULL);
		pthread_mutex_init(&vars->main_mutex, NULL);
		pthread_mutex_lock(&vars->main_mutex);
		vars->start_time = get_time();
	}
	else
		return (NULL);
	return (vars);
}
