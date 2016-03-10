#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct particle{
	int color;
	double radius;
	double rx;
	double ry;
	double vx;
	double vy;
	double mass;
	int count;

}particle;

double rnd(int max, int min)
{
	int res=1000;
	int r = (rand() % ((max*res)+res-(min*res))+(min*res));
	return (r/res);
}


void init(particle *p)
{
	p->mass=1;
	p->rx=((double)rand()/(double)RAND_MAX);
	p->ry=((double)rand()/(double)RAND_MAX);
	p->vx=rnd(-10,10); 
	p->vy=rnd(-10,10); 
	p->count=0;

}

void bounceOff(particle *a, particle *b) {
        double dx  = b->rx - a->rx;
        double dy  = b->ry - a->ry;
        double dvx = b->vx - a->vx;
        double dvy = b->vy - a->vy;
        double dvdr = dx*dvx + dy*dvy;             // dv dot dr
        double dist = a->radius + b->radius;   // distance between particle centers at collison

        // normal force F, and in x and y directions
        double F = 2 * a->mass * b->mass * dvdr / ((a->mass + b->mass) * dist);
        double fx = F * dx / dist;
        double fy = F * dy / dist;

        // update velocities according to normal force
        a->vx += fx / a->mass;
        a->vy += fy / a->mass;
        b->vx -= fx / b->mass;
        b->vy -= fy / b->mass;

        // update collision counts
        a->count++;
        b->count++;
    }

void move(particle *p,double dt) {
        p->rx += p->vx * dt;
        p->ry += p->vy * dt;
    }

void main()
{
	srand(time(NULL));

}