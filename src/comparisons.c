#include "s21_decimal.h"
#include <stdlib.h>
#include <math.h>

// закомментил уже существующую реализацию функции s21_is_less в файле s21_decimal.c

int max(int first, int second) { return first >= second ? first : second; }

// return value:
//               1 - true
//               0 - false

int s21_is_equal(s21_decimal first, s21_decimal second)
{
    int equal = 1;
    for(int i = 0; i < 4 && equal == 1; ++i)
        if(first.bits[i] != second.bits[i])
            equal = 0;

    return equal;
}

void intToBinary(unsigned int number, int** result)
{
    int i = 0;
    while(number > 0)
    {
        (*result)[i++] = number % 2;
        number /= 2;
    }
}

unsigned int binaryToInt(int* binary)
{
    unsigned int number = 0;
    for (int i = 0; i < 32; ++i)
        if(binary[i] == 1)
            number += pow(2, i);

    return number;
}

void multiplyBy10(unsigned int** number)
{
    int* numberCopy = (int*)malloc(32 * 7 * sizeof(int));
    if(numberCopy != NULL)
    {
        for (int i = 0; i < 7; ++i)
        {
            int* binary = (int*)malloc(32 * sizeof(int));
            if(binary != NULL)
            {
                intToBinary((*number)[i], &binary);
                for(int j = 0; j < 32; ++j)
                    numberCopy[i * 32 + j] = binary[j];
                free(binary);
            }
        }
        int* numberCopyMultipliedBy2 = (int*)malloc(32 * 7 * sizeof(int));
        if(numberCopyMultipliedBy2 != NULL)
        {
            numberCopyMultipliedBy2[0] = 0;
            numberCopyMultipliedBy2[1] = 0;
            for (int i = 0; i < 32 * 7 - 2; ++i)
                numberCopyMultipliedBy2[i + 2] = numberCopy[i];
            
            int* result = (int*)malloc(32 * 7 * sizeof(int));
            if(result != NULL)
            {
                int memory = 0;
                for (int i = 0; i < 7 * 32; ++i)
                {
                    int localResult = numberCopy[i] + numberCopyMultipliedBy2[i] + memory;
                    memory = localResult > 1 ? 1 : 0;
                    result[i] = localResult % 2;
                }

                for(int i = 0; i < 7; ++i)
                {
                    (*number)[i] = binaryToInt(result);
                }
                free(result);
            }
            free(numberCopyMultipliedBy2);
        }
        free(numberCopy);
    }
}

void normilize(s21_decimal numberWithMaxScale, s21_decimal otherNumber,
    unsigned int** newNumber)                                             // newNumber = otherNumber * 10^maxScale
{
    int scale = getScale(numberWithMaxScale);
    
    for (int i = 0; i < 3; ++i)
        (*newNumber)[i] = otherNumber.bits[i];

    for (int i = 0; i < scale; ++i)
        multiplyBy10(newNumber);
}

int s21_is_less(s21_decimal first, s21_decimal second)
{
    int result = -1;
    int firstSign = getSign(first);
    int secondSign = getSign(second);
    if(firstSign != secondSign)
    {
        result = firstSign;
    } else {
        if(getScale(first) == getScale(second))
        {
            int resultByModule = -1;
            for(int i = 2; i >= 0 && resultByModule == -1; --i)
                if(first.bits[i] > second.bits[i])
                    resultByModule = 0;
                else if(first.bits[i] < second.bits[i])
                    resultByModule = 1;
            result = resultByModule == -1
                ? 0
                : firstSign == 0
                    ? resultByModule
                    : 1 - resultByModule;
        } else {
            unsigned int* newNumber = (unsigned int*)malloc(sizeof(unsigned int) * 7);
            if(newNumber != NULL)
            {
                s21_decimal* numberWithMaxScale = getScale(first) >= getScale(second)
                    ? &first
                    : &second;

                normilize(numberWithMaxScale == &first
                    ? first, second
                    : second, first, &newNumber);
                
                int resultByModule = -1;
                if(newNumber[3] != 0 || newNumber[4] != 0 || newNumber[5] != 0)
                {
                    resultByModule = numberWithMaxScale == &first
                            ? 1 : 0;
                } else {
                    for(int i = 2; i >= 0 && resultByModule == -1; --i)
                        if(numberWithMaxScale->bits[i] < newNumber[i])
                            resultByModule = numberWithMaxScale == &first
                                ? 1
                                : 0;
                        else if(numberWithMaxScale->bits[i] > newNumber[i])
                            resultByModule = numberWithMaxScale == &first
                                ? 0
                                : 1;
                }
                free(newNumber);
                result = resultByModule == -1
                ? 0
                : firstSign == 0
                    ? resultByModule
                    : 1 - resultByModule;
            }
        }
    }

    return result;
}

int s21_is_less_or_equal(s21_decimal first, s21_decimal second)
{
    return s21_is_less(first, second) || s21_is_equal(first, second);
}

int s21_is_greater(s21_decimal first, s21_decimal second)
{
    return !s21_is_less(first, second) && !s21_is_equal(first, second);
}

int s21_is_greater_or_equal(s21_decimal first, s21_decimal second)
{
    return !s21_is_less(first, second);
}

int s21_is_not_equal(s21_decimal first, s21_decimal second)
{
    return !s21_is_equal(first, second);
}
