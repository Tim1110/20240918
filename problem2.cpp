#include <iostream>
#include <vector>

using namespace std;

// ���j��ƭp�⾭��
vector<vector<char>> powerset(vector<char> S) {
    if (S.empty()) {
        return { {} };
    }
    else {
        // ���X���X�����Ĥ@�Ӥ���
        char element = S[0];
        // �Ѿl�����X�]���F�Ĥ@�Ӥ����H�~�^
        vector<char> rest(S.begin() + 1, S.end());

        // �p��Ѿl���X������
        vector<vector<char>> subsets_without_element = powerset(rest);

        // �Ыؤ@�ӷs���e���Ӧs�]�t�Ĥ@�Ӥ������l��
        vector<vector<char>> subsets_with_element;

        for (auto subset : subsets_without_element) {
            // �N�C�Ӥ��]�t�Ӥ������l���ƻs�@���A�ñN�Ӥ����[��Ӥl����
            subset.push_back(element);
            subsets_with_element.push_back(subset);
        }

        // �N��ӵ��G�X��
        subsets_without_element.insert(subsets_without_element.end(), subsets_with_element.begin(), subsets_with_element.end());

        return subsets_without_element;
    }
}

int main() {
    // ��l�ƶ��X S
    vector<char> S = { 'a', 'b', 'c' };

    // �p�⾭��
    vector<vector<char>> result = powerset(S);

    // ��X���G
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
