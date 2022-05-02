#include "../inc/philo.h"

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	printf("%lld ms %d has taken a fork\n", (ft_get_timestamp()
			- philo->args->zero_time) / 1000, philo->r_fork_id);
	pthread_mutex_lock(&philo->left->fork);
	printf("%lld ms %d has taken a fork\n", (ft_get_timestamp()
			- philo->args->zero_time) / 1000, philo->r_fork_id);
	philo->last_meal = ft_get_timestamp();
	printf("%lld ms %d is eating\n", (philo->last_meal
			- philo->args->zero_time) / 1000, philo->id);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_lock(&philo->left->fork);
	return (0);
}

void	ft_sleeping(t_philo *philo)
{
(void)philo;
	return ;
}

void	ft_thinking(t_philo *philo)
{
(void)philo;
	return ;
}
