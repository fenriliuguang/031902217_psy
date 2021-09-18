#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctype.h>

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

struct Input {
    // 文件路径
    string  file_path;
    // 查询等级
    int     level;     
};

struct CaseCount {
    int count;
    CaseCount *next;
};

struct OutputDate {
    int         sum;
    int         level;
    int         key_count[32];
    int         if_else_count;
    int         if_else_if_else_count;
    bool        switch_flag;
    int         else_if_flag;
    CaseCount   *case_head;
};

// cil面向用户界面
class CilIo {
    public:
        Input   prompt();
        void    output( OutputDate *output_date ); 
};

void CilIo :: output( OutputDate *o ) {
    CaseCount *node = o->case_head;

    cout << endl;
    cout << "Total              num: " << o->sum << endl;
    cout << "Switch             num: " << o->key_count[25] << endl;
    cout << "Case               num:";
    while( node->next != nullptr ){
        cout << " " << node->count;
        node = node->next;
    }
    cout << endl;
    cout << "if                 num: " << o->key_count[15] << endl;
    cout << "if-else            num: " << o->if_else_count << endl;
    cout << "if-else_if-else    num: " << o->if_else_if_else_count << endl;
}

// 关键字提取器
class KeyWordGetter {
    private: 
        OutputDate  output_data;
        void        keyCount( OutputDate *o, string w,
                                              char *c );
    public:
        OutputDate *keyWord( string context, int l );
};

// 关键字计数，已完成
void KeyWordGetter :: keyCount( OutputDate *o, string w,
                                               char *c ){
    CaseCount *node = o->case_head;

    cout << w << ' ';
    while( node->next != nullptr ) {
         node = node->next;
    }
    if( w == "switch" ) o->switch_flag = true;
    if( w == "case" ) {
        if( !o->switch_flag ){
            node->count++;
        } else {
            node->next = new CaseCount{
                count : 0,
                next : nullptr
            };
            o->switch_flag = false;
        }
    }
    if( w == "if" ) {
        char *p = c - 3;
        while( *p == ' ') {
            p--;
        }
        if( *p == 'e' ) {
            o->else_if_flag ++;
        }
    }
    if( w == "else" ) {
        if( o->else_if_flag == 1 ) {
            o->if_else_if_else_count++;
        } else if(o->else_if_flag == 0) {
            o->if_else_count++;
        }
    }
    for(int i = 0; i < 32; i++) {
        if( K_keyWord[i] == w) {
            o->key_count[i]++;
            o->sum++;
            cout << o->sum << " ";
        }
    }
    cout << endl;
}

// 单词提取，已完成
OutputDate *KeyWordGetter :: keyWord( string c, int l ) {
    int         index;
    bool        flag;
    bool        quo_flag = false;
    bool        dou_slash_flag = false;
    bool        slash_star_flag = false;

    OutputDate *out = new OutputDate{
        sum : 0,
        level : 0,
        key_count : {0},
        if_else_count : 0,
        if_else_if_else_count :0,
        switch_flag : false,
        else_if_flag : 0,
        case_head : new CaseCount {
            count : 0,
            next : nullptr
        }
    };
    for( int i = 1; i < c.size(); i++ ) {
        if( c[i-1] == '"') {
            quo_flag = !quo_flag;
        }
        if( c[i-1] == '/' && c[i] == '*') {
            slash_star_flag = true;
        }
        if( c[i] == '/' && c[i-1] == '*') {
            slash_star_flag = false;
        }
        if( c[i-1] == '/' && c[i] == '/') {
            dou_slash_flag  = true;
        }
        if( c[i] == '\n' )dou_slash_flag = false;
        if( !isalpha( c[i-1] ) && isalpha( c[i] ) ) { 
            index = i;
        }
        if(dou_slash_flag||quo_flag||slash_star_flag)continue;
        if( !isalpha( c[i] ) && isalpha( c[i-1] ) ) {
            keyCount(
                out, 
                c.substr( index, i - index),
                &(c[i])
            );
        }
    }

    return out;
}

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
    KeyWordGetter key_word;
    OutputDate *output_date;

    input = cil_io.prompt();
    context = fileReader( input.file_path );
    cout << context;
    output_date = key_word.keyWord( context, input.level);
    cil_io.output( output_date );
    return 0;
}
