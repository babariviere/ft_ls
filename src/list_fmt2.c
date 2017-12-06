/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fmt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:38:39 by briviere          #+#    #+#             */
/*   Updated: 2017/12/06 16:38:46 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_total_blocks(t_path **path, size_t total_blk,
		size_t tab_len)
{
	char	*tmp;

	if (tab_len == 1 && FT_ISREG(path[0]->stat->st_mode))
		return ;
	ft_putstr("total ");
	tmp = ft_itoa(total_blk);
	ft_putendl(tmp);
	free(tmp);
}
