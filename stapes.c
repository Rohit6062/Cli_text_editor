#include"avlTree.c"
node * file ;
char official[] = ".default";
FILE* f;

buffArray* bapush(buffArray* ba, char data, int direction){
    if(data==10){
        if(file==NULL){
            file = createNode(ba);
        }
        else if(ba!=NULL){
            file = insertInAvl(file,ba,file->leftc+file->rightc+2);
        }
        return NULL;
    }
    else if(ba == NULL){
        ba=newBuffArray(data);
    }
    else if(direction==1){
        ba=baAppend(ba,data);
    }else{
        ba=baInsert(ba,data);
    }
    return ba;
}

void displayFile(){
    if(!file)return;
    int count=0;
    for(int i=1;i<=file->leftc+1+file->rightc;i++){
        printba(valueAt(file,i)->line);
        count += baLen(valueAt(file,i)->line)+1; 
    }
    printf("size Of File = %d bytes\n", count);
}

void savefile(FILE* f){
    if(!file)return;
    for(int i=1;i<file->leftc+file->rightc+2;i++){
        buffArray* tmp = valueAt(file,i)->line;
        int j=0;
        while(j<tmp->len){
            unsigned char ch= tmp->a[mod(tmp->start+tmp->size+1+j,tmp->size)];
            putc(ch,f);
            j++;
        }
        putc('\n',f);
    }
}

int searchBefore(char* word,int wlen,int lineNo){
    int output=-1;
    for(int i=lineNo-1;i>=0;i--){
        if (searchWord((valueAt(file,i))->line,word,wlen) == 1)
        {
            output=i;
            i=-1;
        }
    }
    return output;
}

int searchAfter(char* word, int wlen, int lineNo){
    int output=-1;
    if(!file)return output;
    for(int i=lineNo;i<file->leftc+file->rightc+2;i++){
        if (searchWord((valueAt(file,i))->line,word,wlen) != -1)
        {
            output=i;
            i=file->rightc+file->leftc+2;
        }
    }
    return output;
}

// returns index of line no if word found else -1
int search(char * word, int wlen){
    return searchAfter(word,wlen,0);
}

void storeCompressed(){
    f = fopen(official,"w");
    savefile(f);
    fclose(f);
    system("./compress .default .default1");
    system("mv .default1 .default");
    exit(0);
} 


void menu(){
    printf("Choose what you Want to Do: \n");
    printf("    Options: \n");
    printf("\t 0: Save and Exit\n");
    printf("\t 1: display file: \n");
    printf("\t 2: Add Line: \n");
    printf("\t 3: Delete Line: \n");
    printf("\t 4: search Word: \n");
}

int main()
{
    buffArray* bf = NULL;
    buffArray* l = NULL; 
    int read = 0;
    char str[10000];
    system("./decompress .default .default1");
    f = fopen(".default1","r");
    read = fgetc(f);
    while(read!=EOF){
        bf = bapush(bf,read,1);
        read = fgetc(f);
    }
    fclose(f);

    int ind=0;
    unsigned char byte;
    while(1){
        menu();
        scanf("%d",&read);
        switch(read){
            case 0:
                printf("Thank You !\n");
                storeCompressed();
            case 1:
                printf("\n\t ---> Contents Of File <--- \n");
                displayFile();
                break;
            case 2:
                printf("Enter Line: \n");
                ind=0;
                scanf("%c",&byte);
                scanf("%[^\n]s",str);
                printf("str = %s\n", str);
                while(ind < strlen(str)){
                    l=bapush(l,str[ind],1);
                    ind++;
                }
                if(file){
                    file = insertInAvl(file,l,file->leftc+file->rightc+2);
                }
                else{
                    file = insertInAvl(file,l,1);
                }
                l=NULL;
                break;
            case 3:
                printf("Enter Line No: \n");
                scanf("%d",&ind);
                file = deleteInAvl(file,ind);
                break; 
            case 4:
                printf("Enter the word to search: \n");
                scanf("%s",str);
                printf("If word is there You get Line No: Else -1 \n");
                printf("Result :- %d \n",search(str,strlen(str)));
                break;
            default:
                printf("Enter Valid choice\n");
                break;
        }
        printf("\n");
    }
}
