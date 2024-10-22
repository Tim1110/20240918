#include <iostream>
#include <vector>

using namespace std;

// 遞迴函數計算冪集
vector<vector<char>> powerset(vector<char> S) {
    if (S.empty()) {
        return { {} };
    }
    else {
        // 取出集合中的第一個元素
        char element = S[0];
        // 剩餘的集合（除了第一個元素以外）
        vector<char> rest(S.begin() + 1, S.end());

        // 計算剩餘集合的冪集
        vector<vector<char>> subsets_without_element = powerset(rest);

        // 創建一個新的容器來存包含第一個元素的子集
        vector<vector<char>> subsets_with_element;

        for (auto subset : subsets_without_element) {
            // 將每個不包含該元素的子集複製一份，並將該元素加到該子集中
            subset.push_back(element);
            subsets_with_element.push_back(subset);
        }

        // 將兩個結果合併
        subsets_without_element.insert(subsets_without_element.end(), subsets_with_element.begin(), subsets_with_element.end());

        return subsets_without_element;
    }
}

int main() {
    // 初始化集合 S
    vector<char> S = { 'a', 'b', 'c' };

    // 計算冪集
    vector<vector<char>> result = powerset(S);

    // 輸出結果
    cout << "Powerset of {a, b, c} is: " << endl;
    for (const auto& subset : result) {
        cout << "{ ";
        for (char elem : subset) {
            cout << elem << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}
