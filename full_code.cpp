#include "bits/stdc++.h"
#include "fstream"
using namespace std;
unordered_map<string,vector<string>>specialties;
int displayBill(unordered_map<string,int>& med)
{
    ifstream csvFile("medicines.csv");
   string line;
    double totalCost = 0.0;

    while (getline(csvFile, line)) {
        istringstream iss(line);
        string medicineName;
        double medicinePrice;

        if (getline(iss, medicineName,',') && iss >> medicinePrice) {
            if (med.find(medicineName) != med.end()) {
                int quantity = med[medicineName];
                totalCost += medicinePrice * quantity;
                med[medicineName]=medicinePrice;
            }
        }
    }

    csvFile.close();

    return totalCost;


}
class doctor
{
    private:
    string speciality,doc;
    public:
    doctor()
    {

    }
    void findSpeciality(string problemname)
    {
       for(const auto&[key,value]:specialties)
       {
            for(auto &prob:value)
            {
                if(prob==problemname)
                {
                    speciality=key;
                    break;
                }
            }
       }

    }
    string findDoctor()
    {
        fstream fin;
        fin.open("doctors.csv", ios::in);
        vector<string> row;
        string line, word, temp;
        string find;
        while (fin >> temp) {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word,',')) {
            row.push_back(word);
        }
        find = row[1];

        if(find==speciality){
           doc=row[0];break;
        }
        }
        return doc;
  
    }



};
class patients
{
    private:
    string name,problem;
    public:
    patients()
    {
        
    }
    void record(string name,string problem)
    {
    fstream fout;
    fout.open("patients.csv", ios::out | ios::app);
     fout<<name<<","<<problem<<endl;
     cout<<"Details Recorded Successfully\n";
    }


};
void initialize()
{   
    specialties["Cardiology"] = {"Chest pain", "Shortness of breath", "Irregular heartbeat"};
    specialties["Dermatology"] = {"Skin rash", "Itching", "Acne"};
    specialties["Orthopedics"] = {"Joint pain", "Fracture", "Back pain"};
    specialties["Pediatrics"] = {"Fever", "Cough", "Developmental delay"};
    specialties["Gastroenterology"] = {"Abdominal pain", "Nausea", "Diarrhea"};
    specialties["Gynecology"] = {"Irregular periods", "Pregnancy", "Pelvic pain"};
    specialties["Neurology"] = {"Headache", "Seizures", "Numbness"};
    specialties["Ophthalmology"] = {"Blurred vision", "Eye pain", "Redness"};
    specialties["Psychiatry"] = {"Depression", "Anxiety", "Hallucinations"};
    specialties["Endocrinology"] = {"Fatigue", "Weight changes", "Thyroid problems"};
}
int main()
{
    char input;
    patients p;
    doctor d;
    string name,problem,date_of_appointment,doc;
    initialize();
    do
    {
     cin>>input;
     switch(input)
     {
        case 'i':
                 cout<<"Enter patient name and problem:\n";
                 cin>>name>>problem;
                 p.record(name,problem);
                 break;
        case 'c':
                  cout<<"Enter problem and the date of appointment\n";
                  cin>>problem>>date_of_appointment;
                  d.findSpeciality(problem);
                  doc=d.findDoctor();
                  cout<<"You have been appointed to "+doc+" on "+date_of_appointment<<endl;
                  break;
        case 'b':
                 cout<<"BILL:\n";
                 int n;
                 cin>>n;
                 unordered_map<string,int>med;
                 for(int i=0;i<n;++i)
                 {
                    string med_name;
                    cin>>med_name;
                    int quantity;
                    cin>>quantity;
                    med[med_name]=quantity;
                 }
                 int amount=displayBill(med);
                 for(const auto&[key,value]:med)
                 cout<<key<<" : "<<value<<endl;
                 cout<<"Total Amount : "<<amount<<endl;
                 break;


     }
    } while(input!='q');

}