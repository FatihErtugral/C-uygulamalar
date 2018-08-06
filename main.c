/**       
 *  Title: Hatalı Çarpma İşlemi Yapan Program
 *  Author: Fatih Ertuğral.
 *  Created on Aug 4, 2018, 10:50 PM
 * 
 *  Arkadaşlar yapacağımız hatalı bir çarpma işlemi olacak.
 *  Hatası çarpma işlemini yaparken bir birim sola kaymaması,
 *  toplarken de eldeyi hesaba katmaması olacak.
 *
 *    Örnek :
 *
 *    ►Hatalı Çözüm                      ►Doğru Çözüm
 *
 *          624                                 624
 *           38                                  38
 *      x—————–                            x——————-
 *         4992                                4992
 *         1872                                1872
 *      +—————–                            +——————-
 *         5764                               23712
 *   
 *       
 *      ◘ TOPLAMA ALGORİTMAMIZIN ÇALIŞMA ADIMLARI ◘
 *      • iki dizideki rakamların, birler basamağını bul
 *      • Bulunan birler basamağındaki rakamları topla. Örn: 8 + 9 = 17
 *      • Elde edilen sonucunda birler basamağını al. Örn: 17 %10 = 7
 *      • Elde edilen sonucu, bulunduğun basamağın katıyla çarp. Örn: 7 * 1 = 7
 *      • Değeri "sonuc" değişkenine kayıt et.
 *      • İki dizideki rakamında birler basamağından kurtul.           
 *      • Örn: d[0]:128 -> d[0]:12    |     d[1]:459 -> d[1]:45
 *      • Yukardaki işlem döngü sayesinde devam eder fakat bir ayrıntı var onluKat sayısı 10 konumunda.
 *      • "sonuc" değişkeni içinde 7 değeri mevcuttu
 *      • (2 + 5)%10*10 = 70
 *      • sonuc = 7 + 70 = 77;
 *      • İşlemlerimiz böyle katlanarak devam eder.
 *      • "off" değişkeni büyük sayının basamak değerini tutar, bu sayede basamak sayısı kadar katlama yapılır.
 *      • "boyut" sayesinde bütün dizideki sayılar, özyineli olarak toplanır.
 *      • Bulunan sonuc d[0] indisine kayıt edilir ve geri değer olarak döndürülür.
 *      
 *
 *      ■ Konsoldan girişlerin numaratik olup olmadığı kontroledilmiştir.
 * 
 *      ■ Maximum işlem kapasitesi
 *          
 *          9,999,999,999
 *          9,999,999,999
 *        x________________
 **/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void        HataliCarp(long long *carpim, long long *carpan);
long long   NumaratikGiris(int size, char *mesaj);
/**********************************************************************************/
int main()
{
    system("color 011");
    long long s1 = NumaratikGiris(10, "Ilk sayiyi giriniz: ");  // maximum kabul edilecek basamak sayisiyle ilk mesaj belirtilir.
    long long s2 = NumaratikGiris(10, "Ikinci sayiyi giriniz: ");
    HataliCarp(&s1, &s2);
    getchar();
    return (EXIT_SUCCESS);
}
/**********************************************************************************/
int sBasamak(long long x) //> Verilen rakamın kaç basamaklı olduğunu geri döndürür.
{
    int i = 1;
    while (x > 9)
    {
        x = (x - x % 10) / 10;
        i++;
    }
    return i;
}
/**********************************************************************************/
long long toplaDizi(long long *d, int boyut) // Açıklama üst kısımda.
{
    long long onluKat = 1, sonuc = 0;
    int off = sBasamak(d[0]);
    --boyut;
    while (boyut != 0)
    {
        if (d[0] < d[boyut]) //> Amaç büyük sayıyı, 0. indise yerleştirmek formülümüz için.
        {
            long long temp = d[0];
            d[0] = d[boyut];
            d[boyut] = temp;
            off = sBasamak(d[0]);
        }
        sonuc += (d[0] % 10 + d[boyut] % 10) % 10 * onluKat;
        d[0] = (d[0] - (d[0] % 10)) / 10;
        d[boyut] = (d[boyut] - (d[boyut] % 10)) / 10;
        onluKat *= 10;
        off--;
        if (off == 0) //> Özyineleme işlemi
        {
            onluKat = 1;
            d[0] = sonuc;
            sonuc = 0;
            boyut--;
            off = sBasamak(d[0]);
        }
    }
    return d[0];
}
/**********************************************************************************/
void HataliCarp(long long *carpim, long long *carpan)
{
    long long sBuyuk = *carpan > *carpim ? *carpan : *carpim; //> Buyuk sayiyi tespit et
    long long sKucuk = *carpan < *carpim ? *carpan : *carpim; //> Kucuk Sayiyi tespit et
    int boyut = sBasamak(sKucuk);                             //> Carpilacak en düşük değer
    long long *dizi = (long long *)malloc(sizeof(long long) * boyut); //> En düşük değer kadar dizi oluştur.
    
    printf("\n\n%20lld\n", *carpim);
    printf("%20lld\n", *carpan);
    printf("%20s\n", "x____________");
    for (int i = boyut - 1; i > -1; i--)
    {
        dizi[i] = sBuyuk * (sKucuk % 10);
        sKucuk = (sKucuk - sKucuk % 10) / 10;
        printf("%20lld\n", dizi[i]);
    }
    printf("%20s\n", "+____________");
    printf("%20lld\n", toplaDizi(dizi, boyut));
}
/**********************************************************************************/
long long NumaratikGiris(int size, char *mesaj){
    long long rvalue;
    char *giris;
    int flag;
    
    do
    {
        flag = 0;
        giris = (char *)malloc(sizeof(char) * (size+1));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        printf("%s", mesaj);
        fgets(giris, (size+1), stdin);
        fflush(stdin);
        for(int i=0; size > i && giris[0] != '\0' && giris[i] != '\n'; i++)
        {
            if(giris[i] >= 48 && giris[i] <= 57)
                ;
            else
            {
                flag = 1; 
                break;
            }
        }
        if(flag == 1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            printf("UYARI: Lutfen 0 ile 9 arasinda rakamlar kullaniniz!\n");
            printf("UYARI: Giridiniz sayi en fazla %d basamakli olabilir!\n\n", size);
            free(giris); fflush(stdin);
        }
    }while(flag == 1);
    rvalue = atoll(giris);
    return rvalue;
}