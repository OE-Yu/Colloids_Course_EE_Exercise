def distribute_particles_over_compartments(N, P, particles_in_compartment):
    """
    N: Number of particles
    P: Number of compartments
    particles_in_compartment: array containing the number of particles per compartment
    
    Instructions:
    - Loop over all particles, pick a random compartment, and add a particle to it.
    - A random integer in the interval [0,N] can be generated using randint(0, N).
    
    NB: A python array with N elements is indexed from 0 to N-1     
    """
    for i in range(N):
        random_index = randint(0, P - 1)
        particles_in_compartment[random_index] += 1
        
    return particles_in_compartment  