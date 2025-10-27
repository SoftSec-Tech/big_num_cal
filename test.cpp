#include <iostream>
#include <string>
#include "big_data_int.h"

typedef unsigned long long size_t;
extern void *malloc(size_t);
int *alloc(unsigned count);

void test44_1() { int *p = alloc(10); }  // #nodefect#RESOURCE_LEAK

int *alloc2(unsigned count) {
  if (count >= 0) {
    return (int *)malloc(count);
  }
  return 0;
}

void MyFunc() { int *p = alloc2(10); }

int main() 
{
    cout<<"please input two numbers:"<<endl;
    string s_a, s_b;
    cin>>s_a;
    cin>>s_b;

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
        // case '/':
        //     c = a / b;
        //     break;
        // case '%':
        //     c = a % b;
            break;
        default:
            cout<<"Wrong operator input"<<endl;  
            return -1;
    }

    cout <<"Result is:"<<endl<<c.data()<<endl;

    MyFunc();

    return 0;
}
