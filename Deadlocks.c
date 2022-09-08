/*
 Name: Rasandeep Singh Panag
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <semaphore.h>

#define TEAM 5
#define DELAYS 5000
#define PRACTICE 100

#define TEAM 5
#define DELAYS 5000
#define PRACTICE 100

void *team (void *id);
void grab_threewickets (int, int, char *);
void down_threewickets (int, int);
int wickets_on_ground ();
int get_token();
void return_token();

pthread_mutex_t threewickets[TEAM];
pthread_t tme[TEAM];
pthread_mutex_t threewickets_set_lock;
int sleep_seconds = 0;
sem_t num_can_practice;


int
main (int argn,
      char **argv)
{
    int i;

    pthread_mutex_init (&threewickets_set_lock, NULL);
    sem_init(&num_can_practice, 0, TEAM - 1);
    for (i = 0; i < TEAM; i++)
        pthread_mutex_init (&threewickets[i], NULL);
    for (i = 0; i < TEAM; i++)
        pthread_create (&tme[i], NULL, team, (void *)i);
    for (i = 0; i < TEAM; i++)
        pthread_join (tme[i], NULL);
    return 0;
}

void *team (void *num)
{
    int id;
    int i, left_threewickets, right_threewickets, f;

    id = (int)num;
    printf ("Team %d is done thinking and now ready to Practice.\n", id);
    right_threewickets = id;
    left_threewickets = id + 1;

    if (left_threewickets == TEAM)
        left_threewickets = 0;

    while (f = wickets_on_ground ()) {
        get_token ();

        grab_threewickets (id, right_threewickets, "right ");
        grab_threewickets (id, left_threewickets, "left");

        printf ("Team %d: done.\n", id);
        usleep (DELAYS * (PRACTICE - f + 1));
        down_threewickets (left_threewickets, right_threewickets);

        return_token ();
    }

    printf ("Team %d is done practicing.\n", id);
    return (NULL);
}

int wickets_on_ground ()
{
    static int practice = PRACTICE;
    int teampractice;

    pthread_mutex_lock (&threewickets_set_lock);
    if (practice > 0) {
        practice--;
    }
    teampractice = practice;
    pthread_mutex_unlock (&threewickets_set_lock);
    return teampractice;
}

void
grab_threewickets (int tam,
                int s,
                char *side)
{
    pthread_mutex_lock (&threewickets[s]);
    printf ("Team %d: got %s threewickets %d\n", tam, side, s);
}

void down_threewickets (int s1,int s2)
{
    pthread_mutex_unlock (&threewickets[s1]);
    pthread_mutex_unlock (&threewickets[s2]);
}


int get_token ()
{
    sem_wait(&num_can_practice);
}

void return_token ()
{
    sem_post(&num_can_practice);
}
