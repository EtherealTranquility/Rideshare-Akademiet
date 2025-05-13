import pandas as pd
import matplotlib.pyplot as plt

# Read CSV file
def read_sensor_data(filename):
    data = pd.read_csv(filename)
    return data

# Plot acceleration, gyro, and temperature data
def plot_sensor_data(data):
    plt.figure(figsize=(12, 10))

    # Acceleration
    plt.subplot(3, 1, 1)
    plt.plot(data['time(ms)'], data['ax'], label='ax', color='red')
    plt.plot(data['time(ms)'], data['ay'], label='ay', color='green')
    plt.plot(data['time(ms)'], data['az'], label='az', color='blue')
    plt.title('Akselerasjon over tid')
    plt.ylabel('Akselerasjon (m/s²)')
    plt.legend()
    plt.grid(True)

    # Gyroscope
    plt.subplot(3, 1, 2)
    plt.plot(data['time(ms)'], data['gx'], label='gx', color='orange')
    plt.plot(data['time(ms)'], data['gy'], label='gy', color='purple')
    plt.plot(data['time(ms)'], data['gz'], label='gz', color='brown')
    plt.title('Gyroskop over tid')
    plt.ylabel('Rotasjon (°/s)')
    plt.legend()
    plt.grid(True)

    # Temperature
    plt.subplot(3, 1, 3)
    # Antar at temperatur er siste kolonne
    temp_column = data.columns[-1]
    plt.plot(data['time(ms)'], data[temp_column], label='Temperatur', color='black')
    plt.title('Temperatur over tid')
    plt.xlabel('Tid (ms)')
    plt.ylabel('Temperatur (°C)')
    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.show()

# Main program
def main():
    filename = '../måledata/testmåling_06_13_25.csv'
    data = read_sensor_data(filename)
    plot_sensor_data(data)

if __name__ == '__main__':
    main()