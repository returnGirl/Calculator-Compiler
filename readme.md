### 利用LL文法构造的简单计算器
#### 14331275 王镇佳

#### 功能
+ 支持 + - * / () 运算
+ 支持优先级计算
+ 允许输入空白字符

#### 首先，构造其文法如下：
```
E -> TE’
E’ -> + TE’ | -TE’ | ϵ
T -> FT’
T’ -> * FT’ | / FT’ | ϵ
F -> -F | id | (E)

其中id -> [0-9]*.[0-9]*| [0-9]+
```
在代码中用完整函数名代替
```
expr -> term expr'
expr' -> + term expr' | - term expr' | epsilon
term -> factor term'
term' -> * factor term' | / factor term' | epsilon
factor -> -factor | real | (expr)
real -> [0-9]*.[0-9]*| [0-9]+
```

#### 根据LL(1)文法构造预测分析表

|    非终结符号   |    id | +  | - | * | / | ( | ) | $
| :-------- | --------:| :--: |
| E  | E -> TE' |     | E -> TE' | | | E -> TE'| | |
| E'  | | E' -> +TE'    | E' -> -TE' | | | | E' -> ϵ  | E' -> ϵ  |
| T  | T -> FT' |     | T -> FT' | | | T -> FT'| | |
| T'  | |   T' -> ϵ   | T' -> ϵ  | T' -> *FT' | T' -> /FT' | | T' -> ϵ | T' -> ϵ |
| F  | F -> **id** |     | F -> -F | | | F -> (E)| | | |

##### 最后根据此表完成对应函数
```cpp
double expr(void);
double expr_(void); // means E'
double term(void);
double term_(void); // means T'
double factor(void);
void errorHandler(void);
```

#### 运行

c语言实现
编译环境：gcc

运行方法：
```makefile
make clean
make
./bin/Calc
```
