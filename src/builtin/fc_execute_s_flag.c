/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_execute_s_flag.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/24 13:41:03 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/05 14:01:38 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

static void		exec_s_flag(t_hist *hist, t_var **var)
{
	char	**env;
	t_var	*my_env;
	char	**cmd;
	char	*tmp_cmd;

	cmd = (char**)malloc(sizeof(char*) * 2);
	cmd[1] = NULL;
	cmd[0] = ft_strdup(hist->cmd);
	tmp_cmd = ft_strdup(hist->cmd);
	env = split_env(*var);
	my_env = init_env(env, stock(NULL, 1));
	ft_printf("%s\n", tmp_cmd);
	if ((check_error(hist->cmd)) != -1)
		start_exec(start_lex(my_env, tmp_cmd), my_env);
	ft_free_tab(env);
	place_new_cmds_in_history(cmd, hist);
}

static void		correct_int_first(t_fc *fc, t_hist *hist)
{
	if (fc->ename == NULL)
		fc->int_first = hist->cmd_no - 1;
	else if (fc->ename && ((fc->ename[0] >= '0' && fc->ename[0] < '9') ||
		(fc->ename[0] == '-' && fc->ename[1] >= '0' && fc->ename[1] < '9')))
		fc->int_first = ft_atoi(fc->ename);
	if (fc->int_first < 0)
		fc->int_first = hist->cmd_no + fc->int_first;
	if (fc->int_first < 0)
	{
		fc->error = 1;
		ft_printf_err("%s: fc: history specification out of range\n", TERM);
	}
	if (fc->int_first >= hist->cmd_no)
		fc->int_first = hist->cmd_no - 1;
}

static void		finish_s_flag(t_fc *fc, t_hist *hist, t_var **var)
{
	while (hist->prev && hist->cmd_no + 1 > fc->int_first)
		hist = hist->prev;
	if (fc->int_first == 0 && hist->next->cmd == NULL)
	{
		fc->error = 1;
		ft_printf_err("%s: fc: history specification out of range\n", TERM);
	}
	if (fc->error == 0)
		exec_s_flag(hist, var);
	else
	{
		remove_cmd_from_hist(hist);
		overwrite_history_file(hist);
	}
}

void			prepare_s_flag(t_fc *fc, t_hist *hist, t_var **var)
{
	if (fc->ename == NULL || ((fc->ename[0] == '-' && fc->ename[1] >= '0' &&
		fc->ename[1] < '9') || (fc->ename[0] >= '0' && fc->ename[0] < '9')))
		correct_int_first(fc, hist);
	else if (fc->ename)
	{
		if (fc->ename[0] == '-' && (fc->ename[1] < '0' || fc->ename[1] > '9'))
			fc->int_first = -1;
		fc->str_first = ft_strdup(fc->ename);
		fc->first_is_str = 1;
		make_str_arg_into_int(fc, hist);
	}
	if (fc->error == 1)
		return ;
	finish_s_flag(fc, hist, var);
}
