int determine_larger_number(int input_one, int input_two)
{
    int current_maximum = input_one;

    if (input_two > current_maximum)
    {
        current_maximum = input_two;
    }

    int doubled_maximum = current_maximum * 2;

    return doubled_maximum;
}