#include <stdio.h>

static int max_in_arr(int arr[26])
{
    int ind_max = 0;
    int max = arr[0];
    for (int i = 1; i < 26; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            ind_max = i;
        }
    }
    return ind_max;
}

void freq_analysis(const char text[], const char table[])
{
    int rec[26] = { 0 };
    int i = 0;
    while (text[i])
    {
        rec[text[i] - 'A'] += 1;
        i++;
    }
    int count[26] = { 0 };
    for (int j = 0; table[j]; j++)
    {
        int max_ind = max_in_arr(rec);
        count[max_ind] = table[j];
        rec[max_ind] = -1;
    }
    for (int j = 0; j < 26; j++)
    {
        if (count[j] != 0)
            printf("%c %c\n", j + 'A', count[j]);
    }
}
