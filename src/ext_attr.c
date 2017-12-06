/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_attr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 03:23:39 by briviere          #+#    #+#             */
/*   Updated: 2017/12/06 10:04:08 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		has_xattr(const char *path, int follow_lnk)
{
	return (listxattr(path, 0, 0, (follow_lnk ? 0 : XATTR_NOFOLLOW)) > 0);
}

char			*get_xattr_symbol(const char *path, int follow_lnk)
{
	if (has_xattr(path, follow_lnk))
		return (ft_strdup("@"));
	else
		return (ft_strdup(" "));
}
