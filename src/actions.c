#include "../inc/philo.h"

int	ft_eating(t_philo *philo)
{
	printf("Tiempo zzzzzzero: %llu\n", philo->args->zero_time);
	printf("%i\t%i\t%i\t%i\t%i\t\n", philo->args->n_philo, philo->args->t_die, philo->args->t_eat, philo->args->t_sleep, philo->args->n_meal);
	long long num1, num2;
	pthread_mutex_lock(&philo->fork);
	num1 = ft_get_timestamp();
	sleep(1);
	num2 = ft_get_timestamp();
	printf("************%llu\n", num1);
	printf("////////////%llu\n", num2);
	printf("pruebaaaaaaaaa: %llu\n", num2 - num1);
	printf("TIEMPO %d has taken a fork %d\n", philo->id, philo->r_fork_id);
	pthread_mutex_lock(&philo->left->fork);
	philo->last_meal = ft_get_timestamp();
	printf("Hora ultima comida. %llu\n", philo->last_meal);
	printf("TIEMPO %d has taken a fork %d\n", philo->id, philo->left->r_fork_id);

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