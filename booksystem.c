#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

#define MAX 500
#define MAXTOKEN 40
#define MAXSTR 100
#define MAXID 100
#define MAXHASH 100

//コマンドの定義
enum Command {
	COMMAND_RETRIEVE = 1,
	COMMAND_LEND,
	COMMAND_RETURN,
	COMMAND_QUIT
};
//検索キーの定義
enum Retrieve_Key {
	RETRIEVE_KEY_ID = 1,
	RETRIEVE_KEY_AUTHOR,
	RETRIEVE_KEY_TITLE,
	RETRIEVE_KEY_KEYWORD,
};

struct book{
	int id;	     //図書ID
	char title[MAXTOKEN]; //タイトル
	char author[MAXTOKEN];//著者名
	int num;     //冊数
	int borrowed;//貸出冊数
};

struct book_low{
	int id;	 //図書ID
	char title[MAXTOKEN];     //タイトル
	char title_low[MAXTOKEN]; //タイトル(小文字)
	char author[MAXTOKEN];    //著者名
	char author_low[MAXTOKEN];//著者名(小文字)
	int num;     //冊数
	int borrowed;//貸出冊数
};

struct idx_tbl{
	int id;//図書id
	int idx;//Book[]のインデックス番号
};

struct kw_id{
	char kw[MAXSTR];
	int id;
};

struct kw_hash{
	int flag;        //0:空き, 1:使用中
	char kw[MAXSTR]; //キーワード
	int n;           //idに登録した数
	int id[MAXID];   //図書ID
};

//プロトタイプ宣言
	//@brief Book構造体配列に	書かれた本の情報をidx_tbl構造体配列に格納する関数
	//@params (infp) ファイルのパス
	//@params (book) Book構造体配列 本の情報が書かれている
	//@params (idx_tbl) idx_tbl構造体配列、本の情報を書き込む
	//@return 本の数
	int create_tbl(FILE *infp, struct book *book, struct idx_tbl *idx_tbl);
	
	//@brief IDの昇順にクイックソートする関数
	//@params (idx_tbl) ソートする構造体配列
	//@params (left) 左端
	//@params (right) 右端
	//@return なし
	void sort_book(struct idx_tbl *idx_tbl, int left, int right);

	//@brief 利用者とインタラクション(プログラムとユーザ間を結ぶ手段のこと)を行う関数
	//@params (book) 未ソートの本の情報が書かれた構造体配列
	//@params (idx_tbl) ソート済みの本の情報が書かれた構造体配列 
	//@params (n) 本の数
	//@return -1
	int proc_request(struct book_low *Book, struct idx_tbl *Idx_tbl, int n);
	
	//@brief IDに合致する本を見つけ、そのインデックス番号を返す関数
	//@params (id) 検索するID
	//@params (Idx_tbl) 本の情報が入った構造体配列
	//@params (n) 本の数
	//@return 該当する本のindex番号
	int retrieve_by_id(int id, struct idx_tbl *Idx_tbl, int n);
		
	//@brief 著者名検索する関数
	//@params (*author) 検索する著者名へのポインタ
	//@params (book) 未ソートの本の情報が書かれた構造体配列へのポインタ
	//@params (b) 検索を開始するBook[]のインデックス
	//@params (n) 本の数
	//@return -1 見つからなかった
	//@return 上記以外の整数 該当する図書のインデックス
	int retrieve_by_author(char *author, struct book_low *book, int b, int n);

	//@brief タイトル検索する関数
	//@params (*title) 検索するタイトル名へのポインタ
	//@params (book) 未ソートの本の情報が書かれた構造体配列へのポインタ
	//@params (b) 検索を開始するBook[]のインデックス
	//@params (n) 本の数
	//@return -1 見つからなかった
	//@return 上記以外の整数 該当する図書のインデックス
	int retrieve_by_title(char *title, struct book_low *book, int b, int n);
	
	//@brief 貸出処理を行う関数
	//@params (*book) book構造体へのポインタ
	//@params (i) Book[]のインデックス
	//@return なし
	void lend(struct book_low *book, int i);
	
	//@brief 返却処理を行う関数
	//@params (*book) book構造体へのポインタ
	//@params (i) Book[]のインデックス
	//@return なし
	void ret(struct book_low *book, int i);

	//@brief 関数名を参考にしてください
	//@params (book) 未ソートの本の情報が書かれた構造体配列へのポインタ
	//@params (idx_tbl) ソート済みの本の情報が書かれた構造体配列
	//@params (n) 本の数
	//@return 1 正常終了
	int on_request_retrieve(struct book_low *book, struct idx_tbl *idx_tbl, int n);
	int on_request_retrieve_by_id(struct book_low *Book, struct idx_tbl *Idx_tbl, int n);
	int on_request_retrieve_by_author(struct book_low *Book, struct idx_tbl *Idx_tbl, int n);
	int on_request_retrieve_by_title(struct book_low *Book, struct idx_tbl *Idx_tbl, int n);
	int on_request_retrieve_by_keyword(struct book_low *Book, struct idx_tbl *Idx_tbl, int n);
	int on_request_lend(struct book_low *Book, struct idx_tbl *Idx_tbl, int n);
	int on_request_return(struct book_low *Book, struct idx_tbl *Idx_tbl, int n);
	int on_request_exit(struct book_low *book, struct idx_tbl *idx_tbl, int n);
	
	//@brief キーワード検索を行う関数
	//@params (keyword) キーワード（複数指定可能）
	//@params (keyword_num) keywordで指定したキーワードの数
	//@params (kw_hash) キーワードのハッシュテーブルへのポインタ
	//@params (idset) キーワードに合致した本の図書IDを格納するための配列へのポインタ
	//@return 1 正常終了
	int retrieve_by_keyword(char keyword[][MAXSTR], int keyword_num, struct kw_hash *kw_hash, int *idset);
	
	//@brief デリミッタ、改行文字で区切ったトークンをtoken[][]に格納する関数
	//@params (buff) 一行分のデータ
	//@params (del) 区切り文字
	//@params (token) 切り出したトークンの配列
	//@return 切り出したトークンの数
	int gettoken(char *buff, char del, char token[][MAXSTR]);
	
	//@brief token[][]のトークンをBook構造体配列とidx_tbl構造体配列に格納する関数
	//@params (token) トークンが書かれた二次元配列
	//@params (token_num) トークン数
	//@params (book) Book_low構造体配列 本の情報を書き込む
	//@params (idx_tbl) idx_tbl構造体配列、本の情報を書き込む。後でソートする
	//@return なし
	void create_tbl2(char token[][MAXSTR], int token_num, struct book_low *book, struct idx_tbl *idx_tbl);

	//@brief str内の大文字を小文字に変える関数
	//@params (str) 文字列のポインタ
	//@return なし
	void up2low(char *str);
	
	//@brief kw_id配列を作る関数
	//@params (low) Book_low構造体配列
	//@params (n) Book_lowへの登録数
	//@params (kw_id[]) キーワードと図書IDをペアとする構造体配列
	//@return kw_id[]に書き込んだペア数
	int collect_kyword(struct book_low *book, int n, struct kw_id kw_id[]);
	
	//@brief ハッシュ値を返す関数
	//@params (key) ハッシュ前の文字列ポインタ
	//@return ハッシュ値
	int hash(char *key);

	//@brief ハッシュ表を初期化する関数
	//@params (kw_hash[]) ハッシュ表の文字列ポインタ
	//@return なし
	void initialize_hash_table(int kw_num, struct kw_hash kw_hash[]);
	
	//@brief ハッシュ表を作る関数
	//@params (kw_num) キーワードの数
	//@params (kw_id[]) キーワードと図書IDの連想配列
	//@params (kw_hash[]) ハッシュ表
	//@return なし
	void create_hash_table(int kw_num, struct kw_id kw_id[], struct kw_hash kw_hash[]);
	
	//@brief idset[]にidがあるか調べる関数
	//@params (idset) idの配列
	//@params (id) あるか調べるID
	//@params (m) idsetに登録しているIDの数
	//@return 1 図書IDがある
	//@return 0 図書IDがない
	int exist_in_idset(int *idset, int id, int m);
//プロトタイプ宣言

typedef int (*CommandHandler)(struct book_low *book, struct idx_tbl *idx_tbl, int n);

struct CommandHandle {
	char *name;
	int command;
	CommandHandler handler;
};

struct CommandHandle command_handles[] = {
	{ "検索", COMMAND_RETRIEVE, on_request_retrieve},
	{ "貸出", COMMAND_LEND, on_request_lend},
	{ "返却", COMMAND_RETURN, on_request_return},
	{ "終了", COMMAND_QUIT, on_request_exit},
};
struct CommandHandle retrieve_handles[] = {
	{ "ID", RETRIEVE_KEY_ID, on_request_retrieve_by_id},
	{ "著者名", RETRIEVE_KEY_AUTHOR, on_request_retrieve_by_author},
	{ "タイトル", RETRIEVE_KEY_TITLE, on_request_retrieve_by_title},
	{ "キーワード", RETRIEVE_KEY_KEYWORD, on_request_retrieve_by_keyword},
};

int main(int argc, char *argv[]){
	int n, idx;
	char file[MAX], buff[124], token[MAXTOKEN][MAXSTR];
	char del = ','; //区切り文字
	FILE *infp;
	//struct book Book[MAX];        //図書データ
	struct book_low Book_low[MAX];//小文字を含む図書データ
	//struct idx_tbl Idx_tbl[MAX];
	struct idx_tbl Idx_tbl2[MAX];
	int token_num, kw_num;
	struct kw_id kw_id[MAXID];
	struct kw_hash kw_hash[MAXHASH];
	int hash_num;

	//コマンドライン引数を読み取る
	if(argc == 1)
		strcpy(file, "books.txt");
	//fileを指定した場合
	if(argc == 2)
		strcpy(file, argv[1]);
	//C:\Users\kokok\Downloads\book2.txt
	//strcpy(file,"C:\\Users\\kokok\\Downloads\\book2.txt");
	printf("file名：%s\n", file);

	
	//ファイルが見つからなければ、エラー処理
	if((infp=fopen(file,"r"))==NULL){
		printf("file not found.\n");
		exit(1);
	}
	
	/*step7より前の処理
	infp = fopen(file,"r");
	n = create_tbl(infp, Book, Idx_tbl);
	sort_book(Idx_tbl, 0, n-1);
	
	//正しく取得できてるか表示
	for(int i=0; i<n; i++){
		//正しく取得できてるか確認する
		idx = Idx_tbl[i].idx;
		printf("Id=%d Title=%s Author=%s Num=%d\n",Book[idx].id, Book[idx].title, Book[idx].author, Book[idx].num);
	}

	//ここからインタラクション
	while(proc_request(Book, Idx_tbl, n));
	fclose(infp);
	*/
	
	infp = fopen(file, "r");
	
	n = 0;
	while(fgets(buff, sizeof(buff), infp) != NULL){
		token_num = gettoken(buff, del, token);
		create_tbl2(token, token_num, Book_low, Idx_tbl2);
		n++;
	}
	sort_book(Idx_tbl2, 0, n-1);

	//正しく取得できてるか表示
	for(int i=0; i<n; i++){
		//正しく取得できてるか確認する
		idx = Idx_tbl2[i].idx;
		printf("Id=%d Title=%s TitleLow=%s Author=%s AuthorLow=%s Num=%d\n",Book_low[idx].id, Book_low[idx].title, Book_low[idx].title_low, Book_low[idx].author, Book_low[idx].author_low, Book_low[idx].num);
	}
	//ここからインタラクション
	while(proc_request(Book_low, Idx_tbl2, n));
	fclose(infp);

	return 0;
	
}



/*
int create_tbl(FILE *infp, struct book *book, struct idx_tbl *idx_tbl){
	int i = 0;
	int id, num;
	char author[MAXTOKEN], title[MAXTOKEN];
	
	while(fscanf(infp,"%d %s %s %d", &id, author, title, &num)!=EOF){
		//bookに情報を代入する処理
		book[i].id = id;
		strcpy(book[i].author, author);
		strcpy(book[i].title, title);
		book[i].num = num;
		book[i].borrowed = 0;
		
		//構造体配列に代入する処理
		idx_tbl[i].id = book[i].id;
		idx_tbl[i].idx = i;
		i++;
	}
	return i;
}
*/

int gettoken(char *buff, char del, char token[][MAXSTR]){
	int i = 0;
	char *p, *q, *r;
	q = buff;
	
	while(1){
		while(*q == ' ') q++; //空白を飛ばす
		p = strchr(q, del);   //pにはデリミッタのアドレスが入る
		if (p != NULL) {      //区切り文字が見つかった場合
			*p = '\0';
			strcpy(&token[i][0], q);
			q = p+1;
			i++;
		} else { // 区切り文字が見つからなかった場合
			r = strchr(q, '\n');
			if(r != NULL){
				*r = '\0';//最後の改行文字を\0に変える
			}
			strcpy(&token[i][0], q);
			break;
		}
	}
	return i+1;
}

void up2low(char *str){
	while(*str != '\0') {
		if('A' <= *str && *str <= 'Z')
			*str = tolower(*str);
		str++;
	}
	return;
}


void create_tbl2(char token[][MAXSTR], int token_num, struct book_low *book, struct idx_tbl *idx_tbl){
	static int i = 0;
	
	//bookに情報を代入する処理
	book[i].id = atoi(token[0]);
	strcpy(book[i].author, token[1]);
	up2low(token[1]);
	strcpy(book[i].author_low, token[1]);
	strcpy(book[i].title, token[2]);
	up2low(token[2]);
	strcpy(book[i].title_low, token[2]);
	book[i].num = atoi(token[3]);
	book[i].borrowed = 0;
	
	//構造体配列に代入する処理
	idx_tbl[i].id = book[i].id;
	idx_tbl[i].idx = i;
	
	i++;
}

int collect_kyword(struct book_low *Book, int n, struct kw_id kw_id[]){
	int token_num, k, j = 0;
	char token[MAXTOKEN][MAXSTR];
	for(int i =0; i < n; i++){		
		token_num = gettoken(Book[i].author_low, ' ', token);
		for(k = 0; k < token_num; k++){
			strcpy(kw_id[j].kw,token[k]);
			kw_id[j].id = Book[i].id;
			j++;
		}
		token_num = gettoken(Book[i].title_low, ' ', token);
		for(k = 0; k < token_num; k++){
			strcpy(kw_id[j].kw,token[k]);
			kw_id[j].id = Book[i].id;
			j++;
		}
	}
	return j;
}

void sort_book(struct idx_tbl *idx_tbl, int left, int right){
	int i, j, somewhere;
	int pivot;
	struct idx_tbl tmp;
	int stack_left[MAXTOKEN], stack_right[MAXTOKEN];
	int stack_top = 0;
	int tmp_left, tmp_right;
	
	//最初のプッシュ
	stack_left[stack_top] = left;
	stack_right[stack_top] = right;
	stack_top++;
	//スタックが空になるまで繰り返す
	while(stack_top != -1){
		//ポップする処理
		stack_top--;
		tmp_left = stack_left[stack_top];
		tmp_right = stack_right[stack_top];
		//ポップする処理
		somewhere = (tmp_left + tmp_right) / 2;
		pivot = idx_tbl[somewhere].id;
		i = tmp_left; j = tmp_right;
		while(i <= j){
			while(idx_tbl[i].id < pivot) i++;//pivot以上の値を見つける
			while(idx_tbl[j].id > pivot) j--;//pivot以下の値を見つける
			if(i <= j){
				//入れ替える処理
				tmp        = idx_tbl[i];
				idx_tbl[i] = idx_tbl[j];
				idx_tbl[j] = tmp;
				//入れ替える処理
				i++; j--;
			}
		}
		//プッシュする処理
		if(tmp_left < j) {
			stack_left[stack_top] = tmp_left;
			stack_right[stack_top] = j;
			stack_top++;
		}
		if(i < tmp_right) {
			stack_left[stack_top] = i;
			stack_right[stack_top] = tmp_right;
			stack_top++;
		}
		//プッシュする処理
	}
	//スタックが空になるまで繰り返す
}

int proc_request(struct book_low *Book, struct idx_tbl *Idx_tbl, int n){
	char cmd_str[MAXTOKEN];
	int cmd;
	const int size = sizeof(command_handles) / sizeof(struct CommandHandle);
	printf("図書検索・貸出システム\n");
	printf("コマンドを入力してください ");
	for(int i=0; i<size; i++){
		printf("%s(%d)", command_handles[i].name, command_handles[i].command);
	}
	printf(":");
	
	//検索 貸出 返却 終了の４つ
	//scanf("%d", &cmd);
	fgets(cmd_str, MAXTOKEN,stdin);
	cmd = atoi(cmd_str);
	for(int i=0; i<size; i++){
		if(command_handles[i].command == cmd){
			return command_handles[i].handler(Book, Idx_tbl, n);
		}
	}
	printf("無効なコマンドです\n");
	return -1;
}

int retrieve_by_id(int id, struct idx_tbl *Idx_tbl, int n){
	int low,mid,high;
	low = 0;
	high = n-1;
	while(low <= high){
		mid = (low + high) / 2;
		if(id == Idx_tbl[mid].id) return Idx_tbl[mid].idx;
		else if(id < Idx_tbl[mid].id) high = mid-1;
		else low = mid + 1;
	}
	return -1;
}


int retrieve_by_author(char *author, struct book_low *book, int b, int n){
	for(int i=b;i<n;i++){
		if(strstr(book[i].author_low, author) != NULL){
			return i;
		}
	}
	return -1;
}

int retrieve_by_title(char *title, struct book_low *book, int b, int n){
	int i,length;
	length = strlen(title);
	for(i=b; i<n; i++){
		if(strstr(book[i].title_low, title) != NULL){
			return i;
		}
	}
	return -1;
}

int hash(char *key){
	int i,h=0;
	int k = 3, max=59;
	for(i=0;key[i]!='\0';i++)
		h = (h * k + key[i]) % max;
	return h;
}

void initialize_hash_table(int kw_num, struct kw_hash kw_hash[]){
	for(int i = 0; i < kw_num; i++) {
		kw_hash[i].flag = 0;
		kw_hash[i].n = 0;
	}
}
void create_hash_table(int kw_num, struct kw_id kw_id[], struct kw_hash kw_hash[]){
	int hash_num;
	for(int i = 0; i < kw_num; i++){
		hash_num = hash(kw_id[i].kw);
		while(1){
			if(kw_hash[hash_num].flag == 0){//エントリが未使用
				kw_hash[hash_num].flag = 1;
				strcpy(kw_hash[hash_num].kw,kw_id[i].kw);
				kw_hash[hash_num].n++;
				kw_hash[hash_num].id[0] = kw_id[i].id;
				break;
			} else if(kw_hash[hash_num].flag == 1 && strcmp(kw_hash[hash_num].kw,kw_id[i].kw) == 0){//エントリが使用中かつ登録キーワードが同じ
				kw_hash[hash_num].id[kw_hash[hash_num].n] = kw_id[i].id;
				kw_hash[hash_num].n++;
				break;
			} else if(kw_hash[hash_num].flag == 1 && strcmp(kw_hash[hash_num].kw,kw_id[i].kw) != 0){//エントリが使用中かつ登録キーワードが異なる
				hash_num = (hash_num+1) % MAXHASH;
			}
		}
	}
}
	
int on_request_retrieve_by_keyword(struct book_low *Book, struct idx_tbl *Idx_tbl, int n){
	static struct kw_hash kw_hash[MAXHASH];
	static bool is_firsttime = true;
	char key[MAXTOKEN], keyword_token[MAXTOKEN][MAXSTR];
	int idset[MAXID], idx, keyword_num, m, kw_num;
	struct kw_id kw_id[MAXID];

	//ハッシュテーブルを作る処理
	if(is_firsttime){
		is_firsttime = false;
		kw_num = collect_kyword(Book, n, kw_id);
		initialize_hash_table(kw_num, kw_hash);
		create_hash_table(kw_num, kw_id, kw_hash);	
	}
	//ハッシュテーブルを作る処理


	
	printf("キーワードを入力してください:");
	fgets(key, MAXTOKEN, stdin);
	up2low(key);
	keyword_num = gettoken(key, ' ', keyword_token);
	m = retrieve_by_keyword(keyword_token, keyword_num, kw_hash, idset);
	
	for(int i = 0; i < m; i++){
		idx = retrieve_by_id(idset[i], Idx_tbl, n);
		if(idx != -1) {
			printf("こちらが見つかりました:\n");
			printf("Id=%d Title=%s Author=%s Num=%d\n",Book[idx].id, Book[idx].title, Book[idx].author, Book[idx].num);
		}
	}
	if(m == 0){
		printf("該当する本は見つかりませんでした\n");
	}
	return 1;

}

int retrieve_by_keyword(char keyword[][MAXSTR], int keyword_num, struct kw_hash *kw_hash, int *idset){
	int hash_num, m=0;
	for(int i = 0; i < keyword_num; i++){
		hash_num = hash(keyword[i]);
		while(1){
			if(kw_hash[hash_num].flag == 1){//エントリが使用中
				if(strcmp(kw_hash[hash_num].kw, keyword[i]) == 0){//キーワードが同じ
					for(int j = 0; j < kw_hash[hash_num].n; j++){//kw_hashのIDをすべて登録する
						if(!exist_in_idset(idset, kw_hash[hash_num].id[j], m)){
							idset[m] = kw_hash[hash_num].id[j];
							m++;	
						}
					}
					break;
				} else { //キーワードが異なる
					hash_num = (hash_num+1) % MAXHASH;
					continue;
				}
			} else if(kw_hash[hash_num].flag == 0) { //エントリが未使用
				break;
			}
		}
	}
	return m;
}

int exist_in_idset(int *idset, int id, int m){
	for(int i = 0; i<m; i++){
		if(idset[i] == id)
			return 1;
	}
	return 0;
}

int on_request_retrieve(struct book_low *Book, struct idx_tbl *Idx_tbl, int n){
	char subcmd_str[MAXTOKEN];
	int subcmd;
	const int size = sizeof(retrieve_handles) / sizeof(struct CommandHandle);
	printf("キーは何にしますか？ ");
	for(int i=0; i<size; i++){
		printf("%s(%d)", retrieve_handles[i].name, retrieve_handles[i].command);
	}
	printf(":");

	fgets(subcmd_str,MAXTOKEN,stdin);
	subcmd = atoi(subcmd_str);
	for(int i=0; i<size; i++){
		if(retrieve_handles[i].command == subcmd)
			retrieve_handles[i].handler(Book, Idx_tbl, n);
	}
	return 1;
}

int on_request_lend(struct book_low *Book, struct idx_tbl *Idx_tbl, int n)
{
	char id_str[MAXTOKEN];
	int id,idx;
	printf("借りたい本のIDを入力してください\n");
	fgets(id_str,MAXTOKEN,stdin);
	id = atoi(id_str);
	idx = retrieve_by_id(id, Idx_tbl, n);
	if(idx == -1){
		printf("ID=%dの本は存在しません\n",id);
	} else {
		lend(Book, idx);
	}
	return 1;
}
	
void lend(struct book_low *book, int i)
{
	if(book[i].num > book[i].borrowed) {
		book[i].borrowed++;
		printf("こちらの本を貸し出しました\n");
		printf("Id=%d Title=%s Author=%s Num=%d\n",book[i].id, book[i].title, book[i].author, book[i].num);
	} else {
		printf("こちらの本はすべて貸し出し中です\n");
		printf("Id=%d Title=%s Author=%s Num=%d\n",book[i].id, book[i].title, book[i].author, book[i].num);
	}
	printf("貸出数:%d\n",book[i].borrowed);
	printf("残り冊数:%d\n", book[i].num - book[i].borrowed);
}
	
void ret(struct book_low *book, int i)
{
	if(book[i].borrowed > 0) {
		book[i].borrowed--;
		printf("こちらの本を返却しました\n");
		printf("Id=%d Title=%s Author=%s Num=%d\n",book[i].id, book[i].title, book[i].author, book[i].num);
	} else {
		printf("こちらの本は貸し出されていません\n");
		printf("Id=%d Title=%s Author=%s Num=%d\n",book[i].id, book[i].title, book[i].author, book[i].num);
	}
	printf("貸出数:%d\n",book[i].borrowed);
	printf("残り冊数:%d\n", book[i].num - book[i].borrowed);
}	
	
int on_request_return(struct book_low *Book, struct idx_tbl *Idx_tbl, int n){
	char id_str[MAXTOKEN];
	int id, idx;
	printf("返却したい本のIDを入力してください\n");
	fgets(id_str,MAXTOKEN,stdin);
	id = atoi(id_str);
	idx = retrieve_by_id(id, Idx_tbl, n);
	if(idx == -1){
		printf("ID=%dの本は存在しません\n",id);
	} else {
		ret(Book, idx);
	}
	return 1;
}
	
int on_request_retrieve_by_id(struct book_low *Book, struct idx_tbl *Idx_tbl, int n){
	char id_str[MAXTOKEN];
	int id, idx;
	printf("図書IDを入力してください\n");
	fgets(id_str,MAXTOKEN,stdin);
	id = atoi(id_str);
	idx = retrieve_by_id(id, Idx_tbl, n);
	if(idx != -1) {
		printf("こちらが見つかりました:\n");
		printf("Id=%d Title=%s Author=%s Num=%d\n",Book[idx].id, Book[idx].title, Book[idx].author, Book[idx].num);
	} else {
		printf("該当する本は見つかりませんでした\n");
	}
	return 1;
}
	
int on_request_retrieve_by_author(struct book_low *Book, struct idx_tbl *Idx_tbl, int n){
	int j,m;
	char author[MAXTOKEN];
	char *p;
	printf("著者名を入力:");
	//scanf("%s", author);
	fgets(author, MAXTOKEN, stdin);
	p = strchr(author, '\n');
	if(p)
		*p = '\0';
	up2low(author);
	j=0;//検索開始位置
	m=0;//冊数
	while((j=retrieve_by_author(author, Book, j, n))!= -1){
		printf("こちらの本が見つかりました。Id=%d Title=%s Author=%s\n",Book[j].id, Book[j].title, Book[j].author);
		j++;
		m++;
	}
	if(m == 0){
		printf("該当する本は見つかりませんでした\n");
	}
	return 1;
}
	
int on_request_retrieve_by_title(struct book_low *Book, struct idx_tbl *Idx_tbl, int n){
	int j, m;
	char title[MAXTOKEN];
	char *p;
	printf("タイトルを入力:");
	fgets(title, MAXTOKEN,stdin);
	p = strchr(title, '\n');
	if(p)
		*p = '\0';
	up2low(title);
	j=0;//検索開始位置
	m=0;//冊数
	while((j=retrieve_by_title(title, Book, j, n))!=-1){
		printf("こちらの本が見つかりました。Id=%d Title=%s Author=%s\n",Book[j].id, Book[j].title, Book[j].author);
		j++;
		m++;
	}
	if(m == 0){
		printf("該当する本は見つかりませんでした\n");
	}
	return 1;
}
	
int on_request_exit(struct book_low *book, struct idx_tbl *idx_tbl, int n){
	printf("さようなら\n");
	return 0;
}
	