#include <iostream>
#include <string>
#include "big_data_int.h"

string* getString() {
    str->reserve(100);
    std::cout << "请输入内容：";
    std::cin.getline(str->c_str(), 100);
    return str;
}

big_data_int calc(big_data_int a, big_data_int b, string op) {
    switch (op.c_str()[0]) {
        case '+':
            c = a + b;
            break;
        case '-':
            c = a - b;
            break;
        case '*':
            c = a * b;
            break;
        case '/':
            c = a / b;
            break;
        case '%':
            c = a % b;
            break;
        default:
            cout<<"Wrong operator input"<<endl;  
            return big_data_int("-1");
    }
    return c;
}

int main() 
{
    cout<<"please input two numbers:"<<endl;
    string* s_a, *s_b;
    s_a = getString();
    s_b = getString();

    cout<<"Please input the operator(+,-,*,/,%):"<<endl;
    string op;
    cin>>op;

    big_data_int a(s_a), b(s_b), c;

    c = calc(a, b, op);

    cout <<"Result is:"<<endl<<c.data()<<endl;

    return 0;
}
