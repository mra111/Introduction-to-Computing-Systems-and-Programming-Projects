/*define the constants*/
#define NOT_LOGED_IN 0
#define NORMAL_USER_LOGED_IN 1
#define AMIN_LOGED_IN 2
#define NOT_FIND 0
#define FINDED 1
#define TRUE 1
#define INITIAL_NUMBER 0
#define MAX_ARRAY_SIZE 100
#define NO_ERROR 0
#define ERROR 1
#define NOT_EXIST -1


/*define users structure*/
typedef struct Users {
	char *username;
	int student_id;
	char *password;
	int credit;
	int count_foods_reserved;
	int *foods_reserved_id;
	struct Users *next;
} Users;


/*define commands structure*/
typedef struct Commands {
	char word[MAX_ARRAY_SIZE];
} Commands;


/*define halls structure*/
typedef struct Halls {
	char *name;
	int hall_id;
	int capacity;
	int days_reserved[7];
	int days_profit[7];
	struct Halls *next;
} Halls;


/*define foods structure*/
typedef struct Foods {
	char *name;
	int food_id;
	int price;
	int capacity;
	int hall_id;
	int day;
	int total_capacity;
	int profit;
	struct Food *next;
} Foods;


/*define coupons structure*/
typedef struct Coupons {
	int coupon_id;
	int percentage;
	int capacity;
	struct Coupons *next;
} Coupons;


/*declare functions*/
int count_file_lines(FILE* file);

int count_line_word(char *input);

int count_word_chars(char *word);

void insert_user(Users *head, Users *user);

void insert_hall(Halls *head, Halls *hall);

void insert_food(Foods *head, Foods *food);

void insert_coupon(Coupons *head, Coupons *coupon);

Users *find_user(int id, Users *users_list);

Halls *find_hall(int id, Halls *halls_list);

Foods *find_food(int id, Foods *foods_list);

Coupons *find_coupon(int id, Coupons *coupons_list);

int find_username(int count_users, char *user, Users *users_list);

int find_user_id(int count_users, int id, Users *users_list);

int find_hall_id(Halls *head, int id);

int find_food_id(Foods *head, int id);

int find_coupon_id(Coupons *head, int id);

Users *read_data(int count_users, int *error_status, FILE* file);

void user_login(int *login_status, int count_users, int *current_user_id, Commands *commands_word, Users *users_list);

Users *user_singup(int count_words, int *count_users, int *error_status, Commands *commands_word, Users *users_list);

void user_logout(int *login_status);

Halls *add_hall(int *count_halls, int *error_status, Commands *commands_word, Halls *halls_list);

Foods *add_food(int *count_foods, int count_halls, int *error_status, Commands *commands_word, Foods *foods_list, Halls *halls_list);

Coupons *add_coupon(int *count_coupons, int *error_status, Commands *commands_word, Coupons *coupons_list);

void get_money(int current_user_id, Users *users_list, Commands *commands_word);

void show_money(int current_user_id, Users *users_list);

void print_hall_name(int id, Halls *halls_list);

void menu(int count_foods, Foods *foods_list, Halls *halls_list);

void reserve_food(int *error_status, Users *users_list, Foods *foods_list);

void reserve_normal(int current_user_id, int *error_status, Commands *commands_word, Users *users_list, Foods *foods_list, Halls *halls_list);

void reserve_discount(int current_user_id, int *error_status, Commands *commands_word, Users *users_list, Foods *foods_list, Halls *halls_list, Coupons *coupons_list);

void show_reserved(int current_user_id, Users *users_list, Foods *foods_list, Halls *halls_list);

void food_report(int count_foods, int *error_status, Foods *foods_list);

void hall_report(int count_halls, int *error_status, Halls *halls_list);

void delete_users_list(int count_users, Users *users_list);

void delete_halls_list(int count_halls, Halls *halls_list);

void delete_foods_list(int count_foods, Foods *foods_list);

void delete_coupons_list(int count_coupons, Coupons *coupons_list);