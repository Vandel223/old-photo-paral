#include "gd.h"


/******************************************************************************
 * texture_image()
 *
 * Arguments: in - pointer to image
 *            texture - pointer to texture image
 * Returns: out - pointer to image with watermark, or NULL in case of failure
 * Side-Effects: none
 *
 * Description: creates clone of image and puts a watermark on it
 *
 *****************************************************************************/
gdImagePtr  texture_image(gdImagePtr in_img, gdImagePtr watermark);



/******************************************************************************
 * smooth_image()
 *
 * Arguments: in - pointer to image
 * Returns: out - pointer to smoother image, or NULL in case of failure
 * Side-Effects: none
 *
 * Description: creates clone of image smoother
 *
 *****************************************************************************/
gdImagePtr  smooth_image(gdImagePtr in_img);

/******************************************************************************
 * sepia_image()
 *
 * Arguments: in - pointer to image
 * Returns: out - pointer to sepia image, or NULL in case of failure
 * Side-Effects: none
 *
 * Description: creates clone of image but with sepia color
 *
 *****************************************************************************/
gdImagePtr  sepia_image(gdImagePtr in_img);


/******************************************************************************
 * contrast_image()
 *
 * Arguments: in - pointer to image
 * Returns: out - pointer to transformed image, or NULL in case of failure
 * Side-Effects: none
 *
 * Description: creates clone of image but its contrast reduced
 *
 *****************************************************************************/
gdImagePtr  contrast_image(gdImagePtr in_img);


/******************************************************************************
 * read_png_file()
 *
 * Arguments: file_name - name of file with data for PNG image
 * Returns: img - the image read from file or NULL if failure to read
 * Side-Effects: none
 *
 * Description: reads a PNG image from a file
 *
 *****************************************************************************/
gdImagePtr read_png_file(char * file_name);

/******************************************************************************
 * write_png_file()
 *
 * Arguments: img - pointer to image to be written
 *            file_name - name of file where to save PNG image
 * Returns: (bool) 1 in case of success, 0 in case of failure to write
 * Side-Effects: none
 *
 * Description: writes a PNG image to a file
 *
 *****************************************************************************/
int write_png_file(gdImagePtr write_img, char * file_name);



/******************************************************************************
 * read_jpeg_file()
 *
 * Arguments: file_name - name of file with data for JPEG image
 * Returns: img - the image read from file or NULL if failure to read
 * Side-Effects: none
 *
 * Description: reads a PNG image from a file
 *
 *****************************************************************************/
gdImagePtr read_jpeg_file(char * file_name);

/******************************************************************************
 * write_jpeg_file()
 *
 * Arguments: img - pointer to image to be written
 *            file_name - name of file where to save JPEG image
 * Returns: (bool) 1 in case of success, 0 in case of failure to write
 * Side-Effects: none
 *
 * Description: writes a PNG image to a file
 *
 *****************************************************************************/
int write_jpeg_file(gdImagePtr write_img, char * file_name);

/******************************************************************************
 * read_heif_file()
 *
 * Arguments: file_name - name of file with data for HEIF image
 * Returns: img - the image read from file or NULL if failure to read
 * Side-Effects: none
 *
 * Description: reads a HEIF image from a file
 *
 *****************************************************************************/
gdImagePtr read_heif_file(char * file_name);

/******************************************************************************
 * write_heif_file()
 *
 * Arguments: img - pointer to image to be written
 *            file_name - name of file where to save HEIF image
 * Returns: (bool) 1 in case of success, 0 in case of failure to write
 * Side-Effects: none
 *
 * Description: writes a HEIF image to a file
 *
 *****************************************************************************/
int write_heif_file(gdImagePtr write_img, char * file_name);

/******************************************************************************
 * create_directory()
 *
 * Arguments: file_name - name of directory to be created
 * Returns: (bool) 1 if the directory already exists or succesfully created
 *                 0 in case of failure to create
 * Side-Effects: none
 *
 * Description: Create a directory. 
 *
 *****************************************************************************/
int create_directory(char * dir_name);

/******************************************************************************
 * readFiles()
 *
 * Arguments: dir - name of directory to look for image-list.txt and read it
 * Returns: (char **) -         array of filenames
 *          int nn_files -      number of files
 *          int total_size -    total size of files in KBytes
 * Side-Effects: allocs an array of strings
 *
 * Description: Reads all picture names names in image-list.txt in the given
 * 				directory
 *
 *****************************************************************************/
char **readFiles(char *dir, int *nn_files);

/******************************************************************************
 * destroyFiles()
 * 
 * Arguments:	files - array of filenames
 * Returns: 	(void)
 * 
 * Description: function o free the array of filenames
 * 
 ******************************************************************************/
void destroyFiles(char **files, int nn_files);

/*****************************************************************************
 * isFileExists()
 * 
 * Arguments:	path - path to file
 * Returns: 	(int)	1 if file exists at given path otherwise returns 0.
 * 
 * Description: function to check whether a file exists or not using
 * 				fopen() function.
 *****************************************************************************/
int isFileExists(const char *filename);

/******************************************************************************
 * isFileExists()
 * 
 * Arguments:	path - path to directory
 * Returns: 	(int)	1 if directory exists at given path otherwise returns 0.
 * 
 * Description: function to check whether a dir exists or not using opendir()
 * 
 ******************************************************************************/
int isDirExists(const char *dirname);

struct timespec diff_timespec(const struct timespec *time1, const struct timespec *time0);
