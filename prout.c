/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prout.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 08:45:24 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/02 08:47:50 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include "ft_select.h"

void	get_start_info(char *buf, int *start_li, int *start_co)
{
	int        i;

	i = 0;
	while (buf[i] && buf[i] != '[')
		i++;
	if (buf[i] == '\0')
		*start_li = -1;
	else
		*start_li = ft_atoi(buf + i + 1);
	i = 0;
	while (buf[i] && buf[i] != ';')
		i++;
	if (buf[i] == '\0')
		*start_co = -1;
	else
		*start_co = ft_atoi(buf + i + 1);
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
		close(pos->history);
		exit(0);
	}
	else
		poussin = 0;
}

void	remove_str(t_pos *pos)
{
	char	*swap;

	swap = ft_strnew(pos->act_co);
	swap = ft_strncpy(swap, pos->ans, pos->act_co - 1);
	swap = ft_strjoinf(swap, pos->ans + pos->act_co, 0);
	//	free(pos->ans);
	pos->ans = swap;
}

void	fill_str(char *buf, t_pos *pos)
{
	char	*swap;

	swap = NULL;
	if (pos->act_co == pos->tot_co)
		pos->ans = ft_strjoinf(pos->ans, buf, 0);
	else
	{
		swap = ft_strnew(pos->act_co + 1);
		swap = ft_strncpy(swap, pos->ans, pos->act_co);
		swap = ft_strjoinf(swap, buf, 0);
		swap = ft_strjoinf(swap, pos->ans + pos->act_co, 0);
		//		free(pos->ans);
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
	char	buf[10];
	//	char	*name_term;
	struct	termios term;
	int		i;
	t_pos	pos;
	char	*tmp;
	t_hist	*hist;
	int		start_li;
	int		start_co;

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

	hist = NULL;
	hist = create_history(&pos, hist);
	write (1, "\033[6n", 4);
	ret2 = read(1, buf, 8);
	get_start_info(buf + 1, &start_li, &start_co);
	if (start_li == -1 || start_co == -1)
		ft_printf("FATAL ERROR\n");
	bzero(buf, 10);
	//	ft_printf("ligne %d et colonne %d\n", start_li, start_co);
	pos.act_co = start_co;
	pos.act_li = start_li;
	pos.tot_co = pos.act_co;
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
				tmp = tgetstr("le", NULL);
				tputs(tmp, 1, ft_putchar);
				//	free(tmp);
				tmp = NULL;
				tputs(tgetstr("dc", NULL), 1, ft_putchar);
				remove_str(&pos);
				pos.tot_co -= pos.tot_co == 0 ? 0 : 1;
				pos.act_co -= pos.act_co == 0 ? 0 : 1;
			}
			//			else if (buf[0] == 32)
			//				write(1, "\033[6n", 4);
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
				tputs(tgetstr("im", NULL), 1, ft_putchar);
				tputs(buf , 1, ft_putchar);
				fill_str(buf, &pos);
				pos.tot_co++;
				pos.act_co++;
				check_poussin(buf[0]/*, &pos*/);
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

