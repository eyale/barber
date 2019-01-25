#include <stdio.h>
#include <stdlib.h>
// поток
#include <pthread.h>
// содержит символические константы и структуры.
#include <unistd.h>
#include "queue.c"

#define QSIZE 2
int brodWork = 0;
// аналог одноместного семафора, необходим для сопоставления синхронно выполняющихся потоков
pthread_mutex_t cs_mutex = PTHREAD_MUTEX_INITIALIZER;

void *brodobrey() {
    int client = 0;
    for (;;) {
        if (qCnt) {
            pthread_mutex_lock(&cs_mutex);
            brodWork = 1;
            client = getItem();
            pthread_mutex_unlock(&cs_mutex);
            printf("%d Клиент бреется\n", client);
            sleep(100+rand()%100); // barbing
            brodWork = 0;
            printf("%d Клиент побрился\n", client);
        } else {
            sleep(10);
        }
    }
}

void *clients() {
    int tmpCnt = 0;
    for (;;) {
        tmpCnt++;
        printf("Новый клиент: %d\n", tmpCnt);
        if (qCnt != QSIZE) {
            printf("%d Клиент сел в очередь\n", tmpCnt);
            pthread_mutex_lock(&cs_mutex);
            putItem(tmpCnt);
            pthread_mutex_unlock(&cs_mutex);
        } else {
            printf("%d Клиент ушел - нет мест\n", tmpCnt);
        }
        sleep(rand()%100);
    }
}

int main() {
    // создаем переменные потоков
    pthread_t brod;
    pthread_t cl;
    // возвращает текущее календарное время системы.
    time(NULL);
    
    pthread_create(&brod, NULL, brodobrey, NULL);
    pthread_create(&cl, NULL, clients, NULL);

    sleep(1000);
    exit(0);
}
