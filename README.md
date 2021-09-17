### 代码规范
> 个人版本

#### 缩进

- 所有次一级的代码块必须缩进，使用制表符而非空格
  ```
  if( num == 100 ) {
      doSomething();
      // ···
  }
  // 正确示例

  myFunction( int num1, int num2 ) {
    doSomething();
    // ···
  }
  // 错误示例
  ```
#### 变量命名规则
- 普通变量。
  采用全小写形式，每个单词必须用下划线 `_` 分隔开来。并且除了专有词汇，所有变量名一律采用英文书写，摒弃拼音与英文混杂或纯拼音的形式。数字必须标注在末尾。
  ```
  int student_date; // 正确
  int StudentDate;  // 错误
  int xueshengDate; // 错误
  int taobao_user_data; //正确
  ```
  除了日常常见词汇和专业常用词汇以外，所有变量命名不采用缩写，避免可读性的降低。
  ```
  int num; // 正确，代码中常用
  int sql_driver; // 正确
  int string_cont; // 错误，缩写引起歧义
  int string_context; // 正确
  ```
- 类成员变量。
  成员变量除了遵循普通变量命名规则以外，变量名需以下划线 `_` 结尾。

- 结构体变量。
  遵循普通变量命名规则。

- 自定义类型。
  大写字母开头的驼峰命名法，单词以下划线间隔。
  自定义结构体的别名，应当以类型名去掉下划线为准。

#### 每行最多字数

- 最多每行60个字符，包括注释在内。
  除了自然换行外，还可以采用函数拆分换行的形式。
  ```
  void longLongLongLongLongLongLongFunction( int num1,
                                             int num2,
                                             int num3 ) {
      doSomething();
  }
  // 正确。

  void longLongLongLongLongLongLongFunction(
      int long_long_long_num1,
      int long_long_long_num2,
      int long_long_long_num3,
  ) {
      doSomething();
  }
  // 正确。
  ```
#### 函数/代码块最大行数
- 20行。
  如果内容过多，需按逻辑封装成函数。

#### 函数/类命名
- 函数命名。
  采用驼峰命名法，且首字母小写。
  ```
  addTableItem();
  deleteLine();
  checkContext();
  ```
- 类命名。
  采用驼峰命名法，且首字母大写。
  ```
  class UrlChecker { ... }
  class NameSelect { ... }
  ```
#### 常量命名
- 常量。
  以 `K_`开头，后接部分以驼峰命名法命名，且首字母小写。
  ```
  const K_studentMaxNum = 100;
  ``` 
#### 空行
- 必要空行。
  两段函数的定义之间必须留以空行。
  代码块，数据定义段和程序段必须留以空行。特别说明，除非有特别严格的执行顺序要求，一个代码块中的定义段和程序段必须分离。
  ```
  void userGet () {
      ...
      ...
      ...
  }

  void userCheck () {
      int num1;
      int num2;
      int num3;
      ...
      ...

      userGet();
      userGet();
      if ( ... ) {
          ...
      } else {
          ...
      }
      ...
      ...
  }
  ```
#### 注释规则
- 注释风格。
  使用 `//` 而非 `/* */` 。同时尽可能保证同语段的注释区 `//` 对齐。注释以中文优先。在代码块前的是解释性注释，代码后的是评价性注释。
  ```
                            //<--留白一行
  //这个函数的作用
  void myFunction() {
      ...
  }
  //这个函数的效率等
  ```
                            //<--留白一行
- 函数注释。
  除非函数非常简单，否则应当指出：
  - 函数的输入输出.
  - 对类成员函数而言: 函数调用期间对象是否需要保持引用参数, 是否会释放这些参数.
  - 函数是否分配了必须由调用者释放的空间.
  - 参数是否可以为空指针.
  - 是否存在函数使用上的性能隐患.
  - 如果函数是可重入的, 其同步前提是什么?

#### 水平留白
- 操作符。
  `()` 和 `{}` 除非内容为空，否则向内留左右各留一个空格；`;` 和 `,` 只有右侧留以空格； 各种运算符和操作数之间，必须留以空格隔开。
- 声明对齐。
  除非数据段的声明具有良好的对齐效果，可采用空格以外，一律采用制表符对齐。
  ```
  int num1;
  int num2;
  int other_num;
  //正确

  int       other_num1   = 3;
  int       big_num2     = 6;
  char      my_char      = 'A';
  string    hello_world  = "hello world!";

  //正确
  ```