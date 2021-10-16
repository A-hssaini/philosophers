/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahssaini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:43:50 by ahssaini          #+#    #+#             */
/*   Updated: 2021/10/12 16:43:53 by ahssaini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watch_him_die(void *arg)
{
	long	time;
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	philo->time_left_die = get_time() + vars->time_to_die;
	while (1)
	{
		time = get_time();
		pthread_mutex_lock(&philo->mutex);
		if (time > philo->time_left_die
			&& philo->meal_nbr != vars->nbr_must_eat)
		{
			pthread_mutex_lock(&philo->vars->mutex_print);
			printf("%ld\t%d\tdied\n", (time - vars->start_time), philo->index + 1);
			pthread_mutex_unlock(&philo->vars->main_mutex);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(500);
	}
	return (NULL);
}

void	routine(t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&philo->mutex);
	philo->meal_nbr++;
	printf_text(philo, vars, "is eating");
	philo->time_left_die = get_time() + vars->time_to_die;
	usleep(vars->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&vars->fork[philo->index]);
	pthread_mutex_unlock(&vars->fork[philo->right_fork]);
	printf_text(philo, vars, "is sleeping");
	usleep(vars->time_to_sleep * 1000);
	printf_text(philo, vars, "is thinking");
}

void	*simulation(void *arg)
{
	t_philo		*philo;
	t_vars		*vars;
	pthread_t	th;

	philo = (t_philo *)arg;
	vars = philo->vars;
	pthread_create(&th, NULL, &watch_him_die, arg);
	pthread_detach(th);
	pthread_create(&th, NULL, &check_if_finished_eating, arg);
	pthread_detach(th);
	while (1)
	{
		lock_forks(philo, vars);
		routine(philo, vars);
	}
	return (NULL);
}

void	mini_main(t_vars *vars)
{
	int			i;
	pthread_t	th;

	i = -1;
	while (++i < vars->nbr_philo)
	{
		pthread_mutex_init(&vars->fork[i], NULL);
		initial_philo(vars, i);
	}
	i = -1;
	while (++i < vars->nbr_philo)
	{
		pthread_create(&th, NULL, simulation, &vars->philo[i]);
		pthread_detach(th);
		usleep(100);
	}
	pthread_mutex_lock(&vars->main_mutex);
}

int	main(int ac, char **av)
{
	t_vars			*vars;

	if ((check_args(ac, av) == 1))
		return (1);
	vars = vars_init(ac, av);
	if (vars)
	{
		mini_main(vars);
	}
	else
		printf("check argument\n");
	return (ft_free(vars));
}
