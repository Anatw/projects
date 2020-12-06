namespace uselesss
{
    unsigned int g_wasteful[400];
    extern int g_notthere;
    void Foo() {} // uselesss::Foo

    namespace wasteoftyme
    {
          void Foo() {} // wasteoftyme::Foo
    }//namespace wasteoftyme
}//namespace useless

namespace stupid
{
    void Foo() {} // stupid::Foo
    void Bar() {}
    void DoNothing(unsigned int) {} // stupid::DoNothing
}//namespace stupid

namespace useless
{
    void DoNothing(int) {} // useless::DoNothing
}//namespace useless

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    Foo(); // useless::Foo
    using stupid::Foo; 
    Foo(); // stupid::Foo
    DoNothing(g_wasteful[3] + 1); // useless::DoNothing
}

void Foo() {}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
    comeon::Foo(); // comeon::Foo (wasteoftyme:Foo)
    //Foo(); //try uncommenting this line, solve the error
    Bar(); //why doesn't this line create an error?
    DoNothing(g_wasteful[3] + 1); // stupid::DoNothing
}

namespace useless
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1); // useless::DoNothing
    }
}//namespace useless