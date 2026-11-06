int calculateBonusMarks(int obtainedMarks, int extraMarks)
{
    int updatedMarks = obtainedMarks + extraMarks;
    int maximumMarks = 100;

    if (updatedMarks > maximumMarks)
    {
        return maximumMarks;
    }

    return updatedMarks;
}