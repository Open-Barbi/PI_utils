import serial
import csv


def log_datos_uart(archivo_csv):
    # Configurar la comunicación serial
    # Reemplaza 'COM1' con el puerto correcto
    puerto_serial = serial.Serial('/dev/ttyACM0', 115200, timeout=1)

    try:
        # Abrir el archivo CSV en modo escritura y configurar el escritor CSV
        with open(archivo_csv, mode='w', newline='') as archivo:
            escritor_csv = csv.writer(archivo)

            # Bucle para leer y loguear los datos por UART línea por línea
            while True:
                linea = puerto_serial.readline().decode().strip()

                # Escribir la línea en el archivo CSV
                print(linea)
                escritor_csv.writerow([linea])

    except (serial.SerialException, ValueError) as e:
        print(f"Error de comunicación serial o formato inválido: {e}")


if __name__ == "__main__":
    archivo_csv = "datos_uart.csv"
    log_datos_uart(archivo_csv)
