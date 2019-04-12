/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_termcaps.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 11:44:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 11:53:53 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

int		check_term(void)
{
	int			ret;
	char		*term_type;

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
		ft_printf("Terminal type '%s' is not defined in termcap database ");
		ft_printf("or have too few informations).\n", term_type);
		return (-1);
	}
	return (0);
}

void	get_start_info(char *buf, t_pos *pos)
{
	int			i;

	i = 0;
	while (buf[i] && buf[i] != '[')
		i++;
	if (buf[i] == '\0')
		pos->start_li = -1;
	else
	{
		pos->start_li = ft_atoi(buf + i + 1) - 1 +
			ft_strlen(pos->prompt) / pos->max_co;
		if (pos->start_li > pos->max_li)
			pos->start_li = pos->max_li;
	}
	i = 0;
	while (buf[i] && buf[i] != ';')
		i++;
	if (buf[i] == '\0')
		pos->start_co = -1;
	else
		pos->start_co = ft_atoi(buf + i + 1) - 1 + pos->len_prompt;
}

int		init_pos(t_pos *pos, char *buf)
{
	int			ret2;

	pos->max_co = tgetnum("co");
	pos->max_li = tgetnum("li") - 1;
	pos->history_mode = 0;
	pos->len_prompt = ft_strlen(pos->prompt) % pos->max_co;
	pos->ans = ft_strnew(0);
	pos->saved_ans = NULL;
	pos->len_ans = pos->len_prompt;
	pos->let_nb = 0;
	write(1, "\033[6n", 4);
	ret2 = read(1, buf, 8);
	get_start_info(buf + 1, pos);
	if (pos->start_li == -1 || pos->start_co == -1)
		ft_printf("FATAL ERROR\n");
	pos->act_li = pos->start_li;
	pos->act_co = pos->start_co;
	return (ret2);
}

void	init_terminfo(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
}

void	update_act_pos(t_pos *pos)
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

char	*termcaps42sh(char *prompt, int error, t_pos *pos, t_hist *hist)
{
	int			ret;
	int			ret2;
	char		buf[9];
	t_inter		inter;
   
	inter = (t_inter){0, 0, 0, 0, 0, 0, 0, 0};
	ft_printf("%d, %d, %d, %d, %d, %d, %d, %d\n", inter.sg_quote, inter.db_quote, inter.bracket, inter.parenthesis, inter.a_quote, inter.db_and, inter.pipe, inter.db_pipe);
	error = 0;
	while (hist->next)
		hist = hist->next;
	if (pos->prompt == NULL)
		pos->prompt = ft_strdup(prompt);
	init_terminfo();
	ret = check_term();
	if (ret == -1)
		exit(0);
	ret2 = init_pos(pos, buf);
	bzero(buf, 8);
	print_info(pos);
	print_hist(pos, hist);
	ft_printf("%s", pos->prompt);
	while (1)
	{
	//	update_position(&pos, pos->ans);
		ret2 = read(0, buf, 4);
		hist = check_input(buf, pos, hist);
		print_info(pos);
		print_hist(pos, hist);
		if (buf[0] == 10)
			return (pos->ans);
		bzero(buf, 8);
	}
	return (NULL);
}

