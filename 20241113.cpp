#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// �G���j�M��ơA��^�ؼЭȦb�}�C�������ޡA�Y�䤣��h��^ -1
template <typename T>
int binary_search(const vector<T>& data, const T& target) {
    int left = 0, right = data.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid] == target) {
            return mid;  // ���ؼСA��^����
        }
        else if (data[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;  // �S�����ؼ�
}

int main() {
    int n, q;
    char T;
    while (cin >> T >> n >> q) {
        vector<string> str_data;
        vector<int> int_data;

        // �ھڸ�ƫ��OŪ�����
        if (T == 'i') {
            int_data.resize(n);
            for (int i = 0; i < n; ++i) {
                cin >> int_data[i];
            }
        }
        else if (T == 's') {
            str_data.resize(n);
            for (int i = 0; i < n; ++i) {
                cin >> str_data[i];
            }
        }

        // �B�z�C�@�Ӭd��
        for (int i = 0; i < q; ++i) {
            if (T == 'i') {
                int target;
                cin >> target;
                int result = binary_search(int_data, target);
                cout << result << endl;
            }
            else if (T == 's') {
                string target;
                cin >> target;
                int result = binary_search(str_data, target);
                cout << result << endl;
            }
        }
    }

    return 0;
}
