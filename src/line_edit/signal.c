/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:09:42 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/09 18:42:56 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

struct s_hist **ghist;

static void		resize_screen(t_pos *pos)
{
	int		len;

	check_term();
	pos->max_co = tgetnum("co");
	pos->max_li = tgetnum("li") - 1;
	len = get_len_with_lines(pos);
	pos->let_nb = ft_strlen(pos->ans);
	pos->len_ans = pos->let_nb;
	short_update(pos, len);
	clean_at_start(pos);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->start_li), 1, ft_putchar);
	print_prompt(pos);
	if (pos->ctrl_search_history == 1)
	{
		write(1, "(reverse-i-search)'", 19);
		ft_printf("%s':", pos->ans);
		write(1, pos->ctrl_hist_cmd, ft_strlen(pos->ctrl_hist_cmd));
	}
	else
		print_ans(pos, 0, pos->start_co);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
}

static void		ctrl_c(t_pos *pos)
{
	char	*pwd;

	while ((*ghist) && (*ghist)->next)
		*ghist = (*ghist)->next;
	if (pos->ans)
		ft_strdel(&pos->ans);
	write(1, "\n", 1);
	ft_printf("\n{T.cyan.}42sh {eoc}{B.}--- {B.T.yellow.}%s{eoc}\n",
				pwd = getcwd(NULL, 1000));
	init_pos(pos);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	print_prompt(pos);
	ft_strdel(&pwd);
}

static void		sighandler(int signum)
{
	t_pos *pos;

	pos = stock(NULL, 1);
	if (signum == RESIZING)
		resize_screen(pos);
	if (signum == CTRL_C)
		ctrl_c(pos);
}

void			sig_child_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGUSR1, SIG_DFL);
	signal(SIGHUP, SIG_DFL);
	signal(SIGIO, SIG_DFL);
}

void			signal_list(void)
{
	signal(SIGWINCH, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGILL, SIG_IGN);
	signal(SIGTRAP, SIG_IGN);
	signal(SIGEMT, SIG_IGN);
	signal(SIGFPE, SIG_IGN);
	signal(SIGSYS, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}
