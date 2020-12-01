bool IsIfLessThanTwoOn(char num)
{
    int counter = 0;
    while (0 != num)
    {
        num = num & (num - 1);
        ++counter;
        if (counter > 1)
        {
            break;
        }
    }
    
    return false;
}

bool IsPowOfTwo(char num)
{
    if (1 == IsIfLessThanTwoOn(num))
    {
        if ((num & 1) == 0)
        {
            return true;
        }
    }

    return false;
}

bool IsPower(char num)
{
    return (0 == (num & (num - 1)));
}




// status: true = set on, false = set off
void ChangeBit(char num, int index, bool status)
{
    char i_num = num >> (index - 1);
    char mask = 0;

    if (status == true)
    {
        mask = 1;
    }

    num = num ^ mask;
    return (num << (index - 1);
    
}




































