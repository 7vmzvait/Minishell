#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

void ft_putstr(char *str, int *ret)
{
    if (str == NULL)
        str = "(null)";
    while (*str)
        *ret += write(1, str++, 1);
}
void ft_putnbr(long nbr, int *ret)
{
    char *base = "0123456789";
    if(nbr < 0)
    {
        *ret += write(1, "-", 1);
        nbr = nbr * -1;
    }
    if(nbr >= 10)
        ft_putnbr((nbr / 10), ret);
    *ret += write(1, &base[nbr % 10], 1);
}

void ft_puthexa(unsigned int nbr, int *ret)
{
    char *hexa = "0123456789abcdef";
    if(nbr >= 16)
        ft_puthexa((nbr / 16), ret);
    *ret += write(1, &hexa[nbr % 16], 1);
}

int ft_printf(const char *format, ... )
{
    va_list ap;
    int ret = 0;

    va_start(ap, format);
   if(!format)
       return -1;
    while(*format != '\0')
    {
        if(*format == '%')
        {
            format++;
            if(*format == 'd')
                ft_putnbr((long) va_arg(ap, int), &ret);
            else if(*format  == 's')
                ft_putstr(va_arg(ap, char *), &ret);
            else if(*format == 'x')
                ft_puthexa(va_arg(ap, unsigned int), &ret);
        }
        else
            ret += write(1, format, 1);
        format++;
    }
    va_end(ap);
    return ret;
}