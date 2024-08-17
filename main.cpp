#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
using namespace std;

class OrderDetails{
    private:
        int orderNumber;
        vector<string> VIPList = {"ADM123", "NAJ123"};
        string buyerName;
        string buyerId;
        string carId;
        string carBrand;
        string modelName;
        string carColor;
        int productionYear;
        double carPrice;
        double totalPrice;
        double discount;
        time_t timeValue;
        static vector<int> numbers;
        // time https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
        struct tm ltm = {0};
        struct tm currentDate = {0};


        void generateOrderNumber(){
            orderNumber = rand()%(1001);
            for(auto& n : numbers){
                if(n == orderNumber){
                    generateOrderNumber();
                    return;
                }
            }
            numbers.push_back(orderNumber);
        }

        void isDiscount(){
            for(auto& vip : VIPList){
                if(vip == buyerId){
                    discount = 0.1;
                    totalPrice = carPrice - (carPrice * discount);
                }
                else{
                    totalPrice = carPrice;
                }
            }
        }

    public:
        OrderDetails(string name, string id, string cid, string brand,
                     string model, string color, int py, double price){
            time_t now = time(0);
            buyerName = name;
            buyerId = id;
            carId = cid;
            carBrand = brand;
            modelName = model;
            carColor = color;
            productionYear = py;
            carPrice = price;
            generateOrderNumber();
            isDiscount();
            ltm = *localtime(&now);
            currentDate.tm_year = ltm.tm_year;  // Year since 1900
            currentDate.tm_mon = ltm.tm_mon;    // Month (0-11)
            currentDate.tm_mday = ltm.tm_mday;
            timeValue = mktime(&currentDate);
        }
        string getCustomerId(){
            return buyerId;
        }
        string getCarId(){
            return carId;
        }

        double getFinalPrice(){
            return totalPrice;
        }

        struct tm getTime(){
            return ltm;
        }
        time_t getCurrentDate(){
            return timeValue;
        }
        void displayDetails(){
            cout << endl;
            cout << "Bill ID: " << orderNumber << endl;
            cout << "Customer ID: " << buyerId << endl;
            cout << "Customer Name: " << buyerName << endl;
            cout << "Car ID: " << carId << endl;
            cout << "Car Brand: " << carBrand << endl;
            cout << "Car Model: " << modelName << endl;
            cout << "Car Color: " << carColor << endl;
            cout << "Production Year: " << productionYear << endl;
            cout << "Price: RM" << fixed << setprecision(2) << carPrice << endl;
            cout << "Discount : " << discount * 100 << "%" << endl;
            cout << "Total Price: RM" << fixed << setprecision(2) << totalPrice << endl;
            cout << "Date:" << ltm.tm_mday << "/" <<
            1 + ltm.tm_mon << "/" <<
            1900 + ltm.tm_year << endl;
            cout << "Time (00:00, 24-hour time): "<< ltm.tm_hour << ":";
            cout << ltm.tm_min;
            cout << endl << endl;
        }
        void displayReport(){
            cout << endl;
            cout << "Car ID: " << carId << endl;
            cout << "Car Brand: " << carBrand << endl;
            cout << "Car Color: " << carColor << endl;
            cout << "Customer Name: " << buyerName << endl;
            cout << "Date:" << ltm.tm_mday << "/" <<
            1 + ltm.tm_mon << "/" <<
            1900 + ltm.tm_year << endl;
            cout << "Price: RM" << fixed << setprecision(2) << totalPrice << endl;
            cout << endl << endl;
        }
};

class Car{
    private:
        string carID;
        string brand;
        string model;
        string color;
        string manufactureCountry;
        int manufactureYear;
        double price;
        int Sales;
        bool bestSeller;

        string generateNumber(){
            int num;
            num = rand()%10;
            return to_string(num);
        }

        void randomID(){
            carID = brand.substr(0,3);
            for(int i = 0; i<9; i++){
                carID += generateNumber();
            }
        }

    public:
        Car() = default;
        Car(string b, string m, string c, string country, int year, double p, int s = 0){
            brand = b;
            model = m;
            color = c;
            manufactureCountry = country;
            manufactureYear = year;
            price = p;
            Sales = s;
            randomID();
        }
        // Get methods
        string getCarId(){
            return carID;
        }
        string getBrand(){
            return brand;
        }
        string getModel(){
            return model;
        }
        string getColor(){
            return color;
        }
        string getManufactureCountry(){
            return manufactureCountry;
        }
        int getManufactureYear(){
            return manufactureYear;
        }
        double getPrice(){
            return price;
        }
        int getSales(){
            return Sales;
        }
        bool isBestSelling(){
            if (Sales > 8){
                bestSeller = 1;
            }
            else{
                bestSeller = 0;
            }
            return bestSeller;
        }
        // Set methods
        string setBrand(string b){
            if(b!="-1")
                brand = b;
        }
        string setModel(string m){
            if(m!="-1")
                model = m;
        }
        string setColor(string c){
            if(c!="-1")
                color = c;
        }
        string setManufactureCountry(string country){
            if(country!="-1")
                manufactureCountry = country;
        }
        int setManufactureYear(int year){
            if(year!=-1)
                manufactureYear = year;
        }
        double setPrice(double p){
            if(p!=-1)
                price = p;
        }
        void increaseSales(){
            Sales += 1;
        }
};

class User{
    private:
        string userID;
        string userName;
        string userPassword;
        string status;
    public:
        User() = default;
        User(string id, string name, string password){
            userID = id;
            userName = name;
            userPassword = password;
        }

        // Get methods
        string getUserId(){
            return userID;
        }
        string getUserName(){
            return userName;
        }
        string getUserPassword(){
            return userPassword;
        }
        string getUserStatus(){
            return status;
        }

        // Set methods
        void setUserStatus(string s){
            status = s;
        }
};

class System{
    private:
        vector<User> userList;
        vector<User> adminList;
        vector<Car> carList;
        vector<Car> temp; // temp vector to stored sorted cars
        vector<OrderDetails> orderList;
        vector<OrderDetails> reportList;
        User currentUser;
        int taskOption;
        double totalPrice;

        void registerFunc(){
            string userId;
            string name;
            bool valid;
            string password;
            cin.ignore();
            cout << endl;
            cout << "Registration" << endl;

            do{
                valid = 1;
                cout << "Enter unique Id >";
                getline(cin, userId);
                for(auto& user : userList){
                    if (userId == user.getUserId()){
                        cout << "ID existed, please try another id" << endl;
                        valid = 0;
                    }
                }
                if(userId == "-1"){
                    cout << "Invalid ID" << endl;
                    valid = 0;
                }
            }while(!valid);
            cout << "Enter your name >";
            getline(cin, name);
            cout << "Enter your password >" ;
            getline(cin, password);
            cout << "Register successfully!" << endl << endl;
            registeredUser(User(userId, name, password));
        }

        void addOrder (OrderDetails order){
            for(auto& car : carList){
                if (car.getCarId() == order.getCarId()){
                    car.increaseSales();
                }
            }
            orderList.push_back(order);
        }

        void purchase(int x){
            int choice;
            cout << "(type in '-1' to exit selection)> ";
            cin >> choice;
            bool status = true;
            while(status){
                try{
                    digitInputValidation();
                    status = false;
                }
                catch(string errorMsg){
                    cout << endl;
                    cout << "Error: " << errorMsg << endl;
                    cout << endl;
                    cout << endl;
                    cout << "(type in '-1' to exit selection)> ";
                    cin >> choice;
                }
            }
            if (x == 1){
                if(choice == -1){
                    cout << endl;
                    cout << "Return to Main Page" << endl;
                }
                else if(choice < 1 || choice > carList.size()){
                    cout << endl;
                    cout << "Option out of range" << endl;
                    purchase(x);
                }
                else{
                    OrderDetails order(currentUser.getUserName(), currentUser.getUserId(), carList[choice-1].getCarId(),
                                          carList[choice-1].getBrand(),carList[choice-1].getModel(), carList[choice-1].getColor(),
                                          carList[choice-1].getManufactureYear(), carList[choice-1].getPrice());
                    addOrder(order);
                    order.displayDetails();
                }
            }
            else if(x == 2){
                if(choice == -1){
                    cout << endl;
                    cout << "Return to Main Page" << endl;
                }
                else if(choice < 1 || choice > temp.size()){
                    cout << endl;
                    cout << "Option out of range" << endl;
                    purchase(x);
                }
                else{
                    OrderDetails order(currentUser.getUserName(), currentUser.getUserId(), temp[choice-1].getCarId(),
                                          temp[choice-1].getBrand(),temp[choice-1].getModel(), temp[choice-1].getColor(),
                                          temp[choice-1].getManufactureYear(), temp[choice-1].getPrice());
                    addOrder(order);
                    order.displayDetails();
                }
            }

        }

        // Search Car id
        int Binary_Search_ID(vector<Car> carList, int low_arr, int high_arr, string id){
            while(low_arr <= high_arr){
                int middle_arr = ( ( high_arr - low_arr ) / 2 ) + low_arr ;

                if(carList[middle_arr].getCarId() == id)
                    return middle_arr;

                if(carList[middle_arr].getCarId() <= id)
                    low_arr = middle_arr + 1;

                else
                    high_arr = middle_arr - 1;
            }
            return -1;
        }

        // Search best selling cars
        int Binary_Search_bestSelling(vector<Car> carList, int low_arr, int high_arr, bool best){
            while(low_arr <= high_arr){
                int middle_arr = ( ( high_arr - low_arr ) / 2 ) + low_arr ;

                if(carList[middle_arr].isBestSelling() == best)
                    return middle_arr;

                if(carList[middle_arr].isBestSelling() <= best)
                    low_arr = middle_arr + 1;

                else
                    high_arr = middle_arr - 1;
            }
            return -1;
        }

        // Search report within specific period
        int Binary_Search_report(vector<OrderDetails> orderList, int low_arr,
                                 int high_arr, struct tm startTime, struct tm endTime){
            time_t start_time_t = mktime(&startTime);
            time_t end_time_t = mktime(&endTime);
            while(low_arr <= high_arr){
                int middle_arr = ( ( high_arr - low_arr ) / 2 ) + low_arr ;
                if(orderList[middle_arr].getCurrentDate() >= start_time_t && orderList[middle_arr].getCurrentDate() <= end_time_t)
                    return middle_arr;

                if(orderList[middle_arr].getCurrentDate() < start_time_t)
                    low_arr = middle_arr + 1;

                else
                    high_arr = middle_arr - 1;
            }
            return -1;
        }

        // sort best selling car according to brand
        void bubbleSort(vector<Car>& arr){
            for(int i =0; i < arr.size(); i++){
                for(int j =0; j<arr.size()-i-1; j++){
                    if(arr[j].getBrand() > arr[j+1].getBrand()){
                        swap(arr[j], arr[j+1]);
                    }
                }
            }
        }

        void linearSearch_Bills(){
            for (int i = 0; i < orderList.size(); i++){
                if(orderList[i].getCustomerId() == currentUser.getUserId()){
                    orderList[i].displayDetails();
                }
            }
        }

        void linearSearch_Bills_Date(tm date){
            for (int i = 0; i < orderList.size(); i++){
                if (orderList[i].getTime().tm_mday == date.tm_mday &&
                    orderList[i].getTime().tm_mon == date.tm_mon &&
                    orderList[i].getTime().tm_year == date.tm_year){
                    orderList[i].displayDetails();
                }
                else{
                    cout << endl;
                    cout << "No bill issued that day." << endl;
                    cout << endl;
                }
            }
        }

        int partition(vector<OrderDetails> &v, int low, int high){
          double pivot = v[high].getFinalPrice();
          int i = low - 1;
          for(int j = low; j < high; j++){
            if(v[j].getFinalPrice() < pivot){
              i++;
              swap(v[i], v[j]);
            }
          }
          swap(v[i+1], v[high]);
          return (i+1);
        }

        void quickSort(vector<OrderDetails> &v, int low, int high){
          if (low < high){
            int pi = partition(v, low, high);

            quickSort(v, low, pi - 1);
            quickSort(v, pi+1, high);
          }
        }
        // Function to merge two halves
        void mergeBrand(vector<Car>& arr, int left, int mid, int right) {
            int n1 = mid - left + 1;
            int n2 = right - mid;

            // Create temporary arrays
            vector<Car> LeftArray(n1);
            vector<Car> RightArray(n2);

            // Copy data to temporary arrays
            // The Mid element is saved in LeftArray
            for (int i = 0; i < n1; i++)
                LeftArray[i] = arr[left + i];
            for (int i = 0; i < n2; i++)
                RightArray[i] = arr[mid + 1 + i];

            // Merge the temporary arrays back into arr[left..right]
            int i = 0; // Initial index of first subarray
            int j = 0; // Initial index of second subarray
            int k = left; // Initial index of merged subarray

            while (i < n1 && j < n2) {
                if (LeftArray[i].getBrand() <= RightArray[j].getBrand()) {
                    arr[k] = LeftArray[i];
                    i++;
                } else {
                    arr[k] = RightArray[j];
                    j++;
                }
                k++;
            }

            // Copy the remaining elements of L[], if there are any
            while (i < n1) {
                arr[k] = LeftArray[i];
                i++;
                k++;
            }

            // Copy the remaining elements of R[], if there are any
            while (j < n2) {
                arr[k] = RightArray[j];
                j++;
                k++;
            }
        }
        void mergePrice(vector<Car>& arr, int left, int mid, int right) {
            int n1 = mid - left + 1;
            int n2 = right - mid;

            // Create temporary arrays
            vector<Car> LeftArray(n1);
            vector<Car> RightArray(n2);

            // Copy data to temporary arrays
            // The Mid element is saved in LeftArray
            for (int i = 0; i < n1; i++)
                LeftArray[i] = arr[left + i];
            for (int i = 0; i < n2; i++)
                RightArray[i] = arr[mid + 1 + i];

            // Merge the temporary arrays back into arr[left..right]
            int i = 0; // Initial index of first subarray
            int j = 0; // Initial index of second subarray
            int k = left; // Initial index of merged subarray

            while (i < n1 && j < n2) {
                if (LeftArray[i].getPrice() <= RightArray[j].getPrice()) {
                    arr[k] = LeftArray[i];
                    i++;
                } else {
                    arr[k] = RightArray[j];
                    j++;
                }
                k++;
            }

            // Copy the remaining elements of L[], if there are any
            while (i < n1) {
                arr[k] = LeftArray[i];
                i++;
                k++;
            }

            // Copy the remaining elements of R[], if there are any
            while (j < n2) {
                arr[k] = RightArray[j];
                j++;
                k++;
            }
        }

        void mergeId(vector<Car>& arr, int left, int mid, int right) {
            int n1 = mid - left + 1;
            int n2 = right - mid;

            // Create temporary arrays
            vector<Car> LeftArray(n1);
            vector<Car> RightArray(n2);

            // Copy data to temporary arrays
            // The Mid element is saved in LeftArray
            for (int i = 0; i < n1; i++)
                LeftArray[i] = arr[left + i];
            for (int i = 0; i < n2; i++)
                RightArray[i] = arr[mid + 1 + i];

            // Merge the temporary arrays back into arr[left..right]
            int i = 0; // Initial index of first subarray
            int j = 0; // Initial index of second subarray
            int k = left; // Initial index of merged subarray

            while (i < n1 && j < n2) {
                if (LeftArray[i].getCarId() <= RightArray[j].getCarId()) {
                    arr[k] = LeftArray[i];
                    i++;
                } else {
                    arr[k] = RightArray[j];
                    j++;
                }
                k++;
            }

            // Copy the remaining elements of L[], if there are any
            while (i < n1) {
                arr[k] = LeftArray[i];
                i++;
                k++;
            }

            // Copy the remaining elements of R[], if there are any
            while (j < n2) {
                arr[k] = RightArray[j];
                j++;
                k++;
            }
        }

        // Function to implement merge sort
        void mergeSort(vector<Car>& arr, int left, int right) {
            if (left >= right)
                return;

            int mid = left + (right - left) / 2;


            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            if(taskOption == 2){
                mergePrice(arr, left, mid, right);
            }
            else if(taskOption == 3){
                 mergeBrand(arr, left, mid, right);
            }
            else if(taskOption == 4){
                 mergeId(arr, left, mid, right);
            }
        }

        void digitInputValidation(){
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                string msg = "Please enter digits.";
                throw msg;
            }
        }

        void dateInputValidation(){
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                string msg = "Please enter proper date.";
                throw msg;
            }
        }

    public:
        System(){
            cout << "Welcome to Car Dealership" << endl;
        }



        void registeredUser(User user){
            userList.push_back(user);
        }

        void registeredAdmin(User admin){
            adminList.push_back(admin);
        }

        void registeredCar(Car car){
            carList.push_back(car);
        }

        string getStatus(){
            return currentUser.getUserStatus();
        }

        void addNewCar(){
            string brand;
            string model;
            string color;
            string country;
            int year;
            double price;
            cout << endl;
            cout << "Please enter new car information." << endl;
            cout << "Car Brand: ";
            getline(cin, brand);
            cout << "Car Model Name: ";
            getline(cin, model);
            cout << "Car Color: ";
            getline(cin, color);
            cout << "Manufacture country: ";
            getline(cin, country);
            cout << "Manufacture Year: ";
            cin >> year;
            bool status = true;
            while(status){
                try{
                    digitInputValidation();
                    status = false;
                }
                catch(string errorMsg){
                    cout << endl;
                    cout << "Error: " << errorMsg << endl;
                    cout << endl;
                    cout << endl;
                    cout << "Manufacture Year: ";
                    cin >> year;
                }
            }


            cout << "Price: ";
            cin >> price;
            status = true;
            while(status){
                try{
                    digitInputValidation();
                    status = false;
                }
                catch(string errorMsg){
                    cout << endl;
                    cout << "Error: " << errorMsg << endl;
                    cout << endl;
                    cout << endl;
                    cout << "Price: ";
                    cin >> price;
                }
            }
            registeredCar(Car(brand, model, color, country, year, price));
            cout << "New car added successfully." << endl << endl;
            cin.ignore();
        }
        void removeCar(){
            if (!carList.empty()){
                displayAllCars();
                int option;
                cout << endl;
                cout << "Choose a car to delete: ";
                cin >> option;
                bool status = true;
                while(status){
                    try{
                        digitInputValidation();
                        status = false;
                    }
                    catch(string errorMsg){
                        cout << endl;
                        cout << "Error: " << errorMsg << endl;
                        cout << endl;
                        cout << endl;
                        cout << "Choose a car to delete: ";
                        cin >> option;
                    }
                }
                if (option > 0 && option <= carList.size()){
                    carList.erase(carList.begin()+(option -1));
                    cout << "Car removed successfully." << endl << endl;
                }
                else{
                    cout << endl;
                    cout << "Option out of range" << endl;
                    cout << endl;
                }
            }
        }
        void modifyCar(){
            string id;
            cout << endl;
            cout << "Enter the car id to modify: ";
            cin >> id;
            string brand;
            string model;
            string color;
            string country;
            int year;
            double price;

            for (auto& car : carList){
                if (car.getCarId() == id){
                    cout << "Enter -1 if you do not wish to modify this section." << endl;
                    cout << "Enter new brand: ";
                    cin >> brand;
                    car.setBrand(brand);
                    cout << "Enter new model name: ";
                    cin >> model;
                    car.setModel(model);
                    cout << "Enter new color: ";
                    cin >> color;
                    car.setColor(color);
                    cout << "Enter new Manufacture Country: ";
                    cin >> country;
                    car.setManufactureCountry(country);
                    cout << "Enter new Manufacture Year: ";
                    cin >> year;
                    bool status = true;
                    while(status){
                        try{
                            digitInputValidation();
                            status = false;
                        }
                        catch(string errorMsg){
                            cout << endl;
                            cout << "Error: " << errorMsg << endl;
                            cout << endl;
                            cout << endl;
                            cout << "Enter new Manufacture Year: ";
                            cin >> year;
                        }
                    }

                    car.setManufactureYear(year);
                    cout << "Enter new price: ";
                    cin >> price;
                    status = true;
                    while(status){
                        try{
                            digitInputValidation();
                            status = false;
                        }
                        catch(string errorMsg){
                            cout << endl;
                            cout << "Error: " << errorMsg << endl;
                            cout << endl;
                            cout << endl;
                            cout << "Enter new price: ";
                            cin >> price;
                        }
                    }


                    car.setPrice(price);

                    cout << "Changes made." << endl << endl;
                    return;
                    }
                }
            cout << "No such car exist." << endl << endl;
        }


        bool loginFunc(){
            string userId;
            string password;
            char x;

            while(true){
                cout << "Please Login (-1 to quit)" << endl;
                cout << "Enter User Id >" ;
                getline(cin, userId);
                if (userId == "-1"){
                    return 0;
                }
                cout << "Enter Password >" ;
                getline(cin, password);


                for(auto& user : userList){
                    if(userId == user.getUserId() && password == user.getUserPassword()){
                        currentUser = User(user.getUserId(),user.getUserName(), user.getUserPassword());
                        currentUser.setUserStatus("user");
                        cout << endl;
                        cout << "Login Successful" << endl;
                        cout << "Welcome, " << currentUser.getUserName() << endl;
                        cout << endl;
                        return 1;
                    }
                }
                for(auto& admin : adminList){
                    if(userId == admin.getUserId() && password == admin.getUserPassword()){
                        currentUser = User(admin.getUserId(),admin.getUserName(), admin.getUserPassword());
                        currentUser.setUserStatus("admin");
                        cout << endl;
                        cout << "Login Successful" << endl;
                        cout << "Welcome, " << currentUser.getUserName() << "(Admin)" << endl;
                        cout << endl;
                        return 1;
                    }
                }
                cout << endl;
                cout << "Invalid login" << endl;
                cout << "Do you wish to register? (Y/N)" << endl;
                cin >> x;
                if (x == 'Y' || x == 'y'){
                    registerFunc();
                }
                else{
                    cout << endl;
                    cin.ignore();
                }
            }
        }

        int availableTasks(){
            cout << endl;
            cout << "Please choose a task to continue: " << endl;
            cout << "1) Display all cars" << endl;
            cout << "2) Display cars sorted by price" << endl;
            cout << "3) Display cars sorted by brand" << endl;
            cout << "4) Display cars sorted by ID" << endl;
            cout << "5) Display best selling cars" << endl;
            cout << "6) Search car by ID" << endl;
            cout << "7) Search issued bills" << endl;
            if (currentUser.getUserStatus() == "admin"){
                cout << "8) Add new car" << endl;
                cout << "9) Modify car" << endl;
                cout << "10) Remove car" << endl;
                cout << "11) Generate Report" << endl;
                cout << "12) Exit" << endl;
            }
            else{
                cout << "8) Exit" << endl;
            }
            cout << "> ";
            cin;
            cin >> taskOption;

            bool status = true;
            while(status){
                try{
                    digitInputValidation();
                    status = false;
                }
                catch(string errorMsg){
                    cout << endl;
                    cout << "Error: " << errorMsg << endl;
                    cout << endl;
                    cout << endl;
                    cout << "> ";
                    cin >> taskOption;
                }
            }


            if (((taskOption < 1 || taskOption > 8) && currentUser.getUserStatus() != "admin")
                || ((taskOption < 1 || taskOption > 12) && currentUser.getUserStatus() == "admin")){

                availableTasks();

            }
            else{
                cin.ignore();
                return taskOption;
            }
        }

        void displayAllCars(){
            int i = 1;
            cout << endl << "Car options" << endl;
            if (taskOption == 1){
                if (carList.empty()){
                cout << endl;
                cout << "No car available for now." << endl;
                cout << endl;
                }
                else{
                    cout << endl;
                    for(auto& car : carList){
                        cout << i << ")";
                        cout << car.getBrand() << endl;
                        cout << "Car ID: " << car.getCarId() << endl;
                        cout << "Car Model Name: " << car.getModel() << endl;
                        cout << "Color: " << car.getColor() << endl;
                        cout << "Manufacture Country: " << car.getManufactureCountry() << endl;
                        cout << "Manufacture Year: " << car.getManufactureYear() << endl;
                        cout << "Price: RM" << fixed << setprecision(2) << car.getPrice() << endl;
                        cout << "Sales: " << car.getSales() << endl << endl;
                        ++i;
                    }
                purchase(1);
                }
            }
            else if(taskOption == 10){
                cout << endl;
                for(auto& car : carList){
                    cout << i << ")";
                    cout << car.getBrand() << endl;
                    cout << "Car ID: " << car.getCarId() << endl;
                    cout << "Car Model Name: " << car.getModel() << endl;
                    cout << "Color: " << car.getColor() << endl;
                    cout << "Manufacture Country: " << car.getManufactureCountry() << endl;
                    cout << "Manufacture Year: " << car.getManufactureYear() << endl;
                    cout << "Price: RM" << fixed << setprecision(2) <<  car.getPrice() << endl;
                    cout << "Sales: " << car.getSales() << endl << endl;
                    ++i;
                }
            }
            else{
                if (temp.empty()){
                    cout << endl;
                    cout << "No car available for now." << endl;
                    cout << endl;
                }
                else{
                    cout << endl;
                    for(auto& car : temp){
                    cout << i << ")";
                    cout << car.getBrand() << endl;
                    cout << "Car ID: " << car.getCarId() << endl;
                    cout << "Car Model Name: " << car.getModel() << endl;
                    cout << "Color: " << car.getColor() << endl;
                    cout << "Manufacture Country: " << car.getManufactureCountry() << endl;
                    cout << "Manufacture Year: " << car.getManufactureYear() << endl;
                    cout << "Price: RM" << fixed << setprecision(2) <<  car.getPrice() << endl;
                    cout << "Sales: " << car.getSales() << endl << endl;
                    ++i;
                    }
                purchase(2);
                }
            }
        }

        void sortCar_MergeSort(){
            temp = carList;
            mergeSort(temp, 0, temp.size()-1);
            displayAllCars();
        }


        void searchCarByID(){
            int found;
            string id;
            if (!carList.empty()){
                temp = carList;
                cout << endl;
                cout << "Enter Car ID: ";
                cin >> id;
                // sort for binary search algorithm
                sort(temp.begin(), temp.end(), [](Car& a, Car& b) {
                        return a.getCarId() < b.getCarId();
                    });
                found = Binary_Search_ID(temp, 0, temp.size()-1, id);
                if (found != -1){
                    Car elementToKeep = temp[found];
                    temp.clear();
                    temp.push_back(elementToKeep);
                    displayAllCars();
                }
                else{
                    cout << endl;
                    cout << "Car with this ID does not exist." << endl << endl;
                }

            }
            else {
                cout << endl;
                cout << "No car available." << endl << endl;
            }

        }

        void searchBestSelling(){
            int found;
            temp.clear();
            if (!carList.empty()){
                vector<Car> searchList = carList;
                // sort for binary search algorithm
                sort(searchList.begin(), searchList.end(), [](Car& a, Car& b) {
                        return a.isBestSelling() < b.isBestSelling();
                    });
                found = Binary_Search_bestSelling(searchList, 0, searchList.size()-1, 1);
                if (found == -1){
                    cout << endl;
                    cout << "No Best Selling Cars for now." << endl << endl;
                }
                else{
                    while (found != -1){
                        temp.push_back(searchList[found]);
                        searchList.erase(searchList.begin()+found);
                        found = Binary_Search_bestSelling(searchList, 0, searchList.size()-1, 1);

                    }
                    bubbleSort(temp);
                    displayAllCars();
                }

            }
            else {
                cout << endl;
                cout << "No car available." << endl << endl;
            }

        }

        void searchIssuedBills(){
            int choice;
            cout << endl << "Issued bills by: " << endl;
            cout << "1)Customer ID " << endl;
            cout << "2)Date of bill issued " << endl;
            cout << "> ";
            cin >> choice;
            bool status = true;
            while(status){
                try{
                    digitInputValidation();
                    status = false;
                }
                catch(string errorMsg){
                    cout << endl;
                    cout << "Error: " << errorMsg << endl;
                    cout << endl;
                    cout << endl;
                    cout << "> ";
                    cin >> choice;
                }
            }
            if (choice == 1){
                if (orderList.empty()){
                    cout << endl << "You have no previous purchase.";
                    cout << endl << endl;
                }
                else{
                    linearSearch_Bills();
                }
            }
            else if (choice == 2){
                if (orderList.empty()){
                    cout << endl << "You have no previous purchase.";
                    cout << endl << endl;
                }
                else{
                    struct tm date;
                    char dash;
                    cout << endl;
                    cout << "Enter bill data (day/month/year): ";
                    cin >> date.tm_mday >> dash >> date.tm_mon >> dash >> date.tm_year;
                    bool status = true;
                    while(status){
                        try{
                            dateInputValidation();
                            status = false;
                        }
                        catch(string errorMsg){
                            cout << endl;
                            cout << "Error: " << errorMsg << endl;
                            cout << endl;
                            cout << endl;
                            cout << "Enter bill data (day/month/year): ";
                            cin >> date.tm_mday >> dash >> date.tm_mon >> dash >> date.tm_year;
                        }
                    }
                    date.tm_mon -= 1;
                    date.tm_year -= 1900;
                    cout << endl;
                    linearSearch_Bills_Date(date);
                }
            }

        }
        void generateReport(){
            struct tm startTime = {0};
            struct tm endTime = {0};
            char dash;
            int found;
            totalPrice = 0;
            vector<OrderDetails> tempList = orderList;
            cout << "Enter specific period range" << endl;
            cout << "Please type according to the format and include '/' " << endl;
            cout << "Starting Date (day/month/year): ";
            cin >> startTime.tm_mday >> dash >> startTime.tm_mon >> dash >> startTime.tm_year;
            bool status = true;
            while(status){
                try{
                    dateInputValidation();
                    status = false;
                }
                catch(string errorMsg){
                    cout << endl;
                    cout << "Error: " << errorMsg << endl;
                    cout << endl;
                    cout << endl;
                    cout << "Starting Date (day/month/year): ";
                    cin >> startTime.tm_mday >> dash >> startTime.tm_mon >> dash >> startTime.tm_year;
                }
            }

            startTime.tm_mon -= 1;
            startTime.tm_year -= 1900;
            cout << "Ending Date (day/month/year): ";
            cin >> endTime.tm_mday >> dash >> endTime.tm_mon >> dash >> endTime.tm_year;
            status = true;
            while(status){
                try{
                    dateInputValidation();
                    status = false;
                }
                catch(string errorMsg){
                    cout << endl;
                    cout << "Error: " << errorMsg << endl;
                    cout << endl;
                    cout << endl;
                    cout << "Ending Date (day/month/year): ";
                    cin >> endTime.tm_mday >> dash >> endTime.tm_mon >> dash >> endTime.tm_year;
                }
            }


            endTime.tm_mon -= 1;
            endTime.tm_year -= 1900;

            time_t start_time_t = mktime(&startTime);
            time_t end_time_t = mktime(&endTime);

            if (end_time_t >= start_time_t) {
                reportList.clear();

                found = Binary_Search_report(tempList, 0, tempList.size()-1, startTime, endTime);
                if (found == -1){
                    cout << endl;
                    cout << "No purchase within this period." << endl << endl;
                }
                else{

                    while (found != -1){
                        reportList.push_back(tempList[found]);
                        tempList.erase(tempList.begin()+found);
                        found = Binary_Search_report(tempList, 0, tempList.size()-1, startTime, endTime);

                    }
                    quickSort(reportList, 0, reportList.size()-1);
                    for (auto& order : reportList){
                        order.displayReport();
                        totalPrice += order.getFinalPrice();
                    }
                    cout << "Total price of all sold cars: RM" << fixed << setprecision(2) << totalPrice;
                    cout << endl << endl;
                }

            } else {
                cout << endl;
                cout << "Period is invalid" << endl;
                cout << endl;
            }



        }
};



vector<int> OrderDetails :: numbers;

int main()
{
    srand(time(0)); // for generate random car ID
    int optionTask;
    char running;

    System system;
    // Initialize existing users and admins
    system.registeredAdmin(User("ADM123", "Ang Yi Xun", "Cho030909$"));
    system.registeredUser(User("NAJ123", "Dr Najla'a Ateeq M. Draib", "najla2024"));
    system.registeredUser(User("AIT935", "Choo Qie Sheng", "QS030208"));
    system.registeredUser(User("AIT974", "Khoo Song Hao", "SH050503"));

    // Initialize cars
    system.registeredCar(Car("Audi", "R8", "black", "Germany", 2021, 1200000, 5));
    system.registeredCar(Car("Toyota", "Prius", "Purple", "Japan", 2020, 200000, 10));
    system.registeredCar(Car("Peroduo", "MyVi", "Red", "Malaysia", 2022, 80000, 12));
    system.registeredCar(Car("Proton", "X70", "White", "China", 2023, 400000, 6));
    system.registeredCar(Car("BYD", "Seal", "black", "China", 2024, 400000, 11));
    system.registeredCar(Car("Honda", "Civic", "black", "Japan", 2022, 600000, 7));

    while(system.loginFunc()){
        running = 'y';
        while(running == 'y'){
            switch(system.availableTasks()){
                case 1:
                    system.displayAllCars();
                    break;
                case 2:
                    system.sortCar_MergeSort();
                    break;
                case 3:
                    system.sortCar_MergeSort();
                    break;
                case 4:
                    system.sortCar_MergeSort();
                    break;
                case 5:
                    system.searchBestSelling();
                    break;
                case 6:
                    system.searchCarByID();
                    break;
                case 7:
                    system.searchIssuedBills();
                    break;
                case 8:
                    if(system.getStatus() == "admin")
                        system.addNewCar();
                    else{
                        cout << endl;
                        running = 'n';
                    }
                    break;
                case 9:
                    system.modifyCar();
                    break;
                case 10:
                    system.removeCar();
                    break;
                case 11:
                    system.generateReport();
                    break;
                case 12:
                    cout << endl;
                    running = 'n';
                    break;
                default:
                    cout << "Invalid Input" << endl;
            }
        }
    }
    cout << endl;
    cout << "Thank you for visiting." << endl;
    cout << "Hope to see you again." << endl;
    return 0;
}
