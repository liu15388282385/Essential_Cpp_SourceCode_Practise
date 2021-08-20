//
// Created by 刘民皓 on 2021/7/29.
//

#include "ch3_ex.h"

int main() {
//    ex3_1();
//    ex3_2();
//    ex3_3();
//    ex3_4();
    ex_filter();
    return 0;
}

[[maybe_unused]]void ex3_1() {

    ifstream ifile("MooCat.txt");
    ofstream ofile("MooCat.map");

    if (!ifile || !ofile) {
        cerr << "Unable to open file -- bailing out!\n";
        return;
    }

    set<string> exclude_set;
    initialize_exclusion_set(exclude_set);//初始化排除字集;

    map<string, int> word_count;
    progress_file(word_count, exclude_set, ifile);//处理文件;
    user_query(word_count);//允许用户查询某个单字是否出现于本文中;
    display_word_count(word_count, ofile);//显示单字统计清单;

}

/**
 * 初始化排除字眼集
 * @param exs
 */
void initialize_exclusion_set(set<string> &exs) {
    static string _excluded_words[26] = {
            "the", "and", "but", "that", "then", "are", "been",
            "can", "a", "could", "did", "for", "of",
            "had", "have", "him", "his", "her", "its", "is",
            "were", "which", "when", "with", "would"};
    exs.insert(_excluded_words, _excluded_words + 26);
}

/**
 * 处理文件
 * @param ifile
 */
void progress_file(map<string, int> &word_count,
                   const set<string> &exclude_set, ifstream &ifile) {
    string word;

    while (ifile >> word) {
        //如果排除字集里面存在的，跳过不计入map
        if (exclude_set.count(word))
            continue;
        word_count[word]++;
    }
}

/**
 * 允许用户查询某个单字是否出现于本文中
 * @param word_map
 */
void user_query(const map<string, int> &word_map) {
    string search_word;
    cout << BLUE << "Please enter a word to search (q to quit) : " << RESET;
    cin >> search_word;
    while (!search_word.empty() && search_word != "q") {
        map<string, int>::const_iterator iter;
        if ((iter = word_map.find(search_word)) != word_map.end())
            cout << "Found! " << iter->first
                 << " occurs " << iter->second
                 << " times.\n";
        else
            cout << search_word
                 << " was not found in text.\n";
        cout << "\nAnother search? (q to quit) ";
        cin >> search_word;
    }
}

/**
 * 显示单字统计清单
 * @param word_map
 * @param os
 */
void display_word_count(const map<string, int> &word_map, ofstream &os) {
    auto iter = word_map.begin();

    while (iter != word_map.end()) {
        os << iter->first << " ( "
           << iter->second << " )" << endl;
        ++iter;
    }

    os << endl;
}

[[maybe_unused]]void ex3_2() {

//    ifstream ifile("MooCat.txt");
//    ofstream ofile("MooCat.sort");
    ifstream ifile("column.txt");
    ofstream ofile("column.map");

    if (!ifile || !ofile) {
        cerr << "Unable to open file -- bailing out!\n";
        return;
    }

    vector<string> text;
    string word;

    int elem_cnt = 1;
    while (ifile >> word) {
        cout << word
             << (!(elem_cnt++ % 20) ? '\n' : ' ');
        text.push_back(word);
    }
    cout << endl;

    sort(text.begin(), text.end(), LessThan());
    display_vector(text, ofile);

}

[[maybe_unused]]void ex3_3() {

    map<string, vstring> families;

    ifstream nameFile("families.txt");
    ofstream nameMap("families.map");
    if (!nameFile || !nameMap) {
        cerr << "Unable to find families.txt and families.map file. Bailing Out!\n";
        return;
    }

    populate_map(nameFile, families);

    string family_name;
    while (true) {
        cout << "Please enter a family name or q to quit ";
        cin >> family_name;
        if (family_name == "q")
            break;
        query_map(family_name, families);
    }

    display_map(families, nameMap);

}

/**
 * 处理文件、把内容读入map
 * @param nameFile
 * @param families
 */
void populate_map(ifstream &nameFile, map<string, vstring> &families) {
    string textline;
    //文件中的每一行都存有家族姓氏及孩子们的名字;
    while (getline(nameFile, textline, '\n')) {
        string fam_name;
        vector<string> child;
        cout << "textline: " << textline << endl;

        string::size_type pos = 0, prev_pos = 0,
                text_size = textline.size();

        if (!text_size)
            continue;

        // ok: 找出以空格分割开来的所有单字
        while ((pos = textline.find_first_of(' ', pos)) != string::npos) {
            //计算字符串的终点
            string::size_type end_pos = pos - prev_pos;
            //倘若prev_pos并未设置（或说其值为0），那么读到的单字就是
            //家庭姓氏，否则我们就一一读取孩子们的名字......
            if (!prev_pos)
                fam_name = textline.substr(prev_pos, end_pos);
            else
                child.push_back(textline.substr(prev_pos, end_pos));
            prev_pos = ++pos;
        }

        // 现在处理最后一个孩子的名字
        if (prev_pos < text_size)
            child.push_back(textline.substr(prev_pos, pos - prev_pos));

        cout << "family name: " << fam_name << '\t'
             << "children: " << child.size() << endl;

        if (!families.count(fam_name))
            families[fam_name] = child;
        else
            cerr << "Oops! We already have a "
                 << fam_name << " family in our map!\n";
    }
}

/**
 * 允许用户查询map中是否存在某个家庭
 * @param family
 * @param families
 */
void query_map(const string &family, const map<string, vstring> &families) {
    auto it = families.find(family);
    if (it == families.end()) {
        cout << "Sorry. The "
             << family << " family is not currently entered.\n";
        return;
    }

    cout << "The " << family << " family ";
    if (it->second.empty())
        cout << " has no children\n";
    else { // 打印出vector内所有小孩的名字
        cout << " has " << it->second.size()
             << " children: ";

        auto iter = it->second.begin(),
                end_iter = it->second.end();

        while (iter != end_iter) {
            cout << *iter << " ";
            ++iter;
        }
        cout << endl;
    }
}

/**
 * 打印map
 * @param families
 * @param os
 */
void display_map(const map<string, vstring> &families, ostream &os) {
    auto it = families.begin(), end_it = families.end();

    while (it != end_it) {

        os << it->first;// 打印出当前的家庭姓氏

        if (it->second.empty())
            os << " (0)\n";
        else  // 打印出对应vector内的个数
            os << " (" << it->second.size() << ")\n";

        ++it;
    }
}

[[maybe_unused]]void ex3_4() {

    vector<int> input;
    istream_iterator<int> in(cin), eof;
    ofstream even_file("even_file.txt"),
            odd_file("odd_file.txt");

    if (!even_file || !odd_file) {
        cerr << "arghh!! unable to open the output files. bailing out!";
        return;
    }

    copy(in, eof, back_inserter(input));

    auto division = stable_partition(input.begin(), input.end(), even_elem());

    ostream_iterator<int> even_iter(even_file, "\n"),
            odd_iter(odd_file, " ");

    copy(input.begin(), division, even_iter);
    copy(division, input.end(), odd_iter);

}

//filter练习

/**
 * 过滤函数
 * @tparam InputIterator 
 * @tparam OutputIterator 
 * @tparam ElemType 
 * @tparam Comp 
 * @param first 
 * @param last 
 * @param out 
 * @param val 
 * @param pred 
 * @return 
 */
template<typename InputIterator, typename OutputIterator,
        typename ElemType, typename Comp>
OutputIterator filter(InputIterator first, InputIterator last,
                      OutputIterator out, const ElemType &val, Comp pred) {
    while ((first = find_if(first, last, bind2nd(pred, val))) != last) {
        cout << "found value: " << *first << endl;
        *out++ = *first++;
    }
    return out;
}

[[maybe_unused]]void ex_filter() {
    cout << "filtering integer array for values less than 8\n";
    filter(ia, ia + elem_size, ia2, elem_size, less<int>());

    cout << "filtering integer vector for values greater than 8\n";
    filter(ivec.begin(), ivec.end(), back_inserter(ivec2), elem_size, greater<int>());
}