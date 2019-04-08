/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_termcaps.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 11:44:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 15:27:26 by rlegendr    ###    #+. /#+    ###.fr     */
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
	{
		pos->start_li = ft_atoi(buf + i + 1) - 1 + ft_strlen(pos->prompt) / pos->max_co;
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

int			init_pos(t_pos *pos, char *buf)
{
	int		ret2;

	pos->max_co = tgetnum("co");
	pos->max_li = tgetnum("li") - 1;
	pos->debug = 0;
	pos->debug2 = 0;
	pos->debug3 = 0;
	pos->debug4 = 0;
	pos->debug5 = 0;
	pos->len_prompt = ft_strlen(pos->prompt) % pos->max_co;
	pos->ans = ft_strnew(0);
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
	char	buf[9];
	t_pos	pos;
	t_hist	*hist;

	pos.prompt = "minishell &> ";
	init_terminfo();
	ret = check_term();
	ret2 = init_pos(&pos, buf);
	hist = (t_hist*)malloc(sizeof(t_hist));
	init_t_hist(hist);
	hist = create_history(&pos, hist);
	bzero(buf, 8);
/*	while (hist && hist->prev)
	{
		ft_printf("hist->cmd = {%s} / hist->prev->cmd = {%s}\n", hist->cmd, hist->prev == NULL ? NULL : hist->prev->cmd);
		hist = hist->prev;
	}
	ft_printf("\n	------------\n\n");
	while (hist && hist->next)
	{
		ft_printf("hist->cmd = {%s} / hist->next->cmd = {%s} / hist->cmd_no = %d\n", hist->cmd, hist->next == NULL ? NULL : hist->next->cmd, hist->cmd_no);
		hist = hist->next;
	}*/
//	while (hist->prev)
//		hist = hist->prev;
//	print_info(&pos);
//	print_hist(&pos, hist);
	ft_printf("%s", pos.prompt);
	while (1)
	{
		//		update_act_pos(&pos);
		ret2 = read(0, buf, 4);
		hist = check_input(buf, &pos, hist);
//		print_info(&pos);
//		print_hist(&pos, hist);
		bzero(buf, 8);
	}
	return (0);
}
