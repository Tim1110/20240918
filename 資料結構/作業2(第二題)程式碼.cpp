int main() {
    Polynomial p1, p2, p3;
    cout << "Enter polynomial 1:" << endl;
    cin >> p1;
    cout << "Enter polynomial 2:" << endl;
    cin >> p2;

    p3 = p1.Add(p2);
    cout << "Sum: " << p3 << endl;

    p3 = p1.Mult(p2);
    cout << "Product: " << p3 << endl;

    float value;
    cout << "Enter a value to evaluate polynomial 1: ";
    cin >> value;
    cout << "Value of polynomial 1 at " << value << " is " << p1.Eval(value) << endl;

    return 0;
}
