#ifndef _BMP_H_
# define _BMP_H_
# include "./cub3d.h"

typedef struct		s_BMPFileHeader{
	unsigned int	file_type;          // File type always BM which is 0x4D42
	unsigned int	file_size;               // Size of the file (in bytes)
	unsigned int	reserved1;               // Reserved, always 0
	unsigned int	reserved2;               // Reserved, always 0
	unsigned int	offset_data;             // Start position of pixel data (bytes from the beginning of the file)
}					t_BMPFileHeader;

typedef struct		s_BMPInfoHeader{
	unsigned int	size;                      // Size of this header (in bytes)
	int				width;                      // width of bitmap in pixels
	int				height;                     // width of bitmap in pixels
                                                  //       (if positive, bottom-up, with origin in lower left corner)
	                                             //       (if negative, top-down, with origin in upper left corner)
	unsigned int	planes;                    // No. of planes for the target device, this is always 1
	unsigned int	bit_count;                 // No. of bits per pixel
	unsigned int	compression;               // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
	unsigned int	size_image;                // 0 - for uncompressed images
	int				x_pixels_per_meter;
	int				y_pixels_per_meter;
	unsigned int	colors_used;               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
	unsigned int	colors_important;          // No. of colors used for displaying the bitmap. If 0 all colors are required
}					t_BMPInfoHeader;

typedef struct		s_BMPColorHeader{
	unsigned int	red_mask;         // Bit mask for the red channel
	unsigned int	green_mask;       // Bit mask for the green channel
	unsigned int	blue_mask;        // Bit mask for the blue channel
	unsigned int	alpha_mask;       // Bit mask for the alpha channel
	unsigned int	color_space_type; // Default "sRGB" (0x73524742)
//	unsigned int	unused[16]{ 0 };                // Unused data for sRGB color space
}					t_BMPColorHeader;

typedef struct		s_BMP{
	t_BMPFileHeader		file_header;
	t_BMPInfoHeader		bmp_info_header;
	t_BMPColorHeader	bmp_color_header;
}					t_BMP;

#endif
