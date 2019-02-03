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

    int q_index, h_index, SOF_index;
    for(int i = 0; i<400; i++){
        printf("%x\t", buffer[0+i]);
        //find the quantization table part
        if(buffer[0+i]==0xff && buffer[1+i]==0xdb)  
            q_index = i;
        //find the SOF part
        if(buffer[0+i]==0xff && buffer[1+i]==0xc0)  
            SOF_index = i;
        //find the huffman table part
        if(buffer[0+i]==0xff && buffer[1+i]==0xc4)  
            h_index = i;
        if(i%10==0)
            printf("\n");
    }
    printf("\n\nQuantization Table\n");

    //extract the Quantization Table (DQT) with two table: index0 and index1
    int QT_length = buffer[q_index+2]*16*16+buffer[q_index+3];
    BYTE * QT = malloc(sizeof(BYTE)*QT_length);
    for(int i = 0; i < 4; i++){
        QT[i] = buffer[q_index+i];
        printf("%x\t", QT[i]);
    }
    /*for(int i = 0, index = 0; i < DHT_length-2; i++){
        index = i + 4;
        QT[index] = buffer[q_index+index];
        if(i%13==0)
            printf("\n");
        printf("%d\t", QT[index]);
    }*/
    int count = 0;
    for(int i = 0, index = 0; i < QT_length-2; i++){
        index = i + 4;
        QT[index] = buffer[q_index+index];
        if(i==1 || i == 66){
            printf("\n");
            count = 0;
        }
            
        if(i>=1)
            count++;
        printf("%d\t", QT[index]);
        if(count%8==0)
            printf("\n");
    }
    /*  QT information(1 byte): here: index0 8 bits and index1 8 bits
        bit 0..3: number of QT (0..3, otherwise error)
        bit 4..7: precision of QT, 0 = 8 bit, otherwise 16 bit */


    printf("\n");
    printf("\nSOF information\n");
    //extract the SOF information
    int SOF_length = buffer[SOF_index+2]*16*16+buffer[SOF_index+3];
    for(int i = 0; i < SOF_length+2; i++){
        printf("%x\t", buffer[SOF_index+i]);
    }
    int image_precision = buffer[SOF_index+4];
    int image_height = buffer[SOF_index+5]*16*16+buffer[SOF_index+6];
    int image_width = buffer[SOF_index+7]*16*16+buffer[SOF_index+8];
    int Number_components = buffer[SOF_index+9];
    printf("\nThe Data precision of image: %d\n", image_precision);
    printf("The Image height of image: %d\n", image_height);
    printf("The Image width of image: %d\n", image_width);
    printf("The Number of components in image: %d\n", Number_components);

    /*  (component Id(1byte)(1 = Y, 2 = Cb, 3 = Cr, 4 = I, 5 = Q),
        sampling factors (1byte) (bit 0-3 vertical., 4-7 horizontal.),
        quantization table number (1 byte)). */

    printf("\n");
    printf("\nHuffman Table\n");

    //extract the Huffman Code Tables (DHT)
    int DHT_length = buffer[h_index+2]*16*16+buffer[h_index+3];
    BYTE * DHT = malloc(sizeof(BYTE)*(DHT_length+2));
    //get HT information
    int DHT_num = buffer[h_index+4] & 0x0f; //0000 1111
    int DHT_type=(buffer[h_index+4] & 0x10) >> 4; //0001 0000
    printf("The number of DHT %d and the type of DHT %d\n", DHT_num, DHT_type);//0 = DC table, 1 = AC table 
    for(int i = 0; i < DHT_length+2; i++){
        DHT[i] = buffer[h_index+i];
        printf("%x\t", DHT[i]);
        if(i%10==0)
            printf("\n");
    }
    printf("\n");
    for(int i = 0; i< 16; i++)
        printf("There are %x of symbols with length of %d\n", buffer[h_index+5+i], i+1);
    printf("\n");



    //0xffec and 0xffee: (APP1~APP15) Application-specific data
    //0xffdb: quantization table
    //0xffc0: start of frame, Indicates that this is a baseline DCT-based JPEG, and specifies the width, height, number of components, and component subsampling
    //0xffc4: huffman table
    //0xffda: start of scan
    //0xffd9: end of file

    // terminate
    fclose(fp);
    free(buffer);
    return 0;
}