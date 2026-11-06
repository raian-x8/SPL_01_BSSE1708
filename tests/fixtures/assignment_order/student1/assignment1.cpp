int calculateTotalMarks(int quizScore, int labScore)
{
    int totalMarks = quizScore + labScore; // Combine components.
    totalMarks += 5;                       // Add attendance marks.

    if (totalMarks > 100) // Check upper limit.
    {
        totalMarks = 100; // Apply maximum.
    }

    if (totalMarks < 0) // Check lower limit.
    {
        totalMarks = 0; // Apply minimum.
    }

    return totalMarks; // Return final marks.
}

int calculatePercentage(int obtainedMarks)
{
    int percentageValue = obtainedMarks;
    percentageValue *= 100; // Apply percentage scale.
    percentageValue /= 100;

    if (percentageValue > 100)
    {
        percentageValue = 100;
    }

    return percentageValue;
}