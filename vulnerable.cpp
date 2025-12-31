#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// 1. 硬编码敏感信息 (CWE-798)
// SAST 会扫描变量名（如 api_key, secret）和高熵字符串
const string AWS_SECRET_KEY = "AKIAIOSFODNN7EXAMPLE"; 

class UserManager {
public:
    // 2. 也是硬编码，且作为类成员
    string db_password = "root";

    // 3. SQL 注入 (CWE-89)
    /**
     * @brief Builds an SQL query for a user ID and prints it.
     *
     * Constructs an SQL SELECT statement using the provided userId and outputs
     * the resulting query string to standard output.
     *
     * @param userId The user identifier used to populate the WHERE clause.
     */
    void queryUser(string userId) {
        string query = "SELECT * FROM users WHERE id = '" + userId + "'";
        cout << "Executing query: " << query << endl;
    }

    // 4. 命令注入 (CWE-78)
    /**
     * @brief Executes the system ping command targeting the given IP address or hostname.
     *
     * @param ipAddress IP address or hostname to ping; passed directly to the system shell.
     */
    void pingHost(string ipAddress) {
        string cmd = "ping -c 4 " + ipAddress;
        system(cmd.c_str());
    }
};

/**
 * @brief Copies a null-terminated C string into a fixed-size stack buffer.
 *
 * Copies the contents of `input` into a local 10-byte buffer using `strcpy`.
 * If `input` has length greater than or equal to 10 bytes (including the null
 * terminator), this will overwrite adjacent stack memory and cause undefined
 * behavior.
 *
 * @param input Null-terminated C string to copy into the local buffer.
 */
void legacyBufferOverflow(char* input) {
    char buffer[10];
    
    // 5. 经典的栈缓冲区溢出 (CWE-121)
    // 虽然是 C++，但混用 C 风格字符串处理函数非常常见且危险
    strcpy(buffer, input); 
}

/**
 * @brief Demonstrates allocation of a dynamic array without guaranteed deallocation.
 *
 * Allocates a heap array of 100 integers and may return before releasing it,
 * causing a memory leak in that early-return path.
 */
void memoryLeakAndRawPointers() {
    // 6. 内存泄漏 (CWE-401)
    // 使用了 new 但没有 delete
    int* data = new int[100];
    data[0] = 10;
    
    // 抛出异常可能导致 delete 永远不执行 (异常安全问题)
    if (data[0] == 10) {
        // throw runtime_error("Error occurred!"); 
        return; 
    }
    
    delete[] data;
}

/**
 * @brief Demonstrates iterator invalidation by modifying a vector while iterating over it.
 *
 * Iterates a small vector of integers and calls push_back during traversal when a specific
 * element is encountered. Mutating the container while iterating may reallocate the
 * underlying storage and invalidate iterators, resulting in undefined behavior or a crash.
 *
 * @note This function intentionally contains unsafe behavior to illustrate iterator
 *       invalidation (logic error).
 */
void iteratorInvalidation() {
    vector<int> numbers = {1, 2, 3, 4, 5};

    // 7. 迭代器失效 (CWE-835/Logic Error)
    // 在遍历 vector 时进行 push_back 会导致底层数组重新分配，
    // 从而使迭代器失效，导致未定义行为或崩溃。
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it == 3) {
            numbers.push_back(6); 
        }
    }
}

/**
 * @brief Generates and prints a non-cryptographic security token.
 *
 * Prints a time-seeded C-library `rand()` value to stdout in the form
 * "Security Token: <value>".
 *
 * This token is not suitable for cryptographic or security-sensitive purposes.
 */
void weakRandomness() {
    // 8. 弱伪随机数生成器 (CWE-338)
    // srand/rand 不适合用于安全相关的随机数生成
    srand(time(NULL));
    int token = rand(); 
    cout << "Security Token: " << token << endl;
}

/**
 * @brief Program entry point that invokes a set of functions demonstrating common insecure coding patterns.
 *
 * The function constructs a UserManager instance and, when provided a command-line argument,
 * passes that argument to several helper functions which exercise vulnerabilities such as
 * SQL/command injection, buffer overflow, memory-management issues, iterator invalidation,
 * and weak randomness. It returns early when required input is missing.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return int 0 on normal completion; 1 if a required command-line argument is missing.
 */
int main(int argc, char* argv[]) {
    UserManager um;

    if (argc < 2) {
        return 1;
    }

    // 模拟攻击路径
    um.queryUser(argv[1]); // 传入 "' OR '1'='1" 即可注入
    
    legacyBufferOverflow(argv[1]);
    
    memoryLeakAndRawPointers();
    
    iteratorInvalidation();
    
    weakRandomness();

    // 9. 被除数为零 (CWE-369)
    int x = 0;
    int y = 100 / x; 

    return 0;
}