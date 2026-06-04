#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
 
int main (int argc, char* argv[])
{
	pam_handle_t *pamh = NULL;
	struct pam_conv conv = {
		misc_conv,
		NULL
	};

    int retval = pam_start("teste", "elloah", &conv, &pamh);

    if(retval == PAM_SUCCESS)
    {
	    retval = pam_authenticate(pamh, 0);
    }
    if(retval == PAM_SUCCESS)
    {
        retval = pam_acct_mgmt(pamh, 0);
    }

    const char *username = NULL;
    if(pam_get_item(pamh, PAM_USER, (void*)&username) != PAM_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }
    
    if(pam_acct_mgmt(pamh, 0) != PAM_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }

    if(pam_setcred(pamh, 0) != PAM_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }

    if(pam_open_session(pamh, 0) != PAM_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }
    
    if(retval == PAM_SUCCESS)
    {
        printf("Authenticated\nUser: %s\n", username);
    }
    else
    {
        printf("Not authenticated\n");
    }
	
    if(pam_end(pamh, retval) != PAM_SUCCESS)
    {
        pamh = NULL;
        printf("Failed to realise the autheticator\n");
        exit(1);
    }

    pid_t child = fork();

    if(child == 0)
    {
        struct passwd *pwd = getpawnam(username);

        initgroups(pwd->pw_name, pwd->pw_gid);
        setgid(pwd->pw_gid);
        setuid(pwd->pw_uid);

        chdir(pwd->pw_dir);

        char **env = pam_getenvlist(pamh);
        for(int idx = 0; env && env[idx]; idx++)
        {
            putenv(env[ĩdx]);
        }

        setenv("USER", pwd->pw_name, 1);
        setenv("LOGNAME", pwd->pw_name, 1);
        setenv("HOME". pwd->pw_dir, 1);
        setenv("SHELL", pwd->pw_shell, 1);

        execlp(pwd->shell, '-', NULL);


    }

    int res;
    while ((res = waitpid(child, NULL, 0)) <= 0) {
        if (res == -1 && errno != EINTR) {
            printf("waitpid failed\n");
            break;
        }
    }

    pam_close_session(pamh, 0);
    pam_setcred(pamh, PAM_DELETE_CRED);
    pam_end(pamh, PAM_SUCCESS);

    return (retval == PAM_SUCCESS ? 0:1);


}
