#include "snake.h"

void Game::GameStart(Snake &snake)
{
    // 1.打印环境界面	 2.功能介绍
    /*设置光标隐藏*/

    HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE); // 获得句柄
    CONSOLE_CURSOR_INFO cursor_info = {0};
    GetConsoleCursorInfo(houtput, &cursor_info); // 获得控制台光标信息
    cursor_info.bVisible = false;                // 修改\设置光标属性
    SetConsoleCursorInfo(houtput, &cursor_info);

    WelcomeToGame();

    // 3.绘制地图
    CreateMap();

    // 4.创建蛇和食物
    // 对蛇进行初始化
    snake.Init();
    // 创建食物
    snake.CreateFood();

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    (void)GetAsyncKeyState(VK_SPACE); // 可选：读一次以复位“刚按过”的标志位
}

#define KEY_PRESS(vk) ((GetAsyncKeyState(vk) & 1) ? 1 : 0)
void Game::GameRun(Snake &snake)
{
    // 游戏运行逻辑
    // 每走一步 看一下蛇的状态
    // 打印帮助信息
    PrintHelpInfo();

    // 检测按键
    do
    {
        // 打印总分和食物分值
        SetPosition(64, 10);
        std::wcout << L"总分: " << snake.GetScore() << L" 食物分值" << snake.GetFoodWeight();

        if (KEY_PRESS(VK_UP) && snake.GetDir() != DOWN)
        {
            snake.SetDir(UP);
        }
        else if (KEY_PRESS(VK_DOWN) && snake.GetDir() != UP)
        {
            snake.SetDir(DOWN);
        }
        else if (KEY_PRESS(VK_LEFT) && snake.GetDir() != RIGHT)
        {
            snake.SetDir(LEFT);
        }
        else if (KEY_PRESS(VK_RIGHT) && snake.GetDir() != LEFT)
        {
            snake.SetDir(RIGHT);
        }
        else if (KEY_PRESS(VK_SPACE))
        {
            // 暂停
            Pause();
        }
        else if (KEY_PRESS(VK_F3)) // 加速
        {
        }
        else if (KEY_PRESS(VK_F4)) // 减速
        {
        }
        else if (KEY_PRESS(VK_ESCAPE))
        {
            snake.SetStatus(EXIT);
        }

        // 贪吃蛇走起来
        snake.SnakeMove();
        Sleep(snake.GetSleepTime());

    } while (snake.GetStatus() == NORMAL);
}
void Game::GameEnd(Snake &snake)
{
    SetPosition(24, 12);
    // 检测游戏状态
    switch (snake.GetStatus())
    {
    case EXIT:
        std::wcout << L"主动退出";
        break;
    case KILL_BY_WALL:
        std::wcout << L"撞墙, 失败";
        break;
    case KILL_BY_SELF:
        std::wcout << L"撞自己, 失败";
        break;
    }

    // 释放资源
    SnakeNode *cur = snake.GetHead();
    while (cur)
    {
        SnakeNode *del = cur;
        cur = cur->_next;
        delete del;
    }
}

void SetPosition(short x, short y)
{
    HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);

    // 定位光标
    COORD pos = {x, y};
    SetConsoleCursorPosition(houtput, pos);
}
void WelcomeToGame()
{
    SetPosition(65, 16);
    std::wcout << L"欢迎来到贪吃蛇" << std::endl;
    SetPosition(64, 22);
    system("pause");

    system("cls"); // 清理屏幕

    SetPosition(65, 16);
    std::wcout << L"用↑ ↓ ← → 控制蛇的方向,按F3加速,按F4减速" << std::endl;
    SetPosition(65, 17);
    std::wcout << L"加速可以获得更多分数" << std::endl;

    SetPosition(64, 22);
    system("pause");

    system("cls");
}
void CreateMap()
{
    (void)_setmode(_fileno(stdout), _O_U8TEXT);
    setlocale(LC_ALL, "en_US.UTF-8");
    // 上
    for (int i = 0; i < 29; i++)
    {
        std::wcout << WALL;
    }
    // 下
    SetPosition(0, 26);
    for (int i = 0; i < 29; i++)
    {
        std::wcout << WALL;
    }
    // 左
    for (int i = 1; i <= 25; i++)
    {
        SetPosition(0, i);
        std::wcout << WALL;
    }
    // 右
    for (int i = 1; i <= 25; i++)
    {
        SetPosition(56, i);
        std::wcout << WALL;
    }
}

void Snake::Init()
{
    _snake_head = nullptr;
    _food = nullptr;
    SnakeNode *cur = nullptr;
    for (int i = 0; i < 5; i++)
    {
        cur = new SnakeNode;
        if (cur == nullptr)
        {
            std::cerr << "初始化错误" << std::endl;
            return;
        }
        cur->_next = nullptr;
        cur->_x = POS_X + 2 * i;
        cur->_y = POS_Y;

        // 头插
        if (_snake_head == nullptr)
        {
            _snake_head = cur;
        }
        else
        {
            cur->_next = _snake_head;
            _snake_head = cur;
        }
    }
    cur = _snake_head;
    while (cur)
    {
        SetPosition(cur->_x, cur->_y);
        std::wcout << BODY;
        cur = cur->_next;
    }

    _dir = RIGHT;
    _score = 0;
    _food_weight = 10;
    _sleep_time = 200;
    _status = NORMAL;
}

void Snake::CreateFood()
{
    int x;
    int y;
again:
    do
    {
        x = rand() % 53 + 2;
        y = rand() % 25 + 1;
    } while (x % 2 != 0);

    // 食物和身体不重合
    SnakeNode *cur = _snake_head;
    while (cur)
    {
        if (x == cur->_x && y == cur->_y)
        {
            goto again;
        }
        cur = cur->_next;
    }

    // 创建食物节点
    SnakeNode *food = new SnakeNode;
    food->_x = x;
    food->_y = y;
    food->_next = nullptr;

    // 打印
    SetPosition(x, y);
    std::wcout << FOOD;
    _food = food;
}
void PrintHelpInfo()
{
    SetPosition(64, 20);
    std::wcout << L"不可以撞墙, 不可以吃自己" << std::endl;
    SetPosition(64, 21);
    std::wcout << L"用↑ ↓ ← → 控制蛇的移动" << std::endl;
    SetPosition(64, 22);
    std::wcout << L"F3 加速 , F4 减速" << std::endl;
    SetPosition(64, 23);
    std::wcout << L"ESC退出游戏, SPACE暂停游戏" << std::endl;
}
void Pause()
{
    while (true)
    {
        Sleep(200);
        if (KEY_PRESS(VK_SPACE))
        {
            break;
        }
    }
}
void Snake::SnakeMove()
{
    // 创建一个节点表示蛇即将到的下一个位置
    SnakeNode *nextbody = new SnakeNode;
    switch (_dir)
    {
    case UP:
        nextbody->_x = _snake_head->_x;
        nextbody->_y = _snake_head->_y - 1;
        break;
    case DOWN:
        nextbody->_x = _snake_head->_x;
        nextbody->_y = _snake_head->_y + 1;
        break;
    case LEFT:
        nextbody->_x = _snake_head->_x - 2;
        nextbody->_y = _snake_head->_y;
        break;
    case RIGHT:
        nextbody->_x = _snake_head->_x + 2;
        nextbody->_y = _snake_head->_y;
        break;
    }
    if (NextIsFood(nextbody))
    {
        EatFood(nextbody);
    }
    else
    {
        NoFood(nextbody);
    }

    // 检测撞墙
    KillByWall();
    // 检测撞到自己
    KillBySelf();
}
