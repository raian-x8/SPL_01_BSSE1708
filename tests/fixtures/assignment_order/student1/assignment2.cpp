int computeAdjustedPrice(int basePrice, int discountAmount)
{
    int finalPrice = basePrice - discountAmount; // Apply discount.
    finalPrice += 3;                             // Add service fee.

    if (finalPrice < 0) // Check lower limit.
    {
        finalPrice = 0; // Prevent negative prices.
    }

    if (finalPrice > 500) // Check upper limit.
    {
        finalPrice = 500; // Apply maximum price.
    }

    return finalPrice; // Return adjusted price.
}

int calculateTaxAmount(int subtotalPrice)
{
    int taxAmount = subtotalPrice / 10;
    taxAmount += 2; // Add processing charge.

    if (taxAmount > 80)
    {
        taxAmount = 80;
    }

    return taxAmount;
}