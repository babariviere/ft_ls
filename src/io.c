/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 04:35:54 by briviere          #+#    #+#             */
/*   Updated: 2017/12/05 08:39:06 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		count_files(const char *path, int hidden)
{
	DIR				*dir;
	struct dirent	*ent;
	int				count;

	dir = opendir(path);
	if (dir == 0)
		return (-1);
	count = 0;
	while ((ent = readdir(dir)))
	{
		if ((ent->d_name[0] == '.' && hidden) || ent->d_name[0] != '.')
			count++;
	}
	closedir(dir);
	return (count);
}
