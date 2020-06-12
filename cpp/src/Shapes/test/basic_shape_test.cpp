static void DrawFunction()
{
    Point b_pos(500, 500);
    double angle_ = 12;
    Point left_p(180, 120);
    Color circle_color(40, 40, 40);
    Circle left(left_p, angle_, circle_color, rCircle);
    // left.SetPosition(left_p);
    // left.SetColor(circle_color);
    left.Draw();

    Point right_p(780, 120);
    Circle right(right_p, angle_, circle_color, rCircle);
    // right.SetPosition(right_p);
    // right.SetColor(circle_color);
    right.Draw();

    Color line_color(10, 20, 30);
    Line line(b_pos, angle_, line_color, 1);

    line.SetColor(line_color);
    line.Draw();
    //move:
    Point move_line(500, 300);
    Point line_cur = line.GetPosition();
    line_cur += move_line;
    line.Move_m(move_line);

    Square square(b_pos, angle_, Color(), 50);
    square.SetAngle(3);
    square.Revolve_m(square.GetPosition(), 37);
    square.Draw();

    double rec_angle = 45;
    Rectangle rec(b_pos, rec_angle, Color(), 130, 350);
    Point rec_pos(500, 800);
    rec.SetAngle(45);
    rec.SetPosition(Point(700, 500));
    rec.Revolve_m(rec.GetPosition(), 37);
    rec.Draw();

    //revolve:
    Point rev_point = rec.GetPosition();
    Point move_rec(0, 0);
    rev_point += move_rec;

    // int i = 0;
    // while ((i) < 50)
    // {
    //     double angle = 1;
    //     std::cout << rec.GetPosition() << std::endl;
    //     rec.Revolve_m(move_rec, angle);
    //     std::cout << rec.GetPosition() << std::endl;
    //     rec.Draw();
    //     ++i;
    //     ++angle;
    // }
}
