

class Shapes
{
public:
    virtual void Draw();
    virtual void drawInternal(); //Draw will call this function - to make sure that function draw is always called first.
    inline Point GetPosition();
    inline void SetPosition();
    inline getColor();
    inline setColoe();
    inline getAngle();
    inline setAngle();
    virtual Rotate(double delta_angle);
    virtual Revolve(Point c_point, double angle);
    virtual Move(Point vector);

private:
    Point possition;
    double angle;
    Color color;
};

class Line : public Shapes
{
public:
    int getLength();
    void drawInternal();

private:
    int length;
};

class Circle : public Shapes
{
public:
    int getRadius();
    void drawInternal();

private:
    int radius;
};

class Rectangle : public Shapes
{
public:
    int getLength();
    int GetWidth();
    void drawInternal();

private:
    int width;
    int length;
};

class Square : public Shapes
{
public:
    int getLength();
    void drawInternal();

private:
    int edge;
};
