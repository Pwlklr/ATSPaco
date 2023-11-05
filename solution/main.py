import json
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Import cities data
with open('D:\Studia\Semestr_3\OptymalizacjaKombinatoryczna\projekt\data\generatedData.json') as json_file:
    cities_data = json.load(json_file)

with open('solutionBruteForce.json') as json_file:
    route_data = json.load(json_file)

route = route_data['route']

# Prepare data in numpy format
x = np.array([city['x'] for city in cities_data])
y = np.array([city['y'] for city in cities_data])
z = np.array([city['z'] for city in cities_data])

# Create 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Add cities
ax.scatter(x, y, z, c='b', marker='o', label='Cities')

# Plot edges based on the route
for i in range(len(route) - 1):
    city1_index = route[i]
    city2_index = route[i + 1]
    ax.plot([x[city1_index], x[city2_index]], [y[city1_index], y[city2_index]], [z[city1_index], z[city2_index]], c='r')

for i, city in enumerate(cities_data):
    ax.text(x[i], y[i], z[i], f'City {i}', fontsize=10)

ax.legend()

ax.set_box_aspect([10, 10, 5])

plt.show()