/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:00:01 by briviere          #+#    #+#             */
/*   Updated: 2017/11/24 17:00:28 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	count_files(char *path)
{
	size_t	count;
	DIR		*dir;

	count = 0;
	dir = opendir(path);
	if (dir == 0)
		return (0);
	while (readdir(dir))
		count++;
	closedir(dir);
	return (count);
}

int		check_if_is_dir(char *path)
{
	struct stat		path_stat;

	stat(path, &path_stat);
	return ((path_stat.st_mode & S_IFDIR) == S_IFDIR);
}

char	**get_dir_rec(char *path, t_arg_opt *opt)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**paths;
	char			*joined;
	size_t			idx;

	dir = opendir(path);
	paths = ft_memalloc(sizeof(char *) * (len + 1));
	while ((ent = readdir(dir)) != 0)
	{
		if (ft_strcmp(ent->d_name, ".") == 0 ||
				ft_strcmp(ent->d_name, "..") == 0)
			continue ;
		if (ent->d_name[0] == '.' && opt->hidden == 0)
			continue ;
		joined = ft_strjoin(path, ent->d_name);
		if (check_if_is_dir(joined))
			paths[idx++] = ft_strjoin(joined, ent->d_name);
	}
	closedir(dir);
}
