/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:44:02 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 17:49:16 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//# include "termcaps.h"
# include <unistd.h>
# include "builtin.h"
# include <signal.h>

# include "../libft/includes/ft_str.h"

# define STOPED 1
# define FINISHED 1

typedef struct			s_lexeur t_lexeur;
typedef struct			s_var t_var;


typedef	struct			s_redirect
{
	char				*fd_in;
	char				*fd_out;
	int					fd;
	char				*token;
	struct s_redirect	*next;
}						t_redirect;

typedef	struct			s_process
{
	struct s_process	*next;
	char				**cmd;
	pid_t				pid;
	char				status;
	char				split;
	int					ret;
	int					completed;
	int					stoped;
	int					builtin;
	int					fd_in;
	int					fd_out;
	int					fd_error;
	t_redirect			*redirect;
}						t_process;

typedef struct			s_job
{
	struct s_job		*next;
	t_process			*p;
	pid_t				pgid;
	char				split;
	char				status;
	int					notified;
	int					id;
}						t_job;

typedef struct			s_job_list
{
	struct s_job_list	*next;
	t_job				*j;
}						t_job_list;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 exec.c                                     ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int		start_exec(t_lexeur **res, t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 process.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		fill_process(t_job *j, t_lexeur **res);
void		free_process(t_job *j);
void		fill_token(t_process *p, t_lexeur **res, int *i);


/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            process_tool.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						cnt_process(t_lexeur **res, int i);
void					change_job(t_job **j, t_process **start);
int						check_moove_index(t_lexeur **res, int *t);
t_redirect				*init_var(int *done, int *t, int *i);
int						check_token_in_condition(t_lexeur **res, int t);
/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            process_fill.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		fill_process_split(t_job **j, t_lexeur **res, int *i);
void		fill_token(t_process *p, t_lexeur **res, int *i);
void		fill_ag_first(t_redirect *tmp, t_lexeur **res, int *t);
void		fill_ag_next(t_redirect *tmp, t_lexeur **res, int *t);
void		fill_all_cmd(t_lexeur **res, t_job **j, int *k, int i);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 exec_main.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		launch_job(t_job *j, t_var *var);
//int			solve_execve(char *path, char **arg, t_var *var);
//int			main_exec_while(t_process *p, t_var *var);
int		ft_test_path(t_process *p, t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools.c       	                           ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char		*ft_join_env(char *s1, char const *s2);
char		**split_env(t_var *var);
char		*strjoin_path(char *s1, char *s2);
int			use_execve_acces(char *tmp, char **res, t_var *l_var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools.c       	                           ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		cnf_print_error(char *str);
void		ft_tabfree(char **res);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 option_exec.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			main_option_exec(t_process **first, t_process **second, t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                    alias.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			main_alias(t_process *p, t_var **var);
int			main_unalias(t_process *p, t_var **var);

void		put_foreground(t_job *j);
void		put_background(t_job *j);

int			test_builtin(t_process *p);
int			find_builtins(t_process *p, t_var *var);

int			fork_simple(t_job *j, t_process *p, t_var *var);

void		wait_process(pid_t pid);
void		print_start_process(t_job *j);
void		check_zombie();
void		print_job(t_job *j);
void		add_job(t_job *j);
void		remove_job(int id);
void		set_job_status(pid_t id, char status);
int			find_job_pgid(pid_t pgid);
void		job_notification(void);
int			mark_process_status(pid_t pid, int status);
void		signal_handler(pid_t pid);

int			job_is_stoped(t_job *j);

t_job		*find_job_by_id(char *argv);

int			launch_redirection(t_process *p);
#endif
