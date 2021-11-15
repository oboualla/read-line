/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libac.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 00:35:26 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/14 19:07:48 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBAC_H
#define LIBAC_H
#include "read_line.h"
#define ONLY_DIR    1
#define ONLY_CMD    2
#define ALL         3

typedef struct s_ac t_ac;

struct s_ac
{
	char	*cmd;
	char	*file;
	char	*path;
	char	**files;
};


// objet.c
int		ft_strcmp_index(char *file, char *cmp);
size_t	get_len(char **t_file);
int		exit_prog(t_ac **ac);

//readpath.c
int		get_lfile(t_ac *ac, size_t *len);

//couler
void	couleur(char *file, char *path);

//print_ac
int		print_ac(t_ac *ac, t_objet *obj, size_t len);

//complet_line
void	complet_line(t_ac *ac, t_objet *obj, size_t cmp);

#endif
