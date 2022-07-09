#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void convert_8b_str(unsigned char *buf, unsigned char d_8b);
void convert_str_8b(unsigned char *buf, unsigned char* str);
void modulo_2(unsigned char *dividend, char *divisor, int size_dvd, int size_dvs);
int check_codeword_error(unsigned char* cw, int size_cw, int size_re);
void save_dw(unsigned char* dws, int *dwsp, int size_dw, unsigned char *cw);

int main(int argc, char **argv)
{
    if(argc != 6){
        fprintf(stderr, "usage: ./crc_decoder input_file output_file result_file generator dataword_size\n");
        return -1;
    }

    FILE *fin, *fout, *fresult;
    fin = fopen(argv[1], "rb");
    fout = fopen(argv[2], "wb");
    fresult = fopen(argv[3], "w");

    if(!fin){
        fprintf(stderr, "input file open error.\n");
        return -1;
    }
    if(!fout){
        fprintf(stderr, "output file open error.\n");
        return -1;
    }
    if(!fresult){
        fprintf(stderr, "result file open error.\n");
        return -1;
    }
    
    int size_dw = atoi(argv[5]);

    if(size_dw != 4 && size_dw != 8){
        fprintf(stderr, "dataword size must be 4 or 8.\n");
        return -1;
    }

    int size_gen = strlen(argv[4]);
    char *gen = (char*)malloc(sizeof(char)*size_gen);
    strncpy(gen, argv[4], sizeof(char)*size_gen);

    int size_re, size_cw;
    for(size_re=size_gen-1; size_re>=0; size_re--){
        if(gen[size_gen-size_re-1] == '1') break;
    }
    size_cw = size_dw + size_re;
    size_gen = size_re+1;

    unsigned char *cw = (unsigned char*)malloc(sizeof(unsigned char)*size_cw);
    unsigned char dws[8], cache[8], d_8b;
    int curp = 0, dwsp = 0;

    unsigned char buf, size_pad;
    int i, j, cnt_cw=0, cnt_err=0;
    fscanf(fin, "%c", &size_pad);

    if(size_pad != 0){
        fscanf(fin, "%c", &buf);
        convert_8b_str(cache, buf);
        for(i=size_pad; i<8; i++){
            cw[curp++] = cache[i];
        }
    }

    while(fscanf(fin, "%c", &buf) != -1){
        convert_8b_str(cache, buf);
        for(i=0; i<8; i++){
            cw[curp++] = cache[i];
            if(curp == size_cw) {
                modulo_2(cw, gen, size_cw, size_gen);
                cnt_err += check_codeword_error(cw, size_cw, size_re);
                save_dw(dws, &dwsp, size_dw, cw);
                if(dwsp == 8){
                    convert_str_8b(&d_8b, dws);
                    fwrite(&d_8b, sizeof(unsigned char), 1, fout);
                    dwsp = 0;
                }
                curp=0;
                cnt_cw++;
            }
        }
    }

    fprintf(fresult, "%d %d\n", cnt_cw, cnt_err);

    fclose(fin);
    fclose(fout);
    fclose(fresult);

    free(gen);
    free(cw);

    return 0;
}

void convert_8b_str(unsigned char *buf, unsigned char d_8b)
{
    for(int i=7; i>=0; i--){
        buf[i] = (d_8b%2)+'0';
        d_8b/=2;
    }
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

void modulo_2(unsigned char *dividend, char *divisor, int size_dvd, int size_dvs)
{
    int i = size_dvd-1, j;
    char *tmp = (char*)malloc(sizeof(char)*size_dvd);
    strncpy(tmp, (char*)dividend, size_dvd);

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

int check_codeword_error(unsigned char* cw, int size_cw, int size_re)
{
    int i, bit_sum = 0;
    for(i=0; i<size_re; i++){
        if(cw[size_cw-i-1] != '0') return 1;
    }
    return 0;
}

void save_dw(unsigned char* dws, int *dwsp, int size_dw, unsigned char *cw)
{
    int p = *dwsp, i;
    for(i=0; i<size_dw; i++){
        dws[p+i] = cw[i];
    }
    *dwsp = p+size_dw;
}