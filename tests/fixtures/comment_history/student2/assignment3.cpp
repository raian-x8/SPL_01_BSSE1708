int calculateFuelUse(int travelDistance, int mileageValue)
{
    int fuelUnits = travelDistance + mileageValue; // Combine measurements.
    fuelUnits += 5;                                // Apply adjustment.

    if (fuelUnits > 300) // Check maximum.
    {
        fuelUnits = 300; // Limit fuel estimate.
    }

    if (fuelUnits < 0) // Check minimum.
    {
        fuelUnits = 0; // Prevent negative values.
    }

    return fuelUnits; // Return fuel estimate.
}

int calculateTollFee(int vehicleWeight)
{
    int tollFee = vehicleWeight / 4;
    tollFee += 7; // Add service charge.

    if (tollFee > 150)
    {
        tollFee = 150;
    }

    return tollFee;
}