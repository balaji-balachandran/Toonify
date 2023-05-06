# Toonify
CS 225 Final Project

## Our Project
Toonify is a C++ based program that allows the user to input a .png and outputs the image as a cartoonified version of itself. The project utilizes the SLIC (Simple Iterative Linear Clustering) algorithm.

The SLIC superpixeling algorithm is described in the article by Achanta et al. titled "SLIC Superpixels", linked below:
https://www.iro.umontreal.ca/~mignotte/IFT6150/Articles/SLIC_Superpixels.pdf

## Repository Organization

Frontend files - located in /frontend

Includes php files in /frontend/scripts and /frontend/pages, and CSS files in /frontend/css


Backend files - located in /backend

Includes primary algorithms in /backend/src and supporting image classes in /backend/lib


Makefile - located in /backend


Image files - located in /backend/images


Written Report - located in /results.md

## Running our files

To run all the algorithms in this project, please navigate to the folder containing the Makefile and running it. Your output will be a Toonified image named 'toonified.png' in the backend/images folder. All the steps for this are written out below.

A video explanation of our project is attached as an mp4 file in the repository. View the youtube video here: https://youtu.be/219YsAPvwi4

# Steps to run the files:

To run the PHP, you must first download xampp and apache (download links here: https://www.apachefriends.org/download.html)

Then, git clone the repository into htdocs (in C: drive if used default installation)

To run the php, open the apache control panel and hit start on apache and SQL.

Navigate to localhost/Toonify/frontend/pages to get to the landing page

Then back in terminal: 

cd backend

make exec
./bin/exec

make test 
./bin/test

make clean
  ** cleans bin directory

Runs slic.cpp main function:            
g++ src/slic.cpp -std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic -o bin/slic

./bin/exec will start the C++ for accepting the file.

Then we can simply upload the image into the home page and see the results pop up under Toonify/backend/images !

Hope you enjoy!
