#include "RentalUI.h"

int main() {
    RentalUI app;
    app.loadCars("C:\\Users\\AD\\Downloads\\cars.csv");
    app.run();
    return 0;
}
