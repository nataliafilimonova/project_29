#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

float calc_q(float curr, float prev) {
    if (prev == 0) return 0;
    float diff = (curr - prev) / prev;
    return diff * diff;
}

int check_rule(float q_curr, float q_prev) {
    if (q_curr > 1.0 && q_prev > 1.0) {
        return 1;
    }
    return 0;
}

int analyze_comp(char name[]) {
    float val;
    float x1 = 0, x2 = 0; 
    float q_prev = 0;
    int warn = 0;

    printf("\n========================================\n");
    printf("Компонент: %s\n", name);
    printf("Введите 5 значений (через пробел, затем Enter):\n");
    
    for (int i = 0; i < 5; i++) {
        if (scanf("%f", &val) != 1) {
            printf("Ошибка! Введите число.\n");
            while (getchar() != '\n'); 
            i--; 
            continue;
        }
        
        if (i >= 2) {
            float q = calc_q(val, x1);
            printf("  X[%d]=%.1f, X[%d]=%.1f -> Q = %.6f", i+1, val, i-1, x1, q);
            
            if (i >= 3) {
                if (check_rule(q, q_prev)) {
                    warn = 1;
                    printf(" | ПРЕДУПРЕЖДЕНИЕ\n");
                } else {
                    printf(" | НОРМА\n");
                }
            } else {
                printf("\n");
            }
            q_prev = q;
        }
        x1 = x2;
        x2 = val;
    }
    
    if (warn == 1) {
        printf("-> Итог %s: ПРЕДУПРЕЖДЕНИЕ\n", name);
    } else {
        printf("-> Итог %s: НОРМА\n", name);
    }
    
    return warn;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int a = analyze_comp("APP");
    int b = analyze_comp("SSD");
    int c = analyze_comp("LOG");

    printf("\n========================================\n");
    printf("--- ПРОВЕРКА ИНЦИДЕНТА ---\n");
    
    if ((a && b) || (a && c) || (b && c)) {
        printf("ВНИМАНИЕ: Инцидент зафиксирован!\n");
    } else {
        printf("Инцидентов не обнаружено. Все системы в норме.\n");
    }
    printf("========================================\n");

    return 0;
}
