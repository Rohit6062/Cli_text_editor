#include"huffman.c"
int main(int argc,char* argv[]){
    FILE* fileToRead;
    FILE* fileToWrite;
    char* strI=malloc(sizeof(char)*30);
    char* strO=malloc(sizeof(char)*30);    
    strcpy(strO,"decompressed.txt");
    if(argc>2){
        strcpy(strO,argv[2]);
        strcpy(strI,argv[1]);
    }
    else if(argc>1){
        strcpy(strI,argv[1]);
    }
    else{
        printf("Enter Full File Name: \n");
        scanf("%s",strI);
    }
    fileToRead = fopen(strI,"r");
    fileToWrite = fopen(strO,"w");
    if(fileToRead == NULL){
        printf("Failed To Open File\n");
        exit(0);
    }
    if(fileToRead == NULL){
        printf("Failed To Open File\n");
        exit(0);
    }
    unsigned char n;
    fread(&n,sizeof(n),1,fileToRead);
    //node* root = extractTree(fileToRead,root);
    printf("n = %d\n", n);
    asciicode* codeArray= malloc(sizeof(asciicode)*n);
    //generateCodes(root,codeArray,0,0);
    unsigned char get;
    int x;
    for(int i=0;i<n;i++){
        fread(&get,sizeof(get),1,fileToRead);
        codeArray[i].ascii=get;
        fread(&get,sizeof(get),1,fileToRead);
        codeArray[i].size=get;
        fread(&x,sizeof(x),1,fileToRead);
        codeArray[i].code=x;
    }
    asciiCodeSortBySize(codeArray,n);
    int read;
    char size=0;
    int find=0; 
    unsigned char res;
    
    unsigned char toAnd = 128;
    while(1){
        read = fgetc(fileToRead);
        if(read==EOF)break;
        while(1){
            size++;
            find = find << 1;
            find = find | (read & toAnd) >> (log_2(toAnd)-1);
            if (searchCode(codeArray,n,find,size,&res) == 1){
                fwrite(&res,sizeof(res),1,fileToWrite);
                size = 0;
                find = 0;
            }
            toAnd = toAnd >> 1;
            if(toAnd == 0){
                toAnd = 128;
                break;
            }
        }
    }
    fclose(fileToRead);
    fclose(fileToWrite);
    printf("Done\n");
    return 0;
}
