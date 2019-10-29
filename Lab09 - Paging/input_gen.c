#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGES 10
#define MAX_LINE 80
#define MAX_FRAME 7

/* Create a randomized page frame count from 1 to 7 */
/* Create a randomized reference string of random integers from range 0 to 9 */
int main(void)
{
    srand(time(NULL));

    FILE *fp = fopen("input.txt","wt");

    int num_frames = rand() % MAX_FRAME + 1;
    fprintf(fp, "%d\n", num_frames);

    int ref_str_len = rand() % MAX_LINE + 1;
    for (int i=0;i<ref_str_len;++i)
    {
        fprintf(fp, "%d ", rand() % MAX_PAGES);
    }
    fprintf(fp, "\n");

    fclose(fp);

    return 0;
}