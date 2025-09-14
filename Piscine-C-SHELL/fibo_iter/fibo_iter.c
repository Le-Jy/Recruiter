unsigned long fibo_iter(unsigned long n)
{
    if (n == 0 || n == 1)
        return n;

    unsigned long q1 = 0;
    unsigned long q2 = 1;
    for (unsigned long i = 2; i <= n; i++)
    {
        unsigned long q3 = q1 + q2;
        q1 = q2;
        q2 = q3;
    }
    return q2;
}
