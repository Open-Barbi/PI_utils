import matplotlib.pyplot as plt
import time
import serial

# Longitudes de onda correspondientes en nm
longitudes_de_onda = [610, 680, 730, 760, 810, 860]


def actualizar_datos_uart():
    # Configurar la comunicación serial
    # Reemplaza 'COM1' con el puerto correcto
    # Leer datos desde el puerto UART
    input()
    puerto_serial.write(b'\n')
    time.sleep(2)

    # Leer datos desde el puerto UART
    datos_leidos = puerto_serial.readline().decode().strip()
    # Separar los datos por coma y convertirlos a valores flotantes

    print(datos_leidos)
    try:
        datos_uart = [float(dato) for dato in datos_leidos.split(',')]
    except:
        datos_uart = [1, 1, 1, 1, 1, 1]
    print(datos_uart)
    return datos_uart


# Código para el ploteo (el mismo que se mostró anteriormente)
# ...
# Configurar el gráfico

puerto_serial = serial.Serial('/dev/ttyACM0', 115200, timeout=1)


plt.ion()  # Modo interactivo activado
fig, ax = plt.subplots()
datos_uart = [1, 1, 1, 1, 1, 1]
line, = ax.plot(longitudes_de_onda, datos_uart, 'b.-')

ax.set_xlabel('Longitud de onda (nm)')
ax.set_ylabel('Intensidad')
ax.set_title('Espectro de frecuencias')
ax.grid(True)
ax.set_xlim(600, 870)
ax.set_ylim(0, 1)  # Rango del eje y de 0 a 1

try:
    while True:
        # Actualizar datos de la lista datos_uart con la lectura por UART
        datos_uart = actualizar_datos_uart()

        if datos_uart.__len__() == 6:
            # Actualizar los datos del gráfico
            # Normalizar los datos dividiendo cada valor por el máximo valor en la lista
            max_valor = max(datos_uart)
            if max_valor == 0:
                max_valor = 1
            datos_normalizados = [dato / max_valor for dato in datos_uart]

            line.set_ydata(datos_normalizados)
            fig.canvas.draw()
            fig.canvas.flush_events()

        # Esperar un segundo antes de la próxima actualización
        time.sleep(1)

except KeyboardInterrupt:
    # Detener el bucle con Ctrl+C
    pass

# Desactivar el modo interactivo antes de cerrar el gráfico
plt.ioff()
plt.show()
