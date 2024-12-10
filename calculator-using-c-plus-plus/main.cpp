#include <iostream>

using namespace std;

int main(){
	float x, y,s=0,result;
	char operation,c;
		do{
			cout << "enter first number then operation then second number:\n";
			cin >> x >> operation >> y;
			goto first;
			cont:cout << "enter operation then number:\n";
			cin >> operation >> x;
			
			first:switch (operation) {
			case '+' : result = (result == 0) ? x + y : result + x; break;			
			case '-' : result = (result == 0) ? x - y : result - x; break;			
			case '*' : result = (result == 0) ? x * y : result * x; break;			
			case '/' : if (y != 0) {
			                	result = (result == 0) ? x / y : result / x;
			                } else if (x != 0) {
			                    cout << "Error: Division by zero.\n" << endl;
			                    goto end;
			                }
			                break;
			        	    default: cout << "Error: Invalid operation.\n"; goto end;
			       		}
        
			cout << "result is: " << result << endl;
			
			cout << "Do you want to continue? (Y/N)\n";
			cin >> c;
			y=0;
			if(c == 'y' || c == 'Y')
			goto cont;
			
	}while(0);
	
	end:cout << "thanks for using our app ;)";
	
	cin.ignore();
	cin.get();
		
	
    return 0;
}

