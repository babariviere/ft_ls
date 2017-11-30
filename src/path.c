/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 03:32:38 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 04:34:16 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*ft_concat_path(char *dir_path, char *name)
{
	char	*tmp;
	char	*tmp2;
	size_t	dir_len;

	if (dir_path == 0)
		return (ft_strdup(name));
	dir_len = ft_strlen(dir_path);
	if (dir_len == 0)
		return (ft_strdup(name));
	else if (dir_path[dir_len - 1] == '/')
		return (ft_strjoin(dir_path, name));
	tmp = ft_strjoin(dir_path, "/");
	tmp2 = ft_strjoin(tmp, name);
	free(tmp);
	return (tmp2);
}

t_path		*ft_init_path(char *dir_path, char *name, int follow_lnk)
{
	t_path		*path;
	int			res;

	if ((path = ft_memalloc(sizeof(t_path))) == 0)
		return (0);
	path->path = ft_concat_path(dir_path, name);
	path->name = ft_strdup(name);
	if ((path->stat = malloc(sizeof(struct stat))) == 0)
		return (0);
	if (follow_lnk)
		res = stat(path->path, &path->stat);
	else
		res = lstat(path->path, &path->stat);
	if (res < 0)
	{
		print_error(res, path->path);
		return (0);
	}
	return (path);
}

void		ft_free_path(t_path **path)
{
	if (path == 0 || *path == 0)
		return ;
	if (path->path)
		ft_strdel(&path->path);
	if (path->name)
		ft_strdel(&path->path);
	if (path->stat)
		ft_memdel((void **)&path->stat);
	ft_memdel((void **)path);
}
