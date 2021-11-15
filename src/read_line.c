/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 03:35:04 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/14 19:05:30 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read_line.h"

static void		add_inside_line(char line[], char buff[], t_readl rd)
{
	char *rest;

	rest = ft_strdup(&line[rd.curpos]);
	ft_bzero((void*)&line[rd.curpos], (ft_strlen(line) - rd.curpos));
	ft_strcpy(&line[rd.curpos], buff);
	ft_strcat(line, rest);
	free(rest);
}

static int		take_key(char buff[], t_objet *objet, t_capab *tc, t_hist **lst)
{
	unsigned int cast;

	cast = *(unsigned int*)buff;
	if (ft_isprint(buff[0]))
	{
		add_inside_line(objet->line, buff, objet->rd);
		l_print(objet->line, &objet->rd, tc, ft_strlen(buff));
	}
	else if (cast == '\t')
		auto_c(objet);
	else if (cast == 4)
		return (0);
	arrow_key(objet, lst, cast);
	other_key(objet, cast);
	alt_key(objet, cast);
	return (1);
}

t_objet			**save_objet(t_objet *objet)
{
	static t_objet *save_obj;

	if (!save_obj)
		save_obj = objet;
	return (&save_obj);
}

char			*ft_readline(const char *prompt)
{
	t_objet		*objet;
	char		buff[READ_SIZE];
	t_termios	bckp;
	t_hist		*lst;

	lst = NULL;
	init_sig();
	init_hist(&lst);
	if (tcgetattr(0, &bckp) == -1)
		return (NULL);
	if (!(objet = init_objet(prompt)))
	{
		ft_putendl_fd("failure to initialiser termcap", 2);
		return (NULL);
	}
	save_objet(objet);
	ft_putstr(prompt);
	while (buff[0] != '\n')
	{
		ft_bzero((void*)buff, READ_SIZE);
		if (read(0, buff, READ_SIZE) < 0)
			return (exit_readline(&objet, &lst, 0));
		if (!(take_key(buff, objet, objet->tc, &lst)))
			return (exit_readline(&objet, &lst, 0));
	}
	tcsetattr(0, TCSANOW, &bckp);
	return (exit_readline(&objet, &lst, 1));
}
