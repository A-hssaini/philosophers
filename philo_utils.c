/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahssaini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:44:05 by ahssaini          #+#    #+#             */
/*   Updated: 2021/10/12 16:44:06 by ahssaini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	lock_forks(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->fork[philo->index]);
	printf_text(philo, vars, "has taken a fork");
	pthread_mutex_lock(&vars->fork[philo->right_fork]);
	printf_text(philo, vars, "has taken a fork");
}

void	printf_text(t_philo *philo, t_vars *vars, char *msg)
{
	long	time;

	time = get_time() - vars->start_time;
	pthread_mutex_lock(&vars->mutex_print);
	printf("%ld\t%d\t%s\n", time, philo->index + 1, msg);
	if (vars->philo_finished_eating == vars->nbr_philo && ft_strlen(msg) == 9)
	{
		printf("simulation over\n");
		pthread_mutex_unlock(&philo->vars->main_mutex);
		return ;
	}
	pthread_mutex_unlock(&vars->mutex_print);
}

int	ft_free(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars)
	{
		while (i < vars->nbr_philo)
		{
			pthread_mutex_destroy(&vars->fork[i]);
			i++;
		}
		free(vars->philo);
		if (vars->fork)
			free(vars->fork);
		pthread_mutex_destroy(&vars->main_mutex);
		pthread_mutex_destroy(&vars->mutex_print);
		free(vars);
	}
	return (0);
}

void	*check_if_finished_eating(void *arg)
{
	t_vars	*vars;
	t_philo	*philo;

	philo = (t_philo *)arg;
	vars = philo->vars;
	while (philo->is_full == 0)
	{
		if (philo->meal_nbr == vars->nbr_must_eat)
		{		
			if (philo->is_full == 0)
			{
				vars->philo_finished_eating++;
				philo->is_full = 1;
			}
		}
		usleep(100);
	}
	return (NULL);
}
