/*
* Alex Benasutti
* CSC345-01
* October 30 2019
* Lab 9 Exercise 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_LINE 256

int num_frames;                     /* Number of frames for paging (1-7) */
int num_page_refs;                  /* Number of page references (1-80) */

int pf_fifo, pf_lru, pf_opt;        /* Page fault counts */

int hit(int frames[], int page_num)
{
    int hit = 0;
    for (int i=0;i<num_frames;++i)  /* Walk through frame array and try to match any pages to page_num */
    {
        if (frames[i] == page_num)
        {
            hit = 1;
            break;
        }
    }
    return hit;
}

void calc_pf_fifo(int pages[])
{
    int frames_fifo[num_frames];
    int i, j;
    int idx = 0;
    for (i=0;i<num_frames;++i) frames_fifo[i] = -1; /* Initialize frames to impossible value */
    for (i=0;i<num_page_refs;++i)
    {
        if (!hit(frames_fifo, pages[i]) && idx < num_frames) /* Fill frame list first */
        {
            frames_fifo[idx] = pages[i];
            idx++;
            pf_fifo++;
        }
        else if (!hit(frames_fifo, pages[i])) /* If page cannot be found within frames */
        {
            /* Deal with page fault */
            for (j=0;j<num_frames-1;j++) frames_fifo[j] = frames_fifo[j+1]; /* Push top out of stack */
            frames_fifo[j] = pages[i];              /* Place new val in bottom of stack */
            pf_fifo++;                              /* Increase fault count */
        }
        // else printf("No page fault - FIFO\n");
    }
}

void calc_pf_lru(int pages[])
{
    int frames_lru[num_frames];
    int i, j, k;
    int least[num_frames];
    int idx = 0;
    for (i=0;i<num_frames;++i) frames_lru[i] = -1; /* Initialize frames to impossible value */
    for (i=0;i<num_page_refs;++i)
    {
        if (!hit(frames_lru, pages[i]) && idx < num_frames) /* Fill frrame list first */
        {
            frames_lru[idx] = pages[i];
            idx++;
            pf_lru++;
        }
        else if (!hit(frames_lru, pages[i]))
        {
            /* Deal with page fault */
            for (j=0;j<num_frames;j++)  /* Go through all frames and the last use of each page */
            {
                int page_num = frames_lru[j];   /* Declare a page number from the frame */
                int found = 0;                  /* Was the page number found? */
                for (k=i-1;k>=0;k--)            /* Loop through current page ref back to the start */
                {
                    if (page_num == pages[k])   /* If page number found */
                    {
                        least[j] = k;           /* Save its most recent index */
                        found = 1;              /* Declare page as found and break loop */
                        break;
                    }
                    else found = 0;
                }
                if (!found) least[j] = -9999;   /* Declare index for unfound pages */
            }
            int min = 9999;                     /* Declare minimum distance */
            int replace_idx;                    /* Declare replacement index */
            for (j=0;j<num_frames;j++) /* Go through all frames again and find least recently used page */
            {
                if (least[j] < min)             /* Update min if page idx < min */
                {   
                    min = least[j];             /* smaller min == farther away from current page ref */
                    replace_idx = j;            /* Update replacement index */
                }
            }
            frames_lru[replace_idx] = pages[i]; /* Replace LRU page with current page */
            pf_lru++;                           /* Update page fault count */
        }
    }
}

void calc_pf_opt(int pages[])
{
    int frames_opt[num_frames];
    int i, j, k;
    int distance[num_frames];
    int idx = 0;
    for (i=0;i<num_frames;++i) frames_opt[i] = -1; /* Initialize frames to impossible value */
    for (i=0;i<num_page_refs;++i)
    {
        if (!hit(frames_opt, pages[i]) && idx < num_frames) /* Fill frame list first */
        {
            frames_opt[idx] = pages[i];
            idx++;
            pf_opt++;
        }
        else if (!hit(frames_opt, pages[i]))
        {
            /* Deal with page fault */
            for(j=0;j<num_frames;j++) /* Go through all frames and find their next pos in the page refs */
            {
                int page_num = frames_opt[j];   /* Declare a page number from the frame */
                int found = 0;                  /* Was the page number found? */
                for (k=i;k<num_page_refs;k++)   /* Loop from current page ref to the end */
                {
                    if (page_num == pages[k])   /* If frame page = one of the page refs */
                    {
                        distance[j] = k;        /* Save distance from current page ref to its next ref */
                        found = 1;              /* Declare page as found and exit loop */
                        break;
                    }
                    else found = 0;             /* Page was not found yet */
                }
                if (!found) distance[j] = 9999; /* Unfound page distance declaration */
            }
            int max = -9999;                    /* Declare max distance */
            int replace_idx;                    /* Declare replacement index */
            for (j=0;j<num_frames;j++) /* Go through all frames again and find the longest distance to next page ref */
            {
                if (distance[j] > max)          /* Update max if frame dist > current max */
                {
                    max = distance[j];          
                    replace_idx = j;            /* Update replacement index */
                }
            }
            frames_opt[replace_idx] = pages[i]; /* Replace frame with longest distance to next page ref */
            pf_opt++;                           /* Update page fault count */
        }
    }
}

int main(void)
{
    int buf[MAX_LINE], temp;
    FILE *input = fopen("input.txt","rt");
    fscanf(input, "%1d", &num_frames);  /* First value of input file is frame count */

    for (int i=0;i<MAX_LINE;++i)        /* Loop through input file */
    {
        fscanf(input, "%1d", &temp);    /* Take each integer and place it in an array */
        if (feof(input))                /* number of page refs = i at the end of input file */
        {
            num_page_refs = i;
            break;
        }
        buf[i] = temp;
    }

    fclose(input);                      /* close input */

    /* Some magic to calculate page faults */
    calc_pf_fifo(buf);
    calc_pf_lru(buf);
    calc_pf_opt(buf);

    /* Place each accumulated page fault value in an output file */
    FILE *fp = fopen("output.txt","wt");
    fprintf(fp,"FIFO: %d\n", pf_fifo);
    fprintf(fp,"LRU: %d\n", pf_lru);
    fprintf(fp,"Optimal: %d\n", pf_opt);
    fclose(fp);

    return 0;
}