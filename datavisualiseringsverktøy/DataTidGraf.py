import pandas as pd
import matplotlib.pyplot as plt

# Read CSV file
def read_sensor_data(filename):
    data = pd.read_csv(filename)  # Leser inn med eksisterende header
    return data

# Plot acceleration and gyro data
def plot_sensor_data(data):
    plt.figure(figsize=(12, 8))

    # Acceleration
    plt.subplot(2, 1, 1)
    plt.plot(data['time(ms)'], data['ax'], label='ax', color='red')
    plt.plot(data['time(ms)'], data['ay'], label='ay', color='green')
    plt.plot(data['time(ms)'], data['az'], label='az', color='blue')
    plt.title('Akselerasjon over tid')
    plt.ylabel('Akselerasjon (m/s²)')
    plt.legend()
    plt.grid(True)

    # Gyroscope
    plt.subplot(2, 1, 2)
    plt.plot(data['time(ms)'], data['gx'], label='gx', color='orange')
    plt.plot(data['time(ms)'], data['gy'], label='gy', color='purple')
    plt.plot(data['time(ms)'], data['gz'], label='gz', color='brown')
    plt.title('Gyroskop over tid')
    plt.xlabel('Tid (ms)')
    plt.ylabel('Rotasjon (°/s)')
    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.show()

# Main program
def main():
    filename = '../måledata/testmåling_06_05_25.csv'
    data = read_sensor_data(filename)
    plot_sensor_data(data)

if __name__ == '__main__':
    main()
