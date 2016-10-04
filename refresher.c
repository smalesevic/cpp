#include <iostream>


void notfun(int* array){
	//this segfaults y tho
	/*for(auto int num: array){
		std::cout << &num << "\n";		
	}*/
	for(int i=0; i<4;i++){
		std::cout << array[i] << "\n";
	}
}

int main(){
	int nums[4] = {1,2,3,4};
	notfun(nums);
	return 1;
}
