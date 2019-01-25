#include <stdio.h>

typedef int T;

typedef struct qItem_ {
    T info;
    struct qItem_ *N;
} qItem;

int qCnt = 0;
qItem *qStart, *qFinish;

int putItem(T);
T getItem();
void freeQueue();

int putItem(T info)
{
    qItem* tmp;
    // Функция malloc() возвращает адрес на первый байт области памяти размером size байт
    tmp = (qItem *)malloc(sizeof(qItem));
    if (tmp == NULL) return 0;
    
    tmp->info = info;
    tmp->N = NULL;
    if (qCnt) {
        qFinish->N = tmp;
        qFinish = tmp;
    } else {
        qStart = tmp;
        qFinish = tmp;
    }
    qCnt++;
    
    return 1;
}

T getItem()
{
    T info;
    qItem* tmp;
    if (qCnt) {
        info = qStart->info;
        tmp = qStart;
        qStart = tmp->N;
        if (tmp == qFinish) qFinish = NULL;
        free(tmp);
        qCnt--;
        return info;
    } else {
        return NULL;
    }
}

void freeQueue()
{
    int i=0;
    qItem *tmp;
    for(i=0; i<qCnt; i++) {
        tmp = qStart;
        qStart = tmp->N;
        free(tmp);
    }
}
