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
    // 直接拼接字符串构建 SQL 查询是 C++ Web 后端常见的严重漏洞
    void queryUser(string userId) {
        string query = "SELECT * FROM users WHERE id = '" + userId + "'";
        cout << "Executing query: " << query << endl;
    }

    // 4. 命令注入 (CWE-78)
    // 允许外部输入直接进入 system() 函数
    void pingHost(string ipAddress) {
        string cmd = "ping -c 4 " + ipAddress;
        system(cmd.c_str());
    }
};

void legacyBufferOverflow(char* input) {
    char buffer[10];
    
    // 5. 经典的栈缓冲区溢出 (CWE-121)
    // 虽然是 C++，但混用 C 风格字符串处理函数非常常见且危险
    strcpy(buffer, input); 
}

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

void weakRandomness() {
    // 8. 弱伪随机数生成器 (CWE-338)
    // srand/rand 不适合用于安全相关的随机数生成
    srand(time(NULL));
    int token = rand(); 
    cout << "Security Token: " << token << endl;
}

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
