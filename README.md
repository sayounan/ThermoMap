# ThermoMap
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

<ins>**Click on your OS to get the corresponding .NET installation instructions.**</ins>

<details><summary>Linux</summary><blockquote>
**Ensure ssh is enabled before proceeding.**

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

[Link]: 'https://dotnet.microsoft.com/en-us/download/dotnet/8.0'
[Button Icon]: https://img.shields.io/badge/Installation-EF2D5E?style=for-the-badge&logoColor=white&logo=DocuSign

</blockquote></details>

<details><summary>Windows</summary><blockquote>

[![Button Icon]][Link]

[Link]: 'https://dotnet.microsoft.com/en-us/download/dotnet/8.0'
[Button Icon]: https://img.shields.io/badge/Installation-EF2D5E?style=for-the-badge&logoColor=white&logo=DocuSign

</blockquote></details>

### Software Setup
1. On your terminal, navigate to the directory containing the software.
2. Run the following command: ```dotnet run```
3. In your web browser enter ```localhost: 5232``` into the address bar and press enter.
4. Click on "Connect"
5. Click on the MRI image to indicate location of the heat source.