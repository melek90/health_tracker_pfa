# Health Tracker Monitor

## Description
Health Tracker Monitor est une application de surveillance médicale en temps réel développée dans le cadre d’un projet académique.

Elle permet de collecter, traiter et visualiser plusieurs paramètres physiologiques à travers une interface web intuitive.

---

## Objectifs
- Surveiller l’activité cardiaque en temps réel (ECG)
- Mesurer la fréquence cardiaque (BPM)
- Mesurer la température corporelle
- Afficher les données sur une interface web dynamique

---

## Technologies utilisées

### Matériel
- ESP32
- AD8232 (Capteur ECG)
- MAX30100 (Capteur BPM)
- MLX90614 (Capteur température)

### Logiciel
- Arduino IDE (programmation ESP32)
- Python (Flask)
- HTML / CSS / JavaScript
- Chart.js (visualisation graphique)

---

## Architecture du système

1. Les capteurs collectent les données physiologiques  
2. L’ESP32 traite et envoie les données via WiFi  
3. Un serveur Flask reçoit les données  
4. Une interface web affiche les données en temps réel  

---

## Fonctionnalités principales

- Affichage ECG en temps réel (courbe défilante)
- Fréquence cardiaque (BPM)
- Température corporelle
- Mise à jour en temps réel
- Interface utilisateur simple et claire

---

## Interface utilisateur

L’interface web comprend :
- Un graphique ECG dynamique (style moniteur médical)
- Des indicateurs en temps réel (BPM, Température)
- Une grille ECG pour un affichage réaliste

---

## Installation

### 1. Cloner le projet
```bash
git clone https://github.com/your-repo/health-tracker-monitor.git
cd health-tracker-monitor
```
### 2.Installer les dépendances Python
```bash
pip install flask
```
### 3.Lancer le serveur Flask
```bash
python app.py
```
### 4. Ouvrir dans le navigateur
```bash
http://ip_du_machine:5000
```
### 5.Configuration ESP32
Connecter l’ESP32 au même réseau WiFi que le PC puis modifier l’adresse IP du serveur Flask dans le code Arduino
```bash
const char* serverName = "http://ip_du_machine:5000/data";
```
