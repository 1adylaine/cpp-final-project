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

//int input validator
int intChecker(){
	int num;
	while(true){
		cin >> num;
		if(cin.fail()){
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input! Enter a number: ";
		}
		else{
			return num;
		}
	}
}

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
    char binary[50] = "";
    int binaryLen = 0;
    int pos = 0; //position for storing the code in the result

    // Add first 2 chars of brand
    result[pos++] = brand[0];
    result[pos++] = brand[1];
    result[pos++] = '-';

    // Add first 3 chars of name
    result[pos++] = name[0];
    result[pos++] = name[1];
    result[pos++] = name[2];
    result[pos++] = '-';
    
    result[pos] = '\0'; //null terminator

    int itemNum = count + 1;

    //binary in product code base on number in array
    while(itemNum > 0){
        for(int i = binaryLen; i > 0; i--){
            binary[i] = binary[i - 1];
		}
        if(itemNum % 2 != 0){
        	binary[0] = '1';
		}
		else {
			binary[0] ='0';
		}
		
		binary[++binaryLen] = '\0';
		itemNum /= 2;
    }

    strcat(result, binary);
    strupr(result);
}

void addProduct(){

	if(count >= 100){
		cout << "Inventory is full!\n\n";
		return;
	}

	cout << "---------- ADD PRODUCT DETAIL ----------\n";
	cout << "Name      : "; cin.ignore(); cin.getline(name[count], 50);
	if(strlen(name[count]) < 3){
    	cout << "Invalid input!\n\n";
    	return;
	}	

	cout << "Brand     : "; cin.getline(brand[count], 50);
	if(strlen(brand[count]) < 2){
    	cout << "Invalid input!\n\n";
    	return;
	}	
	
	cout << "Item      : "; cin.getline(item[count], 50);
	if(strlen(item[count]) == 0){
		cout << "Invalid input!\n\n";
		return;
	}

	cout << "Quantity  : "; quantity[count] = intChecker();
	if(quantity[count] < 0){
		cout << "Invalid input!\n\n";
		return;
	}

	cout << "Price     : "; price[count] = intChecker();
	if(price[count] < 0){
		cout << "Invalid input!\n\n";
		return;
	}

	int checkDuplicate = -1; //-1 means no duplicate
	for(int i = 0; i < count; i++){
		if(strcmp(name[i], name[count]) == 0 &&
		   strcmp(brand[i], brand[count]) == 0 &&
		   strcmp(item[i], item[count]) == 0){
			checkDuplicate = i; //if is equal to exact same existing item it returns its index which is != -1 meaning it's a duplicate
			break;   	
		}
	}
	
	if(checkDuplicate != -1){
		int choice, additional;
		cout << "Product already exists!";
		displaySpecificProduct(checkDuplicate);
		
		cout <<"[1] Update Quantity\n";
		cout <<"[2] Update Price\n";
		cout<<"[3] Back to Main Menu\n";
		cout <<"Enter choice: ";
		choice = intChecker();
		if(choice == 1){
			cout<< "Enter additional Quantity: ";
			additional = intChecker();
			if(additional < 0){
				cout << "Invalid input!\n\n";
				return;
			}
			quantity[checkDuplicate] += additional; //* fixed: use validated temp var before adding
			cout << "Quantity updated!\n\n"; 		
		}
		else if(choice == 2){
			//* fixed: store in temp first, validate, then assign to avoid saving negative value
			int newPrice = intChecker();
			if(newPrice < 0){
				cout << "Invalid input!\n\n";
				return;
			}
			price[checkDuplicate] = newPrice;
			cout << "Price updated!\n\n";
		}
		else{
			cout << "Cancelled. Going back to menu.\n\n";
			return;
		}
		return;
	}
	
	productCode(name[count], brand[count], code[count]);
	
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
	choice = intChecker(); 
	
	if(choice == 1){
		cout << "Enter New Name: ";
		cin.ignore(); cin.getline(modifiedDetail, 50);
		if(strlen(modifiedDetail) < 3){
			cout << "Invalid input!\n\n";
			return;
		}
		strcpy(name[index], modifiedDetail);
	}
	else if(choice == 2){
		cout << "Enter New Brand: ";
		cin.ignore(); cin.getline(modifiedDetail, 50);
		if(strlen(modifiedDetail) < 2){
			cout << "Invalid input!\n\n";
			return;
		}
		strcpy(brand[index], modifiedDetail);
	}
	else if(choice == 3){
		cout << "Enter New Item: ";
		cin.ignore(); cin.getline(modifiedDetail, 50);
		if(strlen(modifiedDetail) == 0){
			cout << "Invalid input!\n\n";
			return;
		}
		strcpy(item[index], modifiedDetail);
	}
	else if(choice == 4){
		cout << "Update Quantity: ";
		//* fixed: store in temp first, validate, then assign to avoid saving negative value
		int newQty = intChecker();
		if(newQty < 0){
			cout << "Invalid input!\n\n";
			return;
		}
		quantity[index] = newQty;
	}
	else if(choice == 5){
		cout << "Enter New Price: ";
		//* fixed: store in temp first, validate, then assign to avoid saving negative value
		int newPrice = intChecker();
		if(newPrice < 0){
			cout << "Invalid input!\n\n";
			return;
		}
		price[index] = newPrice;
	}
	else if(choice == 6){
		cout << "Enter New Name: ";
		cin.ignore(); cin.getline(modifiedDetail, 50);
		if(strlen(modifiedDetail) < 3){
			cout << "Invalid input!\n\n";
			return;
		}
		strcpy(name[index], modifiedDetail);
		
		cout << "Enter New Brand: ";
		cin.getline(modifiedDetail, 50);
		if(strlen(modifiedDetail) < 2){
			cout << "Invalid input!\n\n";
			return;
		}
		strcpy(brand[index], modifiedDetail);
		
		cout << "Enter New Item: ";
		cin.getline(modifiedDetail, 50);
		if(strlen(modifiedDetail) == 0){
			cout << "Invalid input!\n\n";
			return;
		}
		strcpy(item[index], modifiedDetail);
		
		cout << "Update Quantity: ";
		//* fixed: store in temp first, validate, then assign to avoid saving negative value
		int newQty = intChecker();
		if(newQty < 0){
			cout << "Invalid input!\n\n";
			return;
		}
		quantity[index] = newQty;
		
		cout << "Enter New Price: ";
		//* fixed: store in temp first, validate, then assign to avoid saving negative value
		int newPrice = intChecker();
		if(newPrice < 0){
			cout << "Invalid input!\n\n";
			return;
		}
		price[index] = newPrice;
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
	string str = s; //need to turn into char??? 
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

	//* added: show product details and ask confirmation before deleting
	cout << "\n---------- PRODUCT TO DELETE ----------\n";
	displaySpecificProduct(index);
	char confirm;
	cout << "Are you sure you want to delete this product? [Y / N]: ";
	cin >> confirm;
	if(confirm != 'Y' && confirm != 'y'){
		cout << "Deletion cancelled.\n\n";
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
	//* fixed: added flag so case 6 actually exits the loop
	bool running = true;
	
	do {
		displayMenu();
		choice = intChecker();
		cout <<endl;
		
		switch(choice){
        	case 1: addProduct(); break;
        	case 2: editProduct(); break;
        	case 3: displayProduct(); break;
        	case 4: searchProduct(); break;
        	case 5: deleteProduct(); break;
        	case 6: running = false; break; //* fixed: was just break, loop never exited
        	default: cout << "Invalid choice!\n";
    	}

		//* fixed: only ask return to menu if not exiting
		if(running){
			do {
    			cout << "Return to menu? [Y / N]: ";
    			cin >> answer;
    			if(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
        		cout << "  Invalid input. Please enter Y or N only.\n";
			} while(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n');

			if(answer == 'N' || answer == 'n') running = false; //* fixed: N answer now also exits
		}
		
		system("cls");
	}while(running); //* fixed: was while(true), now respects the flag
	
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
