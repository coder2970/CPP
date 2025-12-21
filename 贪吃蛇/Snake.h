#pragma once
#include <cstdlib>
#include <windows.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>
#include <time.h>
#include <iostream>
#include <string>
#define POS_X 24
#define POS_Y 5
// 🔲
#define WALL L"⬜"
#define BODY L"⚫"
#define FOOD L"🔶"
void SetPosition(short x, short y);
// 方向
enum DIRECTION
{
    UP = 1,
    DOWN,
    LEFT,
    RIGHT
};

enum GAMESTATUS
{
    // 正常 撞墙 装自己 退出
    NORMAL,
    KILL_BY_WALL,
    KILL_BY_SELF,
    EXIT
};
// 蛇身节点
struct SnakeNode
{
public:
    short _x, _y;     // 坐标
    SnakeNode *_next; // 下一个节点指针
};

class Snake
{
public:
    void Init();
    void CreateFood();
    void SnakeMove();

    GAMESTATUS GetStatus()
    {
        return _status;
    }
    int GetScore()
    {
        return _score;
    }
    int GetFoodWeight()
    {
        return _food_weight;
    }
    int GetSleepTime()
    {
        return _sleep_time;
    }
    DIRECTION GetDir()
    {
        return _dir;
    }
    void SetDir(DIRECTION dir)
    {
        _dir = dir;
    }
    void SetStatus(GAMESTATUS status)
    {
        _status = status;
    }
    bool NextIsFood(SnakeNode *snode)
    {
        if ((_food->_x == snode->_x) && (_food->_y == snode->_y))
            return true;
        else
            return false;
    }
    void EatFood(SnakeNode *snode)
    {
        // 头插法
        _food->_next = _snake_head;
        _snake_head = _food;

        delete snode;
        snode = nullptr;

        SnakeNode *cur = _snake_head;
        while (cur)
        {
            SetPosition(cur->_x, cur->_y);
            std::wcout << BODY;
            cur = cur->_next;
        }
        _score += _food_weight;

        // 重新创建食物
        CreateFood();
    }
    void NoFood(SnakeNode *snode)
    {
        snode->_next = _snake_head;
        _snake_head = snode;

        // 把最后一个坐标打印空格
        // 把最后一个节点释放
        SnakeNode *cur = _snake_head;
        while (cur->_next->_next)
        {
            SetPosition(cur->_x, cur->_y);
            std::wcout << BODY;
            cur = cur->_next;
        }
        SetPosition(cur->_next->_x, cur->_next->_y);
        std::wcout << L"  ";
        delete cur->_next;
        cur->_next = nullptr;
    }
    void KillByWall()
    {
        if (_snake_head->_x == 0 || _snake_head->_x == 56 || _snake_head->_y == 0 || _snake_head->_y == 26)
        {
            _status = KILL_BY_WALL;
        }
    }
    void KillBySelf()
    {
        SnakeNode *cur = _snake_head->_next;
        while (cur)
        {
            if (cur->_x == _snake_head->_x && cur->_y == _snake_head->_y)
            {
                _status = KILL_BY_SELF;
                break;
            }
            cur = cur->_next;
        }
    }

    SnakeNode *GetHead()
    {
        return _snake_head;
    }

private:
    SnakeNode *_snake_head; // 指向蛇头的指针
    SnakeNode *_food;       // 指向食物
    DIRECTION _dir;         // 蛇运动方向
    GAMESTATUS _status;     // 游戏状态
    int _food_weight;       // 每个食物的分数
    int _score;             // 游戏分数
    int _sleep_time;        // 刷新时间 表示蛇的速度 时间越短速度越快
};

class Game
{
public:
    void GameStart(Snake &snake);

    void GameRun(Snake &snake);

    void GameEnd(Snake &snake);

private:
    Snake _snake;
};

void WelcomeToGame();

void CreateMap();

void PrintHelpInfo();
void Pause();
