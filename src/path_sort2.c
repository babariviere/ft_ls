/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:28:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/08 09:57:37 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_path_cmp_name(const t_path *p1, const t_path *p2)
{
	return (ft_strcmp(p1->name, p2->name));
}

int			ft_path_cmp_atime(const t_path *p1, const t_path *p2)
{
	if (p1->fatime == p2->fatime)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->fatime - p1->fatime);
}

int			ft_path_cmp_btime(const t_path *p1, const t_path *p2)
{
	if (p1->fbtime == p2->fbtime)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->fbtime - p1->fbtime);
}

int			ft_path_cmp_ctime(const t_path *p1, const t_path *p2)
{
	if (p1->fctime == p2->fctime)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->fctime - p1->fctime);
}

int			ft_path_cmp_mtime(const t_path *p1, const t_path *p2)
{
	if (p1->fmtime == p2->fmtime)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->fmtime - p1->fmtime);
}
