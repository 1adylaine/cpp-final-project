#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cstring>
using namespace std;

char code[100][50];
char name[100][50];
char brand[100][50];
char item[100][50];
int quantity[100];
int price[100];

static int count = 0; //to store in the array by incrementing index

//search product and return its index for easy access and reusability
int productIndex(char code[][50], int count, char searchCode[]){
	for(int i = 0; i < count; i++){
		if(strcmp(code[i], searchCode) == 0){
			return i; // this returns the index
		}
	}
	return -1; //returns -1 if it does not exist
}

//display specific product for edit and search
void displaySpecificProduct(int i){
	cout << "Code      : " << code[i] << endl;
	cout << "Name      : " << name[i] << endl;
	cout << "Brand     : " << brand[i] << endl;
	cout << "Item      : " << item[i] << endl;
	cout << "Quantity  : " << quantity[i] << endl;
	cout << "Price     : " << price[i] << endl;	
	cout << endl;
}

//code based on product name, brand
void productCode(char name[], char brand[], char result[]){
    string code = "";
    string binary = "";	
    
    for(int i = 0; i < 2; i++){
        code += brand[i];
    }
    code += "-";
    for(int i = 0; i < 2; i++){
        code += name[i];
    }
    
    int itemNum = count + 1;
    
    //binary in product code base on number in array
    while(itemNum > 0){
        int remainder = itemNum % 2;
        if(remainder != 0){
            binary = "1" + binary;
        }
        else{
            binary = "0" + binary;
        }
        itemNum /= 2;
    }
    code += binary;
    
    char temp[50];
    strcpy(temp, code.c_str());
    strupr(temp);
    strcpy(result, temp);
}

void addProduct(){

	cout << "---------- ADD PRODUCT DETAIL ----------\n";
	cout << "Name      : "; cin.ignore(); cin.getline(name[count], 50);
	cout << "Brand     : "; cin.getline(brand[count], 50);
	cout << "Item      : "; cin.getline(item[count], 50);
	cout << "Quantity  : "; cin >> quantity[count];
	cout << "Price     : "; cin >> price[count];
	
	productCode(name[count], brand[count], code[count]);
	
	//check if product is unique
	int checkCode = productIndex(code, count, code[count]);
	
    if(checkCode != -1){
        cout << "\nProduct already exists! (Code: " << code[count] << ")\n";
        displaySpecificProduct(checkCode);
        
        cout << "[1] Update Quantity\n";
        cout << "[2] Update Price\n";
        cout << "[3] Back to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        
        if(choice == 1){
            int additional;
            cout << "Enter additional Quantity: ";
            cin >> additional;
            quantity[checkCode] += additional;
            cout << "Quantity updated! New Quantity: " << quantity[checkCode] << "\n\n";
        }
        else if(choice == 2){
            cout << "Enter New Price: ";
            cin >> price[checkCode];
            cout << "Price updated!\n\n";
        }
        else{
    		cout << "Cancelled. Going back to menu.\n\n";
    		return;
		}
		
        return;
    }
	
	cout << "Code      : " << code[count] << endl;
	cout << "Product added\n\n";
	count++;
}

void editProduct(){
	char editcode[50], modifiedDetail[50];
	int choice, modifiedDetailnum;
	cout << "---------- EDIT PRODUCT ----------\n";
	cout << "Enter product code to edit: ";
	cin.ignore(); cin.getline(editcode, 50);
	cout << endl;
	
	int index = productIndex(code, count, editcode); //get the index to access the searched code
	
	if(index == -1){
		cout << "Product not found.\n\n";
		return;
	}
	
	cout <<"---------- CURRENT PRODUCT DETAILS ---------\n";
	displaySpecificProduct(index);
	
	cout << "\nWhat do you want to edit?\n";
	cout << "[1] Name     [2] Brand     [3] Item\n";
	cout << "[4] Quantity [5] Price     [6] Edit All\n";
	cout << "Enter choice: ";
	cin >> choice; 
	
	if(choice == 1){
		cout << "Enter New Name: ";
		cin.ignore(); cin.getline(modifiedDetail, 50);
		strcpy(name[index], modifiedDetail);
	}
	else if(choice == 2){
		cout << "Enter New Brand: ";
		cin.ignore(); cin.getline(modifiedDetail, 50);
		strcpy(brand[index], modifiedDetail);
	}
	else if(choice == 3){
		cout << "Enter New Item: ";
		cin.ignore(); cin.getline(modifiedDetail, 50);
		strcpy(item[index], modifiedDetail);
	}
	else if(choice == 4){
		cout << "Update Quantity: ";
		cin >> modifiedDetailnum;
		quantity[index] = modifiedDetailnum;
	}
	else if(choice == 5){
		cout << "Enter New Price: ";
		cin >> modifiedDetailnum;
		price[index] = modifiedDetailnum;
	}
	else if(choice == 6){
		cout << "Enter New Name: ";
		cin.ignore(); cin.getline(modifiedDetail, 50);
		strcpy(name[index], modifiedDetail);
		
		cout << "Enter New Brand: ";
		cin.getline(modifiedDetail, 50);
		strcpy(brand[index], modifiedDetail);
		
		cout << "Enter New Item: ";
		cin.getline(modifiedDetail, 50);
		strcpy(item[index], modifiedDetail);
		
		cout << "Update Quantity: ";
		cin >> modifiedDetailnum;
		quantity[index] = modifiedDetailnum;
		
		cout << "Enter New Price: ";
		cin >> modifiedDetailnum;
		price[index] = modifiedDetailnum;
	}
	else {
		cout << "Error input\n\n";
		return;
	}
	
	productCode(name[index], brand[index], code[index]);
	
	cout << "Updated Successfully!\n\n";
	
}

//pad for char arrays
string pad(char s[], int width){
	string str = s;
    while(str.length() < width){
        str += " ";
    }
    return str;
}

string padInt(int num, int width){
    string s = "";
    int temp = num;
    if(temp == 0) s = "0";
    while(temp > 0){
        s = char('0' + temp % 10) + s;
        temp /= 10;
    }
    while(s.length() < width){
        s += " ";
    }
    return s;
}

//display all products
void displayProduct(){
	
	if(count == 0){
		cout << "----- BOUTIQUE INVENTORY IS EMPTY -----\n\n";
		return;
	}
	
	cout <<"============================================================\n";
	cout <<"|                   P R O D U C T   L I S T                |\n";
	cout <<"============================================================\n\n";
	
	char displayedItems[100][50];
	int displayedcount = 0;
	
	
	for(int i = 0; i < count; i++){
		char currentItem[50];
		strcpy(currentItem, item[i]);
		
		bool alreadyDisplayed = false;
		
		for(int j = 0; j < displayedcount; j++){
			if(strcmp(displayedItems[j], currentItem) == 0) {
				alreadyDisplayed = true;
				break;
			}
		}
		
		if(!alreadyDisplayed) {
			cout << "\n                    [ ITEM: "<< currentItem << " ]\n";
			cout << "-----------------------------------------------------------------\n";
			cout << "| CODE     | NAME               | BRAND     | QTY   | PRICE     |\n";
			cout << "-----------------------------------------------------------------\n";
			
			for(int a = 0; a < count; a++){
				if(strcmp(item[a], currentItem) == 0){
					cout << "| " << pad(code[a], 8) 
     				<< " | " << pad(name[a], 18)
     				<< " | " << pad(brand[a], 9)
     				<< " | " << padInt(quantity[a], 5)
     				<< " | Php " << padInt(price[a], 6) << "|\n";
				}
			}
			
			cout << "-----------------------------------------------------------------\n";
			strcpy(displayedItems[displayedcount], currentItem);
			displayedcount++;
		}
		
	}
	cout << "-----------------------------------------------------------------\n";
}


void searchProduct(){
	char searchProduct[50];
	cout << "Product code to search: ";
	cin.ignore(); cin.getline(searchProduct, 50);
	
	int i = productIndex(code, count, searchProduct); //use product index again
	
	if(i == -1){
		cout << "Product not found.\n\n";
		return;
	}
	
	displaySpecificProduct(i);
}

void deleteProduct(){
	char remove[50];
	cout << "Code of product to delete: ";
	cin.ignore(); cin.getline(remove, 50);

	int index = productIndex(code, count, remove); //index of product to be deleted
	
	if(index == -1){
		cout << "Product not found.\n\n";
		return;
	}
	
	//removes the product by changine the index of the rest (example: index 2 will be removed and index 3 will be the new index 2) 
	for(int i = index; i < count - 1; i++){	
		strcpy(code[i], code[i + 1]);
		strcpy(name[i], name[i + 1]);
		strcpy(brand[i], brand[i + 1]);
		strcpy(item[i], item[i + 1]);
		quantity[i] = quantity[i + 1];
		price[i] = price[i + 1];
	}
	cout << "Product deleted.\n\n";
	count--; //minus 1 sa array size
}

void displayMenu(){
	cout << "=========================================\n";
	cout << "|         N A M E   B O U T I Q U E     |\n";
	cout << "|             INVENTORY SYSTEM          |\n";
	cout << "=========================================\n";
	cout << "|  [1] Add Product                      |\n";
	cout << "|  [2] Edit Product                     |\n";
	cout << "|  [3] Display All Products             |\n";
	cout << "|  [4] Search Product                   |\n";
	cout << "|  [5] Remove Product                   |\n";
	cout << "|  [6] Close System                     |\n";
	cout << "=========================================\n";
	cout << "Enter your choice: ";
}

int main(){
	int choice;
	char answer;
	
	do {
		displayMenu();
		cin >> choice;
		cout <<endl;
		
		switch(choice){
        	case 1: addProduct(); break;
        	case 2: editProduct(); break;
        	case 3: displayProduct(); break;
        	case 4: searchProduct(); break;
        	case 5: deleteProduct(); break;
        	case 6: break;
        	default: cout << "Invalid choice!\n";
    	}
		do {
    		cout << "Return to menu? [Y / N]: ";
    		cin >> answer;
    		if(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
        	cout << "  Invalid input. Please enter Y or N only.\n";
		} while(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n');
		
		system("cls");
	}while(true);
	
	cout << "Press any key to exiting Program...";
	getch();
	return 0;
}

	/* todo:
	design user interface -done
	apply topics discussed / replace code if topic applies
	edit product design -done
	try to put parameters in void functions 
	
	responds to possible user input errors
	
	check readability
	structural design
	efficiency
	*/
