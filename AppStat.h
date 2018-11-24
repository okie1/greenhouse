namespace
{
//Reset the system after 60 seconds if the application is unresponsive
ApplicationWatchdog wd(60000, System.reset);

//Holds the time from when the device was started.  Tells us how long it has been running.
String g_UtcStart = "";

//This is updated once every 15 seconds.  Can be used as a heartbeat
String g_UtcCurrent = "";
unsigned long g_TimeUpdate = 0;

int MiscCommand(String command)
{
    if(command == "reboot")
    {
        //Reboot the device.
        System.reset();
    }
    return 0;
}
        
};//End anonymous namespace

class AppStat
{

public:
    AppStat(AppStat const&)        = delete;
    void operator=(AppStat const&) = delete;

    static AppStat& GetInstance()
    {
        static AppStat    instance; // Guaranteed to be destroyed.
        return instance;
    };
    void setup()
    {
        //Grab the current time in YYYY-MM-DD HH:MM:SS format.
        g_UtcStart = Time.format(Time.now(), "%F %T");//YYYY-MM-DD HH:MM:SS
        
        //Register two time variables to determine how long the device has been running and if it still is.
        Particle.variable("App_UtcStart", &g_UtcStart, STRING);
        Particle.variable("App_UtcCurnt", &g_UtcCurrent, STRING);
        
        Particle.function("App_MiscCmd", MiscCommand);
    };
    void loop()
    {
        //Reset the watchdog timer to prevent the system from rebooting.
        wd.checkin();
        
        //Update the heartbeat time if time has expired.
        unsigned long timeNow = millis();
        if((timeNow - g_TimeUpdate) >=15000)
        {
            g_TimeUpdate = timeNow;
            g_UtcCurrent = Time.format(Time.now(), "%F %T");//YYYY-MM-DD HH:MM:SS
        }
    };
private:
    AppStat(){};//Default constructor
};