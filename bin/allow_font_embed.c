/* To run this from Terminal:

    1. Compile this script like
    $ make allow_font_embed

    2. Execute program like
    $ ./allow_font_embed /Volumes/path/to/ttf/font

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fatal();

int main(int argc, char**argv) {
     printf("argc: %d, argv: %s, %s\n", argc, argv[0], argv[1]);
     FILE * inways;
     if(argc != 2)
        printf("ERROR - Usage: %s path_to_font.ttf\n", argv[0]);
     else if((inways = fopen(argv[1],"rb+"))) {
        int a, x;
        char type[5];
        type[4] = 0;
        fseek(inways, 12, 0);
        for(;;) {
           for(x=0; x<4; x++) if (EOF == (type[x] = getc(inways))) fatal();
           if(!strcmp(type, "OS/2")) {
              int length;
              unsigned long loc, fstype, sum=0;
              loc = ftell(inways); /* location for checksum */
              for(x=4; x--;) if(EOF == getc(inways)) fatal();
              fstype  = fgetc(inways) << 24;
              fstype |= fgetc(inways) << 16;
              fstype |= fgetc(inways) << 8 ;
              fstype |= fgetc(inways)      ;
              length  = fgetc(inways) << 24;
              length |= fgetc(inways) << 16;
              length |= fgetc(inways) << 8 ;
              length |= fgetc(inways);
/*              printf("fstype: %d length: %d\n",fstype,length);*/
              if(fseek(inways, fstype+8, 0)) fatal();
              fputc(0, inways);
              fputc(0, inways);
              fseek(inways, fstype, 0);
              for(x=length; x--;)
                  sum += fgetc(inways);
              fseek(inways, loc, 0); /* write checksum */
              fputc(sum >> 24, inways);
              fputc(255&(sum >> 16), inways);
              fputc(255&(sum>>8), inways);
              fputc(255&sum, inways);
              fclose(inways);
              printf("SUCCESS - Altered font: %s\n", argv[1]);
              exit(0);
           }
           for(x=12; x--;) if(EOF == getc(inways)) fatal();
        }

     } else
        printf("ERROR - I wasn't able to open the file %s.\n", argv[1]);
}

void fatal() { fprintf(stderr,"Malformed TTF file.\n");
               exit(-1); }