/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 03:32:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/07 14:37:22 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*ft_concat_path(const char *dir_path, const char *name)
{
	char	*tmp;
	size_t	dir_len;

	if (dir_path == 0)
		return (ft_strdup(name));
	if (dir_path[0] == 0)
		return (ft_strdup(name));
	dir_len = ft_strlen(dir_path);
	if (dir_path[dir_len - 1] == '/')
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

int			ft_path_readstat(t_path *path, int follow_lnk)
{
	struct stat		st;
	int				res;

	if (path->ftype == DT_LNK && !follow_lnk)
		res = lstat(path->path, &st);
	else
		res = stat(path->path, &st);
	if (res < 0)
	{
		ft_putstr("ls: ");
		perror(path->path);
		return (0);
	}
	path->mode = st.st_mode;
	path->nlink = st.st_nlink;
	path->uid = st.st_uid;
	path->gid = st.st_gid;
	path->atime = st.st_atime;
	path->mtime = st.st_mtime;
	path->ctime = st.st_ctime;
	path->btime = st.st_birthtime;
	path->size = st.st_size;
	path->blocks = st.st_blocks;
	return (1);
}

t_list		*ft_get_subpath(const char *path, int follow_lnk, int hidden,
		int set_stat)
{
	DIR				*dir;
	struct dirent	*ent;
	t_list			*spath;
	t_list			*nw;

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
			nw = ft_lstnew(ft_init_path(path, ent->d_name, ent->d_type),
					sizeof(t_path));
			if (set_stat)
				ft_path_readstat(nw->content, follow_lnk);
			ft_lstpush(&spath, nw);
		}
	closedir(dir);
	return (spath);
}

void		ft_free_path(t_path **path)
{
	if (path == 0 || *path == 0)
		return ;
	if ((*path)->path)
		ft_strdel(&(*path)->path);
	if ((*path)->name)
		ft_strdel(&(*path)->name);
	ft_memdel((void **)path);
}
