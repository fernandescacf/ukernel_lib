#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

extern int32_t stdio_read(char *str, uint32_t bytes);

int scanf(char *str, ...)
{
    va_list vl;
    int i = 0, j = 0, ret = 0;
    char buff[201] = {0};
    char *out_loc;

    // Ensure we have a terminator character
    buff[stdio_read(buff, sizeof(buff) - 1)] = 0x0;
    
    va_start(vl, str);
    i = 0;
    while (str && str[i])
    {
        if (str[i] == '%')
        {
            i++;
            switch (str[i])
            {
            case 'c':
            {
                *(char *)va_arg(vl, char *) = buff[j];
                j++;
                ret++;
                break;
            }
            case 'd':
            {
                *(int *)va_arg(vl, int *) = strtoul(&buff[j], &out_loc, 10);
                j += out_loc - &buff[j];
                ret++;
                break;
            }
            case 'x':
            {
                *(int *)va_arg(vl, int *) = strtoul(&buff[j], &out_loc, 16);
                j += out_loc - &buff[j];
                ret++;
                break;
            }
            case 's':
            {
                char *arg_str = va_arg(vl, char*);
                strcpy(arg_str, &buff[j]);
                j += strlen(arg_str);
                ret++;
                break;
            }
            }
        }
        else
        {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    va_end(vl);
    return ret;
}