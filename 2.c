#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Track Track;

struct Track
{
    char track_name[50];
    char composer_name[50];
    char track_media_type[5];
    char album[50];
    int track_duration_seconds;
    Track *next;
};

void print_tracks(Track *track, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\nTrack %d:\n", i + 1);
        printf("Track name: %s\n", track[i].track_name);
        printf("Composer: %s\n", track[i].composer_name);
        printf("Media type: %s\n", track[i].track_media_type);
        printf("Album: %s\n", track[i].album);
        printf("Duration (seconds): %d\n", track[i].track_duration_seconds);
    }
}

void search_track_by_composer(Track *track, int count, char search_input[50])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(track[i].composer_name, search_input) == 0)
        {
            printf("\nElement found at position: %d\n\n", i + 1);
            printf("Name: %s\n", track[i].track_name);
            printf("Composer: %s\n\n", track[i].composer_name);
            break;
        }
    }
}

int compare(const void *a, const void *b) // for qsort()
{
    Track *trackA = (Track *)a;
    Track *trackB = (Track *)b;
    return (trackB->track_duration_seconds - trackA->track_duration_seconds);
}

void input_track_info(Track *new_track)
{
    printf("Track name: ");
    scanf("%s", new_track->track_name);
    printf("Composer: ");
    scanf("%s", new_track->composer_name);
    printf("Media type: ");
    scanf("%s", new_track->track_media_type);
    printf("Album: ");
    scanf("%s", new_track->album);
    printf("Duration (seconds): ");
    scanf("%d", &new_track->track_duration_seconds);
}

void add_track_at_beginning(Track **tracks, int *count, Track new_track)
{
    Track *new_tracks = malloc((*count + 1) * sizeof(Track));
    new_tracks[0] = new_track;
    for (int i = 0; i < *count; i++)
    {
        new_tracks[i + 1] = (*tracks)[i];
    }
    free(*tracks);
    *tracks = new_tracks;
    (*count)++;
}

void add_track_at_end(Track **tracks, int *count, Track new_track)
{
    Track *new_tracks = malloc((*count + 1) * sizeof(Track));
    for (int i = 0; i < *count; i++)
    {
        new_tracks[i] = (*tracks)[i];
    }
    new_tracks[*count] = new_track;
    free(*tracks);
    *tracks = new_tracks;
    (*count)++;
}

void free_list(Track **track, int track_count)
{
    for (int i = 0; i < track_count; i++)
    {
        free((*track)[i].next);
    }
    free(*track);
    *track = NULL;
}

int main()
{
    int track_count = 0;
    Track *track = malloc(track_count * sizeof(Track));
    
    int n;
    do
    {
        printf("Menu:\n");
        printf(" 1| Print tracks\n");
        printf(" 2| Search tracks\n");
        printf(" 3| Sort tracks by duration\n");
        printf(" 4| Add track at beginning\n");
        printf(" 5| Add track at end\n");
        printf(" 6| Free list\n");
        printf(" 0| Exit\n");
        printf("\nYour selection:\n");
        scanf(" %d", &n);
        switch (n)
        {
        case 1:
            print_tracks(track, track_count);
            break;
        case 2:
        {
            char search_input[50];
            printf("\nInput composer to search: ");
            scanf("%s", search_input);
            search_track_by_composer(track, track_count, search_input);
            break;
        }
        case 3:
            qsort(track, track_count, sizeof(Track), compare);

            printf("After sort:\n");
            for (int i = 0; i < track_count; i++)
            {
                printf("Name: %-14s\tDuration: %-5d seconds\n", track[i].track_name, track[i].track_duration_seconds);
            }
            break;
        case 4:
        {
            Track new_track;
            printf("Input track at the beginning:\n");
            input_track_info(&new_track);
            add_track_at_beginning(&track, &track_count, new_track);
            printf("\n");
            break;
        }
        case 5:
        {
            Track new_track;
            printf("Input track at the end:\n");
            input_track_info(&new_track);
            add_track_at_end(&track, &track_count, new_track);
            printf("\n");
            break;
        }

        case 6:
            free_list(&track, track_count);
            track = NULL;
            track_count = 0;
            break;
        case 0:
            printf("exit . . .");
            exit(1);
            break;
        default:
            printf("invalid option.");
            break;
        }
    } while (n != 0);

    return 0;
}
