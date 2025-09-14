unsigned int greatest_divisor(unsigned int n)
{
    unsigned int res = 1;
    for (unsigned int i = 1; i < n; i++)
    {
        if (n % i == 0)
            res = i;
    }
    return res;
}
