#include <cmath>
#include <sstream>

double clockHandDifference(const int hour, const int minute)
{
    // Angles are measured CW from the 12 o'clock mark.
    // 12 o'clock translated to 0 o'clock via mod.
    // 180 degrees -> 6th hour mark.
    double hourAngle = (180.0 / 6.0) * static_cast<double>(hour % 12);
    // 180 degrees -> 30 minute mark.
    double minuteAngle = (180.0 / 30.0) * static_cast<double>(minute);

    double smallestAngleDelta = abs(hourAngle - minuteAngle);
    if (smallestAngleDelta > 180.0)
    {
        // Take the smaller angle between hands.
        smallestAngleDelta = 360.0 - smallestAngleDelta;
    }

    return smallestAngleDelta;
}

void parseClockTime(const char *clockTime, int &hour, int &minute)
{
    static const char delim = ':';

    std::stringstream ss;
    ss.str(clockTime);

    std::string strHour, strMinute;
    std::getline(ss, strHour, delim);
    std::getline(ss, strMinute, delim);

    hour = stoi(strHour);
    minute = stoi(strMinute);
}

int main()
{
    char clockTime[6];
    int hour, minute;

    scanf("%s", clockTime);
    parseClockTime(clockTime, hour, minute);

    while (hour > 0)
    {
        double delta = clockHandDifference(hour, minute);
        delta = round(1000.0 * delta) / 1000.0;
        printf("%.3f\n", delta);

        scanf("%s", clockTime);
        parseClockTime(clockTime, hour, minute);
    }
}
