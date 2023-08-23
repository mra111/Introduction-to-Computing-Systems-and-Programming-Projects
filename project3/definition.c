#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


/*define a function to count file lines*/
int count_file_lines(FILE* file) {
	int count_lines = 0;
	char string_char;
	string_char = fgetc(file);

	/*check if file ends*/
	while (string_char != EOF) {
		if (string_char == '\n') {
			count_lines = count_lines + 1;
		}
		string_char = fgetc(file);
	}

	/*return to the start of the file*/
	fseek(file, 0, SEEK_SET);
	return count_lines;
}


/*define a function to count words*/
int count_line_word(char *input) {
	int count_words = 0;
	int i = 0;
	char string_char = input[i];

	/*check if string ends*/
	while (string_char != NULL) {

		/*check if the character is space*/
		if (string_char == ' ') {
			count_words = count_words + 1;
		}
		string_char = input[i];
		i = i + 1;
	}
	count_words = count_words + 1;
	return count_words;
}


/*define a function to count word characters*/
int count_word_chars(char *word) {
	int count_chars = 0;
	int i = 0;
	while (word[i] != NULL) {
		count_chars = count_chars + 1;
		i = i + 1;
	}
	return count_chars;
}


/*define a function to insert a user*/
void insert_user(Users *head, Users *user) {
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = user;
	user->next = NULL;
}


/*define a function to insert a hall*/
void insert_hall(Halls *head, Halls *hall) {
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = hall;
	hall->next = NULL;
}


/*define a function to insert a food*/
void insert_food(Foods *head, Foods *food) {
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = food;
	food->next = NULL;
}


/*define a function to insert a coupon*/
void insert_coupon(Coupons *head, Coupons *coupon) {
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = coupon;
	coupon->next = NULL;
}


/*define a function to find a user*/
Users *find_user(int id, Users *users_list) {
	while (users_list != NULL) {
		if (users_list->student_id == id) {
			break;
		}
		users_list = users_list->next;
	}
	return users_list;
}


/*define a function to find a hall*/
Halls *find_hall(int id, Halls *halls_list) {
	while (halls_list != NULL) {
		if (halls_list->hall_id == id) {
			break;
		}
		halls_list = halls_list->next;
	}
	return halls_list;
}


/*define a function to find a food*/
Foods *find_food(int id, Foods *foods_list) {
	while (foods_list != NULL) {
		if (foods_list->food_id == id) {
			break;
		}
		foods_list = foods_list->next;
	}
	return foods_list;
}


/*define a function to find a coupon*/
Coupons *find_coupon(int id, Coupons *coupons_list) {
	while (coupons_list != NULL) {
		if (coupons_list->coupon_id == id) {
			break;
		}
		coupons_list = coupons_list->next;
	}
	return coupons_list;
}


/*check a function to find the username*/
int find_username(int count_users, char *user, Users *users_list) {
	int result;
	int find = NOT_FIND;

	/*find the username*/
	while (users_list != NULL) {
		if (strcmp(users_list->username, user) == 0) {
			result = FINDED;
			find = FINDED;
			break;
		}
		users_list = users_list->next;
	}

	if (find == NOT_FIND) {
		result = NOT_EXIST;
	}
	return result;
}


/*define a function to find the id*/
int find_user_id(int count_users, int id, Users *users_list) {
	int result;
	int find = NOT_FIND;

	/*find the id*/
	while (users_list != NULL) {
		if (users_list->student_id == id) {
			result = FINDED;
			find = FINDED;
			break;
		}
		users_list = users_list->next;
	}
	if (find == NOT_FIND) {
		result = NOT_EXIST;
	}
	return result;
}


/*define a function to find if hall exists*/
int find_hall_id(Halls *head, int id) {
	int result = NOT_FIND;
	while (head != NULL) {
		if (head->hall_id == id) {
			result = FINDED;
			break;
		}
		head = head->next;
	}
	return result;
}


/*define a function to find if a food exists*/
int find_food_id(Foods *head, int id) {
	int result = NOT_FIND;
	while (head != NULL) {
		if (head->food_id == id) {
			result = FINDED;
			break;
		}
		head = head->next;
	}
	return result;
}


/*define a function to find if a coupon exists*/
int find_coupon_id(Coupons *head, int id) {
	int result = NOT_FIND;
	while (head != NULL) {
		if (head->coupon_id == id) {
			result = FINDED;
			break;
		}
		head = head->next;
	}
	return result;
}


/*define a function to read data at start*/
Users *read_data(int count_users, int *error_status, FILE* file) {
	Users *users_list = (Users *)malloc(sizeof(Users));
	/*check if memory is allocated*/
	if (users_list == NULL) {
		*error_status = ERROR;
		return NULL;
	}

	/*check if file is open*/
	if (file == NULL) {
		*error_status = ERROR;
		return NULL;
	}

	int i;
	int count_chars;
	char buffer[MAX_ARRAY_SIZE];

	/*define admin user*/
	users_list->username = (char *)malloc(5 * sizeof(char));

	/*check if memory is allocated*/
	if (users_list->username == NULL) {
		*error_status = ERROR;
		return NULL;
	}

	users_list->password = (char *)malloc(5 * sizeof(char));

	/*check if memory is allocated*/
	if (users_list->password == NULL) {
		*error_status = ERROR;
		return NULL;
	}

	strcpy(users_list->username, "admin");
	users_list->student_id = NULL;
	strcpy(users_list->password, "admin");
	users_list->credit = 0;
	users_list->count_foods_reserved = 0;
	users_list->foods_reserved_id = (int *)malloc(sizeof(int));
	if (users_list->foods_reserved_id == NULL) {
		*error_status = ERROR;
		return NULL;
	}
	users_list->next = NULL;


	/*read users from the file*/
	for (i = 1; i < count_users; i++) {
		Users *user = (Users *)malloc(sizeof(Users));
		fscanf(file, "%s ", buffer);
		count_chars = count_word_chars(buffer);
		user->username = (char *)malloc(count_chars * sizeof(char));

		/*check if memory is allocated*/
		if (user->username == NULL) {
			*error_status = ERROR;
			return NULL;
		}

		strcpy(user->username, buffer);

		fscanf(file, "%d ", &user->student_id);

		fscanf(file, "%s\n", buffer);
		count_chars = count_word_chars(buffer);
		user->password = (char *)malloc(count_chars * sizeof(char));

		/*check if memory is allocated*/
		if (user->password == NULL) {
			*error_status = ERROR;
			return NULL;
		}

		strcpy(user->password, buffer);

		user->credit = 0;
		user->count_foods_reserved = 0;
		user->foods_reserved_id = (int *)malloc(sizeof(int));
		if (user->foods_reserved_id == NULL) {
			*error_status = ERROR;
			return NULL;
		}

		insert_user(users_list, user);
	}

	return users_list;
}


/*define function to log in*/
void user_login(int *login_status, int count_users, int *current_user_id, Commands *commands_word, Users *users_list) {
	int i;
	int username_exist = NOT_FIND;
	/*find the username*/
	while (users_list != NULL) {
		if (strcmp(users_list->username, commands_word[1].word) == 0) {
			username_exist = FINDED;
			break;
		}
		users_list = users_list->next;
	}


	/*check if username exists*/
	if (username_exist == FINDED) {
		/*check the password*/
		if (strcmp(users_list->password, commands_word[2].word) == 0) {
			printf("welcome %s\n", users_list->username);
			*current_user_id = users_list->student_id;

			/*check who logs in*/
			if (strcmp(users_list->username, "admin") == 0) {
				*login_status = AMIN_LOGED_IN;
			}
			else {
				*login_status = NORMAL_USER_LOGED_IN;
			}
		}
		else {
			printf("wrong username or pass\n");
		}
	}
	else {
		printf("wrong username or pass\n");
	}
}


/*define a function to sign up*/
Users *user_singup(int count_words, int *count_users, int *error_status, Commands *commands_word, Users *users_list) {
	/*open users file*/
	FILE* users = fopen("users.txt", "a");
	if (users == NULL) {
		*error_status = ERROR;
		return NULL;
	}

	int username_exist;
	int id_exist;
	int id = atoi(commands_word[2].word);
	int count_chars;
	int i;

	/*check if the username exits*/
	username_exist = find_username(*count_users, commands_word[1].word, users_list);

	/*check the id exists*/
	id_exist = find_user_id(*count_users, id, users_list);

	if (username_exist == NOT_EXIST && id_exist == NOT_EXIST) {
		*count_users = *count_users + 1;
		Users *user = (Users *)malloc(sizeof(Users));

		/*check if memory is allocated*/
		if (user == NULL) {
			*error_status = ERROR;
			return NULL;
		}

		/*define the user*/
		count_chars = count_word_chars(commands_word[1].word);
		user->username = (char *)malloc(count_chars * sizeof(char));

		/*check if memory is allocated*/
		if (user->username == NULL) {
			*error_status = ERROR;
			return NULL;
		}

		strcpy(user->username, commands_word[1].word);

		user->student_id = id;

		count_chars = count_word_chars(commands_word[3].word);
		user->password = (char *)malloc(count_chars * sizeof(char));
		if (user->password == NULL) {
			*error_status = ERROR;
			return NULL;
		}

		strcpy(user->password, commands_word[3].word);

		user->credit = 0;
		user->count_foods_reserved = 0;
		user->foods_reserved_id = (int *)malloc(sizeof(int));
		if (user->foods_reserved_id == NULL) {
			*error_status = ERROR;
			return NULL;
		}

		/*write the user to the file*/
		fprintf(users, "%s %d %s\n", user->username, user->student_id, user->password);
		insert_user(users_list, user);
		printf("done\n");
	}
	else {
		printf("user already exists\n");
	}

	/*close the file*/
	fclose(users);
	return users_list;
}


/*define a function to log out*/
void user_logout(int *login_status) {
	*login_status = NOT_LOGED_IN;
	printf("done\n");
}


/*define a function to add halls*/
Halls *add_hall(int *count_halls, int *error_status, Commands *commands_word, Halls *halls_list) {
	int hall_exist = NOT_FIND;
	int id = atoi(commands_word[2].word);
	int capacity = atoi(commands_word[3].word);
	int count_chars;
	int i;
	if (*count_halls != 0) {
		/*check if hall id exists*/
		hall_exist = find_hall_id(halls_list, id);
	}
	if (hall_exist == NOT_FIND) {
		if (*count_halls == 0) {
			*count_halls = *count_halls + 1;

			/*define the hall*/
			count_chars = count_word_chars(commands_word[1].word);
			halls_list->name = (char *)malloc(count_chars * sizeof(char));

			/*check if memory is allocated*/
			if (halls_list->name == NULL) {
				*error_status = ERROR;
				return NULL;
			}

			strcpy(halls_list->name, commands_word[1].word);
			halls_list->hall_id = id;
			halls_list->capacity = capacity;
			for (i = 0; i < 7; i++) {
				halls_list->days_reserved[i] = 0;
			}
			for (i = 0; i < 7; i++) {
				halls_list->days_profit[i] = 0;
			}
			printf("done\n");
		}
		else {
			*count_halls = *count_halls + 1;
			Halls *hall = (Halls *)malloc(sizeof(Halls));

			/*check if memory is allocated*/
			if (hall == NULL) {
				*error_status = ERROR;
				return NULL;
			}

			/*define the hall*/
			count_chars = count_word_chars(commands_word[1].word);
			hall->name = (char *)malloc(count_chars * sizeof(char));

			/*check if memory is allocated*/
			if (hall->name == NULL) {
				*error_status = ERROR;
				return NULL;
			}

			strcpy(hall->name, commands_word[1].word);
			hall->hall_id = id;
			hall->capacity = capacity;
			for (i = 0; i < 7; i++) {
				hall->days_reserved[i] = 0;
			}
			for (i = 0; i < 7; i++) {
				hall->days_profit[i] = 0;
			}
			insert_hall(halls_list, hall);
			printf("done\n");
		}
	}
	else {
		printf("hall id is not unique\n");
	}
	return halls_list;
}


/*define a function to add food*/
Foods *add_food(int *count_foods, int count_halls, int *error_status, Commands *commands_word, Foods *foods_list, Halls *halls_list) {
	int hall_id_exist = NOT_FIND;
	int food_id_exist = NOT_FIND;
	int i;
	int hall_id = atoi(commands_word[5].word);
	int food_id = atoi(commands_word[2].word);
	int price = atoi(commands_word[3].word);
	int capacity = atoi(commands_word[4].word);
	int day = atoi(commands_word[6].word);
	int count_chars;

	/*check if hall id exists*/
	if (count_halls != 0) {
		hall_id_exist = find_hall_id(halls_list, hall_id);
	}

	/*check if food id exists*/
	if (*count_foods != 0) {
		food_id_exist = find_food_id(foods_list, food_id);
	}

	if (hall_id_exist == FINDED && food_id_exist == NOT_FIND) {
		if (*count_foods == 0) {
			*count_foods = *count_foods + 1;

			/*define the food*/
			count_chars = count_word_chars(commands_word[1].word);
			foods_list->name = (char *)malloc(count_chars * sizeof(char));
			/*check if memory is allocated*/
			if (foods_list->name == NULL) {
				*error_status = ERROR;
				return NULL;
			}

			strcpy(foods_list->name, commands_word[1].word);
			foods_list->food_id = food_id;
			foods_list->price = price;
			foods_list->capacity = capacity;
			foods_list->hall_id = hall_id;
			foods_list->day = day;
			foods_list->total_capacity = foods_list->capacity;
			foods_list->profit = 0;
			printf("done\n");
		}
		else {
			*count_foods = *count_foods + 1;

			Foods *food = (Foods *)malloc(sizeof(Foods));
			/*check if memory is allocated*/
			if (food == NULL) {
				*error_status = ERROR;
				return NULL;
			}

			/*define the food*/
			count_chars = count_word_chars(commands_word[1].word);
			food->name = (char *)malloc(count_chars * sizeof(char));
			/*check if memory is allocated*/
			if (food->name == NULL) {
				*error_status = ERROR;
				return NULL;
			}

			strcpy(food->name, commands_word[1].word);
			food->food_id = food_id;
			food->price = price;
			food->capacity = capacity;
			food->hall_id = hall_id;
			food->day = day;
			food->total_capacity = food->capacity;
			food->profit = 0;
			insert_food(foods_list, food);
			printf("done\n");

		}
	}
	else if (hall_id_exist == NOT_FIND) {
		printf("wrong hall id\n");
	}
	else {
		printf("food id is not unique\n");
	}
	return foods_list;
}


/*define a function to add coupon*/
Coupons *add_coupon(int *count_coupons, int *error_status, Commands *commands_word, Coupons *coupons_list) {
	int coupon_id_exist = NOT_FIND;
	int id = atof(commands_word[1].word);
	int percentage = atof(commands_word[2].word);
	int capacity = atof(commands_word[3].word);
	int i;

	/*check if coupon id exists*/
	if (*count_coupons != 0) {
		coupon_id_exist = find_coupon_id(coupons_list, id);
	}

	if (coupon_id_exist == NOT_FIND) {
		if (*count_coupons == 0) {
			*count_coupons = *count_coupons + 1;

			/*define the coupon*/
			coupons_list->coupon_id = id;
			coupons_list->percentage = percentage;
			coupons_list->capacity = capacity;
			printf("done\n");
		}
		else {
			*count_coupons = *count_coupons + 1;

			Coupons *coupon = (Coupons *)malloc(sizeof(Coupons));
			/*check if memory is allocated*/
			if (coupon == NULL) {
				*error_status = ERROR;
				return NULL;
			}

			/*define the coupon*/
			coupon->coupon_id = id;
			coupon->percentage = percentage;
			coupon->capacity = capacity;
			insert_coupon(coupons_list, coupon);
			printf("done\n");
		}
	}
	else {
		printf("coupon id is not unique\n");
	}
	return coupons_list;
}


/*define a function to get money*/
void get_money(int current_user_id, Users *users_list, Commands *commands_word) {
	int money = atof(commands_word[1].word);
	users_list = find_user(current_user_id, users_list);
	users_list->credit = users_list->credit + money;
	printf("done\n");
}


/*define a function to show money*/
void show_money(int current_user_id, Users *users_list) {
	users_list = find_user(current_user_id, users_list);
	printf("%d\n", users_list->credit);
}


/*define a function to print hall name*/
void print_hall_name(int id, Halls *halls_list) {
	while (halls_list != NULL) {
		if (halls_list->hall_id == id) {
			printf("%s", halls_list->name);
			break;
		}
		halls_list = halls_list->next;
	}
}


/*define a function to show menu*/
void menu(int count_foods, Foods *foods_list, Halls *halls_list) {
	int day;
	Foods *head_foods;
	head_foods = foods_list;
	for (day = 1; day <= 7; day++) {
		printf("%d:\n", day);
		if (count_foods > 0) {
			while (foods_list != NULL) {
				if (foods_list->day == day) {
					/*print food*/
					printf("%s %d %d ", foods_list->name, foods_list->price, foods_list->food_id);
					print_hall_name(foods_list->hall_id, halls_list);
					printf(" %d\n", foods_list->capacity);
				}
				foods_list = foods_list->next;
			}
			foods_list = head_foods;
		}
	}
}


/*define a function to write food in food reserved list */
void reserve_food(int *error_status, Users *users_list, Foods *foods_list) {
	users_list->count_foods_reserved = users_list->count_foods_reserved + 1;
	users_list->foods_reserved_id = (int *)realloc(users_list->foods_reserved_id, users_list->count_foods_reserved * sizeof(int));
	/*check if memory is allocated*/
	if (users_list->foods_reserved_id == NULL) {
		*error_status = ERROR;
		return;
	}
	users_list->foods_reserved_id[users_list->count_foods_reserved - 1] = foods_list->food_id;
}


/*define a function to reserve food*/
void reserve_normal(int current_user_id, int *error_status, Commands *commands_word, Users *users_list, Foods *foods_list, Halls *halls_list) {
	int food_id = atof(commands_word[1].word);
	int hall_id;
	/*check if food exists*/
	if (find_food_id(foods_list, food_id) == FINDED) {
		/*find the user*/
		users_list = find_user(current_user_id, users_list);

		/*find the food*/
		foods_list = find_food(food_id, foods_list);

		hall_id = foods_list->hall_id;

		/*find the hall*/
		halls_list = find_hall(hall_id, halls_list);

		/*reserve the food*/
		if (foods_list->capacity > 0 && halls_list->days_reserved[foods_list->day - 1] < halls_list->capacity && users_list->credit >= foods_list->price) {
			reserve_food(error_status, users_list, foods_list);
			if (*error_status == ERROR) {
				return;
			}
			users_list->credit = users_list->credit - foods_list->price;
			foods_list->capacity = foods_list->capacity - 1;
			foods_list->profit = foods_list->profit + foods_list->price;
			halls_list->days_reserved[foods_list->day - 1] = halls_list->days_reserved[foods_list->day - 1] + 1;
			halls_list->days_profit[foods_list->day - 1] = halls_list->days_profit[foods_list->day - 1] + foods_list->price;
			printf("done\n");
		}
		else {
			printf("not possible\n");
		}
	}
	else {
		printf("not possible\n");
	}
}


/*define a function to reserve a food with discount*/
void reserve_discount(int current_user_id, int *error_status, Commands *commands_word, Users *users_list, Foods *foods_list, Halls *halls_list, Coupons *coupons_list) {
	int food_id = atof(commands_word[1].word);
	int coupon_id = atof(commands_word[2].word);
	int hall_id;
	int price;
	float percentage;
	/*check if food exists*/
	if (find_food_id(foods_list, food_id) == FINDED && find_coupon_id(coupons_list, coupon_id) == FINDED) {
		/*find the user*/
		users_list = find_user(current_user_id, users_list);

		/*find the food*/
		foods_list = find_food(food_id, foods_list);

		hall_id = foods_list->hall_id;

		/*find the hall*/
		halls_list = find_hall(hall_id, halls_list);

		/*find the coupon*/
		coupons_list = find_coupon(coupon_id, coupons_list);

		/*find price*/
		percentage = coupons_list->percentage;
		price = foods_list->price * ((100 - percentage) / 100);
		/*reserve the food*/
		if (foods_list->capacity > 0 && halls_list->days_reserved[foods_list->day - 1] < halls_list->capacity && coupons_list->capacity > 0 && users_list->credit >= price) {
			reserve_food(error_status, users_list, foods_list, halls_list);
			if (*error_status == ERROR) {
				return;
			}
			users_list->credit = users_list->credit - price;
			foods_list->capacity = foods_list->capacity - 1;
			foods_list->profit = foods_list->profit + price;
			halls_list->days_reserved[foods_list->day - 1] = halls_list->days_reserved[foods_list->day - 1] + 1;
			halls_list->days_profit[foods_list->day - 1] = halls_list->days_profit[foods_list->day - 1] + price;
			coupons_list->capacity = coupons_list->capacity - 1;
			printf("done\n");
		}
		else {
			printf("not possible\n");
		}
	}
	else {
		printf("not possible\n");
	}
}


/*define a function to show food reserved*/
void show_reserved(int current_user_id, Users *users_list, Foods *foods_list, Halls *halls_list) {
	int day;
	int i;
	int food_id;
	Foods *foods_head;
	foods_head = foods_list;

	/*find the user*/
	users_list = find_user(current_user_id, users_list);

	for (day = 1; day <= 7; day++) {
		printf("%d:\n", day);
		for (i = 0; i < users_list->count_foods_reserved; i++) {
			food_id = users_list->foods_reserved_id[i];

			foods_list = find_food(food_id, foods_list);

			/*print food*/
			if (foods_list->day == day) {
				printf("%s %d %d ", foods_list->name, foods_list->food_id, foods_list->price);
				print_hall_name(foods_list->hall_id, halls_list);
				printf("\n");
			}
			foods_list = foods_head;
		}
	}
}


/*define a function to make food report*/
void food_report(int count_foods, int *error_status, Foods *foods_list) {
	/*open food report file*/
	FILE* food_report_file = fopen("food_report.txt", "w");
	if (food_report_file == NULL) {
		*error_status = ERROR;
		return;
	}
	int reserved;
	if (count_foods != 0) {
		while (foods_list != NULL) {
			reserved = foods_list->total_capacity - foods_list->capacity;
			/*write food in file*/
			fprintf(food_report_file, "%d %d %d %d\n", foods_list->food_id, foods_list->total_capacity, reserved, foods_list->profit);
			foods_list = foods_list->next;
		}
	}
	else {
		fprintf(food_report_file, "there is no food available\n");
	}
	fclose(food_report_file);
	printf("done\n");
}


/*define a function to make hall report*/
void hall_report(int count_halls, int *error_status, Halls *halls_list) {
	/*open hall report file*/
	FILE* hall_report_file = fopen("hall_report.txt", "w");
	if (hall_report_file == NULL) {
		*error_status = ERROR;
		return;
	}
	int day;
	if (count_halls != 0) {
		while (halls_list != NULL) {
			/*write hall in file*/
			fprintf(hall_report_file, "%d %s %d\n", halls_list->hall_id, halls_list->name, halls_list->capacity);
			for (day = 1; day <= 7; day++) {
				fprintf(hall_report_file, "%d %d %d\n", day, halls_list->days_reserved[day - 1], halls_list->days_profit[day - 1]);
			}
			halls_list = halls_list->next;
		}
	}
	else {
		fprintf(hall_report_file, "there is no hall\n");
	}
	fclose(hall_report_file);
	printf("done\n");
}


/*define a function to delete users list*/
void delete_users_list(int count_users, Users *users_list) {
	Users *user;
	if (count_users != 0) {
		while (users_list != NULL) {
			user = users_list->next;
			free(users_list->username);
			free(users_list->password);
			free(users_list->foods_reserved_id);
			free(users_list);
			users_list = user;
		}
	}
}


/*define a food to delete halls list*/
void delete_halls_list(int count_halls, Halls *halls_list) {
	Halls *hall;
	if (count_halls != 0) {
		while (halls_list != NULL) {
			hall = halls_list->next;
			free(halls_list->name);
			free(halls_list);
			halls_list = hall;
		}
	}
}


/*define a function to delete foods list*/
void delete_foods_list(int count_foods, Foods *foods_list) {
	Foods *food;
	if (count_foods != 0) {
		while (foods_list != NULL) {
			food = foods_list->next;
			free(foods_list->name);
			free(foods_list);
			foods_list = food;
		}
	}
}


/*define a function to delete coupons list*/
void delete_coupons_list(int count_coupons, Coupons *coupons_list) {
	Coupons *coupon;
	if (count_coupons != 0) {
		while (coupons_list != NULL) {
			coupon = coupons_list->next;
			free(coupons_list);
			coupons_list = coupon;
		}
	}
}