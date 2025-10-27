#include <string>
#include "big_data_int.h"

string getString(){
    auto* str = new string();
    str->reserve(100);
    std::cout << "请输入内容：";
    std::cin.getline(str->c_str(), 100);  // 直接读取到缓冲区

    std::cout << "输入内容：" << str->c_str() << std::endl;

    return str;
}

int main() 
{
    cout<<"please input two numbers:"<<endl;
    string s_a, s_b;

    s_a = getString();
    s_b = getString();

    cout<<"Please input the operator(+,-,*,/,%):"<<endl;
    string op;
    cin>>op;
    big_data_int a(s_a), b(s_b), c;
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
            return -1;
    }
    cout <<"Result is:"<<endl<<c.data()<<endl;
    return 0;
}
