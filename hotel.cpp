#include <iostream>
#include <string>

using namespace std;
//declaring new type costumer
struct Costumer{
	string firstName;
	string middleName;
	string lastName;
	string phoneNumber;
	string address;
	string nationalID;
};

//declaring new type room
struct Room{
	string Number;
	string Type;
	string amountCostPerhour;
};

//declaring new type for the reserved room
struct ReservedRoom{
	string Number;
	string CostumerID;
};

Costumer costumersList[10007];
Room roomsList[10007];
ReservedRoom reservedRoomList[10007];
int costumersListSize = 0, roomsListSize = 0, reservedRoomsListSize = 0;


// to check if a room with a certain number exist in the rooms List
bool checkRoomExist(string roomNumber){
	for (int i = 0; i < roomsListSize; i++){
		if (roomsList[i].Number == roomNumber)
			return true;
	}
	return false;
}


// to check if a room with a certain number exist in the reserved rooms List
// return index of the room if not available and -1 if available
int checkRoomReserved(string roomNumber){
	for (int i = 0; i < reservedRoomsListSize; i++){
		if (reservedRoomList[i].Number == roomNumber)
			return i;
	}
	return -1;
}


// to check if a certain costumer has reservation or not
// return first index of the reserved room if he has a reservation
// and -1 if he has not
int checkCostumerReservationHistory(string CID){
	for (int i = 0; i < reservedRoomsListSize; i++){
		if (reservedRoomList[i].CostumerID == CID)
			return i;
	}
	return -1;
}


// to check if a certain costumer exist in the costumers list
bool checkCustomerExist(string CID){
	for (int i = 0; i < costumersListSize; i++){
		if (costumersList[i].nationalID == CID)
			return true;
	}
	return false;
}


// to check the input if it's a number
// if not a number repeat until it's a number
string repeatIfNotNumber(string beforeEntring, bool checkPhone){
	string noteNotNumber = "Please Enter only Numbers\n";
	string text;
	bool condition = true;
	while (condition)
	{
		cout << beforeEntring;
		cin >> text;
		bool isNumber = true;
		for (int i = 0; i < text.size(); i++){
			if (text[i] > '9' || text[i] < '0'){
				isNumber = false;
				break;
			}
		}
		if (checkPhone){
			/*
			if(text.size() != 10){
			cout<<"Please Enter a 10 Digit number"<<endl;
			continue;
			}
			*/
		}
		condition = !isNumber;
		if (!condition)
			continue;
		cout << noteNotNumber;
	}
	return text;
}


// adding new Costumer details and insert him into customer list
// if the national Id of the inserted costumer is already existed in the list
// asked for another national Id
void addNewCostumer(){
	Costumer newCostomer;
	cout << "Enter new Costumer Details...." << endl;

	cout << "First Name: ";
	cin >> newCostomer.firstName;

	cout << "Middle Name: ";
	cin >> newCostomer.middleName;

	cout << "Last Name: ";
	cin >> newCostomer.lastName;

	newCostomer.phoneNumber =
		repeatIfNotNumber("Phone Number: ", true);

	cout << "Address: ";
	cin.ignore();
	getline(cin, newCostomer.address);

	newCostomer.nationalID =
		repeatIfNotNumber("National ID: ", false);
	while (checkCustomerExist(newCostomer.nationalID)){
		cout << "this ID is taken try Another One:" << endl;
		newCostomer.nationalID =
			repeatIfNotNumber("National ID: ", false);
	}
	// adding the inserted costumer to the costumers List
	costumersList[costumersListSize] = newCostomer;
	costumersListSize++;

	cout << "New Costumer Added Successfully." << endl;
}


// adding new room details and insert it into room List
// if the inserted room number is already exist in the room list
// ask for another room number
void addNewRoom(){
	Room newRoom;
	cout << "Enter new Room Details...." << endl;

	newRoom.Number =
		repeatIfNotNumber("Room Number: ", false);
	while (checkRoomExist(newRoom.Number)){
		cout << "this Room Number is taken try Another One:"
			<< endl;
		newRoom.Number =
			repeatIfNotNumber("Room Number: ", false);
	}

	cout << "Room Type: ";
	cin >> newRoom.Type;

	newRoom.amountCostPerhour =
		repeatIfNotNumber("Amount Cost per Hour: ", false);

	//adding the new room into the room list
	roomsList[roomsListSize] = newRoom;
	roomsListSize++;

	cout << "New Room Added Successfully." << endl;
}


// add a new reservation
// by adding new reserved room into reserved room list
void reserveRoom(){
	ReservedRoom reservedRoom;
	cout << "Reserving Room..." << endl;

	reservedRoom.Number = repeatIfNotNumber("Room Number: ", false);
	reservedRoom.CostumerID = repeatIfNotNumber("Costumer ID: ", false);
	if (!checkRoomExist(reservedRoom.Number)){
		cout << "No Room with this Number!!" << endl;
		return;
	}
	if (checkRoomReserved(reservedRoom.Number) != -1){
		cout << "this Room is Reserved!!";
		return;
	}
	if (!checkCustomerExist(reservedRoom.CostumerID)){
		cout << "No Costumer with this National ID!!" << endl;
		return;
	}
	// inserting the new reservation
	reservedRoomList[reservedRoomsListSize] = reservedRoom;
	reservedRoomsListSize++;
	cout << "Room " << reservedRoom.Number
		<< " Reserved Successfully." << endl;
}


// deleting a reservation by index of the reservation in the reserved room list
void deleteReservation(int RRIndex){
	for (int i = RRIndex; i < reservedRoomsListSize - 1; i++){
		swap(reservedRoomList[i], reservedRoomList[i + 1]);
	}
	reservedRoomsListSize--;
	cout << "Room " << reservedRoomList[reservedRoomsListSize].Number
		<< " Reservation Canceled Successfully." << endl;
}


// receiving the information of the a certain reservation
// and delete if it can be delete it
void cancelReservation(){
	string roomNumber;
	cout << "Canceling Room Reservation..." << endl;
	roomNumber = repeatIfNotNumber("Room Number: ", false);
	if (!checkRoomExist(roomNumber)){
		cout << "No Room with this Number!!" << endl;
		return;
	}
	int RRIndex = checkRoomReserved(roomNumber);
	if (RRIndex == -1){
		cout << "this Room is not Reserved!!" << endl;
		return;
	}
	deleteReservation(RRIndex);
}


// showing list of the available room that can be reserved
void searchAvailableRoom(){
	cout << "Available Rooms: " << endl;
	for (int i = 0; i < roomsListSize; i++){
		bool isReserved = false;
		// if a room is exist in the reserved room list
		// so this room is not available for reservation
		for (int j = 0; j < reservedRoomsListSize; j++){
			if (reservedRoomList[j].Number == roomsList[i].Number){
				isReserved = true;
				break;
			}
		}
		if (!isReserved){
			cout << roomsList[i].Number << endl;
		}
	}
	cout << "End of the List." << endl;
}


// updating certain costumer details by his national ID
// list of option to choose from
// each option is bounded with a certain detail
void updateCostumerDetails(){
	cout << "Updating Costumer Details..." << endl;
	cout << "Enter Costumer National ID to Update his Details:" << endl;
	string CID;
	CID = repeatIfNotNumber("Costumer ID: ", false);
	if (!checkCustomerExist(CID)){
		cout << "this National ID does not belong to a Costumer" << endl;
		return;
	}
	int CIndex = 0;
	for (int i = 0; i < costumersListSize; i++){
		if (costumersList[i].nationalID == CID){
			CIndex = i;
		}
	}
	cout << "Enter new Details for the Costumer with ID: " << CID << endl;
	int x;
	do{
		cout << "Enter 1 to Update First Name" << endl;
		cout << "Enter 2 to Update Middle Name" << endl;
		cout << "Enter 3 to Update Last Name" << endl;
		cout << "Enter 4 to Update Phone Name" << endl;
		cout << "Enter 5 to Update Address" << endl;
		cout << "Enter -1 to Save and Exit" << endl;
		cin >> x;
		switch (x){
		case 1:
			cout << "new First Name: ";
			cin >> costumersList[CIndex].firstName;
			break;
		case 2:
			cout << "new Middle Name: ";
			cin >> costumersList[CIndex].middleName;
			break;
		case 3:
			cout << "new Last Name: ";
			cin >> costumersList[CIndex].lastName;
			break;
		case 4:
			costumersList[CIndex].phoneNumber =
				repeatIfNotNumber("new Phone Number: ", true);
			break;
		case 5:
			cout << "new Address: ";
			cin.ignore();
			getline(cin, costumersList[CIndex].address);
			break;
		}
	} while (x != -1);

	cout << "Costumer with National ID " << CID
		<< " Updated Successfully." << endl;
}


// updating a certain room details by its number
// list of option to choose from
// each option is bounded with a certain detail
void updateRoomDetails(){
	cout << "Updating Room Details..." << endl;
	cout << "Enter Room Number to Update it's Details:" << endl;
	string roomNumber;
	roomNumber = repeatIfNotNumber("Room Number: ", false);
	if (!checkRoomExist(roomNumber)){
		cout << "there is no Room with this Number.. " << roomNumber << endl;
		return;
	}
	int RIndex = 0;
	for (int i = 0; i < roomsListSize; i++){
		if (roomsList[i].Number == roomNumber){
			RIndex = i;
		}
	}
	cout << "Enter new Details for the Room with Number: " << roomNumber << endl;
	int x;
	do{
		cout << "Enter 1 to Update Type" << endl;
		cout << "Enter 2 to Update Amount Cost per Hour" << endl;
		cout << "Enter -1 to Save and Exit" << endl;
		cin >> x;
		switch (x){
		case 1:
			cout << "new Type: ";
			cin >> roomsList[RIndex].Type;
			break;
		case 2:
			cout << "new Amount Cost per Hour: ";
			cin >> roomsList[RIndex].amountCostPerhour;
			break;
		}
	} while (x != -1);

	cout << "Room with Number" << roomNumber
		<< " Updated Successfully." << endl;
}


// deleting a room by its number
// if the room is reserved clear the reservation first
void deleteRoom(){
	cout << "Deleting Room ..." << endl;
	cout << "Enter Room Number to Delete it:" << endl;
	string roomNumber;
	roomNumber = repeatIfNotNumber("Room Number: ", false);
	if (!checkRoomExist(roomNumber)){
		cout << "this Room does not Exist" << endl;
		return;
	}
	int RRIndex = checkRoomReserved(roomNumber);
	if (RRIndex != -1){
		cout << "this Room is Reserved" << endl;
		cout << "to Stop Deleting Room Enter N else Enter anything" << endl;
		char y;
		cin >> y;
		if (y == 'N'){
			cout << "Deletion Canceled." << endl;
			return;
		}
		deleteReservation(RRIndex);

	}

	int RIndex = 0;
	for (int i = 0; i < roomsListSize; i++){
		if (roomsList[i].Number == roomNumber){
			RIndex = i;
		}
	}
	for (int i = RIndex; i < roomsListSize - 1; i++){
		swap(roomsList[i], roomsList[i + 1]);
	}
	roomsListSize--;
	cout << "Room Number " << roomNumber
		<< " Deleted Successfully." << endl;
}


// deleting a costumer by his national ID
// if the costumer is reserving a room or more than one room
// clear all the reservation then delete the costumer
void deleteCostumer(){
	cout << "Deleting Costumer ..." << endl;
	cout << "Enter Costumer National ID to Delete him:" << endl;
	string CID;
	CID = repeatIfNotNumber("Costumer ID: ", false);
	if (!checkCustomerExist(CID)){
		cout << "this National ID does not belong to a Costumer" << endl;
		return;
	}
	int RRIndex = checkCostumerReservationHistory(CID);
	if (RRIndex != -1){
		cout << "this Customer has Reservation History" << endl;
		cout << "to Stop Deleting Costumer Enter N else Enter anything" << endl;
		char y;
		cin >> y;
		if (y == 'N'){
			cout << "Deletion Canceled." << endl;
			return;
		}
		// deleting all the reservations
		do {
			deleteReservation(RRIndex);
			RRIndex = checkCostumerReservationHistory(CID);
		} while (RRIndex != -1);

	}


	// deleting the costumer
	int CIndex = 0;
	for (int i = 0; i < costumersListSize; i++){
		if (costumersList[i].nationalID == CID){
			CIndex = i;
		}
	}
	for (int i = CIndex; i < costumersListSize - 1; i++){
		swap(costumersList[i], costumersList[i + 1]);
	}
	costumersListSize--;
	cout << "Costumer with National ID " << CID
		<< " Deleted Successfully." << endl;
}


// showing the full details of a certain costumer by his national ID
void printCostumerDetails(){
	cout << "Printing Costumer Details ..." << endl;
	cout << "Enter Costumer National ID to Delete him:" << endl;
	string CID;
	CID = repeatIfNotNumber("Costumer ID: ", false);
	if (!checkCustomerExist(CID)){
		cout << "this National ID does not belong to a Costumer" << endl;
		return;
	}
	int CIndex;
	for (int i = 0; i < costumersListSize; i++){
		if (costumersList[i].nationalID == CID){
			CIndex = i;
		}
	}
	cout << "National ID: " << costumersList[CIndex].nationalID << endl;
	cout << "First Name: " << costumersList[CIndex].firstName << endl;
	cout << "Middle Name: " << costumersList[CIndex].middleName << endl;
	cout << "Last Name: " << costumersList[CIndex].lastName << endl;
	cout << "Phone Number: " << costumersList[CIndex].phoneNumber << endl;
	cout << "Address: " << costumersList[CIndex].address << endl;
	cout << "End of Costumer Details." << endl;
}


// showing the full details of a certain room by its number
void printRoomDetails(){
	cout << "Printing Room Details ..." << endl;
	cout << "Enter Room Number to Delete it:" << endl;
	string roomNumber;
	roomNumber = repeatIfNotNumber("Room Number: ", false);
	if (!checkRoomExist(roomNumber)){
		cout << "this Room does not Exist" << endl;
		return;
	}
	int RIndex;
	for (int i = 0; i < roomsListSize; i++){
		if (roomsList[i].Number == roomNumber){
			RIndex = i;
		}
	}
	cout << "Room Number: " << roomsList[RIndex].Number << endl;
	cout << "Room Type: " << roomsList[RIndex].Type << endl;
	cout << "Amount Cost per Hour : " << roomsList[RIndex].amountCostPerhour << endl;
	cout << "End of Room Details." << endl;

}

int main()
{
	int k;
	// infinite loop for inserting the number of a certain operation
	do{
		cout << "-------------------------" << endl;
		cout << "Enter the Number of the Operation to Proceed:" << endl;
		cout << "Enter 1  to Add New Costumer." << endl;
		cout << "Enter 2  to Add New Room." << endl;
		cout << "Enter 3  to Reserve Room." << endl;
		cout << "Enter 4  to Cancel Reservation." << endl;
		cout << "Enter 5  to Search Available Room." << endl;
		cout << "Enter 6  to Update Costumer Details." << endl;
		cout << "Enter 7  to Update Room Details." << endl;
		cout << "Enter 8  to Delete Costumer Details." << endl;
		cout << "Enter 9  to Delete Room Details." << endl;
		cout << "Enter 10 to Show Costumer Details." << endl;
		cout << "Enter 11 to Show Room Details." << endl;
		cout << "Enter 12 to Exit." << endl;
		cin >> k;
		switch (k){
		case 1:
			addNewCostumer();
			break;
		case 2:
			addNewRoom();
			break;
		case 3:
			reserveRoom();
			break;
		case 4:
			cancelReservation();
			break;
		case 5:
			searchAvailableRoom();
			break;
		case 6:
			updateCostumerDetails();
			break;
		case 7:
			updateRoomDetails();
			break;
		case 8:
			deleteCostumer();
			break;
		case 9:
			deleteRoom();
			break;
		case 10:
			printCostumerDetails();
			break;
		case 11:
			printRoomDetails();
			break;
		}
	} while (k != 12);
	return 0;
}


