/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: husahuc <husahuc@student.42.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 11:50:38 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/08 19:14:21 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "exec.h"

# define LEN_BUILTIN_LIST 10
# define TERM "42sh"
typedef struct	s_var t_var;
typedef struct	s_process t_process;
typedef struct	s_hist t_hist;
typedef struct	s_builtin
{
	const char	*name;
	int			(*ptr_builtin)(t_process*, t_var**);
}				t_builtin;

typedef struct	s_fc
{
	char		*flags_model;
	char		*flags;
	char		*ename;
	char		*str_first;
	char		*str_last;
	int			int_first;
	int			int_last;
	int			first_is_str;
	int			last_is_str;
	int			first_not_precised;
	int			last_not_precised;
	int			error;
}				t_fc;


extern const t_builtin	g_builtin_list[LEN_BUILTIN_LIST];

# include <sys/types.h>
# include <sys/stat.h>

int				ft_test(t_process *p, t_var **var);
int				ft_echo(t_process *p, t_var **var);
int				ft_cd(t_process *p, t_var **var);
int				ft_set(t_process *p, t_var **ptr_var);
int				ft_type(t_process *p, t_var **var);
int				ft_export(t_process *p, t_var **ptr_var);
int				ft_unset(t_process *p, t_var **ptr_var);

char			*ft_get_val(char *name, t_var *var, int type);
int				ft_tabclen(char **array);
void			add_list_env(t_var **var, int type, char *name, char *data);
int				remove_list_var(t_var **ptr_var, int type, char *name);

int				verif_int(char *name);
int				comp_num_operator(char *name1, char *type, char *name2);

/*
**		FT_FC.c
*/

int				ft_fc(t_process *p, t_var **var);
void			print_fc_usage(void);

/*
**		FC_GET_ARGS.C
*/

void			get_str_args_of_fc(t_fc *fc, t_process *p, int i, int check);

/*
**		FC_GET_FLAGS.C
*/

int				determ_fc_flags(t_fc *fc, t_process *p, int k, int i);
int				find_flags_order(t_fc *fc, char let_a, char let_b, int usage);

/*
**		FC_EXECUTE_L_FLAG.C
*/

void			prepare_l_flag(t_fc *fc, t_hist *hist);

# define ARGUMENTS "cd: Too many arguments."
# define CD_NO_HOME "cd: No HOME directory."
# define CD_NO_OLDPWD "cd: No OLDPWD directory"
# define CD_NO_ENV "cd: No ENV variable directory"
# define CD_NO_FILE "No such file or directory"
# define CD_NO_RIGHTS "permission denied"

#endif
