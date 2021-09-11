//
// Created by 刘民皓 on 2021/7/19.
//

#include "ch2_ex.hpp"

//主函数
int main()
{

    ex2_1();
    ex2_2();
    ex2_3();
    ex2_4();
}

/**
 * 练习2-1
 * 用户可循环输入想获取的位置的元素值
 */
[[maybe_unused]] void ex2_1()
{
    cout << "<Exercise 2_1>" << endl;
    int pos, elem;
    char ch;
    bool more = true;

    while (more)
    {
        cout << "Please enter a position: ";
        cin >> pos;

        if (Fibon_elem(pos, elem))
            cout << "element # " << pos
                 << " is " << elem << endl;
        else
            cout << "Sorry, could not calculate element #"
                 << pos << endl;

        cout << "Would you want to try again? ";
        cin >> ch;
        if (ch == 'N' || ch == 'n')
            more = false;
    }
}

/**
 * 练习2-2
 */
[[maybe_unused]] void ex2_2()
{

    cout << "<Exercise 2_2>" << endl;
    vector<int> pent;
    const string title("Pentagonal Numeric Series");

    if (Calc_elem(pent, 1))
        Display_elem(pent, title);
    if (Calc_elem(pent, 8))
        Display_elem(pent, title);
    if (Calc_elem(pent, 14))
        Display_elem(pent, title);
    if (Calc_elem(pent, 65))
        Display_elem(pent, title);
}

/**
 * 练习2-3
 */
[[maybe_unused]] void ex2_3()
{
    cout << "<Exercise 2_3>" << endl;
    vector<int> pent;
    const string title("Pentagonal Numeric Series");

    if (Calc_elems(pent, 1))
        Display_elem(pent, title);
    if (Calc_elems(pent, 8))
        Display_elem(pent, title);
    if (Calc_elems(pent, 32))
        Display_elem(pent, title);
    if (Calc_elems(pent, 65))
        Display_elem(pent, title);

    cout << "ex2-3 end!\n";
}

/**
 * 练习2-4
 */
[[maybe_unused]] void ex2_4()
{
    ofstream outfile("seq.txt", ios_base::app);
    int elem;
    for (int i = 1; i <= 64; ++i)
        if (Pentagonal_elem(i, elem))
            outfile << "element " << i << " is : " << elem << endl;
}

/**
 * 获取斐波那契数列某一位置的元素值
 * @param pos
 * @param elem
 * @return
 */
bool Fibon_elem(int pos, int &elem)
{
    //检查位置是否合理
    if (pos <= 0 || pos > 1024)
    {
        elem = 0;
        return false;
    }

    //位置为1和2时，elem的值为1
    elem = 1;
    int n_2 = 1, n_1 = 1;

    for (int ix = 3; ix <= pos; ++ix)
    {
        elem = n_2 + n_1;
        n_2 = n_1;
        n_1 = elem;
    }

    Print_seq(pos);

    return true;
}

bool Print_seq(int pos)
{
    if (pos <= 0 || pos > 1024)
    {
        cerr << "invalid position: " << pos
             << " -- cannot handle request!\n";

        return false;
    }

    cout << "The Fibonacci Sequence for "
         << pos << " position: \n\t";

    //所有位置都会打印出1 1，只有pos == 1除外
    switch (pos)
    {
    default:
    case 2:
        cout << "1 ";
        //注意此处没有break
    case 1:
        cout << "1 ";
        break;
    }

    int elem;
    int n_2 = 1, n_1 = 1;
    for (int ix = 3; ix <= pos; ++ix)
    {
        elem = n_2 + n_1;
        n_2 = n_1;
        n_1 = elem;

        //一行打印10个元素
        cout << elem << (!(ix % 10) ? "\n\t" : " ");
    }

    cout << endl;

    return true;
}

/**
 * 计算Pentagonal数列
 * @param vec
 * @param pos
 * @return
 */

bool Calc_elem(vector<int> &vec, int pos)
{

    if (pos <= 0 || pos > 64)
    {
        cerr << "Sorry. Invalid position: "
             << pos << endl;
        return false;
    }

    for (int ix = vec.size() + 1; ix <= pos; ++ix)
    {
        vec.push_back((ix * (3 * ix - 1)) / 2);
    }

    return true;
}

/**
 * 打印信息
 * @param vec
 * @param title
 */
void Display_elem(vector<int> &vec, const string &title)
{
    cout << title << ": " << vec.size() << "\n\t";
    for (int ix : vec)
    {
        cout << ix << ' ';
    }
    cout << endl;
}

/**
 * 拆分后真正计算数列的部分
 * @param vec
 * @param pos
 */
void Really_calc_elem(vector<int> &vec, int pos)
{
    for (int ix = vec.size() + 1; ix <= pos; ++ix)
    {
        vec.push_back((ix * (3 * ix - 1) / 2));
    }
}

/**
 * 返回一个const指针，指向一个存储数列的静态vector
 * @param pos
 * @return
 */
const vector<int> *Pentagonal_series(int pos)
{
    static vector<int> _elems;

    if (Check_validity(pos) && (pos > _elems.size()))
    {
        for (int ix = _elems.size() + 1; ix <= pos; ++ix)
        {
            _elems.push_back((ix * (3 * ix - 1) / 2));
        }
    }

    return &_elems;
}

/**
 * 返回数列某一位置上的元素
 * @param pos
 * @param elem
 * @return
 */
bool Pentagonal_elem(int pos, int &elem)
{
    if (!(Check_validity(pos)))
    {
        cerr << "Sorry. Invalid position: "
             << pos << endl;
        elem = 0;
        return false;
    }

    const vector<int> *pent = Pentagonal_series(pos);
    elem = (*pent)[pos - 1];

    return true;
}