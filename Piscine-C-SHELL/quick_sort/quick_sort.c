int partition(int *tab, int low, int high)
{
    int pivot = tab[low];
    int i = high;

    for (int j = high; j > low; j--)
    {
        if (tab[j] >= pivot)
        {
            int tmp = tab[j];
            tab[j] = tab[i];
            tab[i] = tmp;
            i--;
        }
    }
    int tmp = tab[i];
    tab[i] = tab[low];
    tab[low] = tmp;
    return i;
}

void rec(int *tab, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(tab, low, high);
        rec(tab, low, pivot - 1);
        rec(tab, pivot + 1, high);
    }
}

void quicksort(int *tab, int len)
{
    if (len > 1)
        rec(tab, 0, len - 1);
}
