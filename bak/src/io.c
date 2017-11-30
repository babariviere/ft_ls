/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:00:01 by briviere          #+#    #+#             */
/*   Updated: 2017/11/29 20:14:08 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		count_files(size_t *dst, char *path, int hidden)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = opendir(path);
	if (dir == 0)
		return (-1);
	while ((ent = readdir(dir)))
	{
		if (ft_strequ(ent->d_name, ".") || ft_strequ(ent->d_name, ".."))
			continue ;
		if (ent->d_name[0] == '.' && !hidden)
			continue ;
		(*dst)++;
	}
	closedir(dir);
	return (1);
}

int		check_file_exists(char *path)
{
	struct stat		path_stat;

	return (stat(path, &path_stat) == 0);
}
