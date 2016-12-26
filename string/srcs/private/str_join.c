/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:55:29 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:59:10 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_private.h"

#include <stdlib.h>

char	*str_join(char *str1, char *str2)
{
	char	*str;

	if (0 != (str = (char *)malloc(
		sizeof(char) * (str_len(str1) + str_len(str2)))))
		str_cat(str_cat(str, str1), str2);
	return (str);
}
