#include <stdio.h>
#include <math.h>
#include <locale.h>

int check(float x[], int n, char name[]) {
    float q[10]; 
    int warn = 0;
    
    for (int i = 2; i < n; i++) {
        if (x[i-2] != 0) { 
            float diff = (x[i] - x[i-2]) / x[i-2];
            q[i] = diff * diff;
        } else {
            q[i] = 0;
        }
        printf("%s: X[%d]=%.1f, X[%d]=%.1f -> Q = %.6f\n", name, i+1, x[i], i-1, x[i-2], q[i]);
    }
    
    for (int i = 3; i < n; i++) {
        if (q[i] > 1.0 && q[i-1] > 1.0) {
            warn = 1;
        }
    }
    
    if (warn == 1) {
        printf("Состояние: ПРЕДУПРЕЖДЕНИЕ\n");
    } else {
        printf("Состояние: НОРМА\n");
    }
    
    return warn;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    float app[5] = {53.8, 57.2, 55.2, 53.2, 51.2};
    float ssd[5] = {43.7, 44.2, 44.7, 50.6, 51.1};
    float log[7] = {32.0, 33.6, 31.3, 30.6, 35.2, 37.5, 34.5}; 

    printf("--- Анализ состояний ---\n");
    
    int a = check(app, 5, "APP");
    int b = check(ssd, 5, "SSD");
    int c = check(log, 7, "LOG");

    printf("\n--- Проверка инцидента ---\n");
    
    if ((a == 1 && b == 1) || (a == 1 && c == 1) || (b == 1 && c == 1)) {
        printf("Инцидент зафиксирован!\n");
    } else {
        printf("Инцидентов не обнаружено. Все системы в норме.\n");
    }

    return 0;
}
