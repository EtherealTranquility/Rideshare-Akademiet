import matplotlib.pyplot as plt

x = [1, 2, 3, 4, 5]
y = [1, 4, 9, 16, 25]

plt.plot(x, y, label="y = x^2")
plt.xlabel("X-akse")
plt.ylabel("Y-akse")
plt.title("Enkel graf")
plt.legend()
plt.show()
