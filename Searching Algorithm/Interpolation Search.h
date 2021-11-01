#pragma once

template <class T>
int interpolationSearch(T* array, unsigned int nElements, T value)
{
    if (value < array[0] || array[nElements-1] < value)
        return -1;

    unsigned int left = 0;
    unsigned int right = nElements - 1;

    while (left <= right)
    {
        
        int pivot = 
    }
}