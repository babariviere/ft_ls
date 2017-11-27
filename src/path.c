/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 09:55:42 by briviere          #+#    #+#             */
/*   Updated: 2017/11/27 17:41:23 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*ft_init_path(char *path)
{
	t_path	*res;

	if ((res = ft_memalloc(sizeof(t_path))) == 0)
		return (0);
	res->path = ft_strdup(path);
	res->sub_path = 0;
	res->permissions = 0;
	res->nlink = 0;
	res->pw_name = 0;
	res->gr_name = 0;
	res->size = 0;
	res->mtime = 0;
	return (res);
}

void	ft_set_path_info(t_path *path)
{
	struct stat		path_stat;
	time_t			file_time;
	char			*time_str;

	stat(path->path, &path_stat);
	path->permissions = gather_permissions(path_stat.st_mode);
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
	size_t			len;

	len = count_files(path->path, hidden);
	if (len == 0 || (path->sub_path = ft_memalloc(sizeof(t_path *) * (len + 1))) == 0)
		return ;
	path->sub_path[len] = 0;
	if ((dir = opendir(path->path)) == 0)
		return ;
	idx = 0;
	while ((ent = readdir(dir)))
	{
		if (ft_strequ(ent->d_name, ".") || ft_strequ(ent->d_name, ".."))
			continue ;
		if ((ent->d_name[0] == '.' && hidden) || ent->d_name[0] != '.')
		{
			if ((path->sub_path[idx] = ft_memalloc(sizeof(t_path))) == 0)
				return ;
			path->sub_path[idx]->path = ft_strdup(ent->d_name);
			if (recursive)
				ft_set_dir_subfiles(path->sub_path[idx], recursive, set_info, hidden);
			idx++;
		}
	}
	closedir(dir);
}

void	ft_print_path_and_sub(t_path *path, char *parent)
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
