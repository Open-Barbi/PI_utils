import serial
import matplotlib.pyplot as plt

uart_port = '/dev/ttyACM0'  # Cambia esto al puerto UART correcto en tu sistema
# Misma velocidad de transmisión UART especificada en el programa de Arduino
uart_baudrate = 9600

# Inicializar la conexión UART
ser = serial.serial_for_url(uart_port, baudrate=uart_baudrate)

# Configurar la gráfica
plt.ion()  # Activar el modo interactivo
fig, ax = plt.subplots()
line, = ax.plot([], [])
ax.set_xlim(0, 100)  # Cambia los límites adecuados según tus necesidades
ax.set_ylim(0, 5000)

x_data = []
y_data = []

# Función de actualización de la gráfica


def update_plot(new_x, new_y):
    x_data.append(new_x)
    y_data.append(new_y)
    line.set_data(x_data, y_data)
    ax.relim()
    ax.autoscale_view()
    fig.canvas.draw()


# Leer y graficar los datos recibidos
while True:
    if ser.in_waiting > 0:
        data = ser.readline().decode('utf-8').rstrip()
        print(data+"\n")
        try:
            sensor_data = int(data)
            update_plot(len(x_data), sensor_data)
        except ValueError:
            pass  # Ignorar datos no numéricos

    plt.pause(0.001)

# Cerrar la conexión UART al finalizar
ser.close()
