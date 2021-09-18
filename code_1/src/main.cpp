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
    CaseCount   *node;
};

struct Flags {
    bool        quo_flag = false;
    bool        dou_slash_flag = false;
    bool        slash_star_flag = false;
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
    if( o->level >= 2 ) {
        cout << "Switch             num: " 
             << o->key_count[25] << endl;
        cout << "Case               num:";
        while( node != nullptr ){
            cout << " " << node->count;
            node = node->next;
        }
        cout << endl;
    }
    if( o->level >= 3 ) {
        cout << "if-else            num: "
             << o->if_else_count << endl;
    }
    if( o->level == 4) {
        cout << "if-else_if-else    num: "
             << o->if_else_if_else_count << endl;
    }
}

// 关键字提取器
class KeyWordGetter {
    private: 
        OutputDate  output_data;
        bool        symbolIgnore(
            string c, int i, Flags *f);
        void        keyCount( 
            OutputDate *o, string w );
        void        switchCaseCheck( 
            OutputDate *o, string w );
        void        ifElseCheck(
            OutputDate *o, string w, char *c );
    public:
        OutputDate *keyWord( string context, int l );
};

// 排除‘ /* */ ’、 ‘ // ’ 和 ‘ "" ’ 的影响。
bool KeyWordGetter :: symbolIgnore(
    string c, int i, Flags *f) {

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
}

// 对switch-case组的检索
void KeyWordGetter :: switchCaseCheck( 
    OutputDate *o, string w) {
    if( w == "switch" ) {
        if( o->node == nullptr)o->node = o->case_head;
        else {
            cout << "caseline"<< endl;
            o->node->next = new CaseCount {
                count : 0,
                next : nullptr
            };
            o->node = o->node->next;
        }
    }
    if( w == "case" ) {
        o->node->count++;
    }
}

// 对if-else ，if-else-if——else 的检索，未完成。
void KeyWordGetter :: ifElseCheck(
    OutputDate *o, string w, char *c) {
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
}

// 关键字计数，已完成
void KeyWordGetter :: keyCount( 
    OutputDate *o, string w ){
    for(int i = 0; i < 32; i++) {
        if( K_keyWord[i] == w) {
            o->key_count[i]++;
            o->sum++;
        }
    }
}

// 单词提取，已完成
OutputDate *KeyWordGetter :: keyWord(
    string c, int l ) {
    int         index;
    string      w;
    Flags       *flags = new Flags {
        false,
        false,
        false
    };

    OutputDate *out = new OutputDate{
        sum : 0,
        level : l,
        key_count : {0},
        if_else_count : 0,
        if_else_if_else_count :0,
        else_if_flag : 0,
        case_head : new CaseCount {
            count : 0,
            next : nullptr
        },
        node : nullptr
    };
    for( int i = 1; i < c.size(); i++ ) {
        
        if( !isalpha( c[i-1] ) && isalpha( c[i] ) ) { 
            index = i;
        }
        if(symbolIgnore( c, i, flags))continue;
        if( !isalpha( c[i] ) && isalpha( c[i-1] ) ) {
            w = c.substr( index, i - index);
            switchCaseCheck(
                out,
                w
            );
            ifElseCheck(
                out,
                w,
                &(c[i])
            );
            keyCount(
                out, 
                w
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
    CilIo           cil_io;
    Input           input;
    string          context;
    OutputDate      *output_date;
    KeyWordGetter   key_word;

    input           = cil_io.prompt();
    context         = fileReader( input.file_path );
    output_date     = key_word.keyWord( context, input.level);

    cil_io.output( output_date );
    return 0;
}
