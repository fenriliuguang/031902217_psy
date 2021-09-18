## 第一次个人编程作业

| 软件工程A | [福州大学软件工程社区](https://bbs.csdn.net/forums/fzuSoftwareEngineering2021) |
| ----------------- |--------------- | 
| 这个作业要求在哪里| [2021秋软工实践第一次个人编程作业](https://bbs.csdn.net/topics/600574694) | 
| 这个作业的目标 | 完善代码风格约束，练习社区使用，代码实现关键字统计 |
| 学号 | [031902217](https://blog.csdn.net/qq_54903139) |


#### 任务分解
- WBS
  ![WBS](https://img-blog.csdnimg.cn/20210919030427391.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA54Sa5pel5rWB5YWJ,size_15,color_FFFFFF,t_70,g_se,x_16)

  - 将代码任务分解为三个过程：
    1.用户的输入输出
    2.文件的读入
    3.字符串分析过程

    并利用面向对象的方式重构任务，使后续代码的维护更加简便高效。

#### PSP

  |PSP Stages|估计时间/h|完成时间/h|
  |:--:|:--:|:--:|
  |计划|0.2|0.2|
  |时间预估|0.1|0.3|
  |开发| - | - |
  |需求分析| 4 | 5 |
  |生成设计文档|-|-|
  |设计复审| - | - |
  |代码规范| 2 | 3 |
  |具体设计| 3 | 2 |
  |具体编码| 20 | 16|
  |代码复审| - | - |
  |test| 1 | 1 |
  |报告| 2 | 1 |
  |测试报告| - | - |
  |计算工作量| 0.1 |0.1|
  |总结与提高|2|1|
  |总计|34.4|29.6|

#### 工作迭代过程

  ![迭代图](https://img-blog.csdnimg.cn/20210919030443332.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA54Sa5pel5rWB5YWJ,size_19,color_FFFFFF,t_70,g_se,x_16)

#### 代码风格约束
 - 参考自 [《谷歌C++开源项目风格指南》](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)，并生成了自己的代码约束，详见[ 个人代码规范 ](https://github.com/fenriliuguang/031902217_psy/blob/master/README.md) 。

#### 实际编码过程
  > 面向对象的编程方式，令代码的修改和维护变得高效
  - 常量与结构体
    ```
    // 定义需要查找的关键字
    const string K_keyWord[32] = { ...
    // 用户的输入数据
    struct Input { ...
    // 每个switch包含的case组成的链表
    struct CaseCount { ...
    // 整理后的关键字信息和后续可能有用的判别值
    struct OutputDate { ...
    // 符号判别标志
    struct Flags { ...
    ```
  - 用户输入输出类

     实现简洁高效的cli界面。定义成员函数 `prompt()`和`output()`分别完成用户输入数据的整理和已处理的数据的输出。
      ```
      class CilIo {
        public:
          Input   prompt();
          void    output( OutputDate *output_date ); 
      };
      ```
  - 关键字处理类

    实现读入的 c 文件字符串合法单词截取 `KeyWord()`、
    switch-case组的判别 `switchCaseCheck()`、
    if-else及if-else_if-else组的判别 `ifElseCheck()`、 关键词计数 `keyCount()`。

  - 核心代码逻辑实现

    1.注释和字符串忽略
    >采用逐字符识别的方式
    ```
    // in symbolIgnore()
    if( c[i-1] == '"') {
        f->quo_flag = !f->quo_flag;
    }
    if( c[i-1] == '/' && c[i] == '*') {
        f->slash_star_flag = true;
    }
    if( c[i] == '/' && c[i-1] == '*') {
        f->slash_star_flag = false;
    }
    if( c[i-1] == '/' && c[i] == '/') {
        f->dou_slash_flag  = true;
    }
    if( c[i] == '\n' )f->dou_slash_flag = false;

    return (f->dou_slash_flag||
            f->quo_flag||
            f->slash_star_flag);
    ```
    2.Switch-case组判别
    > 采用链表的形式实现多个switch结构的统计，并方便输出。
    > 目前没有考虑到多层嵌套，理想的解决方案是用栈实现匹配，用链表或队列存储数据
    ```
    // in switchCaseCheck()
    if( w == "switch" ) {
        if( o->node == nullptr)o->node = o->case_head;
        else {
            o->node->next = new CaseCount;
            o->node->next->count = 0;
            o->node->next->next = nullptr;
            o->node = o->node->next;
        }
    }
    if( w == "case" ) {
        o->node->count++;
    }
    ```
    3.if与else相关的判别。
    > 利用典型if—else对的堆栈识别法的变形。遇到`if`入栈`1`，遇到 `else if` 入栈`2`, 遇到 `else` 出栈并根据出栈数据判断何种结构的计数增加
    ```
    // in ifElseCheck()
    if( w == "if" ) {
        char *p = c - 3;
        while( *p == ' ' || *p == '\n' ) {
            p--;
        }
        if( *p == 'e' ) {
            o->if_else_stack->push(2);
        }else {
            o->if_else_stack->push(1);
        }
    }
    if( w == "else" ) {
        char *p = c;
        while( *p == ' ' || *p == '\n' ) {
            p++;
        }
        if( !( *p == 'i' && *(p+1) == 'f') ) {
            int i;
            i = o->if_else_stack->top();
            o->if_else_stack->pop();
            switch (i)
            {
            case 1:
                o->if_else_count++;
                break;
            case 2:
                o->if_else_if_else_count++;
            default:
                break;
            }
        }
    }
    ```

  - 其他相关代码请参考 [源码](https://github.com/fenriliuguang/031902217_psy/blob/master/code_1/src/main.cpp) 。

#### 代码分析

- 单元测试。
  ![测试用例1](https://img-blog.csdnimg.cn/20210919030224652.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA54Sa5pel5rWB5YWJ,size_20,color_FFFFFF,t_70,g_se,x_16)
  > [测试用例1](https://github.com/fenriliuguang/031902217_psy/blob/master/code_1/static/test1.c) 的代码覆盖率结果

  ![测试用例2](https://img-blog.csdnimg.cn/20210919030211251.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA54Sa5pel5rWB5YWJ,size_20,color_FFFFFF,t_70,g_se,x_16)
  > [测试用例2](https://github.com/fenriliuguang/031902217_psy/blob/master/code_1/static/test2.c) 的代码覆盖率结果

  可以看到，本代码当测试用例足够复杂，且查询等级为4的情况下，代码覆盖率能达到100%。

- 性能分析

  主要占用资源的是输入输出和文件读取。另外，头文件`<stack>` 的堆栈操作也是性能消耗的主要内容。

  ![性能分析](https://img-blog.csdnimg.cn/20210919030304514.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA54Sa5pel5rWB5YWJ,size_20,color_FFFFFF,t_70,g_se,x_16)

#### 困难及解决途径
> 面向百度的程序设计

- `c++` 在` Visual Studio ` 环境下和 `vscode`的gcc插件环境下，对代码检测报错不同，虽然都能编译成功，但是前者严格的代码规范还是让我吃了不少苦头。
- c++的性能分析目前最好的是运行在vs上，花了不少时间来学习如何熟练运用它，但是仍然没有能够利用它完成代码单元测试，并运用到实际的编程与维护中去。
- 大部分关于开发的内容是什么都不懂的，网上查阅资料＋看书才能勉强有些门路。

#### 用到的工具

  - vscode
    - [PlantUML](https://plantuml.com/zh/)
  - Visual Studio 2019
