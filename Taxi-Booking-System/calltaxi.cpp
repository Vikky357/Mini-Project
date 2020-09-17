#include<bits/stdc++.h>
using namespace std;
int nearest[2]={-1,1};
bool visited[6];
class Taxi
{
protected:
    int taxi_id;
    int total_amount;
    int cust_id;
    int booking_id;
    int curr_amount;
public:
    char frompoint;
    char topoint;
    int p_time;
    int d_time;
    Taxi(){}
    Taxi(int id,int amount,int cid,char frompoint,char topoint,int p_time,int d_time)
    {
        this->taxi_id=id;
        this->total_amount=amount;
        this->cust_id=cid;
        this->frompoint=frompoint;
        this->topoint=topoint;
        this->p_time=p_time;
        this->d_time=d_time;
    }
    void assign_bid(int i)
    {
        this->booking_id=i;
    }
    bool operator < (const Taxi rhs) const
    {
        if(total_amount==rhs.total_amount)
        {
            return taxi_id<rhs.taxi_id;
        }

        else if(total_amount<rhs.total_amount)
            return true;
        else
            return false;
    }
    void print_details()
    {
        cout<<"Booking_ID"<<"    "<<"Customer_ID"<<"    "<<"Pickuppoint"<<"     "<<"Droppoint"<<"     "<<"PicKTime"<<"      "<<"DropTime"<<"        "<<"Amount";
        cout<<"\n";
        cout<<booking_id<<"             "<<cust_id<<"              "<<frompoint<<"              "<<topoint<<"              "<<p_time<<"             "<<d_time<<"                "<<curr_amount;
        cout<<"\n";
    }
    bool getd_time(int ptime)
    {
        return d_time<ptime;
    }
    int get_id()
    {
        return taxi_id;
    }
    int get_totalamount()
    {
        return total_amount;
    }
    int getamount()
    {
        return curr_amount;
    }
    void settamount(int a)
    {
        this->total_amount=a;
    }
    void print_id()
    {
        cout<< taxi_id;
    }
    void update_details(int cid,char ppoint,char en,int ptime,char strt)
    {
        this->cust_id=cid;
        this->frompoint=strt;
        this->topoint=en;
        this->p_time=ptime;
        this->d_time=ptime+((en-strt)*1);
        if(d_time==24)
            d_time=0;
        int dist=(en-strt)*15;
        dist=dist-5;
        if(dist<=0)
            dist=0;
        this->curr_amount=100+(dist*10);

    }

};
class BKS :public Taxi
{
protected:
    static int booking_id;
    vector<Taxi> Taxilist[1000];
    unordered_map<char,set<Taxi> > m;
    int nooftaxi;
public:
    BKS()
    {
        printf("Enter the number of Taxi's\n");
        cin >>nooftaxi;
        for(int i=1;i<=nooftaxi;i++)
        {
            m['a'].insert(Taxi(i,0,0,'-','-',0,0));
            //continue;
        }
    }
    void display()
    {
        printf("\n\n\t\t\t\tTaxi Booking System\t\t\t\t\n\n");
        printf("Enter Your Choice:\n");
        printf("1.Book Taxi\n");
        printf("2.Get Taxi Details\n");
        printf("3.Get Station Details\n");
        printf("4.Exit\n");
        int choice;
        scanf("%d",&choice);
        int getid;
        char stid;
        switch(choice)
        {
            case 1:
                book();
                break;
            case 2:
            printf("Enter the taxi Id:");
            cin >>getid;
            cout<<"TaxiId:"<<getid;
            cout<<"\n";
            if(!(Taxilist[getid].size()))
            {
                cout<<"Not Started\n";
                break;
            }
            cout<<"Total Amount:"<<Taxilist[getid].back().get_totalamount();
            cout<<"\n";
            for(auto details:Taxilist[getid])
            {
                details.print_details();
            }
            break;
            case 3:
                printf("Enter the station id:\n");
                cin >>stid;
                stid=tolower(stid);
                if(isalpha(stid)==false)
                {
                    cout<<"Wrong Input!!";
                    break;
                }
                printf("Cars in Station:%c ",stid);
                if(m[stid].size()==0)
                {
                    cout<<"No Cars Available Currently\n";
                    break;
                }
                for(auto i:m[stid])
                    {
                        i.print_id();
                        cout<<" ";
                    }
                break;
            case 4:
                cout<<"Thanks for Using this System\n";
                break;
            default:
                break;

        }


    }
    void book()
    {
        memset(visited,false,sizeof(visited));
        int cid,ptime;
        char ppoint,dpoint,oppoint;
        int nppoint;
        printf("Customer id:\n");
        cin >>cid;
        printf("Pickup point:\n");
        cin >>ppoint;
        ppoint=tolower(ppoint);
        oppoint=ppoint;
        printf("Drop Point:\n");
        cin >>dpoint;
        if(isalpha(ppoint)==false || !(isalpha(dpoint)))
        {
            cout<<"Wrong Input\n";
            return;
        }
        dpoint=tolower(dpoint);
        printf("Pickup Time\n");
        cin >>ptime;
        queue<int> q;
        visited[ppoint]=true;
        q.push(ppoint-'a');
            while(!(q.empty()))
        {
                int temp=q.front();
                q.pop();
                ppoint=temp+'a';
                if(m[ppoint].size()&& check_availability(ppoint,ptime,cid,dpoint,oppoint))
                {
                    return ;
                }
                for(int i=0;i<2;i++)
                {

                    nppoint=temp+nearest[i];
                    if(nppoint>=0 && nppoint<6 && !visited[nppoint])
                    {
                        q.push(nppoint);
                        visited[nppoint]=true;
                    }

                }
        }
       // cout<<ppoint<<" "<<m[ppoint].size()<<"\n";
        if(q.size()==0)

           {
               cout<<"Sorry!!Taxi cannot be alloted\n";
                return;
            }

    }
    bool check_availability(char ppoint,int ptime,int cid,int dpoint,char oppoint)
      {

        for(auto check:m[ppoint])
        {
            if(check.getd_time(ptime))
            {
                    cout<<"Taxi can be alloted\n";
                    printf("Taxi %d is alloted\n",check.get_id());
                    booking_id++;
                    check.assign_bid(booking_id);
                    auto curr_taxi=m[ppoint].find(check);
                    m[ppoint].erase(curr_taxi);
                    check.update_details(cid,ppoint,dpoint,ptime,oppoint);
                    int tamount;
                    if(Taxilist[check.get_id()].size())
                        tamount=check.getamount()+Taxilist[check.get_id()].back().get_totalamount();
                    else
                        tamount=check.getamount();
                    check.settamount(tamount);
                    m[dpoint].insert(check);
                    Taxilist[check.get_id()].push_back(check);
                return true;

            }
        }
        return false;
    }

};
int BKS::booking_id=0;
int main()
{
    BKS obj;
    int n=1;
    do
    {
        system("cls");
        obj.display();
        cout<<"Do you want to Continue- Y:1 N:0\n";
        cin >>n;
    }while(n==1);
}
