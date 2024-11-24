import matplotlib.pyplot as plt
import pandas as pd
import math

# Чтение данных из CSV-файла
data = pd.read_csv('data.csv')

# Точное значение площади
exact_area = 0.25 * math.pi + 1.25 * math.asin(0.8) - 1.0

# График 1: Приближенное значение площади в зависимости от N
plt.figure(figsize=(10, 6))
plt.plot(data['N'], data['Area_Wide'], label='Широкая область')
plt.plot(data['N'], data['Area_Narrow'], label='Узкая область')
plt.hlines(y=exact_area, xmin=data['N'].min(), xmax=data['N'].max(), colors='red', linestyles='dashed', label='Точное значение')
plt.xlabel('Количество точек N')
plt.ylabel('Приближенная площадь')
plt.title('Приближенная площадь в зависимости от N')
plt.legend()
plt.grid(True)
plt.savefig('approx_area_vs_N.png')
plt.show()

# График 2: Относительное отклонение в зависимости от N
plt.figure(figsize=(10, 6))
plt.plot(data['N'], data['Error_Wide'], label='Широкая область')
plt.plot(data['N'], data['Error_Narrow'], label='Узкая область')
plt.xlabel('Количество точек N')
plt.ylabel('Относительное отклонение (%)')
plt.title('Относительное отклонение от точного значения площади в зависимости от N')
plt.legend()
plt.grid(True)
plt.savefig('relative_error_vs_N.png')
plt.show()
