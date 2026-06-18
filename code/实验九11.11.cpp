#include <stdio.h>

int main() {
    int a, b, d; 
    printf("请输入两个非0自然数：");
    scanf("%d %d", &a, &b); 
    if (a > b) {
        d = a;
        a = b;
        b = d;
    }

    int e = 0; 
    int f = 0; 

    printf("%d和%d之间的素数有：\n", a, b);
    for (int g = a; g <= b; g++) {
        int h = 1;
        if (g < 2) {
            h = 0;
        } else {
            for (int c = 2; c * c <= g; c++) {
                if (g % c == 0) {
                    h = 0;
                    break; 
                }
            }
        }
        if (h == 1) {
            e++;
            printf("%-5d", g);
            f++;
            if (f % 9 == 0) {
                printf("\n");
                f = 0;
            }
        }
    }

    if (f != 0) printf("\n");
    printf("素数的总个数为：%d个！\n", e);

    return 0;
}
