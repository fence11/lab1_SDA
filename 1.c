#include <stdio.h>
#include <string.h>

typedef struct
{
    char track_name[50];
    char composer_name[50];
    char track_media_type[5]; // M4A - FLAC - MP3 - WAV - WMA - AAC
    char album[50];
    int track_duration_seconds;
} Track;

void search_track(Track *track, int count)
{
    char search_input[15];
    printf("\nEnter track composer to search: "); // search by composer . . . etc
    scanf("%s", search_input);
    getchar();

    for (int i = 0; i < count; i++)
    {
        if (strcmp(track[i].composer_name, search_input) == 0)
        {
            printf("\nFirst element found at position %d\n\n", i);
            printf("Name: %s\n", track[i].track_name);
            printf("Composer: %s\n", track[i].composer_name);
            printf("Media Type: %s\n", track[i].track_media_type);
            printf("Album: %s\n", track[i].album);
            printf("Duration (seconds): %d\n", track[i].track_duration_seconds);
            break;
        }
    }
}

int main()
{
    Track track[3];

    for (int i = 0; i < 3; i++)
    {
        printf("Enter details for Track %d:\n", i + 1);
        printf("Track name: ");
        scanf("%s", track[i].track_name);
        printf("Composer: ");
        scanf("%s", track[i].composer_name);
        printf("Album: ");
        scanf("%s", track[i].album);
        printf("Media type (max 5 chars): ");
        scanf("%s", track[i].track_media_type);
        printf("Duration (seconds): ");
        scanf("%d", &track[i].track_duration_seconds);
    }

    for (int i = 0; i < 3; i++)
    {
        printf("\nTRACK %d\n", i + 1);
        printf("Name: %s\n", track[i].track_name);
        printf("Composer: %s\n", track[i].composer_name);
        printf("Media type: %s\n", track[i].track_media_type);
        printf("Album: %s\n", track[i].album);
        printf("Duration: %d seconds\n", track[i].track_duration_seconds);
    }

    search_track(track, 3);

    return 0;
}
