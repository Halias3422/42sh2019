/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_execute_e_flag.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/25 08:56:49 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/25 14:15:15 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

static int					check_if_ename_is_text_editor(t_fc *fc)
{
	DIR				*dirp;
	struct dirent	*read;

	(void)fc;
	dirp = opendir("/usr/bin/");
	while ((read = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(fc->ename, read->d_name) == 0)
		{
			fc->ename = ft_secure_free(fc->ename);
			fc->ename = ft_strdup(read->d_name);
			fc->ename = ft_strjoinf("/usr/bin/", fc->ename, 2);
			return (1);
		}
	}
	closedir(dirp);
	return (0);
}

static void			correct_int_first_and_int_last(t_fc *fc, t_hist *hist)
{
	if (fc->first_not_precised == 1 && fc->last_not_precised == 1)
	{
		fc->int_first = hist->cmd_no;
		fc->int_last = hist->cmd_no;
	}
	else if (fc->first_not_precised == 1)
		fc->int_first = hist->cmd_no;
	else if (fc->last_not_precised == 1)
		fc->int_last = fc->int_first;
	if (fc->int_first < 0)
		fc->int_first = (hist->cmd_no + fc->int_first);
	if (fc->int_last < 0)
		fc->int_last = (hist->cmd_no + fc->int_last);
}

static int			fill_command_to_send_to_text_editor(t_fc *fc, t_hist *hist)
{
	char			*pwd;
	int			fd;

	pwd = getcwd(NULL, 255);
	pwd = ft_strjoinf(pwd, "/.tmp", 1);
	fd = open(pwd, O_RDWR | O_TRUNC | O_CREAT, 0666);
	free(pwd);
	if (fc->int_first <= fc->int_last)
	{
		while (fc->int_first <= fc->int_last && hist->next->next)
		{
			write(fd, hist->cmd, ft_strlen(hist->cmd));
			write(fd, "\n", 1);
			hist = hist->next;
			fc->int_first += 1;
		}
	}
	else if (fc->int_first > fc->int_last)
	{
		while (fc->int_first >= fc->int_last && hist)
		{
			write(fd, hist->cmd, ft_strlen(hist->cmd));
			write(fd, "\n", 1);
			hist = hist->prev;
			fc->int_first -= 1;
		}	
	}
	return (fd);
}

char				**recover_new_cmds_from_tmp(char **new_cmds, int fd)
{
	int			ret;
	char			*line;
	int			i;

	i = 0;
	new_cmds = (char**)malloc(sizeof(char*));
	ret = 1;
	line = NULL;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ft_strlen(line) > 0)
		{
			new_cmds[i] = ft_strnew(0);
			new_cmds[i++] = ft_strjoinf(new_cmds[i], line, 3);		
		}
		new_cmds[i] = NULL;
	}
	return (new_cmds);
}

char				**exec_ide_with_tmp_file(t_fc *fc, t_var *var, int fd)
{
	char			**arg_tmp;
	char			**env;
	pid_t			father;
	char			**new_cmds;

	father = fork();
	arg_tmp = (char**)malloc(sizeof(char*) * 3);
	arg_tmp[0] = ft_strdup(fc->ename);
	arg_tmp[1] = ft_strdup(".tmp");
	arg_tmp[2] = NULL;
	env = split_env(var);
	if (father > 0)
	{
		wait(&father);
		return ;
	}
	if (father == 0)
	{
		if (execve(fc->ename, arg_tmp , env) == -1)
		{
			ft_printf("execve error");	
		}
		new_cmds = recover_new_cmds_from_tmp(new_cmds, fd);
		int i = 0;
		while (new_cmds[i])
		{
			ft_printf("new_cmds[%d] = %s\n", i, new_cmds[i]);
			i++;	
		}
		exit(0);
	}
}

void				prepare_e_flag(t_fc *fc, t_hist *hist, t_var **var)
{
	int			swap;
	int			fd;

	fd = 1;
	(void)hist;
	if (fc->ename != NULL && check_if_ename_is_text_editor(fc) == 1)
	{
		correct_int_first_and_int_last(fc, hist);
		if (ft_strchr(fc->flags, 'r') != NULL)
		{
			swap = fc->int_first;
			fc->int_first = fc->int_last;
			fc->int_last = swap;
		}
		//		cmds = ft_strnew(0);
		while (hist->prev && hist->cmd_no + 1 > fc->int_first)
			hist = hist->prev;
		fd = fill_command_to_send_to_text_editor(fc, hist);
		exec_ide_with_tmp_file(fc, *var, fd);
	}

}
