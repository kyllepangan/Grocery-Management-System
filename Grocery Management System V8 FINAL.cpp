#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<math.h>

//Created by Jedric Amio and Kylle Pangan

using namespace std;
 
class product
{
	int productNumber;
	char productName[50];
	float productPrice,productQuantity,tax,productDiscount,productStock,productSoldItems;
	
	public:
 
	void createProduct()
	{
		cout << endl << "Please Enter The Product Number: ";
		cin >> productNumber;
		cout << endl << "Please Enter The Name of The Product: ";
		cin.ignore();
		cin.getline(productName ,60);
		cout << endl << "Please Enter The Price of The Product: ";
		cin >> productPrice;
		cout << endl << "Please Enter The Discount (%): ";
		cin >> productDiscount;
		
		cout << endl << "Please Enter The Number of Items on Stock: ";
		cin >> productStock;
		cout << endl << "Please Enter The Number of Items Sold: ";
		cin >> productSoldItems;
	}
	
	void retainName(int a)
	{
		productNumber = a;
		/*
		productName = b;
		*/
	}
	
	void alterProductSales(float c, float d, float e, float f)
	{
		productPrice = c;
		productDiscount = d;
		productStock = e;
		productSoldItems = f;
	}
	
	void showProduct()
	{
		cout << endl << "Product No(#): " << productNumber;
		cout << endl << "Product Name: " << productName;
		cout << endl << "Product Price: " << productPrice;
		cout << endl << "Discount %: " << productDiscount;
		cout << endl << "Product Inventory: " << productStock;
		cout << endl << "Items Sold: " << productSoldItems;
		cout << endl << "Profit for Item: " << (productSoldItems * productPrice);
	}
	
	void showProductOOS()
	{
		if(productStock < 1){
			cout << endl << "------------------------------------------------" << endl;
			cout << endl << "Product No(#): " << productNumber;
			cout << endl << "Product Name: " << productName;
			cout << endl << "Product Price: " << productPrice;
			cout << endl << "Discount %: " << productDiscount;
			cout << endl << "Product Inventory: " << productStock;
			cout << endl << "Items Sold: " << productSoldItems;
			cout << endl << "Profit for Item: " << (productSoldItems * productPrice);
			cout << endl << "------------------------------------------------" << endl;
		}
	}
	
	void showProductLOS()
	{
		if(productStock < 11){
			cout << endl << "------------------------------------------------" << endl;
			cout << endl << "Product No(#): " << productNumber;
			cout << endl << "Product Name: " << productName;
			cout << endl << "Product Price: " << productPrice;
			cout << endl << "Discount %: " << productDiscount;
			cout << endl << "Product Inventory: " << productStock;
			cout << endl << "Items Sold: " << productSoldItems;
			cout << endl << "Profit for Item: " << (productSoldItems * productPrice);
			cout << endl << "------------------------------------------------" << endl;
		}
	}
	
	void showProductWSS(int num)
	{
		if(productStock <= num){
			cout << endl << "------------------------------------------------" << endl;
			cout << endl << "Product No(#): " << productNumber;
			cout << endl << "Product Name: " << productName;
			cout << endl << "Product Price: " << productPrice;
			cout << endl << "Discount %: " << productDiscount;
			cout << endl << "Product Inventory: " << productStock;
			cout << endl << "Items Sold: " << productSoldItems;
			cout << endl << "Profit for Item: " << (productSoldItems * productPrice);
			cout << endl << "------------------------------------------------" << endl;
		}
	}
	
	void show_productSales()
	{
		cout << endl << "Product No(#): " << productNumber;
		cout << endl << "Product Name: " << productName;
		cout << endl << "Product Price: " << productPrice;
		cout << endl << "Discount %: " << productDiscount;
		cout << endl << "Product Inventory: " << productStock;
		cout << endl << "Items Sold: " << productSoldItems;
		cout << endl << "Profit for Item: " << (productSoldItems * productPrice);
	}
	
	int getProduct()
	{
		return productNumber;
	}
	
	float getPrice()
	{
		return productPrice;
	}
	
	char* getName()
	{
		return productName;
	}
	
	float getDiscount()
	{
		return productDiscount;
	}
	
	float getStock()
	{
		return productStock;
	}
	
	float getSolditems()
	{
		return productSoldItems;
	}
}; 
 
fstream fp;
product produc;
 
void saveProduct()
{
	fp.open("database.dat",ios::out|ios::app);
	produc.createProduct();
	fp.write((char*)&produc,sizeof(product));
	fp.close();
	cout << endl << endl << "The Product Has Been Sucessfully Created...";
	getchar();
}
 
 
void showAllProducts()
{
	system("cls");
	cout << endl << "\t\t------------------------------------------------------";
	cout << endl << "\t\tRECORDS.";
	cout << endl << "\t\t------------------------------------------------------\n";
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		produc.showProduct();
		cout << endl << "------------------------------------------------------\n"<<endl;
		/*
		getchar();
		*/
	}
	fp.close();
}
 
 
void display_record(int num)
{
	bool found=false;
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getProduct()==num)
		{
			system("cls");
			produc.showProduct();
			found=true;
		}
	}
	
	fp.close();
	if(found == false){
		system("cls");
		cout << endl << endl << "Record of Product " << num << " not Found. :(";
	}
	getchar();
}
 
void editProduct()
{
	int num;
	bool found=false;
	system("cls");
	cout << endl << endl << "\tPlease Enter The Product #: ";
	cin >> num;
	
	fp.open("database.dat",ios::in|ios::out);
	while(fp.read((char*)&produc,sizeof(product)) && found==false)
	{
		if(produc.getProduct()==num)
		{
			produc.showProduct();
			cout << "\n\nPlease Enter The New Details of Product: " << endl;
			produc.createProduct();
			int pos=-1*sizeof(produc);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&produc,sizeof(product));
			cout << endl << endl << "\t Record Successfully Updated. :)";
			found=true;
		}
	}
	fp.close();
	if(found==false){
		cout << endl << endl << "Record Not Found. Sorry. :(";
	}
	getchar();
}
 
 
void deleteProduct()
{
	int num;
	system("cls");
	cout << endl << endl << "Please Enter The product #: ";
	cin >> num;
	fp.open("database.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getProduct()!=num)
		{
			fp2.write((char*)&produc,sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("database.dat");
	rename("Temp.dat","database.dat");
	cout << endl << endl << "\tItem Deleted...";
	getchar();
}

void productMenuSelect(int x)
{
	int a, b, i;
	system("cls");
	
	int num = x;
 	cout << endl << endl;
 	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "------------------------------------------------------" << endl;
	
	cout << endl << "\t\tProduct MENU\n\n";
	cout << "----------------------------------------------------------------------------------\n";
	cout << "P.NO.\t\tNAME                              PRICE\n";
	cout << "----------------------------------------------------------------------------------\n";
		if(num == 1){
			cout << "----------------------------------------------------------------------------------\n";
			cout << "Isle 1: Milk, Coffee, Tea" << endl << endl;
			
			fp.open("database.dat",ios::in);
			while(fp.read((char*)&produc,sizeof(product)))
			{
				if(produc.getProduct() >= 100 && produc.getProduct() <= 199){
				a = strlen(produc.getName());
				b = 35 - a;
				
				cout << produc.getProduct() << "\t\t" << produc.getName();
				for(i = 0; i <= b; i++){
					cout << " ";
				}
				cout << produc.getPrice() << endl;
				}
			}
			fp.close();
			
		}
		
		if(num == 2){
			cout << "------------------------------------------------------" << endl;
			cout << "Isle 2: Plastics and Laundry Products" << endl << endl;
			
			fp.open("database.dat",ios::in);
			while(fp.read((char*)&produc,sizeof(product)))
			{
				if(produc.getProduct() >= 200 && produc.getProduct() <= 299){
					a = strlen(produc.getName());
					b = 35 - a;
					
					cout << produc.getProduct() << "\t\t" << produc.getName();
					for(i = 0; i <= b; i++){
						cout << " ";
					}
					cout << produc.getPrice() << endl;
				}
			}
			fp.close();
			
		}
		
		if(num == 3){
			cout << "------------------------------------------------------" << endl;
			cout << "Isle 3: Beauty Products" << endl << endl;
			
			fp.open("database.dat",ios::in);
			while(fp.read((char*)&produc,sizeof(product)))
			{
				if(produc.getProduct() >= 300 && produc.getProduct() <= 399){
					a = strlen(produc.getName());
					b = 35 - a;
				
					cout << produc.getProduct() << "\t\t" << produc.getName();
					for(i = 0; i <= b; i++){
						cout << " ";
					}
					cout << produc.getPrice() << endl;
				}
			}
			fp.close();
			
		} 
		
		if(num == 4){
			cout << "------------------------------------------------------" << endl;
			cout << "Isle 4: Canned Goods and Oils" << endl << endl;
			
			fp.open("database.dat",ios::in);
			while(fp.read((char*)&produc,sizeof(product)))
			{
				if(produc.getProduct() >= 400 && produc.getProduct() <= 499){
					a = strlen(produc.getName());
					b = 35 - a;
					
					cout << produc.getProduct() << "\t\t" << produc.getName();
					for(i = 0; i <= b; i++){
						cout << " ";
					}
					cout << produc.getPrice() << endl;
					}
			}
			fp.close();
			
		} 
		
		if(num == 5){
			cout << "------------------------------------------------------" << endl;
			cout << "Isle 5: Sandwich-related Products, Noodles, All-Purpose Cream" << endl << endl;
			
			fp.open("database.dat",ios::in);
			while(fp.read((char*)&produc,sizeof(product)))
			{
				if(produc.getProduct() >= 500 && produc.getProduct() <= 599){
					a = strlen(produc.getName());
					b = 35 - a;
				
					cout << produc.getProduct() << "\t\t" << produc.getName();
					for(i = 0; i <= b; i++){
						cout << " ";
					}
					cout << produc.getPrice() << endl;
					}
			}
			fp.close();
			
		} 
		
		if(num == 6){
			cout << "------------------------------------------------------" << endl;
			cout << "Isle 6: Rice, Freezer(Hotdog, Ham, French-Fries, Fish, Easy-To-Cook Foods)" << endl << endl;
			
			fp.open("database.dat",ios::in);
			while(fp.read((char*)&produc,sizeof(product)))
			{
				if(produc.getProduct() >= 600 && produc.getProduct() <= 699){
					a = strlen(produc.getName());
					b = 35 - a;
					
					cout << produc.getProduct() << "\t\t" << produc.getName();
					for(i = 0; i <= b; i++){
						cout << " ";
					}
					cout << produc.getPrice() << endl;
				}
			}
			fp.close();
			
		} 
		
		if(num == 7){
			cout << "------------------------------------------------------" << endl;
			cout << "Isle 7: Pork and Beef" << endl << endl;
			
			fp.open("database.dat",ios::in);
			while(fp.read((char*)&produc,sizeof(product)))
			{
				if(produc.getProduct() >= 700 && produc.getProduct() <= 799){
					a = strlen(produc.getName());
					b = 35 - a;
					
					cout << produc.getProduct() << "\t\t" << produc.getName();
					for(i = 0; i <= b; i++){
						cout << " ";
					}
					cout << produc.getPrice() << endl;
				}
			}
			fp.close();
			
		} 
		
		if(num == 8){
			cout << "------------------------------------------------------" << endl;
			cout << "Isle 8: Chicken" << endl << endl;
			
			fp.open("database.dat",ios::in);
			while(fp.read((char*)&produc,sizeof(product)))
			{
				if(produc.getProduct() >= 800 && produc.getProduct() <= 899){
					a = strlen(produc.getName());
					b = 35 - a;
					
					cout << produc.getProduct() << "\t\t" << produc.getName();
					for(i = 0; i <= b; i++){
						cout << " ";
					}
					cout << produc.getPrice() << endl;
				}
			}
			fp.close();
			
		} 
		
		if(num == 9){
			cout << "------------------------------------------------------" << endl;
			cout << "Isle 9: Vegetables, Egg, Pepper, Sugar and Salt" << endl << endl;
			
			fp.open("database.dat",ios::in);
			while(fp.read((char*)&produc,sizeof(product)))
			{
				if(produc.getProduct() >= 900 && produc.getProduct() <= 999){
					a = strlen(produc.getName());
					b = 35 - a;
					
					cout << produc.getProduct() << "\t\t" << produc.getName();
					for(i = 0; i <= b; i++){
						cout << " ";
					}
					cout << produc.getPrice() << endl;
					}
			}
			fp.close();
			
		}
		
		if (num <= 0 || num >= 10 ) {
			cout << "Invalid input. " << endl;
		}
		
	
	if(num >= 1 || num <= 9){
	cout << "===========================================================" << endl;
	}
}

 
 
 
void placeOrder()
{
	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	float vat = 0;
	float nonvat = 0;
	float paymentAmount = 0;
	float change;
	float loyaltyPts = 0;
	float totalQuantity = 0;
	int num, a, b;
	
	char temp;
	char name[30];
	char loyaltyID[20];
	
	char ch='Y';
	
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "---------------------------------------------------------------------------" << endl;
	cout << "\nWelcome to the Supermarket. Happy Shopping" << endl << endl;
	
			
	printf("Enter Customer Name: ");
	scanf("%c",&temp);
	scanf("%[^\n]s", &name);

			        
	printf("Enter Customer Loyalty Number: ");
	scanf("%c",&temp);
	scanf("%[^\n]s", &loyaltyID);
			
	cout << endl;
	
	cout<<"\n------------------------------------------------";
	cout<<"\n PLACE YOUR ORDER";
	cout<<"\n------------------------------------------------\n";
	do{
		system("cls");
			
			bool menuSelect;
			
			do{
				menuSelect = false;
				
				cout<<"\n------------------------------------------------";
				cout<<"\n CHOOSE THE ISLE WHERE YOU WILL GO TO";
				cout<<"\n------------------------------------------------\n";
				cout << "\nIsle 1: Milk, Coffee, Tea" << endl;
				cout << "Isle 2: Plastics and Laundry Products" << endl;
				cout << "Isle 3: Beauty (Soap, Shampoo, Alcohol, Facial Wash, Toothpaste)" << endl;
				cout << "Isle 4: Canned Goods, Oils" << endl;
				cout << "Isle 5: Bread, Noodles, All-Purpose Creams, Cheese, Spreads" << endl;
				cout << "Isle 6: Rice, Hotdog, Ham, French Fries, Easy-Cook Foods, Fish" << endl;
				cout << "Isle 7: Pork and Beef" << endl;
				cout << "Isle 8: Chicken" << endl;
				cout << "Isle 9: Vegetables, Egg, Sugar and Salt, Pepper" << endl;
				
				cout << "\nEnter Isle that you want to view: ";
				cin >> num;
				
				if(num >= 1 && num <= 9){
					menuSelect = true;
				} 
				
				system("cls");
				productMenuSelect(num);
				
				if(menuSelect == false){
					system("cls");
					cout << endl << "Invalid choice. Choose isle again.";
				}
				
				cout << endl << endl;
			} while (menuSelect == false);
			
			cout << endl;
			
			
			bool prodNum;
			
			do{		
				cout << "Enter The Product #: ";
				cin >> order_arr[c];
				
				a = num * 100;
				b = a + 99;
				
				prodNum = false;
				fp.open("database.dat",ios::in);
				while(fp.read((char*)&produc,sizeof(product)))
				{
					if((order_arr[c] >= a) && (order_arr[c] <= b)){
						if(produc.getProduct()==order_arr[c])
						{
							if(produc.getStock() > 0)
							{
								prodNum=true;
							}
						}
					}
				}
				
				fp.close();
				if(prodNum == false) {
					
					if(produc.getStock() <= 0){
						system("cls");
						productMenuSelect(num);
						cout << endl<< "Product " << order_arr[c] << " is out of stock. Please type again" << endl << endl;
						
					} else if((order_arr[c] < a) && (order_arr[c] >= b)){
						system("cls");
						productMenuSelect(num);
						cout << endl<< "Product " << order_arr[c] << " is not in the list of choices. Please type again" << endl << endl;
						
					} else {
						system("cls");
						productMenuSelect(num);
						cout << endl<< "Product " << order_arr[c] << " not available. Please type again" << endl << endl;
						
					}
				}
			} while (prodNum == false);
			
			bool quantityNum;
			float r;
			
			do{
				quantityNum = false;
				
				cout << "\nQuantity: ";
				cin >> quan[c];
				
				
				r = produc.getStock() - quan[c];
				if(r >= 0 && produc.getStock() > 0) {
						if(quan[c] >= 1){
							quantityNum = true;
						} else {
							quantityNum = false;
						}
					}
				
				if(quantityNum == false){
						if(quan[c] <= 0){
							cout << endl << "Please enter proper quantity." << endl;
						}
						
						if(r < 0){
							cout << endl << "Not enough stock. Only " << produc.getStock() << " items left. Sorry." << endl;
						}
				}
				
			} while (quantityNum == false);
			
		c++;
		cout<<"\nDo You Want To Order Another Product ? (y/n) ";
		cin>>ch;
		}while(ch=='y' ||ch=='Y');
	
	float n, o, p, q, s;
	
	for(int x=0;x<=c;x++)
	{
		fp.open("database.dat",ios::in|ios::out);
		fp.read((char*)&produc,sizeof(product));
		while(!fp.eof())
		{	
			if(produc.getProduct()==order_arr[x])
			{
				if((produc.getStock() - quan[x]) < 0){
					s = quan[x] - (-1 * (produc.getStock() - quan[x]));
					quan[x] = s;
				}
				
				amt=produc.getPrice()*quan[x];
				damt=amt-(amt*produc.getDiscount()/100);
				
				if(quan[x] > 0){
					cout << "\n" << order_arr[x] << "\t" << produc.getName() << "\t" << quan[x] << "\t\t" << produc.getPrice() << "\t" << amt << "\t\t" << damt;
				}
				total = (total + damt);
				totalQuantity = totalQuantity + quan[x];
				
				n = produc.getPrice();
				o = produc.getDiscount();
				p = produc.getStock() - quan[x];
				q = produc.getSolditems() + quan[x];
				
				produc.alterProductSales(n, o, p, q);
				int pos=-1*sizeof(produc);
				fp.seekp(pos,ios::cur);
				fp.write((char*)&produc,sizeof(product));
			}
			fp.read((char*)&produc,sizeof(product));
		}
		fp.close();
	}	
	
	getchar();
	
	int i, l, m;
	
	system("cls");
	cout << "\n\n********************************INVOICE********************************\n";
	cout << endl << "\t\t\tCustomer Name: " << name << endl;
	cout << "\t\t\tCustomer Loyalty ID: " << loyaltyID << endl;
	cout << "\nPr No.\tPr Name                        Quantity\t\tPrice/Pc(s) \tAmount \n";
	for(int x=0;x<=c;x++)
	{
		fp.open("database.dat",ios::in);
		fp.read((char*)&produc,sizeof(product));
		while(!fp.eof())
		{	
			if(produc.getProduct()==order_arr[x])
			{
				amt=produc.getPrice()*quan[x];
				damt=amt-(amt*produc.getDiscount()/100);
				if(quan[x] > 0){
					cout << "\n" << order_arr[x] << "\t" << produc.getName();
					l = strlen(produc.getName());
					m = 30 - l;
					for(i = 0; i <= m; i++){
						cout << " ";
					}
					cout << quan[x] << "\t\t" << produc.getPrice() << "\t\t" << amt;
				}
				total=total;
				totalQuantity=totalQuantity;
			}
			fp.read((char*)&produc,sizeof(product));
		}
		fp.close();
	}
	
	nonvat = total * 0.88;
	vat = total * 0.12;
	loyaltyPts = total * 0.10;
	
	cout << "\n\n\t\t\t\t\tNON-VATABLE AMOUNT = " << nonvat;
	cout << "\n\n\t\t\t\t\tVAT = " << vat;
	cout << "\n\n\t\t\t\t\tTOTAL ITEM QUANTITY = " << totalQuantity;
	cout << "\n\n\t\t\t\t\tTOTAL PRICE = " << total;
	
	do{
		printf("\n\n\t\t\t\t\tHow much is the cash payment: ");
		scanf("%f", &paymentAmount);

		change = paymentAmount - total;
	    if(paymentAmount < total){
			cout << "\n\n\t\t\t\t\tPayment incomplete. Please pay exact or more than the total price." << endl << endl;
		}
	}while(paymentAmount < total);
	
	
	system("cls");
	cout << "\n\n********************************FINAL RECEIPT**********************************\n";
	cout << endl << "\t\t\tCustomer Name: " << name << endl;
	cout << "\t\t\tCustomer Loyalty ID: " << loyaltyID << endl;
	cout << "\nPr No.\tPr Name                        Quantity\t\tPrice \t\tAmount \n";
	
	
	ofstream singlereceipt;
	singlereceipt.open("SingleReceipt.txt",ios::out);
	
	ofstream appReceipt;
	appReceipt.open("CollectedReceipts.txt",ios::app);
	
	appReceipt << "----------------------------------------------------------------------------" << endl;
	singlereceipt << "----------------------------------------------------------------------------" << endl;
			
	singlereceipt << "Put Grocery Name Here Grocery Store" << endl;
	singlereceipt << "Put address here. " << endl;
	singlereceipt << "Contact Number: 09123456789" << endl << endl;
			
	appReceipt << "Put Grocery Name Here Grocery Store" << endl;
	appReceipt << "Put address here. " << endl;
	appReceipt << "Contact Number: 09123456789" << endl << endl;
	
	singlereceipt << "Customer Name: "<< name << endl;
	appReceipt << "Customer Name: "<< name << endl;
	
	singlereceipt << "Customer Loyalty Number: " << loyaltyID << endl;
	appReceipt << "Customer Loyalty Number: " << loyaltyID << endl;
	
	singlereceipt.close();
	appReceipt.close();
	
	
	for(int x=0;x<=c;x++)
	{
		fp.open("database.dat",ios::in);
		fp.read((char*)&produc,sizeof(product));
		while(!fp.eof())
		{	
			if(produc.getProduct()==order_arr[x])
			{
				singlereceipt.open("SingleReceipt.txt",ios::app);
				appReceipt.open("CollectedReceipts.txt",ios::app);
				
				amt=produc.getPrice()*quan[x];
				damt=amt-(amt*produc.getDiscount()/100);
				
				if(quan[x] > 0){
					cout << "\n" << order_arr[x] << "\t" << produc.getName();
					l = strlen(produc.getName());
					m = 30 - l;
					for(i = 0; i <= m; i++){
						cout << " ";
					}
					cout << quan[x] << " \t\t" << produc.getPrice() << "\t\t" << amt;
					
					
					singlereceipt << endl;
					singlereceipt << order_arr[x] << "			" << produc.getName() << endl;
					singlereceipt << "Quantity: " << quan[x] << " pcs" << endl;
					singlereceipt << "Price (/pc): " << produc.getPrice() << endl;
					singlereceipt << "Total Price: " << amt << endl;
					
					appReceipt << endl;
					appReceipt << order_arr[x] << "			" << produc.getName() << endl;
					appReceipt << "Quantity: " << quan[x] << " pcs" << endl;
					appReceipt << "Price (/pc): " << produc.getPrice() << endl;
					appReceipt << "Total Price: " << amt << endl;
				}
				
				total=total;
				singlereceipt.close();
				appReceipt.close();
			}
			fp.read((char*)&produc,sizeof(product));
		}
		fp.close();
	}
	
	cout << "\n\n\t\t\t\t\tVAT = " << vat;
	cout << "\n\n\t\t\t\t\tTOTAL ITEM QUANTITY = " << totalQuantity;
	cout << "\n\n\t\t\t\t\tTOTAL PRICE = " << total;
	cout << "\n\n\t\t\t\t\tAmount Paid: " << paymentAmount;
	if (paymentAmount > total){
		cout << "\n\n\t\t\t\t\tYour change is: " << change << endl;
	}
	else if(paymentAmount = total){
		cout << "\n\n\t\t\t\t\tThank you for paying exact amount" << endl;
	}
	cout << "\n\n\t\t\t\t\tThank you for shopping at the grocery. Stay safe. " << endl << endl;
	
	singlereceipt.open("SingleReceipt.txt",ios::app);
	appReceipt.open("CollectedReceipts.txt",ios::app);
	
	singlereceipt << endl << "Potential Loyalty Points: " << loyaltyPts << endl;
	singlereceipt << "NON VATABLE AMOUNT: " << nonvat << endl;
	singlereceipt << "12% VAT: " << vat << endl;
	singlereceipt << "TOTAL: " << total << endl;
	singlereceipt << "TOTAL ITEM QUANTITY: " << totalQuantity << endl;
	singlereceipt << "Amount Paid: " << paymentAmount << endl;
	singlereceipt << "Change: " << change << endl;
	singlereceipt << "--------------------------------------------------" << endl;
	
	appReceipt << endl << "Potential Loyalty Points: " << loyaltyPts << endl;
	appReceipt << "NON VATABLE AMOUNT: " << nonvat << endl;
	appReceipt << "VAT: " << vat << endl;
	appReceipt << "TOTAL: " << total << endl;
	appReceipt << "TOTAL ITEM QUANTITY: " << totalQuantity << endl;
	appReceipt << "Amount Paid: " << paymentAmount << endl;
	appReceipt << "Change: " << change << endl;
	appReceipt << "-----------------------------------------------------" << endl;
	
	singlereceipt.close();
	appReceipt.close();
	
	getchar();
}

void showStocksWS()
{
	system("cls");
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "\t------------------------------------------------";
	cout << "\n\tShowing Product List with inventory";
	
	cout << endl << "\n\t------------------------------------------------------";
	cout << endl << "\tRECORDS.";
	cout << endl << "\t------------------------------------------------------\n";
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		produc.showProduct();
		cout << endl << "------------------------------------------------------\n"<<endl;
		/*
		getchar();
		*/
	}
	fp.close();
	
	getchar();
}

void showStocksWOS()
{
	system("cls");
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "\t------------------------------------------------";
	cout << "\n\tShowing list of items without stocks";
	
	cout << endl << "\n------------------------------------------------------";
	cout << endl << "\t\tRECORDS.";
	cout << endl << "------------------------------------------------------\n";
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		produc.showProductOOS();
	}
	fp.close();
	cout << endl;
	
	getchar();
}

void showStocksWLS()
{
	system("cls");
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "\t------------------------------------------------";
	cout << "\n\tShowing list of items with low stocks";
	
	cout << endl << "\n\t------------------------------------------------------";
	cout << endl << "\tRECORDS.";
	cout << endl << "\t------------------------------------------------------\n";
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		produc.showProductLOS();
	}
	fp.close();
	cout << endl;
	
	getchar();
}

void showSales(int num)
{
	system("cls");
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "------------------------------------------------";
	cout << "\n\tSearching for product data for product " << num << endl;
	cout << "------------------------------------------------" << endl;
	
	bool found=false;
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getProduct()==num)
		{
			system("cls");
			produc.show_productSales();
			found=true;
		}
	}
	
	fp.close();
	if(found == false){
		system("cls");
		cout << endl << endl << "Record of Product " << num << " not Found... :";
	}

	getchar();
}

void showStocksWSS()
{
	int x;
	system("cls");
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "\t------------------------------------------------";
	
	cout << endl << "\tPlease Enter The # of stocks: ";
	cin >> x;
	
	cout << "\t------------------------------------------------";
	cout << "\n\tShowing list of items with " << x << " stocks";
	cout << endl << "\n\t\------------------------------------------------------";
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		produc.showProductWSS(x);
	}
	fp.close();
	cout << endl;
	
	getchar();
}

void stocks()
{
	int option; 
	system("cls");
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "\t------------------------------------------------";
	cout << "\n        STOCKS" << endl;
	cout << "\t------------------------------------------------";
	cout << "\n\t1: SHOW PRODUCT LIST WITH STOCKS";
	cout << "\n\t2: SHOW ITEMS WITHOUT STOCKS";
	cout << "\n\t3: SHOW ITEMS WITH LOW OR NO STOCKS";
	cout << "\n\t4: SHOW ITEMS WITH USER-DEFINED STOCKS OR LESS";
	cout << "\n\t5: GO BACK TO MAIN MENU";
	cout << "\n\t------------------------------------------------";
 
	cout << "\n\n\tChoose Your Option: ";
	cin >> option;
	switch(option)
	{
		case 1: 
				system("cls");
				showStocksWS();
				break;
				
		case 2: system("cls");
				showStocksWOS();
				break;
				
		case 3:	system("cls");
				showStocksWLS();
				break;
		
		case 4:	system("cls");
				showStocksWSS();
				break;
				
		case 5: system("cls");
				break;
		
		default:stocks();
	}
}

void showSalesMin(int num)
{
	system("cls");
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "------------------------------------------------";
	cout << "\n\tSALES MORE THAN PHP " << num << endl;
	cout << "------------------------------------------------" << endl;
	
	int b;
	
	bool found=false;
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		b = produc.getSolditems() * produc.getPrice();
		if(b >= num)
		{
			produc.show_productSales();
			cout << endl;
			found=true;
		}
	}
	
	fp.close();
	if(found == false){
		system("cls");
		cout << endl << endl << "No sales above Php " << num;
	}

	getchar();
}

void sales()
{
	system("cls");
	int option;
	char ch;
	
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "\t------------------------------------------------";
	cout << "\n        SALES" << endl;
	cout << "\t------------------------------------------------";
	cout << "\n\t1: DISPLAY SALES OF ONE PRODUCT";
	cout << "\n\t2: DISPLAY SALES WITH MINIMUM SALE VALUE";
	cout << "\n\t3: GO BACK TO MENU ";
	cout << "\n\t------------------------------------------------";
 
	cout << "\n\n\tChoose Your Option: ";
	cin >> option;
	switch(option)
	{
		case 1: int numSales;
				system("cls");
				do{
					cout<<"\n\n\tPlease Enter The Product Number: ";
					cin>>numSales;
					showSales(numSales);
					printf ("\nWill you pick something else?: (Y/N) ");
					scanf (" %c", &ch);
					system("cls");
				} while (ch == 'y' || ch == 'Y');
				break;
				
		case 2: int numSalesMin;
				system("cls");
				do{
					cout<<"\n\n\tPlease Enter The Minimum Number: ";
					cin>>numSales;
					showSalesMin(numSales);
					printf ("\nWill you pick another value?: (Y/N) ");
					scanf (" %c", &ch);
					system("cls");
				} while (ch == 'y' || ch == 'Y');
				break;
				
		case 3:
				system("cls");
				break;
		
		default:sales();
	}
}

void adminMenu()
{
	system("cls");
	int option;
	char ch;
	
	do{
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl; 
	cout << "\t------------------------------------------------";
	cout << "\n        ADMIN SIDE" << endl;
	cout << "\t------------------------------------------------";
	cout << "\n\t1: CREATE/ADD PRODUCT TO DATABASE";
	cout << "\n\t2: DISPLAY ALL PRODUCTS";
	cout << "\n\t3: SEARCH ";
	cout << "\n\t4: MODIFY PRODUCT";
	cout << "\n\t5: DELETE PRODUCT FROM DATABASE";
	cout << "\n\t6: INVENTORY";
	cout << "\n\t7: SALES";
	cout << "\n\t8: GO BACK TO MAIN MENU";
	cout << "\n\t------------------------------------------------";
	
	cout << "\n\n\tChoose Your Option: ";
	cin >> option;
	switch(option)
	{
		case 1: system("cls");
				do{
				saveProduct();
				printf ("\nWill you add something else?: (Y/N) ");
				scanf (" %c", &ch);
				system("cls");
				} while (ch == 'y' || ch == 'Y');
				break;
				
		case 2: showAllProducts();
				break;
				
		case 3:
				int num;
				system("cls");
				do{
				cout<<"\n\n\tPlease Enter The Product Number: ";
				cin >> num;
				display_record(num);
				printf ("\nWill you pick something else?: (Y/N) ");
				scanf (" %c", &ch);
				system("cls");
				} while (ch == 'y' || ch == 'Y');
				break;
				
		case 4: do{
				editProduct();
				printf ("\nWill you edit another product?: (Y/N) ");
				scanf (" %c", &ch);
				system("cls");
				} while (ch == 'y' || ch == 'Y');
				break;
		
		case 5: do{
					deleteProduct();
				printf ("\nWill you pick something else?: (Y/N) ");
				scanf (" %c", &ch);
				system("cls");
				} while (ch == 'y' || ch == 'Y');
		        break;
		
		case 6: stocks();
		        break;
		
		case 7: 
				sales();
				break;
				
		case 8: system("cls");
				break;
		
		default:adminMenu();
	}
	printf ("Continue in admin?: (Y/N) ");
	scanf (" %c", &ch);
	system("cls");
	} while (ch == 'y' || ch == 'Y');
	system("cls");
}

void adminLogin(){
	system("cls");
	string uName1 = "jedAmio";
	string uName2 = "kylleP30";
	string password = "abcd1234";
	string username2, password2;
	
	cout << "       --" << endl;
	cout << "         \\ " << endl;
	cout << "          \\_______________________" << endl;
	cout << "           \\_____________________/" << endl;
	cout << "            \\___________________/" << endl;
	cout << "             \\_________________/" << endl;
	cout << "              \\_______________/" << endl;
	cout << "                \O----------O" << endl << endl;
	cout << "\t--------------------------------------------------------" << endl;
	cout << "\tADMIN LOGIN" << endl; 
	cout << "\t--------------------------------------------------------" << endl << endl;
		
		cout << "Please enter your credentials below. No spaces allowed." << endl << endl;
		
		cout << "Enter Username: \n";
        cin >> username2;
        
        cout << endl;
		
		cout << "Enter password: \n";
    	cin >> password2;
    	
    	cout << endl << endl;

	if(username2 == uName1 || username2 == uName2){
		if(password2 == password){
			cout << endl <<"Welcome to the program " << username2 << "." << endl << endl;
			adminMenu();
		} 
		else if (password2 != password) {
			cout << endl << "Incorrect username or password." << endl << endl;
			adminLogin();
		}
		else
	    {
	        cout << "Unknown Error!";
	        cout << endl << endl;
	        adminLogin();
	    }
	}
	else {
		cout << endl << "Username or Password is incorrect. Please try again" << endl;
		adminLogin();
	}
}
 
int main(int argc, char *argv[])
{
	system("cls");
	system("color 00");
	
	int option;
	
	for(;;)
	{
		system("cls");
 		cout << "       --" << endl;
	  	cout << "         \\ " << endl;
	   	cout << "          \\_______________________" << endl;
	   	cout << "           \\_____________________/" << endl;
	   	cout << "            \\___________________/" << endl;
	    cout << "             \\_________________/" << endl;
	   	cout << "              \\_______________/" << endl;
	   	cout << "                \O----------O" << endl << endl; 
		cout << "              Welcome to our Grocery Management System" << endl;
		cout << "        Created by Jedric Neal Amio and Avram Kylle Pangan." << endl;
		cout << "                          Happy Shopping!" << endl << endl << endl;
		cout << "\n\t------------------------------------------------";
		cout << "\n\t1: CASHIER";
		cout << "\n\t2: ADMIN ACCESS";
		cout << "\n\t3: EXIT";
		cout << "\n\t------------------------------------------------";
		
		cout << "\n\tOption: ";
		cin >> option;
		
		switch(option)
		{
			case 1: system("cls");
					placeOrder();
					getchar();
					break;
					
			case 2: adminLogin();
					break;
					
			case 3: 
					cout << "\n\t------------------------------------------------";
					cout << "\n\tThanks for using this program! Stay safe and have a great day.";
					cout << "\n\t------------------------------------------------\n";
					exit(0);
			
			default :cout<<"Invalid Input. :(\n";
		}
	}
}
