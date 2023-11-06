#include <stdio.h>
#include <curl/curl.h>

#define URL "https://www.google.com"
#define FILE_NAME "file.txt"

size_t WriteCallback(void *contents, size_t size, size_t nmeb, void *FILEptr)
{
    static int counter = 0;

    counter++;
    size_t realsize = size * nmeb;
    FILE * fp = (FILE *)FILEptr;

    if (fp)
    {
        printf("Writing data...");
        printf("Counter: %d\n", counter);
        fwrite(contents, size, realsize, fp);
    }
    else
    {
        fprintf(stdout, "Failed to open the file.\n");
        return -1;
    }

    return realsize;
}

int main(void)
{
    // opening file to get output
    FILE *file = fopen(FILE_NAME, "w");
    if (file) 
    {
        // initializing CURL modules
        curl_global_init(CURL_GLOBAL_ALL);
        CURL *handle = curl_easy_init();

        // configuring the handler
        curl_easy_setopt(handle, CURLOPT_URL, URL);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteCallback);

        // checking for errors
        CURLcode result = curl_easy_perform(handle);
        if (result != CURLE_OK)
        {
            fprintf(
                stderr,
                "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(result));

            return -1;
        }

        // closing file
        fclose(file);

        // closing cURL modules
        curl_easy_cleanup(handle);
        curl_global_cleanup();
    }
    else
    {
        fprintf(stderr, "Failed to open the file.\n");
    }

    return 0;
}
