#include <iostream>
#include <fstream>
#include <cstdlib> 
#include "bmplib.h"
#include "point.h"
#include <deque>
#include <vector>
unsigned char image[256][256];
using namespace std;
int main(int argc, char *argv[]) {


	BMPTYPE type;
  BMPFILEHEADER fHeader;
  BITMAPHEADER bmpHeader;
	//char* filename;
	cout<<"read"<<endl;
	readGS_BMP(argv[1], image, type, fHeader, bmpHeader);

	cout<<"starttresh"<<endl;
	for(int i=0; i < 256; i++){
	    for(int j=0; j < 256; j++){
			if(image[i][j]>128)
				{
				image[i][j]=255;
				}
			else{
				image[i][j]=0;
				}
		}}
	
		
	char copy1[256][256];
	cout<<"treshold done"<<endl;
	deque<Point> bfsq;
	int highrow,highcol,lowrow,lowcol;
	//Initializes Copy array with -1
	for(int y=0; y < 256; y++){
	    for(int x=0; x < 256; x++){
			copy1[y][x]=-1;
	
		}
	}	
	int dummy1=0;
int charcount=0;
int counter=0;
//deque<Character> charfound;
vector<Character> charfound;
cout<<"begin for loop"<<endl;
	for(int r=0; r < SIZE; r++){
    		for(int c=0; c< SIZE; c++){
		
		if(image[r][c]==0 && copy1[r][c]==-1){
			cout<<"found a black pix"<<endl;
			Point p(r,c);
			bfsq.push_back(p);
			//charcount++;
			//if(dummy1==0){ //to ensure that it runs only for the first time. 
				highrow=r;
				highcol=c;		
				lowrow=r;	
				lowcol=c;
				//dummy1++;
				//}
			

			
			while(!bfsq.empty()){
			//checks right
			//cout<<r<<" "<<c<<endl;
			Point p(r,c);
			p=bfsq.front();
			r=p.r;
			c=p.c;
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
	bfsq.pop_front();
  	
	if(r>highrow)	
		highrow=r;
	if(r<lowrow)
		lowrow=r;
	if(c>highcol)
		highcol=c;
	if(c<lowcol)
		lowcol=c;
		
	}//while endings
	cout<<"whileend"<<endl;
	//puts in the character

	Character charfound1(image,lowrow,lowcol,highrow-lowrow,highcol-lowcol);
	charfound.push_back(charfound1);
counter++;
	
}//end for the "if if found an black box"

}}//for endings
	int uplr,uplc;
	int height,width;

	//writes the gray code
cout<<"hi"<<endl;
//cout<<counter<<endl;
	for(int k=0;k<counter;k++){
		//cout<<"into for loop"<<endl;
		uplr=charfound[k].retuplr();
		uplc=charfound[k].retuplc();
		height=charfound[k].reth();
		width=charfound[k].retw();

		cout<<"uplr"<<uplr<<endl;
cout<<"uplc"<<uplc<<endl;
cout<<"h"<<height<<endl;
cout<<"w "<<width<<endl;
	
		for(int e=uplc;e<width+uplc+1;e++){  //draws around upper width
			image[uplr][e]=128;
			}
//cout<<"uw"<<endl;
		for(int x=uplc;x<width+uplc+1;x++){  //draws around lower width
			image[uplr+height][x]=128;
			}
//cout<<"lw"<<endl;
		for(int y=uplr;y<uplr+height+1;y++){  //draws around the left height
			image[y][uplc]=128;
			}
//cout<<"uh"<<endl;
		for(int z=uplr;z<uplr+height+1;z++){  //draws aroundthe right height
			image[z][uplc+width]=128;
			}
//cout<<"lh"<<endl;
		
		

	}//ccounter "for: ending	
	
	

	writeGS_BMP("out1.raw", image, type, fHeader, bmpHeader);
return 0;
}


