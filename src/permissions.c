/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:11:38 by briviere          #+#    #+#             */
/*   Updated: 2017/11/21 16:59:40 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_file_type(const int mode)
{
	if (mode & S_IFIFO)
		ft_putchar('p');
	else if (mode & S_IFCHR)
		ft_putchar('c');
	else if (mode & S_IFDIR)
		ft_putchar('d');
	else if (mode & S_IFBLK)
		ft_putchar('b');
	else if (mode & S_IFREG)
		ft_putchar('-');
	else if (mode & S_IFLNK)
		ft_putchar('l');
	else if (mode & S_IFSOCK)
		ft_putchar('s');
	else
		ft_putchar('-');
}

static void		print_exec_perm(const int mode, const int sid_mask, const int x_mask)
{
	if (mode & x_mask && mode & sid_mask)
		ft_putchar('s');
	else if ((mode & x_mask) == 0 && mode & sid_mask)
		ft_putchar('S');
	else if (mode & x_mask)
		ft_putchar('x');
	else
		ft_putchar('-');
}

static void		print_exec_perm_oth(const int mode)
{
	if (mode & S_IXOTH && mode & S_ISVTX)
		ft_putchar('t');
	else if ((mode & S_IXOTH) == 0 && mode & S_ISVTX)
		ft_putchar('T');
	else if (mode & S_IXOTH)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void			print_permissions(const int mode)
{
	print_file_type(mode);
	ft_putchar(mode & S_IRUSR ? 'r' : '-');
	ft_putchar(mode & S_IWUSR ? 'w' : '-');
	print_exec_perm(mode, S_ISUID, S_IXUSR);
	ft_putchar(mode & S_IRGRP ? 'r' : '-');
	ft_putchar(mode & S_IWGRP ? 'w' : '-');
	print_exec_perm(mode, S_ISGID, S_IXGRP);
	ft_putchar(mode & S_IROTH ? 'r' : '-');
	ft_putchar(mode & S_IWOTH ? 'w' : '-');
	print_exec_perm_oth(mode);
}
