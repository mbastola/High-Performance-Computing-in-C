#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
# include <omp.h>

// problem description:
# define M 500
# define N 500
double epsilon = 0.001;
int max_steps = 1000; //max number of iterations
int num_random_walks = 20; 
int step_size = 20;
double w[M][N];

void initialize(){
  int i,j;
#pragma omp parallel shared ( w ) private ( i, j )
  {
#pragma omp parallel for 
    for ( i = 0; i < M; i++ )
      {
	w[i][0] = 100.0;
      }
#pragma omp parallel for 
    for ( i = 0; i < M; i++ )
      {
	w[i][N-1] = 200.0;
      }
#pragma omp parallel for 
    for ( j = 0; j < N; j++ )
      {
	w[M-1][j] = 50.0;
      }
#pragma omp parallel for 
    for ( j = 0; j < N; j++ )
      {
	w[0][j] = 0.0;
      }
  }
  return;
}

inline double boundaryValue(int i_, int j_){
  if (i_ < 0 ){
      i_ = 0;
    }
  if (i_ > M-1){
    i_ = M-1;
  }
  if (j_ < 0 ){
      j_ = 0;
    }
  if (j_ > N-1){
    j_ = M-1;
  }
  return w[i_][j_];
}


inline double random_walk(int i0, int j0, int* const ptr_n_success){
  int i_,j_, step;
  double ub = 0.0;
  i_ = i0;
  j_ = j0;
  double random_numbers[max_steps];
  unsigned int seed = time(NULL);
  for (step = 0; step < max_steps; ++step ){
    random_numbers[step] = ((double)rand_r(&seed)/RAND_MAX);
  }
  int up, down, left, right;
  up = 0;
  down = 0;
  left = 0;
  right = 0;
  for (step = 0; step < max_steps; ++step ){
    if (random_numbers[step] < 0.25){
      i_ = i_ - step_size;  // step left
      left++;
    }
    else if (random_numbers[step] < 0.5){
      i_ = i_ +step_size;  //step right
      right++;
    }
    else if (random_numbers[step] < 0.75){
      j_ = j_ - step_size;   //step down
      down++;
    }
    else{
      j_ = j_ + step_size;   //step up
      up++;
    }
    //check if we hit the boundary
    int boundary = (i_ < 0)||(i_ > M-1)||(j_ < 0)||(j_ > M-1);
    if (boundary){
      ub = boundaryValue(i_,j_);
      *ptr_n_success += 1;
      break; 
    }
  }
  return ub;
}

inline double many_walks(int i0, int j0){
  //ptr_n_success keeps track of how many walks reached boundary 
  double ub_sum = 0.0;   // to accumulate boundary values reached from all walks
  int k;
  double u_mc = 0.0;
  int n_success = 0;
  for (k = 0; k < num_random_walks; ++k){
    double ub = random_walk(i0, j0, &n_success);
    ub_sum += ub;
  }
  if (n_success != 0){
    u_mc = ub_sum /n_success; //average over successful walks
  }
  else{
    u_mc = 0.0;
  }
  return u_mc;
}

void random_walk_laplace(){
  double avg = 0.0;
  int totalSize = N*M;
  int nthreads = 1; 
  //int chunkSize = totalSize/nthreads;
  int i,j;
#pragma omp parallel shared ( avg, w ) private (i,j)
  {
   nthreads = omp_get_num_threads();
#pragma omp for reduction (+:avg) nowait
    
    for (i = 1; i < M-1 ; ++i ){
      for (j = 1; j < N-1 ; ++j ){
	{
	  double tmp = many_walks(i, j);
	  avg += tmp;
	  w[i][j] = tmp;
	}
      }
    }
  }
  avg /= totalSize;
  printf("NumThreads %d Mean temp %f", nthreads, avg);
  return;
}

int main (int argc, char* argv[]){
  double wtime = omp_get_wtime ( );
  initialize();
  random_walk_laplace();
  wtime = omp_get_wtime ( ) - wtime;
  printf ( "  Wallclock time = %f\n", wtime );
  return 0;
}
