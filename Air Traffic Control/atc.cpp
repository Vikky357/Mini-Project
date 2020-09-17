#include<bits/stdc++.h>
#include<Windows.h>
#include<thread>
#include<conio.h>
using namespace std;
void display();
class Airplane
{
 public:
    string name;
    int weight;
    int time;
    Airplane(){}
    Airplane(string name,int weight,int time)
    {
        this->name=name;
        this->weight=weight;
        this->time=time;
    }
};
class Runway
{
public:
    int runway_name;
    int runway_time;
    bool status;
    Runway() {}
    Runway(int rid,int rtime,bool status)
    {
        this->runway_name=rid;
        this->runway_time=rtime;
        this->status=status;
    }
};
class ATC : public Airplane,public Runway
{
   protected:
       string input_flight_name;
       int input_flight_weight;
       unordered_map<string,Airplane> flight_details;
       vector<Runway> Runway_details;
       queue<pair<string,int>> q;
       //private: thread* t;

    public:
        ATC()
        {
            flight_details["atr"]=Airplane("atr",12,30);
            flight_details["airbus"]=Airplane("airbus",20,40);
            flight_details["boeing"]=Airplane("boeing",40,50);
            flight_details["cargo"]=Airplane("cargo",100,60);
            Runway_details.push_back(Runway(1,40,true));
            Runway_details.push_back(Runway(2,60,true));
            Runway_details.push_back(Runway(3,80,true));
            Runway_details.push_back(Runway(4,90,true));

        }

       void display()
       {
           system("cls");
            printf("\t\t\t\tAir Traffic Controller\t\t\t\n");
            printf("\n\n\n\n");
            int choice;
            printf("Enter the following Operation\n");

            printf("Enter your choice:\n");
            printf("1.Take Off\n");
            printf("2.Landing\n");
            printf("3.Emergency Landing\n");
            printf("4.Runway_Staus\n");
            printf("5.Exit\n");
            scanf("%d",&choice);
            switch(choice)
            {
            case 1:
                getdetails();
                take_off(input_flight_name,input_flight_weight);
                break;
            case 2:
                getdetails();
                landing(input_flight_name,input_flight_weight);
                break;
            case 3:
                getdetails();
                elanding(input_flight_name,input_flight_weight);
                break;
            case 4:
                print_platform();
                break;
            case 5:
                break;
            default:
                break;

            }

       }

    void getdetails()
    {

            printf("Enter the Type of Flight\n");
            int choice;
                printf("Enter your choice:\n");
                printf("1.Atr\n");
                printf("2.Airbus\n");
                printf("3.Boeing\n");
                printf("4.Cargo\n");
                scanf("%d",&choice);
                switch(choice)
                {
                case 1:
                    input_flight_name="atr";
                    break;
                case 2:
                    input_flight_name="airbus";
                    break;
                case 3:
                    input_flight_name="boeing";
                    break;
                case 4:
                    input_flight_name="cargo";
                    break;
                default:
                    break;
                }

        printf("Enter the Weight of the current Flight\n");
        scanf("%d",&input_flight_weight);
        while(input_flight_weight>flight_details[input_flight_name].weight)
        {
            cout<<"Excess Weight!! Enter Again\n";
            scanf("%d",&input_flight_weight);
        }


       }

    void take_off(string flight_name,int flight_weight)
    {
        int actual_time=caltime(flight_details[flight_name].weight,flight_weight,flight_details[flight_name].time);
        //assign_runway(flight_details[flight_name],actual_time);
        thread t(&ATC::assign_runway,this,flight_details[flight_name],actual_time,"take_off\0");
        t.detach();
        Sleep(500);
    }

    void landing(string flight_name,int flight_weight)
    {
        int actual_time=caltime(flight_details[flight_name].weight,flight_weight,flight_details[flight_name].time);
        thread t(&ATC::assign_runway,this,flight_details[flight_name],actual_time,"landing\0");
        t.detach();
        Sleep(500);
        return;
    }

    void elanding(string flight_name,int flight_weight)
    {
       int actual_time=caltime(flight_details[flight_name].weight,flight_weight,flight_details[flight_name].time);
       thread t(&ATC::assign_runway,this,flight_details[flight_name],actual_time,"emergency\0");
        t.detach();
        Sleep(500);

        return;

    }
    int caltime(int fl_weight,int cur_weight,int time)
    {
        int percent=(cur_weight/fl_weight)*100;
        if(50<percent&& percent<=75)
            time=time-(time*(10/100));
        else if(percent<=50)
            time=time-(time*(20/100));
        time=time+10;
        //cout<<time;
        return time;
    }
    bool assign_runway(Airplane obj,int time,string runway_status)
    {
        cout<<"Assigning...\n";
       for(auto &rway:Runway_details)
       {
           if(rway.status && rway.runway_time>=time)
           {
               rway.status=false;
               cout<<"\rFlight "<<obj.name<<" is assigned to platform no "<<rway.runway_name<<" and ready for "<<runway_status<<".";
               printf("Platform no %d is busy for %d sec\n",rway.runway_name,time);
               Sleep(1000*time);
               rway.status=true;
               if(!(q.empty()))
               {
                   system("cls");
                   assign_emergency();
               }
               return true;

           }
       }
        if(runway_status!="emergency\0")
        cout<<"Sorry,Please Approach after 35 sec\n";
      else
      {
          cout<<"Please wait,we are clearing the runway\n";
          q.push({input_flight_name,input_flight_weight});
      }
       return false ;
    }
    void assign_emergency()
    {
        if(q.empty())
            return;
        auto temp=q.front();
        q.pop();
       elanding(temp.first,temp.second);
       return;

    }
    void print_platform()
    {
        for(auto pltfrm:Runway_details)
        {
            string status="Free";
            if(pltfrm.status==false)
                status="Busy";
            cout<<"Platform "<<pltfrm.runway_name<<"is "<<status;
            cout<<"\n";
        }
    }


};

int main()
{
    ATC obj;
    int i=1;
    do
    {
        obj.display();
        printf("Do you want to continue Y:1 ? N:0\n");
        scanf("%d",&i);
    }while(i);

}
