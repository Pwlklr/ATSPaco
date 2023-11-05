# ATSPaco

Asymetric traveling salesman problem with ant colony optimization

DESCRIPTION

The project addresses the Traveling Salesman Problem with three-dimensional city coordinates and fuel consumption considerations, extending the classic Traveling Salesman Problem (TSP). It incorporates three additional aspects: three-dimensional city coordinates (x, y, z) where x and y represent standard geographical coordinates, and z represents the altitude above sea level. It also takes into account fuel consumption by the car, depending on the elevation difference between the current and the next city on the route. The goal of the project is to find the optimal route between cities that minimizes the total fuel consumption during the journey.


The project employs various algorithms to solve the Traveling Salesman Problem, including:

Greedy Algorithm: An algorithm that selects cities in the order of minimal fuel consumption.
Brute-Force Algorithm: An exhaustive search algorithm that explores all possible permutations of cities to find the optimal route.
Ant Colony Algorithm: A metaheuristic-based algorithm for solving the TSP.
Data Generator
The project also includes a random input data generator that allows you to prepare a test dataset for the Traveling Salesman Problem with three-dimensional coordinates and fuel consumption. The generator enables you to specify the problem's degree, coordinate intervals, and elevation differences between cities.

Results Visualization
The project provides results visualization, allowing you to understand the optimal Traveling Salesman route and the arrangement of cities in three-dimensional space. Visualization is performed using Python and utilizes the matplotlib and mpl_toolkits.mplot3d libraries.

License
This project is available under the MIT License.
