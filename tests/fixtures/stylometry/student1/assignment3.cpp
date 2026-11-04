int find_largest_value(int first_value, int second_value)
{
    int selected_value = first_value;

    if (second_value > selected_value)
    {
        selected_value = second_value;
    }

    int final_value = selected_value * 2;

    return final_value;
}