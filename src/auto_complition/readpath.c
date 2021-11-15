/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ac_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 00:26:24 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/10 15:36:16 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libac.h"

static int	access_file(char *file, char *path, ushort mode)
{
	char	pfile[100];
	ushort	ret;
	t_stat	st;

	ret = 0;
	ft_strcpy(pfile, path);
	ft_strcat(pfile, "/");
	ft_strcat(pfile, file);
	if (mode == ONLY_DIR)
	{
		if (!stat(pfile, &st) && S_ISDIR(st.st_mode))
			ret = 1;
	}
	else if (mode == ONLY_CMD)
	{
		if (!access(pfile, F_OK | X_OK))
			ret = 1;
	}
	else
		ret = 1;
	return (ret);
}

static void	change_dname(char *d_name)
{
	char	*rest;
	char	*ptr;

	if (!(ptr = ft_strchr(d_name, ' ')))
		return ;
	rest = ft_strdup(ptr);
	ptr[0] = '\\';
	ptr[1] = '\0';
	ft_strcat(ptr, rest);
	ft_strdel(&rest);
}

static int	condition_(char *d_name, char *file, char *path, ushort mode)
{
	int		ret;

	ret = 1;
	if (!ft_strcmp(d_name, "..") && !ft_strcmp(d_name, ".")) 
		ret = 0;
	else if (ft_strncmp(d_name, file, ft_strlen(file)))
		ret = 0;
	else if (!access_file(d_name, path, mode))
		ret = 0;
	else if (ft_strchr(d_name, ' '))
		change_dname(d_name);
	else if (d_name[0] == '.' && (!file || file[0] != '.'))
		ret = 0;
	return (ret);
}

static char	*get_file(char *file, char *path, size_t *len, ushort mode)
{
	DIR         *dirp;
	t_dirent    *drnt;
	char        *str[2];

	str[0] = NULL;
	if (!(dirp = opendir(path)))
		return (NULL);
	while ((drnt = readdir(dirp)))
		if (condition_(drnt->d_name, file, path, mode))
		{
			if (*len < ft_strlen(drnt->d_name))
				*len = ft_strlen(drnt->d_name);
			str[1] = str[0];
			str[0] = ft_strjoin(str[1], ":");
			ft_strdel(&str[1]);
			str[1] = str[0];
			str[0] = ft_strjoin(str[1], drnt->d_name);
			ft_strdel(&str[1]);
		}
	closedir(dirp);
	return (str[0]);
}

static char	**get_tabfile2(char *file, char **path, size_t *len)
{
	char		*str[2];
	char		**t_file;
	char		*tmp;
	size_t		i;

	i = 0;
	str[0] = NULL;
	while (path[i])
	{
		str[1] = get_file(file, path[i], len, ONLY_CMD);
		tmp = str[0];
		str[0] = ft_strjoin(str[0], str[1]);
		ft_strdel(&str[1]);
		ft_strdel(&tmp);
		ft_strdel(&path[i++]);
	}
	free(path);
	t_file = ft_strsplit(str[0], ':');
	ft_strdel(&str[0]);
	return (t_file);
}

static char     **get_tabfile1(t_ac *ac, size_t *len)
{
	char        *str[2];
	char        **t_file;

	str[0] = NULL;
	if (ft_strcmp(ac->cmd, "cd"))
		str[0] = get_file(ac->file, ac->path, len, ONLY_DIR | ONLY_CMD);
	else
		str[0] = get_file(ac->file, ac->path, len, ONLY_DIR);
	t_file = ft_strsplit(str[0], ':');
	ft_strdel(&str[0]);
	return (t_file);
}

int		get_lfile(t_ac *ac, size_t *len)
{
	char    **path;

	if (ac->file && ac->file[0] != '.' && !ft_strcmp(ac->cmd, ac->file))
	{
		if (!(path = ft_strsplit(getenv("PATH"), ':')))
			return (0);
		ac->files = get_tabfile2(ac->file, path, len);
	}
	else
		ac->files = get_tabfile1(ac, len);
	if (!(ac->files))
		return (0);
	return (1);
}
