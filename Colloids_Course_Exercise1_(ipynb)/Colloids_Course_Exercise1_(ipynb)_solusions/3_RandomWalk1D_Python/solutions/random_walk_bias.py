class RandomStep(object):
    """ 
        method: random step method (unbiased, biased or off_lattice)
        step_var: step length variance <l^2> 
        
        perform_random_step(pos): given a position value `pos`,
            returns the updated position after performing a random step
        
    """
    METHODS = ["unbiased", "biased", "off_lattice"]

    def __init__(self, method):
        self.method = method
        self.step_var = 1.0

    method = property(operator.attrgetter("_method"))

    @method.setter
    def method(self, m):
        if not (m in self.METHODS):
            raise Exception("Invalid method.")
        self._method = m

    def perform_random_step(self, pos):
        if self.method == "unbiased":
            if random() < 0.5:
                return pos + Direction.RIGHT.value
            else:
                return pos + Direction.LEFT.value

        elif self.method == "biased":
            if random() < 0.8:
                return pos + Direction.RIGHT.value
            else:
                return pos + Direction.LEFT.value

        elif self.method == "off_lattice":
            return pos

        else:
            return pos