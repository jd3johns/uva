#include <map>
#include <cstring>
#include <iostream>

typedef std::map<char, int> CoinLetterMap;

int main()
{
    static const int NUM_WEIGHS = 3;
    static const int NUM_COINS = 12;

    char leftCoins[NUM_COINS];
    char rightCoins[NUM_COINS];
    char balance[5];
    CoinLetterMap coinMap {
        {'A', 0x001}, {'B', 0x002}, {'C', 0x004}, {'D', 0x008},
        {'E', 0x010}, {'F', 0x020}, {'G', 0x040}, {'H', 0x080},
        {'I', 0x100}, {'J', 0x200}, {'K', 0x400}, {'L', 0x800}
    };

    int numTests = 0;

    // Read num test cases.
    scanf("%d", &numTests);

    for (int test = 0; test < numTests; ++test)
    {
        int real = 0;
        int heavy = 0;
        int light = 0;
        std::string strLeftCoins = "";
        std::string strRightCoins = "";

        for (int weighings = 0; weighings < NUM_WEIGHS; ++weighings)
        {
            // Read weighing results.
            scanf("%s %s %s", leftCoins, rightCoins, balance);
            strLeftCoins = leftCoins;
            strRightCoins = rightCoins;
            
            // Determine which side might be heavy/light/real.
            if (strcmp(balance, "even") == 0)
            {
                for (char coin : strLeftCoins)
                {
                    real |= coinMap[coin];
                    light &= ~coinMap[coin];
                    heavy &= ~coinMap[coin];
                }

                for (char coin : strRightCoins)
                {
                    real |= coinMap[coin];
                    light &= ~coinMap[coin];
                    heavy &= ~coinMap[coin];
                }
            }
            else if (strcmp(balance, "up") == 0)
            {
                heavy = 0;
                light = 0;
                for (char coin : strLeftCoins)
                {
                    heavy |= (coinMap[coin] & real) ^ coinMap[coin];
                }

                for (char coin : strRightCoins)
                {
                    light |= (coinMap[coin] & real) ^ coinMap[coin];
                }
            }
            else if (strcmp(balance, "down") == 0)
            {
                heavy = 0;
                light = 0;
                for (char coin : strLeftCoins)
                {
                    light |= (coinMap[coin] & real) ^ coinMap[coin];
                }

                for (char coin : strRightCoins)
                {
                    heavy |= (coinMap[coin] & real) ^ coinMap[coin];
                }
            }
            else
            {
                return 1;
            }
        }
        
        int result;
        std::string weight;
        if (heavy > 0)
        {
            result = heavy;
            weight = "heavy";
        }
        else if (light > 0)
        {
            result = light;
            weight = "light";
        }
        else
        {
            return 1;
        }
        std::cout << "result is " << weight << " and is number " << result << std::endl;

        // Reverse lookup from value to key.
        for (auto it = coinMap.begin(); it != coinMap.end(); ++it)
        {
            if (it->second == result)
            {
                std::cout << it->first << " is the counterfeit coin and it is "
                          << weight << std::endl;
                break;
            }
        }
    }
}
