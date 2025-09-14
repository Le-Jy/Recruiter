unsigned int number_digits_rec(unsigned int n)
{
    if (n < 10)
    {
        return 1;
    }
    n /= 10;
    return number_digits_rec(n) + 1;
}
