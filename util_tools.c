
#include "ft_select.h"

void	print_info(t_pos *pos)
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 0), 1, ft_putchar);
	ft_printf(" {U.B.T.cyan.}act_co    = %03d/{eoc}\n", pos->act_co);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 1), 1, ft_putchar);
	ft_printf(" {U.B.T.cyan.}act_li    = %03d/{eoc}\n", pos->act_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 2), 1, ft_putchar);
	ft_printf(" {U.B.T.cyan.}tot_co    = %03d/{eoc}\n", pos->tot_co);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 3), 1, ft_putchar);
	ft_printf(" {U.B.T.cyan.}tot_li    = %03d/{eoc}\n", pos->tot_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 4), 1, ft_putchar);
	ft_printf(" {U.B.T.green.}start_co  = %03d/{eoc}\n", pos->start_co);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 5), 1, ft_putchar);
	ft_printf(" {U.B.T.green.}start_li  = %03d/{eoc}\n", pos->start_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 6), 1, ft_putchar);
	ft_printf(" {U.B.T.red.}max_co    = %03d/{eoc}\n", pos->max_co);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 7), 1, ft_putchar);
	ft_printf(" {U.B.T.red.}max_li    = %03d/{eoc}\n", pos->max_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 8), 1, ft_putchar);
	//ft_printf(" {U.B.T.blue.}let_nb    = %03d/{eoc}\n", (pos->tot_li - pos->start_li) * pos->max_co + pos->act_co);
	ft_printf(" {U.B.T.blue.}let_nb    = %03d/{eoc}\n", pos->let_nb);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 9), 1, ft_putchar);
	ft_printf(" {U.B.T.blue.}len_ans   = %03d/{eoc}\n", ft_strlen(pos->ans));
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 10), 1, ft_putchar);
	ft_printf(" {U.B.T.blue.}mode   = %03d/{eoc}\n", pos->mode);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}


int poussin = 0;

void	check_poussin(char c/*, t_pos *pos*/)
{
	if (poussin == 0 && c == 'e')
		poussin = 1;
	else if (poussin == 1 && c == 'x')
		poussin = 2;
	else if (poussin == 2 && c == 'i')
		poussin = 3;
	else if (poussin == 3 && c == 't')
	{
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		//		close(pos->history);
		exit(0);
	}
	else
		poussin = 0;
}



void	clean_screen(t_pos *pos)
{
	(void)pos;
	if (pos->act_li < pos->max_li)
	{
		tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->start_li), 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	if (pos->act_li == pos->max_li)
	{
			tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->start_li - 1), 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
/*	int	cl_screen;

	cl_screen = pos->start_li;
	while (cl_screen < pos->max_li)
	{
		tputs(tgoto(tgetstr("cm", NULL), pos->start_co, cl_screen++), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		tputs(tgetstr("cb", NULL), 1, ft_putchar);
	}

*/}


