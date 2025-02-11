#include "Xdisplay.h"

class Xtime {
public:
    static Xtime& getInstance() {
        static Xtime instance;
        return instance;
    }

    void setupTime(const char* ntpServer1, const char* ntpServer2);
    void displayTime();
    static void timeSyncCallback(struct timeval *t);

private:
    Xtime() {}  // Private constructor
    Xtime(const Xtime&) = delete;  // Prevent copy-construction
    Xtime& operator=(const Xtime&) = delete;  // Prevent assignment

    static Xtime* instance;
    Xdisplay& display = Xdisplay::getInstance();  // Singleton instance
};
