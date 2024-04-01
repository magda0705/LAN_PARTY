   #include <stdio.h>
   int main (int argc, char* argv[]) {
      //printf("Number of input files: %d\n", argc);
      //printf("Exec name: %s\n", argv[0]);
      //printf("File1: %s\n", argv[1]);
      // printf("File2: %s\n", argv[2]);
      // printf("File3: %s\n", argv[3]);

	        FILE *cin = fopen( argv[1], "r" ); 
 		FILE *din = fopen( argv[2], "r" );
	  	FILE *out = fopen( argv[3], "w" );
		int task[5];
			for(int i = 0; i < 5; i++)
			fscanf( cin , "%d" , &task[i] );
		
       // FILE *f_in = fopen( argv[1], "r" );
return 0; }
