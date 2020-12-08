typedef struct List List_t;
typedef struct Person
{
    int age;
    char *name;
}Person_t;

void *ll_find(List_t *list, int key);

int main()
{
    
    return 0;
}

void foo(List_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);
    Person_t *p = static_cast<Person_t *>(vv);
    p->age = age;
}

void *ll_find(List_t *list, int key)
{
    (void)key;
    void *to_return = list;

    return(to_return);
}