/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_termcaps.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 11:44:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/04 16:12:26 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

int			check_term(void)
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
	ret = 0;
	if (term_type == NULL)
	{
		ft_printf("TERM must be set (see 'env').\n");
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		ft_printf("Could not access to the termcap database..\n");
		return (-1);
	}
	else if (ret == 0)
	{
		ft_printf("Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
		return (-1);
	}
	return (0);
}

void		get_start_info(char *buf, t_pos *pos)
{
	int		i;

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

int			init_pos(t_pos *pos, char *buf)
{
	int		ret2;

	pos->ans = ft_strnew(0);
	pos->let_nb = 0;
	write(1, "\033[6n", 4);
	ret2 = read(1, buf, 8);
	get_start_info(buf + 1, pos);
	if (pos->start_li == -1 || pos->start_co == -1)
		ft_printf("FATAL ERROR\n");
	pos->act_li = pos->start_li;
	pos->act_co = pos->start_co;
	pos->max_co = tgetnum("co");
	pos->max_li = tgetnum("li") - 1;
	//	ft_printf("start_li = %d, start_co = %d, max_co = %d, max_li = %d\n", pos->start_li, pos->start_co, pos->max_co, pos->max_li);
	return (ret2);
}

void		init_terminfo(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSADRAIN, &term);
}

void		update_act_pos(t_pos *pos)
{
	pos->max_co = tgetnum("co");
	pos->max_li = tgetnum("li");
	if (pos->act_co > pos->max_co)
	{
		pos->act_li = pos->act_li + pos->act_co / pos->max_co;
		if (pos->act_co % pos->max_co > 0)
			pos->act_li++;
		while (pos->act_li-- > pos->max_li)
			pos->start_li--;
		pos->act_co = pos->act_co % pos->max_co;
	}
}

int		main(void)
{
	int		ret;
	int		ret2;
	char	buf[10];
	t_pos	pos;
	t_hist	*hist;

	init_terminfo();
	ret = check_term();
	ret2 = init_pos(&pos, buf);
	hist = NULL;
	hist = create_history(&pos, hist);
	bzero(buf, 10);
	while (1)
	{
//		update_act_pos(&pos);
		ret2 = read(0, buf, 10);
		hist = check_input(buf, &pos, hist);
		print_info(&pos);
		bzero(buf, 10);
	}
	return (0);
}
