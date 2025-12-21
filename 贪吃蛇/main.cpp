#include "snake.h"

void test()
{
    char ch;
    do
    {
        system("cls"); // 清理屏幕
        // 创建贪吃蛇
        Snake snake;
        // 初始化游戏
        Game game;
        game.GameStart(snake);
        // 运行游戏
        game.GameRun(snake);
        // 结束游戏
        game.GameEnd(snake);
        SetPosition(0, 30);
        std::wcout << L"再来一局 Y N";
        std::string line;
        do
        {
            if (!std::getline(std::cin, line))
                return; // EOF 直接退出
        } while (line.empty());
        ch = line[0];
    } while (ch == L'y');
}
int main()
{
    // 0.设置本地环境
    /*设置窗口大小*/
    system("mode con cols=160 lines=40");
    system("title 贪吃蛇");
    (void)_setmode(_fileno(stdout), _O_U8TEXT);
    setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(NULL));

    // 1.游戏测试
    test();
    // getchar();
    return 0;
}