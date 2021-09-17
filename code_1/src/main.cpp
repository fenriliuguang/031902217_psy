#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

const string K_keyWord[32] = {
    "auto", "break", "case","char",
    "const", "continue", "default", "do",
    "double", "else", "enum", "extern",
    "float", "for", "goto", "if",
    "int", "long", "register", "return",
    "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

typedef struct Input {
    // 文件路径
    string  file_path;
    // 查询等级
    int     level;     
};

typedef struct CaseCount {
    int count;
    CaseCount *next;
};

typedef struct outputDate {
    int         key_count[32];
    int         if_else_flag;
    int         if_else_count;
    int         if_else_if_else_count;
    CaseCount   *case_head;
};

// cil面向用户界面
class CilIo {
    public:
        Input   prompt();
        void    output( int level ); 
};

// 关键字提取器
class KeyWordGetter {
    private: 
        int key_count[32];
        CaseCount *case_head;
        int if_else_flag;
        int if_else_count;
        int if_else_if_else_count;
};

// 用户输入，已完成。
Input CilIo :: prompt() {
    Input UserInput;

    cout << "输入文件路径" << endl;
    cin >> UserInput.file_path;
    cout << "输入查询等级" << endl;
    cin >> UserInput.level;
    cout << "请稍候 ... " << endl;
    return UserInput;
}

// 文件读取，返回c文件字符串，已完成
string fileReader( string path ) {
    fstream c_file;

    c_file.open( path , ios :: in);
    stringstream buffer;
    buffer << c_file.rdbuf();
    return buffer.str();
}

int main() {
    CilIo   cil_io;
    Input   input;
    string  context;

    input = cil_io.prompt();
    context = fileReader( input.file_path );
    cout << context;
    return 0;
}
