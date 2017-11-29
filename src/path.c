/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 09:55:42 by briviere          #+#    #+#             */
/*   Updated: 2017/11/29 20:12:54 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*ft_init_path(char *dir_path, char *name)
{
	t_path			*res;
	char			*dir_path_s;
	struct stat		path_stat;

	if ((res = ft_memalloc(sizeof(t_path))) == 0)
		return (0);
	if (dir_path[ft_strlen(dir_path) - 1] != '/' && ft_strlen(dir_path) > 0)
		dir_path_s = ft_strjoin(dir_path, "/");
	else
		dir_path_s = ft_strdup(dir_path);
	res->path = ft_strjoin(dir_path_s, name);
	ft_strdel(&dir_path_s);
	res->name = ft_strdup(name);
	stat(res->path, &path_stat);
	res->sub_path = 0;
	res->sub_path_len = 0;
	res->is_dir = FT_ISDIR(path_stat.st_mode);
	res->permissions = 0;
	res->nlink = 0;
	res->pw_name = 0;
	res->gr_name = 0;
	res->size = 0;
	res->mtime = 0;
	res->blocks = path_stat.st_blocks;
	return (res);
}

void	ft_set_path_info(t_path *path)
{
	struct stat		path_stat;
	time_t			file_time;
	char			*time_str;
	struct passwd	*pwd;
	struct group	*grp;

	lstat(path->path, &path_stat);
	path->permissions = gather_permissions(path_stat.st_mode);
	path->nlink = path_stat.st_nlink;
	pwd = getpwuid(path_stat.st_uid);
	if (pwd)
		path->pw_name = pwd->pw_name;
	else
		path->pw_name = ft_itoa(path_stat.st_uid);
	grp = getgrgid(path_stat.st_gid);
	if (grp)
		path->gr_name = grp->gr_name;
	else
		path->gr_name = ft_itoa(path_stat.st_gid);
	path->size = path_stat.st_size;
	file_time = path_stat.st_mtimespec.tv_sec;
	time_str = ft_strsub(ctime(&file_time), 4, 13);
	time_str[ft_strlen(time_str) - 1] = 0;
	path->mtime = time_str;
}

int		ft_set_dir_subfiles(t_path *path, int recursive, int set_info, int hidden, int depth)
{
	DIR				*dir;
	struct dirent	*ent;
	size_t			idx;

	if (path == 0)
		return (0);
	if (!path->is_dir)
		return (0);
	if (count_files(&path->sub_path_len, path->path, hidden) == -1)
		return (-1);
	path->sub_path_len += hidden * 2;
	if (path->sub_path_len == 0 || (path->sub_path = ft_memalloc(sizeof(t_path *) *
				(path->sub_path_len + 1))) == 0)
		return (0);
	path->sub_path[path->sub_path_len] = 0;
	if ((dir = opendir(path->path)) == 0)
		return (-1);
	idx = 0;
	depth--;
	while ((ent = readdir(dir)))
	{
		if ((ent->d_name[0] == '.' && hidden) || ent->d_name[0] != '.')
		{
			if ((path->sub_path[idx] = ft_init_path(path->path, ent->d_name)) == 0)
				return (0);
			if (recursive && !(ft_strequ(ent->d_name, ".") || ft_strequ(ent->d_name, "..")) && depth >= 0)
				ft_set_dir_subfiles(path->sub_path[idx], recursive, set_info, hidden, depth);
			if (set_info)
				ft_set_path_info(path->sub_path[idx]);
			idx++;
		}
	}
	closedir(dir);
	return (1);
}

size_t			ft_path_count_recursive(t_path *path)
{
	size_t	count;
	size_t	idx;

	if (!path)
		return (0);
	count = 0;
	idx = 0;
	while (path->sub_path && path->sub_path[idx])
		count += ft_path_count_recursive(path->sub_path[idx++]);
	if (path->path)
		count++;
	return (count);
}

size_t			ft_path_count_elem(t_path *path)
{
	size_t	elem;

	elem = 0;
	if (path->path)
		elem++;
	if (path->permissions)
		elem += 6;
	return (elem);
}

void			ft_sort_subpath(t_path *path, int (*cmp)(const char *, const char *))
{
	size_t		idx;
	size_t		sub_idx;

	if (path->sub_path == 0)
		return ;
	idx = 0;
	while (idx < path->sub_path_len - 1)
	{
		sub_idx = idx + 1;
		while (sub_idx < path->sub_path_len)
		{
			if (cmp(path->sub_path[idx]->name, path->sub_path[sub_idx]->name) > 0)
				ft_swap_ptr((void**)(path->sub_path + idx),
						(void**)(path->sub_path + sub_idx));
			sub_idx++;
		}
		idx++;
	}
}
