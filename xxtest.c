#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. 硬编码凭证 (Hardcoded Credentials)
// SAST工具会扫描特定的变量名（如 password, key）和字符串比较
void check_admin(char *input_pass) {
    if (strcmp(input_pass, "SuperSecretAdminPassword123") == 0) {
        printf("Access Granted!\n");
    }
}

// 2. 内存泄漏 (Memory Leak) & 空指针解引用 (Null Pointer Dereference)
void memory_issues() {
    char *ptr = (char *)malloc(50);
    
    // 错误：没有检查 malloc 是否返回 NULL 就直接使用
    ptr[0] = 'A'; 
    
    // 错误：函数结束前没有调用 free(ptr)，导致内存泄漏
    return; 
}

// 3. 释放后使用 (Use After Free) & 双重释放 (Double Free)
void heap_corruption() {
    char *data = (char *)malloc(10);
    free(data);
    
    // 错误：内存已被释放，但再次写入数据
    strcpy(data, "Hello"); 
    
    // 错误：再次释放同一块内存
    free(data); 
}

void risky_processing(char *user_input) {
    char buffer[10];

    // 4. 栈缓冲区溢出 (Stack Buffer Overflow)
    // 如果 user_input 长度超过 10，会覆盖栈内存
    strcpy(buffer, user_input); 

    // 5. 格式化字符串漏洞 (Format String Vulnerability)
    // 如果 user_input 包含 "%s" 或 "%n" 等格式符，会导致崩溃或内存泄露
    printf(user_input); 
}

int main(int argc, char *argv[]) {
    char local_buf[100];

    // 6. 使用了被废弃且极其危险的函数 (Use of Deprecated/Unsafe Function)
    // gets() 不检查缓冲区长度，是导致缓冲区溢出的头号杀手
    printf("Enter specific text: ");
    gets(local_buf); 

    if (argc > 1) {
        risky_processing(argv[1]);
        check_admin(argv[1]);
    }

    memory_issues();
    heap_corruption();

    // 7. 逻辑错误/死代码 (Unreachable Code)
    return 0;
    
    printf("This line will never run."); 
}
