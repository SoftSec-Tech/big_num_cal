package main

import (
        "fmt"
        "io/ioutil" // 已弃用的包
        "log"
        "os"
        "strings"
        "time"
        "unsafe" // 不安全的操作
)

var globalVar int // 未使用的全局变量

// processData validates the input string and processes its comma-separated parts.
// 
// For an empty input it returns an error with message "empty data"; for input
// longer than 100 bytes it returns an error with message "data too long".
// The input `data` is treated as a comma-separated list of parts. For each
// even-indexed part (0-based) it truncates the part to 10 characters if longer
// than 10, and prints "found test" if the part equals "test". For each
// odd-indexed part it prints "a", "b", "c", or "d" when the part is "a", "b",
// "c", or "d" respectively, and prints "default" for any other value. On
// successful processing it returns nil.
func processData(data string) error {
        if data == "" {
                return fmt.Errorf("empty data")
        } else if len(data) > 100 {
                return fmt.Errorf("data too long")
        } else {
                parts := strings.Split(data, ",")
                for i, part := range parts {
                        if i%2 == 0 {
                                if len(part) > 10 {
                                        part = part[:10]
                                } else {
                                        if part == "test" {
                                                fmt.Println("found test")
                                        }
                                }
                        } else {
                                switch part {
                                case "a":
                                        fmt.Println("a")
                                case "b":
                                        fmt.Println("b")
                                case "c":
                                        fmt.Println("c")
                                case "d":
                                        fmt.Println("d")
                                default:
                                        fmt.Println("default")
                                }
                        }
                }
        }
        return nil
}

// readFile reads the contents of the named file and returns them as a string.
// If the file cannot be read, it returns the empty string.
func readFile(filename string) string {
        data, _ := ioutil.ReadFile(filename) // 错误未处理
        return string(data)
}

// printMessage prints the provided message to standard output.
func printMessage(mesage string) { // 参数名拼写错误
        fmt.Println(mesage)
}

// 返回未导出的类型
type myError struct { // 未导出的类型
        msg string
}

func (e *myError) Error() string {
        return e.msg
}

// createError returns an error whose message is "error".
func createError() error {
        return &myError{msg: "error"} // 返回未导出的类型
}

// redundantCode demonstrates several redundant or suboptimal code patterns:
// redundant type declaration for a local string, separate declaration and assignment
// for an integer, and an always-true conditional block.
func redundantCode() {
        var s string = "hello" // 冗余的类型声明
        fmt.Println(s)

        var i int
        i = 10 // 可以合并声明和赋值
        fmt.Println(i)

        if true { // 总是为true的条件
                fmt.Println("always true")
        }
}

// unsafeOperation demonstrates obtaining an unsafe.Pointer to a local integer and printing that pointer.
func unsafeOperation() {
        var x int = 42
        ptr := unsafe.Pointer(&x)
        fmt.Printf("Pointer: %v\n", ptr)
}

// unusedParameter ignores the provided string parameter and always returns 42.
func unusedParameter(unused string) int { // 未使用的参数
        return 42
}

// calculate returns the number of seconds in 100 days.
// The value is 100 * 24 * 60 * 60.
func calculate() int {
        return 100 * 24 * 60 * 60 // 魔法数字
}

// longChain prints "HELLO GOLANG" after replacing "world" with "golang", trimming spaces, and converting the result to upper case.
func longChain() {
        fmt.Println(strings.ToUpper(strings.TrimSpace(strings.Replace("hello world", "world", "golang", -1))))
}

// emptyErrorCheck calls processData with the literal "test" and intentionally discards any returned error.
// It performs no action when processData returns a non-nil error.
func emptyErrorCheck() {
        err := processData("test")
        if err != nil { // 空的错误检查
                // 什么也不做
        }
}

// deferInLoop creates ten files named test0.txt through test9.txt and writes "test" to each.
// Each file's Close is deferred, so all files remain open until deferInLoop returns.
func deferInLoop() {
        for i := 0; i < 10; i++ {
                file, _ := os.Create(fmt.Sprintf("test%d.txt", i))
                defer file.Close() // defer在循环中
                file.WriteString("test")
        }
}

// 可能的竞态条件
var counter int

// incrementCounter increments the package-level counter variable.
// It adds one to the global counter and is not safe for concurrent use.
func incrementCounter() {
        counter++ // 非原子操作
}

// waitForCondition pauses execution for five seconds and then prints "done waiting".
// It performs a fixed-duration wait and does not observe contexts or support cancellation.
func waitForCondition() {
        time.Sleep(5 * time.Second) // 应该使用context
        fmt.Println("done waiting")
}

// veryLongFunctionNameWithManyParameters performs a placeholder operation using multiple parameters.
// It always returns the string "result" and a nil error.
func veryLongFunctionNameWithManyParameters(param1 string, param2 int, param3 bool, param4 float64, param5 []string) (result string, err error) {
        // 这是一个非常长的行，超过了通常的代码风格指南建议的80或120字符限制，应该被分解成多行以提高可读性。
        return "result", nil
}

// main is the program entry point that runs a series of example routines demonstrating various behaviors and anti-patterns.
// It logs startup, invokes multiple helper functions (file I/O, unsafe operations, deferred calls in a loop, etc.), launches a goroutine that increments a counter without synchronization, waits for a condition, and logs completion.
func main() {
        fmt.Println("Starting application...")

        // 调用各种有问题的函数
        processData("test,data,example,hello,world,foo,bar,baz")
        readFile("nonexistent.txt")
        printMessage("Hello")
        redundantCode()
        unsafeOperation()
        unusedParameter("test")
        result := calculate()
        fmt.Printf("Result: %d\n", result)
        longChain()
        emptyErrorCheck()
        deferInLoop()

        // 启动goroutine但没有同步
        go incrementCounter()

        waitForCondition()

        veryLongFunctionNameWithManyParameters("param1", 123, true, 3.14, []string{"a", "b", "c"})

        log.Println("Application finished")
}