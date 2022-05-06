#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//nama maksimal 16 karakter
//judul maksimal 28 karakter
//kategori maksimal 11 karakter
struct input{
  int tgl;
  int bln;
  int thn;
	char nama[50];
  int kategori;
  int judul;
  int jumlah;
	int harga;
	int total;
}data;

struct dataInput{ //struct untuk ngambil input dari data.txt
	char kategori[50];
	char judul[30];
	int harga;
};

struct bacaRecord{
	int tgl;
  int bln;
  int thn;
	char nama[17];
  char kategori[12];
  char judul[29];
  int jumlah;
	int harga;
	int total;
};

void sortInput(int baris, struct dataInput input[]){//sorting inputan data.txt
	for(int i=0; i<baris-1; i++){ 
		for(int j=i+1; j<baris; j++){
			if(strcmp(input[i].kategori,input[j].kategori)>0){ //sorting ketegori
				struct dataInput swap;
				swap = input[i];
				input[i] = input[j];
				input[j] = swap;
			}
			if((strcmp(input[i].kategori,input[j].kategori)==0)&&(strcmp(input[i].judul, input[j].judul)>0)){ //sorting judul
				struct dataInput swap;
				swap = input[i];
				input[i] = input[j];
				input[j] = swap;
			}
		}
	}
}

int main(){ //PROGRAM UTAMA
  int flag=1; //sentinel pengulangan program	
  while(flag==1){
		int pilih;
    printf("\n==================== PROGRAM TICKETING ====================\n\n");
    printf("1. Tambah record penjualan\n");
    printf("2. Record penjualan terurut berdasarkan tanggal\n");
    printf("3. Record penjualan terurut berdasarkan penjualan terbanyak\n");
    printf("4. Keluar\n");
		int pilihBenar = 1; //sentinel pengulangan piihan menu
		while(pilihBenar == 1){
			printf("\nPilih[1/2/3/4] : ");
			scanf("%d",&pilih);
			if(pilih < 1 || pilih > 4){
				printf("Mohon masukkan pilihan menu yang benar!\n");
			}
			else{
				pilihBenar = 0;
			}
		}
    system("clear");
		switch(pilih){
			case 1 : { //INPUT DATA
			  printf("1. Tambah record penjualan\n");
				
				int ulangInput = 1;//sentinel untuk mengulangi input
				while(ulangInput == 1){
					FILE *fp;
					fp=fopen("sales.txt","a"); //file pointer sales.txt
					FILE *fdata;
					fdata=fopen("data.txt", "r"); //file pointer data.txt
					int baris = 0;
					struct dataInput input[1001];
					while(!(feof(fdata))){ //membaca data.txt
						fscanf(fdata,"%[^#]#%[^#]#%d\n", &*input[baris].kategori, &*input[baris].judul, &input[baris].harga);
						baris++;
					}
					sortInput(baris, input);

					struct dataInput inputClone[baris];
					
					for(int i=0; i<baris; i++) inputClone[i] = input[i];//membuat kloningan 
					int tglBenar = 1;
					while(tglBenar == 1){
						printf("Masukkan tanggal pembelian [dd/mm/yyyy] = ");
						scanf("%d/%d/%d", &data.tgl, &data.bln, &data.thn); //menerima tanggal pembeli
						if(data.tgl>30 || data.tgl < 1 || data.bln > 12 || data.bln < 1 || data.thn > 2100 || data.thn < 2000){
							printf("Mohon masukkan tanggal yang benar!\n");
							printf("Batasan tanggal pembelian:\ndd = 1-30\nmm = 1-12\nyyyy = 2000-2100\n");
						}
						else{
							tglBenar = 0;
						}
					}
					int namaBenar = 1;
					while( namaBenar ==1){
						printf("Masukkan nama = "); getchar();
						scanf("%[^\n]", &*data.nama); //menerima nama
						int panjangNamaMaksimal = strlen(data.nama);
						if(panjangNamaMaksimal >16){
							printf("Maksimal 15 karakter bambank!!!!\n");
						}
						else{
							namaBenar = 0;
						}
					}
					
						
					for(int i=0; i<baris-1; i++){ //mencari duplikat kategori
						for(int j=i+1; j<baris; j++){
							if(strcmp(inputClone[i].kategori,"-")==0) continue;
							else{
								if(strcmp(inputClone[i].kategori,inputClone[j].kategori)==0){ //mengganti duplikat kategori dengan "-"
									strcpy(inputClone[j].kategori, "-");
								}
							}
						}
					}

					int jumlahKategori=0;
					for(int i=0; i<baris; i++){ //menghitung jumlah kategori
						if(strcmp(inputClone[i].kategori,"-")!=0){
							jumlahKategori++;
						}
					}

					char kategori[jumlahKategori][50]; // array char untuk menyimpan kategori
					int z=0;
					for(int i=0; i<baris;i++){ //membuat kategori
						if(strcmp(inputClone[i].kategori, "-")!=0){
							strcpy(kategori[z],inputClone[i].kategori);
							z++;
						}
					}

					printf("Berikut kategori tiket yang tersedia\n");
					for(int i=0; i<jumlahKategori; i++) printf("%d.%s\n", i+1, kategori[i]);//menampilkan kategori
					
					int kategoriBenar = 1; //sentinel untuk pengisian nomor kateogori tidak benar
					while(kategoriBenar == 1){
						printf("Masukkan nomor kategori = ");
						scanf("%d", &data.kategori); //menerima pilihan kategori
						data.kategori -= 1;
						if(data.kategori<0 || data.kategori > jumlahKategori-1){
							printf("Mohon masukkan nomor kategori yang benar!\n");
						}
						else{
							kategoriBenar = 0;
						}
					}

					int jumlahJudul=0;
					for(int i=0; i<baris; i++){ //menghitung banyaknya judul dengan kategori yang sama
						if(strcmp(input[i].kategori,kategori[data.kategori])==0) jumlahJudul++;
					}

					struct dataInput judul[jumlahJudul]; //struct untuk menyimpan judul dengan kategori yang sama
					z=0;
					for(int i=0; i<baris;i++){ //membuat list judul dengan kategori yang sama
						if(strcmp(input[i].kategori,kategori[data.kategori])==0){
							judul[z] = input[i];
							z++;
						}
					}

					printf("Berikut list dari kategori %s\n", kategori[data.kategori]);
					for(int i=0; i<jumlahJudul; i++) printf("%d. %s @Rp.%d\n", i+1, judul[i].judul, judul[i].harga); //menampilkan judul dengan kategori yang sama
					
					int tiketBenar = 1; //sentinel apabila pengisian nomor judul tidak benar
					while(tiketBenar == 1){
						printf("Masukkan nomor tiket pilihan = ");
						scanf("%d", &data.judul); //menerima pilihan judul
						data.judul -= 1;
						if(data.judul < 0 || data.judul > jumlahJudul-1) printf("Mohon masukkan nomor judul yang benar!\n");
						else tiketBenar = 0;
					}
						
					printf("%s @Rp.%d\n", judul[data.judul].judul, judul[data.judul].harga );
					printf("Masukkan jumlah tiket = ");
					scanf("%d", &data.jumlah); //menerima jumlah tiket
					data.harga = judul[data.judul].harga; //menerima harga
					data.total = data.harga * data.jumlah; //menghitung biaya total
					printf("Total = %d\n", data.total);
					fprintf(fp, "%d/%d/%d#%s#%s#%s#%d#%d#%d\n", data.tgl, data.bln, data.thn, data.nama, kategori[data.kategori], judul[data.judul].judul, data.jumlah, data.harga, data.total);

					printf("Apakah ingin menambahkan data penjualan lagi?\n1.Ya\n2.Tidak\n[1/2] = ");
					scanf("%d", &ulangInput);
					fclose(fdata);
					fclose(fp);
					system("clear");
				}
				
				break;
			}
			case 2 : { //sort berdasarkan tanggal
				FILE *fp;
        fp=fopen("sales.txt","r");
        int n=0;
        struct bacaRecord st[1001];
				struct bacaRecord temp;
				int pilihUrutan;
				printf("2. Record penjualan berdasarkan tanggal transaksi :\n");
        printf("1.Terbaru\n2.Terlama\n");
				int urutanBenar = 1;
				while(urutanBenar == 1){ //sentinel untuk memasukkan pilihan yang benar
					printf("Pilihan[1/2] = ");
        	scanf("%d",&pilihUrutan);
					if(pilihUrutan<1||pilihUrutan>2)printf("Mohon masukkan nomor yang benar!\n");
					else urutanBenar = 0;
				}
				system("clear");
        while(!(feof(fp))){
          fscanf(fp,"%d/%d/%d#%[^#]#%[^#]#%[^#]#%d#%d#%d\n", &st[n].tgl, &st[n].bln, &st[n].thn, &*st[n].nama, &*st[n].kategori, &*st[n].judul, &st[n].jumlah, &st[n].harga, &st[n].total);
          n++;
        }
        if(pilihUrutan==1){
					printf("Data terurut berdasarkan tanggal terbaru:\n");
					for(int i=0;i<n-1;i++) { //descending
						for(int j=0;j<n-1-i;j++) {
							if(st[j].thn < st[j+1].thn) {
								temp=st[j];
								st[j]=st[j+1];
								st[j+1]=temp;
							}
							else if(st[j].thn==st[j+1].thn && st[j].bln < st[j+1].bln){
								temp=st[j];
								st[j]=st[j+1];
								st[j+1]=temp;
							}
							else if(st[j].thn==st[j+1].thn && st[j].bln==st[j+1].bln && st[j].tgl < st[j+1].tgl){
								temp=st[j];
								st[j]=st[j+1];
								st[j+1]=temp;
							}
						}
					}
        }
        else if(pilihUrutan==2){
					printf("Data terurut berdasarkan tanggal terlama:\n");
					for(int i=0;i<n-1;i++) { //ascending
						for(int j=0;j<n-1-i;j++) {
							if(st[j].thn > st[j+1].thn) {
								temp=st[j];
								st[j]=st[j+1];
								st[j+1]=temp;
							}
							else if(st[j].thn==st[j+1].thn && st[j].bln > st[j+1].bln){
								temp=st[j];
								st[j]=st[j+1];
								st[j+1]=temp;
								}
							else if(st[j].thn==st[j+1].thn && st[j].bln==st[j+1].bln && st[j].tgl > st[j+1].tgl){
								temp=st[j];
								st[j]=st[j+1];
								st[j+1]=temp;
							}
						}
					}
        }
        
        printf("Tanggal\t\tNama\t\t\tKategori\tJudul\t\t\t\t\t\tJumlah\t\tHarga\t\t\tTotal\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
        for(int i=0;i<n;i++){
          printf("%d/%d/%d\t",st[i].tgl, st[i].bln, st[i].thn);
					int pjgNama = strlen(st[i].nama); 
					if(pjgNama<8)printf("%s\t\t\t", st[i].nama);
					else if(pjgNama>=8 && pjgNama<13)printf("%s\t\t", st[i].nama);
          else printf("%s\t",st[i].nama);
					
					int pjgKategori = strlen(st[i].kategori);
					if(pjgKategori<8) printf("%s\t\t",st[i].kategori); //hitung jumlah karakter
          else if(pjgKategori>=8)printf("%s\t",st[i].kategori);
          
					int pjgJudul = strlen(st[i].judul);
					if(pjgJudul<12) printf("%s\t\t\t\t\t",st[i].judul);
          else if(pjgJudul>=12 && pjgJudul<16)printf("%s\t\t\t\t",st[i].judul);
					else if(pjgJudul>=16 && pjgJudul<20)printf("%s\t\t\t",st[i].judul);
          else if(pjgJudul>=20 && pjgJudul<24)printf("%s\t\t",st[i].judul);
          else printf("%s\t",st[i].judul);
          
					printf("%d\t\t\tRp.%d\t\tRp.%d\n", st[i].jumlah, st[i].harga, st[i].total); 
        }

				int total = 0;
				for(int i=0; i<n; i++){
					total += st[i].total;
				}
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tTotal Pendapatan : Rp.%d\n", total);
				printf("---------------------------------------------------------------------------------------------------------\n");

        fclose(fp);
				printf("\nKlik ENTER untuk kembali ke menu\n"); getchar(); getchar();
				system("clear");
			  break;
			}
			case 3 : { //sort berdasarkan produk dengan pembelian terbanyak
        printf("3. Tampilan sort penjualan terbanyak\n");
				FILE *fp;
        fp=fopen("sales.txt","r");
        int n=0;
        struct bacaRecord st[1001];
        while(!(feof(fp))){
          fscanf(fp,"%d/%d/%d#%[^#]#%[^#]#%[^#]#%d#%d#%d\n", &st[n].tgl, &st[n].bln, &st[n].thn, &*st[n].nama, &*st[n].kategori, &*st[n].judul, &st[n].jumlah, &st[n].harga, &st[n].total);
          n++;
        }
				struct bacaRecord temp;
				for(int i=0;i<n-1;i++) {//descending
					for (int j=0;j<n-1;j++) {
						if(st[j].jumlah < st[j+1].jumlah) {
							temp = st[j];
							st[j] = st[j+1];
							st[j+1] = temp;
						}
					}
				}

				printf("Data tersorting berdasarkan penjualan:\n");
        printf("Tanggal\t\tNama\t\t\tKategori\tJudul\t\t\t\t\t\tJumlah\t\tHarga\t\t\tTotal\n");
				printf("----------------------------------------------------------------------------------------------------------\n");
        for(int i=0;i<n;i++){
          printf("%d/%d/%d\t",st[i].tgl, st[i].bln, st[i].thn);
					int pjgNama = strlen(st[i].nama); 
					if(pjgNama<8)printf("%s\t\t\t", st[i].nama);
					else if(pjgNama>=8 && pjgNama<13)printf("%s\t\t", st[i].nama);
          else printf("%s\t",st[i].nama);
					
					int pjgKategori = strlen(st[i].kategori);
					if(pjgKategori<8) printf("%s\t\t",st[i].kategori); //hitung jumlah karakter
          else if(pjgKategori>=8)printf("%s\t",st[i].kategori);
          
					int pjgJudul = strlen(st[i].judul);
					if(pjgJudul<12) printf("%s\t\t\t\t\t",st[i].judul);
          else if(pjgJudul>=12 && pjgJudul<16)printf("%s\t\t\t\t",st[i].judul);
					else if(pjgJudul>=16 && pjgJudul<20)printf("%s\t\t\t",st[i].judul);
          else if(pjgJudul>=20 && pjgJudul<24)printf("%s\t\t",st[i].judul);
          else printf("%s\t",st[i].judul);
          
					printf("%d\t\t\tRp.%d\t\tRp.%d\n", st[i].jumlah, st[i].harga, st[i].total); 
				}
        
        int total = 0;
				for(int i=0; i<n; i++){
					total += st[i].total;
				}
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tTotal Pendapatan : Rp.%d\n", total);
				printf("---------------------------------------------------------------------------------------------------------\n");
				fclose(fp);
				printf("\nKlik ENTER untuk kembali ke menu\n"); getchar(); getchar();
				system("clear");
				break;
			}
			case 4 : {
				flag=0;//disini dia off gitu
				system("clear");
				printf("Terima kasih telah menggunakan program kami!\n");
				break;
			}
		}
  }
  return 0;
}