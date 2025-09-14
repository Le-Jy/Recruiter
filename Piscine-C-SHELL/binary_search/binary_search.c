int binary_search(const int vec[], int size, int elt)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int pivot = left + (right - left) / 2;
        if (vec[pivot] == elt)
            return pivot;
        if (vec[pivot] < elt)
            left = pivot + 1;
        else
            right = pivot - 1;
    }
    return -1;
}
