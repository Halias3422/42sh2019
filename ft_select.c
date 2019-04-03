
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

	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

void	get_start_info(char *buf, t_pos *pos)
{
	int        i;

	i = 0;
	while (buf[i] && buf[i] != '[')
		i++;
	if (buf[i] == '\0')
		pos->start_li = -1;
	else
		pos->start_li = ft_atoi(buf + i + 1) - 1;
	i = 0;
	while (buf[i] && buf[i] != ';')
		i++;
	if (buf[i] == '\0')
		pos->start_co = -1;
	else
		pos->start_co = ft_atoi(buf + i + 1) - 1;
}

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


t_hist		*find_key(char *buf, t_pos *pos, t_hist *hist)
{

	if (ft_strncmp(buf + 1, "[A", 2) == 0) // fleche haut
	{
		hist = move_through_history(hist, pos, "up");
	}
	if (pos->let_nb < (int)ft_strlen(pos->ans) && ft_strncmp(buf + 1, "[C", 2) == 0)
	{
		if (pos->let_nb == pos->max_co)
			tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->act_li + 1), 1, ft_putchar);
		tputs(buf, 1, ft_putchar);
		if (pos->act_co == pos->max_co)
		{
			pos->act_co = 0;
			pos->act_li += 1;
		}
		else
			pos->act_co++;
		pos->let_nb++;
		if (pos->act_co == 0 && pos->let_nb > 0)
			pos->act_li++;
	}
	if (pos->let_nb > 0 && pos->act_co >= 0 && ft_strncmp(buf + 1, "[D", 2) == 0) // fleche gauche
	{
		pos->let_nb--;
		if (pos->let_nb % pos->max_co == 0)
			pos->act_li--;
		tputs(buf, 1, ft_putchar);
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
	}
	if (ft_strncmp(buf + 1, "[B", 2) == 0) // fleche bas
	{
		hist = move_through_history(hist, pos, "down");
	}
	if (buf[0] == 10)
	{
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		exit (0);
	}
	return (hist);
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

void	remove_str(t_pos *pos)
{
	char	*swap;
	if (pos->act_co > 0)
	{
		swap = ft_strnew(pos->act_co);
		swap = ft_strncpy(swap, pos->ans, pos->act_co - 1);
		if (pos->act_co < pos->tot_co)
			swap = ft_strjoinf(swap, pos->ans + pos->act_co, 0);
		//	free(pos->ans);
		pos->ans = swap;
		pos->let_nb--;
	}
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
//		swap = ft_strnew(pos->act_co);
//		swap = ft_strncpy(swap, pos->ans, pos->act_co - 1);
		pos->act_co = pos->max_co + 1;
		pos->act_li--;
	}
}

void	fill_str(char *buf, t_pos *pos)
{
	char	*swap;

	swap = NULL;
	pos->let_nb = pos->act_co;
	if (pos->act_li > pos->start_li)
		pos->let_nb = ((pos->act_li - pos->start_li) * pos->max_co) + pos->act_co;
	if (pos->let_nb == (int)ft_strlen(pos->ans))
	{
		pos->ans = ft_strjoinf(pos->ans, buf, 0);
	}
	else
	{
		swap = ft_strnew(pos->let_nb + 1);
		swap = ft_strncpy(swap, pos->ans, pos->let_nb);
		swap = ft_strjoinf(swap, buf, 0);
		swap = ft_strjoinf(swap, pos->ans + pos->let_nb, 0);
		pos->ans = swap;
	}
	pos->let_nb++;
}

void	clean_screen(t_pos *pos)
{
	int	cl_screen;

	cl_screen = pos->start_li;
	while (cl_screen < pos->max_li)
	{
		tputs(tgoto(tgetstr("cm", NULL), pos->start_co, cl_screen++), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		tputs(tgetstr("cb", NULL), 1, ft_putchar);
	}
	(void)pos;
	tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->start_li), 1, ft_putchar);
}

void	print_str(t_pos *pos)
{
	int		len_ans;
	int		nb_li;

	len_ans = ft_strlen(pos->ans);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->start_li), 1, ft_putchar);

	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	tputs(tgetstr("cb", NULL), 1, ft_putchar);
	write(1, pos->ans, len_ans);
	nb_li = len_ans / pos->max_co;
	while (nb_li != 0)
	{
		if (pos->act_li < pos->max_li && pos->act_co == pos->max_co)
		{
			pos->act_li++;
			pos->act_co = 0;
		}
		else if (pos->act_co == pos->max_co)
		{
			pos->start_li--;
			pos->act_co = 0;
		}
		nb_li--;
		if (pos->tot_li < pos->act_li)
			pos->tot_li = pos->act_li;
	}
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
	t_hist	*hist;

	tmp = NULL;
	//	name_term = getenv("TERM");
	//	tgetent(NULL, name_term);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSADRAIN, &term);

	ret = init_term();
	col = 0;
	line = 0;
	test = NULL;
	i = 0;
	pos.ans = ft_strnew(0);
	pos.tot_co = 0;
	pos.act_co = 0;
	pos.let_nb = 0;
	hist = NULL;
	hist = create_history(&pos, hist);
	write (1, "\033[6n", 4);
	ret2 = read(1, buf, 8);
	get_start_info(buf + 1, &pos);
	if (pos.start_li == -1 || pos.start_co == -1)
		ft_printf("FATAL ERROR\n");
	bzero(buf, 10);
	//	ft_printf("ligne %d et colonne %d\n", start_li, start_co);
	pos.act_li = pos.start_li;
	pos.act_co = pos.start_co;
	pos.tot_li = pos.start_li;
	pos.tot_co = pos.start_co;
	pos.max_co = tgetnum("co");
	pos.max_li = tgetnum("li");
	while (1)
	{
		i = 0;
		ret2 = read(0, buf, 10);
		if (buf[1])
			hist = find_key(buf, &pos, hist);
		else
		{
			if (buf[0] == 127)
			{
				if (pos.act_co > 0 || pos.act_li > pos.start_li)
				{
					tmp = tgetstr("le", NULL);
					tputs(tmp, 1, ft_putchar);
					//	free(tmp);
					tmp = NULL;
					tputs(tgetstr("dc", NULL), 1, ft_putchar);
					remove_str(&pos);
					pos.tot_co -= pos.tot_co == 0 ? 0 : 1;
					pos.act_co -= pos.act_co == 0 ? 0 : 1;
				}
			}
			else if (buf[0] == 10)
			{
				tputs(tgetstr("ei", NULL), 1, ft_putchar);
				ft_printf("\nreponse -> |%s|\n", pos.ans);
				//	free(buf);
				write(pos.history, pos.ans, ft_strlen(pos.ans));
				write(pos.history, "\n", 1);
				close(pos.history);
				main();
			}
			else
			{
				//	tputs(tgetstr("im", NULL), 1, ft_putchar);
				//	tputs(buf , 1, ft_putchar);
				fill_str(buf, &pos);
				print_str(&pos);
				tputs(tgoto(tgetstr("cm", NULL), pos.act_co + 1, pos.act_li), 1, ft_putchar);
				if (pos.let_nb % pos.max_co == 0)
					tputs(tgoto(tgetstr("cm", NULL), pos.start_co, pos.act_li + 1), 1, ft_putchar);
				//	clean_screen(&pos);
				//
				pos.tot_co++;
				pos.act_co++;

				check_poussin(buf[0]/*, &pos*/);
				//		tputs(tgetstr("ei", NULL), 1, ft_putchar);
			}
		}
		print_info(&pos);
		i = 0;
		while (i < 10)
			buf[i++] = '\0';
	}
	return (0);
}

//tgetnum("ch");
