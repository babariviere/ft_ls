/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 03:32:38 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 04:15:19 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*ft_init_path(char *dir_path, char *name, int follow_lnk)
{
	t_path	*path;
	char	*d_path;
	size_t	dir_len;
	int		res;

	if ((path = ft_memalloc(sizeof(t_path))) == 0)
		return (0);
	dir_len = (dir_path == 0 ? 0 : ft_strlen(dir_path));
	if (dir_len == 0)
		d_path = ft_strnew(0);
	else if (dir_path[dir_len - 1] == '/')
		d_path = ft_strdup(dir_path);
	else
		d_path = ft_strjoin(dir_path, "/");
	path->path = ft_strjoin(d_path, name);
	path->name = ft_strdup(name);
	if (follow_lnk)
		res = stat(path->path, &path->stat);
	else
		res = lstat(path->path, &path->stat);
	if (res < 0)
	{
		perror("ls: ");
		return (0);
	}
	return (path);
}
