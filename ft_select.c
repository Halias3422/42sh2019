#include "ft_select.h"

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


int		find_key(char *buf, t_pos *pos)
{
//	if (ft_strncmp(buf + 1, "[A", 2) == 0) // fleche haut
//		;
	if (pos->actual < pos->total && ft_strncmp(buf + 1, "[C", 2) == 0) // fleche droite
	{
		tputs(buf, 1, ft_putchar);
		pos->actual++;

	}
	if (pos->actual >= 0 && ft_strncmp(buf + 1, "[D", 2) == 0) // fleche gauche
	{
		tputs(buf, 1, ft_putchar);
		pos->actual -= pos->actual == 0 ? 0 : 1;
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

void	remove_str(t_pos *pos)
{
	char	*swap;

	swap = ft_strnew(pos->actual);
	swap = ft_strncpy(swap, pos->ans, pos->actual - 1);
	swap = ft_strjoinf(swap, pos->ans + pos->actual, 1);
	free(pos->ans);
	pos->ans = swap;
}

void	fill_str(char *buf, t_pos *pos)
{
	char	*swap;

	swap = NULL;
	if (pos->actual == pos->total)
		pos->ans = ft_strjoinf(pos->ans, buf, 1);
	else
	{
		swap = ft_strnew(pos->actual);
		swap = ft_strncpy(swap, pos->ans, pos->actual);
		swap = ft_strjoinf(swap, buf, 1);
		swap = ft_strjoinf(swap, pos->ans + pos->actual, 1);
		free(pos->ans);
		pos->ans = swap;
	}
}


int 	main()
{

	int		ret;
	int		col;
	int		line;
	char	*test;
	int		ret2;
	char	buf[3];
	char	*name_term;
	struct	termios term;
	int		i;
	t_pos	pos;
	char	*tmp;

	tmp = NULL;
	name_term = getenv("TERM");
	tgetent(NULL, name_term);
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
	pos.total = 0;
	pos.actual = 0;

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
				tmp = tgetstr("le", NULL);
				tputs(tmp, 1, ft_putchar);
				free(tmp);
				tmp = NULL;
				tputs(tgetstr("dc", NULL), 1, ft_putchar);
				remove_str(&pos);
				pos.total -= pos.total == 0 ? 0 : 1;
				pos.actual -= pos.actual == 0 ? 0 : 1;
			}
			else if (buf[0] == 10)
			{
				tputs(tgetstr("ei", NULL), 1, ft_putchar);
				ft_printf("\nreponse -> |%s|\n", pos.ans);
			//	free(buf);
				exit (0);
			}
			else
			{
				tputs(tgetstr("im", NULL), 1, ft_putchar);
				tputs(buf , 1, ft_putchar);
				fill_str(buf, &pos);
				pos.total++;
				pos.actual++;
				check_poussin(buf[0]);
				tputs(tgetstr("ei", NULL), 1, ft_putchar);
			}
		}
		i = 0;
		while (i < 10)
			buf[i++] = '\0';
	}
	return (0);
}

//tgetnum("ch");
