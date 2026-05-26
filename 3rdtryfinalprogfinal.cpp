#include <iostream>
#include <cstring>
using namespace std;

string code[100];
string name[100];
string brand[100];
string item[100];
int quantity[100];
int price[100];

static int count = 0; //to store in the array by incrementing index

//search product and return its index for easy access and reusability
int productIndex(string code[], int count, string searchCode){
	for(int i = 0; i < count; i++){
		if(code[i] == searchCode){
			return i; // this returns the index
		}
	}
	return -1; //returns -1 if it does not exist
}

void displaySpecificProduct(int i){
	//display the search product
	cout << "Code      : " << code[i] << endl;
	cout << "Name      : " << name[i] << endl;
	cout << "Brand     : " << brand[i] << endl;
	cout << "Item      : " << item[i] << endl;
	cout << "Quantity  : " << quantity[i] << endl;
	cout << "Price     : " << price[i] << endl;	
	cout << endl;
}

//code based on product name, brand
string productCode(string name, string brand, string item){
	string code = "";
	string binary = "";	
	
	for(int i = 0; i < 2; i++){
		code += brand[i];
	}
	code += "-";
		for(int i = 0; i< 2; i++){
		code += name[i];
	}
	
	int itemNum = count + 1;
	
	while(itemNum > 0){
		int remainder = itemNum % 2;
		if (remainder != 0){
			binary = "1" + binary;
		}
		else {
			binary = "0" + binary;
		}
		itemNum /= 2;
	}
	code += binary;
		
	return code;
}

void addProduct(){

	//check if product is unique
	cout << "---------- ADD PRODUCT DETAIL ----------\n";
	cout << "Name      : "; cin >> name[count];
	cout << "Brand     : ";	cin >> brand[count];
	cout << "Item      : "; cin >> item[count];
	cout << "Quantity  : "; cin >> quantity[count];
	cout << "Price     : "; cin >> price[count];
	
	code[count] = productCode(name[count], brand[count], item[count]);
	
	cout << "Code      : " << code[count] << endl;
	cout << "Product added\n\n"; //changename
	count++;
}

void editProduct(){
	string editcode, modifiedDetail;
	int choice, modifiedDetailnum;
	cout << "---------- EDIT PRODUCT ----------\n";
	cout << "Enter product code to edit: ";
	cin >> editcode;
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
		cin >> modifiedDetail;
		name[index] = modifiedDetail;
	}
	else if(choice == 2){
		cout << "Enter New Brand: ";
		cin >> modifiedDetail;
		brand[index] = modifiedDetail;
	}
	else if(choice == 3){
		cout << "Enter New Item: ";
		cin >> modifiedDetail;
		item[index] = modifiedDetail;
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
		cin >> modifiedDetail;
		name[index] = modifiedDetail;
		
		cout << "Enter New Brand: ";
		cin >> modifiedDetail;
		brand[index] = modifiedDetail;
		
		cout << "Enter New Item: ";
		cin >> modifiedDetail;
		item[index] = modifiedDetail;
		
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
	
	cout << "Updated Successfully!\n\n";

	
}

//display all products
void displayProduct(){
	
	if(count == 0){
		cout << "----- BOUTIQUE INVENTORY IS EMPTY -----";
	}
	
	cout <<"============================================================\n";
	cout <<"|                   P R O D U C T   L I S T                |\n";
	cout <<"============================================================\n\n";
	
	string displayedItems[100];
	int displayedcount = 0;
	
	
	for(int i = 0; i < count; i++){
		string currentItem = item[i];
		
		bool alreadyDisplayed = false;
		
		if(int j = 0 ; j < displaycount; j++){
			if(displayedItems[i] == currentItem) {
				alreadyDisplayed = true;
				break
			}
		}
		
		if(!alreadyDisplayed) {
			cout << "\n                    [ ITEM: "<< currentItem << " ]                    \n";
			cout << "-----------------------------------------------------------------\n";
			cout << "| CODE     | NAME               | BRAND     | QTY   | PRICE     |\n";
			cout << "-----------------------------------------------------------------\n";
			
			for(int a = 0; a < count; a++){
				cout << "| " << code[a] << "\t  | " 
						 << name[a] << "\t\t | " 
						 << brand[a] << "\t      | " 
						 << quantity[a] << "\t      | Php " 
						 << price[a] << "     |\n";
			}
			
			cout << "-----------------------------------------------------------------\n";
		}
		
		displayedItems[displayedcount] = currentItem;
		displayedcount++;
	}
	cout << "-----------------------------------------------------------------\n";
}


void searchProduct(){
	string searchProduct;
	cout << "Product code to search: ";
	cin >> searchProduct;
	
	int i = productIndex(code, count, searchProduct); //use product index again
	
	if(i == -1){
		cout << "Product not found.\n\n";
		return;
	}
	
	displaySpecificProduct(i);
}

void deleteProduct(){
	string remove;
	cout << "Code of product to delete: ";
	cin >> remove;

	int index = productIndex(code, count, remove); //index of product to be deleted
	
	if(index == -1){
		cout << "Product not found.\n\n";
		return;
	}
	
	//removes the product by changine the index of the rest (example: index 2 will be removed and index 3 will be the new index 2) 
	for(int i = index; i < count - 1; i++){	
		code[i] = code[i + 1];
		name[i] = name[i + 1];
		brand[i] = brand[i + 1];
		item[i] = item[i + 1];
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
	cout << "|  [1] Name for addproduct              |\n";
	cout << "|  [2] Name for aditproduct             |\n";
	cout << "|  [3] Name for viewproduct             |\n";
	cout << "|  [4] Name for searchproduct           |\n";
	cout << "|  [5] Name for deleteproduct           |\n";
	cout << "|  [6] Name for exiting program         |\n";
	cout << "=========================================\n";
	cout << "Name for answer selection: ";
}

int main(){
	int choice;
	string answer;
	cout << "Boutique System\n";
	
	do {
		displayMenu();
		cin >> choice;
		cout <<endl;
		
		if(choice == 1){
			addProduct();
		}
		if(choice == 2){
			editProduct();
		}
		if(choice == 3){
			displayProduct();
		}
		if(choice == 4){
			searchProduct();
		}
		if(choice == 5){
			deleteProduct();
		}
		if(choice == 6){
			break;
		}
		//for instruction number 5
		cout << "Display menu again? [yes / no]: ";
		cin >> answer;
		if(answer == "no"){
			cout<< "Ending program...";
			return 0;
		}
		cout << endl;
		
	}while(choice > 0);
	
	cout << "Exiting Program...";
	
	return 0;
}

	/* todo:
	design user interface
	apply topics discussed / replace code if topic applies
	edit product design
	try to put parameters in void functions
	
	responds to possible user input errors
	
	check readability
	structural design
	efficiency
	*/
	
