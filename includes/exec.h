/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:44:02 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 09:57:28 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include "builtin.h"
# include <signal.h>

# include "../libft/includes/ft_str.h"

# define STOPED 1
# define FINISHED 1
# define WRITE_END 1
# define READ_END 0
# define PATH_HEREDOC "/tmp/heredoc"

typedef struct s_lexeur	t_lexeur;
typedef struct s_var		t_var;

typedef	struct			s_redirect
{
	char				*fd_in;
	char				*fd_out;
	char				*heredoc_content;
	int					fd;
	int					open_in;
	int					open_out;
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
	int					file_in;
	int					file_out;
	int					background;
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
	char				current;
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

int						start_exec(t_lexeur **res, t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 process.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					fill_process(t_job *j, t_lexeur **res);
void					fill_token(t_process *p, t_lexeur **res, int *i);

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

void					fill_process_split(t_job **j, t_lexeur **res, int i);
void					fill_token(t_process *p, t_lexeur **res, int *i);
int						fill_ag_first(t_redirect *tmp, t_lexeur **res, int *t);
int						fill_ag_next(t_redirect *tmp, t_lexeur **res, int *t);
void					fill_all_cmd(t_lexeur **res, t_job **j, int *k, int i);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 exec_main.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					launch_job(t_job *j, t_var *var);
int						ft_test_path(t_process *p, t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools.c       	                           ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char					*ft_join_env(char *s1, char const *s2);
char					**split_env(t_var *var);
char					*strjoin_path(char *s1, char *s2);
int						use_execve_acces(char *tmp, char **res, t_var *l_var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools.c       	                           ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					cnf_print_error(char *str);
void					ft_tabfree(char **res);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 option_exec.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						main_option_exec(t_process **first, t_process **second,
						t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                    alias.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						main_alias(t_process *p, t_var **var);
int						main_unalias(t_process *p, t_var **var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                    alias.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
void					add_alias(t_var **var, char *name, char *data);
void					find_alias(t_process *p, t_var *var, int k);
void					add_list_alias(t_var **var, char *name, char *data);
void					put_foreground(t_job *j, t_var **var, t_process *p);
void					put_background(t_job *j);
int						test_builtin(t_process *p);
int						find_builtins(t_process *p, t_var **var);
int						fork_simple(t_job *j, t_process *p, t_var **var,
						char *cmd_path);
void					wait_process(t_var **var);
void					print_start_process(t_job *j);
void					check_zombie();
void					print_job(t_job *j);
void					add_job(t_job *j);
void					remove_job(int id);
void					set_job_status(pid_t id, char status);
int						find_job_pgid(pid_t pgid);
void					job_notification(t_var **var);
int						mark_process_status(pid_t pid, int status, t_var **var);
void					signal_handler();
int						job_is_stoped(t_job *j);
t_job					*find_job_by_id(char *argv);
void					free_lexeur(t_lexeur **res);
void					add_local(t_var **var, char *str, t_var *prev,
						int type);
char					**check_exec_var(char **cmd, t_var **var);
void					free_temp(t_var **var);
int						check_cmd(char **str);
int						find_equal(char *str);
int						launch_redirection(t_process *p);
void					remove_item_var(t_var **var);
void					before_redirection(t_process *p);
t_process				*get_and_or(t_process *p);
int						is_builtin_modify(t_process *p);
void					wait_process_pid(int pid, t_var **var);
void					free_job(t_job *j);
int						duplication(t_redirect *redirect, int fd_in,
						int fd_out);
int						fd_right(char *path);
void					free_job_list(void);
int						check_name(char *name);

#endif
