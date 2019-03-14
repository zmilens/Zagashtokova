#include "stroki.h"

MyString::MyString() : lenght(0)
{
	plaintext = new char[256]; //   
	plaintext[0] = '\0'; //     ,   
}

MyString::MyString(char c[]) : lenght(strlen(c))
{
	plaintext = new char[256]; //   
	strcpy(plaintext, c); //   
}

MyString::MyString(const char * c) : lenght(strlen(c))
{
	plaintext = new char[256]; //   
	strcpy(plaintext, c); //   
}

MyString::MyString(std::string str) : MyString(str.c_str()) //    
{

}

MyString::MyString(const MyString & s) : lenght(s.lenght)
{
	plaintext = new char[256]; //   
	strcpy(plaintext, s.plaintext); //   
}


MyString::~MyString()
{
	delete plaintext; //    
}

void MyString::clear()
{
	delete plaintext; //     ,    - 
	plaintext = new char[256]; //    
	plaintext[0] = '\0'; //     ,   
	lenght = 0; //   
}

void MyString::add(const char * c)
{
	strcat(plaintext, c); //    
	lenght += strlen(c); //   
}

void MyString::add(std::string str)
{
	add(str.c_str()); //     std::string      
}

void MyString::insert(const char * c, unsigned int index)
{
	if (index >= lenght) return;  //    /     
	//           

	char* before = new char[256]; //      ()
	strncpy(before, plaintext, index); //       index    ()
	before[index] = '\0'; //   

	strcat(before, c); //      before

	char* after = new char[256]; //      ()
	strncpy(after, plaintext + index, lenght - index); //         ()
	after[lenght - index] = '\0'; //   

	strcat(before, after); //        before

	strcpy(plaintext, before); //     
	lenght = strlen(plaintext); //   
	delete before, after; //    ,    - 
}

void MyString::insert(std::string str, unsigned int index)
{
	insert(str.c_str(), index); //     std::string      
}

void MyString::cut(unsigned int index, unsigned int count)
{
	if (index >= lenght || index + count >= lenght) return; //    /     
	// ,     ,       

	char* before = new char[256]; //      ()
	strncpy(before, plaintext, index); //       index    ()
	before[index] = '\0'; //   

	char* after = new char[256]; //      ()
	strncpy(after, plaintext + index + count, lenght - count - index); //         ()
	after[count + 1] = '\0'; //   

	strcat(before, after); //        before

	strcpy(plaintext, before); //     
	lenght = strlen(plaintext); //   
	delete before, after; //    ,    - 
}

MyString MyString::operator+(MyString s)
{
	MyString temp; //   
	temp.lenght = this->lenght; //   
	strcpy(temp.plaintext, this->plaintext); //    ()

	temp.add(s.plaintext); //  ()   
	return temp; //  
}

unsigned char* MyString::encrypt(unsigned char* password, unsigned char* iv, int* cr_len)
{
	unsigned char *crypted = new unsigned char[128]; // 
	int len; //   
	int ciphertext_len; //    

	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); //     

	EVP_EncryptInit_ex(ctx, //   /,   
		EVP_aes_256_cbc(), //     AES 256 (  )
		NULL,
		password, // //
		iv //  (  )
	);

	EVP_EncryptUpdate(
		ctx, //   
		crypted, //  : ,    
		&len, //  :   
		(unsigned char*)plaintext, //  :  
		strlen(plaintext)
	); //   :   

	ciphertext_len = len;

	// 5.   
	// ,       
	EVP_EncryptFinal_ex(ctx, crypted + len, &len);
	ciphertext_len += len;

	// 6.  
	EVP_CIPHER_CTX_free(ctx);

	*cr_len = ciphertext_len;

	return crypted; //  
}

void MyString::decrypt(unsigned char* crypted, int cr_len, unsigned char* password, unsigned char *iv)
{
	int len; //  
	int plaintext_len; //    

	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); //     

	EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, password, iv); //   AES,   

	EVP_DecryptUpdate(ctx, (unsigned char*)plaintext, &len, crypted, cr_len); // 

	plaintext_len = len;
	EVP_DecryptFinal_ex(ctx, (unsigned char*)plaintext + len, &len); //  

	plaintext_len += len;
	EVP_CIPHER_CTX_free(ctx); //  

	plaintext[plaintext_len] = '\0'; //   
}

int MyString::find(const char * c)
{
	return *strstr(plaintext, c); //     
}

int MyString::find(std::string str)
{
	return find(str.c_str()); //     std::string      
}

void MyString::save(const char * name)
{
	FILE *f = fopen(name, "ab"); //    
	if (f != NULL) // ,      
	{
		fputs(plaintext, f); //  
		fclose(f); //  
	}
}

void MyString::load(const char * name)
{
	FILE *f = fopen(name, "rb"); //    
	if (f != NULL) // ,    
	{
		fgets(plaintext, 256, f); //      
		fclose(f); //  
	}
}

std::ostream& operator<< (std::ostream& os, const MyString& s)
{
	if (s.lenght > 0) //          
	{
		for (int i = 0; i < s.lenght; i++)
			os << s.plaintext[i];
	}
	else os << ""; //      

	return os;
}