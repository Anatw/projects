////////////////////////////////////////////////////////////////////////////////
// Written by Anat Wax, anatwax@gmail.com
// December 30, 2020
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

int main()
{
    std::cout << "Hello world!" << std::endl;
    return (0);
}


#include <iostream>
#include <vector>

bool FindK(std::vector<int>list, int num)
{
    int i = 0;
    int j = 1;
    int len = list.size();
    
    for (i = 0; i < len; ++i)
    {
        for (j = (i + 1); j < len; ++j)
        {
            if ((list[i] + list[j]) == num)
            {
                return true;
            }
        }
    }
    
    return false;
}

int main()
{
  
  std::vector<int> list = {10, 15, 3, 7};
   int num = 25;
   bool status = false;
   
   status = FindK(list, num);
   
   std::cout << status << std::endl;
}
