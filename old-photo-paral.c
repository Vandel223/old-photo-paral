/******************************************************************************
 * Programacao Concorrente
 * MEEC 21/22
 *
 * Projecto - Parte1
 *                           serial-complexo.c
 * 
 * Compilacao: gcc serial-complexo -o serial-complex -lgd
 *           
 *****************************************************************************/

#include <gd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "image-lib.h"

/* the directories wher output files will be placed */
#define OLD_IMAGE_DIR "./Old-image-dir/"

/******************************************************************************
 * struct argsPack
 *
 * Atributes:	st - 		start index
 * 				end - 		end index
 * 				files - 	array of files
 * 				texture - 	texture to filter pictures
 *
 * Description: the atributes of this struct correlate directly to the arguments
 * 				of the function:
 * 					void *oldFilter((argsPack *) void *args);
 *
 *****************************************************************************/

typedef struct {

	int st;
	int end;
	char **files;
	gdImagePtr texture;

} argsPack;

void *oldFilter(void *args) {

	/* local stores all "local variables" of oldFilter */
	argsPack *local = (argsPack *) args;

	int st = local->st;
	int end = local->end;
	char **files = local->files;
	gdImagePtr texture = local->texture;

	/* free local */
	free(local);

	printf("%d - %d:\n", st, end);

	gdImagePtr img;

	gdImagePtr contrastImage;
	gdImagePtr smoothImage;
	gdImagePtr textureImage;
	gdImagePtr sepiaImage;

	char outFileName[128];

	for (int i = st; i < end; i++){	

		fprintf(stdout, "%s\n", files[i]);

		/* load of the input file */
	    img = read_jpeg_file(files[i]);
		if (img == NULL){
			fprintf(stderr, "Impossible to read %s image\n", files[i]); 
			continue;
		}

		/* apply filter */
		contrastImage = contrast_image(img);
		smoothImage = smooth_image(contrastImage);
		textureImage = texture_image(smoothImage, texture);
		sepiaImage = sepia_image(textureImage); 

		/* save resized */ 
		sprintf(outFileName, "%s%s", OLD_IMAGE_DIR, strrchr(files[i], '/'));
		if(write_jpeg_file(sepiaImage, outFileName) == 0){
			fprintf(stderr, "Impossible to write %s image\n", outFileName);
		}
		gdImageDestroy(img);
		gdImageDestroy(contrastImage);
		gdImageDestroy(smoothImage);
		gdImageDestroy(textureImage);
		gdImageDestroy(sepiaImage);

	}

}

/******************************************************************************
 * main()
 *
 * Arguments: (none)
 * Returns: 0 in case of sucess, positive number in case of failure
 * Side-Effects: creates thumbnail, resized copy and watermarked copies
 *               of images
 *
 * Description: implementation of the complex serial version 
 *              This application only works for a fixed pre-defined set of files
 *
 *****************************************************************************/
int main(int argc, char **argv){
    struct timespec start_time_total, end_time_total;
    struct timespec start_time_seq, end_time_seq;
    struct timespec start_time_par, end_time_par;
	struct timespec start_time_seq2, end_time_seq2;

	clock_gettime(CLOCK_MONOTONIC, &start_time_total);
	clock_gettime(CLOCK_MONOTONIC, &start_time_seq);

	/* if argc isn't three we quit*/
	if (argc != 3) {
		fprintf(stdout, "\n\tUse the command:\n\n\t.old-photo-paral <files_dir> <nn_threads>\n\n");
		exit(0);
	}

	int nn_files = 0;
	char *dir = argv[1];						/* directory of files */
	char **files = readFiles(dir, &nn_files);	/* read files list */
	int nn_threads = atoi(argv[2]);	

	/* setup for range of files for threads */
	int idx = 0;
	int div = nn_files / nn_threads;
	int rem = nn_files % nn_threads;

	/* array of threads */
	pthread_t threads[nn_threads];

	/* creation of output directories */
	if (create_directory(OLD_IMAGE_DIR) == 0){
		fprintf(stderr, "Impossible to create %s directory\n", OLD_IMAGE_DIR);
		exit(-1);
	}

	gdImagePtr in_texture_img =  read_png_file("./paper-texture.png");


	clock_gettime(CLOCK_MONOTONIC, &end_time_seq);
	clock_gettime(CLOCK_MONOTONIC, &start_time_par);

	argsPack *args;


	/* Iteration over all the threads
	 */
	for (int i = 0; i < nn_threads; i++){	

		args = (argsPack *) malloc(sizeof(argsPack));

		/* set range of indexes */
		args->st = idx;
		idx += div;
		args->end = idx;

		/* while rem is greater than zero */
		if (rem > 0) {
			args->end++;
			idx++;
			rem --;
		}

		/* set files and texture */
		args->files = files;
		args->texture = in_texture_img;

		/* initialize thread */					  //send args
		pthread_create(&threads[i], NULL, oldFilter, args);

	}


	/* Iteration over all the threads
	 */
	for (int i = 0; i < nn_threads; i++) {

		/* join thread */
		pthread_join(threads[i], NULL);

	}

	clock_gettime(CLOCK_MONOTONIC, &end_time_par);
	clock_gettime(CLOCK_MONOTONIC, &start_time_seq2);

	destroyFiles(files, nn_files);
	gdImageDestroy(in_texture_img);

	clock_gettime(CLOCK_MONOTONIC, &end_time_seq2);
	clock_gettime(CLOCK_MONOTONIC, &end_time_total);

struct timespec par_time = diff_timespec(&end_time_par, &start_time_par);
struct timespec seq_time = diff_timespec(&end_time_seq, &start_time_seq);
struct timespec total_time = diff_timespec(&end_time_total, &start_time_total);
    printf("\tseq \t %10jd.%09ld\n", seq_time.tv_sec, seq_time.tv_nsec);
    printf("\tpar \t %10jd.%09ld\n", par_time.tv_sec, par_time.tv_nsec);
    printf("total \t %10jd.%09ld\n", total_time.tv_sec, total_time.tv_nsec);


	exit(0);
}
