#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "system.h"
#include "sample.h"
#include "ran_uniform.h"

#define CycleMultiplication 1000

enum{UP=1,DOWN=-1};
enum{RIGHT=1,LEFT=-1};
enum{EMPTY=-1};

// Random Walk 2d

int main(void)
{
  int NumberOfJumps,NumberOfInitializationSteps;
  int i,j,k,l,dx,dy,xpos_new,ypos_new,xpos,ypos;
  int LatticeSize;
  double Sum,Count,Rm;

  // initialize the random number generator with the system time
  InitializeRandomNumberGenerator(time(0l));

  Sample(INITIALIZE);

  printf("Number of jumps (x %d) ? ",CycleMultiplication);
  fscanf(stdin,"%d",&NumberOfJumps);

  printf("Lattice size           ? ");
  fscanf(stdin,"%d",&LatticeSize);
  if(LatticeSize<10||LatticeSize>MAX_LATTICE)
  {
    printf("Input parameter error, should be\n");
    printf("\tLattice size [10-%d]\n",MAX_LATTICE);
    exit(0);
  }

  printf("Number of particles  ? ");
  fscanf(stdin,"%d",&NumberOfParticles);
  if(NumberOfParticles<1||NumberOfParticles>=MAX_PARTICLES)
  {
    printf("Input parameter error, should be\n");
    printf("\tNumber of particles [1-%d]\n",MAX_PARTICLES);
    exit(0);
  }


  for(i=0;i<MAX_LATTICE;i++)
    for(j=0;j<MAX_LATTICE;j++)
      Lattice[i][j]=EMPTY;

  for(i=0;i<MAX_PARTICLES;i++)
  {
    Particle[i].posx=0;
    Particle[i].posy=0;
    Mxx[i]=0;
    Myy[i]=0;
  }

  Sum=0.0;
  Count=0.0;
  NumberOfInitializationSteps=NumberOfJumps/4;

  // put particles on the lattice randomly

  for(j=0;j<NumberOfParticles;j++)
  {
    do
    {
      xpos=RandomNumber()*LatticeSize;
      ypos=RandomNumber()*LatticeSize;
    }
    while(Lattice[xpos][ypos]>=0);

    Lattice[xpos][ypos]=j;
    Particle[j].posx=xpos;
    Particle[j].posy=ypos;
    Mxx[j]=xpos;
    Myy[j]=ypos;
  }
         
  // perform the random walk
  for(k=0;k<NumberOfJumps;k++)
  {
    for(l=0;l<CycleMultiplication;l++)
    {
      // Choose a random site (j)
      // Choose a random displacement (Rm)

      j=RandomNumber()*NumberOfParticles;
      Rm=4.0*RandomNumber();

//    MODIFICATION
//    Question 3: to favour displacement of the diffusion in x direction, 
//    change the cutoffs to 1.5, 3.0, 3.5, respectively
//    (for example). 

      dx=dy=0;

      if(Rm<1.0)
        dx=RIGHT;
      else if(Rm<2.0)
        dx=LEFT;
      else if(Rm<3.0)
        dy=UP;
      else
        dy=DOWN;

      // new position

//    MODIFICATION
//    Question 5: if particle is fixed, don't move it:
/*    if(j<Nfixed)
      {
      xpos_new=Particle[j].posx;
      ypos_new=Particle[j].posy;
      }
      else
      {
*/    xpos_new=Particle[j].posx+dx;
      ypos_new=Particle[j].posy+dy;
//    }
//    Don't forget to declare Nfixed.     

      // If the new position is outside of the lattice boundaries, 
      // use periodic boundary conditions: put particle back on the lattice.
      if(xpos_new<0)
        xpos_new+=LatticeSize;
      else if(xpos_new>=LatticeSize)
        xpos_new-=LatticeSize;

      if(ypos_new<0)
        ypos_new+=LatticeSize;
      else if(ypos_new>=LatticeSize)
        ypos_new-=LatticeSize;

      // Check if new lattice site is occupied.
      // If it is empty, accept the new position.
      if(Lattice[xpos_new][ypos_new]==EMPTY)
      {
        Lattice[Particle[j].posx][Particle[j].posy]=EMPTY;
        Particle[j].posx=xpos_new;
        Particle[j].posy=ypos_new;
        Lattice[xpos_new][ypos_new]=j;
        Mxx[j]+=dx;
        Myy[j]+=dy;
        if(k>NumberOfInitializationSteps) 
          Sum+=1.0;
      }

//    MODIFICATION
//    Question 4: instead of above code, use the following.
//    The periodic boundary conditions in the y direction have been removed,
//    and the displacement is only accepted for movements that keep the 
//    particle on the lattice.
//
/*      if(xpos_new<0)
        xpos_new+=LatticeSize;
      else if(xpos_new>=LatticeSize)
        xpos_new-=LatticeSize;
      
      if(Lattice[xpos_new][ypos_new]==EMPTY&&ypos_new<LatticeSize&&ypos_new>=0)
      {
        Lattice[Particle[j].posx][Particle[j].posy]=EMPTY;
        Particle[j].posx=xpos_new;
        Particle[j].posy=ypos_new;
        Lattice[xpos_new][ypos_new]=j;
        Mxx[j]+=dx;
        Myy[j]+=dy;
        if(k>NumberOfInitializationSteps)
          Sum+=1.0;
      }
*/
     if(k>NumberOfInitializationSteps) 
      {
        Count+=1.0;
        Sample(SAMPLE_WALK);
      }
    }
  }

  Sample(WRITE_RESULTS);
  printf("Fraction Accepted Jumps : %f\n",Sum/Count);
  printf("Lattice Occupation      : %f\n",(double)NumberOfParticles/SQR(LatticeSize));

  return 0;
}
