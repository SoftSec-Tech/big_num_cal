<?php
// 文件名: problematic_code.php

// 未使用的 use 语句 (Unused Code Rules)
use DateTime;
use InvalidArgumentException;

// 全局变量 (Global Variables)
$globalCounter = 0;
$debugMode = true;

class UserManager
{
    // 过长的类名 (Naming Rules) - 超过45字符
    private $thisIsAVeryLongVariableNameThatExceedsTheRecommendedLength = 42;

    // 未使用的属性 (Unused Code Rules)
    private $unusedProperty;

    /**
     * Initialize a new UserManager instance.
     *
     * Intentionally empty constructor.
     */
    public function __construct()
    {
        // 空构造函数 (Unused Code Rules)
    }

    /**
     * Filter and return users who meet age, country, and subscription criteria.
     *
     * Processes the provided user records and returns those accepted by the selection
     * rules (age > 18; country is 'US' with 'premium' or 'basic' subscription, or
     * country is 'CA'). When $verbose is true, processing messages may be emitted.
     *
     * @param array $users Array of user records. Each record is expected to contain the keys
     *                     `id`, `name`, `email`, `age`, `country`, `subscription`, and `active`.
     * @param bool $verbose When true, emit processing messages for diagnostic purposes.
     * @return array The list of user records that satisfy the selection criteria.
     *
     * Side effects: increments the global $globalCounter.
     */
    public function processUserData(array $users, bool $verbose = false): array
    {
        // 未使用的参数 (Unused Code Rules)
        $unusedParam = "I'm never used";

        // 局部变量未使用 (Unused Code Rules)
        $tempResult = [];

        // 重复代码块 (Code Clones)
        for ($i = 0; $i < count($users); $i++) {
            if ($users[$i]['active']) {
                $tempResult[] = $users[$i]['name'];
            }
        }

        // 另一个重复代码块 (Code Clones)
        $anotherTemp = [];
        for ($j = 0; $j < count($users); $j++) {
            if ($users[$j]['active']) {
                $anotherTemp[] = $users[$j]['email'];
            }
        }

        // 高圈复杂度 (Cyclomatic Complexity)
        $result = [];
        foreach ($users as $user) {
            if ($user['age'] > 18) {
                if ($user['country'] === 'US') {
                    if ($user['subscription'] === 'premium') {
                        if ($verbose) {
                            echo "Processing premium US user over 18\n";
                        }
                        $result[] = $user;
                    } elseif ($user['subscription'] === 'basic') {
                        if ($verbose) {
                            echo "Processing basic US user over 18\n";
                        }
                        $result[] = $user;
                    } else {
                        if ($verbose) {
                            echo "Skipping non-standard subscription\n";
                        }
                    }
                } elseif ($user['country'] === 'CA') {
                    if ($verbose) {
                        echo "Processing Canadian user over 18\n";
                    }
                    $result[] = $user;
                } else {
                    if ($verbose) {
                        echo "Skipping non-US/CA user over 18\n";
                    }
                }
            } else {
                if ($verbose) {
                    echo "Skipping user under 18\n";
                }
            }
        }

        // 注释掉的代码 (Commented Code)
        /*
        $oldResult = [];
        foreach ($users as $u) {
            $oldResult[] = $u['id'];
        }
        */

        // 不必要的全局变量使用
        global $globalCounter;
        $globalCounter++;

        // 避免使用 @ 抑制错误
        $fileContent = @file_get_contents('non_existent_file.txt');

        // 未处理的异常
        try {
            $date = new DateTime('invalid date');
        } catch (Exception $e) {
            // 空catch块
        }

        // 可疑的魔法数字
        if (count($result) > 10) {
            // ...
        }

        // 返回临时变量
        return $result;
    }

    /**
     * Create a new user record from the provided attributes.
     *
     * @param string $firstName The user's first name.
     * @param string $lastName The user's last name.
     * @param string $email The user's email address.
     * @param string $phone The user's phone number.
     * @param string $address The user's street address.
     * @param string $city The user's city.
     * @param string $state The user's state or region.
     * @param string $zipCode The user's postal or ZIP code.
     * @param string $country The user's country.
     * @param bool $isActive Whether the user is active.
     * @param bool $isAdmin Whether the user has administrative privileges.
     * @return array The created user represented as an associative array of the provided attributes.
     */
    public function createUser(
        string $firstName,
        string $lastName,
        string $email,
        string $phone,
        string $address,
        string $city,
        string $state,
        string $zipCode,
        string $country,
        bool $isActive = true,
        bool $isAdmin = false
    ): array {
        // 函数体为空 (Empty Function Body)
    }

    /**
     * Classifies an integer into a descriptive category based on its sign, magnitude, and parity.
     *
     * @param int $value The integer to classify.
     * @return string "Special case" if $value is a positive even number not equal to 4; "Even number" if $value is 4; "Odd number" if $value is positive and odd; "Large number" if $value is 10 or greater; "Non-positive" if $value is zero or negative.
     */
    public function nestedIfExample(int $value): string
    {
        if ($value > 0) {
            if ($value < 10) {
                if ($value % 2 === 0) {
                    if ($value !== 4) {
                        return "Special case";
                    } else {
                        return "Even number";
                    }
                } else {
                    return "Odd number";
                }
            } else {
                return "Large number";
            }
        } else {
            return "Non-positive";
        }
    }
}

// 未使用的类 (Unused Code Rules)
class UnusedClass
{
    /**
     * Echoes the literal string "I'm never called!" to the output.
     *
     * This method performs a direct output side effect and does not return a value.
     */
    public function doSomething()
    {
        echo "I'm never called!";
    }
}

// 匿名类 (Anonymous Class)
$anonymous = new class {
    /**
     * Outputs a greeting message from the anonymous class.
     */
    public function greet()
    {
        echo "Hello from anonymous class!";
    }
};

// 未使用的函数 (Unused Code Rules)
function unusedFunction(): void
{
    echo "This function is never called";
}

// 主程序逻辑
$manager = new UserManager();
$users = [
    ['id' => 1, 'name' => 'Alice', 'email' => 'alice@example.com', 'age' => 25, 'country' => 'US', 'subscription' => 'premium', 'active' => true],
    ['id' => 2, 'name' => 'Bob', 'email' => 'bob@example.com', 'age' => 17, 'country' => 'UK', 'subscription' => 'free', 'active' => true],
    ['id' => 3, 'name' => 'Charlie', 'email' => 'charlie@example.com', 'age' => 30, 'country' => 'CA', 'subscription' => 'basic', 'active' => false],
];

// 忽略返回值 (Unused Result)
$manager->processUserData($users, true);

// 使用 eval (Security Issue)
eval('$x = 5 + 3;');

// 直接输出敏感信息
echo "Debug mode is " . ($debugMode ? 'ON' : 'OFF');

// 结束
?>