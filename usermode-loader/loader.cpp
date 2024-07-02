#include <windows.h>
#include <iostream>

bool LoadDriver(const char* serviceName, const char* driverPath) {
    SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (!scManager) return false;
    SC_HANDLE scService = CreateService(
        scManager, serviceName, serviceName,
        SERVICE_START | DELETE | SERVICE_STOP,
        SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
        driverPath, NULL, NULL, NULL, NULL, NULL);
          if (!scService) {
              scService = OpenService(scManager, serviceName, SERVICE_START);
          }
          if (!scService) {
              CloseServiceHandle(scManager);
              return false;
          }

    bool result = StartService(scService, 0, NULL);
    CloseServiceHandle(scService);
    CloseServiceHandle(scManager);
    return result;
}

int main() {
    const char* driverPath = "path-here";
    if (LoadDriver("your-driver", driverPath)) {
        std::cout << "Successfully entered" << std::endl;
    } else {
        std::cout << "An error occured" << std::endl;
    }
    return 0;
}
