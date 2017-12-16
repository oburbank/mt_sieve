#include <stdio.h>
#include <pthread.h>

#define S 100000000
#define W 2
pthread_t ts[W];
char a[S];
pthread_mutex_t l = PTHREAD_MUTEX_INITIALIZER;
int prime = 2;

void *worker(void *ptr) {
	long j;
	int i;
	for(;;) {
		pthread_mutex_lock(&l);
			i = prime;
			while (a[++prime]);
			j = i*i;
			if (j>=S) {
				pthread_mutex_unlock(&l);
				return NULL;
			}
			a[j]|=1;
		pthread_mutex_unlock(&l);
		for (j+=i;j<S;j+=i) a[j]|= 1;
	}
}

int main() {
	int i;
	for (i=0;i<W;i++)
		pthread_create(ts+i, NULL, worker, NULL);
	worker(NULL);
	for (i=0;i<W;i++) 
		pthread_join(ts[i], NULL);
	for (i=2;i<S;i++) if (!a[i]) 
		printf("%d\n",i);
	return 0;
}

