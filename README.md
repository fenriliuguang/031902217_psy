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
  采用全小写形式，每个单词必须用下划线 `_` 分隔开来。并且除了专有词汇，所有变量名一律采用英文书写，摒弃拼音与英文混杂或纯拼音的形式。
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