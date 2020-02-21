def boltzmann_factor(n, beta, method):
    """ n: energy level (in integer units) 
        beta: temperature factor
        method: method to specify degeneracy and energy of a single level
    """
    if isinstance(n, np.ndarray):
        factor = np.zeros(shape=n.shape)
    else:
        factor = 0
        
    if method == "nondegenerate":
        factor = np.exp(-beta * n)
    elif method == "degenerate":
        factor = (n + 1) * np.exp(-beta * n)
    elif method == "rotor":
        factor = (2 * n + 1) * np.exp(-0.5 * beta * n * (n + 1))
    else:
        print("Invalid method.")
        return -1
    
    return factor