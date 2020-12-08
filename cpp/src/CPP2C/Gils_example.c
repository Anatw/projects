/*
class X:
{
public:
   explicit X( int num= 0);
private:
   int m_num;
}
 
X::X( int num ): m_num(num)
{}
 
int main()
{
   X x(5);
}
*/

struct X
{
    int m_num;
};

void X_Constructor(struct X *p_this, int num)
{
    p_this->m_num = num;
}
int main_cpp2c_X()
{
    struct X x;
    X_Constructor(&x, 5);
}

/*
class Y
{
public:
   virtual ~Y(){}
   virtual void Foo();
   void Bar()const;
private:
   int x;
};
 
int main()
{
   Y y;
   y.Foo();
   y.Bar();
}
*/

struct Y;

struct VTable_Y
{
    void (*Destructor)(struct Y *);
    void (*Foo)(struct Y *);
};

struct Y
{
    VTable_Y *v_ptr;
    int x;
};

void Y_Destructor(struct Y *p_this)
{
}

void Y_Foo(struct Y *p_this)
{
}

void Y_Bar(struct Y *p_this)
{
}

VTable_Y g_VTable_Y = {Y_Destructor, Y_Foo};

void Y_Constructor(struct Y *p_this)
{
    p_this->v_ptr = &g_VTable_Y;
}

int main_cpp2c_Y()
{
    struct Y y;
    Y_Constructor(&y);
    y.v_ptr->Foo(&y);
    Y_Bar(&y);

    y.v_ptr->Destructor(&y);
}
