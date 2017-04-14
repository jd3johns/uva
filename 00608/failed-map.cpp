#include <map>
#include <cstring>
#include <iostream>

// TODO: Need to deduce properly.

enum CoinStatus
{
    CS_HEAVY = -1,
    CS_REAL = 0,
    CS_LIGHT = 1,
};

typedef std::map<char, CoinStatus> CoinRecord;

void recordStatus(
    const std::string coins,
    const CoinStatus status,
    CoinRecord &record,
    bool overwrite
)
{
    for (char coin : coins)
    {
        // Overwrite current status, or insert if new entry.
        if (overwrite || !record.count(coin))
        {
            record[coin] = status;
        }
    }
}

void printResult(CoinRecord &record)
{
    std::string weight = "heavy";
    for (auto it = record.begin(); it != record.end(); ++it)
    {
        if (it->second != CS_REAL)
        {
            weight = it->second == CS_HEAVY ? "heavy" : "light";
            std::cout << it->first << " is the counterfeit coin and it is "
                      << weight << std::endl;
        }
    }
}

int main()
{
    static const int NUM_WEIGHS = 3;
    static const int NUM_COINS = 12;

    char leftCoins[NUM_COINS];
    char rightCoins[NUM_COINS];
    char balance[5];
    CoinRecord record;

    int numTests = 0;

    // Read num test cases.
    scanf("%d", &numTests);

    for (int test = 0; test < numTests; ++test)
    {
        for (int weighings = 0; weighings < NUM_WEIGHS; ++weighings)
        {
            // Read weighing results.
            scanf("%s %s %s", leftCoins, rightCoins, balance);
            
            // Determine which side might be heavy/light/real.
            bool overwrite = false;
            CoinStatus leftStatus = CS_REAL;
            CoinStatus rightStatus = CS_REAL;
            if (strcmp(balance, "even") == 0)
            {
                overwrite = true;
            }
            else if (strcmp(balance, "up") == 0)
            {
                leftStatus = CS_HEAVY;
                rightStatus = CS_LIGHT;
            }
            else if (strcmp(balance, "down") == 0)
            {
                leftStatus = CS_LIGHT;
                rightStatus = CS_HEAVY;
            }

            // Record what we've learned.
            recordStatus(std::string(leftCoins), leftStatus, record, overwrite);
            recordStatus(std::string(rightCoins), rightStatus, record, overwrite);
        }

        // Search the map for the coin that isn't real.
        printResult(record);
        record.clear();
    }
}
