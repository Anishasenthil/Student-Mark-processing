#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
//#include<conio.h>
#include<stdlib.h>
using namespace std;
class student
{
private:
    int stu_id;
    char name[30];
    int m1;
    int m2;
    int m3;
    int m4;
    int m5;
    int tot;
    int avg;
    char result;
public:
    void getdata()
    {
        cout<<"\n                                Student ID : ";
        cin>>stu_id;
        cout<<"\n                                Name : ";
        fflush(stdin);
        gets(name);
        cout<<"\n                                English : ";
        cin>>m1;
        cout<<"\n                                Maths : ";
        cin>>m2;
        cout<<"\n                                Tamil : ";
        cin>>m3;
        cout<<"\n                                Science : ";
        cin>>m4;
        cout<<"\n                                Social : ";
        cin>>m5;
    }
    int returnstudent_Id()
    {
        return stu_id;
    }
    void calculate()
    {
        tot = m1+m2+m3+m4+m5;
        avg = tot/5;
        if((m1 >= 35)&&(m2 >= 35)&&(m3 >= 35)&&(m4 >= 35)&&(m5 >= 35))
            result = 'P';
        else
            result = 'F';
    }
    void printdata()
    {   
        cout<<"                              -------------------------------";
        cout<<"\n                               STUDENT ID   : "<<stu_id;
        cout<<"\n                               NAME         : "<<name;
        cout<<"\n                               TOTAL        : "<<tot << "/500";
        cout<<"\n                               AVERAGE      : "<<avg;
        cout<<"\n                               FINAL RESULT : "<<result<<endl;
        cout<<"                              -------------------------------";
    }
};
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
int main()
{
    int choice = 0;
    student s;
    cout<<"\n\n                                 STUDENT ";
    delay(400);
    cout<<" MARK ";
    delay(400);
    cout<<" PROCESSING"<<endl;
    //cout<<"\n\n                                  STUDENT MARK PROCESSING  "<<endl;
    cout<<"                                 --------------------------"<<endl;
 while(true)
 {
    cout<<"\n\n                               ***************************** "<<endl;
    delay(500);
    cout<<"\n                                        1. INSERT  "<<endl;
    delay(500);
    cout<<"\n                                        2. READ  "<<endl;
    delay(500);
    cout<<"\n                                        3. UPDATE  "<<endl;
    delay(500);
    cout<<"\n                                        4. DELETE  "<<endl;
    delay(500);
    cout<<"\n                                        5. EXIT  "<<endl;
    cout<<"\n                               ***************************** "<<endl;

    cout<<"\n                                        CHOICE : ";
    cin>>choice;
    system("cls");
    switch(choice)
    {
    case 1:{
         fstream file;
            int i=0;
            file.open("studinf.dat",ios :: out | ios :: app);

            for(int i = 0 ; i < 1 ; i++)
            {
                cout<<"\n           STUDENT "<< i+1<<endl;
                s.getdata();
                file.write((char *)&s,sizeof(s));
            }
            file.close();
            break;
    }

    case 2: {
            fstream file;
            int i=0;

            file.open("studinf.dat",ios :: out | ios :: app | ios :: in);
            file.seekg(0);
            file.read((char *)&s,sizeof(s));

            while(!file.eof())
            {
                cout<<"\n           STUDENT "<< i+1<<endl;
                s.calculate();
                s.printdata();
                file.read((char *)&s,sizeof(s));
                i++;
            }
            file.close();
            break;
    }

    case 3:{
           fstream file,newfile;
            int i=0;
            int ans = 0;
            int org_id = 0;
            int rcount = 0;

             cout<<"\n                        Enter the Id where data to be updated : ";
             cin>>ans;

            file.open("studinf.dat",ios :: out | ios :: app | ios :: in);
            newfile.open("modistuinf.dat", ios :: out | ios :: app | ios :: in);
            file.seekg(0);
            file.read((char *)&s,sizeof(s));

            while(!file.eof())
            {
                rcount++;
                //cout<<" record count "<<rcount<<endl;
                org_id = s.returnstudent_Id();

                if(org_id != ans)
                {
                    newfile.write((char *)&s,sizeof(s));
                }
                else
                {
                    int radd = 0 ;
                    s.calculate(); // to print  the old data so that you can see the changes.
                    s.printdata();
                    radd = sizeof(s)*(rcount-1);
                    newfile.seekg(0);
                    newfile.seekg(radd);
                    s.getdata();
                    newfile.write((char *)&s,sizeof(s));
                }
                file.read((char *)&s,sizeof(s));
            }
            file.close();
            newfile.close();
            remove("studinf.dat");
            rename("modistuinf.dat","studinf.dat");
            cout<<"\n                            "<<ans << "- ID  updated  Successfully!"<<endl;
            break;
    }

    case 4:{
            fstream file,newfile;
            int rmv_id;
            int student_id;

            file.open("studinf.dat",ios :: out | ios :: app | ios :: in);
            newfile.open("nwstudinf.dat",ios :: out | ios :: app | ios :: in);

            cout<<"\n                   Enter the Student Id to be removed : ";
            cin>>rmv_id;

            file.seekg(0);
            file.read((char *)&s,sizeof(s));

            while(!file.eof())
            {
                 student_id = s.returnstudent_Id();

                 if(student_id != rmv_id)
                 {
                     s.calculate();
                     newfile.write((char *)&s,sizeof(s));
                 }
                 file.read((char *)&s,sizeof(s));
            }
            file.close();
            newfile.close();

            remove("studinf.dat");
            rename("nwstudinf.dat","studinf.dat");
            cout<<"\n                             "<<rmv_id <<"-ID  removed Successfully! "<<endl;

             break;
    }

    case 5:
           return 0;
    default:
        cout<<"\n INVALID CHOICE ,PLEASE ENTER AGAIN "<<endl;
    }
}
    return(0);
}
