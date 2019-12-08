#include"ImageProcessing.h"

int main(int argc, char *argv[])
{
    int amount = 0;
    std::string ans;
    std::cout << "Enter amount of pic for scan" << std::endl;
    std::cin >> amount;
    std::cout << "Do you want find contours using cv? (y,n)" << std::endl;
    std::cin >> ans;
    int colorStep = 255/(amount-1); // for depth of contours
    int currRedColor = 0;
    if (ans == "y") {
        for (int i = 0; i < amount; i++) {
            find_contour_cv(std::to_string(i) + ".jpg", currRedColor);
            currRedColor += colorStep;
        }
    } else {
        std::string first = "0.jpg";
        std::string last = std::to_string(amount-1) + ".jpg";
        for (int i = 0; i < amount; i++) {
            find_contour_own(std::to_string(i) + ".jpg", first, last, currRedColor);
            currRedColor += colorStep;
        }
    }
    return 0;
}
