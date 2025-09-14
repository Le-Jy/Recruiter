double pi_generator(int precision)
{
    double res = 1 + precision / (precision * 2 + 1);
    if (precision > 0)
    {
        for (int i = precision; i >= 1; i--)
        {
            res = res * i / (i * 2.0 + 1) + 1;
        }
    }
    else
        res = 1.;
    return 2 * res;
}
