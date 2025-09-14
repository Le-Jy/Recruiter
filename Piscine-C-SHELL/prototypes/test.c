#include <assert.h>
#include <stdio.h>
struct test
{
int i;
};
int      fact(int *val)
{
assert(val != NULL);
if (*val > 1)
return (*val * fact(val - 1));
else
return 1;
}
int main(void)
{
int val = 2;
scanf("%d", &val);
printf("%d\n", fact(&val));
return 0;
}
