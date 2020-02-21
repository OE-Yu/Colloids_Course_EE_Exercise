#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "system.h"
#include "sample.h"


// T_MAX  = maximum timesteps for the correlation time
// T0_MAX = maximum number of time origins

#define T_MAX 500
#define T0_MAX 50

void Sample(int Switch)
{
  int Ttel,i,j,Dt;
  static int T0,Tvacf;
  static double Nvacf[T_MAX],MsdX[T_MAX],MsdY[T_MAX];
  static int OriginX[MAX_PARTICLES][T0_MAX],OriginY[MAX_PARTICLES][T0_MAX],Tt0[T0_MAX];
  FILE *FilePtr;
       
  switch(Switch)
  {
    // Initialize Everything
    case INITIALIZE:
      Tvacf=0;
      T0=0;
      for(i=0;i<T_MAX;i++)
      {
        MsdX[i]=0.0;
        MsdY[i]=0.0;
        Nvacf[i]=0.0;
      }
      break;
    case SAMPLE_WALK:
      // new time origin
      // store particle positions/velocities
      Tvacf++;
      if((Tvacf%50)==0)
      {
        T0++;
        Ttel=(T0-1)%T0_MAX;
        Tt0[Ttel]=Tvacf;
        for(i=0;i<NumberOfParticles;i++)
        {
          OriginX[i][Ttel]=Mxx[i];
          OriginY[i][Ttel]=Myy[i];
        }
      }

      // loop over all time origins
      for(j=0;j<MIN(T0,T0_MAX);j++)
      {
        Dt=Tvacf-Tt0[j];
        if (Dt<T_MAX)
        {
          Nvacf[Dt]+=1.0;
          for(i=0;i<NumberOfParticles;i++)
          {
            MsdX[Dt]+=SQR(Mxx[i]-OriginX[i][j]);
            MsdY[Dt]+=SQR(Myy[i]-OriginY[i][j]);
          }
        }
      }
      break;
    case WRITE_RESULTS:
      // write everything to file
      FilePtr=fopen("rms.dat","w");
      for(i=0;i<T_MAX;i++)
      {
        if(Nvacf[i]>0.5)
        {
          MsdX[i]/=(Nvacf[i]);
          MsdY[i]/=(Nvacf[i]);
        }
        else
        {
          MsdX[i]=0.0;
          MsdY[i]=0.0;
        }
        fprintf(FilePtr,"%d %f %f\n",i,MsdX[i],MsdY[i]);
      }
  }
}

