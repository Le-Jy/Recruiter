unsigned char rol(unsigned char value, unsigned char roll)
{
    while (roll > 0)
    {
        if (value & (1 << 7))
            value = (value << 1) + 1;
        else
        {
            value = value << 1;
        }
        roll--;
    }
    return value;
}
