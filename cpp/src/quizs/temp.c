
/*static*/
Singleton< int >::m_object = NULL;


/*static*/
Singleton< int >::m_initialized = 0;

int main()
{
    int i = Singleton<int>::GetInstance();

    return (0);
}

////////////////////////////////////////////////////////////////////////////////

template<typename T>
class Singleton : public noncopyable
{
public:
    ~Singleton();
    static T& GetInstance();

private:
    Singleton();

    static T *m_object;
    static bool m_initialized;
}


template<typename T>
Singleton< T >::Singleton()
{  
}

template<typename T>
static T& Singleton< T >::GetInstance()
{
    if ()
    {
        if (m_initialized = 0)
        {
            m_object = new T;
            m_initialized = 1;
        }
    }
    else
    {
        
    }

    return m_object; 
}

template<typename T>
Singleton< T >::~Singleton()
{
    delete m_object;
}
