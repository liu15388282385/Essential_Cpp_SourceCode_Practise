//
// Created by 刘民皓 on 2021/7/16.
//

#include "ch1.h"

/**
 * 生成一个Fibonacci数列;
 * @param pos
 * @return
 */
pvec Fibonacci_gen_elems(int pos) {
    static vector<unsigned int> _elems;

    if (!check_integrity(pos))
        return nullptr;

    if (_elems.empty()) {
        _elems.push_back(1);
        _elems.push_back(1);
    }

    if (_elems.size() < pos) {
        unsigned int ix = _elems.size();
        unsigned int n_2 = _elems[ix - 2];
        unsigned int n_1 = _elems[ix - 1];

        for (unsigned int elem; ix < pos; ++ix) {
            elem = n_2 + n_1;
            _elems.push_back(elem);
            n_2 = n_1;
            n_1 = elem;
        }
    }

    return &_elems;
}

/**
 * 生成一个Pell数列;
 * @param pos
 * @return
 */
pvec Pell_gen_elems(int pos) {
    static vector<unsigned int> _elems;

    if (!check_integrity(pos))
        return nullptr;

    if (_elems.empty()) {
        _elems.push_back(1);
        _elems.push_back(2);
    }

    if (_elems.size() < pos) {
        unsigned int ix = _elems.size();
        unsigned int n_2 = _elems[ix - 2];
        unsigned int n_1 = _elems[ix - 1];

        for (unsigned int elem; ix < pos; ++ix) {
            elem = n_2 + 2 * n_1;
            _elems.push_back(elem);
            n_2 = n_1;
            n_1 = elem;
        }
    }

    return &_elems;
}

/**
 * 生成一个Lucas数列;
 * @param pos
 * @return
 */
pvec Lucas_gen_elems(int pos) {
    static vector<unsigned int> _elems;

    if (!check_integrity(pos))
        return nullptr;

    if (_elems.empty()) {
        _elems.push_back(1);
        _elems.push_back(3);
    }

    if (_elems.size() < pos) {
        unsigned int ix = _elems.size();
        unsigned int n_2 = _elems[ix - 2];
        unsigned int n_1 = _elems[ix - 1];

        for (unsigned int elem; ix < pos; ++ix) {
            elem = n_2 + n_1;
            _elems.push_back(elem);
            n_2 = n_1;
            n_1 = elem;
        }
    }

    return &_elems;
}

/**
 * 生成一个Triangular数列;
 * @param pos
 * @return
 */
pvec Triangular_gen_elems(int pos) {
    static vector<unsigned int> _elems;

    if (!check_integrity(pos))
        return nullptr;

    if (_elems.size() < pos) {
        unsigned int ix = !_elems.empty() ? _elems.size() + 1 : 1;
        for (; ix <= pos; ++ix)
            _elems.push_back(ix * (ix + 1) / 2);
    }

    return &_elems;
}

/**
 * 生成一个Square数列;
 * @param pos
 * @return
 */
pvec Square_gen_elems(int pos) {
    static vector<unsigned int> _elems;

    if (!check_integrity(pos))
        return nullptr;

    if (_elems.size() < pos) {
        unsigned int ix = !_elems.empty() ? _elems.size() + 1 : 1;
        for (; ix <= pos; ++ix)
            _elems.push_back(ix * ix);
    }

    return &_elems;
}

/**
 * 生成一个Pentagonal数列;
 * @param pos
 * @return
 */
pvec Pentagonal_gen_elems(int pos) {
    static vector<unsigned int> _elems;

    if (!check_integrity(pos))
        return nullptr;

    if (_elems.size() < pos) {
        unsigned int ix = !_elems.empty() ? _elems.size() + 1 : 1;
        for (; ix <= pos; ++ix)
            _elems.push_back(ix * (3 * ix - 1) / 2);
    }

    return &_elems;
}

// 使用一个函数指针数组来访问在每个函数中产生的静态数列;
pfunc gen_elems[] = {
    nullptr,
    Fibonacci_gen_elems,
    Pell_gen_elems,
    Lucas_gen_elems,
    Triangular_gen_elems,
    Square_gen_elems,
    Pentagonal_gen_elems
};

// 生成数列的种类;
const char *name_seq[] = {
    "Invalid Sequence",
    "Fibonacci", "Pell", "Lucas",
    "Triangular", "Square", "Pentagonal"
};

// 游戏等级;
int level_size[] = {8, 32, 128, 512};

// 提示猜错时的一些反馈信息;
const char *wrong_msg[] = {
    "Oops! Nice guess but not quite it.",
    "Hmm. Sorry. Wrong again.",
    "Ah, this is harder than it looks, isn't it?",
    "It must be getting pretty frustrating by now!"
};

/**
 * 显示玩家在游戏中的猜测信息;
 * @param puser
 */
void display_statistics(user_profile *puser) {
    puser->score = (static_cast<float>(puser->correct) / static_cast<float>(puser->guesses)) * 100;
    cout << GREEN
         << "Game Statistics for " << puser->name << "\n\t"
         << "# guesses: " << puser->guesses << "\n\t"
         << "# correct: " << puser->correct << "\n\t"
         << "% correct: " << puser->score << endl << RESET;

    file_out(puser);
}

/**
 * 读取文件;
 * @param puser
 */
void file_in(user_profile *puser) {
    //    int num_tries = 0;
    //    int num_cor = 0;
    fstream iofile("seq_data.txt", ios_base::in | ios_base::app); //声明一个读写文件对象

    if (!iofile) {
        // 由于某种原因，文件无法打开......
        cerr << "Oops! Unable to open this file!\n";

        // 我们将假设这是一位新用户......
        cout << BLUE << "Welcome ! Nice to meet you ,stranger! \n" << RESET;
    }
    else {

        // ok: 读取档案中的某一行
        //     检查这个用户是否曾经玩过
        // 每一行的格式是：
        //     name num_tries num_correct num_score
        // nt：猜过的总次数（num_tries）
        // nc：猜对的总次数（num_correct）
        // ns：最后的总分数（num_score）

        // 开始读取之前，将文件重新定位至起始处
        iofile.seekg(0);

        string name;
        int nt, nc;
        float ns;

        while (iofile >> name) {
            iofile >> nt >> nc >> ns;
            if (name == puser->name) {
                //找到对应的玩家了
                cout << GREEN
                     << "Welcome back, " << puser->name
                     << "\nYour current score is " << nc
                     << " out of " << nt << " = " << ns
                     << "\nGood Luck!\n" << RESET;

                puser->guesses = nt;
                puser->correct = nc;
                puser->score = ns;
            }
        }
    }

    iofile.close();
}

/**
 * 写文件
 * @param puser
 */

void file_out(user_profile *puser) {
    //    int num_tries = 0;
    //    int num_cor = 0;
    fstream iofile("seq_data.txt", ios_base::in | ios_base::app); // 声明一个读写文件对象

    if (!iofile) {
        // 由于某种原因，文件无法打开......
        cerr << "Oops! Unable to save session data!\n";
    }
    else {
        // ok: 读取档案中的某一行
        //     检查这个用户是否曾经玩过
        // 每一行的格式是：
        //     name num_tries num_correct num_score
        // nt：猜过的总次数（num_tries）
        // nc：猜对的总次数（num_correct）
        // ns：最后的总分数（num_score）

        // 开始读取之前，将文件重新定位至起始处
        iofile.seekg(0);

        string name;
        int nt, nc;
        float ns;
        while (iofile >> name) {
            iofile >> nt >> nc >> ns;
            if (name == puser->name) {
                //todo: 修改用户的猜测信息，并保存进文件
                nt += puser->guesses;
                nc += puser->correct;
                ns = (static_cast<float>(nt) / static_cast<float>(nc)) * 100;
                return;
            }
            else {
                //把用户的猜测信息写入文件
                iofile << setw(10) << setfill(' ') << puser->name
                       << setw(5) << setfill(' ') << puser->guesses
                       << setw(5) << setfill(' ') << puser->correct
                       << setw(5) << setfill(' ') << puser->score << endl;
            }
        }
    }

    iofile.close();
}

/**
 * 初始化玩家信息和游戏信息;
 * @param puser
 * @return
 */
bool greet_user(user_profile *puser) {
    cout << BLUE << "Hi. What's your name? " << RESET;

    string nm;
    cin >> nm;

    if (nm.empty() || nm[0] == ' ') {
        cout << BLUE << "ok. I guess you don't want to play. See ya!\n" << RESET;
        return false;
    }

    cout << BLUE
         << "Hi, " << nm
         << " Would you like to play Guess the Sequence? (y/n) " << RESET;

    char ch;
    cin >> ch;

    if (ch != 'y' && ch != 'Y') {
        cout << BLUE << "ok. I'm sorry you don't want to play.\n" << RESET;
        return false;
    }

    cout << "\n\n" << GREEN
         << "Hey, that's great, " << nm << ".\n"
         << "We'll start in just a moment.\nIt\'s simple, really!\n"
         << "I will print out two elements of a sequence\n"
         << "You just answer with the element value that comes next!\n\n";

    cout << "Oh, by the way, do you consider yourself a\n\t"
         << "beginner     -- enter 1\n\t"
         << "intermediate -- enter 2\n\t"
         << "advanced     -- enter 3\n\t"
         << "guru         -- enter 4\n\t" << RESET
         << endl;

    int level;
    cin >> level;

    if (level < 1 || level > 4)
        level = 4;

    init_user(puser, nm, level);
    return true;
}

/**
 * 打印当前数列中的所有元素
 * @param puser
 */
void print_seq(user_profile *puser) {
    for (unsigned int i : *puser->cur_seq_vec)
        cout << GREEN << i << ' ';
    cout << RESET << endl;
}

void display_seq(user_profile *puser) {
    pvec p = seq_vec(puser);
    cout << BLUE << "The first two elements of the series are: " << RESET
         << (*p)[puser->pos - 3] << ", " << (*p)[puser->pos - 2] //显示倒数第3个和倒数第2个数;
         << BLUE << "\nWhat is the next element? " << RESET;
}

void set_up_index(user_profile *puser) {
    static string wherefrom("set_up_index");

    // 在数列等级数组中随机获取一个位置;
    srand(time(nullptr));
    puser->pos = rand() % (level_size[puser->level]);

    //显示数列最后3个数, 位置不对的话就加3防止出错;
    if (puser->pos < 3)
        puser->pos += 3;

    set_seq_vec(puser, (*gen_elems[puser->cur_seq])(puser->pos));
    trace(wherefrom, "new position: ", puser->pos);
}

void reset_seq(user_profile *puser) {
    static string wherefrom("reset_seq");

    int new_seq = gen_seq_id(); //设置游戏猜测序列的种类;
    if (new_seq == puser->cur_seq)
        new_seq = (new_seq < ns_cnt) ? new_seq + 1 : 1;

    puser->cur_seq = static_cast<num_sequence>(new_seq); //设置玩家当前猜测序列的种类;

    set_up_index(puser);

    print_seq(puser);
    trace(wherefrom, "new sequence: ", name_seq[puser->cur_seq]);
}

/**
 * 初始化游戏各项信息;
 * @param puser
 * @param nm
 * @param level
 */
void init_user(user_profile *puser, const string &nm, int level) {
    static string wherefrom("init_user");

    puser->name = nm;
    puser->guesses = 0;
    puser->correct = 0;
    puser->level = level;

    file_in(puser);

    reset_seq(puser);                            //设置游戏参数;
    trace(wherefrom, nm, puser->cur_seq, level); //打印追踪信息;
}

bool correct_guess(user_profile *puser, unsigned int guess) {
    pvec p = seq_vec(puser);
    if (guess == (*p)[puser->pos - 1])
        return true;
    return false;
}
void play_game(user_profile *puser) {
    bool next_seq = true;  // show next sequence?
    bool go_for_it = true; // user wants to guess?
    bool got_it = false;   // user guessed correctly?
    int num_tries;         // number of tries per sequence

    while (next_seq) {
        num_tries = 0;
        display_seq(puser);
        while ((!got_it) && (go_for_it)) {
            unsigned int usr_guess;
            cin >> usr_guess;
            /*猜对了*/
            if (correct_guess(puser, usr_guess)) {
                bump_correct(puser);
                got_it = true;
                cout << BLUE << "Hey, most excellent! \n\t" << RESET
                     << usr_guess << BLUE << " is element # " << RESET
                     << puser->pos << BLUE << " of the " << RESET
                     << name_seq[puser->cur_seq] << BLUE << " sequence.\n" << RESET; //打印当前数列的部分信息;
            }
            /*猜错了*/
            else {
                bump_guess(puser);
                cout << YELLOW<< wrong_msg[num_tries < ns_wrong_msg ? num_tries : ns_wrong_msg - 1] //打印一条反馈信息;
                     << BLUE << " Would you like to try again? (y/n) " << RESET;

                char usr_rsp;
                cin >> usr_rsp;

                if (usr_rsp == 'N' || usr_rsp == 'n')
                    go_for_it = false;
                else {
                    ++num_tries;
                    cout << BLUE << "Your next guess? " << RESET;
                }
            }
        }

        cout << BLUE << "Want to try another sequence? (y/n) " << RESET;
        char try_again;
        cin >> try_again;

        if (try_again == 'N' || try_again == 'n')
            next_seq = false;
        else {
            got_it = false;
            reset_seq(puser); //再次尝试游戏则重置游戏信息;
        }
    }
}