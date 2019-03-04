#include<bits/stdc++.h>
using namespace std;

long uniqueid;
long accid;
double mainBal;

struct Product {
    long id=-1;
    long orderer=-1;
    string orderer_name="NULL";
    string name="NULL";
    double price=0.0;
    long quantity=0;
    double profit=0.0;
};
typedef struct Product product;

struct ID {
    int id;
    string username;
    string password;
    double balance=10000.00;
    vector<product>pd;
};
typedef struct ID acc;

void deliver(vector<product> &orders, vector<product> &prod, vector<acc> &ret, vector<acc> &man, int loginID);
void fileIn(vector <acc> &man, vector<acc> &ret, vector<product> &prod, vector<product> &orders);
void save(vector <acc> &man, vector<acc> &ret, vector<product> &prod, vector<product> &orders);
void Order(vector<product> &prod, vector<product> &orders, vector<ID> &ret, int loginID);
void myOrders(vector<product> &orders, vector<acc> &ret, int loginID);
void ManufactProd(vector<product> &prod, vector<acc> &man, int loginID);
void pending(vector<product> &v, vector<product> &mp);
void makeID(vector<acc> &p, string a, string b);
void ListAllProd(vector<product> &v, int com);
void outProd(vector<product> &prod, int com);
void inProd(vector<product> &prod, int com);
int searchProd(vector<product> &v, long id);
void removeID(vector<acc> &ac, int id);
void outID(vector<acc> &id, int com);
void inID(vector<acc> &id, int com);
void removeProd(vector<product> &v);
int findID(vector<acc> &v, int id);
void editProd(vector<product> &v);
void addProd(vector<product> &v);
void bal(vector<acc> &v, int id);
int login(vector<acc> &p);
void status(int id);
int homescreen();
void outOthers();
void inOthers();

int main() {
    system("COLOR FC");
    vector<acc> man;
    vector<acc> ret;
    vector<product> prod;
    vector<product> orders;
    fileIn(man, ret, prod, orders);
    status(0);
    while(1) {
        int t;
        puts("1. Manufacturer Login\n2. Retailer Login\n3. Admin Login\n4. Exit\n");
        scanf("%d", &t);
        if(t==1) {
            int loginID=login(man);
            if(loginID!=-1) {
                while(1) {
                    int t1;
                    puts("1. Orders\n2. Modify products\n3. My Account Balance\n4. Main Balance\n5. Logout\n");
                    scanf("%d", &t1);
                    if(t1==5) {
                        status(2);
                        break;
                    }
                    if(t1==4)
                        printf("Main balance is %.2lf$\n\n", mainBal);
                    if(t1==3)
                        bal(man, loginID);
                    if(t1==2) {
                        int t1;
                        while(1) {
                            puts("1. Add product\n2. Edit product\n3. Remove product\n4. List All products\n5. Manufacture\n6. Back\n");
                            scanf("%d", &t1);
                            if(t1==1)
                                addProd(prod);
                            if(t1==2)
                                editProd(prod);
                            if(t1==3)
                                removeProd(prod);
                            if(t1==4)
                                ListAllProd(prod,1);
                            if(t1==5)
                                ManufactProd(prod, man, loginID);
                            if(t1==6)
                                break;
                        }
                        save(man, ret, prod, orders);
                    }
                    if(t1==1) {
                        while(1){
                            puts("1. View pending orders\n2. Deliver\n3. Back\n");
                            scanf("%d", &t);
                            if(t==1)
                                pending(orders, prod);
                            if(t==2)
                                deliver(orders, prod, ret, man, loginID);
                            if(t==3)
                                break;
                        }
                        save(man, ret, prod, orders);
                    }
                    save(man, ret, prod, orders);
                }
            }
        }
        else if(t==2) {
            int loginID=login(ret);
            if(loginID!=-1) {
                while(1) {
                    int t;
                    puts("1. Product ordering\n2. My available products\n3. Account balance\n4. Logout\n");
                    scanf("%d", &t);
                    if(t==1){
                        while(1){
                            int t1;
                            puts("1. List all available products\n2. Order product\n3. My orders\n4. Back\n");
                            scanf("%d", &t1);
                            if(t1==1) ListAllProd(prod, 2);
                            else if(t1==2)
                                Order(prod, orders, ret, loginID);
                            else if(t1==3)
                                myOrders(orders, ret, loginID);
                            else if(t1==4)
                                break;
                        }
                        save(man, ret, prod, orders);
                    }
                    if(t==2)
                        ListAllProd(ret[loginID].pd, 3);
                    if(t==3)
                        bal(ret, loginID);
                    if(t==4) {
                        status(2);
                        break;
                    }
                }
                save(man, ret, prod, orders);
            }
        }
        else if(t==3){
            while(1){
                char str[100], str2[100];
                printf("Enter username: ");
                scanf(" %s", str);
                printf("Enter password: ");
                scanf(" %s", str2);
                string s1=str, s2=str2;
                if(s1+"x"==s2){
                    status(1);
                    while(1){
                        puts("1. Create account\n2. Remove account\n3. View all accounts\n4. View Main Balance\n5. Change main balance\n6. Logout\n");
                        int t1;
                        scanf("%d", &t1);
                        if(t1==6){
                            status(2);
                            break;
                        }
                        if(t1==5){
                            printf("Current Main Balance: %lf$\n", mainBal);
                            printf("New Balance         : ");
                            double nw;
                            scanf(" %lf", &nw);
                            if(nw>10000){
                                mainBal=nw;
                                printf("New Main Balance: %lf$\n\n", mainBal);
                                break;;
                            }
                            else
                                printf("Not possible\n\n");
                        }
                        if(t1==4){
                            printf("Current Main Balance is: %lf\n\n", mainBal);
                        }
                        if(t1==3){
                            if(man.empty()){
                                printf("No Manufacturer account available\n\n");
                            }
                            else{
                                printf("Manufacturer ID's:\n-----------------\n");
                                for(int i=0; i<man.size(); i++){
                                    printf("Manufacturer ID      : %ld\n", man[i].id);
                                    printf("Manufacturer Username: %s\n\n", man[i].username.c_str());
                                }
                            }
                            if(ret.empty()){
                                printf("No Retailer account available\n\n");
                            }
                            else{
                                printf("Retailer ID's:\n--------------\n");
                                for(int i=0; i<ret.size(); i++){
                                    printf("Retailer ID      : %ld\n", ret[i].id);
                                    printf("Retailer Username: %s\n\n", ret[i].username.c_str());
                                }
                            }
                        }
                        if(t1==2){
                            while(1){
                                puts("1. Remove Manufacturer ID\n2. Remove Retailer ID\n3. Back\n");
                                int t2;
                                scanf("%d", &t2);
                                int id;
                                if(t2==1 || t2==2){
                                    printf("Insert ID: ");
                                    scanf("%d", &id);
                                    if(t2==1)
                                        removeID(man, id);
                                    else if(t2==2)
                                        removeID(ret, id);
                                }
                                else break;
                            }
                            save(man, ret, prod, orders);
                        }
                        if(t1==1){
                            while(1){
                                puts("1. Create Manufacturer ID\n2. Create Retailer ID\n3. Back\n");
                                int t2;
                                scanf("%d", &t2);
                                if(t2==1 || t2==2){
                                    char st1[100], st2[100];
                                    printf("Insert Username: ");
                                    scanf(" %[^\n]", st1);
                                    printf("Insert Password: ");
                                    scanf(" %[^\n]", st2);
                                    if(t2==1)
                                        makeID(man, st1, st2);
                                    else if(t2==2)
                                        makeID(ret, st1, st2);
                                    printf("The account has been created\n\n");
                                }
                                else break;
                            }
                            save(man, ret, prod, orders);
                        }
                    }
                }
                else{
                    puts("Invalid ID/Password\n");
                    continue;
                }
                break;
            }
            save(man, ret, prod, orders);
        }
        else break;
    }
    save(man, ret, prod, orders);
    status(-1);
    return 0;
}

void removeID(vector<acc> &ac, int id){
    for(int i=0; i<ac.size(); i++){
        if(ac[i].id==id){
            ac.erase(ac.begin()+i);
            printf("ID is removed Successfully\n\n");
            return;
        }
    }
    printf("ID not found\n\n");
}

void status(int id) {
    if(id==0) {
        puts("\t\t\t\t ==================================== ");
        puts("\t\t\t\t|| Supply Chain Simulation Software ||");
        puts("\t\t\t\t ==================================== ");
        puts("\t\t\t\t -=-==-===-==== V 1.23 ====-===-==-=- ");
        printf("\n\n\n");
    }
    if(id==-1) {
        puts("\t\t\t\t\t ================== ");
        puts("\t\t\t\t\t|| Program Closed ||");
        puts("\t\t\t\t\t ================== ");
    }
    if(id==1){
        puts("\t\t\t\t\t ================== ");
        puts("\t\t\t\t\t||   Logged  In   ||");
        puts("\t\t\t\t\t ================== ");
    }
    if(id==2){
        puts("\t\t\t\t\t ================== ");
        puts("\t\t\t\t\t||   Logged Out   ||");
        puts("\t\t\t\t\t ================== ");
    }
}

int login(vector<acc> &p) {
    string username;
    string password;
    printf("Username:\t");
    cin>> username;
    printf("Password:\t");
    cin>> password;
    int f=0,i;
    for(i=0; i<p.size(); i++) {
        if(p[i].username==username && p[i].password==password) {
            f=1;
            break;
        }
    }
    if(f) {
        status(1);
        return i;
    }
    else {
        int tmp;
        puts("Invalid username/password\nTry again?\n1. Yes\n2. No(back)\n\n");
        scanf("%d", &tmp);
        if(tmp==1)
            return login(p);
        else return -1;
    }
}

void makeID(vector<acc> &p, string a, string b) {
    acc tmp;
    tmp.id=accid++;
    tmp.username=a;
    tmp.password=b;
    p.push_back(tmp);
}

int homescreen() {
    int t;
    puts("1. Manufacturer Login\n2. Retailer Login\n3. Admin\n4. Exit\n");
    while(cin>>t) {
        if(t==1) return 1;
        else if(t==2) return 2;
        else if(t==3) return 3;
        else return 0;
    }
}

void addProd(vector<product> &v){
    product tmp;
    char str[100];
    printf("New product ID        : %ld\n", uniqueid);
    printf("Insert product Name   : ");
    scanf(" %[^\n]", str);
    tmp.name=str;
    printf("Insert Retail Price   : ", tmp.name.c_str());
    while((cin>> tmp.price)&&tmp.price<=0){
        printf("Zero/Negative amount not accepted\n\n");
        printf("Insert Retail Price   : ", tmp.name.c_str());
    }
    printf("Insert profit per unit: ", tmp.profit);
    while((cin>> tmp.profit)&&tmp.price<=0){
        printf("Zero/Negative amount not accepted\n\n");
        printf("Insert profit per unit: ", tmp.name.c_str());
    }
    tmp.id=uniqueid;
    v.push_back(tmp);
    printf("%s added\nNew ID: %ld\n\n", tmp.name.c_str(), uniqueid);
    uniqueid++;
}

int searchProd(vector<product> &v, long id){
    for(int i=0; i<v.size(); i++){
        if(v[i].id==id){
            return i;
        }
    }
    return -1;
}

void removeProd(vector<product> &v){
    printf("Insert product id: ");
    long id;
    cin>> id;
    string name;
    int p=searchProd(v, id);
    if(p!=-1){
        name=v[p].name;
        printf("Product(%ld, %s) is removed successfully\n\n", id, name.c_str());
        v.erase(v.begin()+p);
    }
    else printf("Product %ld not found\n\n", id);
}

void editProd(vector<product> &v){
    printf("Insert product id: ");
    long id;
    string name;
    double tmp;
    cin>> id;
    int p=searchProd(v, id);
    if(p!=-1){
        printf("Current name           : %s\n", v[p].name.c_str());
        printf("New name               : ");
        cin>> name;
        v[p].name=name;
        printf("Retail price           : %.2lf$\n", v[p].price);
        printf("New price              : ");
        cin>>tmp;
        v[p].price=tmp;
        printf("Current profit per unit: %.2lf$\n", v[p].profit);
        printf("New profit per unit    : ");
        cin>> tmp;
        v[p].profit=tmp;
        puts("Product is edited successfully\n\n");
    }
    else printf("Product %ld not found\n\n", id);
}

void ListAllProd(vector<product> &v, int com){
    for(int i=0; i<v.size(); i++){
        printf("Product ID        : %ld\n", v[i].id);
        printf("Product Name      : %s\n", v[i].name.c_str());
        printf("Retail Price      : %.2lf$\n", v[i].price);
        if(com==1)
            printf("Profit per unit   : %.2lf$\n", v[i].profit);
        if(com!=1 && com!=3)
            printf("\n");
        if(com==3 || com==1)
            printf("Products Available: %ld\n\n", v[i].quantity);
    }
    if(v.empty()) printf("No products available currently\n\n");
}

void ManufactProd(vector<product> &prod, vector<acc> &man, int loginID){
    long id;
    int Q;
    if(prod.empty()){
        printf("You have no products to produce\n\n");
        return;
    }
    printf("Insert Product ID: ");
    cin>>id;
    int p=searchProd(prod, id);
    if(p!=-1){
        printf("Insert Quantity  : ");
        cin>>Q;
        if(Q<=0){
            printf("Zero/Negative quantity not accepted\n\n");
            return;
        }
        if(mainBal < (prod[p].price-prod[p].profit)*Q){
            printf("You have insufficient balance\n\n");
            return;
        }
        prod[p].quantity+=Q;
        mainBal-=((prod[p].price-prod[p].profit)*Q);
        printf("Manufacturing done\n");
        printf("You have %ld %ss now\n\n", prod[p].quantity, prod[p].name.c_str());
        return;
    }
    printf("Product %ld not found\n\n", id);
}

void Order(vector<product> &prod, vector<product> &orders, vector<ID> &ret, int loginID){
    long id;
    int Q;
    printf("Insert Product ID: ");
    cin>>id;
    int p=searchProd(prod, id);
    if(p!=-1){
        printf("Insert quantity  : ");
        cin>>Q;
        if(Q<=0){
            printf("Zero/Negative quantity not accepted\n\n");
            return;
        }
        if(ret[loginID].balance < (prod[p].price)*Q){
            printf("You have insufficient balance\n\n");
            return;
        }
        product tmp;
        tmp.quantity=Q;
        tmp.id=id;
        tmp.name=prod[p].name;
        tmp.orderer_name=ret[loginID].username;
        tmp.profit=prod[p].profit;
        tmp.price=prod[p].price;
        tmp.orderer=ret[loginID].id;
        ret[loginID].balance-=(Q*prod[p].price);
        orders.push_back(tmp);
        printf("Your order is taken successfully\n\n");
        return;
    }
    printf("Product %ld not found\n\n", id);
}

void bal(vector<acc> &v, int id){
    printf("Your account balance is: %.2lf$\n\n", v[id].balance);
}

void pending(vector<product> &v, vector<product> &mp){
    if(v.empty()){
        puts("You have no pending orders\n");
        return;
    }
    for(int i=0; i<v.size(); i++){
        printf("Order No          : %ld\n---------------------\n", i+1);
        printf("Ordered by        : %ld\n", v[i].orderer);
        printf("Orderer Name      : %s\n", v[i].orderer_name.c_str());
        printf("Product ID        : %ld\n", v[i].id);
        printf("Product Name      : %s\n", v[i].name.c_str());
        printf("Total Cost        : %.2lf$\n", (v[i].price-v[i].profit)*v[i].quantity);
        printf("Estimated Profit  : %.2lf$\n", v[i].profit*v[i].quantity);
        printf("Products ordered  : %ld\n", v[i].quantity);
        int p=searchProd(mp, v[i].id);
        printf("Products available: %ld\n", mp[p].quantity);
        printf("Ready             : %s\n\n", mp[p].quantity>=v[i].quantity? "Yes":"No");
    }
}

int findID(vector<acc> &v, int id){
    for(int i=0; i<v.size(); i++){
        if(v[i].id==id) return i;
    }
    return -1;
}

void deliver(vector<product> &orders, vector<product> &prod, vector<acc> &ret, vector<acc> &man, int loginID){
    long p, prodID;
    if(orders.empty()){
        printf("You have no orders at this moment\n\n");
        return;
    }
    printf("Insert order ID: ");
    cin>>p;
    prodID=orders[p-1].id;
    if(p>orders.size()){
        printf("Invalid order id\n\n");
        return;
    }
    int q=searchProd(prod, prodID);
    if(q!=-1){
        p--;
        if(prod[q].quantity>=orders[p].quantity){
            int r= findID(ret, orders[p].orderer);
            printf("Product Delivered to: %s\nRetailer id        : %ld\n\n", ret[r].username.c_str(), ret[r].id);
            int f=0;
            int l=ret[r].pd.size();
            for(int i=0; i<l; i++){
                if(ret[r].pd[i].id==prodID){
                    f=1;
                    ret[r].pd[i].quantity+=orders[p].quantity;
                    break;
                }
            }
            if(!f)
                ret[r].pd.push_back(orders[p]);
            prod[q].quantity-=orders[p].quantity;
            double prof=orders[p].profit * orders[p].quantity;
            mainBal+=(orders[p].price * orders[p].quantity)-(prof*25/100.00);
            man[loginID].balance+=(prof*25/100.00);
            orders.erase(orders.begin()+p);
        }
        else
            printf("%ld is not ready to deliver yet\n\n");
    }
    else
        printf("Product %ld not found\n\n", prodID);
}

void myOrders(vector<product> &orders, vector<acc> &ret, int loginID){
    for(int i=0; i<orders.size(); i++){
        if(orders[i].orderer==ret[loginID].id){
            printf("Product ID      : %ld\n", orders[i].id);
            printf("Product Name    : %s\n", orders[i].name.c_str());
            printf("Products ordered: %ld\n", orders[i].quantity);
            printf("Total Cost      : %.2lf$\n\n", orders[i].quantity*orders[i].price);
        }
    }
}

void outProd(vector<product> &prod, int com){
    ofstream myfile;
    if(com==1)
        myfile.open ("Prod.txt");
    else
        myfile.open ("Orders.txt");
    if(myfile.is_open()){
        myfile<<prod.size()<<endl;
        for(int i=0; i<prod.size(); i++){
            myfile<<prod[i].id<<endl;
            myfile<<prod[i].orderer<<endl;
            myfile<<prod[i].orderer_name<<endl;
            myfile<<prod[i].name<<endl;
            myfile<<setprecision(10)<<prod[i].price<<endl;
            myfile<<prod[i].quantity<<endl;
            myfile<<setprecision(10)<<prod[i].profit<<endl;
        }
        myfile.close();
    }
}

void inProd(vector<product> &prod, int com){
    FILE* file;
    if(com==1)
        file = fopen ("Prod.txt", "r");
    else
        file = fopen ("Orders.txt", "r");
    long l;
    fscanf (file, " %d", &l);
    for(int i=0; i<l; i++){
            product tmp;
            char str1[100], str2[100];
            fscanf(file," %ld", &tmp.id);
            fscanf(file," %ld", &tmp.orderer);
            fscanf(file," %[^\n]", str1);
            tmp.orderer_name=str1;
            fscanf(file," %[^\n]", str2);
            tmp.name=str2;
            fscanf(file," %lf", &tmp.price);
            fscanf(file," %ld", &tmp.quantity);
            fscanf(file," %lf", &tmp.profit);
            prod.push_back(tmp);
        }
    fclose (file);
}

void outID(vector<acc> &id, int com){
    ofstream myfile;
    if(com==1)
        myfile.open ("Man.txt");
    else
        myfile.open ("Ret.txt");
    if(myfile.is_open()){
        myfile<<id.size()<<endl;
        for(int i=0; i<id.size(); i++){
            myfile<<id[i].id<<endl;
            myfile<<id[i].username<<endl;
            myfile<<id[i].password<<endl;
            myfile<<setprecision(10)<<id[i].balance<<endl;

            if(com==2){
                myfile<<id[i].pd.size()<<endl;
                for(int j=0; j<id[i].pd.size(); j++){
                    myfile<<id[i].pd[j].id<<endl;
                    myfile<<id[i].pd[j].orderer<<endl;
                    myfile<<id[i].pd[j].orderer_name<<endl;
                    myfile<<id[i].pd[j].name<<endl;
                    myfile<<setprecision(10)<<id[i].pd[j].price<<endl;
                    myfile<<id[i].pd[j].quantity<<endl;
                    myfile<<setprecision(10)<<id[i].pd[j].profit<<endl;
                }
            }
        }
        myfile.close();
    }
}

void inID(vector<acc> &id, int com){
    FILE* file;
    if(com==1)
        file= fopen ("Man.txt", "r");
    else
        file= fopen ("Ret.txt", "r");
    long l;
    fscanf (file, " %d", &l);
    for(int i=0; i<l; i++){
            acc tmp;
            char str1[100], str2[100];
            fscanf(file," %ld", &tmp.id);
            fscanf(file," %[^\n]", str1);
            tmp.username=str1;
            fscanf(file," %[^\n]", str2);
            tmp.password=str2;
            fscanf(file," %lf", &tmp.balance);
            id.push_back(tmp);
            if(com==2){
                long m;
                fscanf (file, " %d", &m);
                for(int j=0; j<m; j++){
                    product tmp2;
                    char st1[100], st2[100];
                    fscanf(file," %ld", &tmp2.id);
                    fscanf(file," %ld", &tmp2.orderer);
                    fscanf(file," %[^\n]", st1);
                    tmp2.orderer_name=st1;
                    fscanf(file," %[^\n]", st2);
                    tmp2.name=st2;
                    fscanf(file," %lf", &tmp2.price);
                    fscanf(file," %ld", &tmp2.quantity);
                    fscanf(file," %lf", &tmp2.profit);
                    id.back().pd.push_back(tmp2);
                }
            }
        }
    fclose (file);
}

void outOthers(){
    FILE* file = fopen ("Others.txt", "w");
    fprintf(file,"%ld\n", uniqueid);
    fprintf(file,"%ld\n", accid);
    fprintf(file,"%.10lf\n", mainBal);
    fclose(file);
}

void inOthers(){
    FILE* file = fopen ("Others.txt", "r");
    fscanf(file," %ld", &uniqueid);
    fscanf(file," %ld", &accid);
    fscanf(file," %lf", &mainBal);
    fclose(file);
}

void save(vector <acc> &man, vector<acc> &ret, vector<product> &prod, vector<product> &orders){
    outOthers();
    outProd(prod, 1);
    outProd(orders, 2);
    outID(man, 1);
    outID(ret, 2);
}

void fileIn(vector <acc> &man, vector<acc> &ret, vector<product> &prod, vector<product> &orders){
    inProd(prod, 1);
    inID(man, 1);
    inProd(orders, 2);
    inID(ret, 2);
    inOthers();
}
