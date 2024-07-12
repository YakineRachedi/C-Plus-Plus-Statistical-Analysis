#include <iostream> // for std::cout, std::cin
#include <fstream> // for std::ofstream, std::ifstream
#include <vector> // for std::vector<T>
#include <algorithm> // for many function (count, count_if, sort ...)
#include <limits> // for numeric_limits<double>::infinity() and numeric_limits<T>::max()
#include <cmath> // Library for maths (std::sqrt,...)
#include <numeric> // for std::accumulate
#include <set> // for std::set
#include <iterator> // for std::iterator, ...
#include <map> // for std::map<E,F>

using namespace std;

struct Fiche {
    string first_name;
    string city;
    int age;
    double time;
};

int main(){
    /*------------ Filling an array of any size from a .txt data file ----------------*/
    vector<Fiche> vdata;
    ifstream F_source_1("./smalldata.txt");
    Fiche f;
    while(F_source_1 >> f.first_name >> f.city >> f.age >> f.time){
        vdata.push_back(f);
    }
    F_source_1.close();

    ofstream output_1("./vdata_while.txt");
    output_1 << "Name City Age Time \n"; 
    for(int i = 0; i < vdata.size(); i++){
        output_1 << vdata[i].first_name << " "
                << vdata[i].city << " "
                << vdata[i].age << " "
                << vdata[i].time << endl; 
    }
    output_1.close();

    cout << "Freeing memory space \n";
    vdata.clear();
    cout << "The size of the array : " << vdata.size() << "\n";
    cout << "Array is clear ! \n";


    /*--------------------------------------------------------------------------------*/ 


    /*------------- Filling a fixed-size array from a .txt data file -----------------*/

    const int N = 2500;
    vdata.resize(N);

    // Traditional for loop
    ifstream F_source_2("./smalldata.txt");
    for(int i = 0; i < N; i++){
        F_source_2
        >> vdata[i].first_name
        >> vdata[i].city
        >> vdata[i].age
        >> vdata[i].time;
    }
    F_source_2.close();

    ofstream output_2("./vdata_traditional_for.txt");
    output_2 << "Name City Age Time \n";
    for(int i = 0; i < vdata.size(); i++){
        output_2 << vdata[i].first_name << " " << vdata[i].city << " " << vdata[i].age << " " << vdata[i].time << "\n";
    }
    output_2.close();


    cout << "Freeing memory space \n";
    vdata.clear();
    cout << "The size of the array : " << vdata.size() << "\n";
    cout << "Array is clear ! \n";

    // Range-based For Loop
    vdata.resize(N);
    ifstream F_source_3("./smalldata.txt");
    for(Fiche & f : vdata){
        F_source_3 
        >> f.first_name 
        >> f.city 
        >> f.age 
        >> f.time;
    }
    F_source_3.close();

    ofstream output_3("./vdata_range_based.txt");
    for(const Fiche & f : vdata){
        output_3 << f.first_name << " " << f.city << " " << f.age << " " << f.time << "\n";
    }
    output_3.close();


    /*-------------- Play with loops, test the algorithm library... ----------------*/
    
    cout << "\n --------------------\n";

    /*
    *
    * * * How many people live in Lyon ? What is the percentage of Lyon residents ?
    *
    */ 

    int Lyon_ResidentsCount_loop = 0;
    for(int i = 0; i < N; i++){
        if(vdata[i].city == "Lyon"){
            Lyon_ResidentsCount_loop++;
        }
    }

    int Lyon_ResidentsCount_algorithm = count_if(vdata.begin(),vdata.end(),[](const Fiche & f) {return f.city == "Lyon";});

    cout << "Number of people who live in Lyon : \n";
    cout << "(loop + test) : " << Lyon_ResidentsCount_loop << "\n";
    cout << "(algorithm library) : " << Lyon_ResidentsCount_algorithm << "\n";

    cout << "percentage of the population from Lyon : " << Lyon_ResidentsCount_loop * 100 / double(N) << " %"<< "\n";

/**************************************************************************************************************************************/

    /*
    *
    * * * How many people live in Lyon and are strictly under 30 years old ?
    *
    */ 

    int Lyon_ResidentsUnder30Count_loop = 0;
    for(const Fiche & cursor : vdata){
        if(cursor.city == "Lyon" && cursor.age < 30){
            Lyon_ResidentsUnder30Count_loop++;
        }
    }

    int Lyon_ResidentsUnder30count_algorithm = count_if(vdata.begin(),vdata.end(),
                            [](const Fiche & f) {return f.city == "Lyon" && f.age < 30;});
    cout << "\n --------------------\n";
    cout << "Number of people who live in Lyon and are strictly under 30 years old \n"; 
    cout << "(loop + test) : " << Lyon_ResidentsUnder30Count_loop << "\n";
    cout << "(algorithm library) : "<< Lyon_ResidentsUnder30count_algorithm << "\n";


    cout << "\n --------------------\n";
 /**************************************************************************************************************************************/
   
    /*
    * 
    * * * Is there a person from Toulouse whose first name starts with the letter A ?
    *
    */
    bool IsToulousianWith_A_FirstName_loop = false;
    for(const Fiche & Searching : vdata){
        if(Searching.city == "Toulouse" && Searching.first_name.front() == 'A'){  // Or Searching.first_name[0] == 'A' (a string is an array too)
           IsToulousianWith_A_FirstName_loop = true; 
        }
    }

    bool IsToulousianWith_A_FirstName_algorithm = any_of(vdata.begin(),vdata.end(),
                [](const Fiche & Search_for) {return Search_for.city == "Toulouse" && Search_for.first_name[0] == 'A';});


    cout << "Is there a Toulousian whose first name starts with A ? \n";
    if(IsToulousianWith_A_FirstName_algorithm && IsToulousianWith_A_FirstName_loop) {
        cout << "Yes, there is a Toulousian whose first name starts with A. \n";
    }
    else{
        cout << "Nope, there is not :( \n";
    }

    /*
    *
    * * *What is his name if he does exist ? His age, time ?
    *
    */ 
    {    
        struct Toulousian_withA {
            string His_First_name;
            int His_age;
            double His_time;
        };

        Toulousian_withA Person;
        for(int i = 0; i < N; i++){
            if(vdata[i].city == "Toulouse" && vdata[i].first_name[0] == 'A'){
                Person.His_First_name = vdata[i].first_name;
                Person.His_age = vdata[i].age;
                Person.His_time = vdata[i].time;
                break;
            }
        }

        cout << "His name : " << Person.His_First_name << "\n";
        cout << "His age : " << Person.His_age << "\n";
        cout << "His time : " << Person.His_time << "\n";
    }

    cout << "\n --------------------\n";
/**************************************************************************************************************************************/


    /*
    *
    * * * What is the minimum age ? The maximum age ? What is the name of the youngest ? The oldest ?
    *
    */ 
    
    int minAge = numeric_limits<int>::max();
    int maxAge = numeric_limits<int>::min();
    
    string youngestName;
    string oldestName;

    for(const Fiche & f : vdata){
        if(f.age < minAge){
            minAge = f.age;
            youngestName = f.first_name;
        }
    }

    for(int i = 0; i < N; i++){
        if(vdata[i].age > maxAge){
            maxAge = vdata[i].age;
            oldestName = vdata[i].first_name;
        }
    }
    
    cout << "\n loop + test \n";
    cout << "The minimum age is : " << minAge << "\n"
        << "The name of the youngest : " << youngestName << "\n"
        << "The maximum age is : " << maxAge << "`\n"
        << "The name of the oldest : " << oldestName << "\n"; 
    
    auto Extremes = minmax_element(vdata.begin(),vdata.end(),[](const Fiche & p1, const Fiche & p2) {return p1.age < p2.age;});
    
    cout << "\n Algorithm library \n";
    cout << "The minimum age is : " << Extremes.first->age << "\n"
        << "The name of the youngest : " << Extremes.first->first_name << "\n"
        << "The maximum age is : " << Extremes.second->age << "`\n"
        << "The name of the oldest : " << Extremes.second->first_name << "\n"; 

    cout << "\n --------------------\n";

/**************************************************************************************************************************************/
    

    /*
    *
    * * * What is the average age of the people in the file ? What is the standard deviation of their age ? 
    * 
    */
    
    cout << "\n loop + test \n";
    {
        double Average_Age = 0.;
        for(const Fiche & counting : vdata){
            Average_Age += counting.age;
        }
        Average_Age /= double(N);
        cout << "The average age is : " <<  Average_Age << " years old\n";

        double stdDevAge = 0.;
        for(int i = 0; i < N; i++){
            stdDevAge += vdata[i].age * vdata[i].age;
        }

        stdDevAge /= double(N);
        stdDevAge -= Average_Age * Average_Age;
        cout << "The standard deviation of their age is : " << std::sqrt(stdDevAge) << " years old \n";
    }
    cout << "\n Numeric library \n";
    {
        auto Average_Age = accumulate(vdata.begin(),vdata.end(),0.,
                                    [](double partial_sum, const Fiche & f)
                                            {return partial_sum + f.age ;});
        Average_Age /= double(N);
        cout << "The average age is : " <<  Average_Age << " years old\n";

        auto stdDevAge = accumulate(vdata.begin(),vdata.end(),0.,
                            [](double partial_sum, const Fiche & f) 
                                    {return partial_sum + f.age * f.age;});
        
        stdDevAge /= double(N);
        stdDevAge -= Average_Age * Average_Age;
        cout << "The standard deviation of their age is : " << std::sqrt(stdDevAge) << " years old \n";
    }

/**************************************************************************************************************************************/

    /*
    *
    * * * Are Parisians on average faster in the 100 meters than Marseillais ?
    *
    */ 
    cout << "\n loop + test \n";
    {
        double AverageTimeParis = 0.0;
        double AverageTimeMarseille = 0.0;
        int Count_Parisians = 0;
        int Count_Marseillais = 0;

        for(const Fiche & f : vdata){
            if(f.city == "Paris"){
                AverageTimeParis += f.time;
                Count_Parisians++;
            }
            if(f.city == "Marseille"){
                AverageTimeMarseille += f.time;
                Count_Marseillais++;
            }
        }
        AverageTimeParis /= double(Count_Parisians);
        AverageTimeMarseille /= double(Count_Marseillais);

        if(AverageTimeParis > AverageTimeMarseille){
            cout << "Parisians are on average faster than Marseillais in the 100-meter race. \n";
        }
        else{
            cout << "Marseillais are on average faster than Parisians in the 100-meter race. \n";
        }
        cout << "Parisians average time : " << AverageTimeParis << "\n";
        cout << "Marseillais average time : " << AverageTimeMarseille << "\n";
    }
    cout << "\n Algorithm library \n";
    {
        int Count_Parisians = count_if(vdata.begin(),vdata.end(),[](const Fiche & f){return f.city == "Paris";});
        int Count_Marseillais = count_if(vdata.begin(),vdata.end(),[](const Fiche & f){return f.city == "Marseille";});

        auto AverageTimeParis = accumulate(vdata.begin(),vdata.end(),0.,
                    [](double partial_sum,const Fiche & f) {return partial_sum + ((f.city == "Paris")?f.time : 0);});

        auto AverageTimeMarseille = accumulate(vdata.begin(),vdata.end(),0.,
                    [](double partial_sum,const Fiche & f) {return partial_sum + ((f.city == "Marseille") ? f.time : 0 );});
        
        
        AverageTimeParis /= double(Count_Parisians);
        AverageTimeMarseille /= double(Count_Marseillais);

        if(AverageTimeParis > AverageTimeMarseille){
            cout << "Parisians are on average faster than Marseillais in the 100-meter race. \n";
        }
        else{
            cout << "Marseillais are on average faster than Parisians in the 100-meter race. \n";
        }
        cout << "Parisians average time : " << AverageTimeParis << "\n";
        cout << "Marseillais average time : " << AverageTimeMarseille << "\n";
    }


    cout << "\n --------------------\n";
/**************************************************************************************************************************************/

    /*
    *
    * * * Producing a file toulousians.txt that contains all the information about people who live in Toulouse, 
    * * *          replacing their age with their date of birth.
    * 
    */ 
    {
        ofstream output_toulousians("./toulousians1.txt");
        output_toulousians << "Name \t" << " Year of birth \t" << " Time \n"; 
        for(int i = 0; i < N; i++){
            if(vdata[i].city == "Toulouse"){
                output_toulousians << vdata[i].first_name << "\t" << 2024 - vdata[i].age << "\t" << vdata[i].time << "\n";
            }
        }
        output_toulousians.close();
    }
    
    {
        ofstream output_toulousians("./toulousians2.txt");
        output_toulousians << "Name \t" << " Year of birth \t" << " Time \n";
        auto Select_Toulouse = [&output_toulousians](const Fiche & f){
            if(f.city == "Toulouse"){
                const int current_year = 2024;
                output_toulousians << f.first_name << "\t" << current_year - f.age << "\t" << f.time << "\n";
            }
            return;
        };    
        for_each(vdata.begin(),vdata.end(),Select_Toulouse);
        output_toulousians.close();
    }
    cout << "The file toulousians.txt with for_each or loop + test has been produced. \n";
    cout << "\n --------------------\n";

/**************************************************************************************************************************************/

    /*
    *
    * * * The empirical covariance between age and time in the 100-meter event for this sample of Toulouse residents.
    * 
    */ 
    cout << "\n loop + test \n";
    
    /* Note: 
        * Well, here we could use the initial array vdata, 
        * but I chose a more laborious approach with the <fstream> library just for fun. 
    */

    ifstream my_file("./toulousians1.txt");
    string line;
    getline(my_file,line);  // Remove Head
    ofstream output_file("./toulousians_withoutFirstLine.txt");
    while(getline(my_file,line)){
        output_file << line << "\t\n";
    }
    output_file.close();
    struct Toulousain{
        string first_name;
        int year_of_birth;
        double time;
    };

    ifstream input_file("./toulousians_withoutFirstLine.txt");
    vector<Toulousain> Data_Toulouse;
    Toulousain Toulouse_citizen;
    while(input_file >> Toulouse_citizen.first_name >> Toulouse_citizen.year_of_birth >> Toulouse_citizen.time){
        Data_Toulouse.push_back(Toulouse_citizen);
    }
    my_file.close();
    output_file.close();
    input_file.close();

    double Age_Toulouse = 0.;
    const int current_y = 2024;
    double Time_Toulouse = 0.;
    double AgeTime_Toulouse = 0.;
    for(int i = 0; i < Data_Toulouse.size(); i++){
        int age = current_y - Data_Toulouse[i].year_of_birth;
        Age_Toulouse += age;
        Time_Toulouse += Data_Toulouse[i].time;
        AgeTime_Toulouse += Data_Toulouse[i].time * age;
    }

    Age_Toulouse /= Data_Toulouse.size();
    Time_Toulouse /= Data_Toulouse.size();

    AgeTime_Toulouse = AgeTime_Toulouse / Data_Toulouse.size() - Age_Toulouse * Time_Toulouse;

    cout << "Number of citizens in Toulouse : " << Data_Toulouse.size() << endl;
    cout << "Average age of Toulouse residents : " << Age_Toulouse << endl;
    cout << "Average time of Toulouse residents : " << Time_Toulouse << endl;
    cout << "Empirical covariance between age and time : " << AgeTime_Toulouse << " year seconds per individual \n"<< endl;

    /*
    
    ************** Alternative solutions for both previous questions **************
        double age_toulouse = 0;
        double time_toulouse = 0;
        double age_time_toulouse = 0;
        const int current_year = 2024;
        int nb_toulouse = 0;
        std::ofstream toulousains("toulousains.txt");
        for(int i = 0 ; i < N ; ++i) {
            if(vdata[i].city == "Toulouse") {
                ++nb_toulouse;
                time_toulouse += vdata[i].time;
                age_toulouse += vdata[i].age;
                age_time_toulouse += vdata[i].age * vdata[i].time;

                toulousains
                    << vdata[i].first_name << "\t"
                    << vdata[i].city << "\t"
                    << current_year - vdata[i].age << "\t"
                    << vdata[i].time
                    << std::endl;
            }
        }
        toulousains.close();
        std::cout << "Le fichier toulousains.txt a été produit.\n\n";

        age_toulouse = age_toulouse / nb_toulouse;
        time_toulouse = time_toulouse / nb_toulouse;
        age_time_toulouse = age_time_toulouse / nb_toulouse
            - age_toulouse * time_toulouse;
            
            std::cout << "Empirical covariance between age and time : " << age_time_toulouse << "year seconds per individual.\n\n";
        
        ********************************************************************************************************************************************
    */
    cout << "\n Algorithm and Numeric libraries \n";
   {
    double Age_Toulouse = std::accumulate(vdata.begin(), vdata.end(), 0.,
                [](double s, const Fiche & x)->double { return s+ ((x.city == "Toulouse")?x.age:0.) ;} );

    double Time_Toulouse = std::accumulate(vdata.begin(), vdata.end(), 0.,
                [](double s, const Fiche & x)->double { return s + ((x.city == "Toulouse")?x.time:0.) ;} );

    double AgeTime_Toulouse = std::accumulate(vdata.begin(), vdata.end(), 0.,
                [](double s, const Fiche & x)->double { return s+ ((x.city == "Toulouse")?(x.time*x.age):0.) ;} );

    int nb_toulouse = std::count_if(vdata.begin(), vdata.end(),
                [](const Fiche & x) { return (x.city == "Toulouse")?true:false;} );

    Age_Toulouse /= double(nb_toulouse);
    Time_Toulouse /= double(nb_toulouse);
    AgeTime_Toulouse /= double(nb_toulouse);
    AgeTime_Toulouse -= Age_Toulouse * Time_Toulouse;

        std::cout << "Empirical covariance between age and time : " << AgeTime_Toulouse << " year seconds per individual.\n\n";
   }
    cout << "\n --------------------\n";

/**************************************************************************************************************************************/


    /*
    *
    * * * Displaying the list of represented cities in the terminal * * *
    * 
    */
    cout << "\n loop + test \n";
    {
        auto contains = [](const vector<string> & my_list, const string & city){
            bool is_there = false;
            for(int i = 0;i < my_list.size();i++){
                if(my_list[i] == city){
                    is_there = true;
                    break;
                }
            }
            return is_there;
        };
        vector<string> cityList;
        for(const Fiche & f : vdata){
            if(contains(cityList,f.city) == false){
                cityList.push_back(f.city);
            }
        }

        cout << "The cities present in the file are : \n";
        for(const string & city : cityList){
            cout << "* " << city << "\n";
        }
    }
    /* Note :
        * The quick solution would be to use the unordered container std::set.
    */
    cout << "\n---------\n";
    cout << "Using the unordered container std::set \n";
    set<string> cityList;
    for(const Fiche & f : vdata){
        cityList.insert(f.city);
    }
    cout << "The cities present in the file are : \n";
    for(set<string>::iterator It = cityList.begin(); It != cityList.end(); It++){
        cout << "* " << *It << "\n";
    }

/**************************************************************************************************************************************/

    /*
    *
    * * * Sorting the array in ascending order. 
    * * * Producing a file data_tri.txt that contains the 100 fastest individuals in the 100 meters sorted by descending speed.
    * 
    */
    cout << "\n --------------------\n";
    vector<Fiche> vdata_copy(vdata.begin(),vdata.end());
    sort(vdata.begin(),vdata.end(),[](const Fiche & p1,const Fiche & p2){return p1.time < p2.time;});
    ofstream output_triData("./tri_data.txt");
    for(const Fiche & f : vdata){
        output_triData << f.first_name << "\t" << f.time << "\t" << f.city << "\t" << f.age << "\n";
    }
    output_triData.close();
    cout << "\n File produced by Algorithm library \n";

    for(int i = 0; i < N; i++){
        int min_index = i;
        for(int j = i + 1; j < N; j++){
            if(vdata_copy[j].time < vdata_copy[min_index].time){
                min_index = j;
            }
        }
        if(i != min_index){
            swap(vdata_copy[i],vdata_copy[min_index]);
        }
        else{
            continue;
        }
    }
    
    ofstream output_ODT("./Ordred_data_by_time.txt");
    for(const Fiche & f : vdata_copy){
        output_ODT << f.first_name << "\t" << f.time << "\t" << f.age << "\t" << f.city << "\n";
    }
    output_ODT.close();
    cout << "\n File produced by classic sorting algorithm \n";
    cout << "\n --------------------\n";

/**************************************************************************************************************************************/
    /*
    *
    * * *  What is the smallest difference between the 100-meter race times of two people ?
    * 
    */
    /* Note :
        * We can use vdata here (already sorted). There is no need to use another vector; I did this in case we hadn't sorted vdata.
    */
    cout << "Using loops + tests + vectors \n------\n\n";
    vector<double> TimesDescending(N);
    vector<long double> gapDifferences(N-1);
    for(int i = 0; i < N; i++){
        TimesDescending[i] = vdata[i].time;
    }

    // sorting TimesDescending vector :
    for(int i = 0; i < N; i++){
        int min_index = i;
        for(int j = i + 1; j < N; j++){
            if(TimesDescending[j] < TimesDescending[min_index]){
                min_index = j;
            }
        }
        if(min_index != i){
            swap(TimesDescending[i],TimesDescending[min_index]);
        }
        else{
            continue;
        }
    }

    double smallestDifference = numeric_limits<double>::infinity();
    for(int i = 0; i < N - 1; i++){
        if(TimesDescending[i] = TimesDescending[i+1]){
            smallestDifference = 0;
            cout << "The two runners have the same time, so the difference = 0. \n";
            break;
        }
        gapDifferences[i] = TimesDescending[i + 1] - TimesDescending[i];
    }
    
    if(smallestDifference != 0){
        for(int i = 0; i < N - 1; i++){
            if(gapDifferences[i] < smallestDifference){
                smallestDifference = gapDifferences[i];
            }
        } 
        cout << "the smallest difference between the 100-meter race times of two people : " << smallestDifference << "\n";
    }
    cout << "\n --------------------\n";
    cout << "We can also use the algorithm library to write clean and readable code:\n";

    vector<double> StoringTimes(N);
    for (int i = 0; i < N; i++) {
        StoringTimes[i] = vdata[i].time;
    }

    sort(StoringTimes.begin(), StoringTimes.end());

    vector<double> Differences(N);
    adjacent_difference(StoringTimes.begin(), StoringTimes.end(), Differences.begin());

    /* Note : 
        We start from differences.begin() + 1 because there is no previous element to subtract from the first element of StoringTimes. 
        For more information, refer to the documentation of the adjacency_differences function.
    */
    auto SmallestDiff = min_element(Differences.begin() + 1, Differences.end());

    cout << "The smallest difference between the 100-meter race times of two people: " << *SmallestDiff << "\n";
    
    cout << "\n --------------------\n";

/**************************************************************************************************************************************/

    /*
    *
    * * * Creation of two vectors, 'young' and 'older', 
        * * * containing respectively the records of individuals under 40 years old and strictly over 40 years old.
    * 
    */
    cout << "\n loop + test \n";
    {
        vector<Fiche> Youngs;
        vector<Fiche> Olders;
        for(const Fiche & f : vdata){
            if(f.age <= 40){
                Youngs.push_back(f);
            }
            else{
                Olders.push_back(f);
            }
        }
        ofstream y("./youngs1.txt");
        ofstream o("./olders1.txt");
        for(const Fiche & f : Youngs){
            y << f.first_name << "\t" << f.city << "\t" << f.age << "\t" << f.time << "\n";
        }
        for(const Fiche & f : Olders){
            o << f.first_name << "\t" << f.city << "\t" << f.age << "\t" << f.time << "\n";
        }
        o.close();
        y.close();
    }
    {
        vector<Fiche> Youngs;
        vector<Fiche> Olders;
        cout << "Using Algorithm library \n";
        partition_copy(vdata.begin(),vdata.end(),back_inserter(Youngs),back_inserter(Olders),[](const Fiche & f){return f.age < 40;});
        ofstream y("./youngs.txt");
        ofstream o("./olders.txt");
        for(const Fiche & f : Youngs){
            y << f.first_name << "\t" << f.city << "\t" << f.age << "\t" << f.time << "\n";
        }
        for(const Fiche & f : Olders){
            o << f.first_name << "\t" << f.city << "\t" << f.age << "\t" << f.time << "\n";
        }
        o.close();
        y.close();
    }
    cout << "\n --------------------\n";

/**************************************************************************************************************************************/
    /*

    * * * Writing a file named ordre.dat the list of 2500 individuals sorted according some constraintes :
            * Alphabetically by first name
            * In case of ties, alphabetically by city
            * If there are still ties, from oldest to youngest
            * If there are still ties, from slowest to fastest
    */
    auto comparison = [](const Fiche & indiv1, const Fiche & indiv2) {
        if (indiv1.first_name.front() != indiv2.first_name.front()) {
            return indiv1.first_name.front() < indiv2.first_name.front();
        } 
        else if (indiv1.city.front() != indiv2.city.front()) {
            return indiv1.city.front() < indiv2.city.front();
        } 
        else if (indiv1.age != indiv2.age) {
            return indiv1.age < indiv2.age;
        } 
        else {
            return indiv1.time < indiv2.time;
        }
    };

    sort(vdata.begin(),vdata.end(),comparison);
    ofstream output_4("./ordre.dat");
    for(const Fiche & f : vdata){
        output_4 << f.first_name << "\t" << f.city << "\t" << f.age << "\t" << f.time << "\n";
    }
    output_4.close();
    cout << "\n File produced \n";

/*****************************************************************************************************************************************/
    cout << "\n --------------------\n";

    /*
        * We want to establish the histogram of ages to understand the distribution of ages. Using the std::map<int, int> container, 
        * calculate the histogram and display it line by line in the terminal.
    */
    map<int,int> histogram;
    for(Fiche & f : vdata) {
        histogram[f.age]++;
    }

    cout << "Displaying age classes 2 by 2 : \n \n";
    for(map<int,int>::iterator It = histogram.begin(); It != histogram.end(); It++) {
        cout << It->first << " " << It->second << "\n";
    }
    cout << "\n";

    auto most_frequent_class = max_element(histogram.begin(),histogram.end(),
                    [](pair<int,int> class1,pair<int,int> class2) {return class1.second < class2.second;});

    cout << "The most frequent age class is: " << most_frequent_class->first << "\n";
    /*-------------------------------------------------------------------- END -----------------------------------------------------------*/
    return 0;
}