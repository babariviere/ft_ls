/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:11:38 by briviere          #+#    #+#             */
/*   Updated: 2017/11/24 13:21:23 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		gather_file_type(const int mode)
{
	if (mode & S_IFIFO)
		return ('p');
	else if (mode & S_IFCHR)
		return ('c');
	else if (mode & S_IFDIR)
		return ('d');
	else if (mode & S_IFBLK)
		return ('b');
	else if (mode & S_IFREG)
		return ('-');
	else if (mode & S_IFLNK)
		return ('l');
	else if (mode & S_IFSOCK)
		return ('s');
	else
		return ('-');
}

static char		gather_exec_perm(const int mode, const int sid_mask,
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

static char		gather_exec_perm_oth(const int mode)
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

char			*gather_permissions(const int mode)
{
	char	*dst;

	if ((dst = ft_strnew(10)) == 0)
		return (0);
	dst[0] = gather_file_type(mode);
	dst[1] = (mode & S_IRUSR ? 'r' : '-');
	dst[2] = (mode & S_IWUSR ? 'w' : '-');
	dst[3] = gather_exec_perm(mode, S_ISUID, S_IXUSR);
	dst[4] = (mode & S_IRGRP ? 'r' : '-');
	dst[5] = (mode & S_IWGRP ? 'w' : '-');
	dst[6] = gather_exec_perm(mode, S_ISGID, S_IXGRP);
	dst[7] = (mode & S_IROTH ? 'r' : '-');
	dst[8] = (mode & S_IWOTH ? 'w' : '-');
	dst[9] = gather_exec_perm_oth(mode);
	return (dst);
}
