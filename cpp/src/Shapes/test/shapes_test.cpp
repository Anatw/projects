/*******************************************************************************
                                Shapes
                          Written by Anat Wax
						     June 7th-13, 2020
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
#include "simpledrawtext.hpp"

using namespace ilrd;
double rCircle = 100;

int frame_length = 1000;
int frame_width = 1000;

Color turqois(134217985, 1, 1);
Color red(65536, 1, 1);
Color yellow_fill(134283520, 1, 1);
Color green_fill(134217984, 1, 1);
Color magenta_fill(134283265, 1, 1);
Color while_fill(134283521, 1, 1);

// Global flags:
int entring_screen = 1;
int game_over_screen = 0;
int winning_screen = 0;
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

#define NUM_LOGS (6)
#define NUM_BUBBLES (65)
int distance = (frame_length - (100 * 2)) / NUM_LOGS;

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

typedef struct Bubbles
{
    Point *initial_position;
    Circle *bubble;
} bubbles_t;

frog_t frog;
log_t logs[NUM_LOGS];
Rectangle lily_pad(Point(500, 930), -3, magenta_fill, lily_width, lily_length);
bubbles_t bubbles[NUM_BUBBLES];

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
        logs[i].position = new Point((rand() % (frame_width - (100 * 2))),
                                     (distance + (distance * i)));
        logs[i].log = new Rectangle(*logs[i].position, 0, fill_log, log_width,
                                    log_length);
        logs[i].speed = (rand() % 3) + 1;
        logs[i].direction = (rand() % 2) + 1;
        logs[i].left_border = new Point(((rand() % ((frame_width / 20) * 4)) +
                                         ((frame_width / 20))),
                                        (distance + (distance * i)));
        logs[i].right_border = new Point(((rand() % ((frame_width / 20) * 16)) +
                                          ((frame_width / 20) * 19)),
                                         (distance + (distance * i)));
        logs[i].checked = 0;
    }
}

static void InitializeBubbles()
{
    srand(time(NULL));

    for (int i = 0; i < NUM_BUBBLES; ++i)
    {
        //Generate rendom position for bubbles:
        bubbles[i].initial_position = new Point(rand() % frame_width,
                                                rand() % frame_length);
        bubbles[i].bubble = new Circle(*bubbles[i].initial_position, 0,
                                       while_fill, (rand() % 2) + 1);
    }
}

static void DrawFunction()
{
    if (entring_screen)
    {
        SimpleDrawText sdt;
        sdt.drawText("The frog and the log", 310, 440, 0, 1, 0);
        sdt.drawText("Help the frog cross the river ", 280, 380, 0, 0, 1);
        sdt.drawText("without falling into the water", 275, 360, 0, 0, 1);
        sdt.drawText("Click 'S' to start", 330, 290, 1, 0, 0);
        sdt.drawText("Created by Anat Wax   (c).2020", 270, 180, 41, 40, 40);
    }

    if (winning_screen)
    {
        SimpleDrawText sdt;
        sdt.drawText("Well played!! Your frog has made it through the river",
                     200, 420, 41, 40, 40);
        sdt.drawText("If you wish to play again, press 'S'", 280, 360, 0, 1, 0);
        sdt.drawText("To exit game press 'ESC'", 310, 300, 0, 1, 0);
    }

    if (game_over_screen)
    {
        SimpleDrawText sdt;
        sdt.drawText("You've played well, but not well enough! your frog has drawned...", 165, 400, 1, 0, 0);
        sdt.drawText("If you wish to try again, press 'S'", 280, 350, 1, 0, 0);
        sdt.drawText("To exit game press 'ESC'", 310, 300, 1, 0, 0);
    }

    if (!entring_screen && !game_over_screen && !winning_screen)
    {
        // Generating water
        Point water1_pos(x_water1, y_water1);
        Rectangle water1(water1_pos, 0, turqois, 1000, 1000);
        water1.Draw();

        for (int i = 0; i < NUM_BUBBLES; ++i)
        {
            bubbles[i].bubble->Draw();
        }

        Rectangle game_frame(Point(500, 500), 0, red, frame_width - 1,
                             frame_length - 1);
        game_frame.Draw();

        lily_pad.Draw();

        Rectangle end_pad(Point(500, 45), 1.3, magenta_fill, lily_width,
                          (lily_length * 2));
        end_pad.Draw();

        for (int i = 0; i < NUM_LOGS; ++i)
        {
            logs[i].log->Draw();
        }

        frog.frog->Draw();
    }
}

static int KeyboardFunction(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;

    if (key == 'S') // Press 'S' to start playing
    {
        InitializeLogs();
        InitializeBubbles();
        InitializeFrog();

        entring_screen = 0;
        game_over_screen = 0;
        winning_screen = 0;
    }
    else if (key == 0x1b /* ESC */)
    {
        return -1;
    }

    if (!entring_screen)
    {
        if (key == 'r') // Restart the game
        {
            game_over_screen = 0;
            entring_screen = 0;
            winning_screen = 0;
        }

        if (key == 'w')
        {
            int new_y = frog.frog->GetPosition().GetY() -
                        (distance + (distance * frog.current_log));
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
            int new_y = frog.frog->GetPosition().GetY() +
                        (distance + (distance * frog.current_log));
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
            winning_screen = 1;

            //return -1;
        }
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
    if (!entring_screen)
    {
        int i = 0;

        for (i = 0; i < NUM_BUBBLES; ++i)
        {
            Point rev((bubbles[i].initial_position->GetX() + 5),
                      bubbles[i].initial_position->GetY());
            bubbles[i].bubble->Revolve_m(rev, 3);
        }

        // Move logs in random directions:
        for (i = 0; i < NUM_LOGS; ++i)
        {
            if (LEFT == logs[i].direction)
            {
                Point log_point((-2 * logs[i].speed), 0);
                logs[i].log->Move_m(log_point);
            }
            else // (RIGHT == logs[i].direction)
            {
                Point log_point((2 * logs[i].speed), 0);
                logs[i].log->Move_m(log_point);
            }
        }

        // Randomly decide if a log should change direction:
        for (i = 0; i < NUM_LOGS; ++i)
        {
            // Enter this part only if you haven't been checked lately(1) or
            //moved past the frame lately(2):
            if (0 == logs[i].checked)
            {
                if (logs[i].log->GetPosition().GetX() <=
                        logs[i].left_border->GetX() ||
                    logs[i].log->GetPosition().GetX() >=
                        logs[i].right_border->GetX())
                {
                    logs[i].direction = (rand() % 2) + 1;
                    logs[i].checked = 1;
                }
            }
        }

        // If log went out of frame (X axe):
        for (i = 0; i < NUM_LOGS; ++i)
        {
            // Enter this part only if you havn't crosed
            // the end of the fram lately:
            if (2 != logs[i].checked)
            {
                if (logs[i].log->GetPosition().GetX() <= 50 ||
                    logs[i].log->GetPosition().GetX() >= 950)
                {
                    int decide = (rand() % 2) + 1;

                    if (1 == decide)
                    {
                        (logs[i].direction == 1) ? (logs[i].direction = 2)
                                                 : (logs[i].direction = 1);
                    }
                    else
                    {
                        if (logs[i].log->GetPosition().GetX() <= 50)
                        {
                            Point other_side((frame_width + (log_width / 2) + 5),
                                             logs[i].log->GetPosition().GetY());
                            logs[i].log->SetPosition(other_side);
                        }
                        else // (logs[i].position->GetX() >= frame_width)
                        {
                            Point other_side((0 - (log_width / 2) - 5),
                                             logs[i].log->GetPosition().GetY());
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
            // Frog is inside the boundery of the lily_pad:
            if (frog.frog->GetPosition().GetX() >=
                    (lily_pad.GetPosition().GetX() - half_lily_l) &&
                frog.frog->GetPosition().GetX() <=
                    (lily_pad.GetPosition().GetX() + half_lily_l) &&
                frog.frog->GetPosition().GetY() >=
                    (lily_pad.GetPosition().GetY() - half_lily_w) &&
                frog.frog->GetPosition().GetY() <=
                    (lily_pad.GetPosition().GetY() + half_lily_w))
            {
                return 1;
            }
        }

        for (i = 0; i < NUM_LOGS; ++i)
        {
            // Frog is inside the boundery of a log:
            if (frog.frog->GetPosition().GetX() >=
                    (logs[i].log->GetPosition().GetX() - half_log_l) &&
                frog.frog->GetPosition().GetX() <=
                    (logs[i].log->GetPosition().GetX() + half_log_l) &&
                frog.frog->GetPosition().GetY() >=
                    (logs[i].log->GetPosition().GetY() - half_log_w) &&
                frog.frog->GetPosition().GetY() <=
                    (logs[i].log->GetPosition().GetY() + half_log_w))
            {
                Point frog_new_pos(logs[i].log->GetPosition().GetX(),
                                   logs[i].log->GetPosition().GetY());
                frog.frog->SetPosition(frog_new_pos);

                return 1;
            }
        }
        // If frog is not on a log
        for (i = 0; i < NUM_LOGS; ++i)
        {
            if (frog.frog->GetPosition().GetX() <
                    (logs[i].log->GetPosition().GetX() - (half_log_l + 5)) ||
                frog.frog->GetPosition().GetX() >
                    (logs[i].log->GetPosition().GetX() + (half_log_l + 5)) ||
                frog.frog->GetPosition().GetY() <
                    (logs[i].log->GetPosition().GetY() - (half_log_w + 5)) ||
                frog.frog->GetPosition().GetY() >
                    (logs[i].log->GetPosition().GetY() + (half_log_w + 5)))
            {
                if (frog.frog->GetPosition().GetY() <= won)
                {
                    winning_screen = 1;
                }
                else // Frog fell into the water
                {
                    game_over_screen = 1;
                    //return -1;
                }
            }
        }
    }

    return 1; /* draw */
}

int main(int argc, char *argv[])
{
    InitializeLogs();
    InitializeBubbles();
    InitializeFrog();

    //DrawCreateMenu();
    DrawInit(argc, argv, frame_length, frame_width, DrawFunction);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 15);

    DrawMainLoop();

    return (0);
}
