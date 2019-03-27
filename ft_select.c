/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bjuarez <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 16:29:23 by bjuarez      #+#   ##    ##    #+#       */
/*   Updated: 2019/03/27 16:36:03 by bjuarez     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <curses.h>

/*int        main(int ac, char **av)
 {
 char    *term;
 char    *buf;
 int        res;

 buf = NULL;
 term = getenv("BLABLA");
 printf("%s\n", term);
 res = tgetent(buf, term);
 printf("res = %d, buf = %s\n", res, buf);
 return (0);
 }*/

#include <stdlib.h>
#include <stdio.h>

#include <curses.h>
#include <term.h>


int init_term()
{
    int ret;
    char *term_type = getenv("TERM");

    if (term_type == NULL)
    {
        fprintf(stderr, "TERM must be set (see 'env').\n");
        return -1;
    }

    ret = tgetent(NULL, term_type);

    if (ret == -1)
    {
        fprintf(stderr, "Could not access to the termcap database..\n");
        return -1;
    }
    else if (ret == 0)
    {
        fprintf(stderr, "Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
        return -1;
    }

    return 0;
}

int        ft_putchar(int c)
{
    write(1, &c, 1);
    return (0);
}

int main(int argc, char **argv)
{
    int ret = init_term();
    int    col;
    int    line;
    char *test;
    int ret2;
    char buf[3];
    char    *name_term;
    struct    termios term;

    name_term = getenv("TERM");
    tgetent(NULL, name_term);
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON);
    term.c_lflag &= ~(ECHO);

    tcsetattr(0, TCSADRAIN, &term);
    col = 0;
    line = 0;
    test = NULL;
  //    On évite les warnings pour variables non utilisées.
    (void)argc;
    (void)argv;

    while (1)
    {
        ret2 = read(0, buf, 1);
        tputs(buf , 1, ft_putchar);
    }
    if (ret == 0)
    {
    //     Le déroulement de notre programme se fera ici.
        printf("on a gagne a la place du truc bleu\n");
        col = tgetnum("co");
        line = tgetnum("li");
        test = tgetstr("cl", NULL);
        int i = 0;
        while (test[i + 1])
            write(1, &test[i++], 1);
        printf("\n");
        i = 1;
        while (test[i])
            write(1, &test[i++], 1);
        printf("col = %d et li = %d\n", col, line);
    }
    return ret;
}
