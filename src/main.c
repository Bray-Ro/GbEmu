#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>





const unsigned int MEMMAP[20][2] = {
	{0x0000, 0x3FFF}, /*16 KiB ROM bank 00*/
	{0x4000, 0x7FFF}, /*16 KiB ROM Bank 01~NN*/
	{0x8000, 0x9FFF}, /*8 KiB Video RAM (VRAM)*/
	{0xA000, 0xBFFF}, /*8 KiB External RAM*/
	{0xC000, 0xCFFF}, /*4 KiB Work RAM (WRAM)*/
	{0xD000, 0xDFFF}, /*4 KiB Work RAM (WRAM)*/
	{0xE000, 0xFDFF}, /*Mirror of C000~DDFF (ECHO RAM)*/
	{0xFE00, 0xFE9F}, /*Sprite attribute table (OAM)*/
	{0xFEA0, 0xFEFF}, /*Not Usable*/
	{0xFF00, 0xFF7F}, /*I/O Registers*/
	{0xFF80, 0xFFFE}, /*High RAM (HRAM)*/
	{0xFFFF, 0xFFFF}, /*Interrupt Enable register (IE)*/
	

};

char memory[65535]; 

/*CPU Registers*/
char A;
/*The flags register*/
char F;

char B;
char C;

char D;
char E;

char H;
char L;

/*Stack pointer*/
int16_t SP;
/*Program counter*/
int16_t PC;

char* read_ROM(char file_name[5000]) {
        /* declare a file pointer */
    FILE    *infile;
    char    *buffer;
    long    numbytes;
    
    /* open an existing file for reading */
    infile = fopen(file_name, "rb");
    
    /* quit if the file does not exist */
    if(infile == NULL) {
        printf("\nERROR WHILE READING FILE: FILE DOES NOT EXIST\n");
        return "ERROR WHILE READING FILE: FILE DOES NOT EXIST";
    }
    
    /* Get the number of bytes */
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    
    /* reset the file position indicator to 
    the beginning of the file */
    fseek(infile, 0L, SEEK_SET);	
    
    /* grab sufficient memory for the 
    buffer to hold the text */
    buffer = (char*)calloc(numbytes, sizeof(char));	
    
    /* memory error */
    if(buffer == NULL) {
        printf("\nERROR WHILE READING FILE: MEMORY ERROR\n");
        return "ERROR WHILE READING FILE: MEMORY ERROR";
    }
    
    /* copy all the text into the buffer */
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);
    /* confirm we have read the file by
    outputing it to the console */
    return buffer;
    
    /* free the memory we used for the buffer */
    free(buffer);
}


int main(int argc, char *argv[255]) {
	
	/*Load cartridge ROM*/
	unsigned char cartridge[64000];	
	FILE *ptr;

	ptr = fopen(argv[1],"rb");  // r for read, b for binary
	
	fseek(ptr, 0L, SEEK_END);
	int sz = ftell(ptr);
	rewind(ptr);

	fread(cartridge,sz,1,ptr);


	int i = 0;
	
	while (i <= sz) {
		if (i % 17 == 0) {
			printf("\n");
		}
		if (i >= 0x104 && i <= 0x133) {
			printf("%x ", cartridge[i]);
		}
		i++;
	}
	
	/*TODO: Load Cartridge into memory*/
	
	return 0;
}
