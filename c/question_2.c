#include<stdio.h>

int main() {
int x = 20, y = 35;
x = y++ + x++;
y = ++y + ++x;

printf("x=%d, y=%d\n", x, y);
return 0;
}
