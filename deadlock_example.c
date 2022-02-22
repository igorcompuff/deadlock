#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;

void *thread1();
void *thread2();

int main(int argc, char *argv[])
{
    pthread_t thread1_tid;
    pthread_t thread2_tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);

    pthread_create(&thread1_tid, &attr, thread1, NULL);
    pthread_create(&thread2_tid, &attr, thread2, NULL);

    pthread_join(thread1_tid, NULL);
    pthread_join(thread2_tid, NULL);

    return 0;
}

void *thread1()
{
    pthread_mutex_lock(&first_mutex);
    //usleep(1000);
    pthread_mutex_lock(&second_mutex);
    printf("Thread1 entrou na região crítica\n");
    pthread_mutex_unlock(&second_mutex);
    pthread_mutex_unlock(&first_mutex);

    pthread_exit(0);
}

void *thread2()
{
    pthread_mutex_lock(&second_mutex);
    //usleep(1000);
    pthread_mutex_lock(&first_mutex);
    printf("Thread2 entrou na região crítica\n");
    pthread_mutex_unlock(&first_mutex);
    pthread_mutex_unlock(&second_mutex);

    pthread_exit(0);
}

