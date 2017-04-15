#include <cmath>
#include <cstdio>

static double DEGREES_PER_MIN = 360.0 / 60.0;  // 6  deg/min
static double DEGREES_PER_HOUR = 360.0 / 12.0; // 30 deg/h

int main()
{
    int hour, minute;
    double minAngle, hourAngle, angleDiff;

    // 0:00 is the terminating sequence.
    while (scanf("%d:%d", &hour, &minute) != EOF && hour != 0)
    {
        // Convert to degrees from 12 o'clock postion.
        minAngle = DEGREES_PER_MIN * minute;
        // Hour hand moves towards next hour as minute hand moves.
        hourAngle = DEGREES_PER_HOUR * (static_cast<double>(hour % 12) + (minAngle / 360.0));

        // Use the smallest angle between hands.
        angleDiff = std::abs(hourAngle - minAngle);
        if (angleDiff > 180.0)
        {
            angleDiff = 360.0 - angleDiff;
        }

        // Round to 3 decimal places.
        angleDiff = round(1000.0 * angleDiff) / 1000.0;
        printf("%.3f\n", angleDiff);
    }
}
