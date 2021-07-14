#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
# include <sys/time.h>

/*

memset, printf, malloc, free, write,
usleep, gettimeofday, 

pthread_create,
pthread_detach, 
pthread_join, 
pthread_join() is a blocking call, it will block the calling thread until the other thread ends.
First parameter of pthread_join() is the ID of target thread.

pthread_mutex_init,
pthread_mutex_destroy, 
pthread_mutex_lock,
pthread_mutex_unlock

*/


void	*ft_routine2(void *arg)
{
	int *azz = (int *)(arg);
	printf("2.starting routine\n");
	printf("arg:-%d-\n", *azz);
	*azz = 666;
	return (arg);

}

void	*ft_routine(void *arg)
{
	printf("starting routine\n");
	printf("arg:-%s-\n", (char *)arg);
	arg = "oiac\0";
	return (arg);

}

int main()
{
	struct timeval	ms;
	gettimeofday(&ms, NULL);
	printf("%d\n", ms.tv_usec);
	gettimeofday(&ms, NULL);
	printf("%d\n", ms.tv_usec);
	gettimeofday(&ms, NULL);
	printf("%d\n", ms.tv_usec);
	gettimeofday(&ms, NULL);
	printf("%d\n", ms.tv_usec);

}


// int main()
// {
// 	pthread_t 		asd1;
// 	pthread_t 		asd2;

// 	char *str;
// 	str = "ciao\0";
// 	if (pthread_create(&asd1, NULL, ft_routine, (void *)str) != 0)
// 		printf("\tp_c:%s\n", strerror(errno));
// 	if (pthread_join(asd1, (void **)&str) != 0)  // simile a waitpid
// 		printf("\tp_j:%s\n",  strerror(errno));
// 	printf("end:-%s-\n", str);

// 	int	fff = 999;
// 	int	*pp = &fff;
// 	// if (pthread_detach(asd2) != 0)
// 	// 	printf("\tp_d: %s\n", strerror(errno));
// 	if (pthread_create(&asd2, NULL, ft_routine2, (void *)pp) != 0)
// 		printf("\tp_c:%s\n", strerror(errno));
// 	if (pthread_join(asd2, (void **)&pp) != 0)
// 		printf("\tp_j:%s\n",  strerror(errno));
// 	printf("2.end: %d\n", fff);
// 	read(0, str, 1);
// }