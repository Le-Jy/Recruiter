#include "my_atoi.h"

int my_atoi(const char *str)
{
    int num = 0;
    size_t i = 0;
    int neg = 0;
    while (str[i] == ' ' || str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-' || str[i] == '+')
        {
            if (str[i + 1] > '9' || str[i + 1] < '0')
                return 0;
            if (str[i] == '-')
                neg = 1;
        }
        i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] != '\0')
        return 0;
    return (neg) ? num * -1 : num;
}
