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

// 过长的函数（圈复杂度高）
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

// 未处理的错误
func readFile(filename string) string {
        data, _ := ioutil.ReadFile(filename) // 错误未处理
        return string(data)
}

// 拼写错误的参数名
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

func createError() error {
        return &myError{msg: "error"} // 返回未导出的类型
}

// 冗余的代码
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

// 使用不安全操作
func unsafeOperation() {
        var x int = 42
        ptr := unsafe.Pointer(&x)
        fmt.Printf("Pointer: %v\n", ptr)
}

// 未使用的参数
func unusedParameter(unused string) int { // 未使用的参数
        return 42
}

// 魔法数字
func calculate() int {
        return 100 * 24 * 60 * 60 // 魔法数字
}

// 冗长的函数调用链
func longChain() {
        fmt.Println(strings.ToUpper(strings.TrimSpace(strings.Replace("hello world", "world", "golang", -1))))
}

// 空的错误检查
func emptyErrorCheck() {
        err := processData("test")
        if err != nil { // 空的错误检查
                // 什么也不做
        }
}

// defer 在循环中
func deferInLoop() {
        for i := 0; i < 10; i++ {
                file, _ := os.Create(fmt.Sprintf("test%d.txt", i))
                defer file.Close() // defer在循环中
                file.WriteString("test")
        }
}

// 可能的竞态条件
var counter int

func incrementCounter() {
        counter++ // 非原子操作
}

// 使用 time.Sleep 而不是 context
func waitForCondition() {
        time.Sleep(5 * time.Second) // 应该使用context
        fmt.Println("done waiting")
}

// 过长的行
func veryLongFunctionNameWithManyParameters(param1 string, param2 int, param3 bool, param4 float64, param5 []string) (result string, err error) {
        // 这是一个非常长的行，超过了通常的代码风格指南建议的80或120字符限制，应该被分解成多行以提高可读性。
        return "result", nil
}

// 主函数
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
