/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:43:50 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/22 16:16:08 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_parse(int fd, t_game *map)
{
	char	*temp;
	char	*buf;
	int		op_num;
	int		blank;

	op_num = 0;
	blank = 0;
	temp = ft_strdup("");
	while (get_next_line(fd, &buf))
	{
		if (op_num == 6)
			check_blank(buf, &temp, &blank);
		if (op_num != 6 && buf[0] != 0)
			op_num += check_option(map, buf);
		free(buf);
	}
	free(buf);
	if (op_num != 6 || !map_check(map, temp))
		error_handler("Error\ninvaild map");
	close(fd);
	free(temp);
}

void	check_blank(char *buf, char **temp, int *blank)
{
	if (*blank == -1 && ft_strlen(buf) > 0)
		error_handler("Error\ninvaild map");
	if (*blank && ft_strlen(buf) == 0)
		*blank = -1;
	if (ft_strlen(buf) > 0)
	{
		*temp = ft_strjoin(*temp, buf);
		*temp = ft_strjoin(*temp, "\n");
		*blank = 1;
	}
}

int		check_option(t_game *map, char *buf)
{
	int pass;

	pass = 0;
	if (buf[0] == 'N' && buf[1] == 'O')
		pass += set_tex_path(map, buf, 1);
	else if (buf[0] == 'S' && buf[1] == 'O')
		pass += set_tex_path(map, buf, 2);
	else if (buf[0] == 'W' && buf[1] == 'E')
		pass += set_tex_path(map, buf, 3);
	else if (buf[0] == 'E' && buf[1] == 'A')
		pass += set_tex_path(map, buf, 4);
	else if (buf[0] == 'F' && buf[1] == ' ')
		pass += set_color(map, &buf[1], 1);
	else if (buf[0] == 'C' && buf[1] == ' ')
		pass += set_color(map, &buf[1], 0);
	else
		error_handler("Error\nUnspecified identifier");
	return (pass);
}

int		set_tex_path(t_game *map, char *buf, int key)
{
	char **line;

	line = ft_split(buf, ' ');
	if (line[2] || !line[1] || !(line[1][0] == '.' && line[1][1] == '/'))
		error_handler("Error\ninvaild texture path");
	is_current_file(line[1], ".xpm");
	if (key == 1)
		map->img.no = ft_substr(line[1], 2, ft_strlen(line[1]) - 2);
	if (key == 2)
		map->img.so = ft_substr(line[1], 2, ft_strlen(line[1]) - 2);
	if (key == 3)
		map->img.we = ft_substr(line[1], 2, ft_strlen(line[1]) - 2);
	if (key == 4)
		map->img.ea = ft_substr(line[1], 2, ft_strlen(line[1]) - 2);
	ft_free(line);
	return (1);
}

int		set_color(t_game *map, char *buf, int key)
{
	char	**temp;
	char	*num;
	int		rgb[3];
	int		color;
	int		i;

	temp = ft_split(buf, ',');
	if (temp[3])
		error_handler("Error\ninvaild rgb color");
	i = -1;
	while (++i < 3)
	{
		num = ft_strtrim(temp[i], " ");
		rgb[i] = ft_atoi(num);
		free(num);
		if ((rgb[i] < 0 || rgb[i] > 255))
			error_handler("Error\ninvaild rgb color");
	}
	color = (rgb[0] * 256 * 256) + (rgb[1] * 256) + rgb[2];
	if (key)
		map->img.floor = color;
	else
		map->img.ceiling = color;
	ft_free(temp);
	return (1);
}
