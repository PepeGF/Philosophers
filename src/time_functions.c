#include "../inc/philo.h"

int	ft_get_timestamp(void)
{
	int				wololo;
	struct timeval	time;

	gettimeofday(&time, NULL);
	wololo = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (wololo);
}

void	ft_set_zero_time(t_args *args)
{
	args->zero_time = ft_get_timestamp();
	return ;
}
