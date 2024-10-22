#include <iostream>
#include <stack>
using namespace std;

int ackermann_non_recursive(int m, int n) {
    stack<pair<int, int>> s;  // 使用 stack 模擬遞迴，存儲 (m, n)
    s.push({ m, n });  // 初始化將 (m, n) 放入棧中

    while (!s.empty()) {  // 只要棧不為空，繼續處理
        m = s.top().first;  // 獲取棧頂元素
        n = s.top().second;
        s.pop();  // 彈出棧頂元素

        if (m == 0) {
            n += 1;  // 如果 m == 0，根據定義，直接計算 n+1
        }
        else if (n == 0) {
            s.push({ m - 1, 1 });  // 如果 n == 0，則按定義計算 A(m-1, 1)
        }
        else {
            s.push({ m - 1, -1 }); // 存入 (m-1, result)，其中 result 將在之後計算
            s.push({ m, n - 1 });  // 先計算 A(m, n-1)
            continue;  // 跳過回溯，等待結果
        }

        // 應用中間結果進行回溯
        while (!s.empty() && s.top().second == -1) {
            m = s.top().first;
            s.pop();
            n = ackermann_non_recursive(m, n);  // 使用前一步的結果進行計算
        }
    }

    return n;  // 返回最終結果
}

int main() {
    int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;
    cout << "Ackermann(" << m << ", " << n << ") = " << ackermann_non_recursive(m, n) << endl;
    return 0;
}
