#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD unsigned short
#define BYTE unsigned char

typedef struct _JFIF_Header
{
    BYTE SOIMarker[2];      // start of image marker
    BYTE APP0_Marker[2];    // Application use marker
    WORD APP0_Length;       // Length of APP0 field
    BYTE Identifier[5];     // zero terminating string "JFIF",X'4A', X'46', X'49', X'46', X'00'
    BYTE Version[2];        // X'01',X'02'
    BYTE Units;             // units = 0:no units ;; units = 1:X and Y are dots per inch ;; units = 2:X and Y are dots per cm
    WORD XDensity;          // horizontal pixel density
    WORD YDensity;          // vertical pixel density
    BYTE XThumbnail;        // Thumbnail horizontal pixel density
    BYTE YThumbnail;        // Thumbnail vertical pixel density
}JFIFHeader;

int main(){
    FILE *fp;
    char *filename = "ncku.jpg";
    
    //open the image file
    fp = fopen(filename,"r");
    if(fp == NULL){
        fputs ("File error",stderr); exit (1);
    }
        //printf("Cannot open the file, filename: %s\n", filename);

    //obtain the file size
    fseek (fp , 0 , SEEK_END); // move the  position indicator to the file end
    int lSize = ftell (fp);
    rewind(fp); // re-point the indicator to beginning of the file
    printf("The file size of file: %d\n", lSize);

    // allocate memory to contain the whole file:
    unsigned char * buffer = (char*) malloc (sizeof(char)*lSize); 
    // the sequential jpeg with Huffman is 8 bits
    if (buffer == NULL){
        fputs ("Memory error",stderr); exit (1);
    }

    //read the whole file
    fread (buffer,1,lSize,fp);

    //check the IFIF
    JFIFHeader header;
    header.SOIMarker[0] = 0xff;
    header.SOIMarker[1] = 0xd8;
    header.APP0_Marker[0] = 0xff;
    header.APP0_Marker[1] = 0xe0;
    if(buffer[0] == header.SOIMarker[0] && buffer[1] == header.SOIMarker[1])
        printf("Checked the SOI Marker of JPEG\n");
    else{
        printf("[ERROR] Can not find the SOI of input image\n"); exit (1);
    }

    //read the APP0 segment
    if(buffer[2] == header.APP0_Marker[0] && buffer[3] == header.APP0_Marker[1])
        printf("Starting the APP0 marker segment\n");
    else{
        printf("[ERROR] The APP0 Marker of input image is wrong\n"); exit (1);
    }
    header.APP0_Length = buffer[4]*16*16  + buffer[5];
    printf("The length of APP0 marker: %d\n", header.APP0_Length);
    
    BYTE APP0_identifier[5]={0x4A,0x46,0x49,0x46,0x00};//identifier: 4A 46 49 46 00 = "JFIF"
    int counter = 0;
    for(int i = 0; i < 5; i++){
        header.Identifier[i] = buffer[6+i];
        if(header.Identifier[i] == APP0_identifier[i])
            counter++;
    }
        
    if(counter==5)
        printf("Pass the APP0 indentifier\n");
    else{
        printf("[ERROR] Not pass the APP0 indentifier\n");
    }
    
    header.Version[0] = buffer[11]; header.Version[1] = buffer[12];
    printf("The IFIF version : %d.0%d\n", header.Version[0], header.Version[1]);
    header.Units = buffer[13];
    if(header.Units == 0x00)
        printf("Density units: No unit\n");
    else if(header.Units == 0x01)
        printf("Density units: Pixels per inch (2.54 cm)\n");
    else if(header.Units == 0x02)
        printf("Density units: Pixels per centimeter\n");
    else
        printf("[ERROR] Density units: WRONG MODE\n");
    header.XDensity = buffer[14]*16*16+buffer[15];
    header.YDensity = buffer[16]*16*16+buffer[17];
    printf("The Density of JPEF: %d x %d\n", header.XDensity, header.YDensity);
    header.XThumbnail = buffer[18];
    header.YThumbnail = buffer[19];
    printf("The XThumbnail: %d, and YThumbnail: %d\n", header.XThumbnail, header.YThumbnail);

    // terminate
    fclose(fp);
    free(buffer);
    return 0;
}