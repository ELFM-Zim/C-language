#include <curl/curl.h>

int main()
{


    CURLcode result; 
   
    CURL *handler = curl_easy_init();

    if(handler)
    {

        curl_easy_setopt(handler, CURLOPT_URL, "https://ntfy.sh/elloah-ntfy");
        curl_easy_setopt(handler, CURLOPT_POSTFIELDS, "O MEU DEUS");
        result = curl_easy_perform(handler);
        if(result != CURLE_OK)
        {
            printf("ERROR: %s\n", curl_easy_strerror(result));
        }
        curl_easy_cleanup(handler);
    }

    return 0;
}
