#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#pragma pack(push, 1) //zmuszenie kompilatora do nie dopisywania pustych bajtów
struct FileHeader {  //informacje o pliku
    short bfType;  
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
};
 
struct PictureHeader { //informacje o obrazie
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    char biClrImportant;
    char biClrRotation;
};
 
struct KoloryRGB {
    unsigned char R;
    unsigned char G;
    unsigned char B;
    };
#pragma pack(pop)

int menu(int numer);

int main() {
	
	ifstream plik("11.bmp", ios::binary);
	ofstream kopia("kopia.bmp", ios::binary);
	
	if(!plik) { //sprawdzenie, czy plik zosta³ otwarty
 		cout << "Plik nie zostal otwarty\n";
	} 
	cout<<"Plik wczytany"<<endl;
	
	char* wsk = new char[sizeof(FileHeader)];  
	plik.read(wsk, 14);  //pierwsze 14bajtów to informacje o pliku
	FileHeader* info = (FileHeader*)(wsk);
	kopia.write(wsk, 14);
	
	//cout<<hex<<setw(4)<<info->bfType;
	//cout<<dec<<setw(4)<<info->bfSize;
	//cout<<dec<<setw(4)<<info->bfReserved1;
	//cout<<dec<<setw(4)<<info->bfReserved2;
	//cout<<dec<<setw(4)<<info->bfOffBits<<endl;
	
	plik.seekg(14, ios::beg);  //od 14bajtu zaczynaja sie informacje o obrazie
	
	wsk = new char[sizeof(PictureHeader)];
 	plik.read(wsk, 40);  
 	PictureHeader* obraz = (PictureHeader*)(wsk);
 	kopia.write(wsk, 40);
 	
 	//cout<<"Wczytano "<< plik.gcount()<<" bajtow"<<endl<<endl;
 	
	//cout<<dec<<obraz->biSize<<endl;
	//cout<<dec<<obraz->biWidth<<endl;
	//cout<<dec<<obraz->biHeight<<endl;
	//cout<<dec<<obraz->biPlanes<<endl;
	//cout<<dec<<obraz->biBitCount<<endl;
	//cout<<dec<<obraz->biCompression<<endl;
	//cout<<dec<<obraz->biSizeImage<<endl;
	//cout<<dec<<obraz->biXPelsPerMeter<<endl;
	//cout<<dec<<obraz->biYPelsPerMeter<<endl;
	//cout<<dec<<obraz->biClrUsed<<endl;
	//cout<<dec<<obraz->biClrImportant<<endl;
	
	KoloryRGB** 
	kolor = new KoloryRGB*[obraz->biHeight];
	
	int numer;
	numer = menu(numer);
	
	switch(numer) {
		case 1: 
		plik.seekg(info->bfOffBits, ios::beg); // bfOffBits wskazuje pocz¹tek danych obrazka
				for(int i=0; i<obraz->biHeight; i++)
    			{
        			kolor[i] = new KoloryRGB [obraz->biWidth];

        			for(int j = 0; j < obraz->biWidth; j++)
        			{
        				wsk = new char[3];    	
            			plik.read(wsk,3);

            			kolor[i][j].B = wsk[0];
            			kolor[i][j].G = wsk[1];
            			kolor[i][j].R = wsk[2];
            
            			char c = (kolor[i][j].R+kolor[i][j].G+kolor[i][j].B)/3;
            		//cout<<(int)c<<endl;
            
            			char* b = new char[3];  
        				b[0]=c; b[1]=c; b[2]=c;
        	
        				kopia.write(b, 3);

        			}
    			}
				break;
				
		case 2: 	
		plik.seekg(info->bfOffBits, ios::beg); 
	
		char wybor;
    	cout<<"wybierz kolor: ";
    	cin >> wybor; 
	 	
 		for(int i=0; i<obraz->biHeight; i++)
    	{
        	kolor[i] = new KoloryRGB [obraz->biWidth];

        	for(int j = 0; j < obraz->biWidth; j++)
        	{
        		wsk = new char[3];    	
            	plik.read(wsk,3);

            	kolor[i][j].B = wsk[0];
            	kolor[i][j].G = wsk[1];
            	kolor[i][j].R = wsk[2];
            
            	char c = 0;
            
            	char* b = new char[3]; 
            
            	if(wybor == 'b') {
            		b[0]=wsk[0]; 
					b[1]=c; 
					b[2]=c;
				}
        		if(wybor == 'g') {
            		b[0]=c; 
					b[1]=wsk[1]; 
					b[2]=c;
				}
				if(wybor == 'r') {
            		b[0]=c; 
					b[1]=c; 
					b[2]=wsk[2];
				}
        	
        		kopia.write(b, 3);

        	}
    	}
		break;
		
		case 3: 
		plik.seekg(info->bfOffBits, ios::beg);
			for(int i=0; i<obraz->biHeight; i++)
    		{
        		kolor[i] = new KoloryRGB [obraz->biWidth];

        		for(int j = 0; j < obraz->biWidth; j++)
        		{
        			wsk = new char[3];    	
            		plik.read(wsk,3);

            		kolor[i][j].B = wsk[0];
            		kolor[i][j].G = wsk[1];
            		kolor[i][j].R = wsk[2];
            
            		char cg = (kolor[i][j].G+kolor[i][j-1].G+kolor[i][j+1].G+kolor[i][j-2].G+kolor[i][j+2].G+kolor[i][j-3].G+kolor[i][j+3].G+kolor[i][j-4].G+kolor[i][j+4].G+kolor[i][j-5].G+kolor[i][j+5].G)/11;
     	
            		char cb = (kolor[i][j].B+kolor[i][j-1].B+kolor[i][j+1].B+kolor[i][j-2].B+kolor[i][j+2].B+kolor[i][j-3].B+kolor[i][j+3].B+kolor[i][j-4].B+kolor[i][j+4].B+kolor[i][j-5].B+kolor[i][j+5].B)/11;
     		
            		char cr = (kolor[i][j].R+kolor[i][j-1].R+kolor[i][j+1].R+kolor[i][j-2].R+kolor[i][j+2].R+kolor[i][j-3].R+kolor[i][j+3].R+kolor[i][j-4].R+kolor[i][j+4].R+kolor[i][j-5].R+kolor[i][j+5].R)/11;
        	
            		char c = (cg+cb+cr)/3;
            
            
            		char* b = new char[3];  
        			b[0]=cb; b[1]=cg; b[2]=cr;
        	
        			kopia.write(b, 3);
        		}
    		}
			break;
	}
	
    //for(int i = 0; i < obraz->biHeight; i++ )
       // for(int j = 0; j < obraz->biWidth; j++)
           // cout<<"r: "<<setw(3)<<(int)kolor[i][j].R<<"  g: "<<setw(3)<<(int)kolor[i][j].G<<"  b: "<<setw(3)<<(int)kolor[i][j].B<<endl;
	cout<<endl<<"Zobacz zmieniony obraz w kopia.bmp"<<endl;
	
	plik.close();
	kopia.close();
	
	return 0;
}

int menu(int numer) {
	cout<<"Menu"<<endl<<"1. czarno-biale"<<endl<<"2. kolor"<<endl<<"3. rozmazanie"<<endl;
	cout<<endl<<"wybierz numer:"<<endl; 
	cin>>numer;
	return numer;
}

