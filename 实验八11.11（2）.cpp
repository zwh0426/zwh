#include <stdio.h>

int main() {
    int n;
    printf("请输入非0自然数n：");
    scanf("%d", &n);

    int a = n * n * n; // 目标值n3
    int b;

    // 外层for循环：遍历起始奇数（从1开始，每次+2）
    for (b = 1; ; b += 2) {
        int sum = 0;
        int c = b;
        // 内层for循环：累加n个连续奇数
        for (int i = 0; i < n; i++) {
            sum += c;
            c += 2;
        }

        // 满足条件则输出并退出
        if (sum == a) {
            printf("%d*%d*%d = ", n,n,n);
            c = b;
            for (int i = 0; i < n; i++) {
                printf("%d", c);
                if (i < n - 1) printf("+");
                c += 2;
            }
            printf("\n");
            break; // 退出外层循环
        }
    }

    return 0;
}
