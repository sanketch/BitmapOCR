BitmapOCR
=========

A basic OCR in C++ that can read in a black and white bitmap image containing decimal digits and recognize/classify each character. 

This repo includes the files that I worked on a part of my Software Design Class at USC. 

The main code to read the file and classify is in the bmplib.cpp file. 

## How accurate it is?
Upon testing with the images included in the repo, the program has been able to successfuly classify the characters. But since the program relies on symmetry, aspect ratio, euler's ratio, horizontal and vertical centroid, if the typeface significantly changes then it might have trouble classifying it. Also the program isn't accurate with digits in Italics.
