/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 14:32:39 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/10 17:23:40 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			signal_main(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

int				check_entry(void)
{
	struct winsize w;

	if (ioctl(0, TIOCGWINSZ, &w) == -1)
	{
		ft_printf("Entry is not a tty\nExit\n");
		exit(0);
	}
	return (0);
}

int				main_loop(t_pos pos, t_var *my_env, t_hist *hist)
{
	char		*pwd;
	char		*ans;

	ft_printf("\n{T.cyan.}42sh {eoc}{B.}--- {B.T.yellow.}%s{eoc}\n",
	pwd = getcwd(NULL, 1000));
	ft_strdel(&pwd);
	ans = termcaps42sh(&pos, hist, my_env);
	job_notification(my_env);
	if (ans == NULL)
		return (1);
	if (pos.error == 1)
		error_handling(&pos, NULL, 0);
	if ((check_error(ans)) != -1)
		start_exec(start_lex(my_env, ans), my_env);
	else
		pos.ans = ft_secure_free(pos.ans);
	pos.error = 0;
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_hist	*hist;
	t_var	*my_env;
	t_pos	pos;
	pid_t	shell_pid;

	(void)ac;
	(void)av;
	check_entry();
	signal_main();
	shell_pid = getpid();
	setpgid(shell_pid, shell_pid);
	tcsetpgrp(STDIN_FILENO, shell_pid);
	my_env = init_env(env, &pos);
	stock(my_env, 5);
	hist = (t_hist *)malloc(sizeof(t_hist));
	init_t_hist(hist);
	pos.is_complete = 1;
	pos.prompt = NULL;
	hist = create_history(&pos, hist);
	ghist = &hist;
	while (1)
	{
		if (main_loop(pos, my_env, hist) != 0)
			break ;
	}
}
