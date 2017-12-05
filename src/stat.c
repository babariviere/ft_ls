/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 19:16:25 by briviere          #+#    #+#             */
/*   Updated: 2017/12/05 08:34:16 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_pw_name(uid_t uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(uid);
	if (pwd)
		return (ft_strdup(pwd->pw_name));
	else
		return (ft_itoa(uid));
}

char	*get_gr_name(uid_t uid)
{
	struct group	*grp;

	grp = getgrgid(uid);
	if (grp)
		return (ft_strdup(grp->gr_name));
	else
		return (ft_itoa(uid));
}

char	*get_file_time(struct timespec time)
{
	time_t		ftime;
	char		*time_str;

	ftime = time.tv_sec;
	time_str = ft_strsub(ctime(&ftime), 4, 13);
	if (time_str == 0)
		return (0);
	time_str[12] = 0;
	return (time_str);
}
