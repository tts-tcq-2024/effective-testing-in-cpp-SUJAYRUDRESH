#include <iostream>
#include <assert.h>

int alertFailureCount = 0;

class NetworkAlertInterface {
public:
    virtual ~NetworkAlertInterface() = default;
    virtual int sendAlert(float celcius) = 0;
};


class StubNetworkAlert : public NetworkAlertInterface {
public:
    int sendAlert(float celcius) override {
        // Simulate a failure for testing
        std::cout << "Sending alert for temperature: " << celcius << " celcius.\n";
        return 500;
    }
};


class ProductionNetworkAlert : public NetworkAlertInterface {
public:
    int sendAlert(float celcius) override {
        // Real network sending code here
        std::cout << "Sending alert for temperature: " << celcius << " celcius.\n";
        return 200; // Simulate success
    }
};


void alertInCelcius(NetworkAlertInterface& alertSystem, float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = alertSystem.sendAlert(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}

int main() {
    StubNetworkAlert stubAlert;
    alertFailureCount = 0;
    alertInCelcius(stubAlert, 400.5); // Should fail
    assert(alertFailureCount == 1 && "Test failed: Failure count should be 1 but is 0. Bug in alertInCelcius function!");

    alertInCelcius(stubAlert, 303.6); // Should fail
    assert(alertFailureCount == 2 && "Test failed: Failure count should be 1 but is 0. Bug in alertInCelcius function!");

    std::cout << alertFailureCount << " alerts failed.\n";
    std::cout << "All is well (maybe!)\n";
    return 0;
}
