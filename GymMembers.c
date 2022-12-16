#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define DATE_STRING_LENGHT 32

int main();
FILE *fp, *ft;
struct gym{
	int id;
	char nama[20];
	char alamat[30];
	char membersince[30];
;}; struct gym mbr;

int checkid(int ids){
    rewind(fp);
    while(fread(&mbr,sizeof(mbr),1,fp)==1)
        if(mbr.id==ids)
            return 0;
    return 1;
}
int getdata(){
    int ids;
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    puts("Silahkan isi data dibawah ini\n");
    printf("ID\t: "); 
    scanf("%6d",&ids); 
    while(getchar()!='\n');
    if(ids>=100000&&ids<1000000){ 
        if(checkid(ids)==0){
            printf("\nID sudah terdaftar, silahkan daftarkan ID yang lain. "); getch(); 
            main();
        }
        mbr.id=ids;
        printf("Nama    : "); 
        scanf("%[^\n]",mbr.nama);
        printf("Alamat  : "); 
        scanf("%s",mbr.alamat); 
        printf("\nKamu terdaftar sebagai Member Gym Sunib tertanggal %d/%d/%d.\n", local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);
        strftime(mbr.membersince, sizeof(mbr.membersince), "%d-%m-%Y-", local_time);
        return 1;
    }
    else{ 
        printf("\nID harus teridiri dari 6 angka! "); getch();
        main();
    }
}
void regist(){ system("cls");
    fp=fopen("gymzzs.txt","a+");
    if(getdata()==1){
        fseek(fp,0,SEEK_END);
        fwrite(&mbr, sizeof(mbr),1,fp);
        fclose(fp);
        printf("\nData kamu sudah tersimpan. "); getch(); 
        main();
    }
}
void list(){system("cls");
    fp = fopen("gymzzs.txt", "r");
    if (fp == NULL){
        printf("Belum ada member yang terdaftar. "); getch(); 
        main();        
    }
    static struct tm *currentTime;
    time_t now = time(NULL);
    currentTime = localtime(&now);
    char *date;
    date = malloc(DATE_STRING_LENGHT);
    now = time(NULL);
    system("cls");
    puts("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd MEMBER LIST \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
    printf("\n   %-15s%-20s%-20s%-20s", "ID", "NAMA", "ALAMAT", "MEMBER SINCE");
    while (fread(&mbr, sizeof(mbr), 1, fp) == 1) {
        strftime(date, DATE_STRING_LENGHT, "%d-%m-%Y", currentTime);
        strcpy(mbr.membersince, date);
        printf("\n %-18d%-20s%-20s%-17s", mbr.id, mbr.nama, mbr.alamat, mbr.membersince);
    }
    fclose(fp);
    free(date);
    printf("\n\nSilahkan kembali ke menu utama."); getch(); 
    main();
}
void delete(){ system("cls");
    int d;
    char hapus='y';
    fp=fopen("gymzzs.txt","r+");
    if (fp == NULL){
        printf("Belum ada member yang terdaftar. ");getch(); 
        main();        
    }
    printf("Masukkan ID yang ingin dihapus: ");
    scanf("%d",&d);
    rewind(fp);
    while(fread(&mbr,sizeof(mbr),1,fp)==1){
        if(mbr.id==d){
            printf("\nID terdaftar atas nama %s.",mbr.nama);
            hapus='t';
        }
    }
    if(hapus=='t'){
        printf("\n\nApakah kamu yakin ingin berhenti berlangganan? (Y/T)");
        if(getch()=='y'){
            ft=fopen("dlt.txt","w+");
            rewind(fp);
            while(fread(&mbr,sizeof(mbr),1,fp)==1){
                if(mbr.id!=d){
                    fseek(ft,0,SEEK_CUR);
                    fwrite(&mbr,sizeof(mbr),1,ft);
                }
            }
            fclose(ft); fclose(fp);
            remove("gymzzs.txt");
            rename("dlt.txt","gymzzs.txt");
            fp=fopen("gymzzs.txt","r+");
            if(hapus=='t'){
                printf("\n\nID kamu berhasil dihapus."); getch(); 
                main();
            }
        }
    }
    else{ 
        printf("ID tidak terdaftar! "); getch(); 
        main();
    }
}
int main(){system("cls");
    puts("Selamat Datang di Sunib Gym\n");
    puts("[1] Daftar Membership");
    puts("[2] List Member");
    puts("[3] Berhenti jadi Membership");
    puts("[4] Keluar");
    printf("\nSilahkan pilih menu : ");
    switch(getch()){
        case '1': 
            regist();
            break;

        case '2': 
            list();
            break;

        case '3': 
            delete();
            break;

        case '4': 
            puts("\n\nTerimakasih sudah menggunakan Aplikasi Sunib Gym");
            exit(1);
            break;

        default : 
            printf("Invalid Input!"); 
            if(getch())
                main();
    }
}