int my_pow(int a, int b)
{
    int res = 1;
    for (int i = 0; i < b / 2; i++)
    {
        res *= a * a;
    }
    if (b % 2 == 0)
        return res;
    return res * a;
}
