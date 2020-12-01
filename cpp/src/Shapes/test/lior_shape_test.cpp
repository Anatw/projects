///////////////////////////////////////////////////////////////////////////////
// File Name: shape_test.cpp                                                 //
// Author: Lior Cohen                                                        //
// Date 08/06/2020                                                           //
// Purpose: The test file for the shape class in the Shapes exercise         //
// Code Reviewer: Anat Wax                                                   //
///////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <ctime>
#include <iostream>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h> // system()
#include <string>
#include <time.h>

#include "circle.hpp"
#include "color.hpp"
#include "glut_utils.h"
#include "line.hpp"
#include "plane.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "simpledrawtext.hpp"
#include "square.hpp"

using namespace std;
using namespace ilrd;
using namespace std::chrono;

#define LIVES_NUM (5)
#define AMMUNITION (100)

// REGULAR COLORS
Color good(40, 40, 40);    // GREEN
Color between(80, 80, 80); // YELLOW
Color bad(32, 32, 64);     // RED

Color fill_good(2, 384, 174763);    // GREEN - FILL
Color fill_between(245, 256, 2141); // YELLOW - FILL
Color fill_bad(256, 256, 2049);     // RED -FILL

// GENERAL FLAGS
int open_screen = 1;
int pause_screen = 0;
int end_screen = 0;
int health_time_check = 0;
int reload_time_check = 0;

// MAIN PLANE DEFEINITIONS
Point p_plane(500, 850);
double l_plane = 50;
Color c_plane(1, 1, 1); // BLUE

// MISSILES STRUCT AND DEFINITIONS
typedef struct ammunition
{
    Point* left_round;
    Point* right_round;
    Line* left_projectile;
    Line* right_projectile;
    int on_off;
} ammu_t;

Color missiles(41, 40, 40); // MGENTA
ammu_t ammo[AMMUNITION];
int ammo_index = 0;
int total_ammo = AMMUNITION;

// NUMBER OF LIVES
typedef struct num_of_lives
{
    Point* position;
    Plane* live;
    int on_off;
} turns_t;

turns_t turns[LIVES_NUM];
int turns_index = 0;

// HEALTH BAR
Point p_health_bar(975, 200);
Rectangle r_health_bar(p_health_bar, double(90), fill_bad, 200, 20);

// HEALTH AND AMMO BUBBLES
typedef struct health_care
{
    Point* p_health;
    Circle* health;
    int on_off;
} hc_t;

hc_t more_health[LIVES_NUM];
int health_index = 0;

typedef struct reloading
{
    Point* p_reload;
    Square* reload;
    int on_off;
} reload_t;

reload_t more_ammo[LIVES_NUM];
int reload_index = 0;

clock_t health_start_t = 0;
clock_t health_end_t = 0;
struct timespec health_start, health_finish;
double health_elapsed = 0;

clock_t reload_start_t = 0;
clock_t reload_start_t = 0;
struct timespec reload_start, reload_finish;
double reload_elapsed = 0;

// CHECK POINT
Point* p = new Point();

// UTILITY FUNCTIONS
static void DrawFunction();
static int KeyboardFunction(unsigned char key, int x, int y);
static int MouseFunction(int button, int state, int x, int y);
static int MotionFunction(int x, int y);
static int TimerFunction();

static void InitializeArr();
static void InitializeTurns();
static void InitializeHealth();
static void InitializeReload();

///////////////////////////////////////////////////////////////////////////////
//                                  MAIN                                     //
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    // system("clear");
    /*--------------------------- mtrace(); */

    InitializeArr();
    InitializeTurns();
    InitializeHealth();
    InitializeReload();

    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    /* advanced: extra functionality */
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetMouseFunc(MouseFunction);
    DrawSetMotionFunc(MotionFunction);
    DrawSetTimerFunc(TimerFunction, 100);

    DrawMainLoop();

    printf("exit\n");

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
//                          UTILITY FUNCTIONS                                //
///////////////////////////////////////////////////////////////////////////////

static void DrawFunction()
{
    // DEFINING THE MAIN FRAME
    Point center_point(500, 500);
    Color c_frame(50, 50, 50); // WHITE
    Square frame(center_point, double(0), c_frame, 900);

    // CREATING THE CONTROLED PLANE
    Plane main_plane(p_plane, double(0), c_plane, l_plane);

    // OPENING SCREEN DRAWING
    if (1 == open_screen)
    {
        SimpleDrawText sdt;
        sdt.drawText("Click \"ENTER\" to start", 350, 500, 1, 0, 0);
    }

    // PAUSE SCREEN DRAWING
    else if (1 == pause_screen)
    {
        SimpleDrawText sdt;
        sdt.drawText("Click \"ENTER\" to continue", 350, 500, 1, 0, 0);
    }

    // END SCREEN DRAWING
    else if (1 == pause_screen)
    {
        SimpleDrawText sdt;
        sdt.drawText("Click \"ENTER\" to restart", 350, 500, 1, 0, 0);
    }

    // MAIN GAME DRAWING
    else if (0 == open_screen && 0 == pause_screen && 0 == end_screen)
    {
        if (0 == health_time_check)
        {
            clock_gettime(CLOCK_MONOTONIC, &health_start);
            health_time_check = 1;
        }

        if (0 == reload_time_check)
        {
            clock_gettime(CLOCK_MONOTONIC, &reload_start);
            reload_time_check = 1;
        }

        // KEY FEATURES DRAWINGS
        frame.Draw();
        r_health_bar.Draw();
        main_plane.Draw();

        // AMOUNT OF LIVES DRAWINGS
        int i = 0;
        for (i = 0; i < LIVES_NUM; ++i)
        {
            if (1 == turns[i].on_off)
            {
                turns[i].live->Draw();
            }
        }

        // AMOUNT OF AMMO DRAWINGS
        int current_ammo = total_ammo - ammo_index;
        std::string ammo_print = to_string(current_ammo);

        SimpleDrawText sdt;
        sdt.drawText("Ammo: ", 80, 10, 0, 1, 0);
        sdt.drawText(ammo_print, 150, 10, 0, 1, 0);

        // CONTROLED PLANE MISSILES DRAWINGS
        for (i = 0; i < AMMUNITION; ++i)
        {
            if (1 == ammo[i].on_off)
            {
                ammo[i].left_projectile->Draw();
                ammo[i].right_projectile->Draw();
            }
        }

        // HEALTH BUBBLES HANDLING
        clock_gettime(CLOCK_MONOTONIC, &health_finish);
        health_elapsed = (health_finish.tv_sec - health_start.tv_sec);

        // Health bubbles creation
        srand(time(NULL));
        int random_number = rand() % 5 + 10;

        // The last health bubble in the array is gone
        if (2 == more_health[4].on_off)
        {
            InitializeHealth();
            health_index = 0;
        }
        else if (random_number <= health_elapsed && 4 >= health_index)
        {
            more_health[health_index].on_off = 1;
            ++health_index;
            health_time_check = 0;
        }
        for (i = 0; i < LIVES_NUM; ++i)
        {
            if (1 == more_health[i].on_off)
            {
                more_health[i].health->Draw();
            }
        }

        // RELOAD BUBBLES HANDLING
        clock_gettime(CLOCK_MONOTONIC, &reload_finish);
        reload_elapsed = (reload_finish.tv_sec - reload_start.tv_sec);

        // Reload bubbles creation
        srand(time(NULL));
        random_number = rand() % 10 + 15;

        // The last reload bubble in the array is gone
        if (2 == more_reload[4].on_off)
        {
            InitializeReload();
            reload_index = 0;
        }
        else if (random_number <= reload_elapsed && 4 >= reload_index)
        {
            more_reload[reload_index].on_off = 1;
            ++reload_index;
            reload_time_check = 0;
        }
        for (i = 0; i < LIVES_NUM; ++i)
        {
            if (1 == more_reload[i].on_off)
            {
                more_reload[i].reload->Draw();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

static int KeyboardFunction(unsigned char key, int x, int y)
{
    const double move = 5;

    // START / PAUSE / RESUME GAME
    if ('p' == key)
    {
        // Pause the game
        if (0 == open_screen && 0 == pause_screen && 0 == end_screen)
        {
            pause_screen = 1;
        }
        // Start the game
        else if (1 == open_screen)
        {
            open_screen = 0;
        }
        // Resume the game
        else if (1 == pause_screen)
        {
            pause_screen = 0;
        }
        // Restart the game
        else if (1 == end_screen)
        {
            end_screen = 0;
        }
        cout << "ENTER was pressed" << endl;
    }

    else if (0 == open_screen && 0 == pause_screen && 0 == end_screen)
    {
        switch (key)
        {
        // Move the plane forward
        case ('w'):
            p_plane.Move(double(p_plane.GetX()), double(p_plane.GetY() - move));
            break;

        // Move the plane to the left
        case ('a'):
            p_plane.Move(double(p_plane.GetX() - move), double(p_plane.GetY()));
            break;

        // Move the plane backward
        case ('s'):
            p_plane.Move(double(p_plane.GetX()), double(p_plane.GetY() + move));
            break;

        // Move the plane to the right
        case ('d'):
            p_plane.Move(double(p_plane.GetX() + move), double(p_plane.GetY()));
            break;

        // Move the plane forward and to the left
        case ('q'):
            p_plane.Move(double(p_plane.GetX() - move),
                         double(p_plane.GetY() - move));
            break;

        // Move the plane forward and to the right
        case ('e'):
            p_plane.Move(double(p_plane.GetX() + move),
                         double(p_plane.GetY() - move));
            break;

        // Move the plane backward and to the left
        case ('z'):
            p_plane.Move(double(p_plane.GetX() - move),
                         double(p_plane.GetY() + move));
            break;

        // Move the plane backward and to the right
        case ('c'):
            p_plane.Move(double(p_plane.GetX() + move),
                         double(p_plane.GetY() + move));
            break;

        // Shooting
        case (32):

            // No ammo
            if (AMMUNITION == ammo_index)
            {
                cout << "space was pressed" << endl;
            }

            // There is ammo
            else if (*ammo[ammo_index].left_round == *p)
            {
                Point temp = p_plane;

                temp.Move(double(p_plane.GetX() - (0.2 * l_plane)),
                          double(p_plane.GetY() + (0.475 * l_plane)));

                *ammo[ammo_index].left_round = temp;

                temp.Move(double(p_plane.GetX() + (0.2 * l_plane)),
                          double(p_plane.GetY() + (0.475 * l_plane)));

                *ammo[ammo_index].right_round = temp;

                *ammo[ammo_index].left_projectile =
                    Line(*ammo[ammo_index].left_round, double(90), missiles,
                         double(l_plane / 5));

                *ammo[ammo_index].right_projectile =
                    Line(*ammo[ammo_index].right_round, double(90), missiles,
                         double(l_plane / 5));

                ammo[ammo_index].on_off = 1;

                ++ammo_index;
                cout << "space was pressed" << endl;
            }

            cout << "p_plane = " << p_plane << endl;

            break;

        // Exit the game
        case (0x1b): // ESC
            return (-1);
        }
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////

static int MouseFunction(int button, int state, int x, int y)
{
    /* printf("Mouse: %d,%d,%d,%d\n", button, state, x, y); */

    /*if (state == 1 && button == MOUSE_WHEEL_UP)
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
        drawCircle = state;
        return 1;
    }*/

    return 0;
}

///////////////////////////////////////////////////////////////////////////////

static int MotionFunction(int x, int y)
{
    printf("Mouse: %d,%d\n", x, y);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////

static int TimerFunction()
{
    if (0 == open_screen && 0 == pause_screen && 0 == end_screen)
    {
        int i = 0;

        // MISSILES MOVMENT
        for (i = 0; i < 100; ++i)
        {
            if (1 == ammo[i].on_off)
            {
                ammo[i].left_projectile->Move(double(0), double(-15));
                ammo[i].right_projectile->Move(double(0), double(-15));
            }

            // Missiles leaving the screen
            if (50 >= ammo[i].left_projectile->GetPosition().GetY())
            {
                ammo[i].on_off = 0;
            }
        }

        // HEALTH BUBBLES MOVMENT
        for (i = 0; i < LIVES_NUM; ++i)
        {
            if (1 == more_health[i].on_off)
            {
                more_health[i].health->Move(double(0), double(10));
            }

            if ((p_plane.GetX() - more_health[i].health->GetPosition().GetX() <=
                 20) &&
                (more_health[i].health->GetPosition().GetX() - p_plane.GetX() <=
                 20) &&
                (p_plane.GetY() - more_health[i].health->GetPosition().GetY() <=
                 20) &&
                (more_health[i].health->GetPosition().GetY() - p_plane.GetY() <=
                 20))
            {
                more_health[i].on_off = 2; // To be able to initialize
            }

            if (950 <= more_health[i].health->GetPosition().GetY())
            {
                more_health[i].on_off = 2; // To be able to initialize
            }
        }
    }

    return 1; /* draw */
}

///////////////////////////////////////////////////////////////////////////////

static void InitializeArr()
{
    int i = 0;
    for (i = 0; i < AMMUNITION; ++i)
    {
        ammo[i].left_round = new Point();
        ammo[i].right_round = new Point();
        ammo[i].left_projectile = new Line();
        ammo[i].right_projectile = new Line();
        ammo[i].on_off = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////

static void InitializeTurns()
{
    double angle = 0;
    double length = 25;

    turns[0].position = new Point(860, 960);
    turns[1].position = new Point(880, 960);
    turns[2].position = new Point(900, 960);
    turns[3].position = new Point(920, 960);
    turns[4].position = new Point(940, 960);

    turns[0].live = new Plane(*turns[0].position, angle, good, length);
    turns[1].live = new Plane(*turns[1].position, angle, good, length);
    turns[2].live = new Plane(*turns[2].position, angle, good, length);
    turns[3].live = new Plane(*turns[3].position, angle, good, length);
    turns[4].live = new Plane(*turns[4].position, angle, good, length);

    turns[0].on_off = 1;
    turns[1].on_off = 1;
    turns[2].on_off = 0;
    turns[3].on_off = 0;
    turns[4].on_off = 0;
}

static void InitializeHealth()
{
    double angle = 0;
    double radius = 20;
    int i = 0;

    srand(time(NULL));

    for (i = 0; i < LIVES_NUM; ++i)
    {
        more_health[i].p_health = new Point(rand() % 800 + 100, 100);
        more_health[i].health =
            new Circle(*more_health[i].p_health, angle, good, radius);
        more_health[i].on_off = 0;
    }
}

static void InitializeReload()
{
    double angle = 0;
    double length = 40;
    int i = 0;

    srand(time(NULL));

    for (i = 0; i < LIVES_NUM; ++i)
    {
        more_ammo[i].p_reload = new Point(rand() % 800 + 100, 100);
        more_ammo[i].reload =
            new Square(*more_ammo[i].p_reload, angle, good, length);
        more_ammo[i].on_off = 0;
    }
}
