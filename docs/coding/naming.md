# Naming Conventions
## Variables
```C
int item_count;                // snake_case style
uint8_t pk_encryption[32];     // Abbreviations may be used. pk = public_key
```
## Functions
```C
void init_system();            // snake_case style
```
## Constants & Macros
```C
#define identity_sign_PUBLICKEYBYTES 32   // Combined: snake_case_CAPS
#define SUCCESS 0                         // All caps
```
## Structs & Types
Regular struct:
```C
struct student {          // The snake_case style
	int id;
	char name[50]
}
```
with `typedef`:
```C
typedef struct {
	uint8_t *buff;
	size_t len;
} DataBuffer;             // UpperCamelCase style
```
## Enums
```C
enum color {              // snake_case style
	COLOR_RED,            // All caps
	COLOR_GREEN
}
```
with `typedef`:
```C
typedef enum {
	CORE_OK               // All caps
	CRYPTO_ERR
} result_t;               // snake_case with '_t'
```