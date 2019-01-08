# Graph-Period
For an irreducible (strongly connected) graph G we can calculate its period as follows:

1. Perform a depth-first search of G
2. For each e in G that connects a vertex on level i of the depth-firstsearch tree to a vertex on level j, let ke = −i−1.
3. Compute the greatest common divisor of the set of numberske
