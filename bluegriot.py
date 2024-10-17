import serial
import numpy as np
import matplotlib.pyplot as plt

# Connexion à l'Arduino 
Arduino = serial.Serial("COM3", baudrate=9600, timeout=1)

# Stockage des données
data = []
compt = 0

# Nombre de mesures faites
while compt < 50:  # 50 mesures
    line = Arduino.readline().decode('utf-8').strip()  # Lecture décodage et enlever les espaces
    if line:  # S'assurer qu'il y a bien des données
        data.append(line)
        compt += 1

# Sauvegarder les données dans un fichier texte
def write(L):
    with open("data.txt", mode="w") as file:
        for line in L:
            file.write(line + '\n')

write(data)

# Charger les données depuis le fichier (3 colonnes : Vpin, Ipin, PWM_filtree, temps)
Vpin, Ipin, PWM_filtree, temps = np.loadtxt("data.txt", delimiter=';', unpack=True)

# Tracé des données
plt.figure(figsize=(10, 6))

# Tracer les courbes
plt.figure()
plt.plot(temps * 0.00001, Vpin * 5 / 1023, color='r')
plt.title("Vpin (Tension)")
plt.xlabel("Temps (s)")
plt.ylabel("Tension (V)")
plt.grid(True)


plt.figure()
plt.plot(temps * 0.00001, Ipin * 5 / 1023, color='g')
plt.title("Ipin (Courant)")
plt.xlabel("Temps (s)")
plt.ylabel("Courant (A)")
plt.grid(True)


plt.figure()
plt.plot(temps * 0.00001, PWM_filtree * 5 / 1023, color='b')
plt.title("PWM_filtree (PWM)")
plt.xlabel("Temps (s)")
plt.ylabel("PWM")
plt.grid(True)
plt.show()
