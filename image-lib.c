#include "image-lib.h"
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/* the image-list file path */
#define IMAGE_LIST "/image-list.txt"
/* the directories wher output files will be placed */
#define OLD_IMAGE_DIR "/old_photo_PAR_A"

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
gdImagePtr  texture_image(gdImagePtr in_img, gdImagePtr texture_img){
	
	gdImagePtr out_img;

	int width,heigth;

	width = in_img->sx;
	heigth = in_img->sy;


	gdImageSetInterpolationMethod(texture_img, GD_BILINEAR_FIXED);
    gdImagePtr scalled_pattern = gdImageScale(texture_img, width, heigth);


	out_img =  gdImageClone (in_img);

	gdImageCopy(out_img, scalled_pattern, 0, 0, 0, 0, width, heigth);
	gdImageDestroy(scalled_pattern);
	return(out_img);		
} 




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
gdImagePtr  smooth_image(gdImagePtr in_img){
	
	gdImagePtr out_img;
	
	out_img =  gdImageClone (in_img);
	if (!out_img) {
		return NULL;
	}

	int ret = gdImageSmooth(out_img, 20);


	if (!out_img) {
		return NULL;
	}

	return(out_img);		
} 




/******************************************************************************
 * contrast_image()
 *
 * Arguments: in - pointer to image
 * Returns: out - pointer to high contrast  image, or NULL in case of failure
 * Side-Effects: none
 *
 * Description: creates clone of image but its contrast reduced
 *
 *****************************************************************************/
gdImagePtr  contrast_image(gdImagePtr in_img){
	
	gdImagePtr out_img;
	
	out_img =  gdImageClone (in_img);
	if (!out_img) {
		return NULL;
	}

	int ret = gdImageContrast(out_img, -20);


	return(out_img);		
} 



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
gdImagePtr  sepia_image(gdImagePtr in_img){
	
	gdImagePtr out_img;
	
	out_img =  gdImageClone (in_img);
	if (!out_img) {
		return NULL;
	}

	int ret = gdImageColor(out_img, 100, 60, 0, 0);


	return(out_img);		
} 




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
gdImagePtr read_png_file(char * file_name){

	FILE * fp;
	gdImagePtr read_img;

	fp = fopen(file_name, "rb");
   	if (!fp) {
        fprintf(stderr, "Can't read image %s\n", file_name);
        return NULL;
    }
    read_img = gdImageCreateFromPng(fp);
    fclose(fp);
  	if (read_img == NULL) {
    	return NULL;
    }

	return read_img;
}

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
int write_png_file(gdImagePtr write_img, char * file_name){
	FILE * fp;

	fp = fopen(file_name, "wb");
	if (fp == NULL) {
		return 0;
	}
	gdImagePng(write_img, fp);
	fclose(fp);

	return 1;
}

/******************************************************************************
 * read_jpeg_file()
 *
 * Arguments: file_name - name of file with data for JPEG image
 * Returns: img - the image read from file or NULL if failure to read
 * Side-Effects: none
 *
 * Description: reads a JPEG image from a file
 *
 *****************************************************************************/
gdImagePtr read_jpeg_file(char * file_name){

	FILE * fp;
	gdImagePtr read_img;

	fp = fopen(file_name, "rb");
   	if (!fp) {
        fprintf(stderr, "Can't read image %s\n", file_name);
        return NULL;
    }
    read_img = gdImageCreateFromJpeg(fp);
    fclose(fp);
  	if (read_img == NULL) {
    	return NULL;
    }

	return read_img;
}

/******************************************************************************
 * write_jpeg_file()
 *
 * Arguments: img - pointer to image to be written
 *            file_name - name of file where to save JPEG image
 * Returns: (bool) 1 in case of success, 0 in case of failure to write
 * Side-Effects: none
 *
 * Description: writes a JPEG image to a file
 *
 *****************************************************************************/
int write_jpeg_file(gdImagePtr write_img, char * file_name){
	FILE * fp;

	fp = fopen(file_name, "wb");
	if (fp == NULL) {
		return 0;
	}
	gdImageJpeg(write_img, fp, 70);
	fclose(fp);

	return 1;
}

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
gdImagePtr read_heif_file(char * file_name){

	FILE * fp;
	gdImagePtr read_img;

	fp = fopen(file_name, "rb");
   	if (!fp) {
        fprintf(stderr, "Can't read image %s\n", file_name);
        return NULL;
    }
    read_img = gdImageCreateFromHeif(fp);
    fclose(fp);
  	if (read_img == NULL) {
    	return NULL;
    }

	return read_img;
}

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
int write_heif_file(gdImagePtr write_img, char * file_name){
	FILE * fp;

	fp = fopen(file_name, "wb");
	if (fp == NULL) {
		return 0;
	}
	gdImageHeif(write_img, fp);
	fclose(fp);

	return 1;
}

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
int create_directory(char * dir_name){

	DIR * d = opendir(dir_name);
	if (d == NULL){
		if (mkdir(dir_name, 0777)!=0){
			return 0;
		}
	}else{
		fprintf(stderr, "%s directory already existent\n", dir_name);
		closedir(d);
	}
	return 1;
}

/******************************************************************************
 * readFiles()
 *
 * Arguments: dir - name of directory to look for image-list.txt and read it
 * Returns: (char **) -         array of filenames in image-list.txt
 *          int nn_files -      number of files
 * Side-Effects: allocs an array of strings
 *
 * Description: Reads all picture names names in image-list.txt in the given
 * 				directory
 *
 *****************************************************************************/
char **readFiles(char *dir, int *nn_files) {

	char buffer[256];						/* allocate buffer*/
	char outFileName[256];					/* another buffer to check out file existence */
	FILE *listFp;
	char **files;

	/* get the image-list path */
	sprintf(buffer, "%s%s", dir, IMAGE_LIST);
	char *img = strrchr(buffer, '/') + 1;
	/* open it */
	listFp = fopen(buffer, "rb");
	*nn_files = 0;

	int imgLen = 256 - strlen(dir) - strlen(IMAGE_LIST);

	/* count the number of files*/
	while ( fgets(img, imgLen, listFp) != NULL ) {

		/* clean fgets() \n*/
		img[strcspn(img, "\n")] = '\0';

		/* check out file existence */
		sprintf(outFileName, "%s%s%s", dir,  OLD_IMAGE_DIR, img - 1);
		if (isFileExists(outFileName)) {
			fprintf(stdout, "Found file:\t%s\n", outFileName);
			continue;
		}

		/* check if file exists*/
		if (!isFileExists(buffer)) {
			fprintf(stdout, "Not able to locate - %s\n", buffer);
			continue;
		}

		/* check if file exists and is JPEG format */
		if ((strcmp(strrchr(img, '.'), ".jpeg") && strcmp(strrchr(img, '.'), ".jpg"))) {
			fprintf(stdout, "Only supports JPEG format - %s\n", buffer);
			continue;
		}
		
		(*nn_files)++;
	}

	/* create array of filenames */
	files = (char **) malloc(*nn_files * sizeof(char *));

	fseek(listFp, 0, SEEK_SET);
	int i = 0;

	while ( fgets(img, imgLen, listFp) != NULL ) {

		/* clean fget() \n */
		img[strcspn(img, "\n")] = '\0';

		/* check out file existence */
		sprintf(outFileName, "%s%s%s", dir,  OLD_IMAGE_DIR, img - 1);
		if (isFileExists(outFileName)) {
			continue;
		}

		/* check if file exists*/
		if (!isFileExists(buffer)) {
			continue;
		}

		/* check if file exists and is JPEG format */
		if ((strcmp(strrchr(img, '.'), ".jpeg") && strcmp(strrchr(img, '.'), ".jpg"))) {
			continue;
		}

		files[i] = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
		sprintf(files[i++], "%s", buffer);
		
	}

	fclose(listFp);
	return files;

}

/******************************************************************************
 * destroyFiles()
 * 
 * Arguments:	files - array of filenames
 * Returns: 	(void)
 * 
 * Description: function o free the array of filenames
 * 
 ******************************************************************************/
void destroyFiles(char **files, int nn_files) {
	for (int i = 0; i < nn_files; i++) {
		free(files[i]);
	}
	free(files);
}

/******************************************************************************
 * isFileExists()
 * 
 * Arguments:	path - path to file
 * Returns: 	(int)	1 if file exists at given path otherwise returns 0.
 * 
 * Description: function to check whether a file exists or not using
 * 				stat() function.
 * 
 ******************************************************************************/
int isFileExists(const char *filename) {

	struct stat buffer;   
	return (stat (filename, &buffer) == 0);

}

/******************************************************************************
 * isFileExists()
 * 
 * Arguments:	path - path to directory
 * Returns: 	(int)	1 if directory exists at given path otherwise returns 0.
 * 
 * Description: function to check whether a dir exists or not using opendir()
 * 
 ******************************************************************************/
int isDirExists(const char *dirname) {

	DIR * aux = opendir(dirname);

	if (ENOENT == errno) {
		return 0;
	}
	closedir(aux);

	return 1;

}

/******************************************************************************
 * diff_timespec()
 *
 * Arguments: time 1 - structure containg the time seasure with  clock_gettime
 *            time 2 - structure containg the time seasure with  clock_gettime
 * Returns: (struct timespec) 
 * Side-Effects: none
 *
 * Description: This functino subtracts the two received times and returns the result
 *
 *****************************************************************************/
struct timespec diff_timespec(const struct timespec *time1, const struct timespec *time0) {
  assert(time1);
  assert(time0);
  struct timespec diff = {.tv_sec = time1->tv_sec - time0->tv_sec, //
      .tv_nsec = time1->tv_nsec - time0->tv_nsec};
  if (diff.tv_nsec < 0) {
    diff.tv_nsec += 1000000000; // nsec/sec
    diff.tv_sec--;
  }
  return diff;
}