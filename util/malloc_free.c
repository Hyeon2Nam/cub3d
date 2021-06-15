/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:23:53 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/14 13:20:49 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free(char **str)
{
	int	len;
	int	i;

	len = 0;
	while (str[len])
		len++;
	i = 0;
	while (i < len)
		free(str[i++]);
	free(str);
	str = NULL;
}

int		**ft_int_malloc(int h, int w)
{
	int	**arr;
	int	i;

	arr = (int **)malloc(sizeof(int *) * h);
	if (!arr)
		return (0);
	i = 0;
	while (i < h)
	{
		arr[i] = (int *)malloc(sizeof(int) * w);
		if (!(arr[i]))
			return (0);
		i++;
	}
	return (arr);
}

char	**ft_char_malloc(int h, int w)
{
	char	**arr;
	int		i;

	arr = (char **)malloc(sizeof(char *) * h + 1);
	if (!arr)
		return (0);
	i = 0;
	while (i < h)
	{
		arr[i] = (char *)malloc(sizeof(char) * w + 1);
		if (!(arr[i]))
			return (0);
		i++;
	}
	return (arr);
}
