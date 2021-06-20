/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:37:12 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/20 13:51:47 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		map_check(t_game *map, char *str)
{
	char	**temp_map;
	int		w;
	int		h;

	temp_map = ft_split(str, '\n');
	w = 0;
	h = 0;
	while (temp_map[h] != 0)
	{
		if (w < (int)ft_strlen(temp_map[h]))
			w = ft_strlen(temp_map[h]);
		h++;
	}
	set_line_weight(temp_map, h, w);
	map->map_info.h = h;
	map->map_info.w = w;
	is_correct(map, temp_map);
	map_atoi(map, temp_map);
	ft_free(temp_map);
	return (1);
}

void	set_line_weight(char **temp, int h, int w)
{
	char	*line;
	int		len;
	int		i;
	int		j;

	i = -1;
	while (++i < h)
	{
		len = ft_strlen(temp[i]);
		if (len != w)
		{
			line = (char *)malloc(sizeof(char) * w + 1);
			if (!line)
				return ;
			ft_strlcpy(line, temp[i], w + 1);
			j = 0;
			while (len + j < w)
				line[len + j++] = ' ';
			line[len + j] = 0;
			free(temp[i]);
			temp[i] = ft_strdup(line);
			free(line);
		}
	}
}

void	map_atoi(t_game *map, char **temp_map)
{
	int overlap;
	int i;
	int j;

	overlap = 0;
	map->map_info.map = ft_int_malloc(map->map_info.h, map->map_info.w);
	i = -1;
	while (++i < map->map_info.h)
	{
		j = -1;
		while (++j < map->map_info.w)
			overlap += data_checking(map, temp_map[i][j], i, j);
	}
	if (overlap > 1)
		error_handler("Error\nToo many player in the map");
	if (!overlap)
		error_handler("Error\nNo player in the map");
}

int		is_correct(t_game *map, char **temp)
{
	char	**transposed;
	int		i;
	int		j;

	transposed = ft_char_malloc(map->map_info.w, map->map_info.h);
	i = -1;
	while (++i < map->map_info.w)
	{
		j = -1;
		while (++j < map->map_info.h)
			transposed[i][j] = temp[j][i];
		transposed[i][j] = 0;
	}
	transposed[i] = 0;
	if (check_side(temp, map->map_info.h) &&
		check_side(transposed, map->map_info.w))
	{
		ft_free(transposed);
		return (1);
	}
	error_handler("Error\ninvaild map");
	return (0);
}

int		check_side(char **arr, int h)
{
	char	*line;
	int		i;

	i = -1;
	while (++i < h)
	{
		line = ft_strtrim(arr[i], " ");
		if (!(line[0] - '0' && line[ft_strlen(line) - 1] - '0'))
			error_handler("Error\ninvaild map (wall)");
		if (ft_strchr(line, ' '))
			if (ft_strchr("1 ", line[ft_strchr(line, ' ') - 2]) < 1 ||
				ft_strchr("1 ", line[ft_strchr(line, ' ')]) < 1)
				error_handler("Error\ninvaild map (blank)");
		free(line);
	}
	return (1);
}
