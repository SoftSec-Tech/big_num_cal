
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_BUFFER 10

void buffer_overflow_vuln(char* user_input) {
    char buffer[MAX_BUFFER];
    strcpy(buffer, user_input); 
}


int integer_overflow_vuln(int count, int size) {
    int total_bytes = count * size; 
    return total_bytes;
}

void memoryLeakVuln() {
    int* data = new int[100];
    if (data == nullptr) return;

    data[0] = 1;
    std::cout << "Memory allocated and leaked." << std::endl;
}
void memoryLeakVuln2() {
    int* data = new int[100];
    if (data == nullptr) return;

    data[0] = 1;
  delete[] data;
    std::cout << "Memory allocated and leaked." << std::endl;
}
void memoryLeakVuln3() {
    int* data = new int[100];
    if (data == nullptr) return;

    data[0] = 1;
  delete data;
    std::cout << "Memory allocated and leaked." << std::endl;
}

int main(int argc, char* argv[]) {
    buffer_overflow_vuln(argv[1]);
    int result = integer_overflow_vuln(INT_MAX, 2);
    return 0;

}
