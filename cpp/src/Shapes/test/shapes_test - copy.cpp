/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-, 2020
						Reviewer: Laura Bedah
*******************************************************************************/
#include <iostream> /* cout, cin, cerr */

#include "glut_utils.h"
#include "shape.hpp"
#include "point.hpp"
#include "color.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "square.hpp"
#include "rectangle.hpp"

using namespace ilrd;
double rCircle = 100;

Color turqois(134217985, 1, 1);
Color white(50, 50, 50);
Color green(40, 40, 40);
Color yellow_fill(134283520, 1, 1);
Color green_fill(134217984, 1, 1);

// Global flags:
int stop_screen = 0;
int won = 20;
int log1_flag = 0;
int log1_change_dir = 250;
int log6_change_dir = 400;
int log6_flag = 0;

// frog:
int x_frog = 500;
int y_frog = 930;

// Rotating (1-2) and Constant (3-5) logs:
int x_c_log4 = 100;
int y_c_log4 = 150;
int x_log1 = 100;
int y_log1 = 300;
int x_c_log3 = 200;
int y_c_log3 = 530;
int x_log6 = 850;
int y_log6 = 450;
int x_log2 = 850;
int y_log2 = 650;
int x_c_log5 = 850;
int y_c_log5 = 820;
int log_width = 50;
int log_length = 180;

int x_water1 = 500;
int y_water1 = 500;

Color fill_log(134283520, 1, 1); // YELLOW - FILL

static void DrawFunction()
{

    // Generating water
    Point water1_pos(x_water1, y_water1);
    Rectangle water1(water1_pos, 0, turqois, 1000, 1000);
    water1.Draw();

    // Generating moveing logs:
    Point log1_basic_pos(x_log1, y_log1);
    Rectangle log1(log1_basic_pos, 0, fill_log, log_width, log_length);
    log1.Draw();

    Point log2_basic_pos(x_log2, y_log2);
    Rectangle log2(log2_basic_pos, 0, fill_log, log_width, log_length);
    log2.Draw();

    //Generating one-directional logs:
    Point log3_basic_pos(x_c_log3, y_c_log3);
    Rectangle log3(log3_basic_pos, 0, fill_log, log_width, log_length);
    log3.Draw();

    Point log4_basic_pos(x_c_log4, y_c_log4);
    Rectangle log4(log4_basic_pos, 0, fill_log, log_width, log_length);
    log4.Draw();

    Point log5_basic_pos(x_c_log5, y_c_log5);
    Rectangle log5(log5_basic_pos, 0, fill_log, log_width, log_length);
    log5.Draw();

    Point log6_basic_pos(x_log6, y_log6);
    Rectangle log6(log6_basic_pos, 0, fill_log, log_width, log_length);
    log6.Draw();

    Point frog_pos(x_frog, y_frog);
    Circle frog(frog_pos, 0, green_fill, 30);
    frog.Draw();
}

void MousFunc(Circle &circle)
{
}
static int MouseFunction(int button, int state, int x, int y)
{
    /* printf("Mouse: %d,%d,%d,%d\n", button, state, x, y); */

    if (state == 1 && button == 'MOUSE_WHEEL_UP')
    {
        rCircle *= 1.1;
        return 1;
    }
    if (state == 1 && button == MOUSE_WHEEL_DOWN)
    {
        rCircle *= 0.9;
        return 1;
    }

    if (button == MOUSE_LEFT)
    {
        //drawCircle = state;
        x_log1 += 1;
        y_log1 += 1;
        return 1;
    }

    return 0;
}
static int KeyboardFunction(unsigned char key, int x, int y)
{
    std::cout << "Keyboard: "
              << "02x" << key << ", " << x << ", " << y
              << std::endl;
    if (key == 0x1b /* ESC */)
    {
        return -1;
    }
    else if (key == 'w')
    {
        y_frog -= 5;
    }
    else if (key == 'd')
    {
        x_frog += 5;
    }
    else if (key == 's')
    {
        y_frog += 5;
    }
    else if (key == 'a')
    {
        x_frog -= 5;
    }

    if (y_frog <= won)
    {
        std::cout << "Good job! You've won!!!" << std::endl;
        stop_screen = 1;
    }

    return 0;
}

static int MotionFunction(int x, int y)
{
    std::cout << "Mouse: " << x << ", " << y << std::endl;

    return 0;
}

static int TimerFunction()
{
    x_c_log3 += 1;
    x_c_log4 -= 1;
    x_c_log5 += 1;
    if (!log1_flag)
    {
        x_log1 += 1;
        x_log2 -= 1;

        //y_log1 += 1;
    }
    else if (log1_flag)
    {
        x_log1 -= 1;
        x_log2 += 1;
    }

    if (!log6_flag)
    {
        x_log6 -= 1;
    }
    else if (log6_flag)
    {
        x_log6 += 1;
    }

    if (x_log1 == log1_change_dir)
    {
        log1_flag = 1;
    }

    if (x_log6 == log6_change_dir)
    {
        log6_flag = 1;
    }

    if (stop_screen)
    {
        x_log1 = x_log1;
        x_log2 = x_log2;
    }

    int half_log_w = log_width / 2;
    int half_log_l = log_length / 2;

    if (x_frog >= (x_c_log5 - half_log_l) && x_frog <= (x_c_log5 + half_log_l) &&
        y_frog >= (y_c_log5 - half_log_w) && y_frog <= (y_c_log5 + half_log_w))
    {
        x_frog = x_c_log5;
        y_frog = y_c_log5;
    }

    return 1; /* draw */

    for (int i = 0; i < 7; ++i)
    {
        x_log1 -= 1;

        //y_log1 += 1;

        return 1; /* draw */
    }
}

void Log_slow(int argc, char *argv[])
{
    DrawInit(argc, argv, 1000, 1000, DrawFunction);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 100);
    // if (rCircle >= 2)
    // {
    //     std::cout << "made it!" << std::endl;
    // }
    DrawMainLoop();
}

int main(int argc, char *argv[])
{

    Log_slow(argc, argv);

    return (0);
}
