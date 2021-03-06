/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:11:38 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 03:03:56 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		get_file_type(const int mode)
{
	if (FT_ISIFO(mode))
		return ('p');
	else if (FT_ISLNK(mode))
		return ('l');
	else if (FT_ISCHR(mode))
		return ('c');
	else if (FT_ISDIR(mode))
		return ('d');
	else if (FT_ISBLK(mode))
		return ('b');
	else if (FT_ISREG(mode))
		return ('-');
	else if (FT_ISSOCK(mode))
		return ('s');
	else
		return ('-');
}

static char		get_exec_perm(const int mode, const int sid_mask,
		const int x_mask)
{
	if (mode & x_mask && mode & sid_mask)
		return ('s');
	else if ((mode & x_mask) == 0 && mode & sid_mask)
		return ('S');
	else if (mode & x_mask)
		return ('x');
	else
		return ('-');
}

static char		get_exec_perm_oth(const int mode)
{
	if (mode & S_IXOTH && mode & S_ISVTX)
		return ('t');
	else if ((mode & S_IXOTH) == 0 && mode & S_ISVTX)
		return ('T');
	else if (mode & S_IXOTH)
		return ('x');
	else
		return ('-');
}

char			*get_permissions(const int mode)
{
	char	*dst;

	if ((dst = ft_strnew(10)) == 0)
		return (0);
	dst[0] = get_file_type(mode);
	dst[1] = (mode & S_IRUSR ? 'r' : '-');
	dst[2] = (mode & S_IWUSR ? 'w' : '-');
	dst[3] = get_exec_perm(mode, S_ISUID, S_IXUSR);
	dst[4] = (mode & S_IRGRP ? 'r' : '-');
	dst[5] = (mode & S_IWGRP ? 'w' : '-');
	dst[6] = get_exec_perm(mode, S_ISGID, S_IXGRP);
	dst[7] = (mode & S_IROTH ? 'r' : '-');
	dst[8] = (mode & S_IWOTH ? 'w' : '-');
	dst[9] = get_exec_perm_oth(mode);
	return (dst);
}
