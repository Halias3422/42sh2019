
#include "ft_select.h"

int init_term()
{
	int ret;
	char *term_type = getenv("TERM");

	ret = 0;
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


int		find_key(char *buf, t_pos *pos)
{
//	if (ft_strncmp(buf + 1, "[A", 2) == 0) // fleche haut
//		;
	if (pos->act_co < pos->tot_co && ft_strncmp(buf + 1, "[C", 2) == 0) // fleche droite
	{
		tputs(buf, 1, ft_putchar);
		pos->act_co++;

	}
	if (pos->act_co >= 0 && ft_strncmp(buf + 1, "[D", 2) == 0) // fleche gauche
	{
		tputs(buf, 1, ft_putchar);
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
	}
//	if (ft_strncmp(buf + 1, "[B", 2) == 0) // fleche bas
//		;
	if (buf[0] == 10)
	{
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		exit (0);
	}
	return (1);
}

int poussin = 0;

void	check_poussin(char c)
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
		exit(0);
	}
	else
		poussin = 0;
}

int		remove_str(t_pos *pos)
{
	char	*swap;

	swap = NULL;
	if (pos->tot_co == 0 && pos->act_co == 0)
	{
		if (!pos->ans)
		{
			free(pos->ans);
			pos->ans = NULL;
		}
		return (1);
	}
	else if (pos->act_co != 0)
	{
		swap = ft_strnew(pos->act_co + 1);
		swap = ft_strncpy(swap, pos->ans, pos->act_co - 1);
		swap = ft_strjoinf(swap, pos->ans + pos->act_co, 1);
		free(pos->ans);
		pos->ans = swap;
		return (1);
	}
	return (0);
}

void	fill_str(char *buf, t_pos *pos)
{
	char	*swap;

	swap = NULL;
/*	if (pos->ans == NULL)
	{
		pos->ans = ft_strnew(1);
		pos->ans[0] = buf[0];
	//	ft_printf("\npos->ans[0] = %c", pos->ans[0]);
	}
	else */if (pos->act_co == pos->tot_co)
		pos->ans = ft_strjoinf(pos->ans, buf, 1);
	else
	{
		swap = ft_strnew(pos->act_co);
		swap = ft_strncpy(swap, pos->ans, pos->act_co);
		swap = ft_strjoinf(swap, buf, 1);
		swap = ft_strjoinf(swap, pos->ans + pos->act_co, 1);
		free(pos->ans);
		pos->ans = swap;
	}
}

void	clean_screen(t_pos *pos)
{
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(tgetstr("cb", NULL), 1, ft_putchar);
	(void)pos;
}

void	get_start_info(char *buf, int *start_li, int *start_co)
{
	int		i;

	i = 0;
	while (buf[i] && buf[i] != '[')
		i++;
	if (buf[i] == '\0')
		*start_li = -1;
	else
		*start_li = ft_atoi(buf + i + 1) - 1;
	i = 0;
	while (buf[i] && buf[i] != ';')
		i++;
	if (buf[i] == '\0')
		*start_co = -1;
	else
		*start_co = ft_atoi(buf + i + 1) - 1;
}

int 	main()
{

	int		ret;
	int		col;
	int		line;
	char	*test;
	int		ret2;
	char	buf[10];
//	char	*name_term;
	struct	termios term;
	int		i;
	t_pos	pos;
	char	*tmp;
	char	*save_pos_prompt;
	int		max_co;
	int		max_li;
	char	*tamp;
	int		start_li;
	int		start_co;

	tamp = NULL;
	tmp = NULL;
//	name_term = getenv("TERM");
//	tgetent(NULL, name_term);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSADRAIN, &term);

//	ret = 0;
	ret = init_term();
	col = 0;
	line = 0;
	test = NULL;
	i = 0;
	pos.ans = ft_strnew(1);
	pos.tot_co = 0;
	pos.tot_li = 0;
	pos.act_co = 0;
	pos.act_li = 0;
	save_pos_prompt = NULL;
	max_co = tgetnum("co") - 1;
	max_li = tgetnum("li") - 1;

	write (1, "\033[6n", 4);
	ret2 = read(1, buf, 8);
	get_start_info(buf + 1, &start_li, &start_co);
	if (start_li == -1 || start_co == -1)
		ft_printf("FATAL ERROR\n");
	bzero(buf, 10);
//	ft_printf("ligne %d et colonne %d\n", start_li, start_co);
	pos.act_li = start_li;
	pos.act_co = start_co;
	pos.tot_li = start_li;
	pos.tot_co = start_co;
	while (1)
	{
		i = 0;
		ret2 = read(0, buf, 10);
		if (buf[1])
			find_key(buf, &pos);
		else
		{
			if (buf[0] == 127)
			{
				if (remove_str(&pos) == 1)
				{
					tputs(tgetstr("le", NULL), 1, ft_putchar);
					tputs(tgetstr("dc", NULL), 1, ft_putchar);	
					pos.tot_co -= pos.tot_co == 0 ? 0 : 1;
					pos.act_co -= pos.act_co == 0 ? 0 : 1;
					if (pos.tot_co == 0 && pos.tot_li > 0)
					{	
						pos.tot_li -= 1;
						pos.tot_co = max_co;
						pos.act_co = max_co;
						tputs(tgoto(tgetstr("cm", NULL), max_co, pos.tot_li), 1, ft_putchar);
					}



				}
			}
			else if (buf[0] == 10)
			{
				void(pos);
			}
			else if (buf[0] == 32)
			{
				clean_screen(&pos);
			}
			else if (buf[0] != 127/* && buf[0] != 10*/ && buf[0] != 32)
			{
				if (pos.tot_co == max_co)
				{
					pos.tot_co = 0;
					pos.act_co = 1;
					if (pos.tot_li < max_li)
					{
						pos.tot_li += 1;
						pos.act_li += 1;
					}
					else
						start_li -= 1;
				}
				else if (pos.act_co == max_co && pos.tot_li > pos.act_li)
				{
						
				}
				tputs(tgetstr("im", NULL), 1, ft_putchar);
				tputs(buf , 1, ft_putchar);
				fill_str(buf, &pos);
				pos.tot_co += 1;
				pos.act_co += 1;
				check_poussin(buf[0]);
				tputs(tgetstr("ei", NULL), 1, ft_putchar);
			}
		}
		tputs(tgetstr("sc", &tamp), 1, ft_putchar);
		tputs(tgoto(tgetstr("cm", &tamp), max_co - 16, 0), 1, ft_putchar);
		ft_printf(" {U.B.T.cyan.}act_co    = %03d{eoc}\n", pos.act_co);
		tputs(tgoto(tgetstr("cm", &tamp), max_co - 16, 1), 1, ft_putchar);
		ft_printf(" {U.B.T.cyan.}act_li    = %03d{eoc}\n", pos.act_li);
		tputs(tgoto(tgetstr("cm", &tamp), max_co - 16, 2), 1, ft_putchar);
		ft_printf(" {U.B.T.cyan.}tot_co    = %03d{eoc}\n", pos.tot_co);
		tputs(tgoto(tgetstr("cm", &tamp), max_co - 16, 3), 1, ft_putchar);
		ft_printf(" {U.B.T.cyan.}tot_li    = %03d{eoc}\n", pos.tot_li);
		tputs(tgoto(tgetstr("cm", &tamp), max_co - 16, 4), 1, ft_putchar);
		ft_printf(" {U.B.T.green.}start_co  = %03d{eoc}\n", start_co);
		tputs(tgoto(tgetstr("cm", &tamp), max_co - 16, 5), 1, ft_putchar);
		ft_printf(" {U.B.T.green.}start_li  = %03d{eoc}\n", start_li);
		tputs(tgoto(tgetstr("cm", &tamp), max_co - 16, 6), 1, ft_putchar);
		ft_printf(" {U.B.T.red.}max_co    = %03d{eoc}\n", max_co);
		tputs(tgoto(tgetstr("cm", &tamp), max_co - 16, 7), 1, ft_putchar);
		ft_printf(" {U.B.T.red.}max_li    = %03d{eoc}\n", max_li);
		tputs(tgetstr("rc", &tamp), 1, ft_putchar);

		i = 0;
		while (i < 10)
			buf[i++] = '\0';
	}
	return (0);
}
