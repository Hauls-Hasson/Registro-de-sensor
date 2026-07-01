import serial
import os

# CONFIG
PORT = 'COM3'  # ou '/dev/ttyUSB0' no Linux
BAUD = 115200

folder = "registro de dados do sensor"
filename = "log.txt"

# Criar pasta se não existir
if not os.path.exists(folder):
    os.makedirs(folder)

filepath = os.path.join(folder, filename)

ser = serial.Serial(PORT, BAUD)

with open(filepath, "a") as f:
    print("Gravando dados...")
    while True:
        line = ser.readline().decode(errors='ignore').strip()
        print(line)
        f.write(line + "\n")
        f.flush()