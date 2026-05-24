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

void addProduct(){
	string newcode;
	cout << "Product code: ";
	cin >> newcode;	
	//check if code is unique
	for(int i = 0; i < count; i++){
		if (newcode == code[i]){
			cout << "Code already exist.\n\n";
			return;
		}
	}
	
	code[count] = newcode; //store the code if its unique
	
	cout << "Name of product: ";
	cin >> name[count];
	cout << "Brand: ";
	cin >> brand[count];
	cout << "Item: ";
	cin >> item[count];
	cout << "Quantity: ";
	cin >> quantity[count];
	cout << "Price: ";
	cin >> price[count];
	
	cout << "Product added.\n\n";
	count++;
}

void editProduct(){
	string editcode, modifiedCode;
	cout << "Product code to edit: ";
	cin >> editcode;
	
	int index = productIndex(code, count, editcode); //get the index to access the searched code
	cout << "Edit code: " << code[index] << " / ";
	cin >> modifiedCode;
	code[index] = modifiedCode; //replace the old code
	
	cout <<endl;
	//to be continued (what design??)
	
}

//display all products
void displayProduct(){
	
	if(count == 0){
		cout << "No product.\n\n";
	}
	for(int i = 0; i < count; i++){
		cout << "Product code: " << code[i] << endl;
		cout << "Product name: " << name[i] << endl;
		cout << "Product brand: " << brand[i] << endl;
		cout << "Item: " << item[i] << endl;
		cout << "Quantity: " << quantity[i] << endl;
		cout << "Price: " << price[i] << endl;	
		cout << endl;
	}
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
	//display the search product
	cout << "Product code: " << code[i] << endl;
	cout << "Product name: " << name[i] << endl;
	cout << "Product brand: " << brand[i] << endl;
	cout << "Item: " << item[i] << endl;
	cout << "Quantity: " << quantity[i] << endl;
	cout << "Price: " << price[i] << endl;	
	cout << endl;
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


int main(){
	int choice;
	string answer;
	cout << "Boutique System\n";
	
	do {
		cout << "1. Add Product\n2. Edit Product\n3. Display All Products\n4. Search a Products\n5. Delete Product\n6. Exit\n";
		cout << "Enter choice: ";
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
