# Water_Tanks_Network_Control_System
This thesis presents a comprehensive project involving the management of three water tanks, treated first with a centralized control system and subsequently with a decentralized control system.

In particular the project is divided in the following parts:
- Physical model and its Components
- System and Network Set-Up.
- Centralized Algorithm.
- Distributed Algorithm.

The complete report is available [here](.Water_Tank_Network_Control_System.pdf).

## Physical model and its Components
The physical model is composed by three interconnected water tanks and an Arduino system.
### Physical model:
The three water tanks are disposed as follows:
<div align="center">
  <img src="./media/tanks.jpg" alt="tanks" width="50%">
</div>
The tray in the center is raised 14 cm above the others thanks to a specially built support. The former is connected to each of the others by a manual valve, made by a syringe of 11 mm diameter.

### Electronic Components
The Arduino system is made up of:
#### MKR 1000 WiFi
#### Water Sensors
#### Pump System including Pump, Relay Shield and an Amplifier Circuit
# Other components: Resistance, Diode and 12 V Battery
The components are connected as follows:
<div align="center">
  <img src="./media/connection_components.jpg" alt="connection_components" width="50%">
</div>
Each water tank is equipped with a different Arduino system connected to a PC. This setup allows for measuring the water level of each tank and activating the pump system for the bottoms tanks as needed.
<div align="center">
  <img src="./media/tanks_comp.jpg" alt="tanks_comp" width="50%">
</div>
