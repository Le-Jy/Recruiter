int int_palindrome(int n)
{
    int res = 0;
    if (n >= 0)
    {
        unsigned long i = 10;
        int tmp = n;
        for (; tmp; i *= 10)
        {
            tmp /= 10;
        }
        i /= 100;
        unsigned long j = 10;
        for (; j <= i; i /= 10, j *= 10)
        {
            if (n % j != n / i)
                break;
        }
        if (j >= i)
            res = 1;
    }
    return res;
}
