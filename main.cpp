#include <iostream>
#include <ctime>
using namespace std;


class SensorStates
{
  class State *current;
  public:
    SensorStates();
    void setCurrent(State *s)
    {
        current = s;
    }
    void sensing();
    void idle();
    void processing();
};

class State
{
  public:
    virtual void sensing(SensorStates *m)
    {
        cout << "   already in SENSING mode\n";
    }
    virtual void idle(SensorStates *m)
    {
        cout << "   already in IDLE mode\n";
    }
    virtual void processing(SensorStates *m)
    {
        cout << "PROCESSING\n";
    }
};

void SensorStates::sensing()
{
  current->sensing(this);
}

void SensorStates::idle()
{
  current->idle(this);
}

void SensorStates::processing()
{
  current->processing(this);
}


class SENSING: public State
{
  public:
    SENSING()
    {
        cout << "   SENSING-ctor ";
    };
    ~SENSING()
    {
        cout << "   dtor-SENSING\n";
    };
    void idle(SensorStates *m);
};

class PROCESSING: public State
{
  public:
    PROCESSING()
    {
        cout << "   PROCESSING-ctor ";
    };
    ~PROCESSING()
    {
        cout << "   dtor-PROCESSING\n";
    };
    void idle(SensorStates *m);
};

class IDLE: public State
{
  public:
    IDLE()
    {
        cout << "   IDLE-ctor ";
    };
    ~IDLE()
    {
        cout << "   dtor-IDLE\n";
    };
    void sensing(SensorStates *m)
    {
        cout << "   moving from IDLE to SENSING mode";
        m->setCurrent(new SENSING());
        delete this;
    }

     void processing(SensorStates *m)
    {
        cout << "  moving from IDLE to processing mode";
        m->setCurrent(new PROCESSING());
        delete this;
    }
};

void SENSING::idle(SensorStates *m)
{
  cout << "   moving from SENSING to IDLE mode";
  m->setCurrent(new IDLE());
  delete this;
}


void PROCESSING::idle(SensorStates *m)
{
  cout << "   moving from PROCESSING to IDLE mode";
  m->setCurrent(new IDLE());
  delete this;
}

SensorStates::SensorStates()
{
  current = new IDLE();
  cout << '\n';
}


int i;
class Temp_Sensor
{
public:
       int Temp;
       void GetTemp()
        {   cout << "Getting Temperature:" <<endl;
            cin >>Temp;
        }
        void ShowTemp()
        {
            cout <<"Showing Temperature=" <<Temp<<endl;
        }
};

class Hum_Sensor
{
    public:
        int Hum;
        void GetHum()
        {
            cout << "Getting Humidity:" <<endl;
            cin >> Hum;
        }
        void ShowHum()
        {
            cout << "Showing Humidity=" << Hum<<endl;
        }
};

class Time
{
    public:
    void Date()
        {
            time_t t = time(NULL);
            char *tm = ctime(&t);
            cout << "Timestamp: " <<tm;
        }
};


class Iot_Data_Queue : public Temp_Sensor, public Hum_Sensor, public Time
{
public:
Temp_Sensor t;
Hum_Sensor h;
Time d;
void result()
    {

    cout<<" Get Sensor input = "<<i<<endl;
    t.GetTemp();
    h.GetHum();
    d.Date();


    cout<<" ----------Here is Sensor Result----- "<<endl;
    cout<<"sensor:  "<<i<<"  result"<<endl;
    t.ShowTemp();
    h.ShowHum();
    d.Date();
    }
};

class Controller: public Iot_Data_Queue
{
    public:

    virtual void sensors()
    {
    Iot_Data_Queue q[i];
    for (i=1; i<=10; i++)
    {
    q[i].result();
    }
    }
};


class Client : public Controller
{
    public:
    void client()
    {
    string User;
    string Pass;
    cout<<"Enter Your Username = ";
    cin>>User;
    cout<<"Enter Password = ";
    cin>>Pass;
    {
    cout<<" "<<"----Welcome to access sensors----"<<User<<endl;
    }
    sensors();
}
};

int main()
{
  void(SensorStates:: *ptrs[])() =
  {
    SensorStates::idle, SensorStates::sensing, SensorStates::processing
  };
  SensorStates fsm;
  int num;
while(1)
  {
    cout << "Enter 0 for idle/1 for sensing/2 for processing: ";
    cin >> num;
    (fsm.*ptrs[num])();

    if(num==2)
    {
    Client c1;
    c1.client();
    return 0;
    }
  }
}

