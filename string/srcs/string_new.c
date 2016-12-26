/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:55:15 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:56:30 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*string_new(char *str)
{
	t_string		*string;

	if (0 == (string = (t_string *)malloc(sizeof(t_string))))
		return (0);
	string->str = 0;
	string->len = 0;
	string_cat((char *)&string->str, str);
	return ((char *)&string->str);
}
