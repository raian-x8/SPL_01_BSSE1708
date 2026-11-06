int calculateInventory(int initialStock, int receivedStock)
{
    int availableStock = initialStock + receivedStock; // Combine inventory.
    availableStock -= 2;                               // Remove damaged items.

    if (availableStock < 0) // Check minimum.
    {
        availableStock = 0; // Prevent negative stock.
    }

    if (availableStock > 800) // Check capacity.
    {
        availableStock = 800; // Limit available stock.
    }

    return availableStock; // Return inventory.
}

int calculateShipping(int itemCount)
{
    int shippingCost = itemCount * 4;
    shippingCost += 15; // Add handling fee.

    if (shippingCost > 200)
    {
        shippingCost = 200;
    }

    return shippingCost;
}