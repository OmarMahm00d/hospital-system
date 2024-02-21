#include <iostream>

using namespace std;
//hospital data structure
const short int MAX_SPECIALIZATION = 20;
const short int MAX_QUEUE = 5;
struct Ali{
    string name;
    bool patient;
};
Ali p[MAX_SPECIALIZATION+1][MAX_QUEUE];
string patientNames[MAX_SPECIALIZATION+1][MAX_QUEUE];
bool patientStatuses[MAX_SPECIALIZATION+1][MAX_QUEUE] = {0};// '0' for regular '1' for urgent
short int queueLengthPerSpec[MAX_SPECIALIZATION+1] = {0};

//functions
void shiftRight(const short int &spNum){
    short int pos = queueLengthPerSpec[spNum];
    for(int i=pos-1;i>=0;i--){
        patientNames[spNum][i+1] = patientNames[spNum][i];
        patientStatuses[spNum][i+1] = patientStatuses[spNum][i];
    }
}
void shiftLift(const short int &spNum){
    short int pos = queueLengthPerSpec[spNum];
    for(int i=0;i<pos-1;i++){
        patientNames[spNum][i] = patientNames[spNum][i+1];
        patientStatuses[spNum][i] = patientStatuses[spNum][i+1];
    }
}
void printSpecialization(const short int &specNum, const string names[], const bool statuses[]){//print the patients in a specific specialization
    int len = queueLengthPerSpec[specNum];
    if(len == 0)//if there are patients
        return;
    cout<< "\nThere are " << queueLengthPerSpec[specNum] << " patients in specialization " << specNum << endl;
    //print the patients name and status
    for(int i=0;i<len;i++){
        cout<< names[i] << "\t";
        if(statuses[i])
            cout<< "urgent\n";
        else
            cout<< "regular\n";
    }
}
void removeFromQueue(const short int &spNum){
    shiftLift(spNum);
    queueLengthPerSpec[spNum]--;
}

//hospital features
void addNewPatient(){
    //get specialization number and name and status from user
    string name;
    short int spec;
    bool st;
    cout <<"Enter specialization, name,  status: ";
    cin >> spec;
    cin>> name;
    /*getline(cin, name);
    cin.ignore();*/
    cin>> st;
    short int pos = queueLengthPerSpec[spec];
    if(pos >= 5){// if the queue is full
        cout << "sorry, We can't add more patients to this specialization\n";
        return;
    }
    if(st == 0){// if status is regular, add to end of queue
        patientNames[spec][pos] = name;
        patientStatuses[spec][pos] = st;
        queueLengthPerSpec[spec]++;
        return;
    }
    if(st){//if status is urgent, add to begin of queue
        shiftRight(spec);
        queueLengthPerSpec[spec]++;
        patientNames[spec][0] = name;
        patientStatuses[spec][0] = st;
        return;
    }
}
void printAllPatient(){
    //iterate in each specialization
    for(int spec=1;spec<MAX_SPECIALIZATION+1;spec++){
        printSpecialization(spec, patientNames[spec], patientStatuses[spec]);
    }
}
void getNextPatient(){
    //read a requested specialization
    short int specNum;
    cout<< "Enter specialization: ";
    cin>> specNum;
    //pop patient from queue if there is patients
    if(queueLengthPerSpec[specNum] == 0){
        cout<<"No patients at the moment. Have rest, Dr\n";
        return;
    }
    cout<< patientNames[specNum][0] << " please go with the Dr\n";
    removeFromQueue(specNum);
    queueLengthPerSpec[specNum]--;
}
void system(){
    bool run = 1;
    while(run){
        short int choice;
        cout<< "Enter your choice:\n1) Add new patient\n2) Print all patient\n3) Get next patient\n4) Exit"<<endl;
        cin>>choice;
        switch(choice){
            case 1:{
                addNewPatient();
                break;
            }
            case 2:{
                cout<<"***************";
                printAllPatient();
                break;
            }
            case 3:{
                getNextPatient();
                break;
            }
            case 4:{
                run = 0;
                break;
            }
            default:{
                cout<<"Invalid number, please choose from the list"<<endl;
            }
        }
        cout<< endl;
    }
}
int main()
{
    system();
    return 0;
}
