import numpy as np
import matplotlib.pyplot as plt

# 定义爱心方程
t = np.linspace(0, 2 * np.pi, 100)
x = 16 * np.sin(t) ** 3
y = 13 * np.cos(t) - 5 * np.cos(2 * t) - 2 * np.cos(3 * t) - np.cos(4 * t)


# 对坐标进行归一化到 -1 到 1 之间
x_min, x_max = np.min(x), np.max(x)
y_min, y_max = np.min(y), np.max(y)
x = 2 * (x - x_min) / (x_max - x_min) - 1
y = 2 * (y - y_min) / (y_max - y_min) - 1

for i in range(100):
    
    print( 0 ,"," ,i+1,",",i+2, ",")
    # print( x[i] ,"," ,y[i],",")


# # 创建图形
# plt.figure(figsize=(8, 8))
# plt.plot(x, y, color='red', linewidth=2)

# # 添加坐标注释
# for i in range(len(x)):
#     plt.annotate(f"({x[i]:.2f}, {y[i]:.2f})", (x[i], y[i]), textcoords="offset points", xytext=(5, 5), ha='left', va='bottom', fontsize=8)

# plt.axis('equal')
# plt.axis('off')
# plt.title('Love Heart')
# plt.show()