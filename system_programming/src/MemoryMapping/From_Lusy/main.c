/*    */

#include <stdio.h>
#include <dlfcn.h>

#include "ar.h"
#include "libso1.h"

void MyFunc(void);

union
{
	void (*func_ptr) (void);
	void *func_address;
}u;

int main(int argc , char *argv[] , char **envp)
{
	typedef void (*bar_ptr) (void);
	void *lib_handle = NULL;
	
	
	bar_ptr dyn_ptr = NULL;

	MyFunc();
	
	foo();
	
	Bar1();
	
	/* run time linking */
	lib_handle = dlopen("./libso2.so", RTLD_LAZY);
	if (!lib_handle)
	{
		printf("dlopen: %s\n", dlerror());
		return (-1);
	} 
	
	*(void **)&dyn_ptr = dlsym(lib_handle,"Bar2");
	if ( !dyn_ptr )
	{
		printf("dlsym: %s\n", dlerror());
		return (-2);
	}
	
	dyn_ptr();
	
	u.func_ptr = MyFunc;
	printf("\n MyFunc address: %p\n", u.func_address);
	
	printf("\n MyFunc address: %p\n", (void *)((size_t)MyFunc));
	printf("\n foo address:    %p\n", (void *)((size_t)foo));
	printf("\n foo1 address:   %p\n", (void *)((size_t)foo1));
	printf("\n foo2 address:   %p\n", (void *)((size_t)foo2));
	printf("\n Bar1 address:   %p\n", (void *)((size_t)Bar1));
	printf("\n Bar2 address:   %p\n", (void *)((size_t)dyn_ptr));

	return 0 ;
}



void MyFunc(void)
{
	puts("\nYour in main :)\n");
}




























