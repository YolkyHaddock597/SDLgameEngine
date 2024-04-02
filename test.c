#include <stdio.h>

typedef struct {
    int x;
    float y;
    char z;
} MyStruct;

// Function to check if a struct is empty
int isStructEmpty(MyStruct s) {
    return (s.x == 0 && s.y == 0.0f && s.z == '\0'); // Assuming empty structs have all fields set to 0 or NULL
}

int main() {
    MyStruct arr[3]; // Array of 3 structs

    // Initialize array elements to arbitrary values

    // Finding empty structs
    printf("Empty structs found at indexes: ");
    for (int i = 0; i < 3; i++) {
        if (isStructEmpty(arr[i])) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}
