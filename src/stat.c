/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 19:16:25 by briviere          #+#    #+#             */
/*   Updated: 2017/12/08 15:06:52 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*get_pw_name(uid_t uid)
{
	struct passwd	*pwd;

	pwd = getpwuid(uid);
	if (pwd)
		return (ft_strdup(pwd->pw_name));
	else
		return (ft_itoa(uid));
}

char		*get_gr_name(uid_t uid)
{
	struct group	*grp;

	grp = getgrgid(uid);
	if (grp)
		return (ft_strdup(grp->gr_name));
	else
		return (ft_itoa(uid));
}

char		*get_file_time(long tm)
{
	time_t		nw;
	time_t		ftime;
	char		*time_str;
	char		*ctime_res;

	if ((time_str = ft_strnew(13)) == 0)
		return (0);
	ftime = tm;
	nw = time(0);
	ctime_res = ctime(&ftime);
	ft_strncpy(time_str, ctime_res + 4, 7);
	if (ftime > nw || ftime < (nw - 16070400))
		ft_strncpy(time_str + 7, ctime_res + 19, 5);
	else
		ft_strncpy(time_str + 7, ctime_res + 11, 5);
	if (time_str[9] == ' ')
		ft_strncpy(time_str + 7, ctime_res + 23, 6);
	return (time_str);
}
