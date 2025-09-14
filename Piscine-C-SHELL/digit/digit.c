unsigned int digit(int n, int k)
{
    if (n <= 0 || k <= 0)
        return 0;
    for (int i = 0; i < k - 1; i++)
    {
        n /= 10;
    }
    unsigned int res = n % 10;
    return res;
}
