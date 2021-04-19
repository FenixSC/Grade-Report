#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>
#include <iomanip>

using namespace std;
class student{
  public:
  student(string f, string l){
    fname = f;
    lname = l;
  }
  void inputGrade(float n){
    grades.push_back(n);
  }
  float getAvg(){
    auto n = grades.size();
    float average = 0.0f;
    if(n != 0){
      average = (accumulate(grades.begin(), grades.end(), 0.0)/n);
    }
    return average;
  }
  float getMax(){
    float max = grades.at(0);
    for(auto i: grades){if(i>max)max = i;}
    return max;
  }

  string getName(){
    return fname+" "+lname;
  }
  
  char letterGrade(){
    float avg = getAvg();
    return (avg>=90)?('A'):((avg>=80)?('B'):((avg>=70)?('C'):((avg>=60)?('D'):('F'))));
  }
  string getTestGrade(){
    ostringstream obs;
    for(auto i: grades){
      obs<<fixed<<setprecision(2)<<i<<" ";
    }
    return obs.str();
  }

  private:
  vector<float> grades;
  string fname = "";
  string lname = "";

};
float classAverage(vector<student> students, int studentNum){
  float avg,total = 0.0;
  for(int i =0;i<studentNum;i++){
    total += students.at(i).getAvg();
    avg = total/studentNum;
  }
  return avg;
}
float maxGrade(vector<student> students, int studentNum){
  float max=0;
  for(int i=0;i<studentNum;i++){
    if(students.at(i).getMax() >= max){
      max = students.at(i).getMax();
    }
  }
  return max;
}

int main() {
  string sp = " ";
  vector<student> students;
  string input, fname, lname, dataFile;
  int numGrades = 5;
  int numStudent = 0;

  cout<<"Input text file name: ";
  cin>>dataFile;
  ifstream f1;
  f1.open(dataFile);

  while(getline(f1,input)){
    istringstream sso(input);
    numStudent++;
    sso >> fname;
    sso >> lname;
    student s(fname, lname);
    for(int i =0;i<numGrades;i++){
      if(!sso){break;}
      float n;
      sso >> n;
      s.inputGrade(n);
    }
    students.push_back(s);
  }
  f1.close();
  ofstream ofile;
  ofile.open("GradeReport.txt");

   cout<<"\nCalculated the data of "<<numStudent<<" studens and outputted to GradeReport.txt"<<endl;

  for(int a=0; a<numStudent;a++){
    ofile << students.at(a).getName();
    if(students.at(a).getName().size() < 30){
      int ex = 0;
      ex = 30 - students.at(a).getName().size();
      for(int c = 0;c<ex;c++){
        ofile<<sp;
      }
    }    
    ofile << students.at(a).getTestGrade()<<"Average: "<< students.at(a).getAvg()
    <<", Letter Grade: "<<students.at(a).letterGrade();
    ofile <<endl;
  }
  ofile<<fixed<<setprecision(2);
  ofile<<"Overall Average: "<<classAverage(students, numStudent)
  <<", Highest Grade "<<maxGrade(students, numStudent);

  return 0;
}


