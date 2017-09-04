/****************************************************************************
  FileName     [ p2Table.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define member functions of class Row and Table ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2016-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#include "p2Table.h"

using namespace std;

void cta(string letter)
{
    for (unsigned int i = 0; i < letter.length(); i++)
    {
        char x = letter.at(i);
        cout << int(x) << "\t";
    }
    cout << endl;
}

string distinguish_enter_type(const string& csvFile){
    const char* filename = csvFile.c_str();
    fstream file;
    file.open(filename);
    stringstream ss;
    copy(istreambuf_iterator<char>(file),
     istreambuf_iterator<char>(),
     ostreambuf_iterator<char>(ss));
    string record = ss.str();
    if(record.find("\r\n")!=string::npos)
        return "\n";
    if(record.find("\r")!=string::npos)
        return "\r";
    if(record.find("\n")!=string::npos)
        return "\n";
}

// Implement member functions of class Row and Table here
bool
Table::read(const string& csvFile)
{
    string MAX_STR = to_string(INT_MAX);
    const char* filename = csvFile.c_str();
    fstream file;
    file.open(filename);
    string line;
    int dot=0;
    int r=0;
    while(getline(file, line, distinguish_enter_type(csvFile))){
        stringstream ss(line);
        string item;
        vector<int> vec;
        while(getline(ss, item, ',')){
            if(item==""||item=="\r"){
                vec.push_back(INT_MAX);
                dot++;
            }
            else{
                vec.push_back(atoi(item.c_str()));
                r++;
            }
        }
        if((ss.rdbuf()->in_avail()==0)&&(item.empty())){
            vec.push_back(INT_MAX);
        }
        _nCols = vec.size();
        Row temp(vec);
        _rows.push_back(temp);
    }
    cout << "real num:" << r << ", dot:" << dot << endl ;
    return true; // TODO
}

Row::Row(vector<int> vc){
    _data=new int[vc.size()];
    for(unsigned int i=0;i<vc.size();i++){
        _data[i]=vc[i];
    }
}

void Table::print(){
    //cout<<"Let print it!\n";
    for(unsigned int i=0;i<_rows.size();i++){
       for(unsigned int j=0;j<_nCols;j++){
            if(_rows[i][j]==INT_MAX){ cout << setw(4) <<'.'; }
            else cout << setw(4) <<_rows[i][j];
        }
        cout << endl;
    }
}

/*
 *
   int SUM(int);
   int MAX(int);
   int MIN (int);
   int DIST (int);
   double AVE (int);
 */
void Table::command(string ins){
    string MAX_STR = to_string(INT_MAX);
    stringstream input(ins);
    string str;
    vector<int> manip;
    vector<string> arg;
    while(getline(input,str,' ')){arg.push_back(str);}
    unsigned int arg_size = (arg.size());
    unsigned int first_num = INT_MAX;
    if(arg_size>1){ first_num = (atoi(arg[1].c_str()));}
    if(arg[0]=="SUM"){
        if(arg_size<2){ cout << "Please Input the Number of Column You Want to Manipulate Together!\n"; }
        else if((!(first_num<_nCols)&&(first_num>=0))||arg_size>2){ cout << "Please Input the Right Number of Column to Manipulate!\n"; }
        else{
            int sum=0;
            bool flag=0;
            for(unsigned int i=0;i<_rows.size();i++){
                if(_rows[i][first_num]!=INT_MAX){
                    sum += _rows[i][first_num];
                    flag=1;
                }
            }
            if(!flag){cout << "Error: This is a NULL column!!\n";}
            else cout<<"The summation of data in column #" << arg[1] << " is " << sum << ".\n";
        }
    }
    else if(arg[0]=="MAX"){
        if(arg_size<2){ cout << "Please Input the Number of Column You Want to Manipulate Together!\n"; }
        else if(!(first_num<_nCols&&(first_num>=0))||arg_size>2){ cout << "Please Input the Right Number of Column to Manipulate!\n"; }
        else{
            int max=INT_MIN;
            for(unsigned int i=0;i<_rows.size();i++){
                if(_rows[i][first_num]!=INT_MAX){
                    int temp = _rows[i][first_num];
                    if(max<temp){max=temp;}
                }
            }
            if(max==INT_MIN){cout << "Error: This is a NULL column!!\n";}
            else cout<<"The maximum of data in column #" << arg[1] << " is " << max << ".\n";
        }
    }
    else if(arg[0]=="MIN"){
        if(arg_size<2){
            cout << "Please Input the Number of Column You Want to Manipulate Together!\n";
        }
        else if(!(first_num<_nCols&&first_num>=0)||arg_size>2){
            cout << "Please Input the Right Number of Column to Manipulate!\n";
        }
        else{
            int min=INT_MAX;
            for(unsigned int i=0;i<_rows.size();i++){
                if(_rows[i][first_num]!=INT_MAX){
                    int temp = _rows[i][first_num];
                    if(min>temp){
                        min=temp;
                    }
                }
            }
            if(min==INT_MAX){
                cout << "Error: This is a NULL column!!\n";
            }
            else
                cout<<"The minimum of data in column #" << arg[1] << " is " << min << ".\n";
        }
    }
    else if(arg[0]=="DIST"){
        if(arg_size<2){
            cout << "Please Input the Number of Column You Want to Manipulate Together!\n";
        }
        else if(!(first_num<_nCols&&first_num>=0)||arg_size>2){
            cout << "Please Input the Right Number of Column to Manipulate!\n";
        }
        else{
            int max=INT_MIN;
            for(unsigned int i=0;i<_rows.size();i++){
                if(_rows[i][first_num]!=INT_MAX){
                    int temp = _rows[i][first_num];
                    if(max<temp){
                        max=temp;
                    }
                }
            }
            int min=INT_MAX;
            for(unsigned int i=0;i<_rows.size();i++){
                if(_rows[i][first_num]!=INT_MAX){
                    int temp = _rows[i][first_num];
                    if(min>temp){
                        min=temp;
                    }
                }
            }
            if((min==INT_MAX)||(max==INT_MIN)){
                cout << "Error: This is a NULL column!!\n";
            }
            else
                cout <<"The distinct count of data in column #" << arg[1] << " is " << max-min << ".\n";
        }
    }
    else if(arg[0]=="AVE"){
        if(arg_size<2){
            cout << "Please Input the Number of Column You Want to Manipulate Together!\n";
        }
        else if(!(first_num<_nCols&&first_num>=0)||(arg_size>2)){
            cout << "Please Input the Right Number of Column to Manipulate!\n";
        }
        else{
            int sum=0;
            int counter=0;
            for(unsigned int i=0;i<_rows.size();i++){
                if(_rows[i][first_num]!=INT_MAX){
                    sum += _rows[i][first_num];
                    counter++;
                }
            }
            if(counter==0){
                cout << "Error: This is a NULL column!!\n";
            }
            else{
                double d_sum = static_cast <double> (sum);
                double d_cter = static_cast <double> (counter);
                cout<<"The average of data in column #" << arg[1] << " is " << fixed << setprecision(1) << d_sum/d_cter << ".\n";
            }
        }
    }
    else if(arg[0]=="ADD"){
        if(arg_size-1 != _nCols){
            cout << "Please Input Exactly #columns Arguments for Adding a New Row!\n";
        }
        else{
            Row temp(arg_size-1);
            for(unsigned int i=1;i<arg_size;i++){
                if(arg[i]=="."){
                    temp[i-1]=INT_MAX;
                }
                else{
                    temp[i-1]=atoi(arg[i].c_str());
                }
            }
            _rows.push_back(temp);
        }
    }
    else if(arg[0]=="EXIT"){
        exit(0);
    }
    else if(arg[0]=="PRINT"){
        this->print();
    }
    else{
        cout << "Please Input the Right Command!\n";
    }
}


