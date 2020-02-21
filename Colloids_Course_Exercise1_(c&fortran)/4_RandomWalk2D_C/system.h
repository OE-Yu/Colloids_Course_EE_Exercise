#define MAX_LATTICE  65 
#define MAX_PARTICLES 2000

#define SQR(x) ((x)*(x))
#define MIN(x,y) ((x)<(y)?(x):(y))

typedef struct
{
  int posx;
  int posy;
} position;

extern int Lattice[MAX_LATTICE][MAX_LATTICE];
extern position Particle[MAX_PARTICLES];
extern int Mxx[MAX_PARTICLES];
extern int Myy[MAX_PARTICLES];
extern int NumberOfParticles;
