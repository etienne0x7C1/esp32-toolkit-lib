class GpioService {
    public:
    static std::vector<GpioService *> *instances;  // the registered components to gpio service
    std::vector<int> *pinConfig;  // gpios used by component

    void listUsed(){

    }

    void listAvailable(){

    }

};