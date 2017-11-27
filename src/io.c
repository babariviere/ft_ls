/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:00:01 by briviere          #+#    #+#             */
/*   Updated: 2017/11/27 17:25:11 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	count_files(char *path, int hidden)
{
	size_t			count;
	DIR				*dir;
	struct dirent	*ent;

	count = 0;
	dir = opendir(path);
	if (dir == 0)
		return (0);
	while ((ent = readdir(dir)))
	{
		if (ft_strequ(ent->d_name, ".") || ft_strequ(ent->d_name, ".."))
			continue ;
		if (ent->d_name[0] == '.' && !hidden)
			continue ;
		count++;
	}
	closedir(dir);
	return (count);
}

int		check_if_is_dir(char *path)
{
	struct stat		path_stat;

	stat(path, &path_stat);
	return ((path_stat.st_mode & S_IFDIR) == S_IFDIR);
}
