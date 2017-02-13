#include <stdio.h>
#include <openssl/aes.h>
#include <string.h>
#include <iostream>

using namespace std;

// Some changes
static void hex_print(const void* pv, size_t len)
{
    const unsigned char * p = (const unsigned char*)pv;
    if (NULL == pv)
        printf("NULL");
    else
    {
        size_t i = 0;
        for (; i<len;++i)
            printf("%02X ", *p++);
    }
    printf("\n");
}

const static unsigned char aes_key[]={"passwordaaaaaaa"}; //15 characters + \0

int main(int argc, char **argv) {

    std::string input;
    if (argc == 2)
        input = argv[1];
    
    //cout<< "Enter a string:";
    //getline(cin, input);
    
    unsigned char aes_input[input.length()+1];
    copy( input.begin(), input.end(), aes_input );
    if (aes_input[input.length() == '\n'])
        aes_input[input.length()] = '\0';
    
    //unsigned char aes_input[]="Hello World 1235 sfljsdf sljgd sljfg fslg21242 dfgljdfg 098fgjljsg jkhsdfah sfkjhskafsd ksafhs df sdafkjhsad fshadf sdakjh sdafsdfjhsadf sdakh dskfjhdsfkjhdsa fkhdsfk sadfkh ksafdh sdfak adfskj hsdfjkh adsjfk hdsaf kjhadsfk hksadf sdfkjhadf sdaf sadfkjhsaf sd sdfkjh dsf sfkhf  sdfkjsf 8798saf sfkh sakfs skfg a00000000sdf askfhs df000dfag ljl agfd00000afsg lajsgl jsaglkja slgkjaslkgj alskgsaglkjasg lkgasklgjalskg aslg aslkglas glkasg900909dg00000 00000 sdkfhsad fksajfhds fh sdfkjh sadkfhds fks ajdhsadkfjhaks dfsadkfjhsad jkfhskjf sdaf kjsdhafk hsdafkj hdsfkjads f sdafkjhsdaf kjhdfs kjsdafh kjsdhf kjsf ksadfhkasjd fkjasdf jkdsafhjkdsa fkjasd fkjhadf kjasfdh sadkfhads kfjhsakjdfh sajkdfh jksadfh asjkdfh sajkdf skajdfhsakjdfgh asjkdgh kajsg kjasg jkashdg kjahsg kjsahdg kj sakjdgh ksaghsak ghsak gds";
 
    unsigned char enc_out[AES_BLOCK_SIZE * ((sizeof(aes_input) + AES_BLOCK_SIZE)/AES_BLOCK_SIZE)];
    unsigned char dec_out[sizeof(aes_input)];
    unsigned char iv[AES_BLOCK_SIZE] = {0};
    
    AES_KEY enc_key,dec_key;
    AES_set_encrypt_key(aes_key,sizeof(aes_key)*8,&enc_key);
    AES_cbc_encrypt(aes_input,enc_out,sizeof(aes_input),&enc_key,iv,AES_ENCRYPT);
    
    //decryption
    memset(iv,0x00,AES_BLOCK_SIZE);
    AES_set_decrypt_key(aes_key,sizeof(aes_key)*8,&dec_key);
    AES_cbc_encrypt(enc_out,dec_out,sizeof(aes_input),&dec_key,iv,AES_DECRYPT);
    
    //verify
    printf("original %s\n",aes_input);
    hex_print(enc_out, sizeof enc_out);
    printf("decrypted %s\n",dec_out);
    return 0;
}
