#include "cub3d.h"


void	create_bmp(t_data *data)
{
	int	bmp_fd;
// PAs sur pour le O TRUNC	
	bmp_fd = 1;
	if ((bmp_fd = open("./screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
	{
	//	ft_putstr_fd("\nFailed creating bmp\n", 1);
//	if ((bmp_fd = open("./screenshot.bmp", O_RDWR, O_TRUNC, S_IRWXU)) == -1)
		
	close_program(data, "Failed creating bmp with open", "");
		}
}


void	init_BMPHileHeader(t_BMPFileHeader *ptr)
{
	ptr->file_type = 0x4D42;
	ptr->file_size = 0;
	ptr->reserved1 = 0;
	ptr->reserved2 = 0;
	ptr->offset_data = 0;
}

void	init_BMPInfoHeader(t_BMPInfoHeader *ptr)
{
	ptr->size = 0;    // Size of this header (in bytes)
	ptr->width = 0;   // width of bitmap in pixels
	ptr->height = 0;  // width of bitmap in pixels
	                  //       (if positive, bottom-up, with origin in lower left corner)
	                  //       (if negative, top-down, with origin in upper left corner)
	ptr->planes = 1;  // No. of planes for the target device, this is always 1
	ptr->bit_count = 0;    // No. of bits per pixel
	ptr->compression = 3;  // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images Personal note : 3 for 32 bits images
	ptr->size_image = 0;   // 0 - for uncompressed images
	ptr->x_pixels_per_meter = 0;
	ptr->y_pixels_per_meter = 0;
	ptr->colors_used = 0;   // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
	ptr->colors_important = 0;  // No. of colors used for displaying the bitmap. If 0 all colors are required
}

void	init_BMPColorHeader(t_BMPColorHeader *ptr)
{
	ptr->red_mask = 0x00ff0000;         // Bit mask for the red channel
	ptr->green_mask = 0x0000ff00;       // Bit mask for the green channel
	ptr->blue_mask = 0x000000ff;        // Bit mask for the blue channel
	ptr->alpha_mask = 0xff000000;       // Bit mask for the alpha channel
	ptr->color_space_type = 0x73524742; // Default "sRGB" (0x73524742)
//	ptr->unused[16] = 0;                // Unused data for sRGB color space
}
