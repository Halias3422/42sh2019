/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   special_params.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/02 16:34:34 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 18:11:12 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

//	LISTE DES SPECIAL PARAMS :
//
//	$0 -> nom du script execute (av[0]);
//	$* -> ensemble des parametres en un seul argument (av[1, 2, 3 ...])
//	$@ -> ensemble des parametres en plusieurs arguments (av[1] av[2] ...)
//	$# -> nb de parametres passes au script (ac)
//	$? -> code retour de la derniere commande
//	$! -> PID du dernier processus passe en background
//	$- -> liste des options courantes du shell (?)
//	$$ -> PID du shell courant
//	$_ -> au demarrage contient le chemin du script puis le dernier argument rentre)


// PARAMS a init dans le main -> $0, $*, $@, $#, $$, $-, $$, $_

// autres -> $? $! $_

// struct -> 

//	typedef struct			s_spe_params
//	{
//		char				*script_name;
//		char				*script_params;
//		char				**db_script_params;
//		int					params_nb;
//		int					ret_last_cmd;
//		int					father_pid;
//		int					pid_bg;
//		char				*script_options;
//		char				*last_arg;
//	}						t_spe_params;

// dans pos -> struct s_spe_params		*params;

void		init_special_params(t_pos *pos, char **av, int ac, t_var *my_env)
{
	int		i;

	i = 1;
	ft_printf("av[0] = %s\n", av[0]);
	pos->params = (t_spe_params*)malloc(sizeof(t_spe_params));
	pos->params->script_name = ft_strdup(av[0]);
	pos->params->script_params = ft_strnew(0);
	while (av[i])
	{
		pos->params->script_params = ft_strjoinf(pos->params->script_params,
				av[i], 1);
		if (av[i + 1])
			pos->params->script_params = ft_strjoinf(pos->params->script_params,
					" ", 1);
		i++;
	}
	// db_script_params je sais pas si il faut faire un db_tab ? 
	pos->params->params_nb = ac - 1;
	// father_pid -> recuperer du processus dans lequel 42sh est lance
	pos->params->ret_last_cmd = 0;
	pos->params->pid_bg = 0;
	// script_options je sais pas ce qu'il faut mettre
	while (my_env)
	{
		if (ft_strcmp(my_env->name, "_") == 0)
			pos->params->last_arg = ft_strdup(my_env->data);
		my_env = my_env->next;
	}
	ft_printf("$0 = [%s]\n$* = [%s]\n$# = [%d]\n$? = [%d]\n$! = [%d]\n$_ = [%s]\n", pos->params->script_name, pos->params->script_params, pos->params->params_nb, pos->params->ret_last_cmd, pos->params->pid_bg, pos->params->last_arg);
}
