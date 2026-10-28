#include <stdio.h>
#include <math.h>

#define K 2
#define L 1.0

int check(float data[], int n, char name[]) {
    float q[10] = {0};
    int status = 0;
    
    for (int i = K; i < n; i++) {
        float curr = data[i];
        float prev = data[i-K];
        if (prev != 0) {
            float diff = (curr - prev) / prev;
            q[i] = diff * diff;
        }
    }
    
    for (int i = K + 1; i < n; i++) {
        if (q[i] > L && q[i-1] > L) {
            status = 1;
        }
    }
    
    printf("Компонент %s: ", name);
    if (status) {
        printf("ПРЕДУПРЕЖДЕНИЕ\n");
    } else {
        printf("НОРМА\n");
    }
    return status;
}

int main() {
    float app[] = {53.8, 57.2, 55.2, 53.2, 51.2};
    float ssd[] = {43.7, 44.2, 44.7, 50.6, 51.1};
    float log[] = {32.0, 33.6, 30.6, 35.2, 34.5};

    printf("--- Анализ состояний ---\n");
    
    int a = check(app, 5, "APP");
    int b = check(ssd, 5, "SSD");
    int c = check(log, 5, "LOG");

    printf("\n--- Проверка инцидента ---\n");
    
    if ((a && b) || (a && c) || (b && c)) {
        printf("Инцидент зафиксирован!\n");
    } else {
        printf("Инцидентов не обнаружено. Все системы в норме.\n");
    }

    return 0;
}
