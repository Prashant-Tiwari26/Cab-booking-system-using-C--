
#include <bits/stdc++.h>
//#include<stdlib.h>
//#include<fstream>
//#include<string>
#include <conio.h>
#include <Windows.h>

using namespace std;
int mainmenu();
int choice;
// bool cinfail;
int confirmation;
string username, password, password2;
#define v 32     // No of Locations
float dista = 0; // Minimun Distance Of Locations

class Cab;
vector<Cab> random;
vector<int> path; //
vector<string> locations_list;

class Cab
{
private:
    string driver_name;
    string driver_contact_number;
    string car_name;
    string car_number;
    float rate;
    float rating;
    int no_of_journeys_completed;

public:
    Cab cab(); // Default Constructor
    Cab(string d_name, string d_number, string c_name, string c_number, float Rate, float ratings, int journey)
    {
        ofstream out;
        out.open("driver.txt", ios::app);
        driver_name = d_name;
        driver_contact_number = d_number;
        car_name = c_name;
        car_number = c_number;
        rate = Rate;
        rating = ratings;
        no_of_journeys_completed = journey;

        out << driver_name << " " << driver_contact_number << " " << car_name << " " << car_number << " " << rate << " " << rating << " " << journey << endl;

        out.close();
    }

    float calculate_price();
    void display_cab_info();
    void get_reviews();
};

Cab search_cabs();

// void randomize_cabs();

void print_locations();

void payment();

string get_perfect_name(string s);

void dijkstra(int edges[v][v], int source, int destination);

int find_min_vertex(int distance[], bool visited[], int n);

void print_solution(int distance[], int n, int parent[], int source, int destination);

void print_path(int parent[], int destination);

int mainmenu();

Cab search_cabs()
{

    int random_index = rand() % random.size();
    return random[random_index];
}
/*int randomfunc(int j)
{
    return rand() % j;
}*/

/*void randomize_cabs()
{
    srand(unsigned(time(0)));
    random_shuffle(random.begin(),random.end(),randomfunc);
}*/

float Cab::calculate_price()
{
    float price = (float)dista * (this->rate);
    return price;
}

void print_locations()
{
    int i = 1;
    cout << "\tALL THE LOCATIONS ARE LISTED BELOW: " << endl;
    for (auto &x : locations_list)
    {

        cout << "\t\t" << i << ".)"
             << "\t" << x << endl;
        i++;
    }
}

void Cab::display_cab_info()
{
    cout << "\n\n\tDRIVER'S DETAILS...";
    cout << "\n\n\tDrive name is: " << driver_name;
    cout << "\n\tDriver no: " << driver_contact_number;
    cout << "\n\tCar name: " << car_name;
    cout << "\n\tCar no: " << car_number;
    cout << "\n\tRate per km: " << rate;
    cout << "\n\tRating: " << rating;
    cout << "\n\tNo of journey completed yet: " << no_of_journeys_completed;
}

void payment()
{
    cout << "\t\tPAYMENT RECEIVED!! THANKS FOR CHOOSING US";
}

void Cab::get_reviews()
{
    string s;
    cin.ignore();
    cout << "\n\n\t\tEnter Your Feedback: ";
    getline(cin, s);
    float stars;
    cout << "\n\n\t\tGive Ratings: ";
    cin >> stars;
    rating = ((rating * no_of_journeys_completed) + stars) / (no_of_journeys_completed + 1);
}

void print_path(int parent[], int destination) // function to print path between source and destination
{
    if (parent[destination] == -1)
    {
        return;
    }
    print_path(parent, parent[destination]);

    path.push_back(destination);
    // cout<<destination<<" ";
}
void print_journey()
{
    cout << "\n\t\t\t   JOURNEY STARTED....\n";
    for (int i = 0; i < path.size(); i++)
    {
        cout << "\t\t-------------------------------------------\n";
        Sleep(5000);
        cout << "\t\t\t  You Reached: " << locations_list[path[i]] << endl;
    }
}

void print_solution(float distance[], int n, int parent[], int source, int destination) // function to print distance and
{                                                                                       // call print_path function
    path.clear();
    cout << "\n\nJourney" << endl;
    cout << locations_list[source] << " --> " << locations_list[destination];
    cout << "\n\nDistance(Km)" << endl;
    cout << distance[destination] << " Km";
    cout << "\n\nPath\n";
    cout << locations_list[source];
    print_path(parent, destination);
    float prev;
    for (auto x : path)
    {
        cout << " --> "
             << " (" << distance[x] - prev << ")" << locations_list[x];
        prev = distance[x];
    }
    cout << endl;
}

int find_min_vertex(float distance[], bool visited[], int n) // function to find min distance vertex
{
    int min_vertex = -1;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && (min_vertex == -1 || distance[i] < distance[min_vertex]))
        {
            min_vertex = i;
        }
    }
    return min_vertex;
}

void dijkstra(float edges[v][v], int source, int destination) // function to implement dijkstra algorithm with some modification
{
    path.clear();
    int n = v;
    float distance[n];
    bool visited[n];
    int parent[n]; // parent array to store the shortest path tree
    for (int i = 0; i < n; i++)
    {
        parent[source] = -1;
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[source] = 0; // distance of source vertex is 0
    for (int i = 0; i < n; i++)
    {
        int min_vertex = find_min_vertex(distance, visited, n);
        visited[min_vertex] = true;
        for (int j = 0; j < n; j++)
        {
            if (edges[min_vertex][j] != 0 && !visited[j]) // there should be an edge and the vertex should not be visited
            {
                float dist = distance[min_vertex] + edges[min_vertex][j];
                if (dist < distance[j])
                {
                    parent[j] = min_vertex;
                    distance[j] = dist;
                }
            }
        }
    }
    dista = distance[destination];
    print_solution(distance, n, parent, source, destination);
}

string get_perfect_name(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (i == 0)
        {
            if (!isupper(s[i]))
                s[i] = toupper(s[i]);
        }
        else
        {
            if (!islower(s[i]))
                s[i] = tolower(s[i]);
        }
    }
    return s;
}

void writetofile(string username)
{
    ofstream writefile;
    string file = username + ".txt";
    writefile.open(file.c_str());
    writefile << password;
    writefile.close();
    cout << "\n\n\tYOU REGISTERED SUCCESSFULLY.......";
    getch();
}

void readtofile(string username)
{
    ifstream readfile;
    string file = username + ".txt";
    readfile.open(file.c_str()); // Check wheather string is null or not
    readfile >> password;
    readfile.close();
}

int login()
{
    int j = 0;
    cout << "\n\tPlease enter your username: ";
    getline(cin, username);
    cout << "\n\tPlease enter the password: ";
    cin >> password2;
    readtofile(username);
    if (password == password2)
    {

        system("cls");
        j = j + 1;
        return 1;
    }

    else
    {

        system("cls");
        cout << "\n\t\t\tUNREGISTERED USER.......";
        getch();
        system("cls");
        return j;
    }
}

void registerpassword()
{
    cout << "\n\tPlease enter the password: ";
    cin >> password;
    cout << "\n\tPlease renter your password: ";
    cin >> password2;
    if (password == password2)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        writetofile(username);
    }
    else
    {
        cout << "\n\n\t\tSorry password doesn't match " << endl;
        registerpassword();
    }
}

void registerme()
{

    cout << "\n\tPlease enter your username: ";
    getline(cin, username);
    registerpassword();
}

void exit()
{
    exit(0);
}

int mainmenu()
{
    int c;
    cout << "\tHello,Would you like to log in or register\n\t[1] Login\n\t[2] Register\n\t[3] Exit\n\n\tEnter your choice: ";
    cin >> c;
    return c;
}

int main()
{
    srand(unsigned(time(0)));
    Cab c1("Aarav", "9874356321", "Altos", "4536", 14, 4, 67);
    Cab c2("Aditya", "9834769721", "Mahindra", "4527", 14, 3.5, 60);
    Cab c3("Bhagat", "9863735383", "Alto", "3652", 14, 4, 47);
    Cab c4("Binod", "9853821437", "Honda City", "9854", 14, 4.2, 97);
    Cab c5("Sanjay", "9845265347", "Toyota", "2541", 14, 4.1, 71);
    Cab c6("Deepak", "9874652342", "Hyundai", "8524", 14, 4.4, 7);
    Cab c7("Lal Bahadur", "9874356342", "Alto", "9632", 14, 3.6, 32);
    Cab c8("Suraj", "6785456321", "Honda", "8564", 14, 3.4, 67);
    Cab c9("Abhinav", "9654824515", "Mahindra", "4233", 14, 4.4, 27);
    Cab c10("Salman Khan", "9874325896", "Chervolet", "1593", 14, 4, 43);
    Cab c11("Ansh", "9624515879", "Altos", "5241", 14, 3.9, 23);
    Cab c12("Bharat", "6854721521", "Maruti", "7531", 14, 3.5, 65);
    Cab c13("Yash", "9874852476", "Maruti", "9999", 14, 4, 12);
    Cab c14("Shivam", "9854751125", "suzuki", "8888", 14, 4.5, 29);
    Cab c15("Shubham", "9854276824", "Suzuki", "7777", 14, 4, 98);
    Cab c16("Ramesh", "8576248617", "Honda", "8426", 14, 4, 100);
    Cab c17("Raju", "9724653819", "Hyundai", "8547", 14, 4, 23);
    Cab c18("Piyush", "9765423845", "Tata", "6521", 14, 4, 90);
    Cab c19("Pratik", "9754386154", "Tata", "3321", 14, 4, 32);
    Cab c20("Karan", "9864547245", "Altos", "5252", 14, 4.2, 25);

    random.push_back(c1);
    random.push_back(c2);
    random.push_back(c3);
    random.push_back(c4);
    random.push_back(c5);
    random.push_back(c6);
    random.push_back(c7);
    random.push_back(c8);
    random.push_back(c9);
    random.push_back(c10);
    random.push_back(c11);
    random.push_back(c12);
    random.push_back(c13);
    random.push_back(c14);
    random.push_back(c15);
    random.push_back(c16);
    random.push_back(c17);
    random.push_back(c18);
    random.push_back(c19);
    random.push_back(c20);

    locations_list.push_back("Shadipur");
    locations_list.push_back("Patel nagar");
    locations_list.push_back("Karol bagh");
    locations_list.push_back("Jhandewalan");
    locations_list.push_back("Anand parbat");
    locations_list.push_back("Inderlok");
    locations_list.push_back("Shastri nagar");
    locations_list.push_back("New subhash place");
    locations_list.push_back("Punjabi bagh");
    locations_list.push_back("Moti nagar");
    locations_list.push_back("Kirti nagar");
    locations_list.push_back("Rajouri garden");
    locations_list.push_back("Mayapuri");
    locations_list.push_back("Naraina");
    locations_list.push_back("Rajendra place");
    locations_list.push_back("Dhaula kuan");
    locations_list.push_back("Gole market");
    locations_list.push_back("Ram krishan ashram");
    locations_list.push_back("Rajiv chowk");
    locations_list.push_back("Yamuna bank");
    locations_list.push_back("Subhash nagar");
    locations_list.push_back("Uttam nagar");
    locations_list.push_back("Nawada");
    locations_list.push_back("Dwarka mor");
    locations_list.push_back("Dwarka");
    locations_list.push_back("Dwarka sector 21");
    locations_list.push_back("Najafgarh");
    locations_list.push_back("Vikaspuri");
    locations_list.push_back("Paschim vihar");
    locations_list.push_back("Nangloi");
    locations_list.push_back("Azadpur");
    locations_list.push_back("Rohini");

    Cab one = search_cabs();
    Cab two = search_cabs();
    Cab three = search_cabs();
    float pr; // Store price
    string source_location, destination_location;
    int source, destination;
    float edges[v][v] = {{0, 1.8, 0, 0, 3, 2, 0, 0, 3.1, 1, 1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {1.8, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {3, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {2, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.2, 0},
                         {0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 4, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.8, 2.4},
                         {3.1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 2, 2.8, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2.1, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 3, 4.9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2.9, 1, 0, 0, 0, 0, 4.6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.9, 0, 3.2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3.2, 0, 2.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2.8, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 5.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 4.6, 0, 0, 0, 0, 0, 0, 0, 2.7, 0, 0, 0, 0, 0, 0, 2.4, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.9, 0, 0, 0, 0, 0, 0, 0, 2.7, 0, 2, 0, 0, 0, 0, 1.6, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1.2, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.2, 0, 2, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1.5, 4, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.5, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.6, 0, 0, 0, 0, 0, 0, 2.2, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.4, 0, 0, 0, 0, 0, 0, 2.2, 0, 1.8, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.8, 0, 0, 0},
                         {0, 0, 0, 0, 0, 4.2, 0, 2.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.7},
                         {0, 0, 0, 0, 0, 0, 0, 2.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.7, 0}};

    system("color 3E");
    cout << "  \t\t\t\t\t============================================================================= ";
    cout << "\n  \t\t\t\t\t******************|C A B  B O O K I N G  S Y S T E M|************************\n";
    cout << "  \t\t\t\t\t============================================================================= " << endl;

    cout << "\n\n\t\t\t\t\t\t\tBY:-Prashant Tiwari";
    cout << "\n\t\t\t\t\t\t\t    Rajesh Chandela";
    getch();
    while (1) // if we give wrong choice in menu its reprint menu
    {
        system("cls");

        int C2;
    line:
        C2 = mainmenu();

        cin.clear();
        cin.ignore(10000, '\n');

        switch (C2) // Choice between login, register and exit
        {
        case 1:
            int g;
            g = login();
            if (g == 0)
                goto line;
            else
            {
                print_locations();
                cin.ignore();
                cout << endl;
                while (1) // run until correct source doesn't enter
                {
                    cout << "\n\tEnter the Location: ";
                    getline(cin, source_location);

                    source_location = get_perfect_name(source_location);

                    auto source_itr = find(locations_list.begin(), locations_list.end(), source_location);
                    if (source_itr != locations_list.end())
                    {
                        source = source_itr - locations_list.begin();
                        break;
                    }
                    else
                        cout << "\n\tLOCATION ENTERED IS WRONG!! PLEASE ENTER THE CORRECT LOCATION\n"
                             << endl;
                }

                while (1) // run until correct destination doesn't enter
                {
                    cout << "\n\tEnter the Destination: ";

                    getline(cin, destination_location);

                    destination_location = get_perfect_name(destination_location);

                    auto destination_itr = find(locations_list.begin(), locations_list.end(), destination_location);
                    if (destination_itr != locations_list.end())
                    {
                        destination = destination_itr - locations_list.begin();
                        break;
                    }
                    else
                        cout << "\n\tLOCATION ENTERED IS WRONG!! PLEASE ENTER THE CORRECT LOCATION\n"
                             << endl;
                }
                cout << endl;
                system("cls");
                cout << "\n\n\tYour locations is " << source_location << "\n\tYou want to go " << destination_location;
                dijkstra(edges, source, destination);
                cout << "\n\n\t Press any key to continue..";
                getch();
                cout << "\n\n\t\tSEARCHING CABS............";
                Sleep(5000);
                system("cls");
                cout << "\n\n\tThese are the nearby cabs available: " << endl;
                one.display_cab_info();
                two.display_cab_info();
                three.display_cab_info();
                int cc; // cab choosed
                while (1)
                {
                    cout << "\n\n\tEnter which cab you want to book: ";
                    cin >> cc;
                    switch (cc)
                    {
                    case 1:
                        system("cls");
                        cout << "\n\n\t\t YOUR CAB DETAILS:";
                        one.display_cab_info();
                        pr = one.calculate_price();
                        cout << "\n\tTotal price: " << pr << " Rs";
                        int p;
                        cout << "\n\n\tWant to book cab or not: \n\n\t1.Yes\n\t2.No";
                        cout << "\n\n\tEnter your choice:";
                        cin >> p;
                        if (p == 2)
                        {
                            system("cls");
                            cout << "\t\t\n\n\n\t THANKS...........\n\n\n";
                        }
                        else
                        {
                            system("cls");
                            cout << "\n\n\t\t CAB BOOKED....";
                            cout << "PRESS ANY KEY....";
                            getch();
                            system("cls");
                            print_journey();
                            cout << "\t\t-------------------------------------------";
                            cout << "\n\n\t\t YOU REACHED....";
                            getch();
                            system("cls");
                            cout << "\n\n\n\t\t\tPress any key";
                            getch();
                            system("cls");
                            int i;
                            cout << "\n\n\n\t\t\tPAYMENTS OPTIONS:\n\t\t1.Cash\n\t\t2.Online Modes" << endl;
                            cout << "\n\t\tEnter your choice: ";
                            cin >> i;
                            Sleep(3000);
                            cout << "\n\n\n";
                            payment();
                            cout << endl;
                            one.get_reviews();
                            cout << "\n\n\n\t\t\t THANKS...........\n\n\n";
                            exit();
                        }
                        break;

                    case 2:
                        system("cls");
                        cout << "\n\n\t\t YOUR CAB DETAILS:";
                        two.display_cab_info();
                        pr = two.calculate_price();
                        cout << "\n\tTotal price: " << pr << " Rs";
                        int p2;
                        cout << "\n\n\tWant to book cab or not:\n\n\t1.Yes\n\t2.No";
                        cout << "\n\n\tEnter your choice:";
                        cin >> p2;
                        if (p2 == 2)
                        {
                            system("cls");
                            cout << "\t\t\n\n\n\t THANKS...........\n\n\n";
                        }
                        else
                        {
                            system("cls");
                            cout << "\n\n\t\t CAB BOOKED....";
                            cout << "PRESS ANY KEY....";
                            getch();
                            system("cls");
                            print_journey();
                            cout << "\t\t-------------------------------------------";
                            cout << "\n\n\t\t YOU REACHED....";
                            getch();
                            system("cls");
                            cout << "\n\n\n\t\t\tPress any key";
                            getch();
                            system("cls");
                            int n;
                            cout << "\n\n\n\t\t\tPAYMENTS OPTIONS:\n\t\t1.Cash\n\t\t2.Online Modes" << endl;
                            cout << "\n\t\tEnter your choice: ";
                            cin >> n;
                            Sleep(3000);
                            cout << "\n\n\n";
                            payment();
                            cout << endl;
                            two.get_reviews();
                            cout << "\n\n\n\t\t\t THANKS...........\n\n\n";
                            exit();
                        }
                        break;

                    case 3:
                        system("cls");
                        cout << "\n\n\t\t YOUR CAB DETAILS:";
                        three.display_cab_info();
                        pr = three.calculate_price();
                        cout << "\n\tTotal price: " << pr << " Rs";
                        int p3;
                        cout << "\n\n\tWant to book cab or not:\n\n\t1.Yes\n\t2.No";
                        cout << "\n\n\tEnter your choice:";
                        cin >> p3;
                        if (p3 == 2)
                        {
                            system("cls");
                            cout << "\t\t\n\n\n\t THANKS...........\n\n\n";
                        }
                        else
                        {
                            system("cls");
                            cout << "\n\n\t\t CAB BOOKED....";
                            cout << "PRESS ANY KEY....";
                            getch();
                            system("cls");
                            print_journey();
                            cout << "\t\t-------------------------------------------";
                            cout << "\n\n\t\t YOU REACHED....";
                            getch();
                            system("cls");
                            cout << "\n\n\n\t\t\tPress any key";
                            getch();
                            system("cls");
                            int j;
                            cout << "\n\n\n\t\t\tPAYMENTS OPTIONS:\n\t\t1.Cash\n\t\t2.Online Modes" << endl;
                            cout << "\n\t\tEnter your choice: ";
                            cin >> j;
                            Sleep(3000);
                            cout << "\n\n\n";
                            payment();
                            cout << endl;
                            three.get_reviews();
                            cout << "\n\n\n\t\t\t THANKS...........\n\n\n";
                            exit();
                        }
                        break;
                    default:
                        cout << "\n\t\t INVALID CHOICE..." << endl;
                        getch();
                    }

                    break;
                }

                getch();
            }
            break;

        case 2:
            registerme();
            break;

        case 3:
            system("cls");
            cout << "\n\n\n\n\t\t\t\tLOADING.........";
            Sleep(2000);
            system("cls");
            cout << "\n\n\n\n\t\t\tTHANKS............\n\n\n\n";
            exit(0);

        default:
            cout << "\n\t\t INVALID CHOICE..." << endl;
            getch();
        }
    }
    return 0;
}
