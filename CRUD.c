#include<stdio.h>
#include<string.h>
int counter=0;
struct Student{
    char name[100];
    char department[100];
    double SGPA;
    double CGPA;
};
void Create(struct Student student[]){
    FILE *fpn = fopen("name.txt","a");
    FILE *fpd = fopen("department.txt","a");
    FILE *fps = fopen("SGPA.txt","a");
    FILE *fpc = fopen("CGPA.txt","a");

    char fname[100];
    printf("enter Student name : ");
    fgets(fname,100,stdin);
    fname[strcspn(fname, "\n")] = '\0';
    for (int i=0;i<counter;i++){
        if(strcmp(fname, student[i].name) == 0){
            printf("entered student already exists");
            goto exit;
        }
    }
    strcpy(student[counter].name,fname);
    student[counter].name[strcspn(student[counter].name, "\n")] = '\0';
    fprintf(fpn,"%-100s\n",student[counter].name);//%-100s\n used to reach the max line length which i set as 100, plus the last \n
    printf("enter Student department : ");
    fgets(student[counter].department,100,stdin);
    student[counter].department[strcspn(student[counter].department, "\n")] = '\0';
    fprintf(fpd,"%-100s\n",student[counter].department);
    printf("enter Student SGPA : ");
    scanf("%lf",&student[counter].SGPA);
    getchar();
    fprintf(fps,"%-100f\n",student[counter].SGPA);
    printf("enter Student CGPA : ");
    scanf("%lf",&student[counter].CGPA);
    getchar();//to collect the \n char from double input
    fprintf(fpc,"%-100f\n",student[counter].CGPA);
    counter++;
    exit:
    fclose(fpn);
    fclose(fpd);
    fclose(fps);
    fclose(fpc);
}
void Read(struct Student student[]){
    char fname[100];
    printf("enter the student to be searched :");
    fgets(fname,100,stdin);
    fname[strcspn(fname, "\n")] = '\0';
    int index=-1;
    for (int i=0;i<counter;i++){
        if (strcmp(fname,student[i].name)==0){
            printf("Student found!\n\n");
            index=i;
        }
    }
    if (index==-1){
        printf("Student not found!\n");
    }
    else{
        printf("Student name : %s\ndepartment : %s\nSGPA : %.3f\nCGPA : %.3f\n\n",student[index].name,student[index].department,student[index].SGPA,student[index].CGPA);
    }
}
void Update(struct Student student[]){
    FILE *fpn = fopen("name.txt","r+");
    FILE *fpd = fopen("department.txt","r+");
    FILE *fps = fopen("SGPA.txt","r+");
    FILE *fpc = fopen("CGPA.txt","r+");

    if (fpn == NULL || fpd == NULL || fps == NULL || fpc == NULL) {
        printf("No database found! Please CREATE a student first.\n");
        if (fpn) fclose(fpn);
        if (fpd) fclose(fpd);
        if (fps) fclose(fps);
        if (fpc) fclose(fpc);
        
        
        return;
    }
    int bytes_per_line=101;//since there is a \n char in the end of the line
    int byte_offset=0;
    next:

    rewind(fpn);
    rewind(fpd);
    rewind(fps);
    rewind(fpc);

    printf("enter student name: ");
    char fname[100];
    fgets(fname,100,stdin);
    fname[strcspn(fname, "\n")] = '\0';
    int index=-1;
    for (int i=0;i<counter;i++){
        if(strcmp(fname,student[i].name)==0){
            index=i;
            byte_offset=(index)*bytes_per_line;//keeping first line as the default there is no need to jump to get first line
        }
    }
    if (index ==-1){
        printf("student not found !!");
    }
    
    else 
    {
        printf("student found !");
        int choice=0;
        while (choice != 6){
            printf("To update name enter 1, for department 2 , for SGPA  3, for CGPA 4 , to update new student 5 & to exit 6 : \n");
            scanf("%d",&choice);
            getchar();
            switch(choice){
                case 1:
                fseek(fpn,byte_offset,SEEK_SET);
                printf("enter new name: ");
                char Nname[100];
                fgets(Nname,100,stdin);
                Nname[strcspn(Nname, "\n")] = '\0';
                strcpy(student[index].name,Nname);
                fprintf(fpn,"%-100s\n",Nname);
                break;
            case 2:
                fseek(fpd,byte_offset,SEEK_SET);
                printf("enter new department: ");
                char Ndept[100];
                fgets(Ndept,100,stdin);
                Ndept[strcspn(Ndept, "\n")] = '\0';
                strcpy(student[index].department,Ndept);
                fprintf(fpd,"%-100s\n",Ndept);
                break;
            case 3:
                fseek(fps,byte_offset,SEEK_SET);
                printf("enter new SGPA: ");
                double NSGPA;
                scanf("%lf",&NSGPA);
                getchar();
                student[index].SGPA=NSGPA;
                fprintf(fps,"%-100f\n",NSGPA);
                break;
            case 4:
                fseek(fpc,byte_offset,SEEK_SET);
                printf("enter new CGPA: ");
                double NCGPA;
                scanf("%lf",&NCGPA);
                getchar();
                student[index].CGPA=NCGPA;
                fprintf(fpc,"%-100f\n",NCGPA);
                break;
            case 5:
                goto next;// to update as many students as u need using just one update function call
                break;
            case 6:
                break;
            default:
                printf("invalid input!\ntry Again");
            }
        }
    }

    fclose(fpn);
    fclose(fpd);
    fclose(fps);
    fclose(fpc);
}
void Delete(struct Student student[]){
    FILE *fpn = fopen("name.txt","r+");
    FILE *fpd = fopen("department.txt","r+");
    FILE *fps = fopen("SGPA.txt","r+");
    FILE *fpc = fopen("CGPA.txt","r+");
    FILE *ftempn = fopen("tempn.txt","w");
    FILE *ftempd = fopen("tempd.txt","w");
    FILE *ftemps = fopen("temps.txt","w");
    FILE *ftempc = fopen("tempc.txt","w");

    if (fpn == NULL || fpd == NULL || fps == NULL || fpc == NULL) {
        printf("No database found! Please CREATE a student first.\n");
        if (fpn) fclose(fpn);
        if (fpd) fclose(fpd);
        if (fps) fclose(fps);
        if (fpc) fclose(fpc);
        if (ftempn) fclose(ftempn);
        if (ftempd) fclose(ftempd);
        if (ftemps) fclose(ftemps);
        if (ftempc) fclose(ftempc);
        
        return;
    }
    int bytes_per_line=101;
    int byte_offset=0;
    char ch=' ';

    printf("enter student name to be deleted :");
    char Dname[100],n[100],d[100];
    fgets(Dname,100,stdin);
    Dname[strcspn(Dname, "\n")] = '\0';
    int index=-1;
    for (int i=0;i<counter ;i++){
        if (strcmp(Dname,student[i].name)==0){
            index=i;
            byte_offset=(index)*bytes_per_line;
            printf("student found !");
        }
    }
    if (index==-1){
        printf("student not found!");
        fclose(ftempn); fclose(ftempd); fclose(ftemps); fclose(ftempc);
        fclose(fpn); fclose(fpd); fclose(fps); fclose(fpc);
        remove("tempn.txt"); remove("tempd.txt"); remove("temps.txt"); remove("tempc.txt");
        return;
    }
    else{
        char bufferN[105], bufferD[105], bufferS[105], bufferC[105];
        int current_line = 0;


        while (fgets(bufferN, sizeof(bufferN), fpn) != NULL &&
               fgets(bufferD, sizeof(bufferD), fpd) != NULL &&
               fgets(bufferS, sizeof(bufferS), fps) != NULL &&
               fgets(bufferC, sizeof(bufferC), fpc) != NULL) {// Read all 4 files line-by-line simultaneously
            
            if (current_line != index) {
                fprintf(ftempn, "%s", bufferN);
                fprintf(ftempd, "%s", bufferD);
                fprintf(ftemps, "%s", bufferS);
                fprintf(ftempc, "%s", bufferC);
            }
        current_line++;
        }
    }
    fclose(ftempn);
    fclose(ftempd);
    fclose(ftemps);
    fclose(ftempc);
    fclose(fpn);
    fclose(fpd);
    fclose(fps);
    fclose(fpc);//closing files before removing or renaming them

    remove("name.txt");
    remove("department.txt");
    remove("SGPA.txt");
    remove("CGPA.txt");

    rename("tempn.txt", "name.txt");
    rename("tempd.txt", "department.txt");
    rename("temps.txt", "SGPA.txt");
    rename("tempc.txt", "CGPA.txt");

    for (int i = index; i < (counter - 1); i++) {
        student[i] = student[i + 1];
    }

    struct Student clear = {0};
    student[counter - 1] = clear;
    counter--;

}
void Load(struct Student student[]) {
    FILE *fpn = fopen("name.txt", "r");
    FILE *fpd = fopen("department.txt", "r");
    FILE *fps = fopen("SGPA.txt", "r");
    FILE *fpc = fopen("CGPA.txt", "r");
    
    if (fpn == NULL || fpd == NULL || fps == NULL || fpc == NULL) {
        if (fpn) fclose(fpn);
        if (fpd) fclose(fpd);
        if (fps) fclose(fps);
        if (fpc) fclose(fpc);
        return; 
    }

    char bufferN[105], bufferD[105];
    
    while (fgets(bufferN, sizeof(bufferN), fpn) != NULL &&
           fgets(bufferD, sizeof(bufferD), fpd) != NULL &&
           fscanf(fps, "%lf", &student[counter].SGPA) == 1 &&
           fscanf(fpc, "%lf", &student[counter].CGPA) == 1) {
            
        //Strip the \n from the end of the loaded line
        bufferN[strcspn(bufferN, "\n")] = '\0';
        bufferD[strcspn(bufferD, "\n")] = '\0';

        //Manually trim the trailing spaces so multi-word names work
        int lenN = strlen(bufferN);
        while (lenN > 0 && bufferN[lenN - 1] == ' ') {
            bufferN[lenN - 1] = '\0';
            lenN--;
        }

        int lenD = strlen(bufferD);
        while (lenD > 0 && bufferD[lenD - 1] == ' ') {
            bufferD[lenD - 1] = '\0';
            lenD--;
        }

        // Copy the perfectly clean strings into the struct
        strcpy(student[counter].name, bufferN); 
        strcpy(student[counter].department, bufferD);
        
        counter++;
    }
    
    fclose(fpn);
    fclose(fpd);
    fclose(fps);
    fclose(fpc);
}
int main(void){
    struct Student student[100];
    Load(student);
    int in=0;
    int choice;
    while(in!=5){
        printf("1.CREATE\n2.READ\n3.UPDATE\n4.DELETE\n5.EXIT\n");
        printf("enter your choice:");
        scanf("%d",&choice);
        getchar();
        in=choice;
        switch(choice){
            case 1:
                Create(student);
                break;
            case 2:
                Read(student);
                break;
            case 3:
                Update(student);
                break;
            case 4:
                Delete(student);
                break;
            case 5:
                printf("Exiting!!\n");
                break;
            default:
                printf("invalid input try again\n");
                break;
        }
    }

}