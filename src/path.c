/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 09:55:42 by briviere          #+#    #+#             */
/*   Updated: 2017/11/28 12:56:08 by briviere         ###   ########.fr       */
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
	if (dir_path[ft_strlen(dir_path - 1)] != '/' && ft_strlen(dir_path) > 0)
		dir_path_s = ft_strjoin(dir_path, "/");
	else
		dir_path_s = ft_strdup(dir_path);
	res->path = ft_strjoin(dir_path_s, name);
	ft_strdel(&dir_path_s);
	res->name = ft_strdup(name);
	stat(res->path, &path_stat);
	res->sub_path = 0;
	res->sub_path_len = 0;
	res->mode = path_stat.st_mode;
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

	stat(path->path, &path_stat);
	path->permissions = gather_permissions(path->mode);
	path->nlink = path_stat.st_nlink;
	path->pw_name = getpwuid(path_stat.st_uid)->pw_name;
	path->gr_name = getgrgid(path_stat.st_gid)->gr_name;
	path->size = path_stat.st_size;
	file_time = path_stat.st_mtimespec.tv_sec;
	time_str = ft_strsub(ctime(&file_time), 4, 13);
	time_str[ft_strlen(time_str) - 1] = 0;
	path->mtime = time_str;
}

void	ft_set_dir_subfiles(t_path *path, int recursive, int set_info, int hidden)
{
	DIR				*dir;
	struct dirent	*ent;
	size_t			idx;

	path->sub_path_len = count_files(path->path, hidden);
	if (path->sub_path_len == 0 || (path->sub_path = ft_memalloc(sizeof(t_path *) *
					(path->sub_path_len + 1))) == 0)
		return ;
	path->sub_path[path->sub_path_len] = 0;
	if ((dir = opendir(path->path)) == 0)
		return ;
	idx = 0;
	while ((ent = readdir(dir)))
	{
		if (ft_strequ(ent->d_name, ".") || ft_strequ(ent->d_name, ".."))
			continue ;
		if ((ent->d_name[0] == '.' && hidden) || ent->d_name[0] != '.')
		{
			if ((path->sub_path[idx] = ft_init_path(path->path, ent->d_name)) == 0)
				return ;
			if (recursive)
				ft_set_dir_subfiles(path->sub_path[idx], recursive, set_info, hidden);
			if (set_info)
				ft_set_path_info(path->sub_path[idx]);
			idx++;
		}
	}
	closedir(dir);
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

t_formatted		**ft_path_to_formatteds(t_path *path, char *str)
{
	t_formatted		**formatteds;
	t_formatted		**tmp1;
	t_formatted		**tmp2;
	char			*p_str;
	size_t			idx;

	if ((formatteds = ft_memalloc(sizeof(t_formatted *) * 2)) == 0)
		return (0);
	if ((formatteds[0] = ft_init_formatted(ft_path_count_elem(path))) == 0)
		return (0);
	p_str = ft_strjoin(str, path->path);
	ft_add_formatted_str(formatteds[0], p_str, 0);
	formatteds[1] = 0;
	idx = 0;
	if (path->sub_path == 0 || path->sub_path_len == 0)
		return (formatteds);
	if (path->path[ft_strlen(path->path) - 1] != '/')
		p_str = ft_strjoin(p_str, "/");
	while (idx < path->sub_path_len)
	{
		tmp1 = formatteds;
		tmp2 = ft_path_to_formatteds(path->sub_path[idx++], p_str);
		formatteds = (t_formatted**)ft_join_tab((void*)tmp1,
				(void*)tmp2, sizeof(t_formatted *));
		ft_memdel((void **)&tmp1);
		ft_memdel((void **)&tmp2);
	}
	return (formatteds);
}

void			ft_print_path_and_sub(t_path *path, char *parent)
{
	char	*full_path;
	char	*tmp;
	size_t	idx;

	if (!path)
		return ;
	if (path->path && parent)
		full_path = ft_strjoin(parent, path->path);
	else if (path->path)
		full_path = ft_strdup(path->path);
	else
		return ;
	ft_putendl(full_path);
	tmp = full_path;
	full_path = ft_strjoin(full_path, "/");
	//free(tmp);
	idx = 0;
	while (path->sub_path && path->sub_path[idx])
		ft_print_path_and_sub(path->sub_path[idx++], full_path);
}
