/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 02:44:55 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/18 03:09:22 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	img_pixel_put(t_img *img, long x, long y, int colour)
{
	char	*pxl;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	pxl = img->img_pxls_ptr + (y * img->line_len)
		+ (x * (img->bits_per_pxl / 8));
	*(unsigned int *)pxl = colour;
}

static void	line_init(t_line *line, t_point *p0, t_point *p1)
{
	line->x0 = p0->screen_x;
	line->x1 = p1->screen_x;
	line->y0 = p0->screen_y;
	line->y1 = p1->screen_y;
	if (line->x1 - line->x0 >= 0)
		line->dx = line->x1 - line->x0;
	else
		line->dx = -(line->x1 - line->x0);
	if (line->y1 - line->y0 >= 0)
		line->dy = line->y1 - line->y0;
	else
		line->dy = -(line->y1 - line->y0);
	line->sx = 1;
	line->sy = 1;
	if (line->x0 > line->x1)
		line->sx = -1;
	if (line->y0 > line->y1)
		line->sy = -1;
	line->err = line->dx - line->dy;
}

static void	draw_line(t_img *img, t_point *p0, t_point *p1)
{
	t_line	line;
	int		e2;
	int		colour;

	colour = p0->colour;
	line_init(&line, p0, p1);
	while (1)
	{
		img_pixel_put(img, line.x0, line.y0, colour);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		e2 = line.err * 2;
		if (e2 > -line.dy)
		{
			line.err = line.err - line.dy;
			line.x0 = line.x0 + line.sx;
		}
		if (e2 < line.dx)
		{
			line.err = line.err + line.dx;
			line.y0 = line.y0 + line.sy;
		}
	}
}

void	img_render(t_data *data)
{
	size_t	x;
	size_t	y;
	t_map	*map;
	t_point	*pts;

	map = data->map;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			pts = &map->matrix[x][y];
			if (x + 1 < map->cols)
				draw_line(&data->img, pts, &map->matrix[x + 1][y]);
			if (y + 1 < map->rows)
				draw_line(&data->img, pts, &map->matrix[x][y + 1]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img_ptr, 0, 0);
}
