#include <iostream>
#include <fstream>
#include "bmplib.h"
#include "point.h"

using namespace std;

int readGS_BMP(char filename[], unsigned char image[][SIZE], BMPTYPE &type,  BMPFILEHEADER &fHeader, BITMAPHEADER &bmpHeader)
{
  int i,j;

  // Open the file for reading and ensure it opened successfully
  //  Print a message and return -1 if it fails
  ifstream ifile(filename);
  if( ! ifile.good() ){
    cerr << "Unable to open file: " << filename << endl;
    return -1;
  }
  // Read in the BMP file type
  ifile.read( reinterpret_cast<char *>(&type), sizeof(BMPTYPE) );

  // Check its the format we want
  if(type.signature[0] != 'B' && type.signature[1] != 'M'){
    cerr << "Not a BMP file" << endl;
    return -1;
  }
	
  // Read in the file header data into fHeader (BMPFILEHEADER)
  ifile.read( reinterpret_cast<char *>(&fHeader), sizeof(BMPFILEHEADER) );

  // Print out the file size in bytes and the byte offset to the pixel array
  //cout << "Size of the file: " << fHeader.fileSize << endl;
  //cout << "Pixel offset: " << fHeader.pixelOffset << endl;

  // Read in the data into the bmpHeader (BITMAPHEADER)
  ifile.read( reinterpret_cast<char *>(&bmpHeader), sizeof(BITMAPHEADER) );
  
  // Print out the dimensions (height x width) read in from the file header
  //cout << "Dimensions:  " << bmpHeader.height << "x" << bmpHeader.width << endl;
  // Print out the color depth (planes * bits_per_pixel) 
  //  read in from the file header
  //cout << "Color depth: " << bmpHeader.planes * bmpHeader.bpp << endl;

  // Seek to the point in the file where the pixel data starts
  ifile.seekg(fHeader.pixelOffset, ios::beg);

  // Ensure the SEEK (read) pointer of the FILE is now pointing at the
  // pixel array

  // Data is read in opposite order (it is stored backwards in the file)

for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
      ifile.read( reinterpret_cast<char *>(&image[SIZE-1-i][j]), sizeof(uint8));
	
    }
  }
  return 0;
}


int writeGS_BMP(char *filename, uint8 Image[][SIZE], BMPTYPE &type,  BMPFILEHEADER &fHeader, BITMAPHEADER &bmpHeader )
{
  ofstream ofile(filename);
  if(! ofile.good() ){
    cerr << "Can't open file: " << filename << endl;
    return -1;
  }

  fHeader.fileSize = SIZE*SIZE + sizeof(BMPTYPE) + sizeof(BMPFILEHEADER)
    + sizeof(BITMAPHEADER);
  fHeader.pixelOffset = sizeof(BMPTYPE) + sizeof(BMPFILEHEADER)
    + sizeof(BITMAPHEADER);
  bmpHeader.dibHeaderSize = sizeof(BITMAPHEADER);
  bmpHeader.colorTableSize = 256;
  bmpHeader.importantColor = 0;


  ofile.write( reinterpret_cast<char *>(&type), sizeof(BMPTYPE) );
  ofile.write( reinterpret_cast<char *>(&fHeader), sizeof(BMPFILEHEADER) );
  ofile.write( reinterpret_cast<char *>(&bmpHeader), sizeof(BITMAPHEADER) );

  // For bits_per_pixel <= 8 we have to write in the color table
  uint8 colorVal[4] = {0,0,0,0};
  for(int i=0; i < SIZE; i++){
    colorVal[0] = colorVal[1] = colorVal[2] = i;
    ofile.write( reinterpret_cast<char *>(colorVal), 4*sizeof(uint8) );
  }


  // Write the data in opposite order
  for(int i=0; i < SIZE; i++){
    for(int j=0; j < SIZE; j++){
      ofile.write( reinterpret_cast<char *>(&Image[SIZE-1-i][j]), sizeof(uint8) );
    }
  }

  ofile.close();
  return 0;
}
Character::Character(unsigned char (*myimage1)[256], int ulr, int ulc, int h, int w){
 	
	myimage=myimage1;	
	uplr=ulr;
	uplc=ulc;

	height=h;
	width=w;

}

int Character::retuplr(){
	return uplr;}

int Character::retuplc(){
	return uplc;}
int Character::reth(){
	return height;}
int Character::retw(){
	return width;}

void Character::get_bounding_box(int &sr, int &sc, int &er, int &ec){
		sr=uplr;
		sc=uplc;
		er=uplr+height;
		ec=uplc+width;
}

void Character::perform_tests(){
//horizontal symmertry

int middle=uplc+(width/2);
int numEqPx=0;
int lhs=uplc;
int rhs=uplc+width;
int u=0;

int numBlkPx=0;
while(rhs>middle){
	
	for(u=uplr;u<uplr+height+1;u++){
		if(myimage[u][lhs]==0 || myimage[u][rhs]==0){
		
			if(myimage[u][lhs]==myimage[u][rhs]){
			numEqPx+=2;
			numBlkPx+=2;}
			else
			numBlkPx++;
		
		}	
	}
lhs++;
rhs--;
}

horizontal=static_cast<double>(numEqPx)/(numBlkPx);
//end checking horizontal symmetry		

//Code for vertical symmetry
int middlever=uplr+(height/2);
numEqPx=0;
int uh=uplr;
int lh=uplr+height;
int v=0;

numBlkPx=0;
while(lh>middlever){
	for(v=uplc;v<uplc+width+1;v++){

	
		if(myimage[uh][v]==0 || myimage[lh][v]==0){
		//cout<<"hi"<<endl;
			if(myimage[uh][v]==myimage[lh][v]){
			numEqPx+=2;
			numBlkPx+=2;}
			else
			numBlkPx++;
		
		}
	}
uh++;
lh--;
}
vertical=static_cast<double>(numEqPx)/(numBlkPx);
//ending vertical symmetry

//code for euler
int count=0;
q1=0;q3=0;qd=0;q2=0;q4=0;q0=0;
	for(int i=uplr-1; i <= uplr+height + 1; i++){
		for(int j=uplc-1; j <= uplc + width + 1; j++){
			count=0;
			if(myimage[i][j]==0)
				count++;
			if(myimage[i][j+1]==0)
				count++;
			if(myimage[i+1][j]==0)
				count++;
			if(myimage[i+1][j+1]==0)
				count++;
	
			if(count==1)
				q1++;
			else if(count==3)
				q3++;
			else if(((myimage[i][j]==0 && myimage[i+1][j+1]==0) && (myimage[i][j+1]!=0 && myimage[i+1][j]!=0)) || 
((myimage[i][j+1]==0 && myimage[i+1][j]==0) && (myimage[i][j]!=0 && myimage[i+1][j+1]!=0)))
				qd++;
			else if(count==0)
				q0++;
			else if(count==2)
				q2++;
			else if(count==4)
				q4++;

		}
	}
	euler=(q1-q3-2*qd)/4;
//ending for euler

//Aspect Ratio
aspRat=static_cast<double>(height)/width;
//ascpect ratio ending

//horizontal centroid444

int isblack=1;
int horiCent_num=0;
int horiCent_den=0;

	for(int l=0;l<height;l++){
	
		for (int k=0;k<width;k++){

			if(myimage[uplr+l][uplc+k]==0){
				isblack=1;
				horiCent_num=horiCent_num+k*isblack;
				horiCent_den=horiCent_den+isblack;
			}
			else{
				isblack=0;
			}
				
				
	}}

if(horiCent_den !=0){
	horiCent=static_cast<double>(horiCent_num)/horiCent_den;
}
else{
horiCent=0;
cout<<"Division by zero!"<<endl;
}
//end for horizontal centroid

//vertical centroid
int verCent_num=0;
isblack=1;
int verCent_den=0;

	for(int d=0;d<height;d++){
		for (int f=0;f<width;f++){
			if(myimage[d+uplr][f+uplc]==0){
				isblack=1;
				verCent_num=verCent_num+d*isblack;
				verCent_den=verCent_den+isblack;
				}
			else{
					isblack=0;
				}
	}}

if(verCent_den !=0){
	verCent=static_cast<double>(verCent_num)/verCent_den;
}
else{
verCent=0;
cout<<"Division by zero!"<<endl;
}

//end for verti centroid

}

void Character::classify(){
/*cout<<uplr<<" " <<uplc<<" ";
cout<<"Hor Sym "<<horizontal;
cout<<"  Ver sym "<<vertical<<endl;
cout<<"Ver Centroid "<<verCent;
cout<<"  Horiz centroid "<<horiCent<<endl;
cout<<" Aspect "<<aspRat<<" ";//<<"bq1"<<q1;
cout<<"  Euler"<<euler<<" "<<"Width"<<width<<" Height"<<height<<" ";*/

//clasify as 8
if(euler==-1){
	actualchar=8; //has to be 8 because it is the only one iwht 2 holes. i.e euler number is -1
	//cout<<actualchar<<endl;
}
//classify as 4,6 or 9
else if(euler==0){ //it could either be 0,4, 6 or 9
	if(vertical >0.9 || horizontal>0.9){  //0 has to be symmetrical but not in italics so we need one more condition. 
		actualchar=0;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}

	else if(horizontal>vertical){ //can be 6 or 9. 
		if(verCent>static_cast<double>(height)/2 ){ //it hasto be 6 becayse black pixels are more on the bottom. 
				
				actualchar=6;
				//cout<<"Char "<<actualchar<<endl<<endl;
				
		}
		else { //9 because black pixels are more on the top. 
				actualchar=9;
				//cout<<"Char "<<actualchar<<endl<<endl;
		}
	
	}

	else if(horiCent>(static_cast<double>(width)/2)+1){ //it has to be 4
		actualchar=4;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}

	else if((static_cast<int>(verCent)==height/2) && (static_cast<int>(horiCent)==(width/2)-1)){		//has to be zero because usually even in italics the centroid has to be equally distributed. 
		actualchar=0;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
	else if(vertical<0.5){      //vertical symmetry if its less then 0.5 in italics, this is the last thing that will execute. If this fails then it has to be 4 as four has a higer vertical symmetry in italics. 
		actualchar=0;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
		
	else{ //possibly foru because6 and 9 and confirmend. So is 0 confirmed. so in case the statement for 4 doesn't work for some font we can rely on this to give us a general idea that it has to either 4 or if its wrong then atleast its a number with one hole. 
				actualchar=4;
				//cout<<"Char "<<actualchar<<endl<<endl;
	}
	
}

//classify as 1,2,3,5,7
else { //it could either be 1,2,3,5,7

	 
	if(aspRat>1.7){ //it has to be 1 because 1 is slim character. 
		actualchar=1;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
	
	else if(verCent<((height/2)-1) && vertical<0.3){   //has to be 7 because vertical symmetry is less and centroid is located on the top. 
		actualchar=7;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
	else if(vertical>0.6){ //only works for regular font not itlaics. But 3 is pretty much has a higher vertical summetry. 
		actualchar=3;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
	//3 for italics
	else if(horiCent>width/2+2){ //horizontal centroid is localted further then the middle as more black pixels are towards the right. 
		actualchar=3;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
	
	else if(verCent<height/2){	//5 only for regular fonts
		actualchar=5;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
	//5 for italics
	else if(vertical<0.2){ // 5 has a really low symmetry in italics
		actualchar=5;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
	else if(verCent>height/2){  //since a lot of theblack pixels are located in the bottom part if veritcal centroid is greater then half of height then it has to be 2. 
		actualchar=2;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
	else if (horiCent>width/2){ //becayse of the curvy part on the right side of 5 it has a higher horizontal centroid in italics. 
		actualchar=5;
		//cout<<"Char "<<actualchar<<endl<<endl;
		}

	else  {//in case everything fails this would be nice guess to assume
		actualchar=2;
		//cout<<"Char "<<actualchar<<endl<<endl;
	}
}
	
}
int Character::get_classification(){  //returns the classification character
	return actualchar;
}

void Character::print_calculations(){
cout<<"Character in bounding box: "<<uplr<<","<<uplc<<" to "<<uplr+height<<","<<uplc+width<<endl;
cout<<"===================================="<<endl;
cout<<"BQ0="<<q0<<" BQ1="<<q1<<" BQ2="<<q2<<" BQ3="<<q3<<" BQ4="<<q4<<" BQD="<<qd<<endl;
cout<<"Euler number="<<euler<<endl;
cout<<"VCentroid="<<verCent<<" / HCentroid="<<horiCent<<endl;
cout<<"VSym="<<vertical<<" / "<<"HSym="<<horizontal<<endl;
cout<<"Aspect ratio="<<aspRat<<endl;
cout<<"Character "<<counter+1<<" is classified as: "<<actualchar<<endl<<endl;
}

void Character::getcount(int &counter1){
	counter=counter1;
}

