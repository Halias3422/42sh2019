/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_execute_e_flag.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/25 08:56:49 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/04 10:25:39 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

static int					check_if_ename_is_text_editor(t_fc *fc, char **paths)
{
	DIR				*dirp;
	struct dirent	*read;
	int				i;

	i = 0;
	if (fc->ename == NULL || (fc->ename[0] > '0' && fc->ename[0] < '9'))
	{
		fc->int_first = ft_atoi(fc->ename);
		fc->ename = ft_strdup("/usr/bin/vim");
		return (1);
	}
		while (paths[i])
		{
			paths[i] = free_strjoin(paths[i], "/");
			dirp = opendir(paths[i]);
			while ((read = readdir(dirp)) != NULL)
			{
				if (ft_strcmp(fc->ename, read->d_name) == 0)
				{
					fc->ename = ft_secure_free(fc->ename);
					fc->ename = ft_strdup(read->d_name);
					fc->ename = ft_strjoinf(paths[i], fc->ename, 2);
					return (1);
				}
			}
			closedir(dirp);
			i++;
		}
		ft_printf_err("42sh: command not found: %s\n", fc->ename);
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
	t_hist		*hist;

	hist = stock(NULL, 8);
	i = 0;
	new_cmds = (char**)malloc(sizeof(char*) * (hist->cmd_no * 2));
	ret = 1;
	line = NULL;

	char	*pwd = getcwd(NULL, 255);
	pwd = ft_strjoinf(pwd, "/.tmp", 1);
	fd = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666);
	free(pwd);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ft_strlen(line) > 0)
		{
			new_cmds[i] = ft_strnew(0);
			new_cmds[i] = ft_strjoinf(new_cmds[i], line, 3);		
			i++;
		}
	}
	new_cmds[i] = NULL;
	return (new_cmds);
}

char				*check_new_cmd_is_valid(char *new_cmds, char **paths)
{
	int				i;
	DIR				*dirp;
	struct dirent	*read;

	i = 0;
	while (paths[i])
	{
		paths[i] = free_strjoin(paths[i], "/");
		dirp = opendir(paths[i]);
		while ((read = readdir(dirp)) != NULL)
		{
			if (ft_strcmp(new_cmds, read->d_name) == 0)
			{
				new_cmds = ft_secure_free(new_cmds);
				new_cmds = ft_strdup(read->d_name);
				new_cmds = ft_strjoinf(paths[i], new_cmds, 2);
				return (new_cmds);
			}
		}
		closedir(dirp);
		i++;
	}
	ft_printf_err("ici 42sh: command not found: %s\n", new_cmds);
	return (0);
}

void				exec_new_cmds(char **new_cmds, char **env, char **paths, char ** arg_tmp)
{
	int				i;
	t_var			*my_env;

	i = 0;
	my_env = init_env(env, stock(NULL, 1));
	(void)new_cmds;
//	(void)env;
	(void)paths;
	(void)arg_tmp;
	i = 0;
	while (new_cmds[i])
	{
		if ((check_error(new_cmds[i])) != -1)
			start_exec(start_lex(my_env, new_cmds[i]), my_env);
		i++;
	}
}

void				exec_ide_with_tmp_file(t_fc *fc, int fd, char **env, char **paths)
{
	char			**arg_tmp;
	pid_t			father;
	char			**new_cmds;

	(void)paths;
	father = fork();
	arg_tmp = (char**)malloc(sizeof(char*) * 3);
	arg_tmp[0] = ft_strdup(fc->ename);
	arg_tmp[1] = ft_strdup(".tmp");
	arg_tmp[2] = NULL;
	new_cmds = NULL;
	if (father > 0)
	{
		wait(&father);
		new_cmds = recover_new_cmds_from_tmp(new_cmds, fd);
		exec_new_cmds(new_cmds, env, paths, arg_tmp);
		return ;
	}
	else if (father == 0)
	{
		if (execve(fc->ename, arg_tmp , env) == -1)
		{
			ft_printf("execve error");
			return ;
		}
	}
}

void				prepare_e_flag(t_fc *fc, t_hist *hist, t_var **var)
{
	int			swap;
	int			fd;
	char		**env;
	int			i;
	char		**paths;

	env = split_env(*var);
	paths = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			paths = ft_strsplit(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	fd = 1;
	if (check_if_ename_is_text_editor(fc, paths) == 1)
	{
		correct_int_first_and_int_last(fc, hist);
		if (ft_strchr(fc->flags, 'r') != NULL)
		{
			swap = fc->int_first;
			fc->int_first = fc->int_last;
			fc->int_last = swap;
		}
		while (hist->prev && hist->cmd_no + 1 > fc->int_first)
			hist = hist->prev;
		fd = fill_command_to_send_to_text_editor(fc, hist);
		exec_ide_with_tmp_file(fc, fd, env, paths);
	}
}
