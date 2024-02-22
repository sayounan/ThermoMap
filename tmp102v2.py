"""
NeuroThermals
22/02/2024 10:10:06
tmp102.py
"""

import time
import smbus2

i2c_ch = 1

# TMP102 address on the I2C bus
i2c_address = 0x48

# Register addresses
reg_temp = 0x00
reg_config = 0x01


# Calculate the 2's complement of a number
def twos_comp(vals, bits):
    if (vals & (1 << (bits - 1))) != 0:
        vals = vals - (1 << bits)
    return vals


# Read temperature registers and calculate Celsius
def read_temp():
    # Read temperature registers
    value = bus.read_i2c_block_data(i2c_address, reg_temp, 2)
    # NOTE: val[0] = MSB byte 1, val [1] = LSB byte 2
    # print ("!shifted val[0] = ", bin(val[0]), "val[1] = ", bin(val[1]))

    temp_c = (value[0] << 4) | (value[1] >> 4)
    # print (" shifted val[0] = ", bin(val[0] << 4), "val[1] = ", bin(val[1] >> 4))
    # print (bin(temp_c))

    # Convert to 2s complement (temperatures can be negative)
    temp_c = twos_comp(temp_c, 12)

    # Convert registers value to temperature (C)
    temp_c = temp_c * 0.0625

    return temp_c


# Initialize I2C (SMBus)
bus = smbus2.SMBus(i2c_ch)

# Read the CONFIG register (2 bytes)
val = bus.read_i2c_block_data(i2c_address, reg_config, 2)
print("Old CONFIG:", val)

# Set to 4 Hz sampling (CR1, CR0 = 0b10)
val[1] = val[1] & 0b00111111
val[1] = val[1] | (0b10 << 6)

# Write 4 Hz sampling back to CONFIG
bus.write_i2c_block_data(i2c_address, reg_config, val)

# Read CONFIG to verify that we changed it
val = bus.read_i2c_block_data(i2c_address, reg_config, 2)
print("New CONFIG:", val)

# Print out temperature every second
while True:
    temperature = read_temp()
    print(round(temperature, 2), "C")
    time.sleep(1)
