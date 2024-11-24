import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Circle, Wedge, Polygon

# Определяем окружности
circles = [
    {'center': (1, 1), 'radius': 1, 'color': 'lightblue'},
    {'center': (1.5, 2), 'radius': np.sqrt(5)/2, 'color': 'lightgreen'},
    {'center': (2, 1.5), 'radius': np.sqrt(5)/2, 'color': 'lightcoral'}
]

fig, ax = plt.subplots(figsize=(8, 8))

patches = []

# Добавляем окружности
for c in circles:
    circle = Circle(c['center'], c['radius'], facecolor=c['color'], alpha=0.5, edgecolor='black')
    ax.add_patch(circle)

# Координаты вершин треугольника T
triangle_coords = np.array([
    [1, 1],
    [1, 2],
    [2, 1]
])

# Добавляем треугольник T
triangle = Polygon(triangle_coords, closed=True, facecolor='yellow', alpha=0.5, edgecolor='black')
ax.add_patch(triangle)

# Настраиваем оси
ax.set_xlim(0, 3)
ax.set_ylim(0, 3)
ax.set_aspect('equal', adjustable='box')
ax.set_title('Разбиение области пересечения на треугольник и сегменты')

# Подписываем элементы
ax.text(1.1, 1.1, 'T', fontsize=12, color='black')
ax.text(0.7, 1.5, 'C1', fontsize=12, color='black')
ax.text(1.7, 2.1, 'C2', fontsize=12, color='black')
ax.text(2.1, 1.7, 'C3', fontsize=12, color='black')

# Сохраняем изображение
plt.savefig('segments.png')
plt.show()
