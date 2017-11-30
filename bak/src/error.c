/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:19:03 by briviere          #+#    #+#             */
/*   Updated: 2017/11/29 15:28:44 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(char *err)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putendl_fd(err, 2);
}

void	print_error2(char *err_s, char *err_e)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(err_s, 2);
	ft_putendl_fd(err_e, 2);
}

void	print_error3(char *err_s, char *err_m, char *err_e)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(err_s, 2);
	ft_putstr_fd(err_m, 2);
	ft_putendl_fd(err_e, 2);
}
