/*
 * model.c
 * provides the grid (model) 
 * and functions to handle the grid for the game of life
 * 
 * Zeynep Ülkü Kılıç
 */

#include "gameoflife.h"
int grid[M][N] = {0}; 	/*M ve N gameOfLife.h ta tanımlıdır.*/
int neighbor[M][N] = {0};	/*neighbor sayısını tutan dizi*/

/**
 * gridi başlangıç durumunda verilen sayıya göre başlatır.
 */
int initGrid(int initialState){
	/*1 seçilirse blinkerı, 2 seçilirse gliderı gösteren fonksiyon*/
	if(1 == initialState){
		/*blinker*/
		for(int i = 5; i < M; i=i+10){
			grid[i][i] = 1; 
			grid[i+1][i] = 1;
			grid[i-1][i] = 1;
				
		}
	}
	if(2 == initialState){
		/*glider*/
		for(int j = 4; j < M; j=j+10){
			grid[j-1][j+1] = 1;
			grid[j][j-1] = 1;
			grid[j][j+1] = 1;
			grid[j+1][j] = 1;
			grid[j+1][j+1] = 1;
		}		
	}
	return 0;
}

/**
 * griddeki x,y indexli hücrenin canlı komşularının sayısını dönderir
 * 
 */
int getNumberOfLiveNeighbors(int x, int y){
	int neighbors = 0;	/*komşu sayısı*/
	/*hücrelerin canlı komşu sayısını bulur*/
	for(int i =  x-1; i <= x+1; i++){
		for(int j = y-1; j <= y+1; j++){
			if(!(i == x && j == y)
			&& (i >= 0) && (i < M) 
			&& (j >= 0) && (j < N)){
				if(1 == grid[i][j]){
					neighbors++;
				}
			}
		}
	}
	return neighbors;
}

/**
 * her bir hücrenin yaşamını kurallara göre günceller
 */
int updateGrid(){
	/*her bir hücrenin komşu sayısını neighbor dizisinin aynı indexli hücrelerine atar*/
	for(int a = 0; a < M; a++){
		for(int b = 0; b < N; b++){
			neighbor[a][b] = getNumberOfLiveNeighbors(a,b);
		}
	}
	/*kurallara göre canlı hücreleri yaşatır, ölü hücreleri canlandırır ya da yaşamalarına izin verir.*/
	for(int x = 0; x < M; x++){
		for(int y = 0; y < N; y++){
			/*hücre canlıysa ve komşu sayısı 2 ya da 3 ise hücre yaşamaya devam eder.*/
			if((grid[x][y] == 1) && ((neighbor[x][y] == 3)
								 || (neighbor[x][y] == 2))){
				grid[x][y] = 1;
			}
			/*hücre canlıysa ve komşu sayısı 1 ya da 1 den az ise hücre ölür*/
			else if((grid[x][y] == 1) && (neighbor[x][y] <= 1)){
				grid[x][y] = 0;				
			}
			/*hücre ölüyse ve komşu sayısı 3 ise hücre canlanır*/
			else if((grid[x][y] == 0) && (neighbor[x][y] == 3)){
				grid[x][y] = 1;
			}
			/*hücre canlıysa ve komşu sayısı 3'ten fazla ise hücre ölür.*/
			else if((grid[x][y] == 1) && (neighbor[x][y] > 3)){
				grid[x][y] = 0;
			}
		}
	}
	return 0;
}


