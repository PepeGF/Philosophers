#include "../inc/philo.h"

long long	ft_get_timestamp(void)
{
	long long		wololo;
	struct timeval	time;

	gettimeofday(&time, NULL);
	wololo = time.tv_sec * 1000000 + time.tv_usec;
	return (wololo);
}