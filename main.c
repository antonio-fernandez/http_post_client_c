#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(void)
{
    struct stat info;
    const char *filename = "/home/antonio/CLionProjects/demo2019_ag_linux/X1_flat45.ntf";
    if (stat(filename, &info) != 0) {
        /* error handling */
    }
    printf("FILE SIZE: %lu\n", (unsigned long)info.st_size);

//    data from the file
    char *content = malloc(info.st_size);
    if (content == NULL) {
        /* error handling */
    }
//    FILE *fp = fopen(filename, "rb");
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        /* error handling */
    }
/* Try to read a single block of info.st_size bytes */
    size_t blocks_read = fread(content, info.st_size, 1, fp);
    if (blocks_read != 1) {
        /* error handling */
    }
    fclose(fp);

    printf("DATA LENGTH: %lu\n", (unsigned long)info.st_size);


    CURLcode res;
    CURL *curl = curl_easy_init();
    if(curl) {
        const char *data = "submit = 1";

        curl_easy_setopt(curl, CURLOPT_URL, "https://valohai.cloud/neonode/inference_server/server/20191023.2/inference_server");
//        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000/data");

        /* size of the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, info.st_size);

        /* pass in a pointer to the data - libcurl will not copy */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);

        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        } else
        {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            printf("Response code: %d\n",response_code);
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    return 0;
}