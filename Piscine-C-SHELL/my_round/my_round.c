int my_round(float n)
{
    int res;
    if (n > 0)
    {
        res = n + 0.5;
    }
    else
    {
        res = n - 0.5;
    }
    return res;
}
