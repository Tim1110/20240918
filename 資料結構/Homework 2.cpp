#include <iostream>
#include <cmath>
using namespace std;

class Term {
    friend class Polynomial; // 聲明 Polynomial 為友元類別
public:
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}

    // Getter 和 Setter 方法
    float getCoef() const { return coef; }
    int getExp() const { return exp; }

    void setCoef(float c) { coef = c; }
    void setExp(int e) { exp = e; }

private:
    float coef; // 系數
    int exp;    // 指數
};

class Polynomial {
public:
    Polynomial();
    ~Polynomial();

    Polynomial Add(const Polynomial& poly) const;
    Polynomial Mult(const Polynomial& poly) const;
    float Eval(float f) const;

    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend istream& operator>>(istream& is, Polynomial& poly);

private:
    Term* termArray; // 非零項的陣列
    int capacity;    // termArray 的大小
    int terms;       // 非零項的數量

    void Resize(int newCapacity);
};

// Constructor
Polynomial::Polynomial() : termArray(nullptr), capacity(0), terms(0) {}

// Destructor
Polynomial::~Polynomial() {
    delete[] termArray;
}

// Resize the term array
void Polynomial::Resize(int newCapacity) {
    Term* newArray = new Term[newCapacity];
    for (int i = 0; i < terms; i++) {
        newArray[i] = termArray[i];
    }
    delete[] termArray;
    termArray = newArray;
    capacity = newCapacity;
}

// Add two polynomials
Polynomial Polynomial::Add(const Polynomial& poly) const {
    Polynomial result;
    result.Resize(terms + poly.terms);

    int i = 0, j = 0, k = 0;
    while (i < terms && j < poly.terms) {
        if (termArray[i].getExp() == poly.termArray[j].getExp()) {
            float sum = termArray[i].getCoef() + poly.termArray[j].getCoef();
            if (sum != 0) {
                result.termArray[k++] = Term(sum, termArray[i].getExp());
            }
            i++;
            j++;
        }
        else if (termArray[i].getExp() > poly.termArray[j].getExp()) {
            result.termArray[k++] = termArray[i++];
        }
        else {
            result.termArray[k++] = poly.termArray[j++];
        }
    }

    while (i < terms) {
        result.termArray[k++] = termArray[i++];
    }

    while (j < poly.terms) {
        result.termArray[k++] = poly.termArray[j++];
    }

    result.terms = k;
    return result;
}

// Multiply two polynomials
Polynomial Polynomial::Mult(const Polynomial& poly) const {
    Polynomial result;
    result.Resize(terms * poly.terms);

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            float newCoef = termArray[i].getCoef() * poly.termArray[j].getCoef();
            int newExp = termArray[i].getExp() + poly.termArray[j].getExp();

            bool found = false;
            for (int k = 0; k < result.terms; k++) {
                if (result.termArray[k].getExp() == newExp) {
                    result.termArray[k].setCoef(result.termArray[k].getCoef() + newCoef);
                    found = true;
                    break;
                }
            }

            if (!found) {
                result.termArray[result.terms++] = Term(newCoef, newExp);
            }
        }
    }

    return result;
}

// Evaluate the polynomial at a given value
float Polynomial::Eval(float f) const {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].getCoef() * pow(f, termArray[i].getExp());
    }
    return result;
}

// Overload << operator for output
ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; i++) {
        if (i > 0 && poly.termArray[i].getCoef() > 0) {
            os << " + ";
        }
        os << poly.termArray[i].getCoef() << "x^" << poly.termArray[i].getExp();
    }
    return os;
}

// Overload >> operator for input
istream& operator>>(istream& is, Polynomial& poly) {
    cout << "Enter the number of terms: ";
    is >> poly.terms;

    poly.Resize(poly.terms);
    for (int i = 0; i < poly.terms; i++) {
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        float coef;
        int exp;
        is >> coef >> exp;
        poly.termArray[i] = Term(coef, exp);
    }

    return is;
}

// Main function
int main() {
    Polynomial p1, p2;
    cout << "Enter first polynomial:\n";
    cin >> p1;

    cout << "Enter second polynomial:\n";
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "First Polynomial: " << p1 << endl;
    cout << "Second Polynomial: " << p2 << endl;
    cout << "Sum: " << sum << endl;
    cout << "Product: " << product << endl;

    return 0;
}
