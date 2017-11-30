/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 04:17:40 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 06:03:38 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(int err, const char *path)
{
	ft_putstr_fd("ls: ", 2);
	if (path)
	{
		ft_putstr_fd(path, 2);
		ft_putchar_fd(':', 2);
	}
	ft_putendl_fd(strerror(err), 2);
}
