/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:00:01 by briviere          #+#    #+#             */
/*   Updated: 2017/11/24 14:02:04 by briviere         ###   ########.fr       */
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
