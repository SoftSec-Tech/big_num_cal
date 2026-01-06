import time

# 1. 逻辑/语法错误：函数定义缺少冒号，且缩进不规范
def calculate_discount(price, discount)
    final_price = price * (1 - discount)
   return final_price  # 缩进错误

# 2. 陷阱：使用可变对象（列表）作为默认参数
def add_item_to_cart(item, cart=[]):
    cart.append(item)
    return cart

class User:
    # 3. 拼写错误：初始化方法写成了 _init_ 而不是 __init__
    def _init_(self, name, age):
        self.name = name
        self.age = age

    def greet(self):
        # 4. 类型错误：尝试将字符串和整数直接连接
        print("Hello, I am " + self.name + " and I am " + self.age + " years old.")

def main():
    print("Welcome to the shop!")
    
    # 5. 逻辑错误：运算符误用 (^ 在 Python 中是异或，不是幂运算)
    square_area = 10 ^ 2 
    print(f"Area calculation check: {square_area}") 

    # 6. 语法错误：在 if 条件中使用了赋值运算符 (=) 而不是比较运算符 (==)
    user_input = "yes"
    if user_input = "yes":
        print("User agreed.")

    # 7. 运行时错误：IndexError (索引越界)
    items = ["Apple", "Banana", "Orange"]
    for i in range(len(items) + 1):
        print(f"Item {i}: {items[i]}")

    # 8. 运行时错误：ZeroDivisionError (除以零)
    count = 0
    total = 100
    average = total / count
    print("Average: " + average)

# 9. 拼写错误：name 变量拼写错误
if __name__ == "__main__":
    mian()