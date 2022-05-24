#include "../inc/philo.h"

/*
int	ft_lst_len(t_philo *lst_philo)
{
	t_philo	*aux;
	int		i;

	if (!lst_philo)
		return (0);
	i = 0;
	aux = lst_philo;
	while (aux)
	{
		aux = aux->right;
		i++;
	}
	printf("Longitud lista: %d\n", i);
	return (i);
}
*/


void ft_prueba()
{
	struct timeval time1;
	struct timeval time2;

	gettimeofday(&time1, NULL);
	usleep(1000);
	gettimeofday(&time2, NULL);

	long long wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	long long wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 1000 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/1000-100);

	gettimeofday(&time1, NULL);
	usleep(500);
	gettimeofday(&time2, NULL);

	wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 500 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/500-100);

	gettimeofday(&time1, NULL);
	usleep(300);
	gettimeofday(&time2, NULL);

	wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 300 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/300-100);

	gettimeofday(&time1, NULL);
	usleep(200);
	gettimeofday(&time2, NULL);

	wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 200 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/200-100);

	gettimeofday(&time1, NULL);
	usleep(100);
	gettimeofday(&time2, NULL);

	wololo1 = time1.tv_sec * 1000000 + time1.tv_usec;
	wololo2 = time2.tv_sec * 1000000 + time2.tv_usec;
	printf("tiempo en 100 us: %llu, porcentaje %.2lld \n", wololo2 - wololo1, (wololo2 - wololo1)*100/100-100);
}