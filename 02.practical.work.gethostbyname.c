#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    char domain[256];

    // Get domain name from argument or stdin
    if (argc > 1) {
        strncpy(domain, argv[1], sizeof(domain));
        domain[sizeof(domain)-1] = '\0';
    } else {
        printf("Enter domain name: ");
        if (fgets(domain, sizeof(domain), stdin) == NULL) {
            fprintf(stderr, "Failed to read domain.\n");
            return 1;
        }
        domain[strcspn(domain, "\n")] = 0;  // Remove newline
    }

    // Use gethostbyname
    struct hostent *host = gethostbyname(domain);
    if (host == NULL) {
        herror("gethostbyname");
        return 1;
    }

    printf("IP addresses for %s:\n", domain);
    for (int i = 0; host->h_addr_list[i] != NULL; i++) {
        struct in_addr *addr = (struct in_addr *) host->h_addr_list[i];
        printf("  - %s\n", inet_ntoa(*addr));
    }

    return 0;
}
