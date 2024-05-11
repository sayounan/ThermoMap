# ThermoMap
Brian Shaver, Cassandra Gasser, & Sari Younan

![Software GIF](https://github.com/sayounan/ThermoMap/blob/main/Media/README%20Media/Software%20Demo.gif)

![UML](https://github.com/sayounan/ThermoMap/blob/main/Media/README%20Media/UML%20Diagram.png)
## Background
ThermoMap is software built to continue the work of a previous year's design named Thermectrode. The intended use is to
monitor the internal temperature of the brain during Radio Frequency (RF) ablation (burning/melting) procedures in the 
brain to treat Drug Resistant Epilepsy (DRE). The Thermectrode was a thermistor embedded Stereo-Electroencephalograph 
(sEEG) that could monitor brain temperature while also reading EEG data during neuro-ablation procedures. The 
Thermectrode fed the analog signal to an external circuit that filtered the signal and passed it onto a data acquisition 
device which then passed it onto a computer via USB protocol. This was then displayed as a graph along with a numerical 
temperature reading. 
## Introduction
The ThermoMap team began by overhauling the hardware to digital circuitry. The primary purpose of this change was to 
make the signal resistant to external electric or electromagnetic noise. An added benefit of the switch to digital 
circuitry was that the overhaul downsized the hardware significantly. The overhaul replaced the thermistor, the external
signal filtering circuit, data acquisition device, and computer with a digital temperature sensor embedded Printed 
Circuit Board (PCB) connected directly to the Raspberry Pi's general purpose input/output (GPIO) pins. The ThermoMap 
software is designed to give clinicians all the important information during a neuro-ablation procedure at a glance. The
software shows the real time heat transfer within the brain overlaid on patient Magnetic Resonance Imaging (MRI) scans. 
The software reads the temperature data from the point of digital sensor and is able to model the four dimensional 
behavior (motion in the x, y, z directions and time) of the heat radiating outward within the brain. The temperature is 
depicted as realtime expanding concentric spheres, color coded to correspond to the temperature increase within each 
sphere.

### Hardware Setup
![Raspberry Pi GPIO Pinout](https://github.com/sayounan/ThermoMap/blob/main/Media/README%20Media/Raspberry-Pi-5-Pinout-.jpg)

#### Sensor &harr; Raspberry Pi GPIO Pins
* VDD &harr; 3V3 Power
* GND &harr; Ground
* SDA &harr; GPIO 2 (SDA)
* SCL &harr; GPIO 3 (SCL)

### Dependencies

***Click on your OS to get the corresponding .NET installation instructions.***

<details><summary>Linux</summary><blockquote>

***Ensure ssh is enabled before proceeding.***

Install .NET:
```angular2html
curl -sSL https://dot.net/v1/dotnet-install.sh | bash /dev/stdin --channel STS
```

Simplify Path Resolution:
```angular2html
echo 'export DOTNET_ROOT=$HOME/.dotnet' >> ~/.bashrc
echo 'export PATH=$PATH:$HOME/.dotnet' >> ~/.bashrc
source ~/.bashrc
```

Verify .NET Installation:
```angular2html
dotnet --version
```
</blockquote></details>

<details><summary>MacOS</summary><blockquote>

[![Button Icon]][Link]

[Link]: https://dotnet.microsoft.com/en-us/download/dotnet/8.0
[Button Icon]: https://img.shields.io/badge/Installation-EF2D5E?style=for-the-badge&logoColor=white&logo=DocuSign

</blockquote></details>

<details><summary>Windows</summary><blockquote>

[![Button Icon]][Link]

[Link]: https://dotnet.microsoft.com/en-us/download/dotnet/8.0
[Button Icon]: https://img.shields.io/badge/Installation-EF2D5E?style=for-the-badge&logoColor=white&logo=DocuSign

</blockquote></details>

### Software Setup
#### Local (to the Raspberry Pi) Connection
1. On your terminal, navigate to the directory containing the software. ```cd /Path/to/software/location```
2. Run the following command: ```dotnet run```
3. Confirm that one of the output lines shows ```http://localhost:5232```
4. In your web browser enter ```http://localhost:5232``` into the address bar and press enter.
5. Click on "Connect"
6. Click on the MRI image to indicate location of the heat source.

#### Remote Connection
***The first step does not need to be repeated when connected to a Wi-Fi router this was already done on. More details 
under step 1.2.***
1. On the Raspberry Pi
   1. Start the terminal.
   2. Run the following command ```hostname -I``` *This is a capital i, not a lower case L*.
      * This command returns two IP address versions, IPv4 and IPv6 respectively. IPv4 is used for the next steps.
      * These IP addresses remain the same for the same Wi-Fi router. It will change with different routers including 
      different Wi-Fi nodes of the same network.
2. On the remote device (i.e. personal computer or laptop)
   1. Run ```ssh -L 5232:localhost:5232 ConfiguredNameOfRaspberryPi@IPv4Address```
      * This uses IP tunneling to go straight to port 5232 of the RPi since that is where our software runs.
   2. Enter the Raspberry Pi password
   3. **Continue on this same device by following the steps in the 
   [Local Connection Setup Instructions](#Local-to-the-Raspberry-Pi-Connection).**

### Future Steps
To the teams who inherit this project from us, listed below are potential avenues of development for the device.

*May this project bring you the fulfilment and excitement that would make your younger self look at you in awe.*

<details><summary>Harware: (Recommended Strength: Electrical/Electronic Engineering)</summary><blockquote>
The components currently being used, incorporated into the build are small enough, with the exception of the AS6221, to
fit inside the SEEG probe (0.8 mm internal diameter) built by the Thermectrode team. Your task would be to replace the 
AS6221 (1.490 x 1.020 x 0.600 mm) with a slightly smaller digital temperature sensor while also maintaining the same 
temperature reading accuracy and incorporate it into the SEEG built by the Thermectrode team. You are essentially tasked
with combining the two products you have inherited into one.
</blockquote></details>

<details><summary>Backend Software: (Recommended Strengths: Programming and Mathematics focusing on differential 
equations and linear algebra)</summary><blockquote>
Currently the software uses the one dimensional heat equation in polar coordinates 

</blockquote></details>

$$
\dfrac{\partial u}{\partial t} = \alpha \dfrac{\partial ^2 u}{\partial x^2}
$$

*Special thanks to : Dr. Samuel DeStefano MD, Dr. Steve Lammers PhD, Dr. Eric Roth PhD, and the members of the 
Thermectrode team from whom we inherited this project: Alyssa Moreno, Elise Carter, Jacob Bado, & Linea Gutierrez.*