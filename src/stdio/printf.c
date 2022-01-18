#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

extern int32_t stdio_write(char *str, size_t len);

int vsprintf(char *buff, const char *fmt, va_list args)
{
    int i = 0, j = 0;
    char tmp[20];

    while (fmt && fmt[i])
    {
        if (fmt[i] == '%')
        {
            i++;
            switch (fmt[i])
            {
            case 'c':
            {
                buff[j] = (char)va_arg(args, int);
                j++;
                break;
            }
            case 'd':
            {
                itoa(va_arg(args, int), tmp, 10);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                break;
            }
            case 'x':
            {
                itoa(va_arg(args, int), tmp, 16);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                break;
            }
            case 's':
            {
                char *arg_str = va_arg(args, char*);
                strcpy(&buff[j], arg_str);
                j += strlen(arg_str);
                break;
            }
            default:
            {
                i--;
                buff[j] = fmt[i];
                j++;
            }
            }
        }
        else
        {
            buff[j] = fmt[i];
            j++;
        }
        i++;
    }

//    buff[j] = 0x0;

//    return ++j;

    return j;
}

int sprintf(char *str, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int ret = vsprintf(str, format, args);
    va_end(args);
    return ret;
}

int printf(char *str, ...)
{
    va_list args;
    char buff[256] = {0};
    va_start(args, str);
    int ret = vsprintf(buff, str, args);
    if(ret > 0) stdio_write(buff, ret);
    va_end(args);
    return ret;
}

#if 0
int printf(char *str, ...)
{
    va_list vl;
    int i = 0, j = 0;
    char buff[200] = {0}, tmp[20];
    va_start(vl, str);
    while (str && str[i])
    {
        if (str[i] == '%')
        {
            i++;
            switch (str[i])
            {
            case 'c':
            {
                buff[j] = (char)va_arg(vl, int);
                j++;
                break;
            }
            case 'd':
            {
                itoa(va_arg(vl, int), tmp, 10);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                break;
            }
            case 'x':
            {
                itoa(va_arg(vl, int), tmp, 16);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                break;
            }
            case 's':
            {
                char *arg_str = va_arg(vl, char*);
                strcpy(&buff[j], arg_str);
                j += strlen(arg_str);
                break;
            }
            default:
            {
                i--;
                buff[j] = str[i];
                j++;
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

    stdio_write(buff);

    va_end(vl);
    return j;
}
#endif