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
        printf("track name: %s\n", track[i].track_name);
        printf("composer: %s\n", track[i].composer_name);
        printf("media type: %s\n", track[i].track_media_type);
        printf("album: %s\n", track[i].album);
        printf("duration (seconds): %d\n", track[i].track_duration_seconds);
    }
}

void search_track_by_composer(Track *track, int count)
{
    char search_input[15];
    printf("\ninput composer to search: ");
    scanf("%s", search_input);
    getchar();

    for (int i = 0; i < count; i++)
    {
        if (strcmp(track[i].composer_name, search_input) == 0)
        {
            printf("\nelement found at position: %d\n\n", i + 1);
            printf("name: %s\n", track[i].track_name);
            printf("composer: %s\n", track[i].composer_name);
            break;
        }
    }
}

int compare(const void *a, const void *b)
{
    Track *trackA = (Track *)a;
    Track *trackB = (Track *)b;
    return (trackB->track_duration_seconds - trackA->track_duration_seconds);
}

void input_track_info(Track *new_track)
{
    printf("track name: ");
    scanf("%s", new_track->track_name);
    printf("composer: ");
    scanf("%s", new_track->composer_name);
    printf("media type: ");
    scanf("%s", new_track->track_media_type);
    printf("album: ");
    scanf("%s", new_track->album);
    printf("duration (seconds): ");
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

int main()
{
    int track_count = 10;
    Track *track = malloc(track_count * sizeof(Track));

    Track predefined_tracks[10] = {
        {"track1", "comp_1", "WAV", "album_1", 465, NULL},
        {"track2", "comp_2", "MP3", "album_2", 231, NULL},
        {"track3", "comp_1", "WAV", "album_2", 661, NULL},
        {"track4", "comp_3", "WAV", "album_3", 211, NULL},
        {"track5", "comp_2", "MP3", "album_2", 289, NULL},
        {"track6", "comp_2", "MP3", "album_3", 129, NULL},
        {"track7", "comp_1", "WAV", "album_3", 372, NULL},
        {"track8", "comp_1", "WAV", "album_2", 273, NULL},
        {"track9", "comp_3", "WAV", "album_1", 249, NULL},
        {"track10", "comp_2", "MP3", "album_2", 332, NULL}};

    for (int i = 0; i < track_count; i++)
    {
        track[i] = predefined_tracks[i];
    }

    int n;
    do
    {
        printf("Menu:\n");
        printf(" 1| Print tracks\n");
        printf(" 2| Search tracks\n");
        printf(" 3| Sort tracks by duration\n");
        printf(" 4| Add track at beginning\n");
        printf(" 5| Add track at end\n");
        printf(" 6| Exit\n");
        printf("\nYour selection:\n");
        scanf(" %d", &n);
        switch (n)
        {
        case 1:
            print_tracks(track, track_count);
            break;
        case 2:
            search_track_by_composer(track, track_count);
            break;
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
            printf("input track at the beginning:\n");
            input_track_info(&new_track);
            add_track_at_beginning(&track, &track_count, new_track);
            printf("Success\n");
            break;
        }
        case 5:
        {
            Track new_track;
            printf("input track at the end:\n");
            input_track_info(&new_track);
            add_track_at_end(&track, &track_count, new_track);
            printf("Success\n");
            break;
        }
        case 0:
            printf("exit . . .");
            exit(1);
            break;
        default:
            printf("invalid option.");
            break;
        }
    } while (n != 0);

    free(track);

    return 0;
}
