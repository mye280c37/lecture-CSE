#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OutBufSize 8

char* make_codeword(char dw_b, char *gen, int size_dw, int size_re);
void modulo_2(char *dividend, char *divisor, int size_dvd, int size_dvs);
void convert_str_8b(unsigned char *buf, unsigned char* str);

int main(int argc, char **argv)
{
    if(argc != 5){
        fprintf(stderr, "usage: ./crc_decoder input_file output_file result_file generator dataword_size\n");
        return -1;
    }

    FILE *fin, *fout;
    fin = fopen(argv[1], "rb");
    fout = fopen(argv[2], "wb");
    
    if(!fin){
        fprintf(stderr, "input file open error.\n");
        return -1;
    }
    if(!fout){
        fprintf(stderr, "output file open error.\n");
        return -1;
    }

    int size_dw = atoi(argv[4]);

    if(size_dw != 4 && size_dw != 8){
        fprintf(stderr, "dataword size must be 4 or 8.\n");
        return -1;
    }

    int size_gen = strlen(argv[3]);
    char *gen = (char*)malloc(sizeof(char)*size_gen);
    strncpy(gen, argv[3], sizeof(char)*size_gen);

    int size_re, size_cw;
    for(size_re=size_gen-1; size_re>=0; size_re--){
        if(gen[size_re] == '1') break;
    }
    size_cw = size_dw + size_re;
    size_gen = size_re+1;

    const unsigned char con_1b = 1; 
    unsigned char data_8b, out_buf=0, tmp, cache[8];
    int cnt_dw = 0, cachep = 0, i, j;

    fseek(fin, 0L, SEEK_END);
    cnt_dw = ftell(fin);
    fseek(fin, 0L, SEEK_SET);
    
    if(size_dw == 4) cnt_dw*=2;

    unsigned char size_pad = 8-(cnt_dw*size_cw%8);
    if(size_pad == 8) size_pad = 0;

    fwrite(&size_pad, 1, sizeof(unsigned char), fout);

    for(i=0; i<size_pad; i++){
        cache[cachep++] = '0';
    }

    int num_process = size_dw==8? 1: 2;
    
    while(fscanf(fin, "%c", &data_8b) != -1){
        tmp = data_8b;
        if(size_dw == 4) data_8b >>= 4;
        for(j=0; j<num_process; j++){
            char *cw = make_codeword(data_8b, gen, size_dw, size_re);
            for(i=0; i<size_cw; i++){
                cache[cachep++] = cw[i];
                if(cachep == 8){
                    convert_str_8b(&out_buf, cache);
                    fwrite(&out_buf, 1, sizeof(unsigned char), fout);
                    cachep = 0;
                }
            }
            free(cw);
            if(size_dw == 4) data_8b = tmp^(data_8b<<4);
        }
    }

    fclose(fin);
    fclose(fout);

    free(gen);

    return 0;
}

char* make_codeword(char dw_b, char *gen, int size_dw, int size_re)
{
    int i;
    int size_cw = size_dw+size_re;
    int size_ge = size_re+1;
    char *cw = (char*)malloc(sizeof(char)*size_cw);

    for(i=size_cw-1; i>=size_cw-size_re; i--){
        cw[i] = '0';
    }
    for(i=size_dw-1; i>=0; i--){
        cw[i] = (dw_b%2)+'0';
        dw_b /= 2;
    }

    modulo_2(cw, gen, size_cw, size_ge);

    return cw;
}

void modulo_2(char *dividend, char *divisor, int size_dvd, int size_dvs)
{
    int i = size_dvd-1, j;
    char *tmp = (char*)malloc(sizeof(char)*size_dvd);
    strncpy(tmp, dividend, size_dvd);

    for(i=0; i<=size_dvd-size_dvs; i++){
        if(tmp[i] == '0') continue;
        for(j=0; j<size_dvs; j++){
            tmp[i+j] = ((tmp[i+j]-'0')^(divisor[j]-'0'))+'0';
        }
    }
    for(i=size_dvd-size_dvs+1; i<size_dvd; i++){
        dividend[i] = tmp[i];
    }
    free(tmp);
}

void convert_str_8b(unsigned char *buf, unsigned char* str)
{
    const unsigned char con_1b = 1;
    unsigned char d_8b = 0; 
    for(int i=0; i<8; i++){
        d_8b <<= 1;
        if(str[i] == '1') d_8b += con_1b;
    }
    *buf = d_8b;
}