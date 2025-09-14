#include "merge_sort.hh"

void merge_sort(iterator_type begin, iterator_type end)
{
    if (end - begin > 1)
    {
        iterator_type middle = begin + (end - begin) / 2;
        merge_sort(begin, middle);
        merge_sort(middle, end);
        std::inplace_merge(begin, middle, end);
    }
}
