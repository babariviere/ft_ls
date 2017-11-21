/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:11:38 by briviere          #+#    #+#             */
/*   Updated: 2017/11/21 15:33:48 by briviere         ###   ########.fr       */
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
	else if ((mode & S_ISUID) || (mode & S_ISGID))
		ft_putchar('s');
	else
		ft_putchar('-');
}

void			print_permissions(const int mode)
{
	print_file_type(mode);
	ft_putchar(mode & S_IRUSR ? 'r' : '-');
	ft_putchar(mode & S_IWUSR ? 'w' : '-');
	ft_putchar(mode & S_IXUSR ? 'x' : '-');
	ft_putchar(mode & S_IRGRP ? 'r' : '-');
	ft_putchar(mode & S_IWGRP ? 'w' : '-');
	ft_putchar(mode & S_IXGRP ? 'x' : '-');
	ft_putchar(mode & S_IROTH ? 'r' : '-');
	ft_putchar(mode & S_IWOTH ? 'w' : '-');
	ft_putchar(mode & S_IXOTH ? 'x' : '-');
}
