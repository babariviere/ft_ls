/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 03:32:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/11 09:51:08 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*ft_concat_path(const char *dir_path, const char *name)
{
	char	*tmp;

	if (dir_path == 0)
		return (ft_strdup(name));
	if (dir_path[0] == 0)
		return (ft_strdup(name));
	if (dir_path[0] == '/' && dir_path[1] == 0)
		return (ft_strjoin(dir_path, name));
	tmp = ft_strjoin_sep(dir_path, "/", name);
	return (tmp);
}

t_path		*ft_init_path(const char *dir_path, const char *name, short ftype)
{
	t_path		*path;

	if ((path = malloc(sizeof(t_path))) == 0)
		return (0);
	path->path = ft_concat_path(dir_path, name);
	path->name = ft_strdup(name);
	path->ftype = ftype;
	return (path);
}

t_lst		*ft_get_subpath(const char *path, int follow_lnk, int hidden,
		int set_stat)
{
	DIR				*dir;
	struct dirent	*ent;
	t_lst			*spath;
	t_lst			*nw;

	if (path == 0)
		return (0);
	spath = 0;
	if ((dir = opendir(path)) == 0)
	{
		print_last_err(path);
		return (0);
	}
	while ((ent = readdir(dir)))
		if ((ent->d_name[0] == '.' && hidden) || ent->d_name[0] != '.')
		{
			nw = ft_lstnew_mv(ft_init_path(path, ent->d_name, ent->d_type),
					sizeof(t_path));
			if (set_stat)
				ft_path_readstat(nw->content, follow_lnk);
			ft_lstpush(&spath, nw);
		}
	closedir(dir);
	spath = (spath == 0 ? ft_lstnew(0, 0) : spath);
	return (spath);
}

void		ft_free_path(t_path **path)
{
	if (path == 0 || *path == 0)
		return ;
	if ((*path)->path)
		free((*path)->path);
	if ((*path)->name)
		free((*path)->name);
	free(*path);
	*path = 0;
}
