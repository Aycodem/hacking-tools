#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#define MAX_WORD_LENGTH 50

//function that calculate the md5 algorithims of a string

void bytes2md5(const char *data, int len, char *md5buf) {
  // Based on https://www.openssl.org/docs/manmaster/man3/EVP_DigestUpdate.html
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  const EVP_MD *md = EVP_md5();
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len, i;
  EVP_DigestInit_ex(mdctx, md, NULL);
  EVP_DigestUpdate(mdctx, data, len);
  EVP_DigestFinal_ex(mdctx, md_value, &md_len);
  EVP_MD_CTX_free(mdctx);
  for (i = 0; i < md_len; i++) {
    snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
  }

}



int main(int argc, char *argv[]){
	if (argc != 3){
		printf("Usage: md5hasher <hash>  <wordlist>\n");
	}
	else{
		if (strlen(argv[1]) == 32){
		FILE *file ;
		char filepath[2000];
        size_t max_length = sizeof(filepath) - 1; // Leave room for the null terminator
       // Use strncpy to copy a limited number of characters
      	strncpy(filepath, argv[2], max_length);
       	filepath[max_length] = '\0'; // Ensure null-termination
		
		file =fopen(filepath,"r");

		if (file == NULL ){
			printf ("Unable to find file...\n");
			return 1;		
		}
		char** wordlistarray =NULL; // creating a array list 
		char** md5Array =NULL; 
		int wordcount = 0;

		while(1){
			char word[MAX_WORD_LENGTH + 1];
			int k = 0;

			int r = fscanf(file, "%s", word); // Read a word based on space-separated words 
			

             if (r == EOF) { // Break if the end of file
                    break;
                }

		
		  char* dynamicWord = strdup(word);

		  if (dynamicWord == NULL){
		   	perror("Memory allocation failed...");
		  	exit(1);
		  }

		  wordlistarray =realloc(wordlistarray, (wordcount + 1 ) * sizeof(char*));
		  if (wordlistarray == NULL ){
		  	perror("Memory allocation failed...");
		  	exit(1);
		  }

		  wordlistarray[wordcount++]= dynamicWord;

		}
	int j; 
	for (j=0 ; j< wordcount ;j++){
		char md5[33];
		bytes2md5(wordlistarray[j], strlen(wordlistarray[j]), md5);
		if (strcmp(md5 , argv[1]) == 0){
			printf("%s : %s\n",argv[1],wordlistarray[j]);
			break;
		}
		free(wordlistarray[j]);

	}


	free(wordlistarray);
	fclose(file);

		
}
else {
		printf("Invalid md5 hash...\n");
		
}
}
	return 0;
}