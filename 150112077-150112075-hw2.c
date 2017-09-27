// Sema Çevik 150112077   Sibel Aymış 150112075   hw2

#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <string.h>     /* String handling */
#include <unistd.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000000

typedef struct{
int prime;
int threadnum;
int isprime;
} Number;

typedef struct{
int selfid;
int id;
} Thread_ID;
Thread_ID ID[SIZE];
Number primes[SIZE];
int limit;
int threads;
int a=1;
FILE *fp;



int main(int argc,char *argv[]){




	int tid,nthreads;
	char filename[50];
		 
int chunk=5;
	int i,j,k;
	

	if(argc<5 ||argc>7){
		printf("Number of argument is invalid.\n");
		printf("Input type should be\n ./project2.out -n 100 -o outputfile\n or\n ./project2.out -n 100 -t 4 -o outputfile\n");
		return 0;
	}
	if(strcmp(argv[1],"-n")==0){
		limit=atoi(argv[2]);
	

	}
	else{
		printf("invalid input type.\n");
		return 1;
	}
	if(strcmp(argv[3],"-t")==0){
		threads=atoi(argv[4]);
if(threads>5 || threads<3){
printf("Threads num is 3-5.\n");
		return 7;
	}

	}
	else if(strcmp(argv[3],"-o")==0){
		threads=4;
		strcpy(filename,argv[4]);
	}
	else if(strcmp(argv[3],"-t")!=0 && strcmp(argv[3],"-o")!=0){
		printf("invalid input type.\n");
		return 2;
	}
	if(argc>6 && strcmp(argv[5],"-o")==0){
		strcpy(filename,argv[6]);
	}
else{
printf("Enter file name\n");
return 3;
}
      
	primes[0].isprime=0;
	primes[1].isprime=0;
	for(i=2;i<=limit;i++){
		primes[i].prime = i;
		primes[i].isprime=1;
	}
omp_set_num_threads(threads);
#pragma omp parallel shared(nthreads) private(tid,j,k,a) 
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Starting matrix multiple example with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }
 printf("Starting matrix multiple example with %d threads\n",tid);


  
 #pragma omp parallel for schedule (dynamic,chunk) //private(j,k) //schedule (static,2) 
	for(a=1;a<=limit;a++){


	        if (primes[a].isprime){

			// printf("a-threadnum  %d tid %d \n",primes[a].threadnum,tid);
			//for(k=0;k<nthreads;k++){
				

					primes[a].threadnum=tid;        
			
			//}
        		for (j = a;a * j < limit; j++){
        			primes[a * j].isprime = 0;

			}

		}
	
 	}
	
	
 

} //finish 	


if((fp = fopen(filename,"w") )==NULL){
		printf("ERROR");
		exit(0);
}



	else{
		for (i = 2;i < limit; i++){
	        	if (primes[i].isprime){
	                fprintf(fp,"thread %d,\t%d\n",primes[i].threadnum, primes[i].prime);

printf("thread %d,\t%d\n",primes[i].threadnum, primes[i].prime);
		}
	}
	}
	fclose(fp);


}
