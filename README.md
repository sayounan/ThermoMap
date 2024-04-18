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
![Raspberry Pi GPIO Pinout](https://github.com/sayounan/ThermoMap/blob/Passing-temp/Media/README%20Media/Raspberry-Pi-5-Pinout-.jpg)
#### Sensor &harr; Raspberry Pi GPIO Pins
* VCC &harr; 3V3 Power
* GND &harr; Ground
* SDA &harr; GPIO 2 (SDA)
* SCL &harr; GPIO 3 (SCL)
#### Clinical Sensor Placement
* Sensor is already embedded within the RF ablator.
### Dependencies
Mono is needed to run .exe programs on Unix based systems like Linux and Mac
#### Linux: [The Mono Project](https://www.mono-project.com)
```angular2html
sudo apt install dirmngr ca-certificates gnupg
sudo gpg --homedir /tmp --no-default-keyring --keyring /usr/share/keyrings/mono-official-archive-keyring.gpg --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
echo "deb [signed-by=/usr/share/keyrings/mono-official-archive-keyring.gpg] https://download.mono-project.com/repo/debian stable-buster main" | sudo tee /etc/apt/sources.list.d/mono-official-stable.list
sudo apt update
```
```angular2html
sudo apt install mono-devel
```
#### MacOS: [The Mono Project](https://www.mono-project.com)
[Download Instructions](https://www.mono-project.com/download/stable/#download-mac)

#### Windows: N/A
### Software Setup
1. Open the executable file.
2. Click the CT scan image to indicate the location of the heat source.
3. Click the "Start Ablation" button to indicate the start of the ablation procedure and begin displaying temperature 
behavior.