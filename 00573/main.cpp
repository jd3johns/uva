#include <iostream>

bool failedClimb(const double climbHeight, const int day)
{
    bool failed = false;
    if (climbHeight < 0.0)
    {
        failed = true;
        std::cout << "failure on day " << day << std::endl;
    }

    return failed;
}

bool succeededClimb(
    const double climbHeight,
    const double wellHeight,
    const double day
)
{
    bool succeeded = false;
    if (climbHeight > wellHeight)
    {
        succeeded = true;
        std::cout << "success on day " << day << std::endl;
    }

    return succeeded;
}

void printOutcome(
    int wellHeight, int climbDist,
    int slideDist, int fatiguePct
)
{
    int dayCount = 0;
    double currentHeight = 0;
    double currentClimbDist = static_cast<double>(climbDist);

    // Convert other program variables to avoid excessive casts
    // and operations in the loop.
    double dWellHeight = static_cast<double>(wellHeight);
    double dSlideDist = static_cast<double>(slideDist);
    double dFatigue = currentClimbDist * static_cast<double>(fatiguePct) / 100.0;

    while (!failedClimb(currentHeight, dayCount))
    {
        // A new day!
        ++dayCount;

        // Climb to victory!
        currentHeight += currentClimbDist;
        if (succeededClimb(currentHeight, dWellHeight, dayCount)) break;

        // Tired after a long day's crawl.
        currentClimbDist -= dFatigue;
        if (currentClimbDist < 0.0)
        {
            currentClimbDist = 0.0;
        }

        // At night we slide back.
        currentHeight -= dSlideDist;
    }
}

int main()
{
    int H = 0, U = 0, D = 0, F = 0;
    while (true)
    {
        // Read test input.
        scanf("%d %d %d %d", &H, &U, &D, &F);

        // A height of zero indicates EOF.
        if (H == 0)
        {
            break;
        }

        printOutcome(H, U, D, F);
    }
}
