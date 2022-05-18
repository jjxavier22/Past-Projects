#The vapor pressure is approximately 10 millibars at 7 degrees celsius

#importing math functions vital to the calculations for the program such as e
import math

#reads the user's input  for the desired degrees celsius for which vapor pressure needs to be calcuated
readCelsius = int(input("Enter the temperature  in degrees C: "))

#implementation of the formula to calculate the vapor pressure at a given temperature in Celsius
vaporPressure = (6.112 * math.exp((17.67 * readCelsius) / (readCelsius + 243.5)))

#truncating the value for vapor pressure so that it only displays the value to two decimal places
vaporPressure = "{:.2f}".format(vaporPressure)

#printing the calculated vapor pressure
print("At this temperature, the vapor pressure is approximately " + vaporPressure + " millibars.")

#Program is only practical and accurate if realistic temperatures are entered
#into the program.
