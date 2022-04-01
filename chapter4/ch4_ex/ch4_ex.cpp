//
// Created by 刘民皓 on 2021/8/12.
//

#include "ch4_ex.h"

int main() {

    ex4_1();
    ex4_2();
    ex4_3();
    ex4_4();
    ex4_5();

    return 0;
}

void ex4_1() {
    Stack st;
    string str;

    cout << "Please enter a series of strings.\n";
    while (cin >> str && !st.full())
        st.push(str);
    fill_stack(st);

    if (st.empty()) {
        cout << '\n' << "Oops: no strings were read -- bailing out\n ";
        return;
    }

    cout << st.peek(str);

    if (st.size() == 1 && st.empty()) {
        cout << '\n' << "Oops: no strings were read -- bailing out\n ";
        return;
    }

    cout << '\n' << "Read in " << st.size() << " strings!\n"
         << "The strings, in reverse order: \n";

    while (st.size())
        if (st.pop(str))
            cout << str << ' ';

    cout << '\n' << "There are now " << st.size()
         << " elements in the stack!\n";
}

void ex4_2() {
    Stack st;
    string str;

    cout << "Please enter a series of strings.\n";
    while (cin >> str && st.size() < 11)
        st.push(str);

    cout << '\n' << "Read in " << st.size() << " strings!\n";
    cin.clear();

    cout << "what word to search for? ";
    cin >> str;

    bool found = st.find(str);
    int count = found ? st.count(str) : 0;

    cout << str << (found ? " is" : " isn't")
         << " in the Stack.";
    cout << " It occurs " << count << " times\n";
}

void ex4_3() {

    if (globalWrapper::program_name().empty()) {
        globalWrapper::program_name("ex_4_3");
        globalWrapper::version_number(1);
        globalWrapper::version_stamp("A1-OK");
    }

    if (globalWrapper::program_name() == "ex_4_3") {
        cout << "Wrapper seems to work ok!!!\n";
        cout << "program_name =\t" << globalWrapper::program_name() << endl
             << "version_num  =\t" << globalWrapper::version_number() << endl
             << "version_stamp=\t" << globalWrapper::version_stamp() << endl;
    } else
        cout << "Hmm. Wrapper doesn't seem to be correct...\n";

}

void ex4_4() {
    UserProfile anon;
    cout << anon;

    UserProfile anon_too;
    cout << anon_too;

    UserProfile ana("AnnaL", UserProfile::Guru);
    cout << ana;

    ana.bump_guess_count(27);
    ana.bump_guess_correct(25);
    ana.bump_login_count();
    cout << ana;

    cin >> anon;
    //输入样例: robin Intermediate 1 8 3
    cout << anon;
}

void ex4_5() {
    Matrix m;
    cout << "\n默认初始化矩阵m:" << endl;
    cout << m << endl;

    elemType ar[16] = {
            1., 0., 0., 0., 0., 1., 0., 0.,
            0., 0., 1., 0., 0., 0., 0., 1.};

    Matrix identity(ar);
    cout << "int数组传入矩阵identity:" << endl;
    cout << identity << endl;

    // guarantee default memberwise copy works correctly
    // 保证默认的成员逐一复制有效
    Matrix m2(identity);
    m = identity;

    cout << "identity成员逐一复制给m2: " << endl;
    cout << m2 << endl;
    cout << "把m2成员逐一复制给m: " << endl;
    cout << m << endl;

    elemType ar2[16] = {
            1.3f, 0.4f, 2.6f, 8.2f, 6.2f, 1.7f, 1.3f, 8.3f,
            4.2f, 7.4f, 2.7f, 1.9f, 6.3f, 8.1f, 5.6f, 6.6f};

    Matrix m3(ar2);
    cout << "float数组传入矩阵m3: " << endl;
    cout << m3 << endl;

    Matrix m4 = m3 * identity;
    cout << "m4 = m3 * identity: " << endl;
    cout << m4 << endl;

    Matrix m5 = m3 + m4;
    cout << "m5 = m3 + m4:" << endl;
    cout << m5 << endl;

    m3 += m4;
    cout << "复合运算符 m3 += m4：" << endl;
    cout << m3 << endl;
}
