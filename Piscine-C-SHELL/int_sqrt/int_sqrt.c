int int_sqrt(int n)
{
    int res = -1;
    if (n >= 0)
    {
        for (int i = 0; i * i <= n; i++)
            res = i;
    }
    return res;
}
