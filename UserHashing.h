#pragma once
#include <string>
#include <fstream>

using namespace std;

struct UserStruct 
{
	string username;
	string password;
	UserStruct(string usr = "", string pwd = "") {
		username = usr;
		password = pwd;
	}
};

static UserStruct EmptyUser("", ""), DeletedUser("_del_", "_del_");

class UserHashing
{
private:
	UserStruct* users;
	int len;
	int count;
public:
	UserHashing(int num = 50) {
		len = num;
		users = new UserStruct[len];
		count = 0;
	}

	int getLength() {
		return len;
	}
	int getUserCount() {
		return count;
	}

	UserStruct GetUserByIndex(int index) {
		if (index < 0 || index >= len) { return UserStruct(); }
		return users[index];
	}

	bool CheckUserPass(UserStruct input_user) {
		int key = hashKey(input_user);

		if (users[key].username == input_user.username && users[key].password == input_user.password) {
			return true;
		}

		for (int i = 1; i < len; i++) {
			int k = (key + i) % len;
			if (users[key].username == EmptyUser.username && users[key].password == EmptyUser.password) {
				return false;
			}
			if (users[key].username == input_user.username && users[key].password == input_user.password) {
				return true;
			}
		}
		return false;
	}
	bool FindUser(string usr_name) {
		int key = hashKey({ usr_name, "" });

		if (users[key].username == usr_name) {
			return true;
		}

		for (int i = 1; i < len; i++) {
			int k = (key + i) % len;
			if (users[k].username == "") {
				return false;
			}
			if (users[k].username == usr_name) {
				return true;
			}
		}
		return false;

	}
	bool AddNewUser(UserStruct usr) {
		if (this->FindUser(usr.username)) { return false; }	//User already exists

		if (usr.username == "") { return false; }
		if (usr.password == "") { return false; }

		if (usr.username == DeletedUser.username) { return false; }
		if (usr.password == DeletedUser.password) { return false; }

		HashInsert(usr);

		return true;
	}

	void HashInsert(UserStruct data) {
		int key = hashKey(data);

		if (users[key].username == EmptyUser.username || users[key].username == DeletedUser.username) {
			users[key].username = data.username;
			users[key].password = data.password;
			count++;
			IsFull();
			return;
		}

		for (int i = 1; i < len; i++) {
			int k = (key + i) % len;
			if (users[key].username == EmptyUser.username || users[key].username == DeletedUser.username) {
				users[k].username = data.username;
				users[k].password = data.password;
				count++;
				IsFull();
				return;
			}
		}
	}
	void HashDelete(UserStruct data) {
		int key = hashKey(data);

		if (users[key].username == data.username) {
			users[key].username = DeletedUser.username;
			users[key].password = DeletedUser.password;
			count--;
			return;
		}

		for (int i = 1; i < len; i++) {
			int k = (key + i) % len;
			if (users[key].username == EmptyUser.username) {
				return;
			}
			if (users[key].username == data.username) {
				users[k].username = DeletedUser.username;
				users[k].password = DeletedUser.password;
				count--;
				return;
			}
		}
	}

	bool LoadData() {
		fstream file;
		file.open("ACCOUNTS_DATA.csv", ios::in);
		if (!file.is_open()) {
			file.open("ACCOUNTS_DATA.csv", ios::out);
			file.close();
		}

		count = 0;

		delete[] users;
		users = new UserStruct[len];

		string username, password;

		while (file.eof() == false) {
			try
			{
				getline(file, username, ',');
				getline(file, password);
				if (username == "" || password == "")
					continue;

				UserStruct user(username, password);
				HashInsert(user);
			}
			catch (exception&)
			{
				//
			}
		}


		file.close();
		return true;
	}
	bool SaveData() {
		fstream file;
		file.open("ACCOUNTS_DATA.csv", ios::out);

		for (int i = 0; i < len; i++) {
			if (users[i].username != EmptyUser.username
				&& users[i].username != DeletedUser.username)
				file << users[i].username << "," << users[i].password << endl;
		}

		file.close();
		return true;
	}

	bool IsFull() {
		if (len != count) {
			return false;
		}

		int TempSize = len;
		UserStruct* temp = new UserStruct[TempSize];
		for (int i = 0; i < len; i++) {
			temp[i].username = users[i].username;
			temp[i].password = users[i].password;
		}

		count = 0;
		delete[] users;
		len *= 2;
		users = new UserStruct[len];

		len *= 2;
		for (int i = 0; i < TempSize; i++) {
			if (users[i].username != EmptyUser.username
				&& users[i].username != DeletedUser.username)
				HashInsert(temp[i]);
		}
		delete[] temp;
		return true;
	}

	int hashKey(UserStruct data) {
		string str = data.username;	//hashing based on username
		int key = 0;
		for (int i = 0; i < str.length(); i++) {
			key = key + str[i];
		}
		return key % len;
	}

	~UserHashing() {
		delete[] users;
	}
};

