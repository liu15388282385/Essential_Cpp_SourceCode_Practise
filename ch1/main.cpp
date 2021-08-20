#include <iostream>
using namespace std;

#include "ch1/ch1.h"

int main() {

    cout << "<Chapter_1> \n";

    /*Chapter_1 一个猜数列数字的互动小程序*/
    user_profile up;                //声明一个玩家对象;

    if ( greet_user( &up ) )        //问候玩家并选择是否开始游戏;
    {
        play_game( &up );           //游戏主菜单;
        display_statistics( &up );  //显示玩家猜测次数和猜测正确率;
    }

    return 0;
}