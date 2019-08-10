#include <vector>

class LogicalUnit {
private:
    struct logicalNumber {
        bool logic;
        bool combine;
    };
    int scale;
    std::vector<logicalNumber> inputLogic;
    int numberOfOne;
    bool minimum;
public:
    explicit LogicalUnit(int scale, std::vector<bool> logic) {
        this->scale = scale;
        this->inputLogic = std::vector<logicalNumber>(scale);
        this->minimum = false;
        int count = 0;
        for (unsigned long i = 0; i < scale; i++) {
            count += logic[i];
            this->inputLogic[i] = logicalNumber{logic[i], false};
        }
        this->numberOfOne = count;
    }

    std::vector<logicalNumber> getInputLogic() {
        return this->inputLogic;
    }

    /*
     *  impossible to combine : -1
     *  possible to combine : Number that can be combine.
     */
    unsigned int possibleIntegrate(LogicalUnit combineDestination) {
        int count = 0;
        unsigned int combineNumber = -1;
        std::vector<logicalNumber> destinationLogic = combineDestination.getInputLogic();
        for (unsigned int i = 0; i < scale; i++) {
            bool combineCheck = !(this->inputLogic[i].combine or destinationLogic[i].logic); // possible to combine : true
            bool numberCheck = this->inputLogic[i].logic == destinationLogic[i].logic;
            if (combineCheck && !numberCheck) {
                ++count;
                if (count == 1) {
                    combineNumber = i;
                } else {
                    return -1;
                }
            }
        }
        return combineNumber;
    }
};

