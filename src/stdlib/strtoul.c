/**
 * @file        strtoul.c
 * @author      Carlos Fernandes
 * @version     1.0
 * @date        08 May, 2020
 * @brief       Convert an ASCII string into an integer
*/

/* Includes ----------------------------------------------- */
#include <stdlib.h>
#include <ctype.h>


/* Private types ------------------------------------------ */


/* Private constants -------------------------------------- */
#define	ULONG_MAX  ((unsigned long)(~0L))

/* Private macros ----------------------------------------- */


/* Private variables -------------------------------------- */


/* Private function prototypes ---------------------------- */


/* Private functions -------------------------------------- */
unsigned long strtoul(const char *nptr, char **endptr, int32_t base)
{
	register const char *s = nptr;
	register unsigned long acc;
	register int32_t c;
	register unsigned long cutoff;
	register int32_t neg = 0, any, cutlim;

	do {
		c = *s++;
	} while (ISSPACE(c));

	if (c == '-')
    {
		neg = 1;
		c = *s++;
	}
    else if (c == '+')
    {
		c = *s++;
    }

	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X'))
    {
		c = s[1];
		s += 2;
		base = 16;
	}

	if (base == 0)
    {
		base = c == '0' ? 8 : 10;
    }

	cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;

	for (acc = 0, any = 0;; c = *s++)
    {
		if(ISDIGIT(c))
        {
			c -= '0';
        }
		else if(ISALPHA(c))
        {
			c -= ISUPPER(c) ? 'A' - 10 : 'a' - 10;
        }
		else
        {
			break;
        }

		if (c >= base)
		{
            break;
        }

		if(any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
        {
			any = -1;
        }
		else
        {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if(any < 0)
    {
		acc = ULONG_MAX;
	}
    else if(neg)
    {
		acc = -acc;
    }
	if(endptr != 0)
    {
		*endptr = (char *) (any ? s - 1 : nptr);
    }

	return (acc);
}