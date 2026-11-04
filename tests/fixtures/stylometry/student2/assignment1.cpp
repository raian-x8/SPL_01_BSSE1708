int calculate_item_cost(int base_price, int tax_amount)
{
    int total_price = base_price + tax_amount;
    int discounted_price = total_price - 2;

    return discounted_price;
}