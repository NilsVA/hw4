#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int CountDataValues(const string);
void read(double* , int ,const string );
void filter(double* S, int n);
void write(double* S, int n);



int main () {

int N ;						//Number of Filteriterations
cout << "Number of filter iterations = "; cin >> N;
const string filename = "noisy.txt";		//Filename of Data Origin

int n = CountDataValues(filename);		//Number of Data Values counted
						//for memory allocation,
						//only single column arrays work
						//correctly
//cout << n << endl;

double* S = new double[n];

	read(S,n,filename);			

	for(int i=1;i<=N;i++) filter(S,n);

	write(S,n);



delete[] S;

return 0;
}



int CountDataValues(const string filename){		//Function to Count DataValues
	ifstream cSignal(filename.c_str());
	int count = 0;				
	string text;
	while(getline(cSignal, text))
		{
		 count ++;
		}
	cSignal.close();
	return(count);
}



void read(double* S, int const n, const string filename){	//Reads the Data out of File into
	ifstream Signal(filename.c_str());			//Array S
	
	for(int i = 0; i<n; i++)
		{
		 Signal >> S[i];
		}
	Signal.close();
}

void filter(double* S , int const n){				//applies filter to the Signal
	
	double a = S[0];			
	double b,c=S[0];
	
	S[0] = (S[n-2]+S[0]+S[1])/3.0;
	for(int i=1; i<n-1 ;i++)
		{
		 b = S[i];
		 S[i] = (a + b + S[i+1])/3.0;
		 a = b;
		}
	S[n-1]= (a+S[n-1]+c)/3.0;

}

void write(double* S, int const n){				//writes Filtered Signal into new 
								//file
	ofstream out("filtered_data.txt");
	for (int i=0; i<n; i++)
		out << S[i] << endl;
	out.close();
}
