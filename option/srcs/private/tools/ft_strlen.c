/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:35 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:35 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_strlen(const char *str)
{
    char *p;

    p = (char *)str;
    while (p && *p)
        p++;
    return (p - str);
}
