#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. 硬编码凭证 (Hardcoded Credentials)
/**
 * Check whether the provided password matches the hardcoded admin password and announce access on success.
 *
 * Compares the given password against the built-in admin credential and prints "Access Granted!" if they match.
 *
 * @param input_pass The password to verify; compared against the hardcoded admin password "SuperSecretAdminPassword123".
 */
void check_admin(char *input_pass) {
    if (strcmp(input_pass, "SuperSecretAdminPassword123") == 0) {
        printf("Access Granted!\n");
    }
}

/**
 * Demonstrates unsafe heap allocation that can cause a null-pointer dereference and a memory leak.
 *
 * Allocates 50 bytes on the heap, writes to the first byte without checking whether allocation succeeded,
 * and returns without freeing the allocation. This may dereference a NULL pointer and results in leaked memory.
 */
void memory_issues() {
    char *ptr = (char *)malloc(50);
    
    // 错误：没有检查 malloc 是否返回 NULL 就直接使用
    ptr[0] = 'A'; 
    
    // 错误：函数结束前没有调用 free(ptr)，导致内存泄漏
    return; 
}

/**
 * Demonstrates heap corruption by performing a use-after-free followed by a double-free.
 *
 * Allocates a small heap buffer, frees it, then writes to the freed memory and frees it again,
 * causing undefined behavior and potential heap corruption.
 */
void heap_corruption() {
    char *data = (char *)malloc(10);
    free(data);
    
    // 错误：内存已被释放，但再次写入数据
    strcpy(data, "Hello"); 
    
    // 错误：再次释放同一块内存
    free(data); 
}

/**
 * Demonstrates unsafe handling of a caller-provided C string that can cause a stack buffer overflow and a format-string vulnerability.
 *
 * Copies the contents of `user_input` into a fixed 10-byte stack buffer without bounds checking, then passes `user_input` directly as the `printf` format string. This may overflow the stack buffer, cause memory corruption, allow arbitrary memory reads/writes, or crash the program.
 *
 * @param user_input Null-terminated input string provided by the caller; treated as untrusted data.
 */
void risky_processing(char *user_input) {
    char buffer[10];

    // 4. 栈缓冲区溢出 (Stack Buffer Overflow)
    // 如果 user_input 长度超过 10，会覆盖栈内存
    strcpy(buffer, user_input); 

    // 5. 格式化字符串漏洞 (Format String Vulnerability)
    // 如果 user_input 包含 "%s" 或 "%n" 等格式符，会导致崩溃或内存泄露
    printf(user_input); 
}

/**
 * Program entry point that reads a line from standard input, conditionally processes a command-line argument, and invokes demonstration routines that illustrate unsafe memory and input handling.
 * @returns 0 on normal termination.
 */
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