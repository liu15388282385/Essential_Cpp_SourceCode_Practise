//
// Created by 刘民皓 on 2021/7/20.
//

#include "ch2.h"

int main()
{

    int change;

    cout << "选择数\t函数\n"
         << "1    \tBubble_sort()\n"
         << "2    \tFibon_elem()\n"
         << endl;
    cout << "输入你的选择，进入不同函数执行选择: \n";
    cin >> change;

    switch (change)
    {
    case 1:
    {
        //冒泡排序，过程记录到文件中
        ofstream ofil("data.txt");

        int ia[8] = {8, 32, 3, 13, 1, 21, 5, 2};
        vector<int> vec(ia, ia + 8);

        Bubble_sort(vec, &ofil);
    }
    break;
    case 2:
    {
        //斐波那契数列
        int elem, pos;
        bool more = true;
        char ch;
        while (more)
        {
            cout << "请输入你想知道对应位置的元素值: ";
            cin >> pos;

            if (Fibon_elem(pos, elem))
                cout << "  " << elem << endl;

            cout << "想再试一次吗? (Y/N)";
            cin >> ch;
            if (ch == 'N' || ch == 'n')
                more = false;
        }
    }
    break;
    default:
        break;
    }
}

/**
 * 交换过程写入文件
 * @param vec
 * @param ofil
 */
void Display(const vector<int> &vec, ofstream &ofil)
{
    for (int ix : vec)
    {
        ofil << ix << ' ';
    }
    ofil << endl;
}

/**
 * 交换函数
 * @param val1
 * @param val2
 * @param ofil
 */
void Swap(int &val1, int &val2, ofstream *ofil)
{
    if (ofil)
        (*ofil) << "swap( " << val1
                << ", " << val2 << " )\n";
    int tmp = val1;
    val1 = val2;
    val2 = tmp;
    if (ofil)
        (*ofil) << "after swap(): val1 " << val1
                << "  val2: " << val2 << "\n";
}

/**
 * 冒泡排序
 * @param vec
 * @param ofil
 */
void Bubble_sort(vector<int> &vec, ofstream *ofil)
{
    for (int ix = 0; ix < vec.size(); ++ix)
    {
        for (int jx = ix + 1; jx < vec.size(); ++jx)
        {
            if (vec[ix] > vec[jx])
            {
                if (ofil != nullptr)
                    (*ofil) << "about to call swap! ix: " << ix
                            << " jx: " << jx << "\tswapping: "
                            << vec[ix] << " with " << vec[jx] << endl;
                Swap(vec[ix], vec[jx], ofil);
                Display(vec, *ofil);
            }
        }
    }
}

/**
 * 计算Fibonacci数列中的size个元素，
 * 并返回持有这些元素的静态容器的地址
 * @param size
 * @return
 */
const vector<int> *Fibon_seq(int size)
{
    static vector<int> elems;

    if (!is_size_ok(size))
        return nullptr;

    //如果size等于或小于elems.size(),
    //就不必重新计算了
    for (unsigned int ix = elems.size(); ix < size; ++ix)
    {
        if (ix == 0 || ix == 1)
            elems.push_back(1);
        else
            elems.push_back(elems[ix - 2] + elems[ix - 1]);
    }

    return &elems;
}

/**
 * 返回Fibonacci数列中位置为pos的元素
 * @param pos
 * @param elem
 * @return
 */
inline bool Fibon_elem(int pos, int &elem)
{
    const vector<int> *pseq = Fibon_seq(pos);

    if (!pseq)
    {
        elem = 0;
        return false;
    }
    elem = (*pseq)[pos - 1];

    const string msg("The sequence is: ");

    Display_message(msg, *pseq);

    return true;
}

bool Seq_elem(int pos, int &elem,
              const vector<int> *(*seq_ptr)(int))
{
    if (!seq_ptr)
        Display_message("Internal Error: seq_ptr is set to null!");

    //调用seq_ptr所指的函数
    const vector<int> *pseq = seq_ptr(pos);

    if (!pseq)
    {
        elem = 0;
        return false;
    }
    elem = (*pseq)[pos - 1];

    return true;
}

/**
 * 判断size是否合理
 * @param size
 * @return
 */
inline bool is_size_ok(int size)
{
    const int max_size = 1024;
    const string msg("Request size is not supported");

    if (size <= 0 || size > max_size)
    {
        Display_message(msg);
        return false;
    }
    return true;
}

/**
 * 打印错误信息
 * @param msg
 */
inline void Display_message(const string &msg)
{
    cout << msg << endl;
}

/**
 * 打印信息，模板函数
 * @tparam elemType
 * @param msg
 * @param vec
 */
template <typename elemType>
void Display_message(const string &msg, const vector<elemType> &vec)
{
    cout << msg << endl;
    for (int ix = 0; ix < vec.size(); ++ix)
    {
        elemType t = vec[ix];
        cout << t << ' ';
    }
    cout << endl;
}
