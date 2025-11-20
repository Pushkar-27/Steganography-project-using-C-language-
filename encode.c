#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

uint get_file_size(FILE *fptr)
{
    // Find the size of secret file data

    uint get_file_size(FILE *fptr);          
    {
        long file_size;
        fseek(fptr, 0, SEEK_END);
        file_size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);
        return (uint)file_size;
    }

}

/*
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    // Check minimum required arguments
    if (argv[2] == NULL || argv[3] == NULL)
    {
        printf("Error: Missing input arguments (source image or secret file)\n");
        return e_failure;
    }

    // Validate source image file
    if (argv[2][0] == '.' || strstr(argv[2], ".bmp") == NULL)
    {
        printf("Error: Source image must be a .bmp file\n");
        return e_failure;
    }
    encInfo->src_image_fname = argv[2];

    // Validate secret file
    if (argv[3][0] == '.')
    {
        printf("Error: Invalid secret file name\n");
        return e_failure;
    }

    if (strstr(argv[3], ".txt") == NULL &&
        strstr(argv[3], ".c") == NULL &&
        strstr(argv[3], ".h") == NULL &&
        strstr(argv[3], ".sh") == NULL)
    {
        printf("Error: Secret file must be .txt, .c, .h, or .sh\n");
        return e_failure;
    }
    encInfo->secret_fname = argv[3];

    // Validate destination (output) image file
    if (argv[4] == NULL)
    {
        // If no output name provided, default to "stego.bmp"
        encInfo->stego_image_fname = "stego.bmp";
        printf("Info: No output filename provided. Using default: stego.bmp\n");
    }
    else
    {
        if (argv[4][0] == '.' || strstr(argv[4], ".bmp") == NULL)
        {
            printf("Error: Destination image must be a .bmp file\n");
            return e_failure;
        }
        encInfo->stego_image_fname = argv[4];
    }

    return e_success;
}


Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

        return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}


Status check_capacity(EncodeInfo *encInfo)
{
    uint image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
    uint secret_size = get_file_size(encInfo->fptr_secret);
    if (image_capacity < (secret_size * 8))
    {
        printf("Error: Insufficient image capacity to hold secret file.\n");
        return e_failure;
    }

    printf("Success: Image can hold the secret file.\n");
    return e_success;
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    char header[54];
    rewind(fptr_src_image);
    fread(header,54,1,fptr_src_image);
    fwrite(header,54,1,fptr_dest_image);
    if(ftell(fptr_src_image)==ftell(fptr_dest_image))
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    char buffer[8];
    for(int i=0;magic_string[i]!='\0';i++){
        fread(buffer,8,1,encInfo->fptr_src_image);
        encode_byte_to_lsb(magic_string[i], buffer);
        fwrite(buffer,8,1, encInfo->fptr_stego_image);
    }
    return e_success;
}
Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer,32,1,encInfo->fptr_src_image);
    encode_byte_to_lsb(size,buffer);
    fwrite(buffer,32,1,encInfo->fptr_stego_image);
    if(ftell(encInfo->fptr_src_image)==ftell(encInfo->fptr_stego_image))
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    char buffer[8];
    for(int i=0;i<=file_extn[i];i++){
        fread(buffer,8,1,encInfo->fptr_src_image);
        encode_byte_to_lsb(file_extn[i],buffer);
        fwrite(buffer,8,1,encInfo->fptr_stego_image);
    }
    if(ftell(encInfo->fptr_src_image)==ftell(encInfo->fptr_stego_image))
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer,32,1,encInfo->fptr_src_image);
    encode_byte_to_lsb(file_size,buffer);
    fwrite(buffer,32,1,encInfo->fptr_stego_image);
    if(ftell(encInfo->fptr_src_image)==ftell(encInfo->fptr_stego_image))
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char buffer[8];
    while(fread(encInfo->secret_data,1,1,encInfo->fptr_secret)){
        fread(buffer,8,1,encInfo->fptr_src_image);
        encode_byte_to_lsb(encInfo->secret_data[0],buffer);
        fwrite(buffer,8,1,encInfo->fptr_stego_image);
    }
    if(ftell(encInfo->fptr_src_image)==ftell(encInfo->fptr_stego_image))
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char buffer[1024];
    size_t bytes;
    while((bytes=fread(buffer,sizeof(char),sizeof(buffer),fptr_src))>0){
        fwrite(buffer,sizeof(char),bytes,fptr_dest);
    }
    return e_success;
}

Status encode_byte_to_lsb(char data, char *image_buffer)
{
    for(int i=7;i>=0;i--){
        image_buffer[7-i]=image_buffer[7-i]&(~1)|((data>>i)&1);
    }
    return e_success;
}

Status encode_size_to_lsb(int size, char *imageBuffer)
{
    for(int i=31;i>=0;i--){
        imageBuffer[31-i]=imageBuffer[31-i]&(~1)|((size>>i)&1);
    }
    return e_success;
}

Status do_encoding(EncodeInfo *encInfo)
{
    printf("INFO: Starting encoding process...\n");

    // Step 1: Open source, secret, and destination files
    if (open_files(encInfo) == e_failure)
    {
        fprintf(stderr, "ERROR: Opening files failed.\n");
        return e_failure;
    }

    printf("INFO: Files opened successfully.\n");

    // Step 2: Check image capacity
    if (check_capacity(encInfo) == e_failure)
    {
        fprintf(stderr, "ERROR: Image does not have enough capacity.\n");
        return e_failure;
    }

    // Step 3: Copy BMP header
    printf("INFO: Copying BMP header...\n");
    if (copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
    {
        fprintf(stderr, "ERROR: Failed to copy BMP header.\n");
        return e_failure;
    }

    // Step 4: Encode magic string
    printf("INFO: Encoding magic string...\n");
    if (encode_magic_string(MAGIC_STRING, encInfo) == e_failure)
    {
        fprintf(stderr, "ERROR: Failed to encode magic string.\n");
        return e_failure;
    }

    // Step 5: Encode secret file extension size
    printf("INFO: Encoding secret file extension size...\n");
    int extn_size = strlen(encInfo->extn_secret_file);
    if (encode_secret_file_extn_size(extn_size, encInfo) == e_failure)
    {
        fprintf(stderr, "ERROR: Failed to encode secret file extension size.\n");
        return e_failure;
    }

    // Step 6: Encode secret file extension
    printf("INFO: Encoding secret file extension...\n");
    if (encode_secret_file_extn(encInfo->extn_secret_file, encInfo) == e_failure)
    {
        fprintf(stderr, "ERROR: Failed to encode secret file extension.\n");
        return e_failure;
    }

    // Step 7: Encode secret file size
    printf("INFO: Encoding secret file size...\n");
    if (encode_secret_file_size(encInfo->size_secret_file, encInfo) == e_failure)
    {
        fprintf(stderr, "ERROR: Failed to encode secret file size.\n");
        return e_failure;
    }

    // Step 8: Encode secret file data
    printf("INFO: Encoding secret file data...\n");
    if (encode_secret_file_data(encInfo) == e_failure)
    {
        fprintf(stderr, "ERROR: Failed to encode secret file data.\n");
        return e_failure;
    }

    // Step 9: Copy remaining image data
    printf("INFO: Copying remaining image data...\n");
    if (copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
    {
        fprintf(stderr, "ERROR: Failed to copy remaining image data.\n");
        return e_failure;
    }

    printf("INFO: Encoding completed successfully!\n");
    fclose(encInfo->fptr_src_image);
    fclose(encInfo->fptr_secret);
    fclose(encInfo->fptr_stego_image);
    return e_success;
}
