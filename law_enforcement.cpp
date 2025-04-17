#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;

const int encryptionKey = 7;
const string filename = "Criminal Record History.txt";
string const SHOpassword = "SHO123";

class MaxHeap_Crime_Points;
class MaxHeapData;
class AVLTree;
class Graph;

class CriminalRecord
{
public:
    int caseNumber;
    string name;
    int age;
    string gender;
    string cnic;
    string phone;
    string carPlate;
    int challan;
    int robbery;
    int murder;
    int drugSelling;
    int crimePoints;
    string dateModified;

    friend class CriminalRecordList;

    CriminalRecord()
        : caseNumber(0), name(""), age(0), gender(), cnic(""),
          phone(""), carPlate(""), challan(0),
          robbery(0), murder(0), drugSelling(0),
          crimePoints(0), dateModified("") {}

    CriminalRecord(int caseNum, const string &n, int a, string g,
                   const string &c, const string &p, const string &cp,
                   int ch, int rb, int mu, int ds,
                   int crimePts, const string &dm)
        : caseNumber(caseNum), name(n), age(a), gender(g), cnic(c), phone(p),
          carPlate(cp), challan(ch), robbery(rb),
          murder(mu), drugSelling(ds), crimePoints(crimePts), dateModified(dm) {
             crimePoints = (challan + (drugSelling * 3) + (robbery * 5) + (murder * 10));
          }

    friend ostream &operator<<(ostream &out, const CriminalRecord *obj);
};

ostream &operator<<(ostream &out, const CriminalRecord *C)
{

    out << C->caseNumber << "           | " << C->name << " | "
        << C->age << " | " << C->gender << " | "
        << C->cnic << " | " << C->phone << " | "
        << C->carPlate << " | "
        << C->challan << " | "
        << C->robbery << " | " << C->murder << " | "
        << C->drugSelling << " | "
        << C->crimePoints << " | " << C->dateModified << endl
        << endl;

    return out;
}

int total_case = 12;

class AVLNode
{
public:
    CriminalRecord *C;
    AVLNode* next;

    AVLNode()
    {
        C = new CriminalRecord(); // Allocate a new CriminalRecord object
        
    }

    AVLNode(int caseNum, const string &n, int a, string g,
            const string &c, const string &p, const string &cp,
            int ch, int rb, int mu, int ds,
            int crimePts, const string &dm)
    {
        C = new CriminalRecord(caseNum, n, a, g, c, p, cp, ch, rb, mu, ds, crimePts, dm);
        next = NULL;
    }

    AVLNode(CriminalRecord *obj)
    {
        C = obj;
        next = NULL;
      
    }
};

class CriminalRecordList {

public:

    AVLNode* head;
    AVLNode* tail;
    CriminalRecordList() : head(nullptr), tail(nullptr) {}

    void push_with_tail(CriminalRecord *obj)
    {
        AVLNode* newNode = new AVLNode(obj);
        if(head==NULL)
        {
            tail = newNode;
            head = newNode;
            return;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
            return;
        }
    }

    void printing(){
        AVLNode* temp=head;
        while (temp!=NULL)
        {
            cout << temp->C;
            temp = temp->next;
        }
        return;
    }
};

class MinHeap_Case_Number
{

private:
    vector<CriminalRecord *> heap;

    void heapify(int first_non_root_child_index)
    {

        int nodes = heap.size();
        int mininum = first_non_root_child_index;
        int left_child = (2 * first_non_root_child_index) + 1;
        int right_child = (2 * first_non_root_child_index) + 2;

        if ((left_child < nodes) && ((heap[left_child]->caseNumber) <= (heap[mininum]->caseNumber)))
        {

            mininum = left_child;
        }

        if ((right_child < nodes) && (heap[right_child]->caseNumber < heap[mininum]->caseNumber))
        {

            mininum = right_child;
        }

        if (mininum != first_non_root_child_index)
        {

            swap(heap[mininum], heap[first_non_root_child_index]);
            heapify(mininum);
        }
    }

public:
    void insert(CriminalRecord *obj)
    {

        int nodes;

        if (heap.empty())
        {

            heap.push_back(obj);
        }
        else
        {

            nodes = heap.size();

            heap.push_back(obj);

            for (int i = (nodes - 1) / 2; i >= 0; i--)
            {

                heapify(i);
            }
        }
    }

    void pop_front()
    {

        int nodes = heap.size() - 1;

        if ((nodes + 1) == 0)
        {

            return;
        }
        else if ((nodes + 1) == 1)
        {

            heap.clear();
        }
        else
        {

            swap(heap[0], heap[nodes]);
            heap.pop_back();

            for (int i = (nodes - 1) / 2; i >= 0; i--)
            {

                heapify(i);
            }
        }
    }

    void print()
    {
        queue<CriminalRecord *> temp;
        CriminalRecord *ptr;
        int size = heap.size();
        for (int i = 0; i < size; i++)
        {
            temp.push(top());
            pop_front();
        }

        for (int i = 0; i < size; i++)
        {
            ptr = temp.front();
            temp.pop();
            cout << ptr;
            insert(ptr);
        }

        cout << endl;
    }

    CriminalRecord *top()
    {

        if (heap.empty())
        {

            return nullptr;
        }

        return heap[0];
    }
};

class MaxHeap_Crime_Points
{

private:
    vector<CriminalRecord *> heap;

    void heapify(int first_non_root_child_index)
    {

        int nodes = heap.size();
        int mininum = first_non_root_child_index;
        int left_child = (2 * first_non_root_child_index) + 1;
        int right_child = (2 * first_non_root_child_index) + 2;

        if ((left_child < nodes) && ((heap[left_child]->crimePoints) >= (heap[mininum]->crimePoints)))
        {

            mininum = left_child;
        }

        if ((right_child < nodes) && (heap[right_child]->crimePoints > heap[mininum]->crimePoints))
        {

            mininum = right_child;
        }

        if (mininum != first_non_root_child_index)
        {

            swap(heap[mininum], heap[first_non_root_child_index]);
            heapify(mininum);
        }
    }

public:
    void insert(CriminalRecord *obj)
    {

        int nodes;

        if (heap.empty())
        {

            heap.push_back(obj);
        }
        else
        {

            nodes = heap.size();

            heap.push_back(obj);

            for (int i = (nodes - 1) / 2; i >= 0; i--)
            {

                heapify(i);
            }
        }
    }

    void pop_front()
    {

        int nodes = heap.size() - 1;

        if ((nodes + 1) == 0)
        {

            return;
        }
        else if ((nodes + 1) == 1)
        {

            heap.clear();
        }
        else
        {

            swap(heap[0], heap[nodes]);
            heap.pop_back();

            for (int i = (nodes - 1) / 2; i >= 0; i--)
            {

                heapify(i);
            }
        }
    }

    void print()
    {
        queue<CriminalRecord *> temp;
        CriminalRecord *ptr;
        int size = heap.size();
        for (int i = 0; i < size; i++)
        {
            temp.push(top());
            pop_front();
        }

        for (int i = 0; i < size; i++)
        {
            ptr = temp.front();
            temp.pop();
            cout << ptr;
            insert(ptr);
        }

        cout << endl;
    }

    CriminalRecord *top()
    {

        if (heap.empty())
        {

            return nullptr;
        }

        return heap[0];
    }
};

class MaxHeapDate
{

private:
    vector<CriminalRecord *> heap;

    void heapify(int first_non_root_child_index)
    {

        int nodes = heap.size();
        int mininum = first_non_root_child_index;
        int left_child = (2 * first_non_root_child_index) + 1;
        int right_child = (2 * first_non_root_child_index) + 2;

        if ((left_child < nodes) && ((heap[left_child]->dateModified) >= (heap[mininum]->dateModified)))
        {

            mininum = left_child;
        }

        if ((right_child < nodes) && (heap[right_child]->dateModified > heap[mininum]->dateModified))
        {

            mininum = right_child;
        }

        if (mininum != first_non_root_child_index)
        {

            swap(heap[mininum], heap[first_non_root_child_index]);
            heapify(mininum);
        }
    }

public:
    void insert(CriminalRecord *obj)
    {

        int nodes;

        if (heap.empty())
        {

            heap.push_back(obj);
        }
        else
        {

            nodes = heap.size();

            heap.push_back(obj);

            for (int i = (nodes - 1) / 2; i >= 0; i--)
            {

                heapify(i);
            }
        }
    }

    void pop_front()
    {

        int nodes = heap.size() - 1;

        if ((nodes + 1) == 0)
        {

            return;
        }
        else if ((nodes + 1) == 1)
        {

            heap.clear();
        }
        else
        {

            swap(heap[0], heap[nodes]);
            heap.pop_back();

            for (int i = (nodes - 1) / 2; i >= 0; i--)
            {

                heapify(i);
            }
        }
    }

    void print()
    {
        queue<CriminalRecord *> temp;
        CriminalRecord *ptr;
        int size = heap.size();
        for (int i = 0; i < size; i++)
        {
            temp.push(top());
            pop_front();
        }

        for (int i = 0; i < size; i++)
        {
            ptr = temp.front();
            temp.pop();
            cout << ptr;
            insert(ptr);
        }

        cout << endl;
    }

    CriminalRecord *top()
    {

        if (heap.empty())
        {

            return nullptr;
        }

        return heap[0];
    }
};

class Graph
{
    vector<CriminalRecord *> adjlist[4];

public:
    void insert_graph(CriminalRecord *c)
    {

        if (c->cnic[15] == '1')
        {
            adjlist[0].push_back(c);
        }
        if (c->cnic[15] == '2')
        {

            adjlist[1].push_back(c);
        }
        if (c->cnic[15] == '3')
        {

            adjlist[2].push_back(c);
        }
        if (c->cnic[15] == '4')
        {

            adjlist[3].push_back(c);
        }
    }

    void print_dist1()
    {


        cout << "Criminals in the district North are as follows: " << endl;

        for (int i = 0; i < adjlist[0].size(); i++)
        {
            CriminalRecord *temp;
            temp = adjlist[0][i];
            cout << temp;
        }
    }
    void print_dist2()
    {

        

        cout << "Criminals in the district East are as follows: " << endl;

        for (int i = 0; i < adjlist[1].size(); i++)
        {
            CriminalRecord *temp;
            temp = adjlist[1][i];
            cout << temp;
        }
    }
    void print_dist3()
    {


        cout << "Criminals in the district West are as follows: " << endl;

        for (int i = 0; i < adjlist[2].size(); i++)
        {
            CriminalRecord *temp;
            temp = adjlist[2][i];
            cout << temp;
        }
        
    }
    void print_dist4()
    {

        

        cout << "Criminals in the district South are as follows: " << endl;
        for (int i = 0; i < adjlist[3].size(); i++)
        {
            CriminalRecord *temp;
            temp = adjlist[3][i];
            cout << temp;
        }
    }
};

MaxHeap_Crime_Points maxheapcrime;
unordered_map<string, CriminalRecord *> _map_cnic;
unordered_map<string, CriminalRecord *> _map_phone;
unordered_map<string, CriminalRecord *> _map_carplate;
unordered_map<int, CriminalRecord *> _map_caseNum;
Graph G;
MaxHeapDate maxheapdate;
MinHeap_Case_Number minheapcase;
CriminalRecordList L;

void main_insert(CriminalRecord* record){
            //LinkedList
            L.push_with_tail(record);

            // Heap
            maxheapcrime.insert(record);
            maxheapdate.insert(record);
            minheapcase.insert(record);
            
            // // Hashmap
            _map_cnic[record->cnic] = record;
            _map_phone[record->phone] = record;
            _map_carplate[record->carPlate] = record;
            

            // // Graph
            G.insert_graph(record);
}

class Filing
{

private:
    AVLNode *root;

public:
    void writeToFileHelper(ofstream &file)
    {   
        AVLNode* AVLnode = L.head;
        while (AVLnode)
        {
            
            file << (AVLnode->C->caseNumber) + encryptionKey << "|" << encrypt(AVLnode->C->name) << "|"
                 << (AVLnode->C->age) + encryptionKey << "|" << encrypt(AVLnode->C->gender) << "|"
                 << encrypt(AVLnode->C->cnic) << "|" << encrypt(AVLnode->C->phone) << "|"
                 << encrypt(AVLnode->C->carPlate) << "|" << (AVLnode->C->challan) + encryptionKey << "|"
                 << (AVLnode->C->robbery) + encryptionKey << "|" << (AVLnode->C->murder) + encryptionKey << "|"
                 << (AVLnode->C->drugSelling) + encryptionKey << "|" << (AVLnode->C->crimePoints) + encryptionKey << "|"
                 << encrypt(AVLnode->C->dateModified) << endl;
            AVLnode = AVLnode->next;
        }
    }

    string encrypt(string str)
    {
        string temp = str;
        for (int i = 0; i < temp.length(); i++)
        {
            temp[i] += encryptionKey;
        }
        return temp;
    }

    string decrypt(string str)
    {
        string temp = str;
        for (int i = 0; i < temp.length(); i++)
        {
            temp[i] -= encryptionKey;
        }
        return temp;
    }

    void readfromfileEncrypted()
    {
        ifstream file(filename, ios::in);

        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Ignore the header line

        while (getline(file, line))
        {
            stringstream iss;
            char *token;
            char *cstr = new char[line.length() + 1];
            strcpy(cstr, line.c_str());
            // Extracting values from the CSV line
            int caseNum;
            string name;
            int age;
            string gender;
            string cnic;
            string phone;
            string carPlate;
            int challan;
            int robbery;
            int murder;
            int drugSelling;
            int crimePoints;
            string dateModified;

            token = strtok(cstr, "|");
            iss << token;
            iss >> caseNum;
            iss.clear();
            caseNum -= encryptionKey;

            token = strtok(NULL, "|");
            name = decrypt(token);

            token = strtok(NULL, "|");
            iss << token;
            iss >> age;
            iss.clear();
            age -= encryptionKey;

            token = strtok(NULL, "|");
            gender = decrypt(token);

            token = strtok(NULL, "|");
            cnic = decrypt(token);


            token = strtok(NULL, "|");
            phone = decrypt(token);
            token = strtok(NULL, "|");
            carPlate = decrypt(token);

            token = strtok(NULL, "|");
            iss << token;
            iss >> challan;
            iss.clear();
            challan -= encryptionKey;

            token = strtok(NULL, "|");
            iss << token;
            iss >> robbery;
            iss.clear();
            robbery -= encryptionKey;

            token = strtok(NULL, "|");
            iss << token;
            iss >> murder;
            iss.clear();
            murder -= encryptionKey;

            token = strtok(NULL, "|");
            iss << token;
            iss >> drugSelling;
            iss.clear();
            drugSelling -= encryptionKey;

            token = strtok(NULL, "|");
            iss << token;
            iss >> crimePoints;
            iss.clear();
            crimePoints -= encryptionKey;

            token = strtok(NULL, "|");
            dateModified = decrypt(token);

            total_case++;
            // Creating CriminalRecord object and inserting into AVL tree
            CriminalRecord *record = new CriminalRecord(caseNum, name, age, gender, cnic, phone, carPlate,
                                                        challan, robbery, murder, drugSelling, crimePoints, dateModified);

            

            main_insert(record);
        }

        file.close();
    }

    void readfromfileDecrypted(string filename2)
    {
        ifstream file(filename2, ios::in);

        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Ignore the header line

        while (!file.eof())
        {    
            
            getline(file, line);
            if(line==""){
                break;
            }
            
            stringstream iss;
            char *token;
            char *cstr = new char[line.length() + 1];
            strcpy(cstr, line.c_str());
            // Extracting values from the CSV line
            int caseNum;
            string name;
            int age;
            string gender;
            string cnic;
            string phone;
            string carPlate;
            int challan;
            int robbery;
            int murder;
            int drugSelling;
            int crimePoints;
            string dateModified;

            token = strtok(cstr, "|");
            iss << token;
            iss >> caseNum;
            iss.clear();

            token = strtok(NULL, "|");
            name = token;

            token = strtok(NULL, "|");
            iss << token;
            iss >> age;
            iss.clear();

            token = strtok(NULL, "|");
            gender = token;

            token = strtok(NULL, "|");
            cnic = token;

            
            
            token = strtok(NULL, "|");
            phone = token;
            

            token = strtok(NULL, "|");
            carPlate = token;
            

            token = strtok(NULL, "|");
            iss << token;
            iss >> challan;
            iss.clear();

            token = strtok(NULL, "|");
            iss << token;
            iss >> robbery;
            iss.clear();

            token = strtok(NULL, "|");
            iss << token;
            iss >> murder;
            iss.clear();

            token = strtok(NULL, "|");
            iss << token;
            iss >> drugSelling;
            iss.clear();

            token = strtok(NULL, "|");
            iss << token;
            iss >> crimePoints;
            iss.clear();

            token = strtok(NULL, "|");
            dateModified = token;

            total_case++;
            // Creating CriminalRecord object and inserting into AVL tree
            CriminalRecord *record = new CriminalRecord(caseNum, name, age, gender, cnic, phone, carPlate,
                                                        challan, robbery, murder, drugSelling, crimePoints, dateModified);

            // cout << record;

           
           main_insert(record);

        }

        file.close();
    }

    void writeToFile()

    {
        ofstream file(filename, ios::out);

        if (!file.is_open())
        {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        // Write header
        file << "CaseNumber | Name | Age | Gender | CNIC | Phone | CarPlate | Challan | Robbery | Murder | Drug Selling | Crime Points | Date Modified" << endl;

        // Call the helper function to write records
        writeToFileHelper(file);

        file.close();

        cout << "Records written to file successfully." << endl;
    }

    void appendToFile()
    {   
        ofstream file(filename, ios::app);

        if (!file.is_open())
        {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        AVLNode* AVLnode = L.tail;
        while (AVLnode)
        {
            
            file << (AVLnode->C->caseNumber) + encryptionKey << "|" << encrypt(AVLnode->C->name) << "|"
                 << (AVLnode->C->age) + encryptionKey << "|" << encrypt(AVLnode->C->gender) << "|"
                 << encrypt(AVLnode->C->cnic) << "|" << encrypt(AVLnode->C->phone) << "|"
                 << encrypt(AVLnode->C->carPlate) << "|" << (AVLnode->C->challan) + encryptionKey << "|"
                 << (AVLnode->C->robbery) + encryptionKey << "|" << (AVLnode->C->murder) + encryptionKey << "|"
                 << (AVLnode->C->drugSelling) + encryptionKey << "|" << (AVLnode->C->crimePoints) + encryptionKey << "|"
                 << encrypt(AVLnode->C->dateModified) << endl;
            AVLnode = AVLnode->next;
        }
        file.close();
        cout << "Records written to file successfully." << endl;
    }
};

Filing F1;

class Driver
{

    bool isLetter(char ch)
    {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z' || ch == ' ');
    }

    bool isValidName(const string &name)
    {

        for (char ch : name)
        {
            if (!isLetter(ch))
            {
                return false;
            }
        }
        return true;
    }

    bool isValidCNIC(const string &input)
    {

        int hyphenCount = 0;

        for (char ch : input)
        {
            if (!((ch >= '0' && ch <= '9') || ch == '-'))
            {
                return false;
            }
            if (ch == '-')
            {
                hyphenCount++;
            }
        }

        return (hyphenCount == 2) && (input.length() == 15) && (input.find('-') != std::string::npos) && (input.rfind('-') != input.length() - 1);
    }

    bool isValidGender(char gender)
    {
        if (gender == 'm')
            gender = 'M';
        else if (gender == 'f')
            gender = 'F';
        return (gender == 'M' || gender == 'F');
    }

    bool isValidPhoneNumber(const string &phoneNumber)
    {

        if (phoneNumber.length() > 11 || phoneNumber.length() < 11)
        {
            return false; // Length is too long
        }

        for (char ch : phoneNumber)
        {
            if (!isdigit(ch))
            {
                return false;
            }
        }

        return true;
    }

    bool isValidINT(int num)
    {
        return (num >= 0 && num <= 99);
    }

    bool isValidDateFormat(const string &date)
    {
        if (date.length() != 10)
        {
            return false;
        }

        if (!(isdigit(date[0]) && isdigit(date[1]) && isdigit(date[2]) && isdigit(date[3]) && date[4] == '-' &&
              isdigit(date[5]) && isdigit(date[6]) && date[7] == '-' &&
              isdigit(date[8]) && isdigit(date[9])))
        {
            return false;
        }

        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));

        if (year < 1000 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31)
        {
            return false;
        }

        return true;
    }

    bool isValidCarNumberPlate(const string &plate)
    {
        // Check if the length is within the valid range
        if (plate.length() != 6)
        {
            return false;
        }

        // Check the first 3 characters are capital letters
        for (int i = 0; i < 3; ++i)
        {
            if (!isupper(plate[i]))
            {
                return false;
            }
        }

        // Check the last 3 characters are digits
        for (int i = 3; i < 6; ++i)
        {
            if (!isdigit(plate[i]))
            {
                return false;
            }
        }

        return true;
    }

public:
    void enterRecord()
    {
        string name, cnic, phoneNumber, carPlate, date, gender;
        int age, challan, robbery, murder, drug_selling, crimePoints;
        do
        {
            cout << "\nEnter name: ";
            fflush(stdin);
            getline(cin, name);
        } while (!isValidName(name));

        do
        {
            cout << "\nEnter Age: ";
            cin >> age;
        } while (!isValidINT(age));

        do
        {
            cout << "\nEnter Gender: ";
            cin >> gender;
        } while (!isValidGender(gender[0]));

        // do
        // {
            cout << "\nEnter CNIC: ";
            fflush(stdin);
            getline(cin, cnic);
        // } while (!isValidCNIC(cnic));
        cnic = " " + cnic + " ";

        do
        {
            cout << "\nEnter Phone Number: ";
            fflush(stdin);
            getline(cin, phoneNumber);
        } while (!isValidPhoneNumber(phoneNumber));
        phoneNumber = " " + phoneNumber + " ";

        do
        {
            cout << "\nEnter Car Plate: ";
            fflush(stdin);
            getline(cin, carPlate);
        } while (!isValidCarNumberPlate(carPlate));
       carPlate = " " +carPlate + " ";

        do
        {
            cout << "\nEnter number of challans: ";
            cin >> challan;
        } while (!isValidINT(challan));

        do
        {
            cout << "\nEnter number of robberies: ";
            cin >> robbery;
        } while (!isValidINT(robbery));

        do
        {
            cout << "\nEnter number of murders: ";
            cin >> murder;
        } while (!isValidINT(murder));

        do
        {
            cout << "\nEnter number of drug selling: ";
            cin >> drug_selling;
        } while (!isValidINT(drug_selling));

        // crimePoints = (challan + (drug_selling * 3) + (robbery * 5) + (murder * 10));

        do
        {
            cout << "\nEnter the date (yyyy-mm-dd): ";
            fflush(stdin);
            getline(cin, date);
        } while (!isValidDateFormat(date));

        total_case++;
        CriminalRecord *record = new CriminalRecord(total_case, name, age, gender, cnic, phoneNumber, carPlate,
                                                                challan,  robbery, murder, drug_selling,  crimePoints, date);
           main_insert(record);
           F1.appendToFile();
    }

    void searchRecord()
    {
        string cnic, carPlate, pn;
        int opt, cn;
        do
        {
            cout << endl
                 << "1. Seacrh by Car Plate" << endl
                 << "2. Search By CNIC" << endl
                 << "3. Search By Phone Number" << endl
                 << "4. Display Most Wanted criminal" << endl
                 << "5. Display most recently added record" << endl
                 << "6. Back" << endl;
            cout << "\nEnter choice (1-6): ";
            cin >> opt;
            switch (opt)
            {

            case 1:
                do
                {
                    cout << "\nEnter Car Plate: ";
                    fflush(stdin);
                    getline(cin, carPlate);
                } while (!isValidCarNumberPlate(carPlate));
                carPlate = " " + carPlate + " ";
                cout << _map_carplate[carPlate];
                return;

            case 2:
            //do
            //{
                    cout << "\nEnter CNIC: ";
                    fflush(stdin);
                    getline(cin, cnic);
                // } while (!isValidCNIC(cnic));
                cnic = " " + cnic + " ";
                cout << _map_cnic[cnic];
                
                return;

            case 3:
                do
                {
                    cout << "\nEnter Phone Number: ";
                    fflush(stdin);
                    getline(cin, pn);
                } while (!isValidPhoneNumber(pn));
                pn = " " + pn + " ";
                cout << _map_phone[pn];
                return;

            case 4:
                    cout << maxheapcrime.top();
                return;

            case 5:
                cout << maxheapdate.top();
                return;

            case 6:
                return;

            default:
                cout << "\nInvalid input!\n";
                break;
            }
        } while (1);
    }

    void DisplayDistrict()
    {
        int opt;
        do
        {
            cout<<endl<<"1. North\n2. East\n3. West\n4. South"<<endl;
            cout << "Enter district (1-4): ";
            cin >> opt;
            switch (opt)
            {
            case 1:
                G.print_dist1();
                return;
            case 2:
                G.print_dist2();
                return;
            case 3:
                G.print_dist3();
                return;
            case 4:
                G.print_dist4();
                return;
            default:
                cout << "\nInvalid input!\n";
                break;
            }
        } while (1);
    }

    void DisplaySorted()
    {
        int opt;
        do
        {
            cout << "\n1. Case Number (ascending)" << endl
                 << "2. Criminal Points (descending)" << endl
                 << "3. Date Modified (descending)" << endl
                 << "4. Go Back" << endl;
            cout << "Enter choice (1-4): ";
            cin >> opt;
            switch (opt)
            {
            case 1:
                minheapcase.print();
                return;
            case 2:
                maxheapcrime.print();
                return;
            case 3:
                maxheapdate.print();
                return;
            case 4:

                return;
            default:
                cout << "\nInvalid input!\n";
                break;
            }
        } while (1);
    }

    void verify_SHO_password()
    {
        int key_tries = 3;
        string k;
        do
        {
            if (key_tries < 1)
            {
                cout << "\nALARM RAISED!\n";
                exit(0);
            }
            cout << "\nTries for secret key remaining: " << key_tries << "\nEnter secret key: ";
            fflush(stdin);
            getline(cin, k);
            if (SHOpassword == k)
            {
                cout << "\nSecurity Key Verified!\n";
                break;
            }
            else
            {
                key_tries--;
                cout << "\nINVALID KEY!\n";
            }
        } while (1);
    }
};

void driver_func()
{
    Driver driver;
    // intro
    driver.verify_SHO_password();
    do
    {
        int option;
        cout << endl
             << "Please select the option: " << endl
             << "1. Enter a criminal record" << endl
             << "2. Search a Criminal Record" << endl
             << "3. Display sorted records" << endl
             << "4. Display criminal records of specific district" << endl
             << "5. Exit";

        cout << endl
             << "Enter your choice (1-5): ";
        cin >> option;

        switch (option)
        {
        case 1:
            driver.enterRecord();
            break;
        case 2:
            driver.searchRecord();
            break;
        case 3:
            driver.DisplaySorted();
            break;
        case 4:
            driver.DisplayDistrict();
            break;
        case 5:
            return;
        default:
        cout << "Invalid Input\n";
        break;
        }
    } while (1);
}




int main()
{
    // F1.readfromfileDecrypted("Decrypted.txt");

    F1.readfromfileEncrypted();

    // auto start_time = high_resolution_clock::now();
    // for (int i = 0; i < total_case; i++)
    // {
    // minheapcase.pop_front();
    // }
    // auto end_time = high_resolution_clock::now();

    // auto duration = duration_cast<microseconds>(end_time - start_time);
    // cout << "Time taken min heap: " << duration.count() << " microseconds" << endl;

     driver_func();

    // F1.writeToFile();

    return 0;
}