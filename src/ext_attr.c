/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_attr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 03:23:39 by briviere          #+#    #+#             */
/*   Updated: 2017/12/02 15:16:09 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		has_xattr(const char *path, int follow_lnk)
{
	return (listxattr(path, 0, 0, (follow_lnk ? 0 : XATTR_NOFOLLOW)) > 0);
}

static int		has_acl(const char *path, int follow_lnk)
{
	acl_t			acl;
	acl_entry_t		acl_entry;

	if (follow_lnk)
		acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	else
		acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_entry) == -1)
	{
		acl_free(acl);
		acl = 0;
	}
	return (acl != 0);
}

char			*get_xattr_symbol(const char *path, int follow_lnk)
{
	if (has_xattr(path, follow_lnk))
		return (ft_strdup("@"));
	else if (has_acl(path, follow_lnk))
		return (ft_strdup("+"));
	else
		return (ft_strdup(" "));
}
