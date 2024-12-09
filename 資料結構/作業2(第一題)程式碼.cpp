#include <iostream>
#include <cmath>
using namespace std;

// Term 類別
class Term {
    friend class Polynomial;
private:
    float coef; // 系數
    int exp;    // 指數
};

// Polynomial 類別
class Polynomial {
private:
    Term* termArray; // 非零項的陣列
    int capacity;    // termArray 的容量
    int terms;       // 非零項的數量

    void Resize() {  // 擴展陣列容量
        capacity *= 2;
        Term* newArray = new Term[capacity];
        for (int i = 0; i < terms; i++)
            newArray[i] = termArray[i];
        delete[] termArray;
        termArray = newArray;
    }

public:
    Polynomial() : capacity(10), terms(0) {
        termArray = new Term[capacity];
    }

    ~Polynomial() {
        delete[] termArray;
    }

    Polynomial Add(Polynomial poly) {
        Polynomial result;
        int i = 0, j = 0;
        while (i < terms && j < poly.terms) {
            if (termArray[i].exp == poly.termArray[j].exp) {
                float sumCoef = termArray[i].coef + poly.termArray[j].coef;
                if (sumCoef != 0) result.termArray[result.terms++] = { sumCoef, termArray[i].exp };
                i++;
                j++;
            }
            else if (termArray[i].exp > poly.termArray[j].exp) {
                result.termArray[result.terms++] = termArray[i++];
            }
            else {
                result.termArray[result.terms++] = poly.termArray[j++];
            }
            if (result.terms >= result.capacity) result.Resize();
        }
        while (i < terms) result.termArray[result.terms++] = termArray[i++];
        while (j < poly.terms) result.termArray[result.terms++] = poly.termArray[j++];
        return result;
    }

    Polynomial Mult(Polynomial poly) {
        Polynomial result;
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < poly.terms; j++) {
                float coef = termArray[i].coef * poly.termArray[j].coef;
                int exp = termArray[i].exp + poly.termArray[j].exp;
                result.AddTerm(coef, exp);
            }
        }
        return result;
    }

    void AddTerm(float coef, int exp) {
        if (coef == 0) return;
        for (int i = 0; i < terms; i++) {
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef;
                if (termArray[i].coef == 0) {
                    for (int j = i; j < terms - 1; j++) termArray[j] = termArray[j + 1];
                    terms--;
                }
                return;
            }
        }
        if (terms >= capacity) Resize();
        termArray[terms++] = { coef, exp };
    }

    float Eval(float f) {
        float result = 0;
        for (int i = 0; i < terms; i++)
            result += termArray[i].coef * pow(f, termArray[i].exp);
        return result;
    }

    // 輸入/輸出運算子重載
    friend istream& operator>>(istream& is, Polynomial& poly);
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
};

istream& operator>>(istream& is, Polynomial& poly) {
    cout << "Enter number of terms: ";
    is >> poly.terms;
    poly.termArray = new Term[poly.terms];
    for (int i = 0; i < poly.terms; i++) {
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        is >> poly.termArray[i].coef >> poly.termArray[i].exp;
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; i++) {
        os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
        if (i < poly.terms - 1) os << " + ";
    }
    return os;
}
