unsigned array_min(const int arr[], unsigned start, unsigned size)
{
    int min = arr[start];
    unsigned res = start;
    for (unsigned i = start + 1; i < size; i++)
    {
        if (min > arr[i])
        {
            min = arr[i];
            res = i;
        }
    }
    return res;
}

void selection_sort(int arr[], unsigned size)
{
    for (unsigned i = 0; i < size; i++)
    {
        unsigned mini = array_min(arr, i, size);
        int tmp = arr[i];
        arr[i] = arr[mini];
        arr[mini] = tmp;
    }
}
