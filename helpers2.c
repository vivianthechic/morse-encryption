// Define all helper functions for hw1 in this file
#include "helpers2.h"

int len(char * str){
	int len = 0;
	int i;
	for(i = 0; *(str+i) != '\0'; i++){
		len++;
	}
	return len;
}

char * concat(char * dest, char * src){
	int i;
	int dlen = len(dest);
	for(i = 0; *(src+i) != '\0'; i++){
		*(dest+dlen+i) = *(src+i);
	}
	*(dest+dlen+i) = '\0';
	return dest;
}

int ncomp(char * str1, char * str2, int n){
	int i;
	for(i = 0; *(str1+i) != '\0' && *(str2+i) != '\0' && i < n; i++){
		if(*(str1+i) != *(str2+i))
			return *(str1+i)-*(str2+i);
	}
	return 0;
}

char charInKey(char * key, char c, int keylen){
	int i;
	for(i = 0; i < keylen; i++){
		if(*(key+i) == c) return 1;
	}
	return 0;
}

char processChar(char * mcletter, char **MorseCode){
	int mclen = len(mcletter);
	int arrindex;
	for(arrindex = 0; arrindex < 58; arrindex++){
		if(mclen == len(*(MorseCode+arrindex))){
			if(ncomp(mcletter,*(MorseCode+arrindex),mclen) == 0)
				return arrindex+33;
		}
	}
	return -1;
}

char * keyToMorse(char c, char *key){
	char * FMCarray = ".....-..x.-..--.-x.x..x-.xx-..-.--.x--.-----x-x.-x--xxx..x.-x.xx-.x--x-xxx.xx-";
	int keyindex;
	char * triplet = malloc(4);
	char found = 0;
	for(keyindex = 0; keyindex < 26 && found == 0; keyindex++){
		if(c == *(key+keyindex)) found = 1;
	}
	if(found){
		keyindex = (keyindex-1)*3;
		int i;
		for(i = 0; i < 3; i++){
			*(triplet + i) = *(FMCarray + keyindex + i);
		}
		return triplet;
	}
	return "";
}
