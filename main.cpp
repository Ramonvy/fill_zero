#include <iostream>
#include <dirent.h>
#include <vector>
#include <stdint.h>
#include "String.cpp"
#include "ArrayList.cpp"

void fill0file(char *filename){
	FILE *f = fopen(filename, "r");
	fseek(f, 0, SEEK_END);
	unsigned long long int fsz = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	
	f = fopen(filename, "w");
	
	while(ftell(f) < fsz){
		fprintf(f, "%c", 0);
	}
	
	fclose(f);
}

ArrayList<char*> listFiles(char *folder){
	char allfiles[30000] = "";
	char *aux;
	
	DIR *dir;
	struct dirent *lsdir;

	dir = opendir(folder);

	ArrayList<char*> files;
	
	/* print all the files and directories within directory */
	while(( lsdir = readdir(dir) ) != NULL ){
		aux = (char*)malloc(3000 * sizeof(char));
		strcpy(aux, lsdir->d_name);
		
		//sprintf(allfiles, "%s%s\n", allfiles, lsdir->d_name);
		
		if(strcmp(String(aux).getstr(), ".") != 0 && strcmp(String(aux).getstr(), "..") != 0 && strcmp(String(aux).getstr(), "fill_zero.exe") != 0){
			files.add(String(aux).getstr());
		}
	}

	closedir(dir);
	
	//printf("%s\n", allfiles);
	
	//printf("list_sz = %d\n", files.size());
	
	return files;
}

void fill0crr_folder(){
	ArrayList<char*> ar = listFiles(".\\");
	
	for(int i = 0; i < ar.size(); i++){
		printf("%s\n", ar.get(i));
		fill0file(ar.get(i));
	}
}

int main(int argc, char** argv) {
	char buffer[1000];
	printf("executar? ");
	gets(buffer);
	
	fill0crr_folder();
	return 0;
}
