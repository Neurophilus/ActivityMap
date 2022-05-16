#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int ARR_SIZE = 1000;

/**
 * @brief getCoordinates reads in a line containing coordinates from
 *        the infilestream and parses out the coordinates
 * @param inFile is the infilestream
 * @param x1 is the first coordinate read
 * @param y1 is the second coordinate read
 * @param x2 is the second coordinate read
 * @param y2 is the second coordinate read
 */
bool getCoordinates(ifstream& inFile, int& x1, int&y1, int& x2, int&y2) {
    string fileLine;
    getline(inFile, fileLine);
    bool good = inFile.good();
    if (good) {
    x1 = stoi(fileLine.substr(0, fileLine.find(",")));
    y1 = stoi(fileLine.substr(fileLine.find(",") + 1, fileLine.find(" -> ")));
    string secondCoords = fileLine.substr(fileLine.find("->") + 3);
    x2 = stoi(secondCoords.substr(0, secondCoords.find(",")));
    y2 = stoi(secondCoords.substr(secondCoords.find(",") + 1));
    }
    return (good);

}

void drawLine(int x1, int y1, int x2, int y2, int *activityMap) {
    if (x1 == x2) {
        if (y1 - y2 > 0) {
            for(int i = y2; i <= y1; i++) {
                activityMap[x1 * ARR_SIZE + i] += 1;
            }
        } else {
            for(int i = y1; i <= y2; i++) {
                activityMap[x1 * ARR_SIZE + i] += 1;
            }
        }

    } else if (y1 == y2) {
        if (x1 - x2 > 0) {
            for(int i = x2; i <= x1; i++) {
                activityMap[i * ARR_SIZE + y1] += 1;
            }
        } else {
            for(int i = x1; i <= x2; i++) {
                activityMap[i * ARR_SIZE + y1] += 1;
            }
        }
    }

}

int countHotspots(int *activityMap) {
    int spotNum = 0;
    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j < ARR_SIZE; j++) {
            if (activityMap[i * ARR_SIZE + j] >= 2) {
                spotNum++;
            }
        }
    }
    return spotNum;
}





int main()
{
    int* activityMap = new int[ARR_SIZE * ARR_SIZE];
    ifstream inFile;
    inFile.open(("input.txt"));
    bool good = true;
    while(good) {
        int x1, y1, x2, y2;
         good = getCoordinates(inFile, x1, y1, x2, y2);
         if (good) {
             drawLine(x1, y1, x2, y2, activityMap);
         } else {
             cout << "inFile Failed!" << endl;
         }
    }


    cout << countHotspots(activityMap) << " hotspots in total." << endl;

    delete [] activityMap;
    inFile.close();
    return 0;
}
