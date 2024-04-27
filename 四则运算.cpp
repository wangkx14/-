#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include <cmath>
#include <fstream>

using namespace std;

// 全局变量
int problemCount; // 算式数量
int maxNumber; // 最大数
int operandCount; // 因子个数
int operation; // 用户输入的运算符
int hasBracket; // 是否有括号
int isFloat; // 是否有小数
int outputType; // 输出形式
char operators[4] = { '+', '-', '*', '/' }; // 运算符
ofstream outfile; // 数据写入文件

// 生成随机数
int randNum(int max) {
    return (rand() % max) + 1;
}

// 生成随机浮点数
float randFloat(int max) {
    return (float)rand() / RAND_MAX * max + 1.0;
}

// 生成括号内表达式
void genBracketExpr(bool isFloat, ostream& out) {
    int op = rand() % 4;
    out << "(";
    if (isFloat) {
        out << randFloat(maxNumber) << operators[op];
        out << randFloat(maxNumber) << ")";
    }
    else {
        out << randNum(maxNumber) << operators[op];
        out << randNum(maxNumber) << ")";
    }
}

// 生成单个项
void genTerm(bool isFloat, bool hasBracket, int n, ostream& out) {
    if (hasBracket && n > 1 && rand() % 2) {
        genBracketExpr(isFloat, out);
    }
    else {
        if (isFloat) {
            out << randFloat(maxNumber);
        }
        else {
            out << randNum(maxNumber);
        }
    }
}

// 生成算式
void genExpr(bool isFloat, bool hasBracket, int op, ostream& out) {
    int i = 0;
    genTerm(isFloat, hasBracket, operandCount, out);
    for (i = 1; i < operandCount; i++) {
        if (op == 5) {
            out << operators[rand() % 4];
        }
        else {
            out << operators[op - 1];
        }
        genTerm(isFloat, hasBracket, operandCount - i, out);
    }
    out << "=" << endl;
}

int main() {
    cout << "-----小学生四则运算练习系统-----" << endl;
    cout << "******************************** " << endl;
    cout << "      1: 请输入算式数量: " << endl;
    cin >> problemCount;
    cout << "      2: 请输入最大数: " << endl;
    cin >> maxNumber;
    cout << "      3: 请输出运算个数：" << endl;
    cin >> operandCount;
    cout << "      4: 请输入运算符: " << endl;
    cout << "      1代表+ 2代表- 3代表* 4代表/ 5代表混合:" << endl;
    cin >> operation;
    cout << "      5: 请选择数字类型: " << endl;
    cout << "      1代表整数 2代表小数" << endl;
    cin >> isFloat;
    cout << "      6: 请选择是否需要括号 " << endl;
    cout << "      1代表不需要括号 2代表需要括号" << endl;
    cin >> hasBracket;
    cout << "      7: 请选择输出形式 " << endl;
    cout << "      1代表输出到文件 2代表打印到屏幕" << endl;
    cin >> outputType;

    if (outputType == 1) {
        outfile.open("test.txt");
    }

    srand(time(NULL));
    for (int i = 0; i < problemCount; i++) {
        if (isFloat == 1) {
            genExpr(false, hasBracket == 2, operation, outputType == 1 ? outfile : cout);
        }
        else {
            genExpr(true, hasBracket == 2, operation, outputType == 1 ? outfile : cout);
        }
    }

    if (outputType == 1) {
        outfile.close();
    }

    cout << "******************************** " << endl;
    return 0;
}