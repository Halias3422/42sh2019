/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_execute_s_flag.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/24 13:41:03 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/04 15:23:39 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void		exec_s_flag(t_hist *hist, t_var **var)
{
	char	**env;
	t_var	*my_env;

	ft_printf("hist->cmd = %s\n", hist->cmd);
	env = split_env(*var);
	my_env = init_env(env, stock(NULL, 1));
	if ((check_error(hist->cmd)) != -1)
		start_exec(start_lex(my_env, hist->cmd), my_env);
	free(my_env);
}

void		prepare_s_flag(t_fc *fc, t_hist *hist, t_var **var)
{
	char	*vim;

	vim = ft_strdup("/usr/bin/vim");
	if (fc->ename == NULL)
		fc->int_first = hist->cmd_no - 1;
	if (fc->ename && ((fc->ename[0] >= '0' && fc->ename[0] < '9') || (fc->ename[0] == '-' && fc->ename[1] >= '0' && fc->ename[1] < '9')))
		fc->int_first = ft_atoi(fc->ename);
	else if (fc->ename)
	{
		fc->str_first = ft_strdup(fc->ename);
		fc->first_is_str = 1;
		make_str_arg_into_int(fc, hist);
	}
	while (hist->prev && hist->cmd_no + 1 > fc->int_first)
		hist = hist->prev;
	exec_s_flag(hist, var);
}
