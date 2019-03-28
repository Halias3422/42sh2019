
#include "ft_select.h"

/*int        main(int ac, char **av)
  {
  char    *term;
  char    *buf;
  int        res;

  buf = NULL;
  term = getenv("BLABLA");
  printf("%s\n", term);
  res = tgetent(buf, term);
  printf("res = %d, buf = %s\n", res, buf);
  return (0);
  }*/

int init_term()
{
	int ret;
	char *term_type = getenv("TERM");

	if (term_type == NULL)
	{
		fprintf(stderr, "TERM must be set (see 'env').\n");
		return -1;
	}

	ret = tgetent(NULL, term_type);

	if (ret == -1)
	{
		fprintf(stderr, "Could not access to the termcap database..\n");
		return -1;
	}
	else if (ret == 0)
	{
		fprintf(stderr, "Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
		return -1;
	}

	return 0;
}

int		find_key(char *buf)
{
	if (ft_strncmp(buf + 1, "[A", 2) == 0)
		ft_printf("  haut");
	if (ft_strncmp(buf + 1, "[C", 2) == 0)
	{
		ft_printf("  droite");
//		tputs(buf, 1, ft_putchar);

	}
	if (ft_strncmp(buf + 1, "[D", 2) == 0)
		ft_printf("  gauche");
	if (ft_strncmp(buf + 1, "[B", 2) == 0)
		ft_printf("  bas");
/*	if (ft_strncmp(buf + 1, "[A", 2) == 0)
		ft_printf("haut");
	if (ft_strncmp(buf + 1, "[A", 2) == 0)
		ft_printf("haut");
	if (ft_strncmp(buf + 1, "[A", 2) == 0)
		ft_printf("haut");

*/


	return (1);
}

int 	main(int argc, char **argv)
{
	int ret = init_term();
	int    col;
	int    line;
	char *test;
	int ret2;
	char buf[3];
	char    *name_term;
	struct    termios term;

	name_term = getenv("TERM");
	tgetent(NULL, name_term);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);

	tcsetattr(0, TCSADRAIN, &term);
	col = 0;
	line = 0;
	test = NULL;
	//    On évite les warnings pour variables non utilisées.
	(void)argc;
	(void)argv;
int	i = 0;
	while (1)
	{
		i = 0;
		ret2 = read(0, buf, 10);
		if (buf[0] == 27)
		{

	//		ft_printf("caracter non imprimable --> ");
			while (buf[i])
			{
	//			ft_printf(" %d{%c}", buf[i], buf[i]);
				i++;
			}
	//		find_key(buf);
		}
		else
		{
			if (buf[0] == 127)
			{
				tputs(tgetstr("le", NULL), 1, ft_putchar);
				tputs(tgetstr("dc", NULL), 1, ft_putchar);
			}
	//		ft_printf("imprimable --> %d -/", buf[0]);
			else
				tputs(buf , 1, ft_putchar);
		}
		i = 0;
		while (i < 10)
			buf[i++] = '\0';
//		ft_printf("\n");
	}
	if (ret == 0)
	{
		//     Le déroulement de notre programme se fera ici.
		printf("on a gagne a la place du truc bleu\n");
		col = tgetnum("co");
		line = tgetnum("li");
		test = tgetstr("cl", NULL);
		int i = 0;
		while (test[i + 1])
			write(1, &test[i++], 1);
		printf("\n");
		i = 1;
		while (test[i])
			write(1, &test[i++], 1);
		printf("col = %d et li = %d\n", col, line);
	}
	return ret;
}

//tgetnum("ch");
