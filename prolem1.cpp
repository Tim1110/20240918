#include <iostream>
#include <stack>
using namespace std;

int ackermann_non_recursive(int m, int n) {
    stack<pair<int, int>> s;  // �ϥ� stack �������j�A�s�x (m, n)
    s.push({ m, n });  // ��l�ƱN (m, n) ��J�̤�

    while (!s.empty()) {  // �u�n�̤����šA�~��B�z
        m = s.top().first;  // ����̳�����
        n = s.top().second;
        s.pop();  // �u�X�̳�����

        if (m == 0) {
            n += 1;  // �p�G m == 0�A�ھکw�q�A�����p�� n+1
        }
        else if (n == 0) {
            s.push({ m - 1, 1 });  // �p�G n == 0�A�h���w�q�p�� A(m-1, 1)
        }
        else {
            s.push({ m - 1, -1 }); // �s�J (m-1, result)�A�䤤 result �N�b����p��
            s.push({ m, n - 1 });  // ���p�� A(m, n-1)
            continue;  // ���L�^���A���ݵ��G
        }

        // ���Τ������G�i��^��
        while (!s.empty() && s.top().second == -1) {
            m = s.top().first;
            s.pop();
            n = ackermann_non_recursive(m, n);  // �ϥΫe�@�B�����G�i��p��
        }
    }

    return n;  // ��^�̲׵��G
}

int main() {
    int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;
    cout << "Ackermann(" << m << ", " << n << ") = " << ackermann_non_recursive(m, n) << endl;
    return 0;
}
