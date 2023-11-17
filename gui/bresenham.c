#include "bresenham.h"

void brs_drawline(brs_point_t *p_one, brs_point_t *p_two, uint8_t color)
{
	int dist_x = abs(p_two->brs_x - p_one->brs_x);
	int dist_y = abs(p_two->brs_y - p_one->brs_y);

	int x_step = (p_one->brs_x < p_two->brs_x) ? 1 : -1;
	int y_step = (p_one->brs_y < p_two->brs_y) ? 1 : -1;

	int error = dist_x - dist_y;
	int error_double;

	while (1) {
		put_pixel(p_one->brs_x, p_one->brs_y, color);

		if (p_one->brs_x == p_two->brs_x &&
		    p_one->brs_y == p_two->brs_y) {
			break;
		}

		error_double = 2 * error;

		if (error_double > -dist_y) {
			error -= dist_y;
			p_one->brs_x += x_step;
		}
		if (error_double < dist_x) {
			error += dist_x;
			p_one->brs_y += y_step;
		}
	}
}