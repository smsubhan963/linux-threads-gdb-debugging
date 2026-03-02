#include <pthread.h>
#include <stdio.h>

int shared_counter = 0;
int results[2] = {0, 0};

void* worker_task(void* arg) {
    int id = *(int*)arg;
    int index = id - 1;

    for (int i = 0; i < 100000; i++) {
        results[index]++;
        shared_counter++;
    }

    // Thread 2 sacrifices itself 😭
    if (id == 2) {
        printf("Thread 2 is about to sacrifice itself!\n");
        int *death = NULL;
        int trigger = *death; // boom (SIGSEGV)
        (void)trigger;
    }

    printf("Thread %d finished. Results[%d] = %d\n", id, index, results[index]);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    printf("Launching threads...\n");

    pthread_create(&thread1, NULL, worker_task, &id1);
    pthread_create(&thread2, NULL, worker_task, &id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
