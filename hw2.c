// Vivian Zhang
// vszhang

#include "morsecode.h"
#include "hw2.h"
#include "helpers2.h"

char* MorseCode[] = {MorseExclamation, MorseDblQoute, MorseHashtag, Morse$, MorsePercent, MorseAmp, MorseSglQoute, MorseOParen, MorseCParen, MorseStar, MorsePlus, MorseComma, MorseDash, MorsePeriod, MorseFSlash, Morse0, Morse1, Morse2, Morse3, Morse4, Morse5, Morse6, Morse7, Morse8, Morse9, MorseColon, MorseSemiColon, MorseLT, MorseEQ, MorseGT, MorseQuestion, MorseAt, MorseA, MorseB, MorseC, MorseD, MorseE, MorseF, MorseG, MorseH, MorseI, MorseJ, MorseK, MorseL, MorseM, MorseN, MorseO, MorseP, MorseQ, MorseR, MorseS, MorseT, MorseU, MorseV, MorseW, MorseX, MorseY, MorseZ};

/* Part 1 Functions */
int toMorse(FILE *instream, char **mcmsg_ptr){
	int size = 50;
	*mcmsg_ptr = (char *)malloc(size);
	char space = 0;
	if (*mcmsg_ptr == NULL) return -1;
       	char c;
	while((c = fgetc(instream)) != EOF){
		if(c < 0 || c > 127) return 0; // non ascii char
		if(c >= 97 && c <= 122) c -= 32; // convert lowercase letter to uppercase
		else if(c == ' ' && space == 0){
			space = 1;
			*mcmsg_ptr = concat(*mcmsg_ptr,"x");
		}
		if(c >= 33 && c <= 90){
			space = 0;
			*mcmsg_ptr = concat(*mcmsg_ptr,*(MorseCode + c - 33));
			*mcmsg_ptr = concat(*mcmsg_ptr,"x");
		}
		if(len(*mcmsg_ptr) >= size - 6){
			size *= 2;
			*mcmsg_ptr = realloc(*mcmsg_ptr,size);
			if (*mcmsg_ptr == NULL) return -1;
		}
	}
	if(space == 0)
		*mcmsg_ptr = concat(*mcmsg_ptr,"x");
	return 1;
}

void createKey(char* keyphrase, char* key){
	int i;
	char c;
	int keylen = 0;
	for(i = 0; i < len(keyphrase); i++){
		c = *(keyphrase+i);
		if(isalpha(c)){
			if(c >= 97 && c <= 122) c -= 32; // lower to upper
			if(charInKey(key,c,keylen) == 0){
				*(key+keylen) = c;
				keylen++;
			}
		}
	}
	for(c = 65; c <= 90; c++){
		if(charInKey(key,c,keylen) == 0){
			*(key+keylen) = c;
			keylen++;
		}
	}
}

char morseToKey(char* mcmsg, char* key){
    char* FMCarray = ".....-..x.-..--.-x.x..x-.xx-..-.--.x--.-----x-x.-x--xxx..x.-x.xx-.x--x-xxx.xx-";
        int index = 0;
	char *FMCindex;
	char found = 0;
	if(len(mcmsg)<3) return -1;
	for(FMCindex = FMCarray; index < 26 && found == 0; FMCindex += 3){
		if(ncomp(mcmsg,FMCindex,3) == 0)
			found = 1;
		else
			index++;
	}
	if(found) return *(key+index);
        else return -1;
}

int FMCEncrypt(FILE *instream, char* key, FILE *outstream){
        char *mcmsg = NULL;
	int tm = toMorse(instream, &mcmsg);
	if(tm != 1) return tm; // unsuccessful mc encoding
	char k = morseToKey(mcmsg,key);
	int temp = 0;
	char * ptr = mcmsg;
	while(k != -1 && *ptr != '\0'){
		fputc(k, outstream);
		ptr += 3;
		k = morseToKey(ptr,key);
	}
	free(mcmsg);
	return 1;
}

/* Part 2 Functions */
int fromMorse(char *mcmsg, FILE* outstream){
        char * mcletter = malloc(6);
	if(mcletter == NULL) return 0;
	int mcindex = 0;
	char wasx = 0;
	char mcc;
	while((mcc = *mcmsg) != '\0'){
		if(mcc == 'x'){
			if(wasx == 1){
				if(*(mcmsg+1) == '\0') break;
				fputc(' ',outstream);
				wasx = 0;
			}
			else{
				*(mcletter + mcindex) = '\0';
				char temp = processChar(mcletter,MorseCode);
				if(temp == -1) return 0;
				fputc(temp,outstream);
				mcindex = 0;
				wasx++;
			}
		}
		else{
			wasx = 0;
			*(mcletter+mcindex) = mcc;
			mcindex++;	
		}
		mcmsg++;
	}
	free(mcletter);
        return 1;
}

int FMCDecrypt(FILE *instream, char* key, FILE *outstream){
        int size = 50;
        char * mcmsg = (char *)malloc(size);
        if(mcmsg == NULL) return -1;
	char c;
	while((c = fgetc(instream)) != EOF){
		if(c < 65 || c > 90) return 0;
		char * mctriplet = keyToMorse(c,key);
		mcmsg = concat(mcmsg, mctriplet);
		if(len(mcmsg) >= size - 5){
			size *= 2;
			mcmsg = realloc(mcmsg,size);
			if(mcmsg == NULL) return -1;
		}
		free(mctriplet);
	}
	mcmsg = concat(mcmsg,"xx");
	int fm = fromMorse(mcmsg, outstream);
	free(mcmsg);
	if(fm != 1) return fm;
        return 1;
}

