#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.t>

#define MIN_TIME 90000
#define MAX_TIME 110000

#define NUM_VIP 42
#define NUM_ECON 129

pthread_mutex_t door;
pthread_mutex_t door[2];

// one passenger passes
void pass(void)
{
	int rnd;
	rnd = (MAX_TIME - MIN_TIME)*rand() + MIN_TIME;
	usleep(rnd);
}

void *uploadSingleVip(void *_)
{
	pthread_mutex_lock(&door);
	pass();
	pthread_mutex_unlock(&door);
}

// upload all VIPs: each of them is another thread
void *UploadVIP(void *num_vip)
{
	pthread_t vips[(int)num_vip];
	pthread_mutex_init(&door, NULL);
	int i;
	for(i = 0; i < (int)num_vip; ++i)
	{
		pthread_create(vips + i, NULL, &uploadSingleVip, NULL);
	}
	for(i = 0; i < (int)num_vip; ++i)
	{
		pthread_join(vips[i], NULL);
	}
	pthread_mutex_destroy(&door);
}

void *uploadSingleEcon(void *j)
{
	pthread_mutex_lock(&door[(int)j]);
	pass();
	pthread_mutex_unlock(&door[(int)j]);
}

// upload all economies: each of them is another thread
void *UploadEcon(void *num_econs)
{
	// This should be done with semaphores,
	// but no time for that :)
	pthread_t econs[(int)num_econs + 1];
	pthread_mutex_init(door, NULL);
	pthread_mutex_init(door + 1, NULL);
	int i;

	for(i = 0; i < (int)num_econs; i+=2)
	{
		pthread_create(econs + i, NULL, &uploadSingleEcon, (void *)0);
		pthread_create(econs + i + 1, NULL, &uploadSingleEcon, (void *)1);
	}
	for(i = 0; i < (int)num_econs; i+=2)
	{
		pthread_join(econs[i], NULL);
		pthread_join(econs[i + 1], NULL);
	}
	pthread_mutex_destroy(&door[0]);
	pthread_mutex_destroy(&door[1]);

}

int main(void)
{
	pthread_t vip, econ;
	pthread_attr_t join_attr;

	pthread_attr_init(&join_attr);
	pthread_attr_setdetachstate(&join_attr, PTHREAD_CREATE_JOINABLE);

	clock_t start, end;
	start = clock();
	pthread_create(&vip, &join_attr, UploadVIP, (void *)NUM_VIP);
	end = clock();

	start = clock();
	pthread_create(&econ, &join_attr, UploadEcon, (void *)NUM_ECON);
	end = clock();

	pthread_attr_destroy(&join_attr);
	void *_;
	pthread_join(vip, &_);
	pthread_join(econ, &_);

	pthread_exit(NULL);
	return 0;
}
