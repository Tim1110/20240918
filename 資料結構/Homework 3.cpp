#include <iostream>
using namespace std;

class Polynomial {
private:
    struct Node {
        int coef;  // �t��
        int exp;   // ����
        Node* next; // �U�@�Ӹ`�I���w
        Node(int c = 0, int e = 0, Node* n = nullptr) : coef(c), exp(e), next(n) {}
    };

    Node* head;  // ���V�Y�`�I�����w

    // �M�Ŧh�������Ҧ��`�I
    void clear() {
        if (!head) return;
        Node* current = head->next;
        while (current != head) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
        head = nullptr;
    }

    // �ƻs�h����
    void copy(const Polynomial& other) {
        if (!other.head) return;

        Node* otherCurrent = other.head->next;
        Node* thisTail = head = new Node();

        while (otherCurrent != other.head) {
            thisTail->next = new Node(otherCurrent->coef, otherCurrent->exp);
            thisTail = thisTail->next;
            otherCurrent = otherCurrent->next;
        }
        thisTail->next = head;
    }

public:
    // �w�]�c�y���
    Polynomial() : head(new Node()) {
        head->next = head;  // ��l�Ƭ��۴`��
    }

    // �ƻs�c�y���
    Polynomial(const Polynomial& a) {
        copy(a);
    }

    // ��ȹB��ŭ���
    Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            clear();
            copy(a);
        }
        return *this;
    }

    // �R�c���
    ~Polynomial() {
        clear();
    }

    // ������J�B���
    friend istream& operator>>(istream& is, Polynomial& x) {
        int n, c, e;
        is >> n;  // Ū���h��������
        for (int i = 0; i < n; ++i) {
            is >> c >> e;
            x.addTerm(c, e);
        }
        return is;
    }

    // ������X�B���
    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        Node* current = x.head->next;
        while (current != x.head) {
            os << current->coef << "x^" << current->exp;
            if (current->next != x.head) os << " + ";
            current = current->next;
        }
        return os;
    }

    // �K�[�h�������涵��
    void addTerm(int coef, int exp) {
        Node* prev = head;
        Node* current = head->next;

        while (current != head && current->exp > exp) {
            prev = current;
            current = current->next;
        }

        if (current != head && current->exp == exp) {
            current->coef += coef;
            if (current->coef == 0) {
                prev->next = current->next;
                delete current;
            }
        }
        else {
            Node* newNode = new Node(coef, exp, current);
            prev->next = newNode;
        }
    }

    // �����[�k�B���
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result = *this;
        Node* bCurrent = b.head->next;
        while (bCurrent != b.head) {
            result.addTerm(bCurrent->coef, bCurrent->exp);
            bCurrent = bCurrent->next;
        }
        return result;
    }

    // ������k�B���
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result = *this;
        Node* bCurrent = b.head->next;
        while (bCurrent != b.head) {
            result.addTerm(-bCurrent->coef, bCurrent->exp);
            bCurrent = bCurrent->next;
        }
        return result;
    }

    // �������k�B���
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        Node* aCurrent = head->next;
        while (aCurrent != head) {
            Node* bCurrent = b.head->next;
            while (bCurrent != b.head) {
                result.addTerm(aCurrent->coef * bCurrent->coef, aCurrent->exp + bCurrent->exp);
                bCurrent = bCurrent->next;
            }
            aCurrent = aCurrent->next;
        }
        return result;
    }

    // �����h������
    float Evaluate(float x) const {
        float result = 0;
        Node* current = head->next;
        while (current != head) {
            result += current->coef * pow(x, current->exp);
            current = current->next;
        }
        return result;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "Enter the first polynomial (format: n c1 e1 c2 e2 ...): ";
    cin >> p1;
    cout << "Enter the second polynomial (format: n c1 e1 c2 e2 ...): ";
    cin >> p2;

    cout << "Polynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;

    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << prod << endl;

    float x;
    cout << "Enter a value for x to evaluate Polynomial 1: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}
