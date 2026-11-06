int calculateDistance(int speedValue, int timeValue)
{
    int totalDistance = speedValue * timeValue;
    totalDistance += 12;

    if (totalDistance > 1000)
    {
        totalDistance = 1000;
    }

    if (totalDistance < 0)
    {
        totalDistance = 0;
    }

    return totalDistance;
}

int estimateTravelCost(int distanceValue)
{
    int baseCost = distanceValue / 5;

    if (baseCost < 10)
    {
        baseCost = 10;
    }

    if (baseCost > 500)
    {
        baseCost = 500;
    }

    int serviceFee = baseCost / 10;

    return baseCost + serviceFee;
}