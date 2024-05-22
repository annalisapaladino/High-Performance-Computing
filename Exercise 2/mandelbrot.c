// Annalisa Paladino SM3800021
// High Performance Computing 2023
// Exercise 2C - The Mandelbrot set (MPI + OpenMP)

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

// Function to compute Mandelbrot
unsigned char mandelbrot(double x0, double y0, int max_iter) {
    double x = 0, y = 0, xtemp;
    int iter = 0;
    while (x*x + y*y <= 4 && iter < max_iter) {
        xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
        iter++;
    }
    return iter;
}

// Main function
int main(int argc, char *argv[]) {
    int mpi_provided_thread_level;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &mpi_provided_thread_level);
    if (mpi_provided_thread_level < MPI_THREAD_FUNNELED) {
        printf("The threading support level is lesser than that demanded\n");
        MPI_Finalize();
        exit(1);
    }
    
    double global_start_time = MPI_Wtime(); // Start time

    // Default values for Mandelbrot set parameters
    int nx = 800;
    int ny = 600; 
    int max_iter = 255;
    double xl = -2.0;
    double xr = 1.0;
    double yl = -1.0;
    double yr = 1.0;

    // MPI variables for process coordination
    int world_size, world_rank, num_threads;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (argc == 9) {
        nx = atoi(argv[1]);
        ny = atoi(argv[2]);
        xl = atof(argv[3]);
        yl = atof(argv[4]);
        xr = atof(argv[5]);
        yr = atof(argv[6]);
        max_iter = atoi(argv[7]);
        num_threads = atoi(argv[8]);
        omp_set_num_threads(num_threads); // Set number of OpenMP threads
    }
    
    // Rows of the image each process will generate
    int rows_per_process = ny / world_size;
    int remainder_rows = ny % world_size;
    int start_row = world_rank * rows_per_process;
    int end_row = start_row + rows_per_process + (world_rank == world_size - 1 ? remainder_rows : 0);
    // Allocate memory for the local portion of the Mandelbrot set
    unsigned char* local_image = (unsigned char*)malloc(nx * (end_row - start_row) * sizeof(unsigned char));

    // Compute Mandelbrot set using OpenMP for parallelization
    #pragma omp parallel for schedule(dynamic)
    for (int j = start_row; j < end_row; j++) {
        for (int i = 0; i < nx; i++) {
            double x = xl + i * (xr - xl) / nx;
            double y = yl + j * (yr - yl) / ny;
            local_image[(j - start_row) * nx + i] = mandelbrot(x, y, max_iter);
        }
    }

    // Gather all partial Mandelbrot sets into a single image on the root process
    int *recvcounts = NULL;
    int *displs = NULL;
    unsigned char *image = NULL;

    if (world_rank == 0) {
        recvcounts = malloc(world_size * sizeof(int));
        displs = malloc(world_size * sizeof(int));
        int displacement = 0;
        for (int i = 0; i < world_size; i++) {
            recvcounts[i] = nx * (rows_per_process + (i == world_size - 1 ? remainder_rows : 0));
            displs[i] = displacement;
            displacement += recvcounts[i];
        }
        image = (unsigned char*)malloc(displacement * sizeof(unsigned char));
    }

    MPI_Gatherv(local_image, nx * (end_row - start_row), MPI_UNSIGNED_CHAR, image, recvcounts, displs, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    free(local_image); // Free the local image memory

    if (world_rank == 0) {
        FILE *file = fopen("mndlbrt.pgm", "w");
        fprintf(file, "P5\n%d %d\n255\n", nx, ny);
        fwrite(image, sizeof(unsigned char), nx * ny, file);
        fclose(file);
        free(image);
        free(recvcounts);
        free(displs);
    }
    
    double global_end_time = MPI_Wtime();
    if (world_rank == 0) {
        printf("%f", global_end_time - global_start_time);
    }

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}
