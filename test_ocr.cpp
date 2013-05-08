#include <iostream>
#include <fstream>
#include <cstdlib> 
#include "bmplib.h"
#include "point.h"
#include <deque>
#include <vector>
using namespace std;


unsigned char image[256][256];

int main(int argc, char *argv[]) {
	char copy1[256][256];
	char* filename;
	int debugInfo;
	BMPTYPE type;
  	BMPFILEHEADER fHeader;
  	BITMAPHEADER bmpHeader;

  	if(argc < 3){  //making sure the input is right. 
    		cerr << "Usage: ./test_ocr input.bmp Debuginfo(1 or 0)" << endl;
  	}
	filename=argv[1];  //points to the file name
	debugInfo=atoi(argv[2]); //accepts 1 or 0.
	

	readGS_BMP(argv[1], image, type, fHeader, bmpHeader);  //reads the file. 

	//pixel values are either 255 or 0
	for(int i=0; i < SIZE; i++){ //transverse throught the image and if its greater then 128 consider it as black otherwise white. 
	    for(int j=0; j < SIZE; j++){
			if(image[i][j]>128)
				{
				image[i][j]=255;
				}
			else{
				image[i][j]=0;
				}
		}}
	
	//treshold done
	deque<Point> bfsq;   //deque to store the bfs queue
	int highrow,highcol,lowrow,lowcol;
	//Initializes Copy array with -1
	for(int y=0; y < SIZE; y++){
	    for(int x=0; x < SIZE; x++){
			copy1[y][x]=-1;
	
		}
	}	
	
	int counter=0;

	vector<Character> charfound; //vector of characters

	int r,c;

	//for loop for checking across the image and it stops when it finds all the characters. 
	for(int r1=0; r1 < SIZE; r1++){
    		for(int c1=0; c1< SIZE; c1++){
		
		if(image[r1][c1]==0 && copy1[r1][c1]==-1){  //if found a black pixel and if not explored already. 
			
			Point p(r1,c1);  //creates a point object
			bfsq.push_back(p); //pushes back the r1 and c1 in the bfsq
			
				highrow=r1;
				highcol=c1;		
				lowrow=r1;	
				lowcol=c1;
				
			

			
			while(!bfsq.empty()){ //runs until the bfsq is empty
			
			
			Point p(r1,c1);

			p=bfsq.front();
			r=p.r;
			c=p.c;
			//checks right
			if(image[r][c+1]==0 && copy1[r][c+1]==-1){
				copy1[r][c+1]=-2;
				Point p(r,c+1);
				bfsq.push_back(p);
			}	
			//checks left
			if(image[r][c-1]==0 && copy1[r][c-1]==-1){
				copy1[r][c-1]=-2;
				Point p(r,c-1);
				bfsq.push_back(p);
			}
			//checks up
			if(image[r-1][c]==0 && copy1[r-1][c]==-1){
				copy1[r-1][c]=-2;
				Point p(r-1,c);	
				bfsq.push_back(p);
			}
			//checks down
			if(image[r+1][c]==0 && copy1[r+1][c]==-1){
				copy1[r+1][c]=-2;
				Point p(r+1,c);
				bfsq.push_back(p);
			}
			//checks diagonoally up right
			if(image[r-1][c+1]==0 && copy1[r-1][c+1]==-1){
				copy1[r-1][c+1]=-2;
				Point p(r-1,c+1);
				bfsq.push_back(p);
			}
			//checks diagonoally up left
			if(image[r-1][c-1]==0 && copy1[r-1][c-1]==-1){
				copy1[r-1][c-1]=-2;
				Point p(r-1,c-1);
				bfsq.push_back(p);
			}
			//checks diagonoally down left
			if(image[r+1][c-1]==0 && copy1[r+1][c-1]==-1){
				copy1[r+1][c-1]=-2;
				Point p(r+1,c-1);
				bfsq.push_back(p);
			}
			//checks diagonoally down right
			if(image[r+1][c+1]==0 && copy1[r+1][c+1]==-1){
				copy1[r+1][c+1]=-2;
				Point p(r+1,c+1);
				bfsq.push_back(p);
			}
	bfsq.pop_front(); //removes the front object since we already explored it. 
  	
	if(r>highrow)	  //tries to find the highest and lowest row and col on every move
		highrow=r;
	if(r<lowrow)
		lowrow=r;
	if(c>highcol)
		highcol=c;
	if(c<lowcol)
		lowcol=c;
		
	}//while endings
	
	//puts in the character

	Character charfound1(image,lowrow,lowcol,highrow-lowrow,highcol-lowcol);
	charfound.push_back(charfound1);
	counter++; //keeps trqack of how many characters are found. 
	
}//end for the "if if found an black box"

}}//for endings
cout<<endl;
	for(int b=0;b<counter;b++){   //for loop to perform tests, classify and prints the resule. 
		
		//cout<<"(counter: "<<b+1<<") ";
		charfound[b].getcount(b);
		charfound[b].perform_tests();
		charfound[b].classify();
		if(debugInfo==1)   //if user entered 1 then it prints the calculations. 
			charfound[b].print_calculations();	
		else
		cout<<"The character "<<b+1<<" is classfied as "<<charfound[b].get_classification()<<endl<<endl;
}

return 0;
}


