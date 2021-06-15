/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyenam <hyenam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:28:10 by hyenam            #+#    #+#             */
/*   Updated: 2021/06/14 12:30:52 by hyenam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char *argv[])
{
	t_game	map;
	int		fd;

	if (argc == 2)
	{
		if (is_current_file(argv[1], ".cub"))
		{
			fd = open(argv[1], O_RDONLY);
			if (fd < 0)
				error_handler("Error\nFile open error\n");
			if (!map_parse(fd, &map))
				error_handler("Error\ninvalid file\n");
			start_game(&map);
		}
	}
	else if (argc > 2)
		error_handler("Error\nToo many file\n");
	else
		error_handler("Error\nInput .cub file\n");
}

void	error_handler(char *text)
{
	printf("%s\n", text);
	exit(1);
}
