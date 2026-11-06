int calculateTemperature(int morningTemp, int eveningTemp)
{
    int averageTemp = (morningTemp + eveningTemp) / 2; // Find average.
    averageTemp += 1;                                  // Apply adjustment.

    if (averageTemp > 45) // Check maximum.
    {
        averageTemp = 45; // Limit high values.
    }

    if (averageTemp < -10) // Check minimum.
    {
        averageTemp = -10; // Limit low values.
    }

    return averageTemp; // Return temperature.
}

int estimateHumidity(int airValue)
{
    int humidityValue = airValue / 3;
    humidityValue += 6; // Apply correction.

    if (humidityValue > 100)
    {
        humidityValue = 100;
    }

    return humidityValue;
}