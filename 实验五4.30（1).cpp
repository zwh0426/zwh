#include <iostream>
#include <iomanip>
using namespace std;

#define maxsize 100
#define QueueIncrement 10
typedef int QElemType;

typedef struct {
    QElemType *data;
    int rear;
    int front;
    int queuesize;
    int incrementsize;
} SqQueue;

// 扩容函数
void IncrementQueuesize(SqQueue &Q) {
    QElemType *a = new QElemType[Q.queuesize + Q.incrementsize];
    for (int k = 0; k < Q.queuesize - 1; k++) {
        a[k] = Q.data[(Q.front + k) % Q.queuesize];
    }
    delete[] Q.data;
    Q.data = a;
    Q.front = 0;
    Q.rear = Q.queuesize - 1;
    Q.queuesize += Q.incrementsize;
}

// 初始化队列
void InitQueue(SqQueue &Q) {
    Q.data = new QElemType[maxsize];
    Q.front = Q.rear = 0;
    Q.incrementsize = QueueIncrement;
    Q.queuesize = maxsize;
}

// 判断队列是否为空
int isEmpty(SqQueue Q) {
    return Q.front == Q.rear ? 1 : 0;
}

// 判断队列是否已满（基于当前 queuesize）
int isFull(SqQueue Q) {
    return Q.front == (Q.rear + 1) % Q.queuesize ? 1 : 0;
}

// 入队
int EnQueue(SqQueue &Q, int x) {
    if (isFull(Q)) {
        IncrementQueuesize(Q);
    }
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % Q.queuesize;
    return 1;
}

// 出队（注意参数 x 为引用）
int DeQueue(SqQueue &Q, int &x) {
    if (isEmpty(Q)) return 0;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % Q.queuesize;
    return 1;
}

// 获取队列长度
int GetLen(SqQueue Q) {
    return (Q.rear - Q.front + Q.queuesize) % Q.queuesize;
}

// 获取队头元素
int GetHead(SqQueue Q, int &e) {
    if (isEmpty(Q)) return 0;
    e = Q.data[Q.front];
    return 1;
}

// 利用循环队列打印杨辉三角
void printYangHui(int n) {
    if (n <= 0) return;

    SqQueue q;
    InitQueue(q);

    // 第一行：1
    EnQueue(q, 1);
    // 添加行分隔符 0
    EnQueue(q, 0);

    for (int row = 1; row <= n; ++row) {
        int prev = 0;
        while (true) {
            int cur;
            DeQueue(q, cur);   // 出队一个元素
            if (cur == 0) {
                // 行结束，将下一行的分隔符入队
                EnQueue(q, 0);
                break;
            }
            // 输出当前元素（每个数占4位）
            cout << setw(4) << cur;
            // 计算新元素 = 上一行相邻两数之和
            int newVal = prev + cur;
            EnQueue(q, newVal);
            prev = cur;
        }
        cout << endl;
    }

    // 释放队列内存
    delete[] q.data;
}

int main() {
    int n;
    cout << "请输入要打印的杨辉三角形的行数：";
    cin >> n;
    printYangHui(n);
    return 0;
}
