
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 
int main(int argc, char* argv[])
{
    // open raw file
    FILE* file = fopen("card.raw","r");
    if (file == NULL)
    {
        fclose(file);
        return 3;
    } 
    
    uint8_t buffer[512];
    char name[8];
    int numImages = 0;
    
    FILE* image = NULL;
    while(fread(buffer,sizeof(buffer),1,file)>0)
    {
        // check if buffer's first 4 elements are same as check(1),(2)
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]==0xe0 || buffer[3]==0xe1))
        {   
            if(image!=NULL)
            {
                fclose(image);
            }
            sprintf(name,"%03i.jpg",numImages);
            image = fopen(name,"w"); 
            numImages++;                                              
        } 
        if(image!=NULL)
        {
            fwrite(buffer,sizeof(buffer),1,image);
        }
    }
    fclose(image);    
    fclose(file);
    return 0;
}
