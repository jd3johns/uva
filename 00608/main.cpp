#include <map>
#include <iostream>

static const int NUM_COINS = 12;
static const int NUM_WEIGHS = 3;
static const std::string COIN_NAMES = "ABCDEFGHIJKL";

enum CoinStatus
{
    CS_UNKNOWN = 0,
    CS_REAL,
    CS_LIGHT,
    CS_HEAVY
};

typedef std::map<char, CoinStatus> CoinRecord;

void markStatus(CoinRecord &record, const std::string &coins, const CoinStatus status)
{
    CoinStatus currentStatus;
    for (char coin : coins)
    {
        currentStatus = record[coin];
        if (currentStatus == CS_UNKNOWN)
        {
            // First weighing.
            record[coin] = status;
        }
        else if (currentStatus == CS_REAL)
        {
            // Real coins stay real. Skip.
        }
        else if (currentStatus != status)
        {
            // If there's a contradiction, then it's real.
            record[coin] = CS_REAL;
        }
        else
        {
            // Re-setting the same status.
            record[coin] = status;
        }
    } 
}

bool updateRecord(CoinRecord &record, std::string leftCoins, std::string rightCoins, std::string balance)
{
    if (balance == "even")
    {
        markStatus(record, leftCoins, CS_REAL);
        markStatus(record, rightCoins, CS_REAL);
    }
    else if (balance == "up")
    {
        markStatus(record, leftCoins, CS_HEAVY);
        markStatus(record, rightCoins, CS_LIGHT);
    }
    else if (balance == "down")
    {
        markStatus(record, leftCoins, CS_LIGHT);
        markStatus(record, rightCoins, CS_HEAVY);
    }
    else
    {
        // String used for balance is wrong.
        return false;
    }

    if (balance == "up" || balance == "down")
    {
        // All the coins not included in the weighing are
        // guaranteed to be real.
        for (auto it = record.begin(); it != record.end(); ++it)
        {
            if (leftCoins.find(it->first) == std::string::npos &&
                    rightCoins.find(it->first) == std::string::npos)
            {
                it->second = CS_REAL;
            }
        }
    }

    return true;
}

void printCounterfeit(const CoinRecord &record)
{
    char coin;
    CoinStatus status;
    std::string weight;
    for (auto it = record.begin(); it != record.end(); ++it)
    {
        coin = it->first;
        status = it->second;
        if (status == CS_LIGHT || status == CS_HEAVY)
        {
            weight = status == CS_LIGHT ? "light" : "heavy";
            std::cout << coin << " is the counterfeit coin and it is " << weight << "." << std::endl;
        }
    }
}

void resetRecord(CoinRecord &record)
{
    record.clear();
    for (char coin : COIN_NAMES)
    {
        record[coin] = CS_UNKNOWN;
    }
}

int main()
{
    int numTests;
    CoinRecord record;
    char leftCoins[NUM_COINS+1], rightCoins[NUM_COINS+1], balance[5];

    scanf("%d", &numTests);
    
    bool success = true;
    for (int test = 0; test < numTests; ++test)
    {
        resetRecord(record);
        for (int weighing = 0; weighing < NUM_WEIGHS; ++weighing)
        {
            scanf("%s %s %s", leftCoins, rightCoins, balance);

            success = updateRecord(record, std::string(leftCoins), std::string(rightCoins), std::string(balance));
            if (!success)
            {
                std::cout << "failed to update counterfeit estimate; malformed input\n";
                return 1;
            }
        }

        printCounterfeit(record);
    }
}
