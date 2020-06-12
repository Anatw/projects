/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-, 2020
						Reviewer: Laura Bedah
*******************************************************************************/
#include <iostream> /* cout, cin, cerr */
#include <time.h>   // srand(), rand()

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

int frame_length = 1000;
int frame_width = 1000;

Color turqois(134217985, 1, 1);
Color white(50, 50, 50);
Color green(40, 40, 40);
Color yellow_fill(134283520, 1, 1);
Color green_fill(134217984, 1, 1);
Color magenta_fill(134283265, 1, 1);

// Global flags:
int stop_screen = 0;
int won = 20;
int log1_flag = 0;
int log1_change_dir = 250;
int log6_change_dir = 400;
int log6_flag = 0;

int log_width = 50;
int log_length = 180;

int x_water1 = 500;
int y_water1 = 500;

int lily_width = 90;
int lily_length = 370;

Color fill_log(134283520, 1, 1); // YELLOW - FILL

typedef struct Log
{
    Point *position;
    Rectangle *log;
    int speed;
    int direction;
    Point *left_border;
    Point *right_border;
    int checked;
} log_t;

enum direction
{
    LEFT = 1,
    RIGHT = 2
};

typedef struct Frog
{
    Point *initial_position;
    Circle *frog;
    int current_log;
    int num_lives;
} frog_t;

frog_t frog;
Rectangle lily_pad(Point(500, 930), -3, magenta_fill, lily_width, lily_length);
recatngle end_pad(Point(500, 70), 2, magenta_fill, lily_width, (lily_length * 2));

#define NUM_LOGS (6)
int distance = (frame_length - (100 * 2)) / NUM_LOGS;

log_t logs[NUM_LOGS];

static void InitializeFrog()
{
    frog.initial_position = new Point(500, 930);
    frog.frog = new Circle(*frog.initial_position, 0.0, green_fill, 30);
    frog.current_log = 0;
    frog.num_lives = 3;
}

static void InitializeLogs()
{
    srand(time(NULL));

    for (int i = 0; i < NUM_LOGS; ++i)
    {
        // Generating a random x position for the log.
        logs[i].position = new Point((rand() % (frame_width - (100 * 2))), (distance + (distance * i)));
        logs[i].log = new Rectangle(*logs[i].position, 0, fill_log, log_width, log_length);
        logs[i].speed = (rand() % 3) + 1;
        logs[i].direction = (rand() % 2) + 1;
        logs[i].left_border = new Point(((rand() % ((frame_width / 20) * 4)) + ((frame_width / 20))), (distance + (distance * i)));
        logs[i].right_border = new Point(((rand() % ((frame_width / 20) * 16)) + ((frame_width / 20) * 19)), (distance + (distance * i)));
        logs[i].checked = 0;
    }
}

static void DrawFunction()
{
    // Generating water
    Point water1_pos(x_water1, y_water1);
    Rectangle water1(water1_pos, 0, turqois, 1000, 1000);
    water1.Draw();

    lily_pad.Draw();
    end_pad.Draw();

    for (int i = 0; i < NUM_LOGS; ++i)
    {
        logs[i].log->Draw();
    }

    frog.frog->Draw();
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
        int new_y = frog.frog->GetPosition().GetY() - (distance + (distance * frog.current_log));
        Point change_frog_y(frog.frog->GetPosition().GetX(), new_y);
        frog.frog->SetPosition(change_frog_y);
    }
    else if (key == 'd')
    {
        int new_x = frog.frog->GetPosition().GetX() + 5;
        Point change_frog_x(new_x, frog.frog->GetPosition().GetY());
        frog.frog->SetPosition(change_frog_x);
    }
    else if (key == 's')
    {
        int new_y = frog.frog->GetPosition().GetY() + (distance + (distance * frog.current_log));
        Point change_frog_y(frog.frog->GetPosition().GetX(), new_y);
        frog.frog->SetPosition(change_frog_y);
    }
    else if (key == 'a')
    {
        int new_x = frog.frog->GetPosition().GetX() - 5;
        Point change_frog_x(new_x, frog.frog->GetPosition().GetY());
        frog.frog->SetPosition(change_frog_x);
    }

    if (frog.frog->GetPosition().GetY() <= won)
    {
        std::cout << "Good job! You've won!!!" << std::endl;
        stop_screen = 1;
        return -1;
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
    int i = 0;
    // Move logs in random directions:
    for (i = 0; i < NUM_LOGS; ++i)
    {
        if (LEFT == logs[i].direction)
        {
            Point log_point((-1 * logs[i].speed), 0);
            logs[i].log->Move_m(log_point);
        }
        else // (RIGHT == logs[i].direction)
        {
            Point log_point((1 * logs[i].speed), 0);
            logs[i].log->Move_m(log_point);
        }
    }

    // Randomly decide if a log should change direction:
    for (i = 0; i < NUM_LOGS; ++i)
    {
        //std::cout << logs[i].checked << " I: " << i << std::endl;
        // Enter this part only if you haven't been checked lately(1) or
        //moved past the frame lately(2):
        if (0 == logs[i].checked)
        {
            if (logs[i].log->GetPosition().GetX() <= logs[i].left_border->GetX() ||
                logs[i].log->GetPosition().GetX() >= logs[i].right_border->GetX())
            {
                logs[i].direction = (rand() % 2) + 1;
                logs[i].checked = 1;
            }
        }
    }

    // If log went out of frame (X axe):
    for (i = 0; i < NUM_LOGS; ++i)
    {
        // Enter this part only if you've changed directions lately
        // Enter this part only if you havn't crosed the end of the fram lately:
        if (2 != logs[i].checked)
        {
            if (logs[i].log->GetPosition().GetX() <= 50 ||
                logs[i].log->GetPosition().GetX() >= 950)
            {
                int decide = (rand() % 2) + 1;
                std::cout << "decide: " << decide << ", i: " << i << std::endl;

                if (1 == decide)
                {
                    (logs[i].direction == 1) ? (logs[i].direction = 2)
                                             : (logs[i].direction = 1);
                }
                else
                {
                    if (logs[i].log->GetPosition().GetX() <= 50)
                    {
                        Point other_side((frame_width + (log_width / 2) + 5), logs[i].log->GetPosition().GetY());
                        logs[i].log->SetPosition(other_side);
                    }
                    else // (logs[i].position->GetX() >= frame_width)
                    {
                        Point other_side((0 - (log_width / 2) - 5), logs[i].log->GetPosition().GetY());
                        logs[i].log->SetPosition(other_side);
                    }
                }

                logs[i].checked = 2;
            }
        }
    }

    // Reset the log flag if the log has crossed the middle of the frame
    //(meaning it had enough time in the game and can change direction):
    for (i = 0; i < NUM_LOGS; ++i)
    {
        // Check if log is crossing the middle of the frame (x axe)
        if (logs[i].log->GetPosition().GetX() <= (frame_width / 2) + 10 &&
            logs[i].log->GetPosition().GetX() >= (frame_width / 2) - 10)
        {
            logs[i].checked = 0;
        }
    }

    int half_log_w = log_width / 2;
    int half_log_l = log_length / 2;
    int half_lily_l = lily_length / 2;
    int half_lily_w = lily_width / 2;

    // If frog is jumping on a log - stick it to the log
    for (i = 0; i < NUM_LOGS; ++i)
    {
        // Frog is insde the boundery of the lily_pad:
        if (frog.frog->GetPosition().GetX() >= (lily_pad.GetPosition().GetX() - half_lily_l) &&
            frog.frog->GetPosition().GetX() <= (lily_pad.GetPosition().GetX() + half_lily_l) &&
            frog.frog->GetPosition().GetY() >= (lily_pad.GetPosition().GetY() - half_lily_w) &&
            frog.frog->GetPosition().GetY() <= (lily_pad.GetPosition().GetY() + half_lily_w))
        {
            return 1;
        }
        // Frog is inside the boundery of a log:
        else if (frog.frog->GetPosition().GetX() >= (logs[i].log->GetPosition().GetX() - half_log_l) &&
                 frog.frog->GetPosition().GetX() <= (logs[i].log->GetPosition().GetX() + half_log_l) &&
                 frog.frog->GetPosition().GetY() >= (logs[i].log->GetPosition().GetY() - half_log_w) &&
                 frog.frog->GetPosition().GetY() <= (logs[i].log->GetPosition().GetY() + half_log_w))
        {
            Point frog_new_pos(logs[i].log->GetPosition().GetX(), logs[i].log->GetPosition().GetY());
            frog.frog->SetPosition(frog_new_pos);

            return 1;
        }
    }
    for (i = 0; i < NUM_LOGS; ++i)
    {
        if (frog.frog->GetPosition().GetX() < (logs[i].log->GetPosition().GetX() - (half_log_l + 5)) ||
            frog.frog->GetPosition().GetX() > (logs[i].log->GetPosition().GetX() + (half_log_l + 5)) ||
            frog.frog->GetPosition().GetY() < (logs[i].log->GetPosition().GetY() - (half_log_w + 5)) ||
            frog.frog->GetPosition().GetY() > (logs[i].log->GetPosition().GetY() + (half_log_w + 5)))
        {
            std::cout << "game is over" << std::endl;
            return -1;
        }
    }

    return 1; /* draw */
}

void Log_slow(int argc, char *argv[])
{
    InitializeLogs();
    InitializeFrog();

    DrawInit(argc, argv, frame_length, frame_width, DrawFunction);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 3);
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
